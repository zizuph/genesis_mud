/*
 * multi enchantment
 *
 * This is the enchantment used for the enchant spell
 * that can be customized
 *
 * Ashlar, 25 Jul 98
 */

#pragma strict_types

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>

#define ENCHANTMENT_OBJ NOBJ + "enchantment"

inherit ENCHANTMENT_OBJ;

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

// Divisor to calculate PEN of air/death attacks. Lower to raise PEN
#define PEN_FACTOR          15
// Divisor to calculate damage to wep/arm from attacks. Lower to increase damage
#define COND_COUNTER_MAX    20
// HP Bonus in percent
#define HP_BONUS_PERCENT    15
// Mana bonus in percent
#define MANA_BONUS_PERCENT  15
// Fatigue drain addition in whole units (1 = 100% more than usual)
#define FATIGUE_BONUS       1

#define ET_WEAPON   1
#define ET_ARMOUR   2
#define ET_OBJECT   4

static int gHitBonus    = 0;    // Here
static int gPenBonus    = 0;    // Here
static int gACBonus     = 0;    // Here
static int gDurBonus    = 0;    // Here
static int gWeightBonus = 0;    // Here

static int gSpeedBonus      = 0;    // Here
static int gFatigueBonus    = 0;    // Shadow
static int *gStatBonus      = ({ 0, 0, 0, 0, 0, 0 });   // Here
static int gHPBonus         = 0;    // Shadow
static int gManaBonus       = 0;    // Shadow

static int gAirDamage       = 0;    // Here
static int gDeathDamage     = 0;    // Here
static int gDoubleDamage    = 0;    // Here
static int gManaAbsorb      = 0;    // Here
static int gHPAbsorb        = 0;    // Here
static int gBreak           = 0;    // Here and shadow

static int gAirReload   = 0;
static int gDeathReload = 0;
static int gBreakReload = 0;

static int gDullCounter = 0;
static int gCorrCounter = 0;

void
set_speed_bonus()
{
    gSpeedBonus += 100;
    gFatigueBonus += 1;
}

void
set_hp_bonus()
{
    gHPBonus += 1;
    gStatBonus[SS_INT] -= 1;
}

void
set_mana_bonus()
{
    gManaBonus += 1;
    gStatBonus[SS_CON] -= 1;
}

void
set_str_bonus()
{
    gStatBonus[SS_STR] += 3;
    gStatBonus[SS_DEX] -= 1;
}

void
set_con_bonus()
{
    gStatBonus[SS_CON] += 3;
    gStatBonus[SS_WIS] -= 1;
}

void
set_int_bonus()
{
    gStatBonus[SS_INT] += 3;
    gStatBonus[SS_DIS] -= 1;
}

void
set_hit_bonus()
{
    gHitBonus += 10;
    gDurBonus -= 1;
}

void
set_pen_bonus()
{
    gPenBonus += 10;
    gDurBonus -= 1;
}

void
set_ac_bonus()
{
    gACBonus += 10;
    gDurBonus -= 1;
}

void
set_dur_bonus()
{
    gDurBonus += 5;
    gWeightBonus -= 1;
}

void
set_weight_bonus()
{
    gWeightBonus += 5;
    gDurBonus -= 1;
}

void
set_air_damage()
{
    gAirDamage += 1;
}

void
set_death_damage()
{
    gDeathDamage += 1;
}

void
set_double_damage()
{
    gAirDamage *= 2;
    gDeathDamage *= 2;
}

void
set_mana_absorb()
{
    gManaAbsorb += 1;
    gDurBonus -= 1;
}

void
set_hp_absorb()
{
    gHPAbsorb += 1;
    gDurBonus -= 1;
}

void
set_break_damage()
{
    gBreak += 1;
    gHitBonus -= 2;
    gPenBonus -= 4;
    gACBonus -= 5;
}

static string wizextra = "";
static mixed *idinfo = ({ });

/* Create the info strings depending on what this enchantment does */
static void
set_up_infos()
{
    wizextra = "Has multiple effects.\n",

    idinfo = ({ "This object has many effects.", 10 });
}

