
/* 
	*A room in Maggot's barn
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit BASE_BARN;
inherit "/d/Shire/std/room";

void make_npcs();

static object *hobbits = allocate(4);

void create_shire_room()
{
	set_short("Inside a sturdy barn");
	
	set_long(short() + ". There are bits of hay on " +
	"the ground, as well as dirt that was probably tracked " +
	"in by the farm hands and animals. Tools hang on " +
	"walls and from the rafters. From the smell, the space " +
	"to west appears to be a stall for animals.\n");
	
	set_add_barn_main();	
	set_add_rtells_barn();
	set_add_barn();
	
	add_exit(ROOM_DIR + "maggotbarn03", "north");
	add_exit(ROOM_DIR + "maggotyard11", "south");
	add_exit(ROOM_DIR + "maggotbarn02", "west");

	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

void make_npcs()
{
    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());
 
    /* Loop over all elements in the array. */
    for(int index = 0; index < 4; index++)
    {
        if (!objectp(hobbits[index]))
        {
		hobbits[index] = clone_object(NPC_DIR + "farm_hand");
		hobbits[index]->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(hobbits[index]->query_nonmet_name()))+ " ambles into the general area.\n");
		hobbits[index]->set_restrain_path("/d/Shire/maggot/rooms");
		hobbits[index]->set_random_move(4);
        }
    }

}
