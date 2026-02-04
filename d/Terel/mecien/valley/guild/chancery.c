/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP      this_player()
#define TO      this_object()
#define EN environment

object seated;

leave_inv(object ob, object to){
  if(ob == seated){
  write("You rise from the chair as you leave this place.\n");
  get_up();
  tell_room(EN(ob), QCTNAME(ob) + " rises from the chair.\n", ob);
}
  ::leave_inv(ob, to);
}

init(){
   ::init();
  add_action("sit", "sit");
   add_action("rise", "rise");
}

rise(){
   if(!seated) return 0;
   if(seated != TP) return 0;
   write("You rise from the chair.\n");
  get_up();
   tell_room(EN(TP), QCTNAME(TP) + " rises from the chair.\n");
   return 1;
}

get_up(){
  seated->remove_prop(LIVE_S_EXTRA_SHORT);
  seated = 0;
}

void
create_room()
{  
   object scroll;
   
   set_short("Chancery");
   set_long("This small vaulted chamber is fashioned of gray stone,\n"
      + "stone of ages. It is supported by eight pillars of the same\n"
      + "stone. The floor is marked with cryptic patterns and the\n"
      + "ceiling painted with a fresco.\n"
      + "A large stone chair rests upon a dias at the north end of\n"
      + "the hall, it dominates here. The hall has one window at its\n"
      + "south side, the light gleaming multi-colors down upon the\n"
      + "chair at the north end.\n"
      + "A small ivory arch, draped with a red curtain leads west\n"
      + "from this hall. An open passage leads east.\n"
   );
   
   add_item("curtain", "It is deep red and made from thick velvet.\n");
   add_item("arch", "It is ivory and has an inscription upon it.\n");
   add_item("chair", "A large stone chair, it looks to have been cut\n"
      + "from a single piece of stone. It is a dark color.\n");
   add_item(({"floor", "patterns"}), 
      "The floor is decorated with strange and cryptic patterns\n"
      + "that seem to confuse the mind with mysteries.\n");
   add_item("dias", "A simple circular set of steps around the chair.\n");
   add_item("pillars", "They are of ancient gray stone.\n");
   add_cmd_item("arch", "read", 
      "Mirabili Arcanus Magistratus Sedes In Seclusus\n");
   
   add_item(({"ceiling", "painting", "fresco"}),
      "It is the image of a mystical elf, he is draped with a white\n"
      + "mantle and holds a seven green stars in his hands. Upon his\n"
      + "head is a wreath of silver leaves. He is shrouded in mist.\n");
   add_item("window", "It is a large window and made from stained glass\n"
      + "and silver. The form of a tree is depicted within it. The tree\n"
      + "having a white trunk with silver traced green leaves.\n");
   add_cmd_item("seventh pillar", "touch", "@@star");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_HIDE, -1);
   add_exit(GUILD_DIR + "library",  "east", 0);
   add_exit(GUILD_DIR + "conclave", "west", "@@my_status");
   scroll=clone_object(GUILD_DIR + "scroll");
   scroll->move(TO);
}

sit(string str){
   if(seated){
      if(seated == TP){
         write("You are already seated in the chair.\n");
         return 1;
      }
      TP->catch_msg(QCTNAME(seated) + " is seated upon the chair.\n");
      seated->catch_msg("You sense the desire of " + QCTNAME(TP) + " to sit upon the chair.\n");
      return 1;
   }
   
   if(TP->query_mystic_rank() < 6){
      TP->catch_msg("You are not worthy to be seated there.\n");
      TP->add_mana(-200);
      return 1;
   }
   seated = TP;
   write("You seat yourself upon the chair.\n");
   TP->add_prop(LIVE_S_EXTRA_SHORT, ", who is seated upon the chair");
   tell_room(EN(TP), QCTNAME(TP) + " sits upon the chair.\n", TP);
   return 1;
}



star(){
   if(TP->query_mystic_rank() < MYSTIC_STAR) {
      write("Nothing happens.\n");
      return 1;
   }
   if(TP->query_mystic_rank() > MYSTIC_STAR) {
      write("You touch the stone, but feel you have passed the time of this mystery.\n");
      return 1;
   }
   tell_room(environment(TP), QCTNAME(TP) +
      " is suddenly surrounded by a halo emanating from the ceiling.\n", TP);
   write("A glowing light of peace takes you away.\n");
   TP->move_living("M", "/d/Terel/mecien/valley/guild/starchamber");
   return 1;
}

my_status()
{
   object mseal;
   
   if (!MEMBER(TP)) {
      write("Only those of the Order may enter there.\n");
      return 1;
   }
   if (TP->query_mystic_rank() < MYSTIC_ARCHON) {
      write("That place is reserved for the archons.\n");
      return 1;
   }
   if(TP->query_present_rank() == 0 && TP->query_real_name()!="mecien"){
      return 1;
   }
   write("You enter the curtain and a solemn burden weighs upon you.\n");
   seteuid(getuid(TO));
   mseal=clone_object(GUILD_DIR + "mseal");
   mseal->move(TP);
   return 0;
}
