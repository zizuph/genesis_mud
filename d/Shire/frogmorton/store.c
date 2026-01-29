/*
 * Frogmorton store
 * By Finwe, September 1998
 */    
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
 
inherit SHIRE_ROOM;
inherit "/lib/store_support";

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

 
void
create_shire_room()
{
    set_short("Frogmorton store"); 
    set_long("Frogmorton store.\n"); 
 
    add_prop(ROOM_I_INSIDE, 1);
    set_max_values(70, 5);
/*
    set_default_stock( ({STAND_OBJ + "shoptorch", 3,
        STAND_OBJ + "shoulderbag", 5,
        STAND_OBJ + "oilflask", 10,
        GONDOR_STAND + "oil_lamp", 5,
        FOBJ_DIR + "herb_gloves", 5, 
        STAND_OBJ + "pouch", 5 }));
*/
    reset_store();


    add_exit(FROG_DIR + "shop", "down");
    reset_shire_room();
}


reset_shire_room() 
{
    reset_store();
}
