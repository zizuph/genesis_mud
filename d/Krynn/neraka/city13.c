/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include "local.h"
inherit TANTALLON_OUTSIDE;

create_tantallon_room()
{
    object door;

    set_short("Dark corner");
    set_long(BS(
    	"Now you stand at a very dark corner. There are big walls both north " +
    	"and west and the ground is hard and sterile. This is no friendly " +
    	"place, indeed there is evil in the air. There is not a sound to be " +
	"heard anywhere.", SL));

    add_item("wall",
    	"Which wall do you mean? The west wall or the one north.\n");
    add_item("west wall", BS(
    	"This wall efficiently blocks your way west. It runs south as long " +
    	"as you can see.", SL));
    add_item("north wall",
    	"It's a black wall made out of stone. The wall seem to radiate" +
	" evil.\n");
    add_item("ground", BS(
    	"Nothing grows here, and if it would have grown something it would " +
   	"have been dead.", SL));

    add_exit(TDIR + "city14", "east",0);
    add_exit(TDIR + "city18", "south",0);

    DARK;

    door = clone_object(OBJ + "d_city13_a");
    door->move(TO);
    door->set_key(K_CITY13);
}

