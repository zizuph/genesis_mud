/*
**  MCLUB - Memorial Shrine, Lower Level, Sacristry/Storage Room
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       7/25/95   Created. Contains a keyring from which the player
**                       can get an unlimited # of copper keys (to the bell-
**                       tower - no value keys) and 1 gate key; contains a
**                       cabinet with ritualistic equipment(objects/cabinet.c);
**                       contains an initially empty chest to store items
**                       (weapons rack that does NOT keep contents over
**                       reboot).
*/
inherit "/std/room";
inherit "/d/Calia/clubs/mclub/specials/check_memlist";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object cabinet,chest;
int    gatekey_here=1;
 
void reset_room() {
   object TO=this_object();
   if (!(cabinet)) {
      cabinet=clone_object(OBJ_DIR+"cabinet");
      cabinet->move(TO);
   }
   if (!(chest)) {
      chest=clone_object(OBJ_DIR+"chest");
      chest->move(TO);
   }
}
 
create_room() {
   set_short("Sacristry");
   set_long(
      "The cold bare walls of this chamber mark it as the storage room "+
      "of the conclave, euphimistically called the sacristry. A small box "+
      "sits on a shelf by the entrance, next to a lamp which lights "+
      "the room. A ring of keys hangs from a peg on the wall.\n");
 
   add_item(({"ring","keys","ring of keys"}),
      "@@exa_ring");
   add_item("peg",
      "It angles out of the wall. A ring of keys hangs from it.\n");
   add_item(({"room","chamber","sacristry"}),
      "It is four inornate walls of stone. Not much else to say.\n");
   add_item("shelf",
     "It is a small shelf on the wall used for a lampstand. There is also "+
     "a small box sitting on it.\n");
   add_item("lamp",
      "It is a small oil lamp made of a tarnished metal, its "+
      "only value being the light it provides.\n");
   add_item("box",
      "It is a simple wooden box filled with loose beads and thin strips "+
      "of leather. You can make a string of prayer beads with them if "+
      "you are worthy.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"shconcon","west",0);
   reset_room();
}
 
string exa_ring() {
   if (gatekey_here) return
      "It is a ring of small copper keys and one brass key "+
      "hanging on the wall from a peg.\n";
   else return
      "It is a ring of small copper keys hanging on the wall "+
      "from a peg.\n";
}
 
int take(string Parms) {
   object TR=this_object();
   object TP=this_player();
   object key;
   if (strlen(Parms)<1) return 0;
   if ((Parms=="key from ring")||(Parms=="copper key from ring")) {
      write("You take a copper key from the ring.\n");
      tell_room(TR,QCTNAME(TP)+" takes a copper key from the ring.\n",TP);
      key=clone_object(OBJ_DIR+"btkey");
      key->move(TP);
      return 1;
   }
   if ((Parms=="gate key from ring")||(Parms=="brass key from ring")) {
      if (!gatekey_here) {
         write("The brass gate key is gone.\n");
         return 1;
      }
      write("You take a brass key from the ring.\n");
      tell_room(TR,QCTNAME(TP)+" takes a brass key from the ring.\n",TP);
      key=clone_object(OBJ_DIR+"gatekey");
      key->move(TP);
      gatekey_here=0;
      return 1;
   }
   return 0;
}
 
void return_copper_key(object key, object TR, object TP) {
   set_this_player(TP);
   write("You put the copper key on the ring.\n");
   tell_room(TR,QCTNAME(TP)+" puts a copper key on the ring.\n",TP);
   key->remove_object();
}
 
void return_gate_key(object key, object TR, object TP) {
   set_this_player(TP);
   write("You put the brass key on the ring.\n");
   tell_room(TR,QCTNAME(TP)+" puts a brass key on the ring.\n",TP);
   key->remove_object();
   gatekey_here = 1;
}
 
int Break(string cmd)
{
   object beads=present(MCLUB_BEADS,this_player());
   notify_fail("Break what? break beads?\n");
   if ((!beads)||(cmd!="beads")) return 0;
   write("You break your beads and they shatter into dust.\n");
   beads->remove_object();
   return 1;
}
 
int make(string Parms) {
   object TR=this_object();
   object TP=this_player();
   object beads=present(MCLUB_BEADS,TP);
   string *p;
   if (strlen(Parms)<1) { write("Make what?\n"); return 1; }
   p=explode(Parms," ");
   if (member_array("beads",p)<0) { write("Make what?\n"); return 1; }
   if (!(InMClub(TP)||check_memlist(TP->query_name())))
      { write("You seem unable to do that.\n"); return 1; }
   if (beads) { write("You already have a string of beads!\n"); return 1; }
   write("You take some loose beads and a leather string from "+
         "the box on the shelf.\n");
   write("You carefully fashion a string of prayer beads.\n");
   beads=clone_object(OBJ_DIR+"beads");
   beads->move(TP);
   tell_room(TR,QCTNAME(TP)+" takes some items from the box on the "+
                "shelf and fashions a string of prayer beads.\n",TP);
   return 1;
}
 
int put(string Parms) {
   object TR=this_object();
   object TP=this_player();
   object key;
   if (strlen(Parms)<1) return 0;
 
   if ((Parms=="key on ring")||(Parms=="key")) {
      key=present(MCLUB_BTKEY,TP);
      if (key)
         return_copper_key(key,TR,TP);
      else {
         key=present(MCLUB_GATEKEY,TP);
         if (key)
            return_gate_key(key,TR,TP);
         else
            write("You don't have a key that goes on the ring.\n");
      }
      return 1;
   }
 
   if (Parms=="copper key on ring") {
      key=present(MCLUB_BTKEY,TP);
      if (key)
         return_copper_key(key,TR,TP);
      else
         write("You don't have a copper key that goes on the ring.\n");
      return 1;
   }
   if ((Parms=="gate key on ring")||(Parms=="brass key on ring")) {
      key=present(MCLUB_GATEKEY,TP);
      if (key)
         return_gate_key(key,TR,TP);
      else
         write("You don't have the brass gate key.\n");
      return 1;
   }
   return 0;
}
 
void init() {
   ::init();
   add_action("take","take");
   add_action("take","get");
   add_action("put","put");
   add_action("put","replace");
   add_action(&Break(),"break");
   add_action("make","make");
}
