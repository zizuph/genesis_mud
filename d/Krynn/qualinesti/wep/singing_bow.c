/* File name : composite_bow.c
 *
 * INFO:
 * The singing longbow wielded by Qualthas. The bow requires combination
 * of SS_STR and SS_DEX to be wielded. It increases the wielder's 
 * SS_WEP_MISSILE skill  but lowers his DEFENCE. If he is an elf, the 
 * bow becomes singing elven longbow and increases the wielder's quickness 
 * by 50. Also if player has skill SS_WEP_MISSILE higher than 29 the bow 
 * will become humming and its to_hit and to_pen increase by 5, but as a 
 * singing bow these values increase by another 5. 
 *
 * Blizzard 02/2003
 * Last update: 7.05.2003 by Blizzard
 * 24.6.2004 various fixes and cleaning by Milan
 *
 * Arman 02/2022
 * Added the bow as a spell enhancer.
 */

#pragma strict_types

inherit "/lib/keep";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit WEP+"elven_bow";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

int     singing_bow(object ob);
int     start_singing(object ob);
int     sing_it(object ob);

#define BOW_I_SING       "_bow_i_sing"
#define BOW_I_HUM        "_bow_i_hum"
#define TO_HIT           44
#define TO_PEN           42
#define SPELLPOWER       43
#define BONUS_SKILL      10

int     add_skill1, add_skill2; 
int     rem_skill1, rem_skill2; 
int     sing_alarm_id, hum_alarm_id, alarm1_id, alarm2_id, alarm3_id;

public void
create_bow()
{
    set_name("bow");
    add_name(({ "_singing_bow_", "longbow" }));
    set_adj( ({ "long", "composite", "elven" }) );
    set_short("long composite bow"); 
    set_pshort("long composite bows");
    set_long("This composite longbow is more a work of art than a weapon of " +
        "war; fine engravings dance over the polished wood, and the " +
        "bowstring gleams of gold, almost singing when drawn. This bow " +
        "was one of many made by an elven craftsman whose name has been " +
        "lost to history. At one time there were several hundred in use, " +
        "a favourite of scouts who patrolled Qualinesti, but many " +
        "have been lost or destroyed. Only a few are still known to exist, " +
        "and they see little use due to the tremendous strength they " +
        "require. However, this makes the weapon very dangerous and arrows " +
        "fired from it deliver more damage.\n");
    add_item( ({ "engravings", "staff", "wood" }),
        "The polished staff of the bow is decorated with strange engravings, " +
        "such as elves usually place on ceremonial items.\n");
       
    add_prop(OBJ_S_WIZINFO,
        "This is one of few singing elven logbows that still exist. If it " +
        "is wielded by an elf it begins, first to hum silently, then to " +
        "intone a song, that makes wielder move faster (adds quickness " +
        "of 50). It also increases the wielder's MISSILE skill by max value " +
        "of 10 and even 20 if he is an elf. To wield this longbow a player " +
        "needs strength and dexterity. Also if the wielder is skilled " +
        "enough in using bows the to_hit and to_pen values are increased by " +
        "5 (the humming longbow), and by another 5 if he is an elf (the " +
        "singing longbow). There is a drawback: the player's defence " +
        "decreases by the value equal to the gained MISSILE skill.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 90, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO,
        ({"Only strong and agile people are able to use this weapon " +
        "properly.\n", 5,
        "The bow is of elven making and thus beautiful yet deadly weapon. " +
        "If you are strong, agile and skilled enough you will have no " +
        "problems with using it.\n", 10,
        "In hands of a skilled user the bow is more deadly.\n", 20,
        "The full powers of this longbow are known only to elves.\n", 40,
        "The bow increases the wielder's ability to use such weapons and " +
        "if he is an elf, it also speeds his moves. However, being under " +
        "influence of its music the player's ability to defend himself "+
        "decreases.\n", 60 }) );

    set_keep(1);
    set_wf(TO);
    set_likely_dull(1);
    set_likely_break(1);
  
    add_prop(OBJ_M_NO_BUY, "Such priceless items are not for sale!\n");
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 20000);

    set_hit(TO_HIT);
    set_pen(TO_PEN);
    set_magic_spellpower(SPELLPOWER);

    seteuid(getuid(TO));
}

void 
hum_msg()
{
    if ( objectp(wielder) )
    {   
        switch (random(8))
        {
        case 0:
            wielder->catch_tell("Your " + TO->short() + " produces a " +
                "low vibrating noise. From one side it is annoying, " +
                "but from the " +
                "other, it makes you tighten your grip on the weapon.\n");
            tell_room(E(wielder), QCTNAME(wielder) + " tightens " + 
                POSSESSIVE(wielder) + " grip on the " + TO->short() + 
                ".\n", wielder);
        break;
        case 1..3:
            wielder->catch_tell("Your " + TO->short() + " produces " +
                "a strange vibrating noise.\n");
            tell_room(E(wielder), "The " + TO->short() + " wielded by " +
                QTNAME(wielder) + " produces a strange vibrating sound.\n",
                wielder);
        break;
        case 4:
            wielder->catch_tell("The low sound coming from your " +
                TO->short() + " is quite annoying, but you have " +
                "a feeling it also helps you somehow.\n");
        break;
        }
        
        hum_alarm_id = set_alarm(80.0, 0.0, hum_msg);
    }
}    
    
