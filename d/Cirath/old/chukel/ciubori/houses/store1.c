/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/store1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
inherit "/lib/store_support";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_room()
{
    	set_short("The shop's store room");
    	set_long("This is the store room for the shop.\n");

    	INSIDE;
   
     	add_exit(CIU_HOU + "shop", "down", 0, 1);
    	reset_room();
}

void
reset_room()
{
    	object ob;
    	int i;

    	if (!present("marketherb", TO))
    	{
    		//  seteuid(getuid(TO));
    		//  ob = clone_object(OBJ+ "herb_gizsha");
    		//  ob->add_name("marketherb");
    		//  ob->move(TO);
    	}
   
}

enter_inv(ob, from)
{
    	::enter_inv(ob, from);
    	store_update(ob);
}
