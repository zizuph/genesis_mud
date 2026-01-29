/*
 *  /d/Gondor/minas/citadel/battlement11.c
 *
 *  The Battlement: The Embrasure
 *
 *  Alto, 20 April 2001
 * 
 *  Revision history:
 *  - Fixed quest for modern uptimes (Gorboth, Aug. 2018) 
 *  - Finwe April 2019: Fixed ring quest stage time so it calls rq_stage()
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/minas/lib/dinen_funcs.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "/d/Gondor/common/lib/clock.h"


#define INNER_MINAS "/d/Gondor/minas"
#define SEAT_NAME   "seat"
#define SEAT_CAPACITY  2

public void    create_gondor();
public void    init();
public void    leave_inv(object ob, object dest);
public string  look_at(string arg);     /* VBFC for chairs */
//int            rq_stage_stored = rq_stage();

static object Halfling;


public int
query_igard_broken()
{
//    if (rq_stage_stored < RQ_LEFT_HENNETH_ANNUN)
    if (rq_stage() < RQ_LEFT_HENNETH_ANNUN)
    {
        return 0;
    }

    return 1;
}

public void
create_gondor()
{
    set_short("Embrasure of the Battlement");
    set_long("This place is at the east end of the great outthrust "
        + "Battlement where there is an embrasure in the walls. A "
        + "stone seat rests beneath the sill. From here you might, like a "
        + "mariner in a mountainous ship, look sheer down upon the First Gate "
        + "seven hundred feet below or scan far beyond at the lands spreading "
        + "out before the city. A narrow walk leads west.\n");


    add_exit(INNER_MINAS + "/citadel/battlement10", "west", check_sitting, 1);

    add_chair(SEAT_NAME,
        "[down] [in] / [on] [the] [first] 'seat' / 'stone seat'",
        SEAT_CAPACITY, "on");


    add_battlement_items();

    add_item(({"battlement"}), "This is the east end of the great "
        + "Battlement built upon the peak of the mighty bastion of stone.\n");
    add_item(({"bastion"}), "Partly from the primeval "
        + "shaping of the hill, partly from the mighty craft and labour of "
        + "old, the towering bastion of stone stands up from the First Gate, "
        + "rising up to its peak, upon which you are standing now.\n");
    add_item(({"first gate", "gate"}), "It lies far below and six "
        + "great circles "
        + "of the city outward. When you lean out of the embrasure, you "
        + "can see tiny figures moving in and out of the Gate. A wave of "
        + "vertigo sends you retreating quickly back to safety.\n");
    add_item(({"figures", "tiny figures"}), "You assume they are men, "
        + "but from here they look almost like ants marching into their "
        + "hill.\n");
    add_item(({"plain"}), "The large open land before the city rolls away "
        + "as far as the eye can see in a panorama that cannot be taken "
        + "in without scanning through a wide arc. Perhaps you should "
        + "try to scan the environment.\n");
    add_item(({"embrasure", "walls", "gap", "wall"}), "The wall is "
        + "broken by a huge "
        + "gap facing east. From here the Men of Gondor keep watch over "
        + "the lands between the Pelennor and the Ephel Duath. Who "
        + "knows what you would see if you tried to scan the environment "
        + "through it?\n");
    add_item(({"walk", "stone", "path"}), "Cobbled in colourful red "
        + "and blue-grey stone, "
        + "the narrow walk forms a straight path to the west.\n");
    add_item(({"sill"}), "A lip of stone framing the bottom of the "
        + "embrasure.\n");
    add_item(({"city", "circles"}), "The six lower circles of Minas Tirith "
        + "descend from "
        + "below and behind you, such that the First Gate is directly beneath "
        + "you - seven hundred feet below!\n");
    add_item(({"panorama", "valley-bottom", "anduin", "river", 
        "great river", "sweep", "sea", "pelennor",
        "farmsteads", "barns", "byres", "townlands",
        "tilth", "orchards", "homesteads", "oast",
        "garner", "fold", "byre", "rills", "highland",
        "roads", "tracks", "road", "wains", "horseman",
        "saddle", "traffic", "highway", "hills",
        "outwall", "outwalls", "ramas echor", "ithilien",
        "fence", "fields", "causeway", "fords", "bridges",
        "osgiliath", "towers", "ruin", "ithilien", "kine",
        "ephel duath", "horizon", "river poros", "beasts",
        "white mountains", "ered nimraith", "lands",
        "mountains of shadow", "gloom", "garden"}),
        "Such things can only be seen by scanning the "
        + "environment through the embrasure.\n");


    add_item( ({"seat", "stone seat"}), &look_at(SEAT_NAME) );


    add_prop(ROOM_I_INSIDE, 0);

    set_tell_time(120);

    add_battlement_tells();


    reset_room();

}   


/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}


void
init()
{
   ::init();
    add_action("scan_here", "scan");
    init_room_chairs();  /* add chair verbs */

}

