/*
 * A herb potion made by Arren
 * The potion is the same that Pippin and Merry drank on 
 * the plains of Rohan. So the idea is stolen from JRRT.
 *
 */

inherit "/std/potion.c";
inherit "/lib/herb_support";

#include <macros.h>
#include <stdproperties.h>
#include <herb.h>
#include "/d/Gondor/defs.h"

public void
create_potion()
{
    set_potion_name("orc-liquor");
    set_short("smelly herb-potion");
    set_unid_long("This is a strange herb liquor.\n");
    set_id_long("A small bottle of orc-liquor. The liquor has a strong "+
    "smell.\n");
    set_id_diff(4);

    add_name(({ "liquor", "herb-potion" }));
    set_adj("smelly");
    add_adj(({ "bottle of", "small bottle of" }));

    set_effect(HERB_HEALING, "fatigue", 80);
    set_id_taste("The potion tastes strong and burns your throat. You also "+
    "feel a bit envigorated.\n");
    set_id_smell("The potion smells bad. You also feel a bit envigorated.\n");
    set_unid_taste("The potion burns your throat.\n");
    set_unid_smell("The potion smells bad.\n");

    add_prop(OBJ_I_WEIGHT, 50); 
    add_prop(OBJ_I_VOLUME, 50);
    set_potion_value(100);
}

/*
 * Function name: dispel_magic
 * Description:   Function called by a dispel spell
 * Argument:      magic - How strong the dispel is
 * Returns:       0 - No dispelling, this potion is not magic
 *                but based on herbs.
 */
int
dispel_magic(int magic)
{
    return 0;
}

void
set_identified()
{
    identified = 1;
    add_name(potion_name);
}