/* These do not require calling of the inherited function */
string wizinfo_extra()
{
    return wizextra;
}

mixed *query_identify_info()
{
    return idinfo;
}

static void
add_player_effects(object pl, object obj)
{
    int i;
    
    if (gSpeedBonus)
    {
        pl->change_prop(LIVE_I_QUICKNESS,
            pl->query_prop(LIVE_I_QUICKNESS) + gSpeedBonus * query_enchantment_strength() / 100);

        pl->query_combat_object()->cb_update_speed();
    }

    for (i = 0; i < SS_NO_EXP_STATS; i++)
    {
        if (gStatBonus[i])
        {
            pl->set_stat_extra(i, pl->query_stat_extra(i) + gStatBonus[i]);
        }
    }

    if (gHPBonus)
    {
        pl->ei_add_hp_bonus(gHPBonus * HP_BONUS_PERCENT);
    }

    if (gManaBonus)
    {
        pl->ei_add_mana_bonus(gManaBonus * MANA_BONUS_PERCENT);
    }

    if (gFatigueBonus)
    {
        pl->ei_add_fatigue_bonus(gFatigueBonus * FATIGUE_BONUS);
    }
        
}

static void
remove_player_effects(object pl, object obj)
{
    int i;
    
    if (gSpeedBonus)
    {
        pl->change_prop(LIVE_I_QUICKNESS,
            pl->query_prop(LIVE_I_QUICKNESS) - gSpeedBonus * query_enchantment_strength() / 100);

        pl->query_combat_object()->cb_update_speed();
    }    

    for (i = 0; i < SS_NO_EXP_STATS; i++)
    {
        if (gStatBonus[i])
        {
            pl->set_stat_extra(i, pl->query_stat_extra(i) - gStatBonus[i]);
        }
    }

    if (gHPBonus)
    {
        pl->ei_add_hp_bonus(-gHPBonus * HP_BONUS_PERCENT);
    }

    if (gManaBonus)
    {
        pl->ei_add_mana_bonus(-gManaBonus * MANA_BONUS_PERCENT);
    }

    if (gFatigueBonus)
    {
        pl->ei_add_fatigue_bonus(-gFatigueBonus * FATIGUE_BONUS);
    }
}

mixed
enchant_object(object obj)
{
    object pl;
    int tmp;

    set_break_damage();
    set_ac_bonus();
    set_hit_bonus();
    set_pen_bonus();
    set_speed_bonus();

    set_up_infos();
    
    switch(gObjectType)
    {
        case ET_WEAPON:
            /* HIT/PEN bonuses */
            if (gHitBonus != 0)
                obj->set_hit(obj->query_hit() + gHitBonus);
            if (gPenBonus != 0)
                obj->set_pen(obj->query_pen() + gPenBonus);
            pl = obj->query_wielded();
            if (pl)
                pl->update_weapon(obj);
            break;
        case ET_ARMOUR:
            /* AC bonuses */
            if (gACBonus != 0)
                obj->set_ac(obj->query_ac() + gACBonus);
            pl = obj->query_worn();
            if (pl)
                pl->update_armour(obj);
            break;
    }

    if (gDurBonus)
    {
        tmp = obj->query_likely_break() - gDurBonus;
        if (tmp < 0)
            tmp = 0;
        if (tmp > 20)
            tmp = 20;
        gDurBonus = obj->query_likely_break() - tmp;

        obj->set_likely_break(tmp);
    }

    if (gWeightBonus)
    {
        tmp = 100 - gWeightBonus * 5;

        obj->change_prop(OBJ_I_WEIGHT,
            (obj->query_prop(OBJ_I_WEIGHT) * tmp) / 100);
    }

    if (objectp(pl))
        add_player_effects(pl, obj);

    return 0;
}

