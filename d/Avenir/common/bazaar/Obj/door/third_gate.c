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
    set_door_id("_avenir_third_gate_");
    set_pass_command(({"e", "east", "enter gate", "pass gate"}));
    set_fail_pass("The Third Gate is closed.\n");
    set_door_name(({"third gate", "gate", "gates"}));

    set_door_desc("This gate dominates this courtyard, easily visible "+
        "from all sections. It is made of wood from the kesoit tree, "+
        "which is both very dark and highly fire-resistant. It consists "+
        "of two half-doors cut to fit perfectly into the archway leading "+
        "toward the Forbidden City. It is known as the Third Gate.\n");
    add_item(({"arch", "archway"}),
        "It is a stone archway, part of a very smooth, very high wall "+
        "behind which the forbidden cities is concealed.\n");
    set_other_room(BAZ_ADMIN + "a15");
    set_open(0);
    set_locked(1);
    set_open_desc("The Third Gate is open to the east.\n");
    set_closed_desc("The Third Gate blocks the way east.\n");
    set_open_command(({"open","turn","push"}));
    set_open_mess(({"slowly pushes the massive doors of the "+
      "Third Gate open.\n",
      "The massive doors of the Third Gate slowly open.\n"}));
   set_fail_open(({"The gate doors are already open.\n",
      "The Third Gate is locked.\n"}));
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"pulls the doors of the Third Gate closed.\n",
       "The Third Gate swings closed.\n"}));
   set_fail_close("The Third Gate is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It is a massive lock with an oddly small keyhole.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"turns a key in the lock of the Third Gate.\n",
      "You hear a click from the lock on the Third Gate.\n"}));
   set_fail_lock(({"The Third Gate is already locked.\n",
      "You must shut the gate before you lock it.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"turns a key and unlocks the Third Gate.\n",
      "You hear a click from the lock on the Third Gate.\n"}));
   set_fail_unlock("It is already locked.\n");
   set_key("_avenir_third_gate_key_");
   set_pick(100);  //not pickable

}
