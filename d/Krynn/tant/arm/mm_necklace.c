/* Mad man's necklace by Teth, April 5, 1996 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "../local.h"

public void
create_armour()
{
    set_name("necklace");
    set_ac(1);
    set_at(A_NECK);
    add_adj( ({ "rusty", "ancient" }) );
    set_short("rusty ancient necklace");
    set_pshort("rusty ancient necklaces");
    set_long("This ancient necklace has been rusted with time. It is made "+
             "of many small fine links with a plain coin-shaped pendant. "+
             "This object might now be of little value, it was certainly "+
             "worth more in the past.\n");
    AI(({"pendant","plain pendant","plain coin-shaped pendant",
        "coin-shaped pendant"}),"This pendant is inscribed with these "+
        "faded and disappearing words:\n    To m. s.n,\n    Remy\n    "+
        "O. y..r 6th b..thd.y.\n");
    add_prop(OBJ_I_VOLUME, 127);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(1, A_NECK));
    add_prop(OBJ_I_VALUE, 40 + random(80));
}

