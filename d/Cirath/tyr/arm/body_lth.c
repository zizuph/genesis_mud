/* body_lth: Slightly better armour then burlap, but what isn't? */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("jerkin");
    set_short("leather jerkin");
    set_long("The low quality leather used to make this piece of armour "+
             "smells so bad that you doubt anything will actually come "+
             "near enough to merit any need for protection.\n");
    set_adj("leather");

    set_ac(15);
    set_am(({ -2, 0, 2}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 3125);
    add_prop(OBJ_I_VOLUME, 1575);
}
