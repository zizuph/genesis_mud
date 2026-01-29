/* 
 *      /d/Gondor/tharbad/ford/f02.c
 *
 *      Modification log:
 *      26-Jan-1997, Olorin:    General revision,
 *                              changed inheritance,
 *                              changed commands and function to cross the river.
 *   Jan 2000, Morbeche:  Changed swim requirements
 *   Mar 2000, changed OBJ_I_CONTAIN_WATER to -1
 *   Mar 2007, Toby: Fixed typo
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

// #define HARD_TO_SWIM 23      /*  This is the old value for swim = 50 */
#define HARD_TO_SWIM 16   /* This is the new swim for skill = 30 */
#define HARD_TO_CLIMB  7 /* how hard is it to climb the slope? */
#define SWIM_FATIGUE  30

public int     climb();
public string  cross_river();

public void
create_roads() 
{
    set_street("riverbank");
    set_where("southeast");
    set_county("Tharbad");
    set_land("Enedwaith");
    set_river_name("Greyflood");
    set_mountain("Greyflood slopes");
    set_vegetation("hanging green moss and purple lichen");
    set_extraline("The old South Road ends here on the bank of the "
      + "river Greyflood. The bridge which once crossed the river "
      + "here lies in ruins. A weathered statue rises among the "
      + "ruins of the bridge.");

    add_exit(THARBAD_DIR+"ford/f01","southeast", climb, 5);

    add_cmd_item( ({ "river", "greyflood", "water", "across river", }), 
      ({ "swim", "cross", }), cross_river);

    add_item( ({ "road", "old stone road", "old stone paved road",
	"old road", "south road", "old south road", }), 
      "The old South Road once crossed the Greyflood here in "
	+ "Tharbad on a mighty bridge, but long ago the bridge "
	+ "was destroyed and Tharbad deserted. Now the road ends "
	+ "here on the bank of the river among the ruins of the "
	+ "bridge. Only a small path continues into the water.\n");
    add_item( ({ "river", "river greyflood", "greyflood", "gwathlo", }),
      "The river Greyflood runs sluggishly in deep channels "
	+ "here, its water being brown and murky. It is almost "
	+ "too wide to cross, but an experienced swimmer might "
	+ "be able to reach the island in the middle of the "
	+ "river.\n");
    add_item( ({ "island", }), BSN("Across a wide expanse of brown "
	+ "and muddy water, you can make out a large island in the "
	+ "middle of the river. Long ago, there probably stood one "
	+ "of the pillars that supported the arches of the bridge "
	+ "before it was destroyed. An experienced swimmer might be "
	+ "able to reach the island."));
    add_item( ({ "bridge", "ford", "fords", "fords of tharbad", }),
      "The bridge which once crossed the Greyflood lies in "
	+ "ruins. All that remains of bridge are large heaps of "
	+ "rubble, one right here on this bank of the river, "
	+ "where the old road ends beneath it, another visible "
	+ "on the island in the middle of the river. A narrow path runs "
	+ "from the end of the bridge down to the water, probably "
	+ "used by those who cross the river by swimming across it.\n");
    add_item(({"city","tharbad","ruin","ruins","old city"}), 
	"Ruined houses rise on both sides of the road on this bank "
	+ "of the river. The road is partially choked by the "
	+ "fallen blocks of stone and masonry. The city is "
	+ "currently impassable.\n"); 
    add_item("water", "The water of the river is brown and murky, "
      + "deep and full of strange eddies.\n"); 
    add_item(({"statue","figure","obelisk"}), "An old statue of a "
      + "tall king in silver robes, inscribed in faded runes.\n"
      + "The runes say, 'Tar-Minastir, King of Numenor'.\n");

    set_drink_from( ({ "river", "greyflood", "gwathlo", }) );
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
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
}

public string
cross_river()
{
    object  tp = TP;
    int     tired = SWIM_FATIGUE;

    if (!swim(HARD_TO_SWIM, SWIM_FATIGUE))
    {
	SAYBB(" leaves swimming across the river.");
	tp->move_living("M", THARBAD_DIR + "ford/f03");
	if (tp->query_encumberance_weight() > 80)
	    tired *= 2;
	tp->add_fatigue(-tired);
	if ( TP != tp )
	    set_this_player(tp);
	SAYBB(" arrives swimming across the river.");
    }
    return "";
}

public int
climb()
{   
    object  tp = TP;
    int     climb_try = (HARD_TO_CLIMB / 2 + random(HARD_TO_CLIMB) + 1),
    skill = tp->query_skill(SS_CLIMB);

    if (skill < climb_try)
    {
	tp->reduce_hit_point(climb_try - skill);
	write("You stumble and momentarily lose your footing.\n");
	say(QCTNAME(tp) + " stumbles.\n");
	return 1;
    }

    write("You climb over the rubble.\n");
    return 0;
}
