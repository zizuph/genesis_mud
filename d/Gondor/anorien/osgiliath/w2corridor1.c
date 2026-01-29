inherit "/d/Gondor/common/room";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
  set_short("In a blind-ended corridor in the ruins of Central Osgiliath");
  set_long(BSN("You are in a rather dark and damp corridor with stone "+
    "walls. There is a little light coming from the northeast, but "+
    "the corridor is blocked here by a large pile of rocks and stones, "+
    "probably from the collapsed ceiling, making it impossible to "+
    "continue that way. There are "+
    "rusty remains of torch-stands at set intervals along both walls, "+
	       "but no torches left."));
  add_prop(ROOM_M_NO_TELEPORT, check_teleport);
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,0);
  add_item(({"torch-stands","stands","torch-stand","stand"}),BSN("They are "+
    "made of metal rings, now rusty beyond being usable."));
  add_item("walls",BSN("The walls are made of smooth white stone, though "+
    "the passage of hundreds of years since repair has left solid tracks."));
  add_item(({"rocks","stones","pile","heap","collapsed ceiling","ceiling"}),
     BSN("The pile of stones "+
    "is blocking the corridor, probably as the result of a tower "+
    "collapsing over the building. The war did not fare lightly "+
    "with Osgiliath."));
  add_exit(OSG_DIR+"w2stairway","south",0,1);
}

