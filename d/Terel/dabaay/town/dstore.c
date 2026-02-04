#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/store_support";
 
#include <stdproperties.h>
 
#define DAB_TOWN DABAAY_DIR + "town/"
#define DWEP DABAAY_DIR + "weapon/"
#define DARM DABAAY_DIR + "armour/"
 
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
 
 
create_room() 
{
    set_short("Beeman's General Store, the Store Room");
    set_long("You are in the storage room for Beeman's General Store.\n");
 
    add_exit(DAB_TOWN + "dshop", "east");
 
    add_prop(ROOM_I_INSIDE, 1);  
    set_default_stock(({ 
        DWEP +"hoe",2,
        DWEP + "trowel",3,
        DARM + "fry_pan",3,
        DARM + "stew_pot",3 }));
    reset_store();
}

