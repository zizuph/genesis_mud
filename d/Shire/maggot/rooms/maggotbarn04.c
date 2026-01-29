
/* 
	*A stall in Maggot's barn
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit BASE_BARN;
inherit "/d/Shire/std/room";

void make_npcs();

object pig1;
object pig2;

void create_shire_room()
{
	set_short("An animal stall inside a sturdy barn");
	
	set_long(short() + ". The floor is covered with fresh " +
	"hay, food and bedding for the animals in this particular " +
	"stall. A trough is built into the wall here.\n");
	
	add_item(({"trough"}), "Currently the trough is empty, " +
	"but it looks like it could be filled with food or water.\n");
	add_item(({"floor"}), "The floor is covered by fresh hay.\n");
	add_item(({"hay", "fresh hay"}), "The hay looks like it " +
	"was recently tossed in here.\n");
	
	set_add_rtells_barn();
	set_add_barn();
	
	add_exit(ROOM_DIR + "maggotbarn03", "east");

	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

void make_npcs()
{
    setuid();
    seteuid(getuid());
 
   if(!pig1)
	{
		pig1 = clone_object(NPC_DIR + "pig_fat");
		pig1->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(pig1->query_nonmet_name()))+ " waddles into the stall.\n");
	}
	
	if(!pig2)
	{
		pig2 = clone_object(NPC_DIR + "pig_porky");
		pig2->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(pig2->query_nonmet_name()))+ " waddles into the stall.\n");
	}
}
