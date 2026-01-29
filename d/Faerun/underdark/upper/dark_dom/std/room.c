#include "../defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit (P_UPPERDARK_STD + "room");

public void
dark_dom(void)
{
}

nomask public void
create_upperdark_room(void)
{
    set_faerun_region("dark dominion");

    set_short("Dark Dominion");
    set_long("You are within the confines of the Dark Dominion, in "+
	"the lightless land below the surface of Faerun. Dark stone "+
	"surrounds you from all directions, seeming to weigh down "+
	"upon you like a physical weight. An oppressive silence "+
	"hangs in the air, as dense as the stone around you.\n");

    set_noshow_obvious(1);

    set_atmosphere_interval(6);
    add_atmosphere("You get the feeling someone is watching your every move.\n");
    add_atmosphere("Water drips from above.\n");
    add_atmosphere("The air is filled with the echo of a dying scream.\n");
    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL );

    add_prop(ROOM_M_NO_TELEPORT, 1);

    dark_dom();
}

/*
 * Drow players know their way around.
 */
public int
query_noshow_obvious(void)
{
    return !(TP->query_underdark_race());
}

/*
 * Make it hard for players to follow.
 */
public int
check_follow(void)
{
    object who = TP->query_leader();

    if (objectp(who))
    {
	/* We can see our team leader. */
	if (who->check_seen(TP))
	    return 0;

	/* Maybe you follow, maybe you don't. */
	return random(2);
    }

    return 0;
}
