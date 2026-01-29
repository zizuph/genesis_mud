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
    set_adj(({"thigh-high","phoenix"}));
    add_adj(({"ash-grey","leather"}));
    add_name(({"pair of boots","pair of phoenix boots"}));
    add_pname(({"pairs of boots","pairs of phoenix boots"}));
    set_short("pair of thigh-high phoenix boots");
    set_pshort("pairs of thigh-high phoenix boots");
    set_ac(30);
    set_at(A_FEET);
    set_long("The ash-grey leather of these "+
        "boots has been stitched with carefully dyed sinew and silken "+
        "thread to create the form of a great crimson and gold "+
        "phoenix wrapped around each boot.  The clever design gives "+
        "the illusion of a single creature if viewed from the front "+
        "or back of the wearer.  "+
        "\n");

    add_item(({"stich","stiches","sinew","sinews","thread","silken thread",
        "phoenix","crimson phoenix","gold phoenix","design"}),
        "The pheonix design is so well crafted from the dyed sinew and "+
        "thread that it gives the illusion of a single creature when "+
        "viewed from the front or back of the wearer.\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_HEAD));
    //expensive!
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) * 2);
}
