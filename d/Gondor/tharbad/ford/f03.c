/* 
 *      /d/Gondor/tharbad/ford/f03.c
 *
 *      Modification log:
 *      26-Jan-1997, Olorin:    General revision,
 *                              changed inheritance,
 *                              changed commands and function to cross the river.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* how hard is it to swim across the water? */
#define HARD_TO_SWIM  15 
#define SWIM_FATIGUE  30
#define THARBAD_BANK  (THARBAD_DIR + "ford/f02")
#define ERIADOR_BANK  (THARBAD_DIR + "ford/f04")

public void
create_roads() 
{
    set_street("old stone road");
    set_where("central");
    set_county("Tharbad");
    set_land("Enedwaith");
    set_mountain("Greyflood valley");
    set_vegetation("thorns and stinging nettles");
    set_extraline("The island is covered by the ruins of a mighty "
        + "stone pillar and the rubble from the two arches of the "
        + "bridge that once spanned the two arms of the river.");

    add_item( "island", BSN("Between the two arms of the river "
        + "Greyflood, this island is used by those who try to swim "
        + "across the river as a place to rest. It is covered by "
        + "rubble and ruins, which are covered by thorns and "
        + "stinging nettles."));
    add_item( ({ "pillar", "ruins", "rubble", "stone pillar", }),
        BSN("In the middle of the island stand the ruins of a mighty "
            + "stone pillar which once supported the two arches of "
            + "the bridge spanning the water to both sides of the "
            + "island. But now the pillar has crumbled down and "
            + "the arches have fallen long ago, covering the island "
            + "with rubble."));
    add_item( ({ "river", "greyflood", "gwathlo", "river greyflood",
                     "water", "bank", "banks", "shore", "shores", }), 
        BSN("The water of the Greyflood is brown and murky, running "
            + "sluggishly down towards the Sea. On the southeastern "
            + "bank, one can see the ruins of Tharbad, on the bank "
            + "to the northwest are the wide plains of southern "
            + "Eriador. Both banks are about the same distance away, "
            + "and an experienced swimmer might be able to reach them."));
    add_item( ({ "city", "tharbad", }), BSN("The ruins of Tharbad are "
        + "just barely visible on the southeast bank of the river. "
        + "Toppled pillars and fallen stone walls stand testament to "
        + "the forces of the terrible flood that destroyed the city "
        + "and the bridge."));
 
    add_exit(THARBAD_BANK, "southeast", &swim(HARD_TO_SWIM, SWIM_FATIGUE), 
	     SWIM_FATIGUE, 1);
    add_exit(ERIADOR_BANK, "northwest", &swim(HARD_TO_SWIM, SWIM_FATIGUE), 
	     SWIM_FATIGUE, 1);

    set_drink_from( ({ "river", "greyflood", "gwathlo", }) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
}

public int
cross_river(string str)
{
    object  tp = TP;
    string  vb = query_verb();

    if (vb == "swim")
        NFN("Swim to Tharbad or swim to Eriador?");
    else
        NFN("Cross the river in which direction?\n" +
            "To Tharbad or to Eriador?\n");

    if (!strlen(str))
        return 0;

    switch (LOW(str))
    {
    case "river":
    case "greyflood":
    case "gwathlo":
    case "across river":
    case "across greyflood":
    case "across gwathlo":
        return 0;
    case "greyflood to tharbad":
    case "water to tharbad":
    case "river to tharbad":
    case "to tharbad":
        if (!swim(HARD_TO_SWIM, SWIM_FATIGUE))
        {
            tp->move_living("across the river towards Tharbad",
                THARBAD_BANK);
            tp->add_fatigue( - SWIM_FATIGUE);
        }
        break;
    case "to eriador":
    case "river to eriador":
    case "water to eriador":
        if (!swim(HARD_TO_SWIM, SWIM_FATIGUE))
        {
            tp->move_living("across the river towards Eriador",
                ERIADOR_BANK);
            tp->add_fatigue( - SWIM_FATIGUE);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

public void
drink_message(string from)
{
    write("You drink some of the muddy water of the Greyflood.\n"
        + "It tastes as muddy as it looks.\n");
    say(QCTNAME(TP) + " drinks some water from the river.\n");
}

public void
init()
{
    ::init();

    init_drink();

    add_action(cross_river, "swim");
    add_action(cross_river, "cross");
}
