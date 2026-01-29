/* 
**A Stout Dwarven Beer
** Created By Leia
** February 20, 2005
*/

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(5);
    set_name("beer");
    set_adj("stout");
    add_adj("dwarven");
    set_short("stout dwarven beer");
    set_pshort("stout dwarven beers");
    set_long("This is a stout dwarven beer with a thick head. The beer is thick and dark, and smells greatly of barley and hopps. It promises to quench the thirst of an ailing dwarf, at least for a little bit.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
