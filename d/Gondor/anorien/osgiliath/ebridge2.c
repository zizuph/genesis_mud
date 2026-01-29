#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void add_stuff();

static object  Troop;

public void
create_area_room()
{
    set_areadesc("bridge over the Anduin river");
    set_area("eastern");
    set_areaname("the ruins of Osgiliath");
    set_land("Gondor");
    set_grass("no");
    set_extraline("The stone bridge is newly repaired, to ease the transport "+
	"of Gondorian troops and Rangers into Ithilien, and enemy-occupied "+
	"territory. Further west is the islet of central Osgiliath, "+
	"where some tall towers and great buildings are still left, not all "+
	"torn down by the wars. But most of the halls and houses have been "+
	"ruined, and the sad remains are no longer populated. East is "+
	"the eastern bank of the Anduin, and the green lands of Ithilien.");
    add_item(({"bridge","ruins"}), BSN(
        "The ancient bridge was smashed during a great battle. " +
	"But this must have been centuries ago. Looking closer, " +
	"the current bridge must be quite recently reconstructed, as the "+
	"stones of the foundations seem to be fresh from the quarry."));
    add_item("towers",BSN("Only a couple of towers are still standing among the "+
	"ruins of the islet of Osgiliath. The fact that the towers were "+
	"built by excellent craftsmen in the ancient days of Gondor's "+
	"founding, and in strong stone, seems to have played a part in "+
	"keeping the towers standing through thousands of years."));
    add_item(({"buildings","houses","halls"}),BSN("Osgiliath was built of "+
	"stone - great halls, towers and houses, all in stone. The city was "+
	"built in three separate parts - the central part on the islet in "+
	"the great river Anduin, the rest on each of the riverbanks. Not much "+
	"is left standing now, only some houses and towers, and the bridge "+
	"connecting the three parts of Osgiliath has been recently repaired."));
    add_item("islet",BSN("On the islet in the Anduin are the ruins of "+
	"central Osgiliath, where the King of Gondor once lived in great halls "+
	"and towers of stone, now mostly crumbled to the ground or into the "+
	"river. The islet is reachable from both riverbanks by bridges of stone "+
	"that have been recently rebuilt."));
    add_item("shore",BSN("The east shore of the Anduin river is not far east, "+
	"but the west bank is further away, beyond the islet "+
	"of Central Osgiliath."));
    add_prop(ROOM_M_NO_TELEPORT, check_teleport);
    add_exit(ITH_DIR + "osgiliath/eosgbridge", "east", 0, 1);
    add_exit(OSG_DIR + "ebridge3",             "west", 0, 1);
    add_stuff();
}

public void
add_stuff()
{
    if (!objectp(Troop))
    {
	Troop = clone_object(MINAS_DIR+"npc/gondor_leader");
	Troop->set_monster_home(OSG_DIR+"ebridge2");
	Troop->set_restrain_path(({OSG_DIR+"ebridge2",OSG_DIR+"ebridge1",
	    OSG_DIR+"e1archway",ITH_DIR+"osgiliath/eosgbridge"}));
	Troop->set_patrol_size(2);
	Troop->arm_me();
	Troop->move_living("down", TO);
    }
}

public void
reset_room()
{
    add_stuff();
}

