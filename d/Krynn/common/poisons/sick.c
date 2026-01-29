/* -*-C++-*- */
/* A sickness, based on the poison-standard, which is passed from one
 * to the next by speaking, coughing, etc.
 * Originator of the sickness is a Cleric of Morgion, the God of disease
 * in Krynn. /d/Krynn/common/npcs/wand_cl_morgion.c
 * 
 * The sickness is supposed to work like 'real', with the ability that
 * people will become immune to it after being sick once (in some cases
 * more than once).
 *
 * Created by ~Aridor 02/97, with input from Teth, Arman and others.
 * Rewritten into one object and interactive transmission by Igneous.
 * Various fixes by all of the above mentioned people.
 *
 *
 * Fixed a minor bug with the interactive transfer of the sickness when
 * no string was supplied when a player whispered or asked.
 * Igneous April 8th 1997
 *
 * Minor modification to change the time of becoming resistant to the
 * sickness to AFTER someone has waited out the full duration. Cleansing
 * (hopefully) or other ways to remove the sickness prematurely will
 * not give any resistance to the player anymore.
 * ~Aridor 09/97
 *
 * Reduced the length of the sickness to between 30 and 60 minutes.
 * Made the sickness to mutate before spreading, these parameters are
 * mutated: interval, duration, damage_mana, damage_hp, damage_fatigue.
 * ~Aridor 01/98
 * 
 * Added a mutation of the contagiousness of the sickness. It might be
 * possible that the sickness develops in a way that not only weakened
 * people (less than max health or fatigue) are infected, but anyone
 * regardless of fitness. This can only happen after at least two(!)
 * mutations, but once it happens it will allow a real 'plaque' again.
 * (It was kind of sad that none appeared again ever since the old times :)
 * Raised the carrying time of the sickness for immune people.
 * ~Aridor 03/99
 *
 * Changed the setup of the sickness so the resistance bits are more
 * meaningful. Another reason is also that the sickness is carried
 * a bit too much currently, infecting more and more people. I'd
 * rather have it so that it pops up occasionally, but very violently,
 * and then (after most active players at the time have become immune)
 * fades back into nothing.
 * ~Aridor 05/99
 *
 * Removed the part where the player has to be tired of hurt to get it.
 * This was done because no one ever got the sickness anymore.
 * At the same time I added a chance for people who is immune to get it
 * again. This models that the sickness can mutate so much that the
 * immune system in the body doesn't recognize it.
 * ~Navarre December 27th 2007.
 *
 * removed the first argument of clear_bit as it was causing runtime
 * errors.
 * ~Petros January 5th 2009.
 *
 * Navarre June 12th 2009, Changed Newbie size from 30 to 60, 
 *                         meaning that people below 60 stat avg wont
 *                         get the plague, it used to be 30.
 */

#include <poison_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

#define SICKNESS  "/d/Krynn/common/poisons/sick"

inherit "/std/poison_effect";

object sickperson;
int incubating = 0;
int poison_fatigue = 200;
int mutate_fatigue = random(200) + random(200) - 190;
int poison_hp = 100;
int mutate_hp = random(125) + random(125) - 95;
int poison_mana = 150;
int mutate_mana = random(60) + random(60) - 55;
int poison_duration = 1800 + random(1800);
int mutate_duration = random(300) + random(300) - 280;
int poison_interval = 80;
int mutate_interval = random(10) + random(10) - 12;
int contagious = 180;
int contagious_mutate = random(10) + random(10) - 8;
/* increase to >= 200 will cause an infection even if the victim is fully 
 * healed, a decrease will lower the chance 
 */

nomask static int do_spread(string str);
void catch_sickness(object who);

void
create_poison_effect()
{
    add_name("nasty_sickness");
    set_interval(80);
    set_time(1800 /*7000*/ + random(1800 /*4000*/ ));
    set_damage(({ POISON_FATIGUE, 200,
		    POISON_HP, 100,
		    POISON_MANA, 150,
		    POISON_STAT, SS_CON,
		    POISON_STAT, SS_DEX,
		    POISON_STAT, SS_DIS,
		    POISON_STAT, SS_STR,
		    POISON_USER_DEF, 500 }));
    set_strength(60);
    set_poison_type("sickness");
    set_silent(2);
    seteuid(getuid());
}

