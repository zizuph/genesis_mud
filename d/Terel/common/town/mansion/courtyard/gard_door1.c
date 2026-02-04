/* An example door made by Nick, 1991-12-19 */

#include "/d/Terel/common/terel_defs.h"

inherit "/std/door";

create_door() {

    /* If you do this you'll get the default descriptions of the door, if you do
       this you only have to set the following functions.
    */
  ::create_door();

    /* You need an id  
    */
   set_door_id("gardendoor");

    /* Here you decide wich command will take you through the door, 'enter' is no
       good pass command, at least not yet, since argument is not tested. If the
       first pass command has only one or two letters in it the second pass command
       will be used in the standard description of the door.
    */
   set_pass_command(({"e", "east", "out", "courtyard", "garden"}));

  set_door_desc(break_string("It's a wooden door with a screen, probably " +
	"leading to some sort of courtyard.\n",70));
  set_open_desc("A wooden door leads out to the courtyard.\n");
  set_closed_desc("A wooden door leads out to the courtyard.\n");

    /* The name of the door. The first name in the array will be used in the
       standard description of the door.
    */
   set_door_name(({"wooden door", "door", "garden door"}));

    /* This is the room on the other side of the door.
    */
   set_other_room(MANSION + "crt/clois41");

    /* If you want to have a look on the door you need to define the following
       sets too.
    */
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");

   set_open(0);
   set_locked(0);

    /* The standard door is open and unlocked, if you want it differently you
       should use these functions too:

           set_open(i)           1 if open, 0 if closed
           set_locked(i)         1 if locked, 0 if unlocked

       There are also plenty of other things you can set in the door, but this
       is all you need. Look in /std/door.c for more details on all the 
       set_functions()
    */
}
