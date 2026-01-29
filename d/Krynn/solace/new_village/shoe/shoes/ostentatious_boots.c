/* 
 * Louie 2005
 * Designed by Anahita
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_armour()
{
    set_name("boots");
    set_pname("boots");
    add_name("armour");
    add_pname("armours");

    set_adj(({"ostentatious","beaded"}));
    add_adj(({"high-heeled","expensive"}));
    add_name(({"pair of boots","pair of ostentatious boots"}));
    add_pname(({"pairs of boots","pairs of ostentatious boots"}));
    set_short("pair of ostentatious beaded boots");
    set_pshort("pairs of ostentatious beaded boots");
    set_ac(20);
    set_at(A_FEET);
    set_long("High-heeled and very expensive, "+
        "these boots are meant for women of discriminating tastes.  Small "+
        "white square-cut pearlescent shells are sewn over the entire "+
        "surface of the boots. They are lined with yeti fur.  "+
        "\n");

    add_item(({"shells","white shells","pearlescent shells",
        "small shells","small white shells",
        "square-cut shells","white square-cut pearlescent shells"}),
        "The small white pearlescent shells are sewn over the entire "+
        "surface of the boots.\n");

    add_item(({"fur","yeti fur"}),
        "Yeti fur lines these extremely fashionable boots.\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_HEAD));
    //expensive!
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20) * 3);
}
