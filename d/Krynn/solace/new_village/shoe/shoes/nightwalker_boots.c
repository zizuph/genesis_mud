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

    set_adj(({"nightwalker","black"}));
    add_adj(({"stiff","leather"}));
    add_name(({"pair of boots","pair of black boots"}));
    add_pname(({"pairs of boots","pairs of black boots"}));
    set_short("pair of nightwalker boots");
    set_pshort("pairs of nightwalker boots");
    set_ac(25);
    set_at(A_FEET);
    set_long("The stiff black leather of these boots "+
        "is stitched with silver thread, and is broken randomly by glass "+
        "and obsidian beads to catch the light, seeming to twinkle like stars.  "+
        "A disc of mother-of-pearl surrounded by moonstones simulates the "+
        "full moon.  The soft soles of these boots were designed for the "+
        "utmost comfort on late night walks.  "+
        "\n");

    add_item(({"thread","silver thread","stitches","stitching","beads",
        "glass beads","obsidian beads"}),
        "The silver stitching contains several beads of glass and obsidian, "+
        "designed to catch the light.\n");

    add_item(({"mother-of-pearl","disc","moonstones"}),
        "The disc of mother-of-pearl is surrounded by moonstones to create "+
        "the image of a full moon.\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
}
