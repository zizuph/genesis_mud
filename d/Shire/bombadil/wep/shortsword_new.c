/*
 * Shortsword used by Tom Bombadill
 * Based on the longsword used by Elrond in Rivendell
 * By Finwe, January 2002
 *
 * Removed evil-align check. Really, anyone should be able to wield it.
 * Finwe, Jan 2005
 *
 * Updated by Zhar, June 2021
 * Increased stats, reduced weight, cleaned up the code and updated
 * hit descriptions so they make sense even against non-fleshy targets.
 */
inherit "/std/weapon";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <filter_funs.h>
#include <composite.h>
#include <options.h>

#define DEBUG_WHO find_player("finwe")

#undef DEBUG_WHO
#ifdef DEBUG_WHO
#define DEBUG(s)  DEBUG_WHO->catch_msg(s + "\n")
#else
#define DEBUG(s)
#endif

mapping get_hit_descs(object wielder, object enemy, int phurt, string hdesc);

void
create_weapon()
{
    set_name(({"sword", "shortsword","short sword"}));
    set_pname(({"swords", "shortswords", "short swords"}));
    set_adj(({"ancient", "runed"}));
    set_short("ancient runed short sword");
    set_pshort("ancient runed short swords");
    set_long("This ancient runed short sword is marvelously light. " +
        "The extremely sharp blade is made of ancient steel but it seems " +
        "lighter than an ordinary steel short sword. Flowing engravings " +
        "are etched onto the blade.\n");

    add_item(({"engravings", "flowing engravings"}),
        "The flowing engravings  run the length of the blade. " +
        "They are flowing, like waves of an ocean. Within the " +
        "etchings are runes.\n");
    add_item(({"runes", "ancient runes",  "intricate runes"}),
        "The runes are ancient characters used by people in ages " +
        "long past. They are etched in the engravings on the blade.\n");

    set_default_weapon(50, 45, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    set_wf(TO);

    add_prop(OBJ_S_WIZINFO,
        "This sword is used Tom Bombadill. " +
        "It has no magical properties other than the " +
        "increased hit/pen. It is also very light and " +
        "non-dulling.\n");

    add_prop(MAGIC_AM_ID_INFO,
        ({
            "This sword shines with power", 20,
            "A strong power has been imbued into the weapon", 40,
            "This sword was forged by men in ages past. " +
            "It is extremely light and durable considering its power.", 60
        })
    );

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({80, "enchantment"}));
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50, 45)); /* magic sword */
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();
    mapping descs = get_hit_descs(wielder, enemy, phurt, hdesc);

    wielder->catch_msg(descs["wielder"]);
    enemy->catch_msg(descs["enemy"]);
    wielder->say(descs["room"], enemy);

    return 1;
}

