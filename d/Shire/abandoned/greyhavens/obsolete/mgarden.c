/*
 * /d/Shire/greyhavens/mgarden.c
 */

#pragma strict_types
inherit "/std/room";

#include "/sys/stdproperties.h"

/* prototypes */
public void     create_room();

/*
 * Function name:        create_room
 * Description:        The first step on the path;
 *                       Meditation Garden
 */
public void
create_room()
{
set_short("a garden path");
set_long("Herbacious shrubs yield intoxicating " +
"scents and sunlight plays in the leaves of the " +
"ancient trees.  You are immediately outside " +
"the sanctuary, standing on steps as old as the " +
"hills that lead into a garden.  Stillness pervades this " +
"place. There is an ivy-covered signpost, " +
"and two paths meet right where you stand.\n ");
add_item( ({"signpost", "post", "ivy-covered signpost"}) ,
"The ivy-covered post holds finely carved signs, one " +
"pointing east, one pointing northeast.\n ");
add_item( ({"signs"}) ,
"You see two signs, one pointing east, the other northeast.\n ");
add_item( ({"east sign"}) ,
"The sign states: All who seek peace will find it best " +
"to walk this way.\n ");
add_item( ({"northeast sign"}) ,
"The sign indicates: Follow this path, and you may be tested.\n ");
add_item( ({"ancient trees", "trees"}) ,
"Towering above you, these ancient trees provide shelter from " +
"the cruel sun and the driving rain. Of the many surrounding you " +
"one tree appears to be standing the most upright.\n ");
add_item( ({"upright", "upright tree", "tree", "birch tree"}) ,
"A black trunk stretches up high into the blue, eventually " +
"giving way to short sturdy limbs. Its elliptical leaves flutter " +
"in the light breeze. Its stature suggests that it is not a force " +
"to be reckoned with.\n ");
}