void
mutate_sickness(int fatigue, int hp, int mana,
		int duration, int interval)
{
    poison_fatigue = fatigue + mutate_fatigue;
    if (poison_fatigue <= 0)
      poison_fatigue = 1;

    poison_hp = hp + mutate_hp;
    if (poison_hp <= 0)
      poison_hp = 1;

    poison_mana = mana + mutate_mana;
    if (poison_mana <= 0)
      poison_mana = 1;

    poison_duration = duration + mutate_duration;
    if (poison_duration <= 200)
      poison_duration = 201;

    poison_interval = interval + mutate_interval;
    if (poison_interval <= 10)
      poison_interval = 11;

    contagious = contagious + contagious_mutate;
    if (contagious > 200)
      contagious = 200;

    set_interval(poison_interval);
    set_time(poison_duration);
    set_damage(({ POISON_FATIGUE, poison_fatigue,
		    POISON_HP, poison_hp,
		    POISON_MANA, poison_mana,
		    POISON_STAT, SS_CON,
		    POISON_STAT, SS_DEX,
		    POISON_STAT, SS_DIS,
		    POISON_STAT, SS_STR,
		    POISON_USER_DEF, 500 })); 
}

void
timeout()
{
    ::timeout();
    sickperson->set_bit(1,7);
}

void
remove_object()
{
    sickperson->add_prop("_live_i_was_sick",1);
    if (incubating == 1)
      TO->start_poison();
    ::remove_object();
}

void
start_poison()
{
    int chance;
    string rc;

    incubating = 0;
    if (!sickperson)
      sickperson = E(TO);
    if (!sickperson)
      return;

    /* Reduced chances only apply when the sickness is just starting.
     * If you log out and back in, the poison should always restart.
     */
    if (!recovery)
    {

	/* different chances for different races here:
	 * dwarves, elves&goblins, humans, hobbits&gnomes in that order,
	 * for those who were sick at least once before.
	 */
	if (sickperson->test_bit("Krynn",1,7))
	{
	    rc = QREALRACE(sickperson);
	    if (rc == "dwarf")
	      chance = 8; /* 8% to become totally immune 
			   * (otherwise won't be affected, but will be a carrier */
	    else if (rc == "goblin" || rc == "elf")
	      chance = 6; /* 6% */
	    else if (rc == "human")
	      chance = 5; /* 5% */
	    else if (rc == "hobbit" || rc == "gnome")
	      chance = 4; /* 4% */
	    else
	      chance = 5; /* 5% */
	    
	    /* Means the player got immune the last time */
	    if (random(100) < chance)
	      sickperson->set_bit(1,8);
	}
    }

    /* Undeads and npcs can't be sick, but will carry the sickness
     * and spread it for a while. People who are immune to the sickness,
     * won't get sick again, but will also spread it for a while.
     *
     * Players with bit 1,7 set will be a long time carrier, and have the 
     * chance to become sick again (1:50)
     * Players with bit 1,8 set will be a carrier for only a short time
     * since they are immune to the sickness and are able to overcome
     * a new infection very quickly.
     */
    if (sickperson->query_prop(LIVE_I_UNDEAD) || sickperson->query_npc() ||
	sickperson->test_bit("Krynn",1,8) || 
	(sickperson->test_bit("Krynn",1,7) && random(50) > 1))
    {
	/* need to start the removing alarm anyway */
	incubating = 2;
	a_time = set_alarm((sickperson->test_bit("Krynn",1,8) ? (0.5 + rnd()) : 6.0) * p_time,
			   0.0,timeout);
        if(!random(5))
        {
            // Since the sickness can mutate, we allow for the mutation to get so far that they
            // can get the sickness again.
            sickperson->clear_bit(1, 8);
        }
	return;
    }

    /* People who haven't had it yet, will get sick. */
    sickperson->catch_msg("You are starting to feel sick.\n");
    set_silent(2);
    ::start_poison();

    set_silent(0);
    sickperson->catch_msg("You feel the urge to vomit and can't resist.\n");
    sickperson->eat_food(-500);
    tell_room(E(sickperson),QCTNAME(sickperson) + " looks really sick and " +
	      "suddenly vomits.\n", sickperson);
}

void
incubate_sickness()
{
    sickperson = E(TO);
    add_prop(OBJ_M_NO_DROP, 1);
//    add_prop(OBJ_M_NO_DROP, no_drop);
    add_prop(OBJ_I_NO_GIVE, "Give what to whom?\n");
    set_alarm(rnd() * 500.0 + 200.0,0.0,start_poison);
    incubating = 1;
}

void
special_damage(int damage)
{
    if (!sickperson)
      sickperson = E(TO);

    if (!interactive(sickperson))
      return;

    if (sickperson && !random(3))
    {
	sickperson->catch_msg("You feel the urge to vomit and can't resist.\n");
	sickperson->eat_food(-(random(damage) + 1),0);
	sickperson->drink_alco(-(random(damage / 10) + 1),0);
	sickperson->drink_soft(-(random(damage) + 1),0);
	tell_room(E(sickperson),QCTNAME(sickperson) +
            " looks really sick and suddenly vomits.\n", sickperson);
    }
}

