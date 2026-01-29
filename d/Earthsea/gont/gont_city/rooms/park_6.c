/* 
* Room at the north end of the park. 
* Contains an add_action for climb wall, which moves"
* the player to another room.
 *  Herbs added 1/31/98
 *  add_action disabled (until palace finished)
 *  Amelia
*
* Coded by Porta 971019.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/d/Earthsea/herbs/specials/hs";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Earthsea/herbs/herb_sets/park_herbs.h"

#define GARDENER_ROOM ("/d/Earthsea/guilds/gardeners/room/wall")

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("By a low stone wall");
    set_long("You arrive at a dark place in the birch"+
        " grove, where half-rotten stems from trees fallen"+
        " long ago are overgrown by a thick foliage of"+
        " new sprouts. Over your head the crowns of the"+
        " older trees shadow most of the light. Just in"+
        " front of you is a low stone wall, in bad repair"+
        " with green moss growing all over it. On the"+
        " other side of the wall, the birch grove"+
        " continues, but you can catch a glimpse of a"+
        " garden beyond.\n");
    add_item("stems","Half-rotten stems of trees fallen"+
        " long ago lie scattered around on the ground,"+
        " giving after as you put your foot on them.\n");
    add_item(({"foliage","sprouts"}),"The new birch sprouts"+
        " growing everywhere here makes it very difficult"+
        " to walk around.\n");
    add_item("wall","A low stone wall is in front of you,"+
        " in bad repair with moss growing thick on and"+
        " between the black cut rocks it is built from. " +
        "You can easily climb over the wall.\n");
    add_item("grove","This must be the thickest part of"+
        " the grove you have seen this far. On the other"+
        " side of the wall the birch trees continues, but"+
        " you can see the green lawns of a garden beyond.\n");
    add_item("crowns","The leafy branches over your head"+
        " entwine to form a compact roof, hindering most of"+
        " the sunlight from coming through.\n");
    add_item("moss","Green, humid moss grows thick on the"+
        " old stone wall.\n"); 
    set_up_herbs(select_herb_files(PARK_HERBS), PARK_LOCATIONS, 3);
    add_exit("park_5", "south");
}

public int
climb_wall(string str)
{
    object tp = this_player();

    if(!str || !parse_command(str, this_object(),
        "[over] [the] [low] [stone] [garden] 'wall'"))
        return notify_fail("Climb over what?\n");

    write("You easily climb over the low stone wall.\n");
    say(QCTNAME(tp) + " climbs over the low stone wall.\n");
    tp->move_living("M", GARDENER_ROOM, 1);
    say(QCTNAME(tp) + " arrives, climbing over the low stone wall to " +
        "the south.\n");

    return 1;
}

public void
init()
{
    ::init();
    add_action(climb_wall, "climb");
}
