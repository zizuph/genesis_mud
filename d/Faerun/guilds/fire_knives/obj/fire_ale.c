inherit "/std/drink";
#include "/sys/stdproperties.h"

/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("ale");
    set_adj("ruddock's");
    set_short("ruddock's ale");
    set_pshort("ruddock's ales");
    set_long("This is the personal refreshling "
    +"brew made by Richard D. Ruddock of the "
    +"assassin outfit 'Fire Knives'. Mmm...tasty!\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
