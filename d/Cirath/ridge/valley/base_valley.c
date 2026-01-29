 /* A base desert room */

#pragma save_binary
#pragma strict_types

inherit "/d/Cirath/std/room";

#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
	 bring_room_mob("sandling", RIDGE_NPC+"sandling.c", random(2), 1);
}


void
create_valley()
{

}

void
create_room()
{


  set_short("A desolete valley outside of Tyr");
  set_long("A desolete valley outside of Tyr.\n");
  create_valley();

  OUTSIDE
  LIGHT
  ADD_SUN_ITEM

}

