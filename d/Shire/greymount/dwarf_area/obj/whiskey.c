/* 
**A Powerful Dwarven Whiskey
** Created By Leia
** February 20, 2005
*/

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(60);
    set_name("whiskey");
    set_adj("powerful");
    add_adj("dwarven");
    set_short("powerful dwarven whiskey");
    set_pshort("powerful dwarven whiskies");
    set_long("This is a powerful dwarven whiskey. The whiskey has beautiful chestnut color, and you detect aromas of chocolate fudge and coffee. An interesting drink indeed, it promises to pack a powerful kick.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}