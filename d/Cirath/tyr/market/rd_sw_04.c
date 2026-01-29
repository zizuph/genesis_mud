#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"


void
reset_room()
{
   bring_room_team(TYR_NPC+"tmpl_mid.c",1,2,TYR_NPC+"hgiant.c",1);
}

void
create_room()
{
   set_short("Entrance to arena");
   set_long("The road forks here.  One turn goes to the northwest "
   	+"into the arena of Tyr, where brave gladiators fight "
   	+"to survive, while the other stretches northeast towards "
   	+"Champion's Gate and the northern parts of Tyr.  The "
   	+"path to the northwest seems to run through a tunnel "
   	+"which is cut through the wall of the arena and will "
   	+"take you to the seating area of the arena so you can "
   	+"watch the fights if you wish.  The crowds around here "
   	+"are as thick as usual, with people pressed against "
   	+"each other struggling to get inside.\n");
   add_item("road","You are walking on it.  It leads to the "
   	+"northwest and northeast.\n");
   add_item("arena","Towering high overhead, the arena is the "
  	+"pinnacle of engineering in Tyr.  Built from massive "
  	+"blocks of stone accented with obsidian, the monolithic "
  	+"arena stretches high into the air.  Only one building "
  	+"in Tyr is taller, and that is Kalak's Ziggurat.\n");
  add_item("tunnel","It runs beneath through the wall of the "
  	+"arena, and leads to the seats inside.\n");
  add_item("wall","The massive stone walls of the arena reach "
  	+"high into the air like a tall bluff.  People can be "
  	+"seen standing on the top of the wall, oblivious of "
  	+"the danger, waiting to see the fights.\n");
  add_item(({"crowd","crowds"}),"They are packed with people "
  	+"of all races, most of whom share the common goal of "
  	+"accessing the arena.\n");
  ADD_ZIG_ITEM
  add_prop(ROOM_I_INSIDE,0);
  add_exit(TYR_MARKET+"rd_sw_03","south");
  add_exit(TYR_SLAVE+"rd_sw_04","northeast");
  add_exit(TYR_STADIUM+"ringside","northwest","@@tunnel_message");
  reset_room();
}


public int
tunnel_message()
{
   TP->catch_msg("The harsh rays of the sun are temporarily "
	+"blocked as you enter the tunnel, but once again "
	+"strike you as you enter the arena.\n");
    return 0;
}


