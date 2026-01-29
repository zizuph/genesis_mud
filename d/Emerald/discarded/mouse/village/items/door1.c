/* door coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/door";
#include "../../mouse.h"

void create_door()  {
     set_other_room(ROOT+"village/rooms/guest1");
     set_door_id("mouse: guestdoor1");
     set_door_name(({"blue room door","blue door","door"}));
     set_door_desc("A plain oaken door which leads to the blue guest room.\n");
     set_open(0);
     set_open_desc("The door to the blue guest room is slightly ajar.\n");
     set_closed_desc("The door to the blue guest room is firmly closed.\n");
     set_fail_pass("Ouch! Walking into that door must have hurt!\n");
     set_open_command("open");
     set_open_mess(({"opens the blue room door.\n",
        "The door to the hallway opens.\n"}));
     set_fail_open(({"The door to the blue guest room is already open.\n",
        "The door to the blue guest room must be unlocked before it "+
        "may be opened.\n"}));
     set_close_mess(({"closes the blue room door.\n",
        "The door to the hallway closes.\n"}));
     set_fail_close("The door to the blue guest room is already closed.\n");
     set_key(ROOT+"village/items/bluekey");
     set_lock_name("lock");
     set_locked(1);
     set_lock_desc("A shiny brass lock that looks as if it could be "+
        "unlocked by a skeleton key.\n");
     set_lock_command("lock");
     set_lock_name("lock");
     set_lock_mess(({"locks the blue room door.\n", 
        "You hear a click as the door to the hallway is locked.\n"}));
     set_fail_lock(({"The blue room door is already locked.\n",
        "The blue room door must be shut in order to lock it.\n"}));
     set_unlock_command("unlock");
     set_unlock_mess(({"unlocks the blue room door.\n",
        "You hear a click as the door to the hallway is unlocked.\n"}));
     set_fail_unlock("The door to the blue guest room is already unlocked.\n");
}


void
do_open_door(string mess)
{
     ::do_open_door(mess);

environment(this_object())->add_exit(ROOT+"village/rooms/guest1","blue");
}


void
do_close_door(string mess)
{
     ::do_close_door(mess);
     environment(this_object())->remove_exit("blue");
}