void
remove_enchantment()
{
    object obj = query_enchanted();
    object pl = 0;
    int tmp;

    switch(gObjectType)
    {
        case ET_WEAPON:
            /* HIT/PEN bonuses */
            if (gHitBonus != 0)
                obj->set_hit(obj->query_hit() - gHitBonus);
            if (gPenBonus != 0)
                obj->set_pen(obj->query_pen() - gPenBonus);
            pl = obj->query_wielded();
            if (pl)
                pl->update_weapon(obj);
            break;
        case ET_ARMOUR:
            /* AC bonuses */
            if (gACBonus != 0)
                obj->set_ac(obj->query_ac() - gACBonus);
            pl = obj->query_worn();
            if (pl)
                pl->update_armour(obj);
            break;
    }

    if (gDurBonus)
    {
        obj->set_likely_break(obj->query_likely_break() + gDurBonus);
    }

    if (gWeightBonus)
    {
        tmp = 100 - gWeightBonus * 5;

        obj->change_prop(OBJ_I_WEIGHT,
            (obj->query_prop(OBJ_I_WEIGHT) * 100) / tmp);
    }

    if (pl)
        remove_player_effects(pl, obj);
}

mixed
wear(object what)
{
    mixed s;

    s = ::wear(what);

    if (intp(s) && s >= 0)
    {
        add_player_effects(this_player(), what);
    }

    return s;
}

mixed
remove(object what)
{
    mixed s;

    s = ::remove(what);

    if (intp(s) && s >= 0)
    {
        remove_player_effects(this_player(), what);
    }

    return s;
}

mixed
wield(object what)
{
    mixed s;

    s = ::wield(what);

    if (intp(s) && s >= 0)
    {
        add_player_effects(this_player(), what);
    }

    return s;
}

mixed
unwield(object what)
{
    mixed s;

    s = ::unwield(what);

    if (intp(s) && s >= 0)
    {
        remove_player_effects(this_player(), what);
    }

    return s;
}

void
clear_air_reload()
{
    gAirReload = 0;
}

void
clear_death_reload()
{
    gDeathReload = 0;
}

void
clear_break_reload()
{
    gBreakReload = 0;
}

void
trigger_air_reload()
{
    gAirReload = 1;
    set_alarm(30.0, 0.0, clear_air_reload);
}

void
trigger_death_reload()
{
    gDeathReload = 1;
    set_alarm(45.0, 0.0, clear_death_reload);
}

void
trigger_break_reload()
{
    gBreakReload = 1;
    set_alarm(120.0, 0.0, clear_break_reload);
}

void
add_dull(int dam)
{
    gDullCounter += dam;
    if (gDullCounter > COND_COUNTER_MAX)
    {
        object obj = query_enchanted();
        gDullCounter -= COND_COUNTER_MAX;
        
        if (gObjectType == ET_WEAPON)
            obj->set_dull(obj->query_dull() + 1);
        else if (gObjectType == ET_ARMOUR)
            obj->set_cond(obj->query_cond() + 1);
    }
}

void
add_corr(int dam)
{
    gCorrCounter += dam;
    if (gCorrCounter > COND_COUNTER_MAX)
    {
        object obj = query_enchanted();
        gCorrCounter -= COND_COUNTER_MAX;
        obj->set_corr(obj->query_corr() + 1);
    }
}

