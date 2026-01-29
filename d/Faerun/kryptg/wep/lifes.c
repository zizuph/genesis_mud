/*
 * dark silver longsword
 * Wielded by the vampire sire of Kryptgarden
 * This sword transfers the damage done to the enemy to the wielder
 * -- Finwe, October 2007
 */

/*
 * Navarre July 30th 2008.
 * Changed if(!random(4)) return 1, to do the special if(!random(4)).
 * It would execute the special when random(4) != 0, which it would most of the times.
 * So it was slightly wrong.
 *
 * Fixed some typos in the descriptions
 * -- Finwe, January 2015
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
#define ADJ2            "silver"
#define WEAPON_NAME     "longsword"
#define WEAPON          "sword"
#define WEP_TYPE        W_SWORD
#define DAMAGE          W_SLASH|W_IMPALE

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
    set_long("This is a " + short() + ". The blade was forged from the finest " +
        "silver. Runes are etched upon it in an intricate design. The grip " +
        "is made from shaped sablewood, and wrapped in black leather. Around " +
        "the hilt are five cut diamonds, each measuring about a knuckle's l" +
        "ength. Each diamond sparkles with an inner flame.\n");

    add_item(({"runes"}),
        "They are etched into the blade in intricate designs. The runes " +
        "are ancient and infuse the blade with power.\n");
    add_item(({"hilt", "handle"}),
        "It is long and made of sablewood. The sablewood is shaped so that " +
        "it can be comfortably wielded by both hands. It is wrapped in " +
        "black leather.\n");
    add_item(({"black leather", "leather"}),
        "The leather is woven around the grip, allowing the user to hold " +
        "the sword.\n");
    add_item(({"sablewood"}),
        "It is a hardwood that has been shaped and wrapped with black " +
        "leather. It is used as the handle of the sword.\n");
    add_item(({"blade"}),
        "The blade has been forged of silver. It is long and double-edged, " +
        "and tapers to a point. A fuller runs down both sides of the blade.\n");
    add_item(({"fuller", "fullers"}),
        "These are grooves which run from the handle and part way up the " +
        "blade. It lightens the blade, and allows the blade to retain its " +
        "strength and durability.\n");
    add_item(({"diamonds"}),
        "Each of the diamonds are cut in the shape of squares. They sparkle " +
        "brilliantly and glow with an inner flame.\n");

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
    add_prop(MAGIC_AM_ID_INFO,({"This sword was forged ages ago and blessed " +
        "with strong magic.",1,
    "The runes seem to dance before your eyes, and enhance the power and " +
        "strength of the blade.",10,
    "The magic in the blade will steal the life force of its enemies. That " +
        "life force is then fed back to its current master..", 45}));
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
    if (TP->query_skill(SS_WEP_SWORD) < MIN_SKILL)
    {
        return "A piercing voice echoes through your mind and says: Fool! " +
            "you lack the knowledge to wield me!\n";
    }

    write("You wrap both hands around the sablewood grip of the "+short()+".\n");
    say(QCTNAME(wielder) + " wields the "+short()+". ");

    write("The " + query_short() + " thrums with power in your grip.\n");
    say("It thrums with power in " + HIS_HER(TP) + " grip.\n");
    return 1;
}

mixed
unwield(object obj)
{
    wielder->catch_tell("You unwrap both hands from around the "+short()+".\n");
    wielder->tell_watcher(QCTNAME(wielder) + " unwields the "+short()+".\n");
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

    move_desc = (({"strike", "leap", "lunge", "spin", "charge", "hit", "pounce"}));
    pmove_desc = (({"strikes", "leaps", "lunges", "spins", "charges", "hits", "pounces"}));
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
                " your " + short() + " at " + QTNAME(enemy) +
                "'s " + hdesc + ", but " + hit_msg + ".\n");
        wielder->tell_watcher_miss(QCTNAME(wielder) + " " + pmove_desc[x] +
            " and " + pswing_desc[y] + " " + HIS_HER(wielder) + " " + short() +
            " at " + QTNAME(enemy) + "'s " + hdesc + ", but " + dam_msg + 
            ".\n",enemy);
        enemy->catch_msg(QCTNAME(wielder) + " " + pmove_desc[x] + " and " +
            pswing_desc[y] + " " + HIS_HER(wielder) + " " + short() +
            " at your " + hdesc + ", but " + dam_msg + ".\n");
    } 
    else
    {
        wielder->catch_msg("You " + move_desc[x] + " and " +swing_desc[y] +
            " your " + short() + ", " + hit_msg + " " + QTNAME(enemy) +
            "'s " + hdesc + ", and do " + dam_msg + " damage.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " " + pmove_desc[x] +
            " and " + pswing_desc[y] + " " + HIS_HER(wielder) + " " + short() +
            " at " + QTNAME(enemy) + ", " + hit_msg + " " + HIS_HER(wielder) +
            " " + hdesc + ", and doing " + dam_msg + " damage.\n",enemy);
        enemy->catch_msg(QCTNAME(wielder) + " " + pmove_desc[x] + " and " +
            pswing_desc[y] + " " + HIS_HER(wielder) + " " + short() +
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
            
            wielder->catch_msg("The " + query_short() + " thrums with power " +
                "and the diamonds flare as new life courses through your body.\n");
            wielder->tell_watcher_miss(QCTNAME(wielder) + "'s " + 
                query_short() + " thrums with power.\n",enemy);
        }
    }
    return 1;
}
