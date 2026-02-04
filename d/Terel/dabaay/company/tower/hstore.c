#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/store_support";
 
#include <stdproperties.h>
 

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
    set_short("Company Herb Store Room");
    set_long("Company Herb Store.\n");
 
    add_exit(COMPANY  + "tower/herb_shop", "north");
 
    add_prop(ROOM_I_INSIDE, 1);  
    set_default_stock(({ 
        GOBJ +"herbjar",6 }));
    reset_store();
}

