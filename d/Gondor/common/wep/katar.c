/* A knife  */

inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon()
{
    set_name("katar");
    set_pname("katars");
    add_pname("knives");
    add_name("knife");
    add_name("katar knife");
    set_short("katar knife"); set_pshort("katar knives");
    set_adj("bejeweled");
    add_adj("stout");
    set_long(break_string("The katar is a gripping knife, so that " +
        "the blade sets across your knuckles, and is gripped like a " +
        "mug handle. The cross grip is ivory, worn smooth with use, " +
        "and the side guards are inlaid with sparkling gems, though " +
        "you suspect they are carved glass rather than real stones. " +
        "The blade itself is stout and wide, made for a punching " +
        "attack as well as a slash. It appears to be tempered steel, " +
        "and has an elegance in its curves and slopes.\n", 75));

    set_default_weapon(14,15,W_KNIFE, W_SLASH | W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14,15)+random(50)-20);
}
