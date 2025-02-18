/*
 * See the dyninst/COPYRIGHT file for copyright information.
 * 
 * We provide the Paradyn Tools (below described as "Paradyn")
 * on an AS IS basis, and do not warrant its validity or performance.
 * We reserve the right to update, modify, or discontinue this
 * software at any time.  We shall have no obligation to supply such
 * updates or modifications or any other form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "ParameterDict.h"
#include "MutateeStart.h"
#include "CmdLine.h"
#include "test_info_new.h"
#include "test_lib.h"
#include "remotetest.h"

#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

#include <sys/time.h>
#include <sys/resource.h>
#define log_printf(str, args...) do { if (getDebugLog()) { fprintf(getDebugLog(), str, args); fflush(getDebugLog()); } } while (0)

static void getPortHostnameFD(int argc, char *argv[], int &port, std::string &hostname, int &fd)
{
   for (unsigned i=0; i<argc; i++) {
      if (strcmp(argv[i], "-hostname") == 0) {
         hostname = argv[++i];
      }
      if (strcmp(argv[i], "-port") == 0) {
         port = atoi(argv[++i]);
      }
      if (strcmp(argv[i], "-socket_fd") == 0) {
         fd = atoi(argv[++i]);
      }
   }
}

int be_main(int argc, char *argv[])
{
   ParameterDict params;
   vector<RunGroup *> groups;

   struct rlimit infin;
   infin.rlim_cur = RLIM_INFINITY;
   infin.rlim_max = RLIM_INFINITY;
   int result = setrlimit(RLIMIT_CORE, &infin);

   int port;
   string hostname;
   int fd = -1;
   getPortHostnameFD(argc, argv, port, hostname, fd);
   if (port == 0 || !hostname.length()) {
      log_printf("[%s:%u] - No connection info.  port = %d, hostname = %s\n",
              __FILE__, __LINE__, port, hostname.c_str());
      return -1;
   }

  log_printf("[%s:%u] - Connecting to %s:%d\n", __FILE__, __LINE__, hostname.c_str(), port);
  Connection connection(hostname, port, fd);
  if (connection.hasError()) {
     log_printf("[%s:%u] - Error connecting to FE\n",
                __FILE__, __LINE__);
     if (getDebugLog()) fclose(getDebugLog());
     return -1;
  }

   RemoteOutputDriver remote_output(&connection);
   setOutput(&remote_output);


   log_printf("[%s:%u] - Connection established--ready to recv\n", __FILE__, __LINE__);

   parseArgs(argc, argv, params);
   getGroupList(groups, params);
   
   RemoteBE remotebe(groups, &connection);

   for (;;) {
      char *buffer = NULL;
      bool result = connection.recv_message(buffer);
      if (!result) {
         //FE hangup.
         break;
      }
      remotebe.dispatch(buffer);
   }
   if (getDebugLog()) fclose(getDebugLog());
   return 0;
}
