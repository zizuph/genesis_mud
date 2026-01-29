/*
Pax Tharkas, Nightbringer, Lord Verminaards mace. 

nightbringer.c
--------------

Coded ........: 95/02/09
By ...........: Jeremiah

Latest update : 2003/06/19
By ...........: Blizzard
INFO: Changed the weapon's stats and allowed all players to wield it,
but they will get blinded upon wielding ( for 3-5 minutes ).
However, if the mace is wielded by evil aligned player (align < -500)
its hit will increase by 5. If wielded by player with align > -1100,
there is 33% chances that his align will go down by a small amount.
Also if the player's alignment is higher than 100, the mace will
hurt him when the power word is spoken.

OLD:
When the wielder of this weapon says 'midnight' s/he calls upon the  
powers of the dark queen(Takhisis), and blinds his/her opponent. The 
wielder must be evilaligned, and the use of the special ability will 
cost the wielder mana. 


Navarre Jan 15th 2008.
Added extra checks to unwield function to avoid runtime.

Arman December 2021.
Added nightbringer as a spell enhancer for clerical guilds.

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <options.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#define NIGHTBRINGER_SUBLOC "nightbringer_subloc"
#define FLAMING_MACE        "_flaming_mace"
#define TO_HIT              45
#define TO_PEN              40

object wielder;
string *modified = ({ });
int    attempt_to_blind, gag_int, alarm1_id, alarm2_id;
string long_desc();

create_weapon()
{
    set_name("nightbringer");
    add_name("mace");
    set_short("black spiked mace");
    set_adj(({ "black", "spiked" }));
    set_long("@@long_desc");

    set_default_weapon(TO_HIT, TO_PEN, W_CLUB, W_BLUDGEON, W_ANYH);
    set_magic_spellpower(35); // default 35, 50 for cleric style classes.

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_ALIGN, -600);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"The spiked mace seems to be magical.\n",1,
	"The mace draws it powers from the dark queen, Takhisis, " +
	"herself and enhances the power of prayers.\n", 25, 
        "It will lower the wielder's alignment.\n", 40,
	"It has the ability to blind the opponent " +
	"of its wielder when it hits, and the right word of command " +
	"is uttered.\n",55, "Only those who are pure evil will be " +
	"granted the full powers of this weapon.\n", 70 }));
    add_prop(OBJ_S_WIZINFO, "This mace was created by evil clerics and " +
        "blessed by Takhisis. When wielded by evil player the to_hit " +
        "value increases by 5. If the wielder is less evil or even good " +
        "there is a 33% chance that his alignment will drop with each " +
        "hit by a small amount. When the good aligned player uses " +
        "the power word, the weapon will hurt him. Such people will " +
        "also get blinded upon wielding the mace (for 3-5 minutes). " +
        "Also upon wielding, the alignment of good players will drop " +
        "by 200. The mace remembers who had his alignment changed and " +
        "will not do it again, though. This mace has a base hit/pen of " +
        "45/40 and spellpower of between 35 or 50 (later for " +
        "cleric-style classes).\n");

    add_prop(OBJ_M_NO_DROP, "@@attempt_to_drop");   
    add_prop(OBJ_M_NO_GIVE, "@@attempt_to_give");

    set_likely_dull(2);
    set_likely_break(2);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50, 50) + random(500));

    set_wf(TO);
    set_keep(1);

    seteuid(getuid(TO));
}

void
init()
{
    ::init();
    add_action("my_say", "say");
    add_action("my_say", "shout");
}

string 
long_desc()
{
   if ( !query_prop(FLAMING_MACE) )
   {
      return "This is a three feet long and narrow footman's mace. The " +
          "deep black shaft ends in a terrible spiked head. The " +
          "head is glowing, like some unearthly gemstone, in a dark " +
          "colour beyond black itself.\n";
   }
   else if ( query_prop(FLAMING_MACE) )
   {
      return "This is a three feet long and narrow footman's mace. The " +
          "deep black shaft ends in a terrible spiked head. The " +
          "weapon seems to be burning with a dark purple fire, " +
          "that reaches up to your forearm.\n";
   }

}


int
attempt_to_drop()
{
    if((E(TO)->id("verminaard")) && (E(TO)->query_hp() > 0))
    {
	tell_room(E(wielder), "The mace stays firmly in the hand of " +
	  QCTNAME(wielder) + ".\n", wielder);
	return 1;
    }

    return 0;  /* Has to be removed later .. trying to solve the */
    /* drop/Ranger brawl(Vampyr fang) problem.   Jer. */

    if(E(TO)->query_mana() < 400)
    {
	write("No! .. You don't want to drop the " + short() + ".\n");
	return 1;
    }   

    return 0;
}


