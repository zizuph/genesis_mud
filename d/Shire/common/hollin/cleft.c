#include "outroom.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define AWARENESS(tp) tp->query_skill(SS_AWARENESS)
#define FR_TRAPS(tp)  tp->query_skill(SS_FR_TRAP)

int lever_up;
int alarm_id;

create_outroom() 
{
   set_short("Cleft");
   set_long(
      "You are in a narrow north-south stretching cleft with mountains "
      + "on each side. The cleft seems to go further south, but since there is "
      + "a large hole that leads down to a "
      + "half-darkened cave. You might slide down there, and perhaps you can "
      + "come out again the same way. ");
   add_item("cleft",
      "It is very narrow, but since there is a large hole here, you can't follow it.\n");
   
   add_item(({"cave", "hole"}),
      "Well, perhaps it is easy to climb up again...\n");
   
   add_item("trap", "@@exa_trap@@\n");
   add_item("lever", "@@exa_lever@@\n");
   
   add_item(({"mountains", "mountain", "wall", "walls"}),
      "Which wall do you mean, the east or the west wall?\n");
   
   add_item(({"east wall", "east mountain"}),
      "@@exa_west_wall@@\n");
   
   add_item("crack",
      "The crack is very narrow, perhaps only hobbits could enter.\n");
   
   add_item(({"west wall","west mountain"}),
      "The mountain seems far to difficult to climb.\n");
   
   add_cmd("climb", "[down] [the] [hole] [cave]", "down");
   add_neg("climb", "[mountain] [mountains]", "No chance, too steep!\n");
   
   add_cmd("enter", "[down] [the] [hole] [cave]", "down");
   add_cmd("slide", "[down]", "down", "Slide??\n");
   
   add_call("remove", "'trap'", "remove_trap", "Remove what?\n");
   add_call("disarm", "'trap'", "remove_trap", "Disarm what?\n");
   
   add_call("push", "'lever' [down]", "lever_down", "Push what?\n");
   add_call("pull", "'lever' [down]", "lever_up", "Pull what?\n");
   
   add_call("carefully", "'go' / 'slide' [down]", "force_down", "Carefully?\n");
   
   NORTH("plain_s");
   add_exit(STAND_DIR+"big_hole", "down", "@@chk_down@@");
   
   add_prop(OBJ_I_SEARCH_TIME, 2);
   add_prop(OBJ_S_SEARCH_FUN,"my_search");
   
   lever_up = 1;
}

reset_outroom()
{
   lever_up = 1;
   tell_room(TO,
      "You hear a squeeky sound from the cave beneath.\n");
}

exa_trap()
{
   tell_room(TO, QCTNAME(TP)+" examines a trap here!\n", TP);
   return
   "The trap seems like a very effective way of blocking the exit "+
   "south if you go down there. If you just slide down, you'll set "+
   "a trap when you land, thereby having huge slabs over your neck. "+
   "You probably should try to remove the trap before going down. "+
   "If you really want to slide down, just: carefully go down.";
}

exa_west_wall()
{
   tell_room(TO, QCTNAME(TP)+" examines the western wall.\n", TP);
   return
   "As you search the western wall you you find a very narrow crack "+
   "in the mountain, probably to small for you do enter.";
}

go_crack()
{
   if(TP->query_prop(OBJ_I_VOLUME)>60000)
      {
      TP->catch_msg(
         "You try to squeeze yourself into the crack, but it is simply "+
         "too narrow! You stop attempting this while thinking that a "+
         "small hobbit thief surely could have done the trick.\n");
      tell_room(TO,
         QCTNAME(TP)+" tries to enter the crack, but sighes when "+
         HE_SHE(TP)+" finds out that "+HE_SHE(TP)+" is too large.\n", TP);
      return 1;
   }
   TP->catch_msg("You manage to sqeeze yourself into the crack!!\n");
   TP->move_living("into the crack", STAND_DIR+"valley");
   return 1;
}

chk_down()
{
   if(call_other(STAND_DIR+"big_hole", "trap_installed")) {
      if(WIS(TP)+AWARENESS(TP)+FR_TRAPS(TP) > 125 || TP->query_npc()) {
         write("Wait!! Isn't that a trap or something!\n");
         write("Hmm, it seems like someone has made a trap here.\n");
         return 1;
      }
      else {
         write("You slide down into the hole.\n");
         alarm_id = set_alarm(0.2,0.0,"notify_going_down");
         return 0;
      }
   } else return 0;
}

notify_going_down()
   {
   remove_alarm(alarm_id);
   (STAND_DIR+"big_hole")->notify_step_on_trap(0, TP);
}

notify_easy_slide()
   {
   (STAND_DIR+"big_hole")->notify_step_on_trap(AWARENESS(TP)+DEX(TP), TP);
}

remove_trap()
{
   if(INT(TP)+DEX(TP)+AWARENESS(TP)+FR_TRAPS(TP)+random(100) > 4*70)
      {
      write("You successfully manage to disarm the trap!\n");
      say(QCTNAME(TP)+" successfully manages to disarm the trap!\n");
      call_other(STAND_DIR+"big_hole", "disarm_trap");
      return 1;
   } else {
      write("You try with all your cunning to disarm the trap, but fail.\n");
      say(QCTNAME(TP) + " fails to disarm a trap.\n");
      return 1;
   }
}

mixed
my_search(object tp, string str)
{
   if(str=="cleft"||str=="trap"||str=="traps"||str=="hole"||str=="lever")
      {
      return "Your search reveals a lever between the rocks!\n";
   }
   else
      return 0;
}

exa_lever()
{
   string str = "You can see that this is a lever, but you are not sure "+
   "what it can be used for. ";
   if(lever_up)
      str += "Right now, the lever is pulled up, so you might push it down.\n";
   else
      str += "Now, the lever seems pushed down, so you might want to pull it up.\n";
   
   return str;
}

set_lever_up(int up) { lever_up = up; }

lever_down()
{
   if(lever_up==0) {
      write("But it is already down!\n");
      return 1;
   }
   lever_up = 0;
   write("You push the lever down.\n");
   say(QCTNAME(TP)+" pushes a lever hidden in the rocks down.\n");
   (STAND_DIR+"big_hole")->install_trap();
   tell_room(TO,
      "You hear a squeeky sound from the cave beneath.\n");
   return 1;
}

lever_up()
{
   if(lever_up==1) {
      write("But it is already up!\n");
      return 1;
   }
   lever_up = 1;
   write("You pull the lever up.\n");
   say(QCTNAME(TP)+" pulls a hidden lever in the rocks in an "+
      "upright position.");
   
   (STAND_DIR+"big_hole")->reset_boulders();
   return 1;
}

force_down()
{
   if(call_other(STAND_DIR+"big_hole", "trap_installed"))
      {
      write("Even though you know the trap is not disarmed, you dare to "+
         "slide down into the hole.\n");
      TP->move_living("down", STAND_DIR+"big_hole");
      set_alarm(0.0, 0.0, notify_easy_slide);
      return 1;
   } else {
      write("You slide down the hole in hope of that the trap is disarmed..\n");
      TP->move_living("down", STAND_DIR+"big_hole");
      return 1;
   }
}
