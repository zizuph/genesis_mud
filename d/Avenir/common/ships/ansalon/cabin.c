// Underwater storeroom   (/d/Avenir/common/port/uw11.c)
 // creator(s):             Glinda may -95
 // last update:            Lilith, Oct 2004 - fixed cloning bug in search.
 // purpose:                "Noise" for the underwater quest. Is also
 //                         supposed to hold some treasures that can be
 //                         found if you stay long enough to kill the octopus
 // note:
 // bug(s):
 // to-do:
#pragma strict_types

#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";

void
create_room()
{
     set_short("In the captains cabin of a ship");
     set_long("You are in the cabin of a large transport ship. " +
         "The cabin is what one could say a normal ship cabin. " +
         "Not much of furniture and what there is, is well " +
         "secured to prevent it from falling around in rough " +
         "weather.\n");
     add_item("furniture", "The furniture consists of a table, " +
         "a bunk and a carpet on the flooring.\n");
     add_item("table","A typical ship table safely secured to " +
         "the flooring.\n");
     add_item("bunk","The bunk is build in the bulkhead and " +
         "is made of wood.\n");
     add_item("carpet","The carpet is dark blue and is made " +
         "of some robust fabric.\n");
     add_exit("/d/Avenir/common/ships/ansalon/deck", "up");
 }

void
reset_room()
{
    object deck;

    deck = find_object("/d/Avenir/common/ships/ansalon/deck");

    if (!(deck))
        return;
    if ((present("Barney", deck)) || (present("Barney", deck)))
        return;
    deck->call_thief();
    return;

}

