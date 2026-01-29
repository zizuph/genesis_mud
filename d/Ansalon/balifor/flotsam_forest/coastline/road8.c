#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("On a cliffside road");
    set_long("@@long_descr");

    add_item(({"forboding forest","forest"}),
      "A forboding forest swallows up the road to the " +
      "southeast.\n");
    add_item(({"grassy top of the bluff","grassy top",
	"bluff","bluffs","cliffs","grassy topped cliffs"}),
      "To your northwest and east grassy topped cliffs drop " +
      "100 metres to the sea. You could probably make your " +
      "way east off the road if you had the inclination to.\n");
    add_item(({"trail","small trail"}),
      "A small trail heads southwest along the edge of the " +
      "forest.\n");
    add_item(({"road","eroding dirt road","dirt road"}),
      "You stand upon a wide dirt road that is slowly " +
      "eroding away due to lack of maintenance.\n");


    add_exit(CROOM + "road7","northwest",0);
    add_exit(CROOM + "road9","southeast",0);
    add_exit(CROOM + "road10","southwest",0);
    add_invis_exit(CROOM + "road14","east",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"cliffs","grass","bluffs","coastline",
        "road","coast"}), 2);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand upon an eroding dirt road that follows " +
    "the grassy top of the bluffs to the northwest, while " +
    "it enters a forboding forest to the southeast. A " +
    "small trail heads southwest along the edge of the " +
    "forest, while to the east the bluff continues.\n";
}
