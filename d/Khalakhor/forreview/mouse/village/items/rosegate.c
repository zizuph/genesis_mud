/* door coded by Elizabeth Cook/Mouse, March 1997 */

inherit "std/door";
#include "../../mouse.h"

void create_door()  {
     set_other_room(ROOT+"village/rooms/cottent");
     set_door_id("mouse: rosegate");
     set_door_name("gate");
     set_door_desc("A thick wooden gate.\n");
     set_open(0);
     set_open_desc("The gate is ajar.\n");
     set_closed_desc("The gate is closed.\n");
     set_fail_pass("Ouch! Walking into that gate must have hurt!\n");
     set_open_command("open");
     set_open_mess(({"opens the gate.\n","The gate opens.\n"}));
     set_fail_open("The gate is already open.\n");
     set_close_mess(({"closes the gate.\n",
        "The gate closes.\n"}));
     set_fail_close("The gate is already closed.\n");
   
}


void
do_open_door(string mess)
{
     ::do_open_door(mess);
     environment(this_object())->add_exit(
         ROOT+"village/rooms/cottent","southwest");
}


void
do_close_door(string mess)
{
     ::do_close_door(mess);
     environment(this_object())->remove_exit("southwest");
}


