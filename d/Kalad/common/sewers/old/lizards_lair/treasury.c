/*     Created by:     Sir Toby, 97-08-14
 *     Purpose:        The treasury of the lizardking.
 *     Location:       /d/Kalad/common/sewers/lizards_lair/treasury.c
 *     Modified:       
 */


#pragma strict_types

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"

void
create_room()
{
::create_room();

    set_short("The treasury");
    set_long("This is the treasury of the lizardking. It is a " +
	     "rather small room carved out of the rock. It is " +
	     "dusty here. " + "@@dwarf_check");

    add_item("ceiling","The ceiling is roughly cut out of the " +
		       "rock.\n");
    add_item("floor","The floor is roughly cut out of the rock.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,-1);

    MONEY_MAKE_GC(random(100)+400)->move(TO);
    MONEY_MAKE_SC(random(200)+600)->move(TO);
    MONEY_MAKE_CC(random(200)+1500)->move(TO);

    clone_object("/d/Kalad/common/sewers/obj/treasure_chest.c")->move(TO);
    clone_object("/d/Kalad/common/sewers/doors/treasury_door.c")->move(TO);

return;
}

string
dwarf_check()
{

    if(TP->query_race() == "dwarf")
        return"You sence that the ground " +
              "is totally flat and that you are deep under " +
              "the surface of Kabal.\n"; 

       return"\n";

}