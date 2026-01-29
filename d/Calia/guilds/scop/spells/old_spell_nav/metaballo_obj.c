
/*
 * metaballo_obj.c
 *
 * This is the spell object for the metaballo (Covert Weapon) spell for 
 * the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *                Jaacar, September 21st, 2003 - Added colours to tell them 
 *                                               apart from each other.
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Changes by Bishop, July 2004.
 * Some adjustments, Bishop Sept. 2004.
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/d/Genesis/newmagic/resist.c";
inherit "/std/weapon";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <tasks.h>
#include <filter_funs.h>

#include "defs.h"
#include SPIRIT_HEADER

//This weapon is good for 600 hits:
#define NUM_HITS 600

int drain_amount = 0; //The hp damage a drain does.
int preparing_drain = 0; 
int humming = 0; //Set to 1 if we are fighting the undead.
int speed = 0; //Bonus to LIVE_I_QUICKNESS
int hits = 0; //The number of hits the weapon has done.

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void 
create_weapon()
{
    set_name("weapon");
    add_name("_metaballo_weapon_");
    set_short("non-descript weapon");
    set_long("Contact the guild master if you see this message. Something" +
        " went wrong creating this weapon.\n");

    add_prop(OBJ_S_WIZINFO, "This is a weapon created with the metaballo "+
        "spell from the Spirit Circle of Psuchae. Another weapon was "+
        "sacrificed in the creation of it. 33% of the time, if the" +
        " wielder is fighting the undead, this weapon will do a special" +
        " attack draining the target of health, transferring" +
        " half of it back to the wielder \n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC, ({"50","transmutation"}));
    add_prop(MAGIC_AM_ID_INFO,({"This weapon has been magically created.\n",20,
        "This weapon was created from another weapon through means of a "+
        "spell. It has been dedicated to eradicating the undead.\n",40}));
    
    set_hit(20);
    set_pen(20);
    set_wt(W_CLUB);
    set_wf(TO);
    set_dt(W_BLUDGEON); 
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(TO->query_pen(), 
        TO->query_wt()));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_WEAPON(TO->query_pen(), 
        TO->query_wt()));
    add_prop(OBJ_M_NO_SELL, "You cannot sell this weapon!");
    add_prop(OBJ_M_NO_BUY, "You cannot buy this weapon.");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

}

//This function just checks if we're in combat, and if we're not, turns the
//humming off.
void
check_humming()
{
    object wielder = environment(TO);
 
    if (humming && !objectp(wielder->query_attack()))
    {
        wielder->catch_msg("The " + TO->short() + " becomes silent and" +
            " still.\n");
        TO->set_hit(TO->query_hit() - 10);
        TO->set_pen(TO->query_pen() - 10);
        wielder->update_weapon(TO);
        wielder->add_prop(LIVE_I_QUICKNESS, 
            wielder->query_prop(LIVE_I_QUICKNESS) - speed);
        humming = 0;    
    }
}

int
start()
{
    set_alarm(20.0, 20.0, &check_humming());
    //60 minute duration:
    return 1;
}


varargs public int
dispel_spell_effect(object dispeller)
{
    object wielder = environment(TO);
    spell_caster->catch_msg("Your " + TO->short() +
        " melds into nothingness.\n");
    if (TO->query_wielded())
    {
        tell_room(environment(spell_caster), "The " + TO->short() + " wielded"+
            " by " + QTNAME(spell_caster) + " melds into nothingness.\n", 
            ({spell_caster}) + FILTER_IS_SEEN(spell_caster, 
            FILTER_LIVE(all_inventory(environment(spell_caster)))));
    }

    if (humming)
    {
        wielder->add_prop(LIVE_I_QUICKNESS, 
            wielder->query_prop(LIVE_I_QUICKNESS) - speed);
        wielder->query_combat_object()->cb_update_speed();             
    }
            
    remove_spell_effect_object();
    return 1;

}

void
set_twoh()
{
    set_hands(W_BOTH);
}

void
configure_weapon(int level)
{
    if (level == 1)
    { 
        if (query_hands() == W_BOTH)
        {
            set_hit(41);
            set_pen(41);
            drain_amount = 150;
            speed = 60;
            set_name("quarterstaff");
            set_adj("steel-grey");
            set_short("steel-grey quarterstaff");
            set_long("This quarterstaff, a gift from Psuchae, appears to be" +
                " a handy weapon. You can sense that its purpose is to" +
                " fight the undead.\n");
        }
        else
        {
            set_hit(40);
            set_pen(38);
            drain_amount = 120;
            speed = 50;
            set_name("baton");
            set_adj("shadow-speckled");
            set_short("shadow-speckled baton");
            set_long("This baton, a gift from Psuchae, appears to be" +
                " a handy weapon. You can sense that its purpose is to" +
                " fight the undead.\n");
        }
    }
    else
    if (level == 2)
    {
        if (query_hands() == W_BOTH)
        {
            set_hit(44);
            set_pen(44);
            drain_amount = 225;
            speed = 90;
            set_name("flail");
            set_adj("shadow-wrought");
            set_short("shadow-wrought flail");
            set_long("This flail, a gift from Psuchae, appears to be" +
                " a strong weapon. You can sense that its purpose is to" +
                " fight the undead.\n");
        }
        else
        {
            set_hit(43);
            set_pen(40);
            drain_amount = 180;
            speed = 75;
            set_name("morning-star");
            set_adj("silvery");
            set_short("silvery morning-star");
            set_long("This morning-star, a gift from Psuchae, appears to be" +
                " a strong weapon. You can sense that its purpose is to" +
                " fight the undead.\n");
        }
    
    }
    else
    {
        if (query_hands() == W_BOTH)
        {
            set_hit(47);
            set_pen(47);
            drain_amount = 300;
            speed = 120;
            set_name("maul");
            set_adj("shadow-infused");
            set_short("shadow-infused maul");
            set_long("This maul, a gift from Psuchae, appears to be" +
                " a powerful weapon. You can sense that its purpose is to" +
                " fight the undead.\n");
        }
        else
        {
            set_hit(46);
            set_pen(42);
            drain_amount = 240;
            speed = 100;
            set_name("war-mace");
            set_adj("umbral");
            set_short("umbral war-mace");
            set_long("This war-mace, a gift from Psuchae, appears to be" +
                " a powerful weapon. You can sense that its purpose is to" +
                " fight the undead.\n");
        }
    }
}


void
do_drain()
{
    string desc = "beam";
    object enemy = spell_caster->query_attack();
    int resist = spell_resist(spell_caster, enemy, SS_ELEMENT_LIFE, 
        TASK_DIFFICULT) + spell_resist(spell_caster, enemy, 
        SS_ELEMENT_DEATH, TASK_DIFFICULT);
    resist = resist/2;

    if (objectp(enemy) && enemy->query_prop(LIVE_I_UNDEAD))
    {
        if (drain_amount >= 180)
            desc = "spear";
        if (drain_amount >= 240)
            desc = "lance";
            
        spell_caster->catch_msg("A " + desc + " of light erupts from your " + 
            TO->short() + ", striking " + enemy->query_the_name(spell_caster) +
            ". You feel invigorated.\n");
        enemy->catch_msg("A " + desc + " of light erupts from " + 
            LANG_POSS(spell_caster->query_the_name(enemy)) + " " + TO->short()+
            ", striking you. You feel drained.\n");
        spell_caster->tell_watcher("A " + desc + " of light erupts from " + 
            LANG_POSS(QTNAME(spell_caster)) + " " + TO->short()+ ", striking "+
            QTNAME(enemy) + ".\n", enemy);
            
        enemy->heal_hp(-drain_amount*(100 - resist)/100);
	spell_caster->heal_hp(drain_amount*(100 - resist)/200);
	
	if (enemy->query_hp() <= 0)
	{
            wielder->add_mana(enemy->query_average_stat()/2);
            spell_caster->catch_tell("As your " + TO->short() + " destroys " + 
                enemy->query_the_name(spell_caster) + " you feel the unholy" +
                " energies binding it to this world dissipating. You are" +
                " able to absorb some of it.\n");	
	    enemy->do_die(spell_caster);
	}
    }
    
    preparing_drain = 0;
}



int
try_hit(object target)
{
    object wielder = environment(TO);
        
    if (!preparing_drain && target->query_prop(LIVE_I_UNDEAD) && 
        objectp(TO->query_wielded()))
    {
        set_alarm(itof(6 + random(6)), 0.0, &do_drain());
        preparing_drain = 1;
    }
    
    if (!humming && target->query_prop(LIVE_I_UNDEAD) && 
        objectp(TO->query_wielded()))
    {
        wielder->catch_msg("The " + TO->short() + " begins to emit a loud" +
            " keening sound, and comes alive in your grip!\n");
        tell_room(environment(wielder), "The " + TO->short() + " wielded by " +
            QTNAME(wielder) + " begins to emit a loud keening sound!\n", 
            ({wielder}));
        TO->set_hit(TO->query_hit() + 10);
        TO->set_pen(TO->query_pen() + 10);
        wielder->update_weapon(TO);        
        wielder->add_prop(LIVE_I_QUICKNESS, 
            wielder->query_prop(LIVE_I_QUICKNESS) + speed);
        wielder->query_combat_object()->cb_update_speed();            
        humming = 1;
    }
    else
    if (humming && !target->query_prop(LIVE_I_UNDEAD))
    {
        //This means we have the hit bonus, but are not actually trying to
        //hit an undead.
        wielder->catch_msg("The " + TO->short() + " becomes silent and" +
            " still.\n");
        TO->set_hit(TO->query_hit() - 10);
        TO->set_pen(TO->query_pen() - 10);
        wielder->update_weapon(TO);        
        wielder->add_prop(LIVE_I_QUICKNESS, 
            wielder->query_prop(LIVE_I_QUICKNESS) - speed);
        wielder->query_combat_object()->cb_update_speed();             
        humming = 0;
    }
    
    return 1;
}


public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, 
    int dam, int hid)
{
    int real_phurt;
    string desc1, desc2, desc3;
    object wielder = environment(TO);

    hits++;
    if (hits >= NUM_HITS)
    {
        set_alarm(1.0, 0.0, &dispel_spell_effect());
    }

    //If target is undead and damage was dealt, special descriptions.
    if (enemy->query_prop(LIVE_I_UNDEAD) && dam > 0)
    {
        switch(random(6))
        {
            case 0:
                desc1 = "You are barely able to hang on as your " + TO->short()
                    + " as it lunges wildly towards " + 
                    LANG_POSS(enemy->query_the_name(wielder)) + " " + hdesc +
                    ".";
                desc2 = QCTNAME(wielder)+" appears barely able to hang on as "+
                    wielder->query_possessive() + " " + TO->short() + 
                    " lunges wildly towards " + LANG_POSS(QTNAME(enemy)) + 
                    " " + hdesc + ".";
                desc3 = capitalize(wielder->query_the_name(enemy)) + 
                    " appears barely able to hang on as " + 
                    wielder->query_possessive() + " " + TO->short() +
                    " lunges wildly towards your " + hdesc + ".";
                break;
            case 1:
                desc1 = "You bring your " + TO->short() + " around in a wide" +
                    " arc, but the weapon violently changes direction in mid" +
                    "-swing, bearing down on " + 
                    LANG_POSS(enemy->query_the_name(wielder)) + " " + hdesc +
                    ".";
                desc2 = QCTNAME(wielder) + " brings " + 
                    wielder->query_possessive() + " " + TO->short() + 
                    " around in a wide arc, but the weapon violently changes" +
                    " direction in mid-swing, bearing down on " +
                    LANG_POSS(QTNAME(enemy)) + " " + hdesc + ".";
                desc3 = capitalize(wielder->query_the_name(enemy)) + 
                    " brings " + wielder->query_possessive() + " " + 
                    TO->short() + " around in a wide arc, but the weapon" +
                    " violently changes direction in mid-swing, bearing down" +
                    " on your " + hdesc + ".";
                break;
            case 2:
                desc1 = "Exploding into motion from a defensive stance, your "+
                    TO->short() + " hurtles towards " + 
                    LANG_POSS(enemy->query_the_name(wielder)) + " " + hdesc +
                    ".";
                desc2 = "Exploding into motion from a defensive stance, " + 
                    LANG_POSS(QTNAME(wielder)) + " " + TO->short() + 
                    " hurtles towards " + LANG_POSS(QTNAME(enemy)) + " " + 
                    hdesc + ".";
                desc3 = "Exploding into motion from a defensive stance, " + 
                    LANG_POSS(wielder->query_the_name(enemy)) + " " + 
                    TO->short() + " hurtles towards your " + hdesc + ".";
                break;
            case 3:
                desc1 = "As you are trying to figure out how to best press" +
                    " your attack, your " + TO->short() + " lurches suddenly,"+
                    " striking out at " +  
                    LANG_POSS(enemy->query_the_name(wielder)) + " " + hdesc +
                    ".";
                desc2 = "As " + QTNAME(wielder) + " contemplates " + 
                    wielder->query_possessive() + " next move, " + 
                    wielder->query_possessive() + " " + TO->short() + 
                    " lurches suddenly, striking out at "  + 
                    LANG_POSS(QTNAME(enemy)) + " " + hdesc + ".";
                desc3 = "As " + wielder->query_the_name(enemy) + 
                    " contemplates " + 
                    wielder->query_possessive() + " next move, " + 
                    wielder->query_possessive() + " " + TO->short() + 
                    " lurches suddenly, striking out at your " + hdesc + ".";
                break;
            case 4:
                desc1 = "You attempt a graceful swing with your " + TO->short()
                    + ", but it jerks abruptly in your grip, crashing down" +
                    " on " + LANG_POSS(enemy->query_the_name(wielder)) + 
                    " " + hdesc + ".";
                desc2 = QCTNAME(wielder) + " attempts a graceful swing with " +
                    wielder->query_possessive() + " " + TO->short() + ", but" +
                    " it jerks abruptly in " + wielder->query_possessive() + 
                    " grip, crashing down on " + 
                    LANG_POSS(QTNAME(enemy)) + " " + hdesc + ".";
                desc3 = capitalize(wielder->query_the_name(enemy)) + 
                    " attempts a graceful swing with " +
                    wielder->query_possessive() + " " + TO->short() + ", but" +
                    " it jerks abruptly in " + wielder->query_possessive() + 
                    " grip, crashing down on your " + hdesc + ".";
                break;
            default:
                desc1 = "Holding your " + TO->short() + " out from your body,"+
                    " you rotate, combining its strength with yours in a" +
                    " furious blow aimed at " +
                    LANG_POSS(enemy->query_the_name(wielder)) + " " + hdesc +
                    ".";
                desc2 = "Holding " + wielder->query_possessive() + " " + 
                    TO->short() + " out from " + wielder->query_possessive() +
                    " body, " + QTNAME(wielder) + " rotates, throwing all " +
                    wielder->query_possessive() + " strength into a furious" +
                    " blow aimed at " +                                   
                    LANG_POSS(QTNAME(enemy)) + " " + hdesc + ".";
                desc3 = "Holding " + wielder->query_possessive() + " " + 
                    TO->short() + " out from " + wielder->query_possessive() +
                    " body, " + wielder->query_the_name(enemy) + 
                    " rotates, throwing all " +
                    wielder->query_possessive() + " strength into a furious" +
                    " blow aimed at your " + hdesc + ".";
        } 
 
        desc1 += " The attack ";
        desc2 += " The attack ";
        desc3 += " The attack ";
    
        switch(phurt)
        {
            case 0..3:
                desc1 += "does not connect properly, leaving" +
                    " only a scratch.";
                desc2 += "does not connect properly, leaving" +
                    " only a scratch.";                    
                desc3 += "does not connect properly, leaving" +
                    " only a scratch.";
                break;
            case 4..7:
                desc1 += "just nicks " + enemy->query_objective() +
                    ", leaving a small bruise.";
                desc2 += "just nicks " + enemy->query_objective() +
                    ", leaving a small bruise.";
                desc3 += "just nicks you, leaving a small bruise.";
                break;
            case 8..13:
                desc1 += "batters " + enemy->query_objective() + ", leaving" +
                    " an unsightly wound.";
                desc2 += "batters " + enemy->query_objective() + ", leaving" +
                    " an unsightly wound.";                    
                desc3 += "batters you, leaving an unsightly wound.";
                break;
            case 14..20:
                desc1 += "pounds " + enemy->query_objective() + ", hurting " +
                    enemy->query_objective() + " badly.";
                desc2 += "pounds " + enemy->query_objective() + ", hurting " +
                    enemy->query_objective() + " badly.";
                desc3 += "pounds you, hurting you badly.";
                break;
            case 21..35:
                desc1 += "smashes into " + enemy->query_objective() + 
                    ", breaking bones.";
                desc2 += "smashes into " + enemy->query_objective() + 
                    ", breaking bones.";                
                desc3 += "smashes into you, breaking bones.";
                break;
            default:
                desc1 += "crushes " + enemy->query_objective() + 
                    ", pulverizing bone.";
                desc2 += "crushes " + enemy->query_objective() + 
                    ", pulverizing bone.";                    
                desc3 += "crushes you, pulverizing bone.";
        }
           
        wielder->catch_msg(desc1 + "\n");
        wielder->tell_watcher(desc2 + "\n", ({wielder, enemy}));
        enemy->catch_msg(desc3 + "\n");
        
        if (enemy->query_hp() <= 0)
        {
            wielder->add_mana(enemy->query_average_stat()/2);
            wielder->catch_tell("As your " + TO->short() + " destroys " + 
                enemy->query_the_name(wielder) + " you feel the unholy" +
                " energies binding it to this world dissipating. You are" +
                " able to absorb some of it.\n");
            enemy->do_die(wielder);
        }
        
        return 1;
    } 
    else
    {
        return 0;
    }
}


/*
 *  FUNCTION: wield
 *  Arguments: object ob
 *  Returns  : int (0,1)
 * 
 * This function is called when someone wields the staff.
 * Only guild members can wield it.
 *
*/
public mixed
wield(object weapon)
{
    if (is_spirit(TP) || TP->query_wiz_level())
    {
        write("You wield the "+weapon->short()+".\n");
        tell_room(environment(TP),QCTNAME(TP)+" wields "+HIS+" "+
            weapon->short()+".\n",TP);
        return 1;
    }
    
    else
    {
        return "Try as you might, you just cannot wield this weapon. Every "+
            "time you hold it in your hands it just slips out.\n";
    } 

}

void 
set_likely_break(int i)
{
    i=0;
    ::set_likely_break(i);
}

public string
query_recover()
{
    return 0;
}

int
wep_dispel(string str)
{
    dispel_spell_effect(spell_caster);
    return 1;
}

void
init()
{
    ::init();
    add_action(wep_dispel, "wepdispel");
}
