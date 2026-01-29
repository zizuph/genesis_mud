/* Stralle @ Genesis 040210
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/rituals/shadows/std_enchantment";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>

#define RELOAD_TIME 8

int gReload;

string
wizinfo_extra()
{
    return "Adds a special to the weapon, the more goodaligned, " +
        "the more damage.\n";
}

string
query_strength_desc()
{
    switch (query_enchantment_strength())
    {
        case 1..15:
            return "weak";
        case 16..30:
            return "somewhat powerful";
        case 31..50:
            return "powerful";
        case 51..75:
            return "very powerful";
        case 76..90:
            return "extremely powerful";
        case 91..100:
            return "vastly powerful";
    }
}

mixed *
query_identify_info()
{
    return ({
        "This weapon is more effective against creatures of the " +
        "light.\n", 10,
        "It spreads the Dark Touch, a corruptive force that hurts " +
        "the enemy.\n", 25,
        "The Dark Touch has no effect on the living dead nor " +
        "the creatures following the path of darkness but is " +
        "most effective against the forces of good.\n", 50,
        "The enchantment laid upon the weapon seems " +
        query_strength_desc() + ".\n", 60,
        });
}

mixed
enchant_object(object obj)
{
    if (query_enchanted_object_type() != 1)
        return "This enchantment can only affect weapons!";
    if (!(obj->query_wt() & W_CLUB))
        return "The enchantment has no effect on the " + obj->short() + ".";

    allbb("The " + obj->short() + " seems to grow darker and a blue " +
        "flame strikes through it for a moment.\n");
    
//    set_enchantment_duration(3600);
    
    return 0;
}

varargs void
remove_enchantment(int quiet)
{
    object obj = query_enchanted();
    if (!quiet && objectp(obj))
    {
        allbb("Somehow the " + obj->short() + " seems duller and " +
            "less powerful.\n");
    }
}

mixed
wield(object what)
{
    mixed r;
    r = ::wield(what);
    
    if (intp(r) && (r >= 0))
    {
        if (this_player()->query_alignment() < -200)
        {
            write("As you wield the " + what->short() +
                ", you sense something welcoming you.\n");
            say(QCTNAME(this_player()) + " wields " +
                this_player()->query_possessive() + " " +
                QSHORT(this_object()) + ".\n");
            return 1;
        }
        else if (this_player()->query_alignment() < 400)
        {
            write("As you wield the " + what->short() +
                ", you sense something grudgingly accepting you.\n");
            say(QCTNAME(this_player()) + " wields " +
                this_player()->query_possessive() + " " +
                QSHORT(this_object()) + ".\n");
            return 1;
        }
        else
        {
            return "As you try to wield the " + what->short() +
                ", it repels you!\n";
        }
    }

    return r;
}

void
reload_darktouch()
{
    gReload = 0;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
        int dam)
{
    object obj = query_enchanted(), tp = obj->query_wielded();
    int res, pen;
    string *h1, *h2, t;
    mixed hitres;
    
    if (!gReload && (dt & (W_BLUDGEON)) && (phurt > 0) &&
        (phurt < 100) && (!enemy->query_prop(LIVE_I_UNDEAD)) &&
        (enemy->query_alignment() > -1000))
    {
        res = enemy->query_magic_protection(MAGIC_I_RES_ELECTRICITY) +
              enemy->query_magic_protection(MAGIC_I_RES_MAGIC);
        if (res > 100)
            res = 100;
        
        pen = ((enemy->query_alignment() + 1000) *
            phurt * (100 - res) * query_enchantment_strength()) / 2000000;
        
        hitres = enemy->hit_me(F_PENMOD(30 + random(10), pen), MAGIC_DT, tp, -1);

        setuid();
        seteuid(getuid());
        if (file_size("/d/Ansalon/log/pot/dark_touch") >= 50000)
            rename("/d/Ansalon/log/pot/dark_touch", "/d/Ansalon/log/pot/dark_touch.old");
        write_file("/d/Ansalon/log/pot/dark_touch", "DEBUG: W: " +
            tp->query_real_name() + ", foe: " + enemy->query_real_name() +
            " pen: " + pen + ", phurt(org): " +
                phurt + ", phurt: " + hitres[0] +
                ", hp: " + hitres[3] + "\n");
        
        if (hitres[0] < 0)
            return obj->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
        
        t = (({ "bludgeon", "smash", "hit", "pound" })[random(4)]);
        h1 = ({ "A cold blue flame leaps from the " + obj->short() +
                " as you " + t + " it into the " + hdesc + " of " +
                QTNAME(enemy),
                "A cold blue flame leaps from " + QTNAME(tp) + "'s " +
                obj->short() + " as " + HE(tp) + " " + LANG_PWORD(t) +
                " it into your " + hdesc,
                "A cold blue flame leaps from " + QTNAME(tp) + "'s " +
                obj->short() + " as " + HE(tp) + " " + LANG_PWORD(t) +
                " it into the " + hdesc + " of " + QTNAME(enemy),
            });
            
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
        set_alarm(itof(RELOAD_TIME + random(RELOAD_TIME / 2)), 0.0,
            reload_darktouch);
        
        tp->catch_msg(h1[0] + ", " + h2[0] + ".\n");
        enemy->catch_msg(h1[1] + ", " + h2[1] + ".\n");
        tp->tell_watcher(h1[2] + ", " + h2[2] + ".\n", enemy);
        
        if (hitres[0] > 0)
            return 1;
    }

    return obj->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}


/*
Enemy sees: "As the " + TO->short() + " connects, darkness erupts from it,
creeping into your skin, chilling it.\n"


Toby (05:43 PM) : 
inte dark spiritual glow?
Kitaare (05:44 PM) : 
Just nu bara "... The weapon has a spiritual glow about it."
Kitaare (05:44 PM) : 
caster->catch_tell("You chant silently and around the " +
tar->query_name() + " a faint glow begins to show, increasing in " +
"strength to suddenly engulf the weapon in a spiritual swirling " +
"glow.\n");
Toby (05:45 PM) : 
jätte bra skada av special extra desc för enemy:
"As the " + TO->short() + " connects, darkness erupts from it, creeping into
your skin, chilling it. Faintly you feel pictures intrude your mind of a
multicoloured dragon clasping your heart.\n"
Toby (05:46 PM) : 
Enemy sees: "As the " + TO->short() + " connects, the swirling glow
surrounding the weapon erupts, creeping over your skin, chilling it.\n"
Toby (05:47 PM) : 
"As the " + TO->short() + " connects, the swirling glow surrounding the
weapon erupts, creeping over your skin, chilling it. Faintly you feel
pictures intrude your mind of a multicoloured dragon clasping your heart.\n"
"As the " + TO->short() + " connects, the swirling glow surrounding the
weapon erupts, creeping over your skin, chilling it. Faintly you feel
pictures intrude your mind of a multicoloured dragon clasping your heart.\n"
Toby (05:54 PM) : 
"The swirling spiritual glow on your " + TO->short() + " pulses, as if alive,
when it connects to the " + hdesc() + " of your enemy, " +
(enemy->query_align(), good = "chilling ", evil = "burning " ) + HIM + " " +
damdesc() + ".\n"
Enemy: "The swirling spiritual glow on " + QTNAME(TP)+ pulses, as if alive
when it connetcs to your " + hdesc() +, hantering för bränna eller kyla
Enemy: "The " + TO->short() + " wielded by " + QTNAME(TP) + suddenly release
a burst of its swirling glow towards your " + hdesc() + ", " + hantering för
bränna eller kyla

Toby (06:10 PM) : 
Ingen special 40% chans för meddelande:

"The spiritual glow surrounding the " + TO->short() +  " dance " +
switch(random(5)) ["vividly", "slowly", "wildly", "with a life of its own",
"vividly almost pulsating"] + " around the weapon.\n"

*/                            
