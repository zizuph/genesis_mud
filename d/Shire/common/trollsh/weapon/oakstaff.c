/*
 * Enchanted staff used by Half-troll guard
 * Jaypeg, June 1999
 *      Zizuph, 2021-12-25:
 *         Turn into a spell enhancer, power 44.
 */

inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
 
#include <options.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Shire/sys/defs.h"

 
void
create_weapon()
{
    set_name (({"staff", "quarterstaff"}));
    set_pname(({"quarterstaves","weapons","staves"}));
    add_name("_trollsh_oakstaff");
    set_adj(({"thin","smooth","polearm","wooden","wood"}));
    set_short("thin wooden quarterstaff");
    set_pshort("thin wooden quarterstaves");

    set_long("This wooden staff is a goodly length, long enough "+
             "to be called a quarterstaff. Its smooth, lacquered "+
             "surface is flawless along its entire length, and provides "+
             "a reassuring grip when held. Although the staff is fairly "+
             "light in weight and thin in diameter, it seems to hum "+
             "with conviction when hefted.\n");
 
    set_default_weapon(45,42, W_POLEARM, W_BLUDGEON, W_BOTH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,42)); 
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(OBJ_S_WIZINFO,
      "This staff is wielded by the half-troll guardian of the "+
      "trollshaws. It is enchanted to increase hit and pen, and in "+
      "addition to be magically light and unencumbering when wielded.\n");

    add_prop(MAGIC_AM_ID_INFO,
        ({"This staff seems to be magically enhanced. ", 20,
	      "It is much more effective than its extremely light weight " +
          "would suggest. ", 40,
	      "This staff probably was enchanted by the Dunedain mystics " +
          "during their reign of the kingdoms of Rhudaur, for the " +
          "use of travellers who required lightweight and effective " +
          "protection.", 60}));

    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));

 
    add_item("surface", "The smooth, regular surface of the wooden shaft "+
             "seems to be made of some age-old hardwood, flawless in "+
             "grain.\n");

    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(44);
}


string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}
 
void
init_recover(string arg)
{
    init_wep_recover(arg);
 
    init_keep_recover(arg);
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
