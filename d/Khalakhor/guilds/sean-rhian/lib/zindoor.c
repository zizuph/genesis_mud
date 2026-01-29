//
// Zima's Inside Door room functions
//    State of door mantained by this (Inside) room
//
// Usage: - inherit this file
//        - invoke setup_indoor() in create_room() (see below for args)
//        - invoke add_indoor_actions in init()
// History:
// Coder       Date       Action
// ----------- ---------- -------------------------------------------------
// Zima        6/20/98    Created
//
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "zdoor.h"
#define  TPN (QCTNAME(tp))
 
object   outsiderm; // pointer to room outside the door
string   opath;     // path    to room outside the door
string   odir;      // exit made available when door is open
int      key;       // NO_LOCK=0, BOLTABLE=1 or Key Value>1
int      dstatus;   // current dstatus of door; OPENED CLOSED LOCKED
 
string*  did;       // array of id's for door, ie: ({"door","doors"})
string   dshort;    // short desc. of the door, used in emotes
string   dlong;     // long desc of the door; add_item(did,dlong);
int      plural;    // use plural verbs? "is" or "are"
int      pickskill; // skill required to pick the lock
function exitCheckFunction; // if any, invoked when play can pass thru door 
                            // must have prototype: int fun(object player)
//
// query functions on globals
//
int    query_dstatus() { return dstatus; }
 
//
// outside - return pointer to room outside the door
//
object outside() {
   if (!objectp(outsiderm)) outsiderm=(opath->get_this_object());
   return outsiderm;
}
 
//
// utility functions related to plurality
//
string dbe()     { if (plural) return "are"; else return "is"; }
string dswing()  { if (plural) return "swing"; else return "swings"; }
string itis()    { if (plural) return "They are"; else return "It is"; }
 
//
// update_doors()
//
varargs void update_doors(object actrm, int quiet=0) {
   string m;
   if (dstatus==OPENED) {
      remove_exit(odir);
      add_exit(opath,odir,"@@check_exit");
      add_item(did,dlong+" "+itis()+" standing open.\n");
      m="open";
   }
   else {
      remove_exit(odir);
      add_exit(opath,odir,"@@isclosed",0,1);
      add_item(did,dlong+" "+itis()+" closed.\n");
      m="shut";
   }
 
   if (actrm==TO)
      outside()->update_door((dstatus==OPENED),quiet);
   else {
      if (!quiet) tell_room(TO,"The "+dshort+" "+dswing()+" "+m+".\n");
      outside()->update_door((dstatus==OPENED),1);
   }
} // update_doors()
 
//
// isclosed()
//
int isclosed() {
   write("The "+dshort+" " + dbe() +" closed.\n");
   return 1;
}

//
// check_exit() - door is open, player can otherwise exit. This adds
//                any extra checks
int check_exit() {
    if (!exitCheckFunction) return 0; // no impediment, allow to pass
    return exitCheckFunction(TP);
}

//
// setup_indoor
//
void setup_indoor(
    string adir,    // direction open door makes available (ie "north")
    string apath,   // full path of room Inside/Behind the door
    string *aid,    // array of idents for door: ie: ({"door","doors","gate"})
                    //    player can use commands on these &
                    //    does add_item(id,dlong) when door opened/closed
    string adlong,  // long desc of doors; (see prev note on id)
    string adshort, // short desc used in "emotes"; ie "The 'heavy oak door'
                    //    swings shut"
    int    aplural, // use plural verbs?  ("door swings" or "doors swing")
    int    akey,    // NO_LOCK, BOLTABLE, or key number
    int    astatus, // initial status of door: OPENED CLOSED LOCKED
    int    apkskill,// pick skill needed to pick lock
    function exitFunction = 0 // prototype: int fun(object player)
    ) {
   odir      = adir;
   opath     = apath;
   did       = aid;
   dlong     = adlong;
   dshort    = adshort;
   plural    = aplural;
   key       = akey;
   dstatus   = astatus;
   pickskill = apkskill;
   exitCheckFunction = exitFunction;
   update_doors(TO,1);
} // setup_indoor()
 
//
// try_open - player tries to open the door
//
int try_open(object tp, string cmd) {
   notify_fail("Open what? The "+did[0]+"?\n");
   if (member_array(cmd,did)<0) return 0;
 
   set_this_player(tp);
   switch (dstatus)
      {
      case OPENED: write("The "+dshort+" "+dbe()+" already opened!\n"); break;
      case LOCKED: write("The "+dshort+" "+dbe()+" locked.\n");         break;
      case CLOSED: write("You open the "+dshort+".\n");
                   tell_room(ENV(tp),TPN+" opens the "+dshort+".\n",tp);
                   dstatus = OPENED;
                   update_doors(ENV(tp));
      }
   return 1;
} // try_open()
 
//
// try_close - player tries to close the door
//
int try_close(object tp, string cmd) {
   notify_fail("Close what? The "+did[0]+"?\n");
   if (member_array(cmd,did)<0) return 0;
 
   set_this_player(tp);
   switch (dstatus) {
      case LOCKED:
      case CLOSED: write("The "+dshort+" "+dbe()+" already closed!\n"); break;
      case OPENED: write("You close the "+dshort+".\n");
                   tell_room(ENV(tp),TPN+" closes the "+dshort+".\n",tp);
                   dstatus = CLOSED;
                   update_doors(ENV(tp));
   }
   return 1;
} // try_close()
 
