inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void add_stuff();

void
create_er_room()
{
add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
    area = "outside of";
    areaname = "Michel Delving";
    land = "Shire";
    areatype = 2;
    areadesc = "meadow";
    grass = "green";

    extraline = "You stand in a pleasant, grassy meadow a bit "+
    "north of the Great Eastroad. The wilderness encroaches on the "+
    "dirt trail you have chosen, wildflowers blooming all "+
    "around, a few bushes and small trees as well. "+
    "To the northeast, you think you can make out a farmhouse, and "+
    "fence posts dot the horizon in all directions.";

    add_item(({"fence","posts","farm","farmhouse","house","horizon"}),
      "The farm on the horizon looks still in use, if a bit run-down, "+
      "and the same goes for the fenceposts- you can hardly "+
      "see any wire between them!\n");

    add_item(({"bush","bushes","tree","trees","wildflower","wildflowers"}),
      "The wild flora around you is very aromatic, and you "+
      "wonder why anyone would live in a smelly city when "+
      "they could have the peace and quiet of the country.\n");


    add_exit(MICH_DIR + "farmrd1","southwest",0,1);
    add_exit(MICH_DIR + "farmrd3","east",0,1);

    add_stuff();
}

void
reset_shire_room()
{
    add_stuff();
}


void
add_stuff()
{
    object bug;
    if (!present("gnat",TO))
    {
	FIXEUID;
	bug = clone_object(MICH_DIR + "npc/gnat");
	bug->move(TO);
	bug = clone_object(MICH_DIR + "npc/gnat");
	bug->move(TO);
    }
}
