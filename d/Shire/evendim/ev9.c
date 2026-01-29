inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

void add_stuff();

void
create_er_room()
{
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "overgrown ancient road";
    grass = "blue-green";
    extraline = "Just outside Annuminas you can barely "+
    "discern the outlines of tall crumbling buildings through "+
    "the fog.  North leads closer to Annuminas, south will "+
    "exact an escape.";
    add_exit(ANNUM_DIR + "am1","north",0,1);
    add_exit(EVENDIM_DIR + "ev8","south","@@enter_shire@@",1);
    set_noshow_obvious(1);
    add_stuff();
}

void
add_stuff()
{
/*
    object animal;
    if(!present("seagull"))
    {
	animal = clone_object(EVENDIM_DIR + "npc/gull");
	animal->move(TO);
    }
*/
}

void
reset_shire_room()
{
    add_stuff();
}


void enter_shire()
{
    write("You cross the North Farthing border and enter the Shire.\n");
}