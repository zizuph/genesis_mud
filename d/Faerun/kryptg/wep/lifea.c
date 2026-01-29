/*
 * dark mithral battleaxe
 * Wielded by the vampires of Kryptgarden
 * This sword transfers the damage done to the enemy to the wielder
 *
 * It is the axe version of the lifestealer sword wielded by the 
 * vampire npcs in Faerun and originally coded by Finwe, October 2007
 * Axe version switched over by Finwe, September 2017
 *
 * In the Forgotten Realms, mithril is spelled as mithral, so this is 
 * not a typo.
 *
 * Fixed type in fail to wield string. Was 'conrol' should be 'control'
 * Mirandus, Feb, 2018
 */

#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

#define ADJ1            "dark"
#define ADJ2            "mithral"
#define WEAPON_NAME     "battleaxe"
#define WEAPON          "axe"
#define WEP_TYPE        W_AXE
#define DAMAGE          W_SLASH | W_BLUDGEON
#define GEM             "emerald"

#define MIN_SKILL       51
#define MAX_DAM         125

int hit = 50 + random(5),
    pen = 50 + random(5);

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name("lifestealer");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME);
    set_long("This is a " + query_short() + ". The blade was forged of " +
        "mithril by dwarves and etched with intricate runes. The handle " +
        "is made of sablewood, and wrapped in black leather. Beneath the " +
        "blade are six cut " + GEM + "s, each measuring about a knuckle's " +
        "length. Each " + GEM + " sparkles with an inner flame.\n");

    add_item(({"runes"}),
        "They are etched into the blade in intricate designs. The runes " +
        "are ancient and sparkle in the light, infusing the blade with power.\n");
    add_item(({"handle"}),
        "It is long and made of sablewood. The handle is shaped so that " +
        "it can be comfortably wielded by both hands. It is wrapped in " +
        "black leather.\n");
    add_item(({"black leather", "leather"}),
        "The leather is woven around the handle, allowing the user to hold " +
        "the " + query_short() + ".\n");
    add_item(({"sablewood"}),
        "It is a hardwood that has been shaped and wrapped with black " +
        "leather. It is used as the handle of the " + query_short() + ".\n");
    add_item(({"blade"}),
        "The blade has been forged of mithral. It is half-moon shaped and sits " +
        "on top of the handle. Beneath the blade, six " + GEM + "s are " +
        "evenly spaced.\n");
    add_item(({GEM}),
        "Each " + GEM + " is cut in the shape of an oval. They sparkle " +
        "brilliantly, and within each gem a green light swirls about.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE);
    set_dt(DAMAGE);
    set_wf(TO);
    set_hands(W_BOTH);
    set_likely_dull(1);
    set_likely_break(1);

    add_prop(OBJ_I_WEIGHT, 8500);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE,9);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({75,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This weapon was forged ages ago and infused " +
        "with dwarven magics.",1,
    "The runes seem to dance before your eyes, and enhance the power and " +
        "strength of the battleaxe.",10,
    "The magics in the blades steal the life force from its enemies, and " +
        "directs it back to its current master.", 45}));
    add_prop(OBJ_S_WIZINFO, "The " + query_short() + " is wielded by " +
        "vampires in the Kryptgarden. When it attacks an enemy, a portion " +
        "of the damage is given to the wielder as health points.");
}

void init()
{
    ::init();

}


mixed
wield(object wep)
{
    if (TP->query_skill(SS_WEP_AXE) < MIN_SKILL)
    {
        write("A piercing voice echoes through your mind and says: Puny fool! " +
            "You think you can wield me!?! You lack the power to control me!!!\n");
        write("You unwield the " + query_short() + ".\n");
        return 1;        
    }

    write("You wrap both hands around the handle of the " + query_short() + ".\n");
    say(QCTNAME(wielder) + " wields the " + query_short() + ". ");

    write("The " + query_short() + " vibrates with power in your grip.\n");
    say("It vibrates with power in " + HIS_HER(TP) + " grip.\n");
    return 1;
}

