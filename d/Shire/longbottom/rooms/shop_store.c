/*
 *   The storage room of the Longbottom shop
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "../defs.h"
#include "/d/Shire/sys/defs.h"
#include </sys/stdproperties.h>


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_room() {
    set_short("longbottom storage room");
    set_long("You have entered the dusty storage room of the Tools and Supplies "
	+ "shop. This is where the shopkeeper keeps all his items that "
	+ "are for sale in the store. "
	+ "You better leave the stuff here alone, or else the shopkeeper "
	+ "will be upset with you.\n");

    set_max_values(70, 7);
    reset_store();
    room_add_object("/d/Shire/common/weapon/orc_scimitar");
//    room_add_object(STAND_WEAPON + "shopsword");
    room_add_object("/d/Shire/common/bree/arm/ltunic");
    room_add_object("/d/Shire/moria/arm/metal_guards");


    add_exit(LB_RM_DIR + "shop","south");

//    add_prop(ROOM_I_NO_CLEANUP, 1); // We don't want this room to be unloaded
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    reset_room();
}

reset_room() 
{


/*  Commented out until Moria shaft is fixed  */
/*
    if (!present("rope"))
   clone_object("/d/Shire/moria/obj/rope")->move(this_object());
*/
    reset_store();


}
