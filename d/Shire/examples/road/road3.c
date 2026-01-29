#include "../local.h"

inherit ROAD_BASE;

object orc;

void
create_road_room()
{
    set_short("A winding road in the Shire");

    add_exit(EXAMPLE_ROAD + "road4","south",0,2);
    add_exit(EXAMPLE_ROAD + "road2","northwest",0,2);
    add_exit(EXAMPLE_FOREST + "forest1","west",0,2,1); // Non-obvious exit

    reset_shire_room();
}

void
reset_shire_room()
{
    setuid(); seteuid(getuid());
    if (!orc)
    {
	orc = clone_object(EXAMPLE_NPC + "orcmaker_orc");
	orc->move(TO);
    }
}
