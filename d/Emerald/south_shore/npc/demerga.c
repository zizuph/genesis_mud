/*  /d/Emerald/room/south_shore/npc/serpent.c
 *
 *  Demerga, the serpent who resides in Lake Telberin and can be
 *  summoned by searching the crack in the cenote. Her tailwhip
 *  deals damage to everybody in team. Everyone she is victorious
 *  over ultimately ends up in the lake.
 *
 *  Created 8.5.2022 by Velith
 *  Tailwhip function largely inspired by the dragon turtle from Krynn.
 *  Functionalities concerning blocking exits created by Arman.
 */

#pragma strict_types
inherit "/lib/unique";
inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/lib/intro";
inherit "/std/combat/unarmed.c";

#include <const.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void          create_emerald_monster();
public void          add_introduced(string name);
public void          react_intro(object tp);
public void          add_serpent_emotes();
public int           query_serpent_half_heath();
void                 notify_you_killed_me(object victim);
public int           special_attack(object enemy);
public varargs int   tailwhip(object victim);
public void          death(object victim);
public void          drown_victim(object victim, object searcher);
public void          remove_victim(object victim);
public void          run_away();

/* definitions */
#define    CLONE_MASTER    ("/d/Genesis/sys/global/unique")
#define    SS_WEP          ("/d/Emerald/south_shore/obj/")
#define    SS_ARM          ("/d/Emerald/south_shore/obj/")
#define    FANG            (SS_WEP + "fang")
#define    SCALE           (SS_ARM + "scale")
#define    UNDERWATER      ("/d/Emerald/south_shore/room/underwater.c")
#define    THIS_LOG        ("demerga")

/* global variables */
public object        Weapon;
int                  exit_blocked;
int                  dead = 1;

/*
 * Function name:        create_emerald_monster
 * Description  :        Set up the serpent with domain presets
 */
public void
create_emerald_monster()
{
    set_name("demerga");
    set_race_name("serpent");
    add_name("_emerald_lake_serpent");
    add_name("Demerga");
    add_serpent_emotes();
    set_gender(G_FEMALE);
    set_title("the Fierce, Deadly Fang of Emerald and "
              + "Leviathan of the Depths");
    set_adj( ({ "deadly", "gleaming", "lake" }) );
    set_short("deadly gleaming lake serpent");
    set_long("A sleek mass towers high above you, dripping wet "
             + "with lake water. A sharp pair of azure eyes regards "
             + "you with supernatural intelligence, flashing dangerously "
             + "in the light. Small beams of sunlight dance across the "
             + "leviathan's body, causing her many hued scales to waver "
             + "and shift in the sunlight. As you edge closer, enthralled "
             + "by her supernatural beauty, you notice the razor-sharp "
             + "row of iridescent fangs that grace the serpent's maw. "
             + "Glancing at the lake, you start as you realize the "
             + "beast's tail is lined with hundreds of piercing spikes. "
             + "Utter terror descends upon you in the presence of this "
             + "powerful creature.\n");

    // str, dex, con, int, wis, dis
    set_stats(({ 240+random(20), 240+random(20), 270+random(10),
                180+random(10), 180+random(10), 200+random(10) }));
    set_alignment(0);
    
    set_attack_unarmed(0, 75, 50, W_BLUDGEON | W_SLASH, 45, "tail");
    set_attack_unarmed(1, 60, 50, W_IMPALE | W_SLASH, 25, "left fang");
    set_attack_unarmed(1, 60, 50, W_IMPALE | W_SLASH, 25, "right fang");
    set_hitloc_unarmed(A_BODY, 70, 50, "body");
    set_hitloc_unarmed(A_FEET, 75, 50, "tail");
    set_hitloc_unarmed(A_NECK, 60, 20, "neck");
    set_hitloc_unarmed(A_HEAD, 55, 10, "head");
	
    set_skill(SS_BLIND_COMBAT, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_AWARENESS, 20);
  
    add_prop(CONT_I_VOLUME,     200000);
    add_prop(CONT_I_WEIGHT,     200000);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK,   100);
    add_prop(MAGIC_I_BREATHE_WATER, 100);
    add_prop(MAGIC_I_RES_MAGIC, 50);
    add_prop(MAGIC_I_RES_WATER, 20);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
  
	// clone special items occasionally
	object scale = clone_unique(SCALE, 4, 0, 0, 40);
	if (scale)
	{
		scale->move_to(this_object(), 1);
	}
	
	object fang = clone_unique(FANG, 4, 0, 0, 40);
	if (fang)
	{
		fang->move_to(this_object(), 1);
	}
} /* create_emerald_monster */
  
void
leave_message()
{
    say(QCTNAME(TO) + " withdraws into the depths of Lake "
        + "Telberin, quickly vanishing from view.\n");
    TO->remove_object();
}
  
string
check_enemy()
{
    if(TO->query_attack())
        return "emote throws her head back and roars, the sound "
        + "resonating all around you.";
    
    set_alarm(3.0, 0.0, leave_message);
    return "emote shifts restlessly, glancing around the beach.";
}

