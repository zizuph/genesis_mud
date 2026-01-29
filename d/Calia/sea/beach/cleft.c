// ROOM:  cleft

    /* Calia Domain

    HISTORY

    [02-09-14] Created by Uhclem from [C:\CALIA\SEA\BEACH\CLEFT.DOC].

    PURPOSE

    This room represents a cleft in the rocky barrier that formerly prevented
    travel south of the seaside village.  It links the village to a new
    cliff-and-beach area coded by Tigerlily.  There are no special functions in
    this room; it exists purely to add a bit of geographic realism to the
    seaside layout. */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// ROOM DEFINITION

void
create_room()

{

    /*
     *  DESCRIPTION    
     */

    set_short("path through cleft in the rocks");

    set_long("You stand in a cleft in the craggy rocks that" +
        " border the south end of a little fishing village." +
        " A steep, jagged cliff looms further to the" +
        " southwest, and waves regularly sweep across the" +
        " narrow rocky path that separates the cliff face" +
        " from the sea.\n");

    /*
     *  EXITS    
     */

    add_exit(BEACH + "village7", "northwest");
    add_exit(BEACH + "cliff/rocks4", "southwest");

    /*
     *  ITEMS    
     */

    add_item(({"village", "little village", "fishing village"}),
        "The village is a cluster of simple huts. Small boats," +
        " some laden with nets and fish, signal the local industry," +
        " as does the distinctive aroma wafting south.\n");

    add_item(({"rocks", "coastline", "cleft", "space", "craggy rocks"}),
        "The rocks are jagged and slippery except for the" +
        " cleft where you're standing. It looks as if a section" +
        " of the rocks broke away, leaving a space large" +
        " enough to walk through.\n");

    add_item(({"huts", "simple huts"}),
        "The simple huts are wooden and painted in various colours.\n");

    add_item(({"path", "rocky path", "narrow path",
        "cliff", "steep cliff", "jagged cliff", "high cliff"}),
        "The high cliff is separated from the sea by a narrow," +
        " rocky path. Both the cliff and the path curve" +
        " toward the southwest, so you can't see from" +
        " here what lies beyond.\n");

    add_item(({"waves", "sea", "blue-green sea"}),
        "The blue-green sea stretches all the way to the" +
        " horizon. Waves wash across the sandy path" +
        " regularly, leaving behind bits of seaweed and foam.\n");

    add_item(({"seaweed", "foam", "bits", "bits of seaweed", "bits of foam"}),
        "As the waves wash across the sand, they deposit little" +
        " bits of seaweed and foam and wash away any footprints.\n");

    add_item(({"boats", "small boats", "fishing boats", "nets", "fish"}),
        "You can see boats of various colors near the village" +
        " and farther out to sea. Some seem to have nets and fish" +
        " in them, but it's difficult to tell much more about" +
        " them from this distance.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    /*
     *  ROOM TELLS    
     */

    set_tell_time(80);

    add_tell("A large wave crashes against the rocks and sprays you" +
        " with a fine mist.\n");

    add_tell("A swarm of small flies buzzes briefly around" +
        " the rocks, then abruptly takes off and disappears.\n");

    add_tell("A boat pushes off from the village toward the open sea.\n");

    add_tell("A gull lands on the rocks, pokes its bill into a" +
        " few cracks, and then flies off.\n");

    add_tell("A gull lands on the rocks, pokes its bill into a" +
        " few cracks, snatches a small fish that had been washed" +
        " up by the waves, and then flies off.\n");

    add_tell("A boat steadily makes its way through the" +
        " waves toward the village.\n");

    add_tell("Someone in the village shouts happily as if he has" +
        " brought in a prize catch.\n");

}