void
song_msg()
{
    if ( objectp(wielder) )
    {   
        if ( random(2) )
        {
            wielder->catch_tell("The sweet tones emited by your " + short() + 
                " flow over you.\n");
            tell_room(E(wielder), "The sweet silent tones are coming from " +
                "the nearby.\n", wielder);
            sing_alarm_id = set_alarm(80.0, 0.0, song_msg);
        }
    } 
}
  
int
start_singing(object ob)
{
    if (E(TO) != TO->query_wielded() || query_prop(BOW_I_SING))
        return 0;
    
    ob->catch_msg("\nAs the humming sound coming from within the " + 
        TO->short() + " becomes more intense, you barely stop yourself from " +
        "unwielding it.\n\n");
    tell_room(E(ob), "The humming sound coming from within the " + 
        TO->short() + " wielded by " + QTNAME(ob) + " becomes more " +
        "intense.\n", ob);
    
    if (E(TO) == ob)
        alarm1_id = set_alarm(4.0, 0.0, &singing_bow(ob));
    
    return 1;
}

int
singing_bow(object ob)
{
    if (E(TO) != TO->query_wielded() || query_prop(BOW_I_SING))
        return 0;
    
    ob->catch_msg("\nSuddenly the sound changes. Now you hear a beautiful " +
        "voice singing an elven song. There is something ... something " +
        "almost hypnotic in it.\n\n");

    remove_prop(BOW_I_HUM);
    set_short("singing elven longbow");
    remove_adj("humming");
    add_adj("singing");
            
    if (query_wielded() == ob)
        alarm2_id = set_alarm(3.0, 0.0, &sing_it(ob));
            
    return 1;
}
        
int
sing_it(object ob)
{
    if (E(TO) != TO->query_wielded())
        return 0;
    
    if (!query_prop(BOW_I_SING))
    {
        ob->catch_msg("\nYou calm down as the sweet tones fill your " +
            "ears. Your moves become swift and full of grace.\n");
        tell_room(E(TO), QCTNAME(ob) + " calms down and " + POSSESSIVE(ob) + 
            " moves become swift, and full of grace.\n", ob);

    /* The song boosts us, increasing quickness and skill */
        ob->add_prop(LIVE_I_QUICKNESS, ob->query_prop(LIVE_I_QUICKNESS) + 50);
        ob->query_combat_object()->cb_update_speed();
        
  // Player gains another 10 (max) to missile skill but loses the same amount
  // in defence.      
        if ( (TP->query_skill(SS_WEP_MISSILE) + BONUS_SKILL) > 100 )
            add_skill2 = (100 - TP->query_skill(SS_WEP_MISSILE));
        else
            add_skill2 = BONUS_SKILL;

        TP->set_skill_extra(SS_WEP_MISSILE, 
            TP->query_skill_extra(SS_WEP_MISSILE) + add_skill2);

  // Check if we do not get negative skill.      
        if ( TP->query_skill(SS_DEFENCE) < add_skill2 )
            rem_skill2 = TP->query_skill(SS_DEFENCE);
        else
            rem_skill2 = add_skill2;
            
        TP->set_skill_extra(SS_DEFENCE,
            TP->query_skill_extra(SS_DEFENCE) - rem_skill2);

        set_hit(TO_HIT + 10);
        set_pen(TO_PEN + 10);
        set_magic_spellpower(SPELLPOWER + 10);
        ob->update_weapon(TO);
        add_prop(BOW_I_SING, 1);
        sing_alarm_id = set_alarm(30.0, 0.0, song_msg);
        
        return 1;
    }
        
}

