#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
   bring_room_team(TYR_NPC+"hgiant.c",1,2);
}

void
create_room()
{
    ::create_room();
    set_short("Entrance to the Crystal Spider's");
    set_long("You step off of the street and into the entryway of "
	+"the Crystal Spider.  Instantly you feel cooler, but as "
	+"you walk further inside, it gets hot again as you notice "
	+"the massive crowd of people all huddling around tables "
	+"trying to get their bets in.  The game they are playing "
	+"is called Brawling Braxat and it resembles a game played "
	+"around the realms called Blackjack.  There are half-giant "
	+"guards here in the entrance keeping an eye on the players "
	+"and those seeking admittance.  Going south will bring you "
	+"to the actual gambling tables while heading northeast will "
	+"put you back out in the merciless Athasian sun.\n");

   ADD_SUN_ITEM;
   INSIDE;

   add_exit(TYR_CASINO+"casino3.c","south",0,1,0);
   add_exit(TYR_CASINO+"casino1.c","northeast");
}
