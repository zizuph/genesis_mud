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

int nuts;

reset_room(){
nuts = random(10) + 1;
}

create_room()
{
  set_short("Mystical Canopy");
  set_long(
   "Beautiful silvery-white branches stretch out in all directions, creating " +
"a magnificent canopy of vibrant life. Leaves of silvery-white grow thick " +
"and plush from the many limbs here, whispering as gentle breezes pass through. " +
"Small nuts grow dangle from the canopy, like treasures awaiting discovery.\n");
    add_prop(ROOM_I_INSIDE, 0);
   add_item("nuts", "They are small silvery-white nuts that grow from the branches.\n");
  add_cmd_item("nut", "pick", "@@pick_nut");
  add_item("leaves", "They are beautiful silvery-white leaves, growing out from all the branches, amazing in their vibrant color.\n");
  add_cmd_item("leaf", "pick", "You have a sense it would be wrong to pick the leaves.\n");
   add_cmd_item("leaves", "pick", "You have a sense it would be wrong to pick the leaves.\n");
   add_item("branches", "They are smooth and silvery-white in colour.\n");
   add_item("trunk", "It is thick and strong, silvery-white in colour.\n");
   add_item("canopy", "It is a thick canopy formed by the many branches, full of leaves and nuts.\n");
   set_alarm(1.0, -1.0, "make_creature");
   reset_room();
}

make_creature(){
  object ob, bf;
   seteuid(getuid());
   if(random(10) > 5){
  ob = clone_object("/d/Terel/mecien/valley/guild/raven");
  ob->move_living("X", TO);
}
    if(random(10) > 4){
   bf = clone_object("/d/Terel/mecien/valley/bf");
   bf->move(TO);
   }
}


pick_nut(){
 object ob;
  if(nuts){
  nuts --;
   seteuid(getuid());
  TP->catch_msg("You pick one of the small nuts from the boughs of " +
  "the canopy.\n");
   say(QCTNAME(TP) + " picks one of the small nuts from the boughs of the canopy.\n");
  ob = clone_object("/d/Terel/mecien/valley/guild/spells/mystic_nut");
  ob->move(TP);
  return 1;
  }
  TP->catch_msg("You cannot find any that are good to pick.\n");
   return 1;
}


