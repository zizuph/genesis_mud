/* 
 * /d/Emerald/thief_lair/thug.c
 * 
 * One of the two inheritable files used by the bandits in 
 * a cave. This is for the more intimidation and combat oriented
 * members of the bandit, whereas thief.c is for the sneakier
 * and stealthier members.
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Emerald/std/emerald_monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#define DIR "/d/Emerald/thief_lair/"

// Special attack prototypes.
int s_attack(object enemy);
int disarm(object enemy);
int run_away();
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

    create_bandit();
    set_special_attack_percent(100);
    add_special_attack(s_attack, 100, "s_attack");
    add_special_attack(run_away, 0, "run_away");
    add_special_attack(disarm, 0, "disarm");
    add_special_attack(backstab, 0, "backstab");
}


/* Determines whether or not a given object can see.
   returns 0 if it can, 1 if the object cannot.
*/
   
int
check_blind(object ob)
{
    return (!CAN_SEE_IN_ROOM(ob) || !CAN_SEE(ob, this_object()));
}

int
s_attack(object enemy)
{

// The bandit will run away if too badly hurt.

    if (query_hp() < query_max_hp() / 4)
    { 
	run_away();	
    }

// Only gets a special attack every five rounds.

    if (random(5))
    {
	return 0;
    }

// The bandit will attempt to disarm his foe if  personally under attack. 
    
    if (sizeof(filter(query_enemy(-1), &operator(==)(this_object()) @
		      &->query_attack())))        
    {
	return disarm(enemy);
    }
    
// The bandit will attempt to backstab his foe should the later's attention
// be focused elsewhere ;)

    else
    {
	return backstab(enemy);
    }
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

    if (check_blind(this_object()))
    {
	return 0; // Its difficult to disarm a foe one cannot see.
    }

    foesWeapon = enemy->query_weapon(W_RIGHT);
    if (foesWeapon == 0)
    {
	foesWeapon = enemy->query_weapon(W_LEFT);
	if (foesWeapon == 0){
	    foesWeapon = enemy->query_weapon(W_BOTH);
	    difficulty = 50; // Its hard to disarm a two handed weapon!
	}
    }

    if (foesWeapon == 0)
    {
	return 0; //Cant disarm a weaponless foe!
    }
    
    foesWeaponID = OB_NAME(foesWeapon);

    if ((enemy->query_skill(SS_PARRY) + enemy->query_stat(SS_STR) +
	difficulty) < (query_stat(SS_STR) + random(125)))
    {
	enemy->catch_msg(QCTNAME(this_object()) + " strikes your " + 
			 foesWeapon->short() +
			 "very hard, knocking it from your hands!\n");
	tell_watcher(QCTNAME(this_object()) + " knocks " + 
		     QTNAME(enemy)+ "'s " + foesWeapon->short() +
		     " from " + enemy->query_possessive() + " hands!\n");
	enemy->command("drop " + foesWeaponID);
	command("get " + foesWeaponID);	
    }

    else
    {
	enemy->catch_msg(QCTNAME(this_object()) + "tries to disarm you, "+
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
	case W_SLASH:
	    damage_verb = "slashes";
	case W_BLUDGEON:
	    damage_verb = "smashes";
	default:
	    damage_verb = "stabs";
	}	     
	
	enemy->hit_me(200 + random(200), damage_type, this_object, A_BODY);
	enemy->catch_tell("Someone " + damage_verb + " you in the back!!!\n");
	tell_watcher(QCTNAME(this_object()) + " " + damage_verb + " " +
		     QTNAME(enemy) + " in the back!\n");
	
	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(this_object());
	}
	
    }
    else
    {
	enemy->catch_tell(QCTNAME(this_object()) + " tried to strike you from behind, "+
			  "but you evaded the attack!\n");
    }
    
    return 1;
}

/* This function allows the bandit to flee to /d/Emerald/thief_lair/lair9
   which is the base_camp for the bandits. Nothing will happen if 
   this function is called when the bandit is already at that location.
*/ 


int 
run_away()
{
    object fleeroom;
    fleeroom = find_object(DIR + "lair9");

    if (environment(this_object()) == fleeroom)
    {
	return 0; // The bandits will not run from their main basecamp.
    }

    LOAD_ERR(DIR +"lair9"); // Make sure the room is loaded, so we can 
                            // find it.
    if (fleeroom == 0)
    {
	tell_room(environment(this_object()), QCTNAME(this_object()) +
		  " tries to run away, but fails!\n", 0, this_object());
    }
    
    else
    {
	tell_room(environment(this_object()), QCTNAME(this_object()) +
		  " runs away!\n", 0, this_object());
	move_living("M", find_object(DIR + "lair9"), 1);
	tell_room(environment(this_object()), QCTNAME(this_object()) +
		  " arrives from the south.", 0, this_object());
    }	
    return 1;
}

 
    



