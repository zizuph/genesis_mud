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
   set_short("End of the road");
   set_long("@@long_descr");
   
   add_item(({"end of the road","road","eroding dirt road",
            "dirt road"}),
      "You stand upon the end of an eroding dirt road in " +
      "the middle of a forest. It seems work stopped on it an " +
      "age ago, and that the forest is slowly taking back " +
      "that which had invaded its depths.\n");
   
   add_item(({"ancient evergreen forest","evergreen forest",
            "forest","canopy","deep shadows","shadows"}),
      "Surrounding you is an ancient evergreen forest. Looming " +
      "over you, its canopy blocks your view of the sky and " +
      "casts deep shadows around you. You get the impression " +
      "you are not wanted within its depths.\n");
   
   add_exit(CROOM + "road8","northwest",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"cliffs","grass","bluffs","coastline",
        "road","coast"}), 2);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand at the end of the eroding dirt road " +
   "within an ancient evergreen forest. Work on the road " +
   "seems to have been stopped an age ago, and no attempts " +
   "to continue it seem to have occurred since.\n";
}
