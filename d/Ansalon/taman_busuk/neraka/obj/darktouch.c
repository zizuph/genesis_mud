/* 
 * darktouch.c
 *
 * Enchantment: Dark Touch
 * This enchantment works on slashing and impaling weapons.
 * On impact, the weapon spreads the dark touch, doing damage
 * to all but undeads and the most evil creatures.
 * However, the more good the creature is, the more damage it
 * does, spreading corruption and evil in the wound.
 * A sword enchanted thus cannot be wielded by creatures above
 * 400 in alignment.
 *
 * Ashlar, 2 Aug 97
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

#define ET_WEAPON   1
#define ET_ARMOUR   2
#define ET_OBJECT   4

#define RELOAD_TIME 15
int gReload;
int gDecay = 0;

/* These do not require calling of the inherited function */
string wizinfo_extra()
{
    return "Makes the weapon do extra damage on creatures, more " +
        "damage the more goodaligned they are.\n";
}

mixed *query_identify_info()
{
    return ({
        "This weapon is more effective against good creatures.\n", 10,
        "It spreads the Dark Touch, a corrupting evil that hurts " +
            "the enemy.\n", 23,
        "The Dark Touch has no effect on undeads or creatures of " +
            "great evil, but much effect against the forces of good.\n", 50,
    });
}

mixed enchant_object(object obj)
{
    if (query_enchanted_object_type() != ET_WEAPON)
        return "This enchantment can only affect weapons!";
    if (!(obj->query_dt() & (W_SLASH | W_IMPALE)))
        return "The enchantment has no effect on the " + obj->short() + ".";

    obj->say("The " + obj->short() + " seems to grow darker, and a cold " +
        "blue flame flickers along the blade.\n");

    gReload = 0;
    return 0;
}
varargs void remove_enchantment(int quiet)
{
    object obj = query_enchanted();
    if (!quiet && objectp(obj))
    {
        obj->say("Somehow, the " + obj->short() + " seems duller and " +
            "less powerful.\n");
    }
}

/*
string query_enchantment_recover() { return sprintf("%d",gMod); }
void init_enchantment_recover(string arg)
{
    if(sscanf(arg,"%d", gMod) != 1)
        gMod = 0;
}
*/

/* To redefine these, you must call the inherited function (::wear etc.) */
mixed
wield(object what)
{
    mixed r;
    r = ::wield(what);

    if (intp(r) && (r >= 0))
    {
        if (TP->query_alignment() < -200)
        {
            write("As you wield the " + what->short() +
                ", you sense something welcoming you.\n");
        }
        else if (TP->query_alignment() < 400)
        {
            write("As you wield the " + what->short() +
                ", you sense something grudgingly accepting you.\n");
        }
        else
        {
            write("As you try to wield the " + what->short() +
                ", it repels you!\n");

            return -1;
        }
    }
    return r;
}


static void
reload_darktouch()
{
    gReload = 0;
    if (gDecay && random(2))
    {
        set_enchantment_strength(query_enchantment_strength()-1);
        if (query_enchantment_strength() <= 0)
            set_alarm(0.0,0.0,dispel_magic(100));
    }
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

    r = obj->did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);

    if ( !gReload && (dt & (W_SLASH | W_IMPALE)) && (phurt > 5) &&
        (phurt < 100) && (!enemy->query_prop(LIVE_I_UNDEAD)) &&
        (enemy->query_alignment() > -1000))
    {
        mixed hitres;
        int pen;
        string *h1, *h2;
        int res;

        res = enemy->query_magic_protection(MAGIC_I_RES_ELECTRICITY) +
            enemy->query_magic_protection(MAGIC_I_RES_MAGIC);
        if (res > 100)
            res = 100;            

        pen = ((enemy->query_alignment() + 1000) *
            phurt * (100 - res) * query_enchantment_strength()) / 2000000;
        
        hitres = enemy->hit_me(pen, MAGIC_DT, tp, -1);
        if (tp->query_wiz_level())
        {
            tp->catch_msg("DEBUG: pen: " + pen + ", phurt: " + hitres[0] + "\n");
        }

        if (hitres[0] < 0)
            return r;
            
        if (dt == W_SLASH)
        {
            h1 = ({
                "A cold blue flame leaps from the blade of your " +
                obj->short() + " as you slash it across " + QTNAME(enemy) +
                "'s " + hdesc,

                "A cold blue flame leaps from the blade of " + QTNAME(tp) +
                "'s " + obj->short() + " as " + HE(tp) + " slashes it " +
                "across your " + hdesc,

                "A cold blue flame leaps from the blade of " + QTNAME(tp) +
                "'s " + obj->short() + " as " + HE(tp) + " slashes it " +
                "across " + QTNAME(enemy) + "'s " + hdesc,
                });
        }
        else
        {
            h1 = ({
                "As you pierce the " + hdesc + " of " + QTNAME(enemy) +
                " with the tip of your " + obj->short() + ", a cold blue " +
                "flame leaps from the weapon",
                
                "As " + QTNAME(tp) + " pierces your " + hdesc + " with " +
                "the tip of " + HIS(tp) + " " + obj->short() + ", a cold " +
                "cold blue flame leaps from the weapon",

                "As " + QTNAME(tp) + " pierces " + QTNAME(enemy) + "'s " +
                hdesc + " with the tip of the " + obj->short() + ", a cold " +
                "blue flame leaps from the weapon",
                });

        }       

        if (hitres[0] <= 0)
        {
            h2 = ({
                "crackling harmlessly against " + HIM(enemy),
                "crackling harmlessly against you",
                "crachling harmlessly against " + HIM(enemy),
                });
        }
        else if (hitres[0] < 7)
        {           
            h2 = ({
                "burning " + HIM(enemy) + " slightly",
                "burning you slightly",
                "burning " + HIM(enemy) + " slightly",
                });
        }
        else if(hitres[0] < 15)
        {
            h2 = ({
                "burning " + HIM(enemy),
                "burning you",
                "burning " + HIM(enemy),
                });
        }
        else if(hitres[0] < 27)
        {
            h2 = ({
                "charring " + HIS(enemy) + " flesh",
                "charring your flesh",
                "charring " + HIS(enemy) + " flesh",
                });
        }
        else if(hitres[0] < 45)
        {
            h2 = ({
                "burning " + HIM(enemy) + " with a searing fire",
                "burning you with a searing fire that spreads through " +
                "your body",
                "burning " + HIM(enemy) + " with a searing fire",
                });
        }
        else if(hitres[0] < 99)
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

        gReload = 1;
        set_alarm(itof(RELOAD_TIME+random(RELOAD_TIME)),0.0,reload_darktouch);

        tp->catch_msg(h1[0] + ", " + h2[0] + ".\n");
        enemy->catch_msg(h1[1] + ", " + h2[1] + ".\n");
        tp->tell_watcher(h1[2] + ", " + h2[2] + ".\n", enemy);

        if (hitres[0] > 0)
            return 1;
    }
    return r;
}

void
set_darktouch_decay(int decay)
{
    gDecay = decay;
}

int
query_darktouch_decay()
{
    return gDecay;
}
