inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "ev17","east","@@try_east@@"
#define EXIT2 EVENDIM_DIR + "ev12","west",0,1

void add_stuff();

int
try_east()
{
    if(present("orc"))
    {
	write("The orc won't let you past!\n");
	return 1;
    }
    return 0;
}

void
create_er_room()
{
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "smooth floodplain";
    grass = "blue-green";
    extraline = "This smooth floodplain has only one oddity: "+
    "it has a hut erected to the east.  Debris covers the grass "+
    "in most places, and the track in the grass goes east "+
    "and west.";
    add_item(({"hut"}),"The hut is rather ramshackle.\n"+
      "Perhaps you could go east and examine it more closely.\n");
    add_item(({"debris"}),"The debris is mostly tree branches and "+
      "other remains of formerly living creatures, like bones.\n");
    add_item("track","It goes east and west.\n");
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
