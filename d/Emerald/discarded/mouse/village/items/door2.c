/* door coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/door";
#include "../../mouse.h"

void create_door()  {
     set_other_room(ROOT+"village/rooms/guest2");
     set_door_id("mouse: guestdoor2");
     set_door_name(({"green room door","green door","door"}));
     set_door_desc("A plain oaken door which leads to the green guest room.\n");
     set_open(0);
     set_open_desc("The door to the green guest room is slightly ajar.\n");
     set_closed_desc("The door to the green guest room is firmly closed.\n");
     set_fail_pass("Ouch! Walking into that door must have hurt!\n");
     set_open_mess(({"opens the green room door.\n",
        "The door to the hallway opens.\n"}));
     set_fail_open(({"The door to the green guest room is already open.\n",
        "The door to the green guest room must be unlocked before it "+
        "may be opened.\n"}));
     set_close_mess(({"closes the green room door.\n",
        "The door to the hallway closes.\n"}));
     set_fail_close("The door to the green guest room is already closed.\n");
     set_key(ROOT+"village/items/greenkey");
     set_lock_name("lock");
     set_locked(1);
     set_lock_desc("A shiny silver lock that looks as if it could be "+
        "unlocked by a skeleton key.\n");
     set_lock_command("lock");
     set_lock_name("lock");
     set_lock_mess(({"locks the green room door.\n", 
        "You hear a click as the door to the hallway is locked.\n"}));
     set_fail_lock(({"The green room door is already locked.\n",
        "The green room door must be shut in order to lock it.\n"}));
     set_unlock_command("unlock");
     set_unlock_mess(({"unlocks the green room door.\n",
        "You hear a click as the door to the hallway is unlocked.\n"}));
     set_fail_unlock("The door to the green guest room is already unlocked.\n");
}


void
do_open_door(string mess)
{
     ::do_open_door(mess);
     environment(this_object())->add_exit(
                 ROOT+"village/rooms/guest2","green");
}


void
do_close_door(string mess)
{
     ::do_close_door(mess);
     environment(this_object())->remove_exit("green");
}


