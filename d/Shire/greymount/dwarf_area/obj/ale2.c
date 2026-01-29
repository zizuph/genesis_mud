/* 
** A Smooth Dwarven Ale
** Created By Leia
** February 20, 2005
*/

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(24);
    set_name("ale");
    set_adj("smooth");
    add_adj("dwarven");
    set_short("smooth dwarven ale");
    set_pshort("smooth dwarven ales");
    set_long("This is a smooth dwarven ale with a foamy head. Dwarven ale is a stronger version of dwarven beer, though it is  far from being one of the dwarve's most powerful drinks. The ale has a rich golden color and smells of barley and hopps.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
