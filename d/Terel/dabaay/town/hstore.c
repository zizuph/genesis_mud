#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/store_support";
 
#include <stdproperties.h>
 
#define DAB_TOWN DABAAY_DIR + "town/"
#define DOBJ DABAAY_DIR + "obj/"
#define GOBJ "/d/Gondor/common/guild/obj/"
 
object jar1, jar2;
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
 
reset_room()
{
    if (!jar1 || !present(jar1,TO))
    {
     jar1 = clone_object(GOBJ + "herbjar");
     jar1->move(TO);
    }
    if (!jar2 || !present(jar2,TO))
    {
     jar2 = clone_object(GOBJ + "herbjar");
     jar2->move(TO);
    }
}
 
 
create_room() 
{
    set_short("Anriel's House of Herbs, the Store Room");
    set_long("You are in the storage room for Anriel's House of Herbs.\n");
 
    add_exit(DAB_TOWN + "herb_shop", "north");
 
    add_prop(ROOM_I_INSIDE, 1);  
    set_default_stock(({ 
        GOBJ +"herbjar",6 }));
    reset_store();
}

