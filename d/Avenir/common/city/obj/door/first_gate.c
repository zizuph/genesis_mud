// file name:  first_gate.c
// creator(s): Lilith Feb 2002
// last update:
// purpose:    First Gate, on the outside
// note:       opens onto CITY /entry/courtyard.c
//             cloned to BAZ_AMIN a18.c
// bug(s):
// to-do:

inherit "/std/door";

#include "/d/Avenir/common/city/city.h"

void
create_door()
{
    set_door_id("_avenir_first_gate_");
    set_pass_command(({"s", "south", "enter gate", "pass gate"}));
    set_fail_pass("The First Gate is closed.\n");
    set_door_name(({"first gate", "gate", "gates"}));

    set_door_desc("This is the First Gate. Beyond it lies the "+
        "Forbidden City. "+
        "It is comprised of two granite slabs so large that "+
        "part of you wonders how they were moved into place. "+
        "A golden trefoil, the symbol of Sybarus, has been carved "+
        "into the stone.\n");
    add_item(({"arch", "archway"}),
        "It is a stone archway, part of a very smooth, very high wall "+
        "behind which the Forbidden City is concealed.\n");
    set_other_room(CITY +"entry/courtyard.c");
    set_open(0);
    set_locked(1);
    set_open_desc("The First Gate is open.\n");
    set_closed_desc("");
    set_open_command(({"open","push"}));
    set_open_mess(({"causes an opening to appear at the base "+
       "of the First Gate.\n",
      "An opening suddenly appears in the base of the First Gate.\n"}));
   set_fail_open(({"The gate is already open.\n",
      "The First Gate is locked.\n"}));
   set_close_command(({"close","shut"}));
   set_close_mess(({"causes the opening near the base of the "+
       "First Gate to disappear.",
       "The opening in the First Gate suddenly closes.\n"}));
   set_fail_close("The First Gate is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("You can't find one.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"", ""}));
   set_fail_lock(({"The First Gate is already locked.\n",
      "It is open. You can't lock it while it is open.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"",
      "Something happens to the Gate.\n"}));
   set_fail_unlock("It is already locked.\n");
   set_key("_avenir_first_gate_key_");
   set_pick(100);  //not pickable

}
