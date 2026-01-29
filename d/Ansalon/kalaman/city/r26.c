#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1, g2;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "militiaman");
	g1->arm_me();
	g1->move(TO);
    }

    if(!objectp(g2))
    {
	g2 = clone_object(KNPC + "militiaman");
	g2->arm_me();
	g2->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Crossroad in the city of Kalaman");

    add_item("crossroad","The crossroad leads northwest towards the western " +
      "gates, northeast to the market place, southeast towards the " +
      "city palace and southwest towards the southern wall.\n");
    add_item(({"gates","western gates","gate"}),
      "To the northwest you can make out two large iron gates that " +
      "lead out of Kalaman.\n");
    add_item(({"palace","spires"}),
      "Looking to the southeast you can make out the spires of the palace of Kalaman.\n");
    add_item(({"market","market place"}),
      "To the northeast you can make out a bustling market place.\n");
    add_item(({"wall","southern wall"}),
      "To the southwest you can make out the grey stones of the southern wall of the city.\n");

    add_item_city();

    add_exit(CITY + "r27","northwest",0);
    add_exit(CITY + "r25","northeast",0);
    add_exit(CITY + "r19","southeast",0);
    add_exit(CITY + "r28","southwest",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand at a crossroad in the city of Kalaman. " +
    tod_descr1() + season_road() + "To the northwest the cobbled street leads " +
    "towards the western gates, while to the southeast the street continues " +
    "towards the palace. To the northeast you can just make out the local " +
    "market place.\n";
}
