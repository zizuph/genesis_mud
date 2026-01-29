#include "../local.h"
#include ORC_FILE

inherit FOREST_BASE;

object leader, orc1, orc2;

void
create_forest_room()
{
    set_short("Deep within a gloomy forest");
    set_long("Room long version.\n");


    add_exit(EXAMPLE_FOREST + "forest3","west",0,3);
    add_exit(EXAMPLE_FOREST + "forest1","southeast",0,4);

    reset_shire_room();  
    // The orcs here basically have trampled on all the herbs.
    set_no_herbs();
}

void
reset_shire_room()
{
    if (!leader)
    {
	leader = clone_object(ORCMAKER);
	leader->set_power(200);
	leader->set_type(WARRIOR);
	leader->move(TO);
    }
    if (!orc1)
    {  
	orc1 = clone_object(ORCMAKER);
	orc1->set_power(100);
	orc1->set_type(SLAVE);
	orc1->move(TO);
    }
    if (!orc2)
    {
	orc2 = clone_object(ORCMAKER);
	orc2->set_power(120);
	orc2->set_type(SCOUT);
	orc2->move(TO);
    }
    if (present(leader,TO))
    {
	leader->team_join(orc1);
	leader->team_join(orc2);
    }
}

