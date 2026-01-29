/* /d/Gondor/guilds/defenders/rooms/racks.c
 *
 * Defenders, guildhall.
 *
 * Nerull, 2016
 *
 */

#include <stdproperties.h>
#include "defs.h";
#include "../guild.h";

inherit DEF_STD_ROOM;


/*
 * Function name: create_def_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_def_room()
{
	object rack1 = clone_object(DEF_GUILDDIR + "obj/guild_rack");

	rack1->set_name("rack");
	rack1->set_adj("complex");
	rack1->add_adj("equipment");
	rack1->set_short("complex equipment rack");
	rack1->set_pname("complex equipment racks");
	rack1->set_long("Covering the entire wall is a complex set of "
		+ "storage possibilities for any weapon or armour. Constructed "
		+ "of metal and wood, this rack is part bin and part closet. Many "
		+ "methods to hang or stack or carefully store any type of item "
		+ "exist. Big enough to supply a small army.\n");

	rack1->set_allow_misc(1);
	rack1->set_allow_armour(1);
	rack1->set_allow_weapon(1);
	rack1->set_allow_glowing(1);
	rack1->set_allow_nonglowing(1);
	rack1->move(this_object(), 1);
	rack1->unset_no_show_composite();
	rack1->remove_prop(CONT_I_ATTACH);

	set_short("Some room");
	set_long("This is a room.\n");

	add_exit(DEF_GUILDDIR + "rooms/start", "west");
	add_exit(DEF_GUILDDIR + "rooms/h2_3", "north");
    add_exit(DEF_GUILDDIR + "rooms/closet",  "south");
	
	add_item(({"stuff", "more stuff"}), "stuff.\n");

    reset_room();
}


void
reset_room()
{
   
}

