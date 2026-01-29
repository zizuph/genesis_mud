inherit "/std/food";
#include <stdproperties.h>

/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    set_name("swordfish steak");
    add_name("steak");
    add_name("steaks");
    set_adj("swordfish");    
    set_long("A thick steak of swordfish grilled over applewood with"
    +" buerre blanc and a hint of celery, mustard and nutmeg.\n");
    set_short("platter of swordfish steak");
    set_pshort("platters of swordfish steak");
    set_amount(320);
}

