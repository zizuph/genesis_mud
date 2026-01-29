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

    set_adj(({"painted","short"}));
    add_name(({"pair of boots","pair of painted boots"}));
    add_pname(({"pairs of boots","pairs of painted boots"}));
    set_short("pair of painted boots");
    set_pshort("pairs of painted boots");
    set_ac(25);
    set_at(A_FEET);
    set_long("These short boots are painted with complex "+
        "scenes of mythology and a long-forgotten royal court.  A soldier "+
        "offers a damsel a flower, a knight battles a dragon.  "+
        "Griffons, centaurs, "+
        "fanciful birds and even a unicorn appear in a forest, and in "+
        "another scene a puppy peeks out from under a banquet table, hoping "+
        "for a scrap from a rich harvest feast.  "+
        "\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
}
