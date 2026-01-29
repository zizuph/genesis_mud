#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include <language.h>
#include <macros.h>
#include "locals.h"

#define N_PIGS	3

object  cerion,
*pig    = allocate(N_PIGS);

void
create_area_room()
{
    set_areatype(4);
    set_areadesc("nice");
    set_whereis("in");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("This is the western part of a square in the centre "+
      "of "+cityname+", at the southwest corner you see a "+
      "small farm. South of here you see a house with a small "+
      "garden in front of it.");

    add_item("road","The road runs through the square from the north to "+
      "the east.\n");
    add_item("square","The square seems to be surrounded by different "+
      "buildings.\n");
    add_item("buildings","You see a farm in the southwest corner of the "+ 
      "square and another house south of here.\n");
    add_item("garden","You see a garden where grass is growing wild. "+ 
      "It is not a well kept garden.\n");

    add_exit(THORN_DIR + "r2a","north",0);
    add_exit(THORN_DIR + "garden","south",0);
    add_exit(THORN_DIR + "r2d","east",0);
    add_exit(THORN_DIR + "delivery_office","west",0);
    add_exit(THORN_DIR + "small_farm","southwest",0);

    reset_room();
}

void
add_npcs()
{
    int     ip = sizeof(pig);

    if (!objectp(cerion))
    {
	cerion = clone_object(NPC_DIR + "cerion");
	cerion->arm_me();
	cerion->move_living("from the void", TO);
    }
    while (ip--)
    {
	if (!objectp(pig[ip]))
	{
	    pig[ip] = clone_object(NPC_DIR + "pig1");
	    pig[ip]->set_random_move(3);
	    pig[ip]->ANIMAL_1ST_PATH;                  //restrain path!
	    pig[ip]->set_monster_home(THORN_DIR + "r2a");
	    pig[ip]->move_living("from the void", TO);
	}
    }
}   

void
reset_room()
{
    set_alarm(1.0, 0.0, add_npcs);
}