void
write_air_hit(object player, object enemy, int phurt, int damage_type,
    string hdesc)
{
    string *h1, *h2;
    object obj = query_enchanted();
    string s = obj->short();
    
    if (damage_type == W_BLUDGEON)
    {
        h1 = ({
            "Lightning shoots out of your " + s + ", as you smash it into " +
            enemy->query_the_name(player) + "'s " + hdesc,

            player->query_The_name(enemy) + " hits your " + hdesc + " with " +
            HIS(player) + " " + s + ", and lightning from the weapon strikes you",

            QCTNAME(player) + " hits " + QTNAME(enemy) + " with " +
            HIS(player) + " " + s + ", and lightning from the weapon strikes " +
            HIM(enemy),
        });
    }
    else if(damage_type == W_SLASH)
    {
        h1 = ({
            "You slash at " + enemy->query_the_name(player) + " with your " +
            s + ", and as the edge cuts " + HIS(enemy) + " " + hdesc +
            ", bolts of lightning crackle into the wound",

            player->query_The_name(enemy) + " slashes your " + hdesc + " with " +
            HIS(player) + " " + s + ", and lightning bolts shoot out from " +
            "the edge",

            QCTNAME(player) + " slashes " + QTNAME(enemy) + " with " +
            HIS(player) + " " + s + ", and lightning bolts shoot out from " +
            "the edge",
        });
    }
    else
    {
        h1 = ({
            "You stab at " + enemy->query_the_name(player) + " with your " +
            s + ", and as you hit " + HIS(enemy) + " " + hdesc +
            ", bolts of lightning crackle into the wound",
            
            player->query_The_name(enemy) + " stabs your " + hdesc + " with " +
            HIS(player) + " " + s + ", and lightning bolts shoot out from " +
            "the tip",

            QCTNAME(player) + " stabs " + QTNAME(enemy) + " with " +
            HIS(player) + " " + s + ", and lightning bolts shoot out from " +
            "the tip",
        });
    }

    if (phurt <= 0)
    {
        h2 = ({
            "crackling harmlessly against " + HIM(enemy),
            "crackling harmlessly against you",
            "crachling harmlessly against " + HIM(enemy),
            });
    }
    else if (phurt < 7)
    {           
        h2 = ({
            "burning " + HIM(enemy) + " slightly",
            "burning you slightly",
            "burning " + HIM(enemy) + " slightly",
            });
    }
    else if(phurt < 15)
    {
        h2 = ({
            "burning " + HIM(enemy),
            "burning you",
            "burning " + HIM(enemy),
            });
    }
    else if(phurt < 27)
    {
        h2 = ({
            "charring " + HIS(enemy) + " flesh",
            "charring your flesh",
            "charring " + HIS(enemy) + " flesh",
            });
    }
    else if(phurt < 45)
    {
        h2 = ({
            "burning " + HIM(enemy) + " with a searing fire",
            "burning you with a searing fire that spreads through " +
            "your body",
            "burning " + HIM(enemy) + " with a searing fire",
            });
    }
    else if(phurt < 99)
    {
        h2 = ({
            "engulfing " + HIS(enemy) + " whole body in a crackling " +
            "blue fire",
            "engulfing your body in a crackling blue fire that " +
            "seems to burn to your very bones",
            "engulfing " + HIS(enemy) + " whole body in a crackling " +
            "blue fire",
            });
    }
    else
    {
        h2 = ({
            "burning " + HIM(enemy) + " to a cinder",
            "burning through you, extinguishing the last spark of " +
            "life",
            "burning " + HIM(enemy) + " to a cinder",
            });
    }

    player->catch_msg(h1[0] + ", " + h2[0] + ".\n");
    enemy->catch_msg(h1[1] + ", " + h2[1] + ".\n");
    player->tell_watcher(h1[2] + ", " + h2[2] + ".\n", enemy);
}

