//
// Branch Cmd  - inherit this in a room to allow 'break branch from tree'
//
// Zima   June 6, 1998
//
#include <macros.h>
#include "defs.h"
#include "../objects/branch.h"
#define  PCP "[a] 'branch' 'from' [the] 'tree' / 'shrub' / '"
 
int     numbranches=0;
int     branchnum=0;
 
int    query_numbranches()    { return numbranches; }
int    query_branchnum()      { return branchnum;   }
void   set_numbranches(int n) { numbranches=n;      }
void   set_branchnum(int n)
       {
       if ((n<0)||(n>=NUM_BRANCHES)) n=0;
       branchnum=n;
       }
 
int break_branch(string cmd)
{
   object branch, *nv=all_inventory(TP);
   string tree=BRANCH[branchnum];
 
   notify_fail("Break what? Branch from "+tree+"?\n");
   if (!(stringp(cmd) && parse_command(cmd,nv,PCP+tree+"'"))) return 0;
 
   if (!numbranches)
      write("None of the remaining branches may be broken from the "+
             tree+".\n");
   else
      {
      write("You break a branch from the "+tree+".\n");
      tell_room(TO,QCTNAME(TP)+" breaks a branch from the "+tree+".\n",TP);
      seteuid(getuid());
      branch=clone_object(SR_OBJ+"branch");
      branch->set_branch(branchnum);
      if (branch->move(TP))
         {
         tell_room(TO,"The branch falls on the ground.\n");
         branch->move(TO);
         }
      numbranches--;
      }
   return 1;
}