//
// try_lock - player tries to lock the door
//
int try_lock(object tp, string cmd) {
   object thekey;
   notify_fail("Lock what? The "+did[0]+"?\n");
   if (member_array(cmd,did)<0) return 0;
   set_this_player(tp);
 
   if (key==NO_LOCK)
      write("There is no lock on the "+dshort+".\n");
   else if ((ENV(tp)!=TO)&&(key==BOLTABLE))
      write("The "+dshort+" can only be locked from the inside.\n");
   else if (dstatus==LOCKED)
      write("The "+dshort+" "+dbe()+" already locked.\n");
   else if (dstatus==OPENED)
      write("The "+dshort+" must be closed first.\n");
   else if (key==BOLTABLE) {
      write("You lock the "+dshort+".\n");
      tell_room(ENV(tp),TPN+" locks the "+dshort+".\n",tp);
      dstatus=LOCKED;
   }
   else {
      thekey = present(ZDKEY+key,tp);
      if (objectp(thekey)) {
         write("You lock the "+dshort+" using the "+(thekey->short())+".\n");
         tell_room(ENV(tp),TPN+" locks the "+dshort+".\n",tp);
         dstatus=LOCKED;
      }
      else
         write("You do not have the correct key for the "+dshort+".\n");
   }
   return 1;
} // try_lock()
 
//
// try_unlock - player tries to unlock the door
//
int try_unlock(object tp, string cmd) {
   object thekey;
   notify_fail("Unlock what? The "+did[0]+"?\n");
   if (member_array(cmd,did)<0) return 0;
   set_this_player(tp);
 
   if (key==NO_LOCK)
      write("There is no lock on the "+dshort+".\n");
   else if ((ENV(tp)!=TO)&&(key==BOLTABLE))
      write("The "+dshort+" can only be unlocked from the inside.\n");
   else if (dstatus!=LOCKED)
      write("The "+dshort+" "+dbe()+" already unlocked.\n");
   else if (key==BOLTABLE) {
      write("You unlock the "+dshort+".\n");
      tell_room(ENV(tp),TPN+" unlocks the "+dshort+".\n",tp);
      dstatus=CLOSED;
   }
   else {
      thekey = present(ZDKEY+key,tp);
      if (objectp(thekey)) {
         write("You unlock the "+dshort+" using the "+(thekey->short())+".\n");
         tell_room(ENV(tp),TPN+" unlocks the "+dshort+".\n",tp);
         dstatus=CLOSED;
      }
      else
         write("You do not have the correct key for the "+dshort+".\n");
   }
   return 1;
} // try_lock()
 
//
// try_pick - the player tries to pick the lock on the door
//
int try_pick(object tp, string cmd) {
   int tpskill = tp->query_skill(SS_OPEN_LOCK);
   notify_fail("Pick what? The lock?\n");
   if ((cmd!="lock")&&(member_array(cmd,did)<0)) return 0;
   set_this_player(tp);
 
   if (key==NO_LOCK)
      write("There is no lock to pick on the "+dshort+".\n");
   else if (dstatus!=LOCKED)
      write("But the "+dshort+" "+dbe()+" not locked!\n");
   else if (tpskill < pickskill)
      write("You attempt to pick the lock on the "+dshort+" but fail.\n");
   else {
      write("You attempt to pick the lock on the "+dshort+" and succeed!\n");
      tell_room(ENV(tp),TPN+" picks open the lock on the "+dshort+".\n",tp);
      dstatus=CLOSED;
   }
   return 1;
} // try_pick()
 
//
// knocked - can be masked
//
void knocked(object tp) {
   tell_room(TO,"You hear a knock from the other side of the "+dshort+".\n");
}
 
//
// knock
//
int knock() {
   if (dstatus==OPENED)
      write("But the "+dshort+" "+dbe()+" open!\n");
   else {
      write("You knock on the "+dshort+".\n");
      tell_room(TO,QCTNAME(TP)+" knocks on the "+dshort+".\n",TP);
      outside()->knocked(TP);
   }
   return 1;
}
 
//
// command functions
//
int cmd_close(string cmd) { return try_close(TP,cmd); }
int cmd_open(string cmd)  { return try_open(TP,cmd);  }
int cmd_lock(string cmd)  { return try_lock(TP,cmd);  }
int cmd_unlock(string cmd){ return try_unlock(TP,cmd);}
int cmd_pick(string cmd)  { return try_pick(TP,cmd);  }
 
//
// add_indoor_actions() - invoke in init() of inheriting room
//
void add_indoor_actions()
{
   add_action(&cmd_open(),   "open");
   add_action(&cmd_close(),  "close");
   add_action(&cmd_lock(),   "lock");
   add_action(&cmd_unlock(), "unlock");
   add_action(&cmd_pick(),   "pick");
   add_action(&knock(),      "knock");
}
 
//
// create_khalakhor_room()
//
void create_khalakhor_room() { }
