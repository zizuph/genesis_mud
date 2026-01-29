/*
 *  file name:   ~landing.c
 *  creator(s):  Zielia
 *  last update:
 *  purpose:     Landing to the Ziggurat.
 *  note:
 *  bug(s):
 *  to-do:
 */
#pragma strict_types

#include "zigg.h"
#include <macros.h>
#include <stdproperties.h>

inherit ZIG_ROOM;


public void
reset_room(void)
{
    /* Empty but needed to enable resets.
     * reset_auto_objects is called in /std/room::reset_container().
     */
}

private int
move_to_stairs(void)
{
    object room = clone_object(STAIR_ROOM);

    if (!objectp(room))
    {
	write("There seems to be an issue using the stairs.\n"+
	    "Notify an Avenir wizard of the problem.\n");
	return 1;
    }

    write("You begin your journey up the Ziggurat steps...\n");
    say(QCTNAME(TP) +" begins to ascend the Ziggurat steps.\n");

    TP->move_living("M", room);
    return 1;
}

static void
zig_room(void)
{
    setuid();
    seteuid(getuid());

    set_short("At the foot of the Ziggurat");
    set_long("You stand at the foot of an enormous Ziggurat. Tiered levels "+
    	"constructed of enormous black stone blocks rise high overhead, haloed "+
    	"by the glow of the Source from the cavern walls beyond. Each tier "+
    	"stands several elves tall and is topped by lush, colorful gardens. "+
    	"Stairs carved into the black stone front stretch upwards across the "+
    	"edifice to a top unseen, climbing between cascading waterfalls.\n");
    	
    add_item(({"waterfalls", "waterfall", "cascading waterfalls", "aqueduct",
    	"channels", "water"}), "Small channels of water rush around the tiers "+
    	"of the Ziggurat, surrounding lush gardens and forming a sort of "+
    	"aqueduct and railing. As the channels reach the stairs, the water "+
    	"cascades from one level to the next, reversing direction to circle "+
    	"the next level. The waterfalls alternate from one side to the other "+
    	"as the water zigzags and spirals around the Ziggurat from the top "+
    	"to bottom where it drains away into a spring passing underground. "+
    	"The water here doesn't look extremely clean, but it is probably nicer "+
    	"near the top.\n");

    add_item(({"wall", "walls", "tiers", "tier", "blocks", "block", "stone",
    	"stones"}), "The looming Ziggurat is constructed of blocks of "+
    	"pure black stone as dark as waters of the black sea. Each level "+
    	"towers over your head. Three elves standing on each others shoulders "+
    	"still could not reach the top of the first level. The effort to "+
    	"build this monument to pleasure must have been staggering.\n");

    add_prop(ROOM_I_LIGHT, 2);

    add_exit("/dummy", "stairs", move_to_stairs);
    add_npc(CITY + "mon/zigg_overseer", 1, &->equip_me());

}
