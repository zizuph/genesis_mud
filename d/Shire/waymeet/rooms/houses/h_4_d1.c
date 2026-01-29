/* 
 * A hidding parchment shop beneath abort
 * hobbit hole.
 * --Raymundo, Jan 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h" 
inherit "/d/Shire/std/room";
inherit WAYM_LIB_DIR + "base_hobbit_hole.c";
inherit "/d/Shire/lib/inn";



#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <money.h>





void reset_shire_room();



void
create_hobbit_room()
{
	set_short("The Scribe's Qarters");
	
	set_long(".I'll describe all this later.\n");
	
		
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 


	add_exit(WAYM_HOUSE_DIR + "h_4_3", "up"); //study



}

void
reset_shire_room()
{
	
}

void
init()
{
	::init();
    init_shire_inn();
	//add_action("dont_order", "order");

}

int
do_order(string str) 
{
	/*
    if (!barliman || !present(barliman))
    {
        notify_fail("There is no-one here to buy anything from.\n"+
          "The innkeeper has been killed!\n");
        return 0;
    }
	*/
    return ::do_order(str);
}


mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    switch (item_name)
    {
    case "scroll":
	case "parchment":
	case "vellum":
	case "paper":
	case "rag paper":
        order = clone_object(WAYM_OBJ_DIR + "scroll_2");
        price = 1;
        break;

    }
    return (({order}) + ({price}));
}

int
dont_order()
{
	write("The scribe says: This isn't an inn, just buy it instead.\n");
	return 1;
}