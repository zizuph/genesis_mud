/* 
 * /d/Emerald/thief_lair/base_thug.c
 * 
 * One of three inheritable files used by the bandits in 
 * a cave. This is for the more intimidation and combat oriented
 * members of the bandit, whereas thief.c is for the sneakier
 * and stealthier members. Leader.c inherits this file, and is
 * in turn inherited by Tevalanar.c and lieutenant.c
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Emerald/std/emerald_monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Emerald/sys/paths.h"

// Special attack prototypes.
int s_attack(object enemy);
int disarm(object enemy);
void run_away();
int backstab(object enemy);

void
config_bandit(int level)
{
    set_stats(({ level * 11 / 10 + random(10),
                 level *  9 / 10 + random(10),
                 level * 11 / 10 + random(10),
                 level *  9 / 10 + random(10),
                 level *  8 / 10 + random(10),
                 level *  9 / 10 + random(10)}));

    set_skill(SS_WEP_CLUB, level / 8 * 10 + random(10));
    set_skill(SS_WEP_SWORD, level  / 8 * 10 + random(10));
    set_skill(SS_WEP_POLEARM, level / 8 * 10 + random(10));
    set_skill(SS_WEP_KNIFE, level  / 8 * 10 + random(10));
    set_skill(SS_WEP_AXE, level / 8 * 10 + random(10));
    set_skill(SS_UNARM_COMBAT, level * 7 / 10 + random(10));
    set_skill(SS_DEFENSE, level * 8 / 10 + random(10));
    set_skill(SS_PARRY, level * 5 / 10 + random(10)); 
    set_skill(SS_AWARENESS, level * 3 /10 + 20 + random(10));
    set_skill(SS_BLIND_COMBAT, min(60, level * 5 / 10 + random(10)));
    set_skill(SS_SNEAK, level * 7 / 10 + random(10));
    set_skill(SS_HIDE, level * 7 / 10 + random(10));
    set_skill(SS_BACKSTAB, level * 7 / 10);

    set_alignment(- (100 + random(600)));
}
 
void
create_bandit()
{
    config_bandit(60);
}

nomask void
create_emerald_monster()
{
    set_race_name("human");

    set_appearance(- 40 + random(80));

    add_prop(CONT_I_HEIGHT, 170 + random(40));
    add_prop(CONT_I_WEIGHT, 75000 + random(35000));
    add_prop(CONT_I_VOLUME, 75000 + random(35000));

    set_special_attack_percent(20);
    add_special_attack(s_attack, 100, "s_attack");

    create_bandit();
}

/* Determines whether or not a given object can see.
   returns 0 if it can, 1 if the object cannot.
*/
   
int
check_blind(object ob)
{
    return (!CAN_SEE_IN_ROOM(ob) || !CAN_SEE(ob, this_object()));
}

public int
special_attack(object enemy)
{
// The bandit will run away if too badly hurt.
    if (query_hp() < (query_max_hp() / 4))
    {
	run_away();
	return 1;
    }

    return ::special_attack(enemy);
}

int
s_attack(object enemy)
{
    // The bandit will attempt to disarm his foe if  personally under attack. 

    if (sizeof(filter(query_enemy(-1), &operator(==)(this_object()) @
		      &->query_attack())))        
    {
	return disarm(enemy);
    }

    // The bandit will attempt to backstab his foe should the latter's
    // attention be focused elsewhere ;)
    return backstab(enemy);
}

/* A special attack in which the thug tries to knock the weapon
   from his foes grasp. If he does so, he will grab it. Called
   only from the special_attack function.
*/