int
scan_here(string str)
{
    if (!strlen(str))
        NF0("Scan what?\n");

    switch (str)
    {
    case "environment":
        write("The panorama spreading out before the city is vast. It would "
            + "perhaps be easiest to scan certain parts of it. You can "
            + "scan the river, Pelennor, roads, outwalls, Osgiliath, "
            + "Ithilien, and mountains.\n");
        return 1;
    case "river":
        write("Away down in the valley-bottom, five leagues or so as the "
            + "the eye leaps, Anduin, the Great River, can "
            + "be seen grey and glittering, coming out of the north-west, "
            + "and bending in a mighty sweep south and west again, till it is "
            + "lost to view in a haze and shimmer. Far beyond lies the sea, "
            + "fifty leagues away.\n");
        return 1;
    case "pelennor":
        write("All the Pelennor is laid out before you, dotted into "
            + "the distance "
            + "with farmsteads and little walls, barns and byres, but nowhere "
            + "can be seen any kine or other beasts. The townlands are rich, "
            + "with wide tilth and many orchards, and homesteads there are "
            + "with oast and garner, fold and byre, and many rills rippling "
            + "through the green from the highlands down to Anduin.\n");
        return 1;
    case "roads":
        write("Many roads and tracks cross the green fields, and there "
            + "is much "
            + "coming and going: wains moving in lines toward the First "
            + "Gate, and others passing out. Now and again a horseman will "
            + "ride up, leap from the saddle, and hasten into the City. Most "
            + "traffic, however, goes out along the chief highway, "
            + "which turns "
            + "south and then bends swifter than the river, skirting the "
            + "hills before passing out of sight.\n");
        return 1;
    case "outwalls":
        write("The outwall of Rammas Echor was built with great labour after "
            + "Ithilien fell under the shadow of the Enemy. For ten leagues "
            + "or more it runs from the mountain's feet and so back again, "
            + "enclosing in its fence the fields of the Pelennor. At its "
            + "furthest point from the First Gate of the City, north-"
            + "eastward, the wall is four leagues distant, where men made "
            + "it high and strong; for at that point, upon a walled causeway "
            + "the road comes to the fords and bridges of Osgiliath and "
            + "passes through a gaurded gate between embattled towers. At "
            + "its nearest point, south-eastward, the wall is little more "
            + "than a league from the City.\n");
        return 1;
    case "osgiliath":
        write("This was a city, the chief city of Gondor, of which "
            + "Minas Tirith "
            + "was only a fortress. It is the ruin of Osgiliath on either "
            + "side of Anduin, which the enemies of Gondor took and burned "
            + "long ago. It was won back in the days of the "
            + "youth of Denethor II, not to dwell in, but to hold as an "
            + "outpost. Less than a year ago, Fell Riders issued from Mordor "
            + "and won back the crossings, and many of the best Men of Gondor "
            + "were slain. Presently, Gondor holds only the half of Osgiliath "
            + "that stands on the west side of Anduin.\n");
        return 1;
    case "ithilien":
        write("A beautiful forest of verdant-green lies beyond the Anduin "
            + "and extends to the Ephel Duath just visible on the furthest "
            + "horizon, and also south, where it is bounded by the River "
            + "Poros. Although it stands under the shadow of the East, it "
            + "yet retains a wholesome quality. Rumour speaks that Men of "
            + "Gondor, Rangers of the Westlands, fight on beneath its fair "
            + "and fragrant leaves.\n");
        return 1;
    case "mountains":
        write("Behind Mount Mindolluin, the White Mountains of the "
            + "Ered Nimraith "
            + "stretch into the western horizon. To the east, beyond the "
            + "garden of Ithilien is the Ephel Duath, the Mountains of Shadow. "
            + "They loom just on the verge of sight, their jagged edges "
            + "softened by wellnigh twenty leagues of misty air. The gloom "
            + "surrounding them seems to be growing and gathering, "
            + "very slowly, "
            + "slowly rising to smother the regions of the sun.\n");
        return 1;
    default:
        NF0("What do you want to scan? The environment?\n");
    }

}


/*
 * Function name:   leave_inv
 * Description :    mask parent to be sure that departing players
 *                  are removed from chair/sofa occupants
 */

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */

/*
 * Function name:   look_at
 * Description :    VBFC to describe chair/sofa + occupants
 */

public string
look_at(string arg)
{
     if (arg == SEAT_NAME)
    {
     return "This is a small stone seat upon which you may sit as "
        + "you scan the environment through the embrasure. It is just "
        + "big enough for two people.\n" +
         sitting_on_chair(SEAT_NAME, this_player(), 0);
    }

} /* look_at */

public void
reset_room()
{
    if (query_igard_broken())
    {
        Halfling = clone_npc(Halfling, INNER_MINAS + "/npc/pippin");
        return;
    }

    if (objectp(Halfling))
    {     
        Halfling->command("emote peers at the sky and departs.");
        Halfling->remove_object();
    }
}


