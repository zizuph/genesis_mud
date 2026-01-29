/*
 * Glorfindel's bracers 
 * by Finwe May 1998
 */
 
inherit "/std/armour";
inherit "/lib/keep";
 
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>
 
#define AC  45 
void
create_armour()
{   
    add_name("_glorfindels_bracers");
    set_name(({"pair of mithril bracers", "mithril bracers", 
        "bracers"}));
    set_pshort("pairs of light elven bracers");
    set_adj(({"elven", "mithril"}));
    set_short("pair of mithril bracers");
    set_long("This pair of "+short()+" was made by the elves " +
        "in ages long past for a high elven lord. The bracers " +
        "are made of mithril and protect the arms " +
        "of the wearer. The " +short()+" are crafted so well " +
        "that the armour doesn't show any signs of battle.\n");
 
    set_at(A_ARMS);
    set_ac(AC);
    set_am(({0, 0, 0}));
    set_keep(1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
    add_prop(OBJ_S_WIZINFO,"This armour is worn by Glorfindel " +
        "from Imladris in battle. No special features are " +
        "implemented into them.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This armour is made by the elves of " +
          "Middle-earth. A strong sense of power seems to " +
          "radiate from them.", 10}));
    add_prop(MAGIC_AM_MAGIC,({80, "enchantment"}));
    
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_ARMS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, 1200 + random(500));
}
