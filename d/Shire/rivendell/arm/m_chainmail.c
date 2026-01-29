/*
 * Chainmail worn by Glorfindel
 * by Finwe May 1998
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
    set_name("chainmail");
    set_adj(({"light","elven"}));
    set_short("light elven chainmail");
    set_long("This "+short()+" is made of mithril rings that " +
        "are interlocked. The chainmail is strong yet " +
        "lightweight and worn only by an elf of high station. " +
        "It appears to have been fashioned by elves of an " +
        "earlier time yet doesn't show any signs of battle.\n");
 
    set_at(A_TORSO);
    set_ac(50);
    set_am(({0, 0, 0}));
    set_keep(1);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
    add_prop(OBJ_S_WIZINFO,
        "This armour is worn by Glorfindel. No specials are " +
        "associated other than improved protection.\n");
 
    add_prop(MAGIC_AM_ID_INFO,
        ({"This "+short()+" was forged by the ancient elves of " +
        "Middle-earth. A strong sense of power seems to " +
        "radiate from it.", 20}));
 
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));

 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(50, A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, 2500 + random(250));
}
