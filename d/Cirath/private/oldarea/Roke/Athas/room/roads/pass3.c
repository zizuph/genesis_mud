inherit "/d/Roke/Athas/room/roads/MOUNTAIN_PASS.c";

#include "/d/Roke/defs.h"
object shepherd;

void
create_mountain_pass()	{
call_out("reset_room",1);
	add_exit(ROAD_D+"pass2","west",0,2);
	add_exit(ROAD_D+"ent_pass2","east","@@down",2 );
}

down()	{
	write("You start to walk down from the mountain.\n");
}
reset_room()
{
if(shepherd) return;
shepherd=clone_object("/d/Roke/gresolle/jab/shepherd");
shepherd->move(this_object());
}