void
write_death_hit(object player, object enemy, int phurt, int damage_type,
    string hdesc)
{
    string *h1, *h2;
    object obj = query_enchanted();
    string s = obj->short();
    
    if (damage_type == W_BLUDGEON)
    {
        h1 = ({
            "You slam your " + s + " into " + enemy->query_the_name(player) +
            "'s " + hdesc,

            player->query_The_name(enemy) + " hits your " + hdesc + " with " +
            HIS(player) + " " + s,

            QCTNAME(player) + " hits " + QTNAME(enemy) + " with " +
            HIS(player) + " " + s,
        });
    }
    else if(damage_type == W_SLASH)
    {
        h1 = ({
            "You slash at " + enemy->query_the_name(player) + "'s " + hdesc +
            " with your " + s,
            
            player->query_The_name(enemy) + " slashes at your " + hdesc + " with " +
            HIS(player) + " " + s,

            QCTNAME(player) + " slashes at " + QTNAME(enemy) + " with " +
            HIS(player) + " " + s,
        });
    }
    else
    {
        h1 = ({
            "You stab at " + enemy->query_the_name(player) + "'s " + hdesc +
            " with your " + s,
            
            player->query_The_name(enemy) + " stabs at your " + hdesc + " with " +
            HIS(player) + " " + s,

            QCTNAME(player) + " stabs at " + QTNAME(enemy) + " with " +
            HIS(player) + " " + s,
        });
    }

    if (phurt <= 0)
    {
        h2 = ({
            ", but the deadly touch of the weapon fails to harm " + HIM(enemy),
            "",
            "",
            });
    }
    else if (phurt < 7)
    {           
        h2 = ({
            ", and the cold touch of the weapon hurts " + HIM(enemy) + " slightly",
            ", and from the weapon a cold, creeping touch emerges, hurting you " +
            "slightly",
            ", and the latter shudders slightly, as if suddenly cold",
            });
    }
    else if(phurt < 15)
    {
        h2 = ({
            ", and from the weapon streams forth a dark touch, festering in " +
            "the wound",
            ", and the touch of the weapon hurts you",
            ", making " + QTNAME(enemy) + " shudder uncontrollably",
            });
    }
    else if(phurt < 27)
    {
        h2 = ({
            ", inflicting upon " + HIM(enemy) + " the very touch of " +
            "grim-visaged death, making " + HIM(enemy) + " cry out " +
            "in agony",
            ", and in the touch of the weapon, a dark power overcomes " +
            "you, the searing pain making you cry out in agony",
            ", making " + QTNAME(enemy) + " cry out in agony",
            });
    }
    else if(phurt < 45)
    {
        h2 = ({
            ", and with that wound, a fell power enters " + HIS(enemy) +
            " whole body, causing the skin to blister in unbearable " +
            "pain",
            ", and an unbearable pain falls upon you, causing your " +
            "skin to blister",
            ", having " + QTNAME(enemy) + " almost to " + HIS(enemy) +
            " knees from an unnatural pain",
            });
    }
    else if(phurt < 99)
    {
        h2 = ({
            ", and with that touch, a hundred wounds open upon " +
            HIS(enemy) + " body, drawing the life out of " + HIS(enemy) +
            " very core",
            ", and a hundred wounds open upon your body, in undescribable " +
            "pain",
            ", rendering " + QTNAME(enemy) + " almost senseless from " +
            "the pain",
            });
    }
    else
    {
        h2 = ({
            ", and with that blow, it is as if a dark torrent of malignant " +
            "force enters " + HIS(enemy) + " very soul, wringing the last " +
            "vestiges of life from " + HIM(enemy),

            ", and with that blow, it is as if a dark torrent of malignant " +
            "force enters your very soul, wringing the last vestiges of " +
            "life from you",

            ", and an almost palpable power of darkness seems to wring the " +
            "very soul from " + QTNAME(enemy),
            });
    }

    player->catch_msg(h1[0] + h2[0] + ".\n");
    enemy->catch_msg(h1[1] + h2[1] + ".\n");
    player->tell_watcher(h1[2] + h2[2] + ".\n", enemy);    
}

