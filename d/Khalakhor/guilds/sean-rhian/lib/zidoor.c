//
// Zima's Inside Door room functions
//    Inherit this code in the room which is inside the door.
//    Assumes nearby room is Outside the Door
//    State of door mantained by this (Inside) room
//
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "zdoor.h"
 
object  outside; // pointer to room outside the door
string  opath;   // path    to room outside the door
string  odir;    // exit made available when door is open
int     key;     // NO_LOCK=0, BOLTABLE=1 or Key Value>1
int     dstatus;  // current dstatus of door; OPENED CLOSED LOCKED
 
string* did;      // array of id's for door, ie: ({"door","doors"})
string  dshort;   // short desc. of the door, used in emotes
string  dlong;    // long desc of the door; add_item(did,dlong);
int     plural;   // use plural verbs? "is" or "are"
int     pickskill;  // skill required to pick the lock
 
//
// query functions on globals
//
int    query_dstatus() { return dstatus; }
object pointer_me()    { return TO; }
 
//
// utility functions related to plurality
//
string dbe()     { if (plural) return "are"; else return "is"; }
string dswing()  { if (plural) return "swing"; else return "swing"; }
string itis()    { if (plural) return "They are"; else return "It is"; }
 
//
// setup_indoor
//
void setup_indoor(object o, string d, string* i, string s, string l,
                  int k, int pl, int st, int sk)
{
   outside  = o;
   opath    = MASTER_OB(outside);
   odir     = d;
   did      = i;
   dshort   = s;
   dlong    = l;
   key      = k;
   plural   = pl;
   dstatus   = st;
   pickskill = sk;
   if (dstatus==OPENED)
      {
      add_exit(opath,odir);
      add_item(did,dlong+" "+itis()+" standing open.\n");
      }
   else
      {
      remove_exit(odir);
      add_item(did,dlong+" "+itis()+" closed.\n");
      }
   outside->update_door((dstatus==OPENED),1);
}
 
//
// try_open - player tries to open the door
//
int try_open(object tp, string cmd)
{
   notify_fail("Open what? The "+did[0]+"?\n");
   if (member_array(cmd,did)<0) return 0;
 
   set_this_player(tp);
   switch (dstatus)
      {
      case OPENED: write("The "+dshort+" "+dbe()+" already opened!\n"); break;
      case LOCKED: write("The "+dshort+" "+dbe()+" locked.\n");         break;
      case CLOSED: write("You open the "+dshort+".\n");
                   tell_room(ENV(tp),QCTNAME(tp)+" opens the "+
                             dshort+".\n",tp);
                   tell_room(TO,"The "+dshort+" "+dswing()+" open.\n");
                   add_exit(opath,odir);
                   add_item(did,dlong+" "+itis()+" standing open.\n");
                   dstatus = OPENED;
                   outside->update_door(1);
      }
   return 1;
}
 
//
// try_close - player tries to close the door
//
int try_close(object tp, string cmd)
{
   notify_fail("Close what? The "+did[0]+"?\n");
   if (member_array(cmd,did)<0) return 0;
 
   set_this_player(tp);
   switch (dstatus)
      {
      case LOCKED:
      case CLOSED: write("The "+dshort+" "+dbe()+" already closed!\n"); break;
      case OPENED: write("You close the "+dshort+".\n");
                   tell_room(ENV(tp),QCTNAME(tp)+" closes the "+
                             dshort+".\n",tp);
                   tell_room(TO,"The "+dshort+" "+dswing()+" shut.\n");
                   remove_exit(odir);
                   add_item(did,dlong+" "+itis()+" closed.\n");
                   dstatus = CLOSED;
                   outside->update_door(0);
      }
   return 1;
}
 
//
// try_lock - player tries to lock the door
//
int try_lock(object tp, string cmd)
{
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
   else if (key==BOLTABLE)
      {
      write("You lock the "+dshort+".\n");
      tell_room(ENV(tp),QCTNAME(tp)+" locks the "+dshort+".\n",tp);
      dstatus=LOCKED;
      }
   else
      {
      thekey = present(ZDKEY+key,tp);
      if (objectp(thekey))
         {
         write("You lock the "+dshort+" using the "+(thekey->short())+".\n");
         tell_room(ENV(tp),QCTNAME(tp)+" locks the "+dshort+".\n",tp);
         dstatus=LOCKED;
         }
      else
         write("You do not have the correct key for the "+dshort+".\n");
      }
   return 1;
}
 
//
// try_unlock - player tries to unlock the door
//
int try_unlock(object tp, string cmd)
{
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
   else if (key==BOLTABLE)
      {
      write("You unlock the "+dshort+".\n");
      tell_room(ENV(tp),QCTNAME(tp)+" unlocks the "+dshort+".\n",tp);
      dstatus=CLOSED;
      }
   else
      {
      thekey = present(ZDKEY+key,tp);
      if (objectp(thekey))
         {
         write("You unlock the "+dshort+" using the "+(thekey->short())+".\n");
         tell_room(ENV(tp),QCTNAME(tp)+" unlocks the "+dshort+".\n",tp);
         dstatus=CLOSED;
         }
      else
         write("You do not have the correct key for the "+dshort+".\n");
      }
   return 1;
}
 
//
// try_pick - the player tries to pick the lock on the door
//
int try_pick(object tp, string cmd)
{
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
   else
      {
      write("You attempt to pick the lock on the "+dshort+" and succeed!\n");
      tell_room(ENV(tp),QCTNAME(tp)+" picks open the lock on the "+
                        dshort+".\n");
      dstatus=CLOSED;
      }
   return 1;
}
 
//
// knocked - can be masked
//
void knocked(object tp)
{
   tell_room(TO,"Someone knocks on the "+dshort+".\n");
}
 
//
// knock
//
int knock()
{
   if (dstatus==OPENED)
      write("But the "+dshort+" "+dbe()+" open!\n");
   else
      {
      write("You knock on the "+dshort+".\n");
      tell_room(TO,QCTNAME(TP)+" knocks on the "+dshort+".\n");
      outside->knocked(TP);
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
// add_in_door_actions() - invoke in init() of inheriting room
//
void add_in_door_actions()
{
   add_action(&cmd_open(), "open");
   add_action(&cmd_close(),"close");
   add_action(&cmd_lock(), "lock");
   add_action(&cmd_unlock(), "unlock");
   add_action(&cmd_pick(), "pick");
   add_action(&knock(),    "knock");
}
