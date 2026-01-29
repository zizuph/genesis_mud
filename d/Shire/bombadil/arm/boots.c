    /*
 * Tom Bombadill's Boots
 * By Finwe, January 2002
 */

inherit "/std/armour";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/wa_types.h"

void
create_armour()
{
    set_name("boots");
    add_name("pair of boots");
    set_short("pair of bright yellow boots");
    add_adj(({"yellow","bright","bright yellow"}));
    set_long("This pair of bright yellow boots has an elvish "+
        "quality to it that makes you feel like singing a happy "+
        "merry song.\n");
    set_default_armour(
        20,
        A_FEET,
        0,
        0);
      add_prop(OBJ_I_WEIGHT, 300);
      add_prop(OBJ_I_VOLUME, 400);
      add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+ random(100));
}