mixed 
wield(object ob)
{
 //   int stat_check = TP->query_stat(SS_STR) + TP->query_stat(SS_DEX);
    
    if ( (TP->resolve_task(900, ({TS_STR, TS_DEX })) < 0) &&
        !TP->query_npc() )
    {
        say(QCTNAME(TP) + " wields the " + ob->short() + " and struggles " +
            "in a vain attempt to test it. Cursing silently, " +
            HE(TP) + " releases the grip on this beautiful weapon.\n");
        return "You wield the " + ob->short() + " and struggle for a " +
            "moment in a vain attempt to test it. You curse silently and " +
            "release the grip on this beautiful weapon.\n";
    }
             
    if ( TP->query_skill(SS_WEP_MISSILE) > 29 )
    {
        if ( !interactive(TP) )
            set_secondary_wep_cmd("elf_wield_sec_weapon");
            
        write("As you grasp the staff of the " + ob->short() + ", it begins " +
            "to hum silently.\n");
        say("As " + QTNAME(TP) + " grasps the staff of the " + ob->short() +
            ", it begins to hum silently.\n");
        
        set_short("humming long bow");
        add_adj("humming");
        add_prop(BOW_I_HUM, 1);
        set_hit(TO_HIT + 5);
        set_pen(TO_HIT + 5);
        set_magic_spellpower(SPELLPOWER + 5);
        wielder->update_weapon(TO);      
        
  // Player gains max. 10 to missile skill but loses the same in defence.
        if ( (TP->query_skill(SS_WEP_MISSILE) + BONUS_SKILL) > 100 )
            add_skill1 = (100 - TP->query_skill(SS_WEP_MISSILE));
        else
            add_skill1 = BONUS_SKILL;
                    
        TP->set_skill_extra(SS_WEP_MISSILE, 
            TP->query_skill_extra(SS_WEP_MISSILE) + add_skill1);

  // Check if we do not get negative skill.      
        if ( TP->query_skill(SS_DEFENCE) < add_skill1 )
            rem_skill1 = TP->query_skill(SS_DEFENCE);
        else
            rem_skill1 = add_skill1;

        TP->set_skill_extra(SS_DEFENCE,
            TP->query_skill_extra(SS_DEFENCE) - rem_skill1);
            
        if ( (TP->query_race_name() == "elf" || 
            TP->query_race_name() == "half-elf") && !query_prop(BOW_I_SING))
        {     
            wielder = TP;
            alarm3_id = set_alarm(6.0, 0.0, &start_singing(wielder));
            return 1;
        }
        
        hum_alarm_id = set_alarm(30.0, 0.0, hum_msg);
        return 1;
    }
    
    return 0;
}        

public void
check_active_alarms()
{
    if ( hum_alarm_id )
        remove_alarm(hum_alarm_id);
    if ( sing_alarm_id )
        remove_alarm(sing_alarm_id);
    if ( alarm1_id )
        remove_alarm(alarm1_id);
    if ( alarm2_id )
        remove_alarm(alarm2_id);
    if ( alarm3_id )
        remove_alarm(alarm3_id);
}
        
mixed
unwield(object what)
{
    set_this_player(query_wielded());
   
    check_active_alarms();
    
    if ( query_prop(BOW_I_SING) )
    {
        wielder->catch_msg("You release the grip on your " + what->short() +
            " and its song dies away.\n");
        tell_room(E(wielder), QCTNAME(wielder) + " releases the grip on " +
            POSSESSIVE(wielder) + " " + what->short() + 
            " and its song dies away.\n", wielder);
    
 /* remove the bonuses and set normal short description */
        set_short("long composite bow");
        remove_adj("singing");
        TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - 50);
        TP->query_combat_object()->cb_update_speed();

        TP->set_skill_extra(SS_WEP_MISSILE, 
            TP->query_skill_extra(SS_WEP_MISSILE) - (add_skill1 + add_skill2));
        TP->set_skill_extra(SS_DEFENCE,
            TP->query_skill_extra(SS_DEFENCE) + (rem_skill1 + rem_skill2));

        remove_prop(BOW_I_SING);
        set_hit(TO_HIT);
        set_pen(TO_PEN);
        set_magic_spellpower(SPELLPOWER);
        wielder->update_weapon(TO);
    
        return 1;
    }
    
    if ( query_prop(BOW_I_HUM) )
    {
        wielder->catch_msg("You release the grip on your " + what->short() +
            " and its humming sound dies away.\n");
        tell_room(E(wielder), QCTNAME(wielder) + " releases the grip on " +
            POSSESSIVE(wielder) + " " + what->short() + 
            " and the humming sound dies away.\n", wielder);

        TP->set_skill_extra(SS_WEP_MISSILE, 
            TP->query_skill_extra(SS_WEP_MISSILE) - add_skill1);
        TP->set_skill_extra(SS_DEFENCE,
            TP->query_skill_extra(SS_DEFENCE) + rem_skill1);

        set_short("long composite bow");
        remove_adj("humming");
        remove_prop(BOW_I_HUM);
        set_hit(TO_HIT);
        set_pen(TO_PEN);
        set_magic_spellpower(SPELLPOWER);
        E(TO)->update_weapon(TO);
        
        return 1;
    }
    
    return 0;
}       

/* 
 * Function name: did_parry 
 * Description:   Called when this weapon was used to parry an attack. It can 
 *                be used to wear down a weapon. Note that his method is called 
 *                before the combat messages are printed out. 
 * Arguments:     att:   Attacker 
 *                aid:   The attack id 
 *                dt:    The damagetype 
 */
public varargs void
did_parry(object att, int aid, int dt)
{    
    if (stringed && !random(F_BOWSTRING_SNAP_CHANCE))    
    {        
        tell_object(query_wielded(), "The bowstring of your " + 
			short(query_wielded()) + " whistles sharply.\n");    
    }
}

int
set_dull(int du)
{
    return 0;
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