void
init()
{
    add_action(do_spread, "rsay");
    add_action(do_spread, "ask");
    add_action(do_spread, "whisper");
    add_action(do_spread, "say");
    add_action(do_spread, "'", 2);
    add_action(do_spread, "sneeze");
    add_action(do_spread, "cough");
}

nomask static int
do_spread(string str)
{
    string player_name, foo;  
    object *infect;
    int i, infectall = 1;

    if (!sickperson)
      sickperson = E(TO);
    
    if (!living(sickperson))
      return 0;
    
    //  The bug fix I mentioned -Igneous-
    if (!str)
    {
	if (query_verb() != "cough" || query_verb() != "sneeze")
	  return 0;
    }
    switch(query_verb())
    {
    case "ask":       
	if (parse_command(str, E(sickperson), "%l %s", infect, foo))
	  infect = NORMAL_ACCESS(infect, 0, 0) - ({sickperson});
	break;

    case "say":
    case "rsay":
    case "'": 
    case "whisper":
	if (wildmatch("to *",str))
	{
	    sscanf(str, "to %s %s", player_name, foo);
	    infect = FIND_STR_IN_OBJECT(player_name, E(sickperson));
	    infect = FILTER_LIVE(infect);  
	}
	else if (query_verb() == "whisper")
	{
	    sscanf(str, "%s %s", player_name, foo);
	    infect = FIND_STR_IN_OBJECT(player_name, E(sickperson));
	    infect = FILTER_LIVE(infect);  	 
	}
	else
	{
	    infectall = 0;
	    infect = FILTER_LIVE(all_inventory(E(sickperson))) - ({sickperson});
	}
    default:
	infectall = 0;
	infect = FILTER_LIVE(all_inventory(E(sickperson))) - ({sickperson});
	break;
    }

    if (!infect || !sizeof(infect))
      return 0;
    
    if (infectall)
    {
	for (i = 0; i < sizeof(infect); i++)
	  catch_sickness(infect[i]);
    }
    else
      catch_sickness(infect[random(sizeof(infect))]);
    
    return 0;
}

void
catch_sickness(object who)
{
    object ob;
    string nm;

    if (present("nasty_sickness",who))
      return;

    /* Newbies are exempt :) */
    if (who->query_average_stat() < 60)
      return;

    /* Wizards shouldn't get it. */
    if (who->query_wiz_level())
      return;

    /* People who had it once this reboot won't get it again. */
    if (who->query_prop("_live_i_was_sick"))
      return;

    /* only tired and/or hurt players will catch the sickness */
    //    if (((who->query_fatigue() * 100 / who->query_max_fatigue()) +
    //	 (who->query_hp() * 100 / who->query_max_hp())) > contagious)
    //      return;
    
    /* 2/3 rds of the time it won't get passed on. */
    if (random(3)) 
      return;

    setuid();
    seteuid(getuid());
    ob = clone_object(SICKNESS);
    ob->mutate_sickness(poison_fatigue, poison_hp, poison_mana,
			poison_duration, poison_interval);
    ob->move(who, 1);
    ob->incubate_sickness();

    if (!who->test_bit("Krynn",1,8))
    {
        //	find_living("teth")->catch_msg("INFECTED: " + who->query_name() + "\n");
        //	find_living("aridor")->catch_msg("INFECTED: " + who->query_name() + "\n");
	nm = sickperson->query_name();
	log_file("sickness",ctime(time())[4..15] + " " + who->query_name() + 
		 " by "  + (nm ? nm : "Cleric of Morgion") + "\n");
    }
}

public void
kill_player()
{
    log_file("sickness",ctime(time())[4..15] + " " + sickperson->query_name() +
	     " died from Sickness.\n");
    ::kill_player();
}

public int
query_incubation()
{
    return incubating;
}


/* We need to record the timeout time of the poison ourselves
 * because the standard poison will add some time whenever
 * the player quits. Due to the longlasting effect of this
 * sickness, it occurs frequently that the player will quit
 * out at least once before the time is up, and therefore
 * prolonging the effect. Since the timeout will then be
 * even later, the chance that another logout will occur
 * (thus prolonging the time even further) is increasing
 * until impossible timeout times are reached.
 */
string
query_poison_recover()
{
    float time_left = 0.0;
    mixed arr;

    if (a_time &&
	sizeof(arr = get_alarm(a_time)))
    {
	time_left = arr[2];
    }

    return "" + ftoi(time_left);
}

/* Just overwrite the p_time with our own value here.
 * This is after the standard recovery routine has
 * already filled the variable.
 */
void
init_poison_recover(string arg)
{
    sscanf(arg, "%f", p_time);

    /* This check makes sure that 'overtimed' sickness
     * objects will be removed immediately.
     */
    if (p_time > 500000.0)
      set_alarm(5.0,0.0,timeout);
}

