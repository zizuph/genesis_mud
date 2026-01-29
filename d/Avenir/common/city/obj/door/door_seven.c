// file name:  door_seven.c
// creator(s): Lilith Feb 2002
// last update: Lucius, Jan 2005: Updated door messages.
// purpose:    door to private room in the bath
// note:       opens onto BATH "priv_seven"
//             cloned to  BATH "ne_arc"
// bug(s):
// to-do:

inherit "/std/door";

#include "/d/Avenir/common/city/city.h"

void set_combo();

void
create_door()
{
    set_door_id("_avenir_bath_seven_");
    set_pass_command(({"ne", "northeast", "enter", "pass"}));
    set_fail_pass("The door to room seven is closed.\n");
    set_door_name(({"door", "door seven", "seventh door"}));
    set_door_desc("This is the door to Private Room Seven.\n");
    set_other_room(BATH +"priv_7.c");
    set_open(0);
    set_locked(1);
    set_open_desc("The door to room seven is open.\n");
    set_closed_desc("The door to room seven is closed.\n");
    set_open_command(({"open","push"}));
    set_open_mess(({"opens the door to room seven.\n",
      "The door opens.\n"}));
   set_fail_open(({"The door is already open.\n",
      "The door is locked.\n"}));
   set_close_command(({"close","shut"}));
   set_close_mess(({"closes the door to room seven.\n",
       "The door closes.\n"}));
   set_fail_close("The door is already closed.\n");
   set_lock_name(({"lock","keyhole"}));
   set_lock_desc("It appears to be the usual lock, made for "+
       "a key to fit into it.\n");
   set_lock_command(({"lock","turn key"}));
   set_lock_mess(({"locks the door to room seven.\n",
       "You hear a click.\n"}));
   set_fail_lock(({"The door is already locked.\n",
      "It is open. You can't lock it while it is open.\n"}));
   set_unlock_command(({"unlock","turn key"}));
   set_unlock_mess(({"locks the door to room seven.\n",
      "You hear a click.\n"}));
   set_fail_unlock("It is already locked.\n");
   set_key(700 + random(99));
   set_pick(100);  //not pickable

   set_combo();

}

void 
set_combo()
{
    int i;
    i = this_object()->query_key();
    "/d/Avenir/common/city/bath/bath.c"->set_seven_key(i);
}
