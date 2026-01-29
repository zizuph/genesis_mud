//
// Zima's Outside Door room functions
//    Inherit this code in the room which is outside the door.
//    State of door mantained by the Behind room
//
// Usage: - inherit this file
//        - invoke setup_outdoor() in create_room() (see below for args)
//        - invoke add_outdoor_actions in init()
// History:
// Coder       Date       Action
// ----------- ---------- -------------------------------------------------
// Zima        6/20/98    Created
//
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "zdoor.h"
 
object  behindrm; // pointer to room behind the door
string  bpath;    // path    to room behind the door
string  fdir;     // exit made available when door is open
string* fid;      // array of id's for door, ie: ({"door","doors"})
string  dlong;    // long description of door
string  dshort;   // short desc of door, for emotes.
int     key;      // NO_LOCK=0, BOLTABLE=1 or Key Value>1
int     plural;   // use plural in descriptions?
 
//
// setup_outdoor
//
void setup_outdoor
    (
    string adir,    // direction open door makes available (ie "north")
    string apath,   // full path of room Inside/Behind the door
    string *aid,    // array of idents for door: ie: ({"door","doors","gate"})
                    //    player can use commands on these &
                    //    does add_item(id,dlong) when door opened/closed
    string adlong,  // long desc of doors; (see prev note on id)
    string adshort, // short desc used in "emotes"; ie "The 'heavy oak door'
                    //    swings shut"
    int    aplural  // use plural verbs?  ("door swings" or "doors swing")
    )
 
{
   fdir      = adir;
   bpath     = apath;
   fid       = aid;
   dlong     = adlong;
   dshort    = adshort;
   plural    = aplural;
   behindrm  = bpath->get_this_object();
}
 
//
// behind - return pointer to room behind the door
//
object behind()
{
   if (!objectp(behindrm)) behindrm=(bpath->get_this_object());
   return behindrm;
}
 
//
// update_door() - update the dstatus of the door. Invoked by behind
//                 door room.
//
varargs void update_door(int opened, int quiet=0)
{
   string d,ds;
   if (plural) { ds="swing"; d="They are"; } else { ds="swings"; d="It is"; }
   if (opened)
      {
      remove_exit(fdir);
      add_exit(bpath,fdir);
      add_item(fid,dlong+" "+d+" standing open.\n");
      if (!quiet) tell_room(TO,"The "+dshort+" "+ds+" open.\n");
      }
   else
      {
      remove_exit(fdir);
      add_exit(bpath,fdir,"@@isclosed",0,1);
      add_item(fid,dlong+" "+d+" closed.\n");
      if (!quiet) tell_room(TO,"The "+dshort+" "+ds+" shut.\n");
      }
}
int isclosed()
{
   write("The "+dshort+" is closed.\n");
   return 1;
}
 
//
// try_open - player tries to open the door
//
int try_open(string cmd)
{
   notify_fail("Open what? The "+dshort+"?\n");
   return behind()->try_open(TP,cmd);
}
 
//
// try_close - player tries to close the door
//
int try_close(string cmd)
{
   notify_fail("Close what? The "+dshort+"?\n");
   return behind()->try_close(TP,cmd);
}
 
//
// try_lock - player tries to lock the door
//
int try_lock(string cmd)
{
   notify_fail("Lock what? The "+dshort+"?\n");
   return behind()->try_lock(TP,cmd);
}
 
//
// try_unlock - player tries to unlock the door
//
int try_unlock(string cmd)
{
   notify_fail("Unlock what? The "+dshort+"?\n");
   return behind()->try_unlock(TP,cmd);
}
 
//
// try_pick - player tries to pick the lock
//
int try_pick(string cmd)
{
   notify_fail("Pick what? The "+dshort+"?\n");
   return behind()->try_pick(TP,cmd);
}
 
//
// knocked - can be masked
//
void knocked(object tp)
{
   tell_room(TO,"You hear a knock from the other side of the "+dshort+".\n");
}
 
//
// knock
//
int knock()
{
   string dbe;
   if (plural) dbe="are"; else dbe="is";
   if ((behind()->query_dstatus())==OPENED)
      write("But the "+dshort+" "+dbe+" open!\n");
   else
      {
      write("You knock on the "+dshort+".\n");
      tell_room(TO,QCTNAME(TP)+" knocks on the "+dshort+".\n",TP);
      behind()->knocked(TP);
      }
   return 1;
}
 
//
// add_out_door_actions() - invoke in init() of inheriting room
//
void add_outdoor_actions()
{
   add_action(&try_open(),   "open");
   add_action(&try_close(),  "close");
   add_action(&try_lock(),   "lock");
   add_action(&try_unlock(), "unlock");
   add_action(&try_pick(),   "pick");
   add_action(&knock(),      "knock");
}
 
//
// create_khalakhor_room()
//
void create_khalakhor_room()
{
}
