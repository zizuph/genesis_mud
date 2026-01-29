/*
 * Milan
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../guild.h"

inherit SHIRE_ROOM;

// Global Variables
//public object       weapon_rack = 0;
//public object       armour_rack = 0;
public object       misc_rack = 0;


void
create_room()
{
  set_short("Store room");
  set_long("This is the store room of Angmar's Army.\n");

  add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

  add_exit(AA_DIR+"rooms/priv", "west");

  reset_room();
}
 
void
reset_room()
{
    if(!objectp(misc_rack))
    {
		misc_rack = clone_object("/d/Shire/guild/AA/obj/rack_current");

		misc_rack->set_name("rack");
		misc_rack->set_adj("complex");
		misc_rack->add_adj("equipment");
		misc_rack->set_short("complex equipment rack");
		misc_rack->set_pname("complex equipment racks");
		misc_rack->set_long("Covering the entire wall is a complex set of "
			+ "storage possibilities for any weapon or armour. Constructed "
			+ "of metal and wood, this rack is part bin and part closet. Many "
			+ "methods to hang or stack or carefully store any type of item "
			+ "exist. Big enough to supply a small army. Officers can "
			+ "'read/tail/ log' to see who has stored or received items "
			+ "from the rack.\n");


		misc_rack->move(this_object(), 1);

		misc_rack->unset_no_show_composite();
		misc_rack->remove_prop(CONT_I_ATTACH);


       
    }


    /*if(!objectp(armour_rack))
    {
        armour_rack = clone_object(AA_DIR + "obj/armour_rack");
        armour_rack->move(TO);
    }
    if(!objectp(weapon_rack))
    {
        weapon_rack = clone_object(AA_DIR + "obj/weapon_rack");
        weapon_rack->move(TO);
    }*/
}
