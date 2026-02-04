/* room1.c
   Mort 911004 */
/* Modified by Azireon, August 15, 1992, stab_loft2.c
   "All generations shall call me blessed"  Assumption 1992 */

inherit "/std/room";

#include <tasks.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define DIFFICULTY  (TASK_ROUTINE + 200)

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

object mouse;

reset_room(arg)
{
    if(!mouse)
    {
        if(present("mouse")) return;
        mouse = clone_object(TOWNDIR + "stable/dormouse");
        mouse->move(this_object());
    }
}

create_room()
{
    set_short("Stable loft");
    set_long(break_string(
      "This is the stable's loft, a wide open space as large as the " +
      "entire building.  Above your head, the rafters are lost in " +
      "an enveloping blanket of darkness.  A vast supply of straw " +
      "and hay has been stored here, in bales stacked up nearly " +
      "twelve feet.  You are at the end of a narrow walkspace that " +
      "leads eastward and comes to a dead end to the west.\n", 70) );

    add_item( ({ "rafter", "rafters" }), break_string(
      "It's too dark to see much but you can hear the flutter of " +
      "wings from time to time.\n", 70) );

    add_item( ({ "hay", "straw", "supply", "bale", "bales" }),
      break_string(
      "It is impossible to tell just how much hay is stored here.  " +
      "People must value being prepared for anything in these " +
      "conditions.  Some of the bales seem to have been knocked " +
      "somewhat out of place here.\n", 70) );

    add_item( ({ "walkway", "walkspace", "space" }),
      "It leads westward into darkness.\n");

    add_cmd_item(
        ({ "hay", "straw", "bale", "bales" }),
        "climb", "@@climb" );

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    add_exit(TOWNDIR + "stable/stab_loft1", "east", 0);

    mouse = clone_object(TOWNDIR + "stable/dormouse");
    mouse->move(this_object());

    reset_room();
}

/*
 * Function name:  climb
 * Description  : player attempts to climb on top of hay bales
 */

climb()
{
    int success;

    success = this_player()->resolve_task(DIFFICULTY,
        ({ SKILL_WEIGHT, 600, SS_CLIMB,
           SKILL_WEIGHT, 150, SS_DEX }) );

    if (success < 0)
    {
        write(break_string(
          "You start to climb up the pile of straw but then lose your " +
          "grip and fall down.\n", 70) );
        say(QCTNAME(this_player()) + " tried to climb up the pile of straw " +
          "but did not succeed.\n");
        return 1;
    }

    if (success < 20 )
    {
        write(break_string(
          "Struggling to maintain your grip, you manage to climb " +
          "up the pile of straw and pull yourself over the top.\n", 70));
        this_player()->move_living("struggling up the pile of straw",
                                    TOWNDIR + "stable/stab_loft3");
        return 1;
    }

    write(break_string(
      "You adroitly scale the pile of straw and pull yourself on " +
      "top of it.\n", 70) );
    this_player()->move_living("effortlessly hurdling the pile of straw",
                             TOWNDIR + "stable/stab_loft3");
    return 1;
}
