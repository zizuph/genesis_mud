/* created by Aridor 12/20/93 */

#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>
#define ASHORE 20

inherit OUTSIDE_BASE;


create_splains_room()
{
    set_short("In the river");
    set_long("You are paddling in the river.\n");
    
    add_item(({"river","water"}),
	     "It's not a very wide river, and the waterlevel is much lower " +
	     "than the plains. Therefore you cannot see up to the plains.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    set_num_npc(0);
}


init()
{
    ::init();
    if (TP->query_stat(SS_DEX) > random(ASHORE))
      set_alarm(3.0,0.0,"climb_ashore",TP);
    else
      set_alarm(8.0,0.0,"carry_away",TP);
}


carry_away(object who)
{
    write("You get carried further down the river.\n");
    who->move_living("floating in the river.",ROOM + "in_water6",1,0);
}


climb_ashore(object who)
{
    write("You are able to grasp secure ground and manage to climb ashore.\n");
    who->move_living("soaking wet from out of the river.",ROOM + "river7",1,0);
}
