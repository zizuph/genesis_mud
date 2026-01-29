/*
*  A Spring Water
*  Created By Leia
*  June 05, 2005
*/

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    /* Name _water_for_cleansing is a part of the fountain quest. Please do not remove. */
    set_name("_water_for_cleansing");
    add_name("water");
    set_adj("spring");
    set_short("spring water");
    set_pshort("spring waters");
    set_long("This is a small bottle of spring water. The water is cool and clear, and looks delicious.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
