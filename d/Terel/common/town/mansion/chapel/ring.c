/* A gold ring. Mortricia 920910 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"
#include <stdproperties.h>



create_terel_armour()
{
    set_name("ring");
    set_short("golden ring");
    set_adj("golden");
    set_long(BS(
        "It's a golden ring.\n"
        ));
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    set_armour_size(ANY_SIZE);

    set_default_armour(1, A_FINGERS, 0, 0);
}