void
write_air_hitback(object player, object enemy, int phurt)
{
    string *h1, *h2;
    object obj = query_enchanted();
    string s = obj->short();

    /* Messages in this order: ({ player, enemy, others }) */

    h1 = ({ "Bolts of lightning strike out from your " + s +
        " towards " + enemy->query_the_name(player),
        
        "Bolts of lightning strike out from " + player->query_the_name(enemy) +
        "'s " + s + " towards you",
        
        "Bolts of lightning strike out from " + QTNAME(player) + "'s " + s +
        " towards " + QTNAME(enemy),
    });

    if (phurt <= 0)
    {
        h2 = ({ ", narrowly missing " + HIM(enemy),
            ", narrowly missing you",
            ", narrowly missing " + HIM(enemy),
        });
    }
    else if (phurt < 7)
    {
        h2 = ({ ", singeing " + HIM(enemy) + " slightly",
            ", singeing you slightly",
            ", singeing " + HIM(enemy) + " slightly",
        });
    }
    else if (phurt < 15)
    {
        h2 = ({ ", burning " + HIM(enemy) + " somewhat",
            ", burning you somewhat",
            ", burning " + HIM(enemy) + " somewhat",
        });
    }
    else if (phurt < 27)
    {
        h2 = ({ ", burning " + HIM(enemy),
            ", burning you",
            ", burning " + HIM(enemy),
        });
    }
    else if (phurt < 45)
    {
        h2 = ({ ", burning " + HIM(enemy) + " severely",
            ", burning you severely",
            ", burning " + HIM(enemy) + " severely",
        });
    }
    else if (phurt < 99)
    {
        h2 = ({ ", engulfing " + HIS(enemy) + " whole body " +
            "in a searing blue fire",
            "engulfing your whole body in a searing blue fire",
            "engulfing " + HIS(enemy) + " whole body " +
            "in a searing blue fire",
        });
    }
    else
    {
        h2 = ({ ", burning " + HIM(enemy) + " to a cinder",
            "burning you to a cinder",
            "burning " + HIM(enemy) + " to a cinder",
        });
    }

    player->catch_msg(h1[0] + h2[0] + ".\n");
    enemy->catch_msg(h1[1] + h2[1] + ".\n");
    player->tell_watcher(h1[2] + h2[2] + ".\n", enemy);
}

void
write_death_hitback(object player, object enemy, int phurt)
{
    string *h1, *h2;
    object obj = query_enchanted();
    string s = obj->short();

    /* Messages in this order: ({ player, enemy, others }) */

    h1 = ({ "A dark power seeps from your " + s +
        " towards " + enemy->query_the_name(player),
        
        "A dark, chilling power seeps out from " + player->query_the_name(enemy) +
        "'s " + s + " towards you",
        
        "Strands of darkness emanates from " + QTNAME(player) + "'s " + s +
        ", reaching towards " + QTNAME(enemy),
    });

    if (phurt <= 0)
    {
        h2 = ({ ", narrowly missing " + HIM(enemy),
            ", narrowly missing you",
            ", narrowly missing " + HIM(enemy),
        });
    }
    else if (phurt < 7)
    {
        h2 = ({ ", and the cold touch hurts " + HIM(enemy) + " slightly",
            ", and the cold touch hurts you slightly",
            ", hurting " + HIM(enemy) + " slightly",
        });
    }
    else if (phurt < 15)
    {
        h2 = ({ ", hurting " + HIM(enemy) + " somewhat",
            ", hurting you somewhat",
            ", hurting " + HIM(enemy) + " somewhat",
        });
    }
    else if (phurt < 27)
    {
        h2 = ({ ", inflicting a cold, painful burning upon " + HIM(enemy),
            ", inflicting a cold, painful burning upon you",
            ", hurting " + HIM(enemy),
        });
    }
    else if (phurt < 45)
    {
        h2 = ({ ", making " + HIS(enemy) + " skin blister as the darkness festers",
            ", making your skin blister painfully as the darkness festers",
            ", making " + HIS(enemy) + " skin blister",
        });
    }
    else if (phurt < 99)
    {
        h2 = ({ ", engulfing " + HIM(enemy) + " in a dark cloud of " +
            "malignant power",
            "engulfing you in a dark cloud of malignant power that hurts " +
            "you severely",
            "engulfing " + HIM(enemy) + " in a dark cloud of malignant " +
            "power",
        });
    }
    else
    {
        h2 = ({ ", seemingly consuming " + HIS(enemy) + " very soul",
            ", touching you with the power of the grave, consuming your soul",
            ", seemingly consuming " + HIS(enemy) + " very soul",
        });
    }

    player->catch_msg(h1[0] + h2[0] + ".\n");
    enemy->catch_msg(h1[1] + h2[1] + ".\n");
    player->tell_watcher(h1[2] + h2[2] + ".\n", enemy);
    
}

