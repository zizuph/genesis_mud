/* room1.c
   Mort 911004 */
/* field_1.c, modified by Azireon, August 9, 1992 */

inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

int i;  /* Test for hidden exit, 0 means closed, 1 open */

reset_room(arg)
{
    if (i == 1)
    {
        this_object()->remove_exit("west");
        this_object()->remove_my_desc();
        this_object()->add_my_desc(
          "A snowdrift has completely covered the stable door.\n");
        say(break_string(
          "A strong, howling wind blows an enormous snowdrift over " +
          "the stable door.\n", 70) );
        i = 0;
        return 1;
    }
    else
    return 1;
}

create_room()
{
    object door;

    set_short("Field");
    set_long(break_string(
      "It is extremely cold here.  Many trees have been cleared from " +
      "this area to make an open space and the wind, as a result, blows " +
      "through here quite fiercely, seeming to cut you to the " +
      "bone.  A fence, running along a path to the east, has enclosed " +
      "the field.  Beyond the fence is a neat, well-kept cottage.  To " +
      "the west stands a large stable, buried in a snow drift.\n", 70) );

    add_item( ({ "trees", "forest" }), break_string(
      "The tall, green pine trees of this forest seem to do well in the " +
      "cold.  They are covered with snow in such a way that the light " +
      "reflected from them gives them a silver color.\n", 70) );

    add_item( ({ "cottage" }), break_string(
      "This small wood and brick cottage is well kept and attractive.  " +
      "Although it is covered with snow, its door and step have been " +
      "neatly cleared.\n", 70) );

    add_item( "path",
      "The path to the east runs north and south into the forest.\n");

    add_item( ({ "stable", "large stable" }), break_string(
      "It is difficult to tell how large the stable is because it has " +
      "been almost completely covered by a snow drift.  Smoke is curling " +
      "up from its stone chimney.\n", 70) );

    add_item("smoke", "It is drifting up from the chimney.\n");

    add_item( "fence", break_string(
      "Constructed out of wooden beams lashed together, this fence has " +
      "marked out a considerably large field.\n", 70) );

    add_item( ({ "snow", "drift", "snow drift", "snowdrift" }),
      break_string(
      "Snow has encased the trees and most of the stable.  The snow " +
      "on the ground has been trodden down by hooves to form a very " +
      "slippery surface of ice that reflects the sunlight " +
      "brilliantly.\n", 70) );
/*
    door = clone_object(TOWNDIR + "stable/fgate2");
    door->move(this_object());
*/
    i = 0;  /* Door is initially set as closed */

    add_cmd_item(
        ({ "snow", "drift", "snowdrift", "door" }),
        ({ "remove", "clear", "move", "uncover" }),
        ({ "@@open", "@@open", "@@open", "@@open" }));

    add_exit(TOWNDIR + "forest7_1", "east", 0);

    reset_room();
}

/*
 * Function name: open
 * Description  : Unclears snow from stable door, akes west exit.
 */
open()
{
    if ( i == 0 )
    {
    write("You clear the snow away from the stable door.\n");
    write("Touching the snow has made you rather cold!\n");
    say(break_string(
      QCNAME(this_player()) + " clears away the snow from the stable " +
        "door.\n", 70) );
    add_exit(TOWNDIR + "stable/stable1", "west", 0);
    this_object()->remove_my_desc();
    this_object()->add_my_desc(
      "Someone has cleared the snow away from the stable door.\n");
    i = 1;
    return 1;
    }
    else
    {
        write("The snow has already been cleared from the door.\n");
        return 1;
    }
}

