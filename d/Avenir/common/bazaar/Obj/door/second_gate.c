// file name:  third_gate.c
// creator(s): Lilith Feb 2002
// last update:
// purpose:    Gate between admin and the city
// note:       
// bug(s):
// to-do:

inherit "/std/door";

#include "/d/Avenir/common/bazaar/admin/admin.h"


void
create_door()
{
    set_door_id("_avenir_second_gate_");
    set_pass_command(({"e", "east", "enter gate", "pass gate"}));
    set_fail_pass("The Second Gate is closed.\n");
    set_door_name(({"second gate", "gate", "gates"}));

    set_door_desc("This gate is really a portcullis. The grating "+
        "is made of the same bar-and-wire pattern as the sides of "+
        "the bridge.  Anyone who runs into it while it is lowered "+
        "would suffer serious damage from the razor-sharp wires. "+
        "To the people of Sybarus, it is known as the Third Gate.\n");
    add_item(({"arch", "archway"}),
        "It is a stone archway, part of a very smooth, very high wall "+
        "behind which the forbidden cities is concealed.\n");
    set_other_room(BAZ_ADMIN + "a17");
    set_open(1);
    set_open_desc("The open portcullis of the Second Gate lies east.\n");
    set_closed_desc("The Second Gate blocks the way east.\n");
    set_open_command(({"open","lift","push"}));
    set_open_mess(({"carefullly pushes the portcullis up.\n",
      "The portcullis of the Second Gate slowly raises.\n"}));
    set_fail_open(({"The portcullis of the Second Gate is already open.\n",
      "The Third Gate is locked.\n"}));
    set_fail_pass("Walking through a portcullis is a skill you haven't " +
       "mastered yet. Try lifting it first.\n");
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the portcullis down.",
       "The portcullis of the Second Gate lowers to the ground.\n"}));
   set_fail_close("The portcullis of the Second Gate is already closed.\n");
}