mapping
get_hit_descs(object wielder, object enemy, int phurt, string hdesc)
{
    mapping descs = ([]);

    switch(phurt)
    {
        case -1:
        case -2:
            descs["wielder"] = "You lunge at " + QTNAME(enemy) + " with your "
                + short() + " but miss.\n";
            descs["enemy"] = QCTNAME(wielder) + " lunges at you with "
                + HIS_HER(wielder) + " " + short() + " but misses.\n";
            descs["room"] = QCTNAME(wielder) + " lunges at " + QTNAME(enemy)
                + " with " + HIS_HER(wielder) + " " + short() + " but misses.\n";
            break;
        case 0:
            descs["wielder"] = "You lash out quickly at " + QTNAME(enemy)
                + " with your " + short() + " but fail to do any damage.\n";
            descs["enemy"] = QCTNAME(wielder) + " lashes out quickly at you "
                + " with " + HIS_HER(wielder) + " " + short()
                + " but fails to do any damage.\n";
            descs["room"] = QCTNAME(wielder) + " lashes out quickly at "
                + QTNAME(enemy) + " with " + HIS_HER(wielder) + " " + short()
                + " but fails to do any damage.\n";
            break;
        case 1..5:
            descs["wielder"] = "You open a shallow wound in the " + hdesc
                + " of " + QTNAME(enemy) + " with your " + short() + ".\n";
            descs["enemy"] = QCTNAME(wielder) + " opens a shallow wound in your "
                + hdesc + " with " + HIS_HER(wielder) + " " + short() + ".\n";
            descs["room"] = QCTNAME(wielder) + " opens a shallow wound in the "
                + hdesc + " of " + QTNAME(enemy) + " with " + HIS_HER(wielder)
                + " " + short() + ".\n";
            break;
        case 6..10:
            descs["wielder"] = "Your " + short() + " opens a wound in the "
                + hdesc + " of " + QTNAME(enemy) + ".\n";
            descs["enemy"] = QCTNAME(wielder) + "'s " + short()
                + " opens a wound in your " + hdesc + ".\n";
            descs["room"] = QCTNAME(wielder) + "'s " + short()
                + " opens a wound in the " + hdesc + " of "
                + QTNAME(enemy) + ".\n";
            break;
        case 11..20:
            descs["wielder"] = "Your " + short() + " rips into the "
                + hdesc + " of " + QTNAME(enemy) + ", opening a deep wound.\n";
            descs["enemy"] = QCTNAME(wielder) + "'s " + short()
                + " rips into your " + hdesc + ", opening a deep wound.\n";
            descs["room"] = QCTNAME(wielder) + "'s " + short()
                + " rips into the " + hdesc + " of " + QTNAME(enemy)
                + ", opening a deep wound.\n";
            break;
        case 21..40:
            descs["wielder"] = "You hack at " + QTNAME(enemy) + "'s " + hdesc
                + " with your " + short() + ", wounding " + HIM_HER(enemy)
                + " badly.\n";
            descs["enemy"] = QCTNAME(wielder) + " hacks at your " + hdesc
                + " with " + HIS_HER(wielder) + " " + short()
                + ", wounding you badly.\n";
            descs["room"] = QCTNAME(wielder) + " hacks at " + QTNAME(enemy)
                + "'s " + hdesc + " with " + HIS_HER(wielder) + " " + short()
                + ", wounding " + HIM_HER(enemy) + " badly.\n";
            break;
        case 41..60:
            descs["wielder"] = "Your " + short() + " flashes through the air "
                + "and opens a serious wound in " + QTNAME(enemy)
                + " 's " + hdesc + ".\n";
            descs["enemy"] = QCTNAME(wielder) + "'s " + short()
                + " flashes through the air and opens a serious wound in your "
                + hdesc + ".\n";
            descs["room"] = QCTNAME(wielder) + "'s " + short()
                + " flashes through the air and opens a serious wound in "
                + QTNAME(enemy) + "'s " + hdesc + ".\n";
            break;
        case 61..80:
            descs["wielder"] = "With a quick lunge you bury your " + short()
                + " deeply within " + QTNAME(enemy) + "'s " + hdesc
                + ", opening a grievous wound.\n";
            descs["enemy"] = "With a quick lunge " + QTNAME(wielder)
                + " buries " + HIS_HER(wielder) + " " + short()
                + " deeply within your " + hdesc
                + ", opening a grievous wound.\n";
            descs["room"] = "With a quick lunge " + QTNAME(wielder)
                + " buries " + HIS_HER(wielder) + " " + short()
                + " deeply within " + QTNAME(enemy) + "'s "
                + hdesc + ", opening a grievous wound.\n";
            break;
        case 81..90:
            descs["wielder"] = "You plunge your " + short() + " into "
                + QTNAME(enemy) + "'s " + hdesc + " and then quickly "
                + " twist and tear it away, leaving " + HIM_HER(enemy)
                + " mortally wounded.\n";
            descs["enemy"] = QCTNAME(wielder) + " plunges "
                + HIS_HER(wielder) + " " + short() + " into your "
                + hdesc + " and then quickly twists and tears it away"
                + ", leaving you mortally wounded.\n";
            descs["room"] = QCTNAME(wielder) + " plunges "
                + HIS_HER(wielder) + " " + short() + " into "
                + QTNAME(enemy) + "'s " + hdesc
                + " and then quickly twists and tears it away"
                + ", leaving " + HIM_HER(enemy) + " mortally wounded.\n";
            break;
        default:
            descs["wielder"] = "You bring down your " + short()
                + " with a mighty swing, barely missing "
                + QTNAME(enemy) + "'s " + hdesc + ".\n";
            descs["enemy"] = QCTNAME(wielder) + " brings down "
                + HIS_HER(wielder) + " " + short()
                + " with a mighty swing, barely missing "
                + hdesc + ".\n";
            descs["room"] = QCTNAME(wielder) + " brings down "
                + HIS_HER(wielder) + " " + short()
                + " with a mighty swing, barely missing "
                + QTNAME(enemy) + "'s " + hdesc + ".\n";
            break;
    }

    return descs;
}
