/*     Created by:     Sir Toby, 97-08-14
 *     Purpose:        The treasury of the lizardking.
 *     Location:       /d/Kalad/common/sewers/lizards_lair/before.c
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
    set_long("This is before the treasury of the lizardking. It is a " +
	     "rather small room carved out of the rock. The floor " +
	     "is very dusty. " + "@@dwarf_check");

    add_item("ceiling","The ceiling is roughly cut out of the " +
		       "rock.\n");
    add_item("floor","The floor is roughly cut out of the rock and " +
		     "covered with dust.\n");	

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,-1);

    clone_object("/d/Kalad/common/sewers/doors/treasury_door2.c")->move(TO);
    add_exit(PATH + "ll31.c","east",0,1);
    set_noshow_obvious(1);

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