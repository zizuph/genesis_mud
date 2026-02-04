/* An example door made by Nick, 1991-12-19 */
/* Modified by Azireon, August 5, 1992, fgate2.c */

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"

inherit "/std/door";

create_door() {

    /* If you do this you'll get the default descriptions of the door, if you do
       this you only have to set the following functions.
    */
  ::create_door();

    /* You need an id
    */
   set_door_id("wooden gate");

    /* Here you decide wich command will take you through the door, 'enter' is no
       good pass command, at least not yet, since argument is not tested. If the
       first pass command has only one or two letters in it the second pass command
       will be used in the standard description of the door.
    */
   set_pass_command(( { "e", "east" } ));

    /* The name of the door. The first name in the array will be used in the
       standard description of the door.
    */

   set_door_name(( { "wooden gate", "gate" } ));

    /* This is the room on the other side of the door.
    */
    set_other_room(TOWNDIR + "forest7_1");

    /* If you want to have a look on the door you need to define the following
       sets too.
    
  set_lock_command("lock");
  set_lock_name( ({"lock"}) );
  set_unlock_command("unlock");

   
  set_open(0);           
  set_locked(1);       
    */
   
}
