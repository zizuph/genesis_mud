/* An example door made by Nick, 1991-12-19 */
/* used by Olorin to make door for          */
/* /d/Gondor/rohan/farm/road/house1.c       */
/* Dec-1992                                 */

inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door() 
{
/* You need an id, and both sides should have the same id               */
    ::create_door();
    set_door_id("road_cottage_door");

/* Here you decide wich command will take you through the door, 'enter' */
/* is no good pass command, at least not yet, since argument is not     */
/* tested. If the first pass command has only one or two letters in it  */
/* the second pass command will be used in the standard description of  */
/* the the door.                                                        */
    set_pass_command(({"n","north"}));

/* The name of the door. The first name in the array will be used in    */
/* the standard description of the door.                                */
    set_door_name(({"wooden door","door"}));
    set_door_desc("It looks like the typical door to a farmer's cottage.\n");

/* This is the room on the other side of the door.                      */
    set_other_room(FARM_DIR + "road/yard1");

/* If you want to have a look on the door you need to define the        */
/* following sets too.                                                  */
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");

/* The standard door is open and unlocked, if you want it differently   */
/* you should use these functions too:                                  */

  set_open(0);         /* 1 if open, 0 if closed */
  set_locked(0);       /* 1 if locked, 0 if unlocked */

/* There are also plenty of other things you can set in the door, but   */
/* this is all you need. Look in /std/door.c for more details on all    */
/* the set_functions()                                                  */
}
