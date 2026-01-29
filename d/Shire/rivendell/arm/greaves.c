/*
 * Battle greaves for elves
 * by Finwe May 1998
 *
 * 1999/05/06 Last update
 * 2011/07/25 Lavellan - Added MAGIC_AM_MAGIC needed for magic armour.
 */
 
inherit "/std/armour";
inherit "/lib/keep";
 
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>
 
void
create_armour()
{   
    add_name("_imladris_battle_greaves");
    set_name(({"pair of light elven greaves", "light elven greaves", 
        "greaves"}));
    set_pshort("pair of light elven greaves");
    set_adj(({"light","elven"}));
    set_short("pair of light elven greaves");
    set_long("This pair of "+short()+" was made by the elves " +
        "in Middle-earth. They are designed to protect the legs " +
        "of the wearer and are made of tempered steel. The " +
        "exceptional workmanship is so good that the armour " +
        "doesn't show any signs of battle.\n");
 
    set_at(A_LEGS);
    set_ac(35);
    set_am(({0, 0, 0}));
    set_keep(1);
 
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
    add_prop(OBJ_S_WIZINFO,
        "This armour is the common armor worn by the elves in " +
        "Imladris. No specials associated other than improved " +
        "protection.\n");
 
    add_prop(MAGIC_AM_MAGIC, ({35, "enchantment"}) );
 
    add_prop(MAGIC_AM_ID_INFO,
        ({"This "+short()+" was forged by the ancient elves of " +
        "Middle-earth. A strong sense of power seems to " +
        "radiate from it.", 20}));
 
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(5, A_LEGS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35) + 75 + random(125));
}
