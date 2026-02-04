#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/store_support";
 
#include <stdproperties.h>
 
#define DAB_TOWN DABAAY_DIR + "town/"
#define DOBJ DABAAY_DIR + "obj/"
 
object alb1, alb2, peng1, peng2;
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
 
reset_room()
{
    if (!alb1 || !present(alb1,TO))
    {
     alb1 = clone_object(DOBJ + "albatross");
     alb1->move(TO);
    }
    if (!alb2 || !present(alb2,TO))
    {
     alb2 = clone_object(DOBJ + "albatross");
     alb2->move(TO);
    }
    if (!peng1 || !present(peng1,TO))
    {
     peng1 = clone_object(DOBJ + "penguin");
     peng1->move(TO);
    }
    if (!peng2 || !present(peng1,TO))
    {
     peng2 = clone_object(DOBJ + "penguin");
     peng2->move(TO);
    }
}
 
 
create_room() 
{
    set_short("Dabaay's Menagerie of Messengers, the Store Room");
    set_long("You are in the storage room for Dabaay's Menagerie of Messengers.\n");
 
    add_exit(DAB_TOWN + "mesg_shop", "north");
 
    add_prop(ROOM_I_INSIDE, 1);  
    set_default_stock(({ 
        DOBJ +"albatross",4,
        DOBJ + "penguin",6 }));
    reset_store();
}

