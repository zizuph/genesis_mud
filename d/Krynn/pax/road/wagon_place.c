/* wagon_place.c
 * The dwarven merchant stops here.
 * (move this file to /d/Krynn/pax/road/)
 *
 * Blizzard 1/06/2003
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>
#include <composite.h>

inherit  "/d/Krynn/pax/road/road_base.c";

object   dwarf, horse, wagon;

void
reset_pax_room()
{
    if ( !wagon )
    {
        wagon = clone_object("/d/Krynn/qualinesti/obj/wagon");
        wagon->move(TO, 1);
    }
    
    if ( !horse )
    {
        horse = clone_object("/d/Krynn/qualinesti/npc/horse");
        horse->move(TO, 1);
    }
    
    if ( !dwarf )
    {
        dwarf = clone_object("/d/Krynn/qualinesti/npc/kragh");
        dwarf->move(TO, 1);
    }
    
}

void
create_pax_room()
{
    /* Add warefare support */
    set_area_name(WAR_AREA_NEWPORT);
    
    reset_pax_room();
    
    set_short("On the plains, east of the road");
    set_long("@@long_descr");
    
    OUTSIDE;
    add_item(({"mountain", "mountains"}), "The Kharolis mountains " +
        "stretching from east to west, across the horizon. " +
        "They look quite inpenetrable, but maybe somewhere " +
        "there is a way over, or through, them.\n");
                                                                                                                      
    add_item(({"plain", "plains"}), "The flat plains of southern " +
        "Abanasinia, stretching out to all sides of you. Low " +
        "grass and scattered bushes are the only kinds of " +
        "vegetation growing on these plains.\n");
                                                                                                                                                               
    add_item(({"forest", "canopy"}), "The forest visible is the " +
        "outskirts of the elven kingdom Qualinesti. It is " +
        "rumoured that deep within the forest lies the rich " +
        "and beautiful city of Qualinost, capital of the " +
        "Qualinesti elves.\n");

    add_item("vegetation", "Low grass and scattered bushes.\n");

    add_item("grass", "Low grass covering the largest part of the " +
        "plains around you.\n");
                                                                                                                                                                                                                                    
    add_item("bushes", "Here and there, small groups of bushes break " +
        "the monotony of the flat plains.\n");

    add_item(({"track", "tracks"}),
        "There are some tracks on the ground. They were probably " +
        "left by some vehicle.\n");
        
    add_item("road", "You see a simple dusty road just to the west. " +
        "It leads southwest towards Pax Tharkas and to Newports, that " +
        "lays northeast from here.\n");
    
    add_exit(ROAD + "road2", "northwest", 0, 3);
}

string
long_descr()
{
    string ret_str;
    object shadow;
    
    ret_str = "You are standing on the plains, just east from the " +
        "road running across southern Abanasinia. South, the Kharolis " +
        "mountains stretches across the horizon from east to west. " +
        "Far off to the northwest you see the green canopy of a " +
        "huge forest. You also notice few tracks, left probably by " +
        "wheels of some vehicle, on the ground.";
    
    if ( shadow = P("_dragon_shadow_", TO) )
    {
        ret_str += "You see a huge shadow on the ground, slowly " +
            "gliding " + shadow->query_direction() + "wards.";
    }
    
    ret_str += "\n";
    
    return ret_str;
}

                                                                                                                                                                                                                                  