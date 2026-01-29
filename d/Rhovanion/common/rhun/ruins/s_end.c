
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"


reset_room()
{
    if(!present("_rhosgobel_quest_moss"))
        clone_object(RHUN+"ruins/moss")->move(TO,1);
}

create_room()
{   
    reset_euid();

    set_short("Edge of the ruins");
    set_long("A few scattered stones lay here, remnants of what "+
    "was perhaps once a great building or shrine, which now has "+
    "been laid to rest and is little more than piles of dirt and rubble.  "+
    "You stand on the edge of this area, with the ruins continuing "+
    "around you to the "+
    "north and northeast"+
    ".\n");
    
    AE(RHUN+"ruins/s_side","north");
    AE(RHUN+"ruins/se_side","northeast");
    
    add_item(({"stone", "stones", "ruins", "rubble"}),
	"The stones which stand "+
	"near to here are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");

    reset_room();

}
