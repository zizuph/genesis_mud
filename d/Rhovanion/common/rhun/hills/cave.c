
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"
#include <stdproperties.h>

reset_room()
{
    reset_euid();
    if(!present("_rhun_hills_cave_troll"))
	clone_object(RHUN+"npc/hills_troll")->move(TO);
}

create_room()
{
    set_short("Cave");
    set_long("You have stepped into a darkened cave.  Outside, "+
	"the thunder rolls as a storm approaches.  This cave is "+
	"apparently the lair of some beast.  It is not very large.  "+
	"A few bones and other remains are scattered around here.  "+
	"Most noticeable of all is the stench which hangs heavily "+
	"in the air.  The only exit is back to the northeast.\n");
	
    AE(RHUN+"hills/p2", "northeast");
    
    IN;
    add_prop(ROOM_I_LIGHT,0);
    
    reset_room();
}
