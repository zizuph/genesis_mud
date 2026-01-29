/**
* Store room for the shoe merchant.
* Designed by Anahita.
* Louie  2005
*/

#pragma strict_types
 
#include "/d/Krynn/common/defs.h"
#define SHOES_PATH ("/d/Krynn/solace/new_village/shoe/shoes/")

inherit R_FILE
inherit "/lib/store_support";

/** prototypes **/
void set_shoe_stock();

public void
reset_krynn_room()
{
    /*
    object ob;

    if (!present("hat"))
    {
        ob = clone_object(SHOE1);
        ob->move(TO);
        enter_env(ob, TP);
    }

    if (!present("boots"))
    {
        ob = clone_object(SHOE2);
        ob->move(TO);
        enter_env(ob, TP);
    }
    */

    reset_store();
    
}

public void
create_krynn_room()
{
    set_short("storeroom");
    set_long("This is the shoe store room.\n");
    set_shoe_stock();
    
    reset_krynn_room();
}

//Set the default stock
void
set_shoe_stock()
{
    string *files, file;
    mixed stock_list = ({});
    int i, k;

    files = get_dir(SHOES_PATH + "*.c");

    k = sizeof(files);

    while (k--)
    {
        file = SHOES_PATH + files[k];
        
        //Stock is stored as ({ "item", number, "item2", number2, })
        stock_list += ({ file, 1 });
    }

    set_default_stock(stock_list);
}

/* To make the store work you have to include the following function in your
 * store-room code:
 */
public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}