int
attempt_to_give()
{
    return 0;  /* Has to be removed later .. trying to solve the */
    /* drop/Ranger brawl(Vampyr fang) problem.   Jer. */

    if(E(TO)->query_mana() < 400)
    {
	write("No! .. You don't really want to give the " + short() +
	  " away.\n");
	return 1;
    }

    return 0;
}      


void
reset_power_word()
{
    attempt_to_blind = 1;
}

void
get_ready_to_blind()
{
    if (wielder->query_mana() <= 150)
    {
	wielder->catch_msg("A female voice tells you: You are " +
	  "mentally too weak to call upon my powers!\n");
	return;
    }

    if ( attempt_to_blind == 1 )
    {
        wielder->catch_msg("You have just chanted the power word. You " +
            "have to wait a bit, before you can try it again.\n");
        return;
    }
    
    wielder->add_mana(-100);
    wielder->catch_msg("You feel mentally drained as you call " +
        "the powers of the " + short() + "!\n");
        
    attempt_to_blind = 1;
}


int
my_say(string what)
{
    if (!wielder)
	return 0;

    if (wielder != TP)
	return 0;

    if (!wielder->query_attack())
	return 0;

    if (what != "midnight" && what != "Midnight")
	return 0;

    set_alarm(1.0, 0.0, &get_ready_to_blind());

    return 0;
}


void
wield_message1()
{
    object blinding;
    
    write("A dark fire courses up around your clutching hand. The fire " +
      "races up your wrist and forearm in rivulets of purple " +
      "flames.\n");

    say("A dark fire courses up around " + QCTPNAME(TP) + " clutching " +
      "hand. The fire races up " + POSSESSIVE(TP) + " wrist and forearm " +
      "in rivulets of purple flames.\n");
 
    if ( TP->query_alignment() > 100 )
    {
        if( !present("Nightbringer_Blind_Object", query_wielded()) )
        {
            wielder->catch_msg("Suddenly, the " + short() + " flashes " +
                "with a dim light and your eyes are covered with mist.\n"); 
            say("The " + short() + ", wielded by " + QTNAME(wielder) +
                ", flashes with a dim light.\n");
        
	    blinding = clone_object(POBJ + "night_ob");
	    blinding->set_time(180 + random(120));
	    blinding->move(query_wielded(), 1);
        }
    }

    if ( !query_prop(FLAMING_MACE) )
    {
        set_short("flaming spiked mace");
        add_adj("flaming");
        add_prop(FLAMING_MACE, 1);
    }

}


void
wield_message2()
{
    int     align, i, sz;
    string  name;
     
    align = query_wielded()->query_alignment();
    name  = query_wielded()->query_real_name();
    
    if ( query_wielded()->query_guild_member("Priests of Takhisis") )
    {
        write("A seductive female voice whispers to you 'Ahh, " +
            query_wielded()->query_name() + ", my dear servant. I shall " +
            "grant you my powers once again.'.\n");
    }
    else
    { 
        write("A seductive female voice tells you 'You belong to me now! " +
            "All other bonds are broken. Bonds of family, blood, friendship " + 
            "or oath. All of your bonds, save for those with me.'.\n"); 
    }
    
    /* We will remember who had his alignment lowered once,
       and it will not happen second time. */
    if ( align > 0 )
    {
        for ( i = 0, sz = sizeof(modified); i < sz; i++)
        {
            if ( modified[i] == name )
            {
                return;
            }
        }
        
        query_wielded()->set_alignment(align - 200);
        query_wielded()->change_prestige(align, 1);
        modified += ({ name }) ;
    }
    
}

