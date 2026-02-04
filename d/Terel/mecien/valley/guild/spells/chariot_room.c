/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#include "/d/Terel/common/terel_defs.h"

#define BSN(xx)        break_string(xx+"\n", 70)
#define NF(xx)         notify_fail(xx)
#define TP             this_player()
#define TO             this_object()
#define EN environment

object set_chariot(object ob);
object query_chariot();
object chariot;


set_chariot(object ob){
   chariot = ob;
}

query_chariot(){ return chariot; }



init(){
   ::init();
   add_action("away", "away");
}

away(string str){
   
   string *places;
   string dest;
   dest = "/d/Terel/common/road/cornerstone";
   places = ({ "shrine", "valley", "sparkle", "cornerstone" });
   if(member_array(str, places) > -1){
      if(str == "shrine") dest = "/d/Terel/mecien/valley/guild/entry";
      if(str == "valley") dest = "/d/Terel/mecien/valley/entrance";
      if(str == "sparkle") dest = "/d/Genesis/start/human/town/road4";
   }
   
  TP->catch_msg("You command the chariot to be off at once!\n");
  tell_room(EN(TP), QCTNAME(TP) + " commands the chariot to be off at once!\n", TP);
  chariot->set_dest_room(dest);
   chariot->do_depart();
   
   return 1;
}

create_room()
{
   set_short("Inside a mystic chariot");
  set_long(
   "This chamber is the inside of some strange and mysterious covered vehicle, a " +
"chariot of sorts. Draped with black silk and velvet, it is luxurious " +
"and startling, for everything about it seems otherworldly.\n");
   add_prop(ROOM_I_INSIDE, 1);
}