mixed
unwield(object obj)
{
    wielder->catch_tell("You unwrap both hands from around the " + 
        query_short() + ".\n");
    wielder->tell_watcher(QCTNAME(wielder) + " unwields the " + 
        query_short() + ".\n");
    return 1;
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string *move_desc, *pmove_desc, *swing_desc, *pswing_desc;
    string hit_msg, dam_msg;
    mixed *hitresult;
    object wielder = query_wielded();
    int x, y, dam_to_hp;

    ::did_hit();

//    move_desc = (({"strike", "leap", "lunge", "spin", "charge", "hit", "pounce"}));
    move_desc = (({"drive", "pound", "rush", "batter", "slam", "hit", "swing"}));
    pmove_desc = (({"drives", "pounds", "rushes", "batters", "slams", "hits", "swings"}));
    swing_desc = (({"swing", "slash with", "stab with", "cut with", "hack with"}));
    pswing_desc = (({"swings", "slashes with", "stabs with", "cuts with", "hacks with" }));

    x = random(sizeof(move_desc));
    y = random(sizeof(swing_desc));

    switch(phurt)
    {
/*        case -1:
            hit_msg = "missing";
            dam_msg = "no";
            break;
        case 0:
            hit_msg = "barely missing";
            dam_msg = "no";
            break;*/

        case -2:
            hit_msg = "are parried";
            dam_msg = "is parried";
            break;
        case -1:
            hit_msg = "miss";
            dam_msg = "misses";
            break;
        case 0:
            hit_msg = "tapping";
            dam_msg = "no";
            break;
        
        case 1..5:
            hit_msg = "scratching";
            dam_msg = "hardly any";
            break;
        case 6..10:
            hit_msg = "nicking";
            dam_msg = "very little";
            break;
        case 11..19:
            hit_msg = "cutting";
            dam_msg = "a little";
            break;
        case 20..29:
            hit_msg = "slicing";
            dam_msg = "some";
            break;
        case 30..39:
            hit_msg = "carving";
            dam_msg = "some";
            break;
        case 40..49:
            hit_msg = "scoring";
//            dam_msg = "alot of";
            dam_msg = "a lot of";
            break;
        case 50..59:
            hit_msg = "hacking";
//            dam_msg = "alot of";
            dam_msg = "a lot of";
            break;
        case 60..69:
            hit_msg = "slashing";
            dam_msg = "a considerable amount of";
            break;
        case 70..79:
            hit_msg = "hewing";
//            dam_msg = "a great of deal";
            dam_msg = "a great deal of";
            break;
        default:
            hit_msg = "sundering";
            dam_msg = "a deadly amount of";
            break;
    }

    if (phurt < 0)  // A miss!
    {
        if (!wielder->query_option(OPT_GAG_MISSES))
            wielder->catch_msg("You " + move_desc[x] + " and " +swing_desc[y] +
                " your " + query_short() + " at " + QTNAME(enemy) +
                "'s " + hdesc + ", but " + hit_msg + ".\n");
        wielder->tell_watcher_miss(QCTNAME(wielder) + " " + pmove_desc[x] +
            " and " + pswing_desc[y] + " " + HIS_HER(wielder) + " " + query_short() +
            " at " + QTNAME(enemy) + "'s " + hdesc + ", but " + dam_msg + 
            ".\n",enemy);
        enemy->catch_msg(QCTNAME(wielder) + " " + pmove_desc[x] + " and " +
            pswing_desc[y] + " " + HIS_HER(wielder) + " " + query_short() +
            " at your " + hdesc + ", but " + dam_msg + ".\n");
    } 
    else
    {
        wielder->catch_msg("You " + move_desc[x] + " and " +swing_desc[y] +
            " your " + query_short() + ", " + hit_msg + " " + QTNAME(enemy) +
            "'s " + hdesc + ", and do " + dam_msg + " damage.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " " + pmove_desc[x] +
            " and " + pswing_desc[y] + " " + HIS_HER(wielder) + " " + query_short() +
            " at " + QTNAME(enemy) + ", " + hit_msg + " " + HIS_HER(wielder) +
            " " + hdesc + ", and doing " + dam_msg + " damage.\n",enemy);
        enemy->catch_msg(QCTNAME(wielder) + " " + pmove_desc[x] + " and " +
            pswing_desc[y] + " " + HIS_HER(wielder) + " " + query_short() +
            " at you, " + hit_msg + " your " + hdesc + ", and does " +
            dam_msg + " damage.\n");
    }

    // transfers hp from the enemy to the wielder
    if(!random(9))
    {
        if(dam)
        {
            if(dam > MAX_DAM)
                dam_to_hp = MAX_DAM;
            else
                dam_to_hp = dam;
            
            wielder->heal_hp(dam_to_hp);
            
            wielder->catch_msg("\nThe " + query_short() + " hums with power " +
                "and the " + GEM + "s flare as new life courses through your body.\n\n");
            wielder->tell_watcher_miss(QCTNAME(wielder) + "'s " + 
                query_short() + " hums with power.\n",enemy);
        }
    }
    return 1;
}
