/* Created by Stevenson */
/*
Have a rope here to climb up and into caverns as a short cut.
If you weigh too much, the rope will break and you will have
to take the long way thru the mansion basement until the
next reboot.
*/
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit ICEINROOM;

static int rope_present = 0;

reset_icewall_room() {
   set_alarm(3.0,0.0,"show_reset");
}

show_reset() {
   if (!rope_present) {
      rope_present = 1;
      (QUEST+"cave")->make_rope();
      tell_room(QUEST+"cave","A little mouse with a rope runs across the room, ties the rope to a rock and then runs out.\n");
      tell_room(TO,"A rope descends from above.\n");
   }
}

init() {
   ADD("do_climb","climb");
   ADA("pull");
   ::init();
}


create_icewall_room() {
   set_short("Behind Waterfall");
   set_long(
      "You have ended up behind the waterfall. High "
      + "above you is the mysterious source of water "
      + "for this arctic realm. The ground is slightly rocky, but still "
      + "dry. Through the waterfall you can see light. "
      + "@@check_rope@@\n");
   
   add_cmd_item("rope","test","It isn't very strong.\n");
   add_item("waterfall","It crashes down from above.\n");
   add_item("water","The water is very cold and clear.\n");
   add_item("ground","What isn't covered by water is covered by rocks.\n");
   add_item("rocks","They resemble the rare rocks you would find anywhere.\n");
   add_item("light","It comes from the other side of the waterfall.\n");
   add_item("rope","@@exa_rope");
   add_cmd_item("waterfall","enter","@@go_waterfall");
   
   reset_icewall_room();
}

string check_rope() {
   if (rope_present)
      return "\nHanging from above is a rope. ";
   return "";
}

string exa_rope() {
   if (rope_present)
      return "The rope is old and quite frayed. You wonder how "
   + "strong it really is.\n";
   return "What rope?\n";
}

string go_waterfall() {
   write("You step out through the waterfall.\n");
   say(QCTNAME(TP)+" steps out through the waterfall.\n");
   tell_room(ICE_FOREST + "waterfall",QCTNAME(TP)
      + " arrives through the waterfall.\n");
   TP->move_living("M",ICE_FOREST+"waterfall",1,0);
   return "";
}

int do_climb(string str) {
   if ((!rope_present) || ((str != "rope") && (str != "up rope") && (str != "up"))) {
      NF("Climb What?\n");
      return 0;
   }
   write("Grasping the rope firmly, you slowly begin "
      + "hauling yourself up.\n");
   say(QCTNAME(TP)+" begins to climb the rope.\n");
   if ((TP->weight() / TP->max_weight()) * 100 > 70) {
      set_alarm(0.0,0.0,"rope_breaks");
      return 1;
   }
   tell_room(QUEST+"cave",QCTNAME(TP)+" climbs in through the waterfall.\n");
   set_alarm(0.0,0.0,"move_player");
   return 1;
}

move_player() {
   TP->move_living("M",QUEST+"cave",1,0);
}

rope_breaks() {
   break_rope();
   write("The weight you put on the rope is just too much. It snaps and you fall down.\n");
   say(QCTNAME(TP)+" falls down as the rope breaks.\n");
   tell_room(QUEST+"cave","The rope suddenly comes undone "
      + "and flies out through the waterfall.\n");
   TP->move_living("M",ICE_OUT+"back_waterfall");
}

int query_rope() { return rope_present; }
break_rope() {
   rope_present = 0;
   (QUEST+"cave")->break_rope();
}

int pull(string str) {
   if ((str == "rope") || (str == "the rope")) {
      write("You pull the rope and it starts to come loose.\n");
      say(QCTNAME(TP)+" pulls on the rope and a hidden bucket of water falls on "
         + TP->query_possessive() + " head.\n");
      return 1;
   }
   NF("Pull on what?\n");
   return 0;
}