void
decide_spellpen()
{
    int spellpen;
    object who = query_wielded();

    if (!objectp(who))
	return;

    if(who->query_guild_style_lay() == "cleric" ||
        who->query_guild_style_occ() == "cleric")
    {
        if(who->query_alignment() > 0)
            who->catch_tell("You feel the " + short() + " seems " +
                "to enhance your spell abilities in an attempt to " +
                "seduce you with the power of the Dark Queen.\n");
        else
            who->catch_tell("The " + short() + " seems to respond " +
                "to your malevolent faith, enhancing your spell " +
                "abilities.\n");

        spellpen = 50;
    }
    else 
    {
        spellpen = 35;
    }

    set_magic_spellpower(spellpen);
    who->update_weapon(this_object());
}

mixed 
wield(object what)
{
    wielder = TP;
    if( TP->query_alignment() < -500 )
    {
        set_hit(TO_HIT + 5);
        wielder->update_weapon(TO);
    }    

    alarm1_id = set_alarm(1.0, 0.0, &wield_message1());
    alarm2_id = set_alarm(5.0, 0.0, &wield_message2()); 

    set_alarm(6.0, 0.0, &decide_spellpen());

    wielder->add_subloc(NIGHTBRINGER_SUBLOC, TO);
    
    return 0;
}

public void
check_active_alarms()
{
    if ( alarm1_id )
    {
        remove_alarm(alarm1_id);
        alarm1_id = 0;
    }
    if ( alarm2_id )
    {
        remove_alarm(alarm2_id);
        alarm2_id = 0;
    }
}

mixed
unwield(object what)
{
    if((E(TO)->id("verminaard")) && (E(TO)->query_hp() > 0))
    {
        if(objectp(wielder))
        {
            tell_room(E(wielder), "The mace stays firmly in the hand of " +
                      QCTNAME(wielder) + ".\n", wielder);
        }
        return "No!";
    }
    if(objectp(wielder))
    {
        wielder->remove_subloc(NIGHTBRINGER_SUBLOC);
        wielder->catch_msg("The dark purple fire around your forearm slowly " + 
                           "dies out.\n");
        say("The dark purple fire around " + QCTPNAME(wielder) + " forearm " + 
            "slowly dies out.\n");
    }
    
    check_active_alarms();
    
    if ( query_prop(FLAMING_MACE) )
    {
        remove_adj("flaming");
        set_short("black spiked mace");
        remove_prop(FLAMING_MACE);
    }
    
    set_hit(TO_HIT);
    set_magic_spellpower(35);
    query_wielded()->update_weapon();
    wielder = 0;
    return 0;
}


string
where_is_mace()
{
    if(wielder->query_weapon(W_RIGHT) == TO)
	return "right";

    else
	return "left";
}


string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if(for_obj == carrier)
	str = "You have a strange dark purple fire raging around your " + 
	where_is_mace() + " forearm.\n";            

    else
	str = C(PRONOUN(carrier)) + " has a strange dark purple fire raging " +
	"around " + POSSESSIVE(carrier) + " " + where_is_mace() + 
	" forearm.\n";

    return str;
}


/*
* Function name: tell_watcher
* Description:   Send the string from the fight to people that want them
* Arguments:     The string to send
*/

