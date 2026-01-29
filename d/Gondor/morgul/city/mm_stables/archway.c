/*
 *  /d/Gondor/morgul/city/mm_stables/archway.c
 *
 *  The archway that leads into the stables of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/std/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "mm_stables.h"

void
create_room()
{
    ::create_room();
    
    set_short("In a darkened archway in the eastern parts of " +
              "Minas Morgul");
    set_long("As you move in the darkened archway, you hear footsteps " +
             "echoing further down the cobbled way. The air is stale here. " +
             "With each step, the smells of moisture, animal skins and " +
             "fresh droppings thicken. Ornamental borders run along the " +
             "lower part of each wall, all the way through the archway. " +
             "In the far end, the archway seems to open up in a yard of " +
             "some kind.\n");
    
    add_item(({"skin", "skins"}),
              ("You look around for an animal skin, but apart from some " +
               "hairs you find yourself to be stuck only with the smell of " +
               "them.\n"));
    
    add_item(({"dropping", "droppings"}),
              ("These are horse-droppings, most likely, but you refrain " +
               "from investigating the matter further.\n"));
    
    add_item(({"borders"}),
              ("Both borders are around three feet high, in three " +
               "registers. In some places, the white marble still shines " +
               "forth beneath the damp dirt which now covers most of the " +
               "borders. You will have to decide which border to study " +
               "more closely, the left or the right one.\n"));
    
    add_item(({"left border"}),
              ("The left border depicts an array of horses setting out " +
               "from a walled city with a tower. An air of anticipation " +
               "lingers over the horses, which have all been crafted with " +
               "open nostrils, raised ears, and half-opened mouths, but " +
               "the self-admiration put into this masterpiece serves now " +
               "only as a reminder of what this city of Minas Ithil " +
               "once was.\n"));
    
    add_item(({"right border"}),
              ("Only a few unbroken pieces remain of its marble " +
               "sculptures, which seem to have formed a series. You can " +
               "barely make out what could be two separate landmasses. " +
               "Inbetween, and relatively unscathed, you clearly discern " +
               "two ships, and some remains of what could possibly be a " +
               "third one. The reminder of the sculptures have been so " +
               "scurvily chopped as to be past recognition.\n"));
    
    add_prop(ROOM_I_INSIDE, 0);
    
    add_exit("../barrstr4.c", "west", 0, 0);
    add_exit("court.c", "east", 0, 0);
}
