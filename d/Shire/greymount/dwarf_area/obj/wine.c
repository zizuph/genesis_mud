/* 
**A Dark Dwarven Wine
** Created By Leia
** February 20, 2005
*/

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(15);
    set_name("wine");
    set_adj("dark");
    add_adj("dwarven");
    set_short("dark dwarven wine");
    set_pshort("dark dwarven wines");
    set_long("This is a dark dwarven wine. The wine is of the deepest red color and has a sweet smell to it. Made from the finest grapes, it is a favorite of many dwarves and has been brought to this settlement for that very reason.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}