void
do_hitback(int type, int pen, object tp, object att)
{
    mixed hitres;
    
    hitres = att->hit_me(pen, MAGIC_DT, tp, -1);

    if (tp->query_wiz_level())
    {
        tp->catch_tell("DEBUG: type: " + type + ", pen: " + pen + ", phurt: " + hitres[0] + "\n");
    }

    if (type == 1)
    {
        write_air_hitback(tp, att, hitres[0]);
    }
    else
    {
        write_death_hitback(tp, att, hitres[0]);
    }

    if (hitres[3] > 0 && gManaAbsorb > 0)
    {
        int mana = hitres[3] / 25;
        if (tp->query_wiz_level())
        {
            tp->catch_tell("DEBUG: absorb " + mana + " mana.\n");
        }
        if (mana > 0)
        {
            tp->add_mana(mana);
            tp->catch_tell("You feel mentally refreshed!\n");
        }
    }

    if (hitres[3] > 0 && gHPAbsorb > 0)
    {
        int hp = hitres[3] / 10;
        if (tp->query_wiz_level())
        {
            tp->catch_tell("DEBUG: absorb " + hp + " HP.\n");
        }
        if (hp > 0)
        {
            tp->heal_hp(hp);
            tp->catch_tell("You feel healthier!\n");
        }
    }
}

static void
do_break(object obj)
{
    if (objectp(obj))
        obj->remove_broken(0);
}

