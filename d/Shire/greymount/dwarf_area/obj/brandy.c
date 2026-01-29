/* 
**A Strong Dwarven Brandy
** Created By Leia
** February 20, 2005
*/

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(30);
    set_name("brandy");
    set_adj("strong");
    add_adj("dwarven");
    set_short("strong dwarven brandy");
    set_pshort("strong dwarven brandy");
    set_long("This is a strong dwarven pomace brandy. The brandy has a deep color to it and has a very pungent scent. A strong drink such as this is said to put hair on any lesser race's chest.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}