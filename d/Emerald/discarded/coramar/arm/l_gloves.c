/*
 * l_gloves.c
 * Pair of soft, leather gloves worn by Thanduin. -REQUIRED- for mistwraith
 * quest completion.
 * - Alaron Feb 1998
 */

#include "../dirheader.h"
#include "../coramar.h"
#include <wa_types.h>
#include <formulas.h>
#include "/d/Emerald/defs.h"

inherit "/std/armour";

void
create_armour()
{
    set_name("gloves");
    add_name("_thanduins_runed_gloves_");
    set_adj("leather");
    add_adj("soft");
    add_adj("pair");
    set_short("pair of soft, leather gloves");

    set_long("This is a very well cared for pair of soft, leather "+
             "gloves. The hide is still smooth and fuzzy, despite the "+
             "harsh, moist environment they have been subjected to. They "+
             "were made for large hands, but seem like they would fit "+
             "just about anyone. On the palm of each glove, a rune has been burned into the hide.\n");

    add_item( ({"rune", "runes","palm"}),
             "The palms of each glove have had a rune burned into them. "+
             "The rune is a small, uncomplicated symbol. There is a "+
             "thick, vertical line, and three wavy lines passing through "+
             "the vertical line. You wonder what the rune could mean.\n");


    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC, ({10, "enchantment"}));

    set_at(A_HANDS);
    set_ac(5);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
}
