inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "ev13","east",0,1
#define EXIT2 EVENDIM_DIR + "ev11","northwest",0,1

void add_stuff();

void
create_er_room()
{
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "smooth floodplain";
    grass = "blue-green";
    extraline = "This expanse of blue-green grass is a bit "+
    "littered with debris, such as might wash up after a "+
    "flood. You notice a track leading northwest and east.";
    add_item(({"expanse","debris","litter"}),
      "The litter is mostly brush and other formerly living "+
      "debris, including not a few bones.\n");
    add_item("track","The track is little more than a "+
      "depression in the grass where feet have passed.\n");
    add_exit(EXIT1);
    add_exit(EXIT2);
    set_noshow_obvious(1);

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
    object orc, orc2, orc3;

    if(!present("orc"))
    {
	orc = clone_object(EVENDIM_DIR + "npc/invading_orc");
	orc->move(TO);
	orc2 = clone_object(EVENDIM_DIR + "npc/invading_orc");
	orc2->move(TO);
	orc3 = clone_object(EVENDIM_DIR + "npc/invading_orc");
	orc3->move(TO);
    }

}
