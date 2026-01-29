inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "orc_camp/track01","southeast",0,1
#define EXIT2 EVENDIM_DIR + "ev7","west",0,1

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
    extraline = "The smooth floodplain of this place is marred "+
    "only by a depression in the blue-green grass leading "+
    "west and southeast from here.";
    add_item(({"floodplain","plain","place"}),
      "The floodplain of the Brandywine River stretches out "+
      "a long way from its banks.\n");
    add_item(({"depression"}),
      "The depression is made by walking feet.\n");
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
    object orc;

    if(!present("orc"))
    {
	orc = clone_object(EVENDIM_DIR + "npc/warning_orc");
	orc->move(TO);
    }

}