/*
 * Function name:       add_introduced
 * Description  :       Add the name of the being who has introduced
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
    /* wizards always know the npc name, so query_met() is true.
    * however, assume that if a wiz intro'd, we should respond
    */
    if (interactive(this_player()) &&
        CAN_SEE_IN_ROOM(this_object()) &&
        CAN_SEE(this_object(), this_player()) &&
        (!this_player()->query_met(query_name()) ||
         this_player()->query_wiz_level()))
    {
        set_alarm(1.0 + (2.0 * rnd()), 0.0,
                  &react_intro(this_player()));
    }
} /* add_introduced */
  
/*
 * Function name:        react_intro
 * Description  :        the serpent introduces herself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{    
    if (!present(tp, environment(this_object())))
    {
        command("emote draws her head back and snarls.");
    	command("emote hisses: The waves will soon claim those "
                + "who are insolent.");
    	return;
    }
    
    command("emote rises towards the ceiling of the cenote and "
            + "regards you with her icy gaze.");
    command("introduce me");
} /* react_intro */

/*
 * Function name:        add_serpent_emotes
 * Description  :        the emotes for the serpent
 */
public void
add_serpent_emotes()
{
    set_act_time(5 + random(10));
    add_act("emote hisses threateningly.");
    add_act("emote 's tail moves under the surface of the "
            + "water, causing large waves to rush up the beach.");
    add_act("emote lifts part of her serpentine body out "
            + "of the lake, rising high above you.");
    add_act("emote inspects you closely with her azure gaze.");
    add_act("@@check_enemy", 1);
  
    set_cact_time(10 + random(5));
    add_cact("emote snarls at you, baring her many "
             + "rows of razor-sharp teeth.");
    add_cact("emote thrashes restlessly, spraying water "
             + "in every direction.");
    add_cact("emote narrows her eyes.");
    add_cact("emote opens her great maw and hisses, "
             + "the chilling sound echoing around the cenote.");
} /* add_dragon_emotes */

public int
query_serpent_half_heath()
{
    if( TO->query_hp() < (TO->query_max_hp() / 2) )
        return 1;
    else
	    return 0;
}

/*
 * Function name:        notify_you_killed_me
 * Description:          Trigger remove_victim when the player dies
 * Arguments:            object victim - the player
 */
void
notify_you_killed_me(object victim)
{
    ::notify_you_killed_me(victim);
    if(dead == 1)
    {
        remove_victim(victim); 
    }
}

/*
 * Function name:        special_attack
 * Description  :        The timing for the serpent's special attack
 * Arguments    :        object enemy - who the npc fights
 * Returns      :        0 - no special attack
 *                       1 - special attack
 */
public int
special_attack(object victim)
{  
    if( TO->query_serpent_half_heath() && !exit_blocked)
    {
        tell_room(environment(TO),"The serpent's flailing tail "
                  + "lands across the exit to the beach, effectively "
                  + "blocking the opening!\n");
        exit_blocked = 1;
    }
    
    int attack_type = random(20);
    if (attack_type < 5)
    {
        tailwhip(victim);
    	return 1;
    }
} /* special_attack */

/*
 * Function name:        tailwhip
 * Description  :        The serpent's special. She deals damage by
 *                       lashing out at her enemies with her tail.
 * Arguments    :        object victim - the player
 * Returns      :        integer 1
 */
public varargs int
tailwhip(object victim)
{
    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    object searcher = QCTNAME(victim);
    mixed  *sdam;
    string *hitloc;
    string  his = victim->query_possessive();
    string  him = victim->query_objective();
    string  he  = victim->query_pronoun();
    string  swipe_msg;
    string result;
    mixed* hitresult;
    int i, damage;
    
    tell_room(environment(TO), QCTNAME(this_object()) + " draws "
              + "herself upwards, and whips her tail forth!\n");

    for (i = 0; i < sizeof(enemies); i++)
    {
        damage = random(100) + F_PENMOD(150, 75);
    	hitresult = enemies[i]->hit_me(damage, W_SLASH, TO, -1);
    	result = "hardly touched";
      
    	if (hitresult[0] > 0)
    	    result == "barely scratched";
    	if (hitresult[0] > 10)
    	    result = "slightly cut";
    	if (hitresult[0] > 20)
    	    result = "badly sliced";
    	if (hitresult[0] > 40)
    	    result = "deeply slashed";
    	if (hitresult[0] > 60)
    	    result = "brutally lacerated";
      
    	enemies[i]->catch_msg("You were " + result + " by the " 
                              + "attack!\n");
    	tell_room(environment(TO), QCTNAME(enemies[i]) + " is " 
                  + result + " by the attack!\n", enemies[i]);
      
      if (enemies[i]->query_hp() <= 0)
      {
          dead = 0;
          drown_victim(enemies[i], QCTNAME(enemies[i]));
          enemies[i]->do_die(TO); 
      }
    }
    
    if( !TO->query_serpent_half_heath() && exit_blocked)
    {
        tell_room(environment(TO),"The serpent's tail moves away "
                  + "from the exit of the cenote!\n");
	    exit_blocked = 0;
    }
} /* tailwhip */

