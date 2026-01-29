inherit "std/room";
#include "/d/Roke/common/defs.h"
#include <stdproperties.h>

object mon=0;

void
create_room()
{
	set_short("End of Hallway");
	set_long("You are in a hallway in the slave pens under Tyr, "+
	   "which seem to be more of a prison than anything else. "+
	   "The hallway ends here, with additional cells "+
	   "to the north and south. To the east is a prominent "+
	   "looking cell, that seems to have great importance. "+
	   "There is a ladder leading down into the dark and "+
	   "forbidding fighting pits of Tyr.\n");

	add_item(({ "cell" })"The cell is very dim and is difficult to "+
	   "see inside. From here, it looks much cleaner than the "+
	   "rest of the cells.\n");
	add_item(({ "ladder", "fighting pens", "pens", "down" })"The "+
	   "fighting pens are where the slaves test their mettle to "+
	   "see who is worthy of fighting the gladiators. "+
	   "Some even prove worthy enough to join the legendary "+
	   "guild.\n");

	LIGHT

	add_exit(PEN_DIR+"pen9.c","east","@@block");
	add_exit(PEN_DIR +"pen3.c", "north");
	add_exit(PEN_DIR +"pen12.c", "south");
	add_exit(PEN_DIR +"pen13.c", "down", "@@pits");
	seteuid(getuid());
	reset_room();
}
block()
{
	if(!MAL("magron"))
	  return 0;
	
	say(QCTNAME(TP)+" tries to walk east but is stopped "+
	   "by the goblin.\n");
	write("You try to go east but the goblin won't let you!\n");

	return 1;
}
pits()
{
	say(QCTNAME(TP)+" descends the the ladder into the dark "+
	   "and deadly fighting pits.\n");
	write("You steadily climb down the ladder into the "+
	   "dangerous fighting pits of Tyr.\n");
}

reset_room()
{
	seteuid(getuid(TO));
	if(mon)
	  return;
	tell_room(TO, "A dangerous looking goblin jumps to "+
	   "attention at your approach.\n");
	mon = clone_object(A_NPC_D+"goblinguard");
	mon->move(TO);
}