int
disarm(object enemy)
{
    int difficulty = 0;
    object foesWeapon;
    string foesWeaponID;
    object myWeapon;
    object *myWeapons;

    if (check_blind(this_object()))
    {
	return 0; // Its difficult to disarm a foe one cannot see.
    }

    foesWeapon = enemy->query_weapon(W_RIGHT) || enemy->query_weapon(W_LEFT);
    if (!foesWeapon)
    {
        if (!(foesWeapon = enemy->query_weapon(W_BOTH)))
        {
	    return 0; // Can't disarm a weaponless foe!
	}

        difficulty = 50; // Its hard to disarm a two handed weapon!
    }

    foesWeaponID = OB_NAME(foesWeapon);

    if ((enemy->query_skill(SS_PARRY) + enemy->query_stat(SS_STR) +
	difficulty) < (query_stat(SS_STR) + random(125)))
    {
	enemy->catch_tell(query_The_name(enemy) + " strikes your " + 
            foesWeapon->short(enemy) + " very hard, knocking it from " +
            "your hands!\n");
	tell_watcher(QCTNAME(this_object()) + " knocks " + 
		     QTPNAME(enemy)+ " " + QSHORT(foesWeapon) +
		     " from " + enemy->query_possessive() + " hands!\n", enemy);
	enemy->command("$drop " + foesWeaponID);
	
	if (random(2)) // Assume the bandit can grab the weapon before the 
	               // player 50% of the time.
	{
	    command("get " + foesWeaponID);
	}
	/* The bandit might attempt to wield an obviously superior weapon,
	   should he/she manage to grab one. */

	if ((foesWeapon->query_tohit() + foesWeapon->query_pen() >
	    60) && random(2))
	{	
	    myWeapons = query_weapon(-1);
	    myWeapon = myWeapons[0];
	    command("unwield all");  
	    
	    if (!(wield(foesWeapon))) //Wields the stolen weapon, or his own 
	    {                         //again should he fail to wield his prize.
      		wield(myWeapon);
	    }
	}
    }
    
    else
    {
	enemy->catch_tell(query_The_name(enemy) + " tries to disarm you, "+
			 "but fails!\n");
    }
    
    return 1;
}

/* A damage special which will only be employed when the bandit is not 
   (personally) under attack. It does quite a bit of damage.
*/
	   
int
backstab(object enemy)
{
    object *weps = query_weapon(-1), chosen_wep;
    string damage_verb;
    int damage_type;

    if (check_blind(this_object()))
    {
	return 0; // Cant backstab what you cannot see!
    }

    if (random(query_skill(SS_BACKSTAB)) > 
	((enemy->query_stat(SS_DEX) + enemy->query_skill(SS_AWARENESS)) / 10))
    {
	if (!sizeof(weps))
	{
	    return 0; // Cant backstab effectively with bare hands!
	}

	chosen_wep = weps[random(sizeof(weps))];
	damage_type = chosen_wep->query_dt();
	
	switch (damage_type)
	{
	case 2:
	    damage_verb = "slashes";
	case 4:
	    damage_verb = "smashes";
	default:
	    damage_verb = "stabs";
	}	     
	
	enemy->hit_me(200 + random(200), damage_type, this_object(), A_BODY);
	enemy->catch_tell("Someone " + damage_verb + " you in the back!!!\n");
	tell_watcher(QCTNAME(this_object()) + " " + damage_verb + " " +
		     QTNAME(enemy) + " in the back!\n", enemy);
	
	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(this_object());
	}
    }
    else
    {
	enemy->catch_msg(QCTNAME(this_object()) + " tried to strike you from behind, "+
			  "but you evaded the attack!\n");
    }
    
    return 1;
}

/* This function allows the bandit to flee to /d/Emerald/thief_lair/cave9
   which is the base_camp for the bandits. Nothing will happen if 
   this function is called when the bandit is already at that location.
*/ 


public void
run_away()
{
    object fleeroom;

    /* Make sure the room is loaded, so we can find it */
    LOAD_ERR(THIEF_LAIR_DIR + "cave9"); 
    fleeroom = find_object(THIEF_LAIR_DIR + "cave9");

    if (environment(this_object()) == fleeroom)
    {
	return;
    }

    if (!fleeroom)
    {
	// Let the bandit wimpy normally if the room isn't loaded
	::run_away();
	return;
    }
    
    tell_room(environment(this_object()), QCTNAME(this_object()) +
        " runs away!\n", 0, this_object());
    move_living("M", find_object(THIEF_LAIR_DIR + "cave9"), 1);
    tell_room(environment(this_object()), QCTNAME(this_object()) +
        " arrives from the south.", 0, this_object());
}

/* Allows one to query the inventory of a room for the presence of
   bandits. Naturally, the inventory in the room may be reduced in 
   size after they have left ;)
*/

public int
query_bandit()
{
    return 1;
} 


/* Called when the bandit is attacked (see attacked_by(object ob),
   below:

   Checks to see if any bandit leaders are present in the room,
   and if so, this function prompts them to issue orders.
*/

void
notify_leader()
{
    object *leaders;
    object myleader;

    leaders = filter(all_inventory(environment(this_object())),
		     &->query_bandit_leader());
    // All objects in the room identifying themselves as bandit leaders.

    if (sizeof(leaders))
    {
	myleader = leaders[0];
	myleader->request_orders();
    }
}

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 * 
 * Slightly modified so that the bandit "notifies" any bandit
 * leaders in the room that he has been attacked.
 */

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    notify_leader();
}    