/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object obj = query_enchanted();
    object tp = obj->query_wielded();
    int r;
    int type = 0;
    object la;

    if (gAirDamage > 0 && !gAirReload)
        type = 1;
    if (gDeathDamage > 0 && !gDeathReload)
    {
        if (type == 1)
            type += random(2);
        else
            type = 2;
    }
    if (gBreak > 0 && !gBreakReload && phurt > 3)
    {
        int hitloc = 0;

        switch(hdesc)
        {
            case "head":
                hitloc = TS_HEAD;
                break;
            case "body":
                hitloc = TS_TORSO;
                break;
            case "left arm":
                hitloc = TS_LARM;
                break;
            case "right arm":
                hitloc = TS_RARM;
                break;
            case "legs":
                hitloc = TS_LEGS;
                break;
        }
        
        if (hitloc && (type == 0 || random(2)) && objectp(la = enemy->query_armour(hitloc)))
            type = 3;
    }
    
    r = obj->did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);

    if ( type == 3 )
    {
        /* Break armour, or try at least */
        tp->catch_msg("There is a flash of white light as your " +
            obj->short() + " impacts with " + enemy->query_the_name(tp) +
            "'s " + la->short() + ".\n");

        enemy->catch_msg("There is a flash of white light as " +
            tp->query_the_name(enemy) + "'s " + obj->short() + " impacts with " +
            "your " + la->short() + ".\n");
            
        tp->tell_watcher("There is a flash of white light as " +
            QTNAME(tp) + "'s " + obj->short() + " impacts with " +
            QTNAME(enemy) + "'s " + la->short() + ".\n", enemy);

        if (random(query_enchantment_strength()) >
            (la->query_ac() * 2) / 3)
        {
            set_alarm(0.1, 0.0, &do_break(la));
        }

        trigger_break_reload();
    }
    else if ( (type > 0) && (type < 3) && (phurt > 5) && (phurt < 100) )
    {
        int pen;
        int res;
        int damt;
        mixed hitres;

        if (type == 1)
        {
            res = enemy->query_magic_protection(MAGIC_I_RES_ELECTRICITY) +
                enemy->query_magic_protection(MAGIC_I_RES_MAGIC);
            damt = gAirDamage;
        }
        else
        {
            res = enemy->query_magic_protection(MAGIC_I_RES_DEATH) +
                enemy->query_magic_protection(MAGIC_I_RES_MAGIC);
            damt = gDeathDamage;
        }
        if (res > 100)
            res = 100;            

        pen = damt * (100 - res) * query_enchantment_strength() / PEN_FACTOR;
        if (type == 2)
            pen = (pen * 3) / 2;

        hitres = enemy->hit_me(pen, MAGIC_DT, tp, -1);

        if (tp->query_wiz_level())
        {
            tp->catch_tell("DEBUG: type: " + type + ", pen: " + pen + ", phurt: " + hitres[0] + "\n");
        }

        if (type == 1)
        {
            write_air_hit(tp, enemy, hitres[0], dt, hdesc);
            trigger_air_reload();
            add_dull( damt == 1 ? 1 : 3 );    
        }
        else
        {
            write_death_hit(tp, enemy, hitres[0], dt, hdesc);
            trigger_death_reload();
            add_corr( damt == 1 ? 1 : 3 );
        }

        if (hitres[3] > 0 && gManaAbsorb > 0)
        {
            int mana = hitres[3] / 25;
            if (tp->query_wiz_level())
            {
                tp->catch_tell("DEBUG: absorb " + mana + " mana.\n");
            }
            if (mana > 0)
            {
                tp->add_mana(mana);
                tp->catch_tell("You feel mentally refreshed!\n");
            }
        }

        if (hitres[3] > 0 && gHPAbsorb > 0)
        {
            int hp = hitres[3] / 10;
            if (tp->query_wiz_level())
            {
                tp->catch_tell("DEBUG: absorb " + hp + " HP.\n");
            }
            if (hp > 0)
            {
                tp->heal_hp(hp);
                tp->catch_tell("You feel healthier!\n");
            }
        }

        if (hitres[0] > 0)
            return 1;
    }
    
    return r;
}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    object tp = this_object()->query_worn();
    object obj = query_enchanted();
    int r;
    int type = 0;
    object lw;

    if (gAirDamage > 0 && !gAirReload)
        type = 1;
    if (gDeathDamage > 0 && !gDeathReload)
    {
        if (type == 1)
            type += random(2);
        else
            type = 2;
    }
    if (gBreak > 0 && !gBreakReload && ph > 1 && objectp(lw = tp->ei_query_last_weapon()))
    {
        if (type == 0 || random(2))
            type = 3;
    }

    r = obj->got_hit(hid,ph,att,dt,dam);

    if ( type == 3 )
    {
        /* Break weapon, or try at least */
        tp->catch_msg("There is a flash of white light as " +
            att->query_the_name(tp) + "'s " + lw->short() + " impacts with " +
            "your " + obj->short() + ".\n");
            
        att->catch_msg("There is a flash of white light as your " +
            lw->short() + " impacts with " + tp->query_the_name(att) +
            "'s " + obj->short() + ".\n");
            
        tp->tell_watcher("There is a flash of white light as " +
            QTNAME(att) + "'s " + lw->short() + " impacts with " +
            QTNAME(tp) + "'s " + obj->short() + ".\n", att);

        if (random(query_enchantment_strength()) >
            (lw->query_hit() + lw->query_pen()) / 3)
        {
            set_alarm(0.1, 0.0, &do_break(lw));
        }

        trigger_break_reload();
    }
    else if ( (dt != MAGIC_DT) && (type > 0) && (type < 3) && (ph > 0) )
    {
        mixed hitres;
        int pen;
        int res;
        int damt;

        if (type == 1)
        {
            res = att->query_magic_protection(MAGIC_I_RES_ELECTRICITY) +
                att->query_magic_protection(MAGIC_I_RES_MAGIC);
            damt = gAirDamage;
        }
        else
        {
            res = att->query_magic_protection(MAGIC_I_RES_DEATH) +
                att->query_magic_protection(MAGIC_I_RES_MAGIC);
            damt = gDeathDamage;
        }
        if (res > 100)
            res = 100;            

        pen = damt * (100 - res) * query_enchantment_strength() / PEN_FACTOR;
        if (type == 2)
            pen = (pen * 3) / 2;

        /* If this blow kills us, up the charge in desperation */
        if (ph > 100)
            pen *= 3;

        do_hitback(type, pen, tp, att);

        if (type == 1)
        {
            trigger_air_reload();
        }
        else
        {
            trigger_death_reload();
        }
        add_dull( damt == 1 ? 1 : 3 );
    }

    return 0;
}