static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->query_option(OPT_BLOOD) == 0 ||
	  !gag_int || (gag_int && !ob[i]->query_option(OPT_GAG_MISSES)))
	    ob[i]->catch_msg(str);
}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object blinding;
    int    align, align_dam;
    
    align = wielder->query_alignment();
        
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    gag_int = 0;

    switch(phurt)
    {
    case -1:
    case -2:
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("A dark shadow trails the head of the " + 
	      short() + " as you swing it harmlessly through the air.\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg("A dark shadow trails the head of the " +
	      short() + " as " + QTNAME(wielder) + " swings it uncomfortably " +
	      "close to you.\n");
	tell_watcher("A dark shadow trails the head of the " + short() +
	  " as " + QTNAME(wielder) + " swings it at " + QTNAME(enemy) +
	  " but misses.\n", enemy);
	gag_int = 1;
	break;

    case 0:
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("You swing the " + short() + " very close to " +
	      QTNAME(enemy) + ", only narrowly missing your victim.\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg(QCTNAME(wielder) + " swings the " + short() + 
	      " very close to you, only narrowly missing you.\n");
	tell_watcher(QCTNAME(wielder) + " swings the " + short() +
	  " at " + QTNAME(enemy) + " and narrowly misses.\n", enemy);
	gag_int = 1;
	break;

    case 1..4:
	wielder->catch_msg("You scratch the " + hdesc + " of " +
	  QTNAME(enemy) + " with your " + short() + ". The spikes " +
	  "leaving tiny trails of blood on " + POSSESSIVE(enemy) + 
	  " skin.\n");
	enemy->catch_msg(QCTNAME(wielder) + " scratches your " + hdesc +
	  " with the " + short() + ". The spikes leaving tiny trails " +
	  "of blood on your skin.\n");
	tell_watcher(QCTNAME(wielder) + " scratches the " + hdesc + " of " +
	  QTNAME(enemy) + " with the " + short() + ". The spikes " +
	  "leaving tiny trails of blood on " + POSSESSIVE(enemy) +  
	  " skin.\n", enemy);
	break;

    case 5..9:
	wielder->catch_msg("You graze the " + hdesc + " of " +
	  QTNAME(enemy) + " with your " + short() + ". The spikes " +
	  "drawing shallow wounds in " + POSSESSIVE(enemy) + 
	  " skin.\n");
	enemy->catch_msg(QCTNAME(wielder) + " grazes your " + hdesc +
	  " with the " + short() + ". The spikes drawing shallow wounds " +
	  "in your skin.\n");
	tell_watcher(QCTNAME(wielder) + " grazes the " + hdesc + " of " +
	  QTNAME(enemy) + " with the " + short() + ". The spikes " +
	  "drawing shallow wounds in " + POSSESSIVE(enemy) +
	  " skin.\n", enemy);
	break;

    case 10..19:
	wielder->catch_msg("You graze the " + hdesc + " of " +
	  QTNAME(enemy) + " with your " + short() + ". The spikes " +
	  "ripping shallow wounds in " + POSSESSIVE(enemy) + 
	  " skin.\n");
	enemy->catch_msg(QCTNAME(wielder) + " grazes your " + hdesc +
	  " with the " + short() + ". The spikes ripping shallow " +
	  "wounds in your skin.\n");
	tell_watcher(QCTNAME(wielder) + " grazes the " + hdesc + " of " +
	  QTNAME(enemy) + " with the " + short() + ". The spikes " +
	  "ripping shallow wounds in " + POSSESSIVE(enemy) +
	  " skin.\n", enemy);
	break;

    case 20..29:
	wielder->catch_msg("You hurt the " + hdesc + " of " +
	  QTNAME(enemy) + " with your " + short() + ". The spikes " +
	  "tearing deep wounds in " + POSSESSIVE(enemy) + 
	  " flesh.\n");
	enemy->catch_msg(QCTNAME(wielder) + " hurts your " + hdesc +
	  " with the " + short() + ". The spikes tearing deep " +
	  "wounds in your flesh.\n");
	tell_watcher(QCTNAME(wielder) + " hurts the " + hdesc + " of " +
	  QTNAME(enemy) + " with the " + short() + ". The spikes " +
	  "tearing deep wounds in " + POSSESSIVE(enemy) +
	  " flesh.\n", enemy);
	break;

    case 30..49:
	wielder->catch_msg("You tear deep wounds in the " + hdesc + " of " +
	  QTNAME(enemy) + " with your " + short() + ". Blood spatters " +
	  "all over, as the spikes shred " + POSSESSIVE(enemy) + 
	  " flesh.\n");
	enemy->catch_msg(QCTNAME(wielder) + " tears deep wounds in your " +
	  hdesc + " with the " + short() + ". Blood spatters all over, " + 
	  "as the spikes shred your flesh.\n");
	tell_watcher(QCTNAME(wielder) + " tears deep wounds in the " + 
	  hdesc + " of " + QTNAME(enemy) + " with the " + short() + 
	  ". Blood spatters all over, as the spikes shred " + 
	  POSSESSIVE(enemy) + " flesh.\n", enemy);
	break;

    case 50..69:
	wielder->catch_msg("You hammer your " + short() + " into the " + 
	  hdesc + " of " + QTNAME(enemy) + ". The spikes pierces deep " +
	  "into " + POSSESSIVE(enemy) + " flesh. Blood pours from the " +
	  "gaping wounds left by the spikes.\n");
	enemy->catch_msg(QCTNAME(wielder) + " hammers the " + short() +
	  " into your " + hdesc + ". The spikes pierces deep into " +
	  "your flesh. Blood pours from the gaping wounds left by " +
	  "spikes.\n");
	tell_watcher(QCTNAME(wielder) + " hammers the " + short() +
	  " into the " + hdesc + " of " + QTNAME(enemy) + ". The " + 
	  "spikes pierces deep into " + POSSESSIVE(enemy) + " flesh. " +
	  "Blood pours from the gaping wounds left by the " +
	  "spikes.\n", enemy);
	break;

    case 70..89:
	wielder->catch_msg("You smash the " + short() + " into the " +
	  hdesc + " of " + QTNAME(enemy) + ". The spikes pierces deep " +
	  "into " + POSSESSIVE(enemy) + " flesh. You hear the sound of " +
	  "bones breaking as your mace hits. Blood spurts from the " +
	  "gaping wounds left by the spikes.\n");
	enemy->catch_msg(QCTNAME(wielder) + " smashes the " + short() +
	  " into your " + hdesc + ". The spikes pierces deep into " +
	  "your flesh. You feel the pain as you bones break from the " +
	  "hit. Blood pours from the gaping wounds left by " +
	  "spikes.\n");
	tell_watcher(QCTNAME(wielder) + " hammers the " + short() +
	  " into the " + hdesc + " of " + QTNAME(enemy) + ". The " +
	  "spikes pierces deep into " + POSSESSIVE(enemy) + " flesh. " +
	  "You hear the sound of bones breaking at the " + short() +
	  "hits. Blood pours from the gaping wounds left by the " +
	  "spikes.\n", enemy);
	break;

    default:
	wielder->catch_msg("You hear the sickening sound of bones " +
	  "breaking, as your " + short() + " massacres the " + hdesc + 
	  " of " + QTNAME(enemy) + ". The spikes penetrate deep " +
	  "into " + POSSESSIVE(enemy) + " flesh, leaving blood " +
	  "flowing from deep gaping wounds in the shattered limb.\n");
	enemy->catch_msg("You hear the sickening sound of your bones " +
	  "breaking as " + QTNAME(wielder) + " massacres your " + 
	  hdesc + " with " + POSSESSIVE(wielder) + " " + short() + 
	  " The spikes penetrate deep into your flesh, leaving blood " +
	  "flowing from deep gaping wounds in the shattered limb.\n");
	tell_watcher("You hear the sickening sound of bones breaking " +
	  "as " + QTNAME(wielder) + " massacres the " + hdesc +
	  " of " + QTNAME(enemy) + " with " + POSSESSIVE(wielder) + 
	  " " + short() + ". The spikes penetrate deep into the " +
	  "flesh of " + QTNAME(enemy) + ", leaving blood flowing " +
	  "from the shattered limb.\n", enemy);
	break;

    }

    if ( (dam > 10) && !random(3) )
    {
        if ( align > -1100 )
        {
            wielder->set_alignment(align - 4);
            wielder->change_prestige(10, 1);
        }
    }
        
    if ( attempt_to_blind )
    {
	attempt_to_blind = 0;

	if (phurt > 0)
	{
	    if(!present("Nightbringer_Blind_Object", enemy))
	    {
                if ( align > 100 )
                {
                    align_dam = ((wielder->query_hp()) / 100 ) * (align / 100); 
                    wielder->heal_hp(-align_dam);
                    wielder->catch_msg("You feel sharp pain, as you " +
                        "call the evil powers of the " + short() + ".\n");

                    if ( wielder->query_hp() <= 0 )
                    {
                        wielder->do_die(TO);
                        return 1;
                    }
                
                }
                
		wielder->catch_msg(QCTNAME(enemy) + " staggers. " +
		  C(POSSESSIVE(enemy)) + " eyes roll white. Blinded !!\n");
		enemy->catch_msg("Suddenly everything turns pitch dark. " +
		  "You cannot see !!.\n");
		tell_watcher(QCTNAME(enemy) + " staggers. " + 
		  C(POSSESSIVE(enemy)) + " eyes roll white.\n", enemy);    
		blinding = clone_object(POBJ + "night_ob");
		blinding->set_time(60 + random(30));
		blinding->move(enemy);
	    }
	    else
	    {
	        wielder->catch_msg("Nothing seem to happen, as the flaming " +
	            "spikes connect with " + QTNAME(enemy) + ". You realize " + 
	            "that " + HE(enemy) + " has been blinded already.\n");
	    }
	}
    }
    return 1;
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