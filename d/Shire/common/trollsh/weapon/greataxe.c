/*
 * Replacement weapon for Grothaur when the corrupted mithril 
 * axe is out in the game.
 *
 * Has no magical properties but increased hit and pen
 * -- Finwe, Octover 2001
 */

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
/*
#include <language.h>
#include <composite.h>
#include <files.h>
#include <time.h>
#include <std.h>
#include <options.h>
#include <adverbs.h>
#include <cmdparse.h>
*/


inherit "/std/weapon";
inherit "/cmd/std/command_driver";
inherit "/lib/keep";

#define WEAPON_HIT 40
#define WEAPON_PEN 39

object wielder;

void
create_weapon()
{
    set_name("axe");
    set_adj("great");
    set_adj("steel");
    set_short("great steel axe");
    set_long("This is a great steel axe. It has two large, steel, " +
        "curved axe heads on either side of the handle. The blades " +
        "are are polished and sharpened to razor sharpness and " +
        "look very dangerous. The handle is made from a long " +
        "shaft of oak and wrapped with leather. The axe is heavy, " +
        "requiring both hands to wield it.");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(TO);
    add_prop(OBJ_M_NO_SELL,"This axe is too valuable to sell.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"The great steel axe was once " +
        "forged by ancient dwarves. It was plundered by the " +
        "trolls years ago and now used by them in their constant " +
        "plunderings. Only the greatest trolls use it.\n",1}));

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));

    seteuid(getuid(TO));
}

mixed
wield(object what)
{
    object *oblist;

    if(TP->query_race() == "goblin")
    {
	     write("You raise the axe above your head, roaring " +
            "defiantly and challenging all your enemies who stand " +
            "before you.\n");
         all(" raises the "+short()+" above "+HIS_HER(TP)+
            " heard, roaring defiantly and challenging all "+
            HIS_HER(TP)+" enemies who stand before "+HIM_HER(TP)+".",oblist);
    }
    else
    {
        write("You raise the axe above your head, preparing to " +
            "battle your enemies. A glint of light sparkles off " +
            "the sharp blades before lowering the dangerous weapon.\n");
        all(" raises the "+short()+" above "+
        HIS_HER(TP)+ " head in preparation for battle. A glint of " +
        "light sparkles off the sharp blade before "+HE_SHE(TP)+
        " lowers the dangerous blade.\n",oblist);
    }
    return 0;
}
