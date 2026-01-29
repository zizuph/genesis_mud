inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/desert/defs.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"
#include "../tyr.h"

void
reset_room()
{
   bring_room_team(TYR_NPC+"tmpl_mid.c",1,2,TYR_NPC+"hgiant.c",1);
}

void
create_room()
 {
  set_short("Tunnel through the Champion's Gate");
set_long("You are inside the massive tunnel which leads through "
	+"the walls of Tyr and is called the Champion's Gate.  "
	+"The gate is enormous, easily big enough to allow one of"
	+"the enormous mekillots and the wagons it tows through "
	+"with room to spare.  A large stone block is visible in "
	+"an alcove to the north, most likely it is used to block "
	+"the gate in the rare chance that someone attempt to "
	+"attack the city or force their way inside.  Lining the "
	+"ceiling you see a variety of holes, some as large as "
	+"one foot in diameter, some smaller.  They seem to be a "
	+"very strange thing to have here.\n");
add_item("holes","These holes of different sizes are murder-holes.  "
	+"They are used for the defence of the city.  People in "
	+"the chamber above can drop things through these holes "
	+"to wound or kill attackers.  Things like hot coals, "
	+"boiling oil or tar, huge rocks and the like, are typical "
	+"munitions.\n");
add_item("alcove","It looks to be designed to hold the massive "
	+"stone block used for blocking the tunnel during "
	+"attacks.\n");
add_item(({"stone block","block","massive stone block"}),
	"This block is a massive slab of granite that is "
	+"currently occupying an alcove to the north.  In times "
	+"of war, this enormous slab of granite is slid into the "
	+"tunnel to block it from invaders.\n");
add_item("ceiling","The ceiling is high above you, but even from "
	+"here you can see the holes spaced out along it.\n");
add_item("tunnel","Leading through the massive walls that defend "
	+"Tyr from all invaders, this huge tunnel is one of two "
	+"gates that allows travellers and caravans into Tyr.\n");

   add_exit(TYR_SLAVE+ "rd_sw_05","west");
    add_exit(DESERT + "r1","east");
    set_alarm(1.0,0.0,"reset_room");
}