/*
 * Function name:        death
 * Description  :        Aftermath of when a player dies; heals the 
 *                       serpent and logs the player's death
 * Arguments    :        object victim - the soon-to-be-dead player
 */
public void
death(object victim)
{
    // Make the serpent heal a little when she kills someone
    tell_room(environment(TO), QCTNAME(this_object()) + " basks in "
              + "the bloody spray, invigorated by her victory!\n\n", victim);
    TO->heal_hp(2000);
    
    log_file(THIS_LOG, TIME2FORMAT(time(), "mm/dd/yyyy")
             + " (" + ctime(time())[11..18]
             + ") " + capitalize(query_real_name()) + " killed "
             + capitalize(victim->query_name()) + ".\n");
} /* death */

/*
 * Function name:        drown_victim
 * Description  :        Drown the victim if they die by the special
 * Arguments    :        object victim - the soon-to-be-dead player
 */
public void
drown_victim(object victim, object searcher)
{
    string  him = victim->query_objective();
    string  his = victim->query_possessive();
  
    victim->catch_msg("\nThe serpent whips her tail around with lightning "
                      + "speed. Before you can react, one of her tail "
                      + "spikes has buried itself deep into your flesh! The rocks "
                      + "of the shores slash into your flesh as the serpent begins "
                      + "to draw you towards the lake. The burning pain ceases as "
                      + "you depart from the shore and slip into the waves. "
                      + "Darkness clouds your vision as the icy waters of Lake "
                      + "Telberin envelope you.\n\n");
    victim->cb_stop_fight(({ TO }));
    victim->move_living("M", UNDERWATER, 1, 0);
  
    tell_room(environment(TO), "\nWith lightning speed, the serpent "
              + "whips her tail around, spearing the corpse of "
              + QTNAME(victim) + " with one of her spikes! As you watch, "
              + "frozen in terror, she agonizingly draws her unresponsive "
              + "victim into the frigid waves of Lake Telberin. The "
              + "surface of the lake breaks one last time as a few air "
              + "bubbles escape, and is disturbed no more.\n\n");
  
    tell_room(environment(TO), searcher + " died.\n" + QCTNAME(TO) 
              + " drowned " + victim->query_objective() + ".\n");
    death(victim);
  
} /* drown_victim */

/*
 * Function name:        remove_victim
 * Description  :        Used to remove the victim if they die by a 
 *                       white hit
 * Arguments    :        object victim - the dead player
 */
public void
remove_victim(object victim)
{  
    tell_room(environment(TO), "\nThe waters of Lake Telberin "
              + "suddenly swell. An eerie calm settles over the cavern "
              + "as the waves crashing onto the beach grow steadily "
              + "stronger. Suddenly, a towering wave crashes into the "
              + "beach, filling the cavern with water!\n");
  
    victim->catch_msg("You weakly grasp at the rocks on the beach "
                      + "as a torrent of water pours over you. As the wave recedes "
                      + "back into the lake, you feel yourself being swept in with "
                      + "it. Darkness clouds your sight.\n\n");
    victim->cb_stop_fight(({ TO }));
    victim->move_living("M", UNDERWATER, 1, 0);
  
    tell_room(environment(TO), "You gasp for air, clinging "
              + "desperately onto the jagged wall in an effort not to be "
              + "swept away. As the water ebbs and recedes back into the "
              + "lake, you realize that " + QCTNAME(victim) + " is gone.\n");
  
    death(victim);
  
} /* remove_victim */

/*
 * Function name:        notify_death
 * Description  :        Notify onlookers of the serpent's death,
 * Arguments    :        object killer - the object that killed the 
 *                       serpent
 */
public void
notify_death(object killer)
{
    tell_room(environment(this_object()),
              "\n" + QCTNAME(this_object()) + " sways, and her graceful "
              + "figure arcs downward. A wave of water washes over "
              + "the plunging frame of the serpent, and she disintegrates "
              + "into foam. Another swell of the tide sweeps the "
              + "froth into the lake.\n");
    tell_room(environment(this_object()),
              "\n" + QCTNAME(this_object()) + " is defeated.\n");
	
    if (living(killer))
    {
        tell_object(killer, "You have slain " 
                    + query_the_name(this_object()) + "!\n\n");
    	tell_room(environment(this_object()),  QCTNAME(killer) 
                  + " has slain " +  query_objective() + "!\n\n",
                  ({ this_object(), killer }));
    }
} /* notify_death */

/*
 * Function name:        run_away
 * Description  :        Keep the serpent from ever wimpying.
 */
public void
run_away()
{
    command("hiss");
    command("emote seethes: To retreat is to accept defeat!");
    return;
} /* run_away */
