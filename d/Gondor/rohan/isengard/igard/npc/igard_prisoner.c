/*
 * This file is IGARD_NPC + "igard_prisoner.c"
 *
 * The base file for Isengard prisoner NPCs
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_monster.c
 *
 * 2016-01-22 - Cotillion
 * - Fixed to only execute arm_me once
 */

#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/lib/unique.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

#define WEP_ARRAY1 ({IGARD_WEP + "i_bar", IGARD_WEP + "i_shank"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY1 ({IGARD_ARM + "i_prison_tunic"}) 
#define ARM_ARRAY2 ({IGARD_ARM + "i_prison_leggings"})
#define ARM_ARRAY3 ({ })

#define IGARD_I_KILLS	"_igard_i_kills"
#define SEQ_PICK        "_mon_pick"

#define A_R_FIST   1

#define PUNCH_TASK	TASK_ROUTINE
#define PUNCH_SKILLS	({ TS_DEX, TS_STR })
#define PUNCH_VICTIM_SKILLS	({ TS_DEX })

#define PUNCH_RATE	25
#define PUNCH_PEN	30

static int     punch_rate  = PUNCH_RATE,
               punch_pen   = PUNCH_PEN,
               armed       = 0;

void
set_punch_rate(int i) { punch_rate = i; }

void
set_punch_pen(int i)  { punch_pen = i; }

// Prototypes:
void            help_friend(object ob, object friend);
void            test_can_see(object victim);

// Global variables:
static  int     Attack_Alarm,
                Wimpy_Run;
static  object  Victim;
static  string *Wep1,
               *Wep2,
               *Arm1,
               *Arm2,
               *Arm3;

object HOME;

void
set_wimpy_run(int i)
{
    Wimpy_Run = i;
}

int
query_wimpy_run()
{
    return Wimpy_Run;
}

public void
create_igard_prisoner()
{
    set_race_name("human");
}

nomask void
create_monster()
{
    int rnd     = random(11);

    seteuid(getuid(TO));
    add_name("_igard_prisoner");

    set_skill(SS_AWARENESS,    55+rnd);
    set_skill(SS_CLIMB,        25+rnd);
    set_skill(SS_BLIND_COMBAT, 80+rnd);

    set_skill(SS_WEP_SWORD,   30);
    set_skill(SS_WEP_POLEARM, 30);
    set_skill(SS_WEP_AXE,     30);
    set_skill(SS_WEP_KNIFE,   30);
    set_skill(SS_WEP_CLUB,    30);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_whimpy(45);
    set_wimpy_run(20);

    set_learn_pref( ({ 1, 1, 1, 0, 0, 1, }) );

    set_pick_up(75);

    create_igard_prisoner();
}

public int     query_knight_prestige() {return (- query_alignment()); }

static void
set_arm_arrays()
{
   Wep1 = WEP_ARRAY1;
   Wep2 = WEP_ARRAY2;
   Arm1 = ARM_ARRAY1;
   Arm2 = ARM_ARRAY2;
   Arm3 = ARM_ARRAY3;

   set_all_hitloc_unarmed(10);
}


public void
set_restrain_path_with_delay()
{
    if (!query_restrain_path() || !sizeof(query_restrain_path()))
        set_restrain_path(implode(explode(file_name(ENV(TO)),"/")[0..3], "/"));
}

public void
arm_me()
{
   int iw, is;
   
   if (armed) 
      return;
   armed = 1;
   
   set_arm_arrays();
   
   seteuid(getuid(TO));
   
   if (is = sizeof(Wep1))
   {
      iw = random(is);
      if (Wep1[iw] == IGARD_WEP + "bestscim")
      {
          clone_unique(IGARD_WEP + "bestscim", 5, 
                      IGARD_WEP + "largescim")->move(TO);
      }

      if (Wep1[iw] == IGARD_WEP + "bestaxe")
      {
          clone_unique(IGARD_WEP + "bestaxe", 5, 
                      IGARD_WEP + "largeaxe")->move(TO);
      }

      if (Wep1[iw] == IGARD_WEP + "besthalberd")
      {
          clone_unique(IGARD_WEP + "besthalberd", 5, 
                      IGARD_WEP + "largehalberd")->move(TO);
      }

      else
      {
          clone_object(Wep1[iw])->move(TO);
      }
   }

   command("wield weapon");
   
   if (is = sizeof(Wep2))
   {
      iw = random(is);
      clone_object(Wep2[iw])->move(TO);
   }
   
   if (is = sizeof(Arm1))
   {
      iw = random(is);
      clone_object(Arm1[iw])->move(TO);
   }
   
   if (is = sizeof(Arm2))
   {
      iw = random(is);
      clone_object(Arm2[iw])->move(TO);
   }
   
   if (is = sizeof(Arm3))
   {
      iw = random(is);
      clone_object(Arm3[iw])->move(TO);
   }
   command("wield all");
   command("wear all");

   // automatical setting of restrain path if no path is set
   if (!query_restrain_path() || !sizeof(query_restrain_path()))
        set_alarm(0.0, 0.0, set_restrain_path_with_delay);

    refresh_mobile();
}


int
go_back_home()
{
    return 1;
}


/*
 * Function name:   start_follow
 * Description:     Start following the enemy.
 * Arguments:       The object to follow.
 */
public void
start_follow(object ob)
{
    object *follower,
            shadow;

    if (!objectp(ob) || !objectp(present(ob, ENV(TO))) || 
	(ob != query_attack()) || (Victim == ob))
	return;

    if (pointerp(follower = ob->query_follower()))
    {
	if (member_array(TO, follower) < 0)
	    ob->add_follower(TO);
    }
    else
    {
	shadow = clone_object(GONDOR_FOLLOW_SHADOW);
	shadow->follow(ob, TO);
    }
    Victim = ob;
    set_alarm(60.0, 0.0, &go_back_home());
}

public varargs void
remove_victim(object victim)
{
    if (objectp(victim) && (Victim != victim))
	return;
    Victim = 0;
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    ::attack_object(ob);
//    start_follow(ob);
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object  room = ENV(TO),
          *arr;
    
    ::attacked_by(ob);

    if (GOODIE || FRIEND)
    {
    switch (random(4))
        {
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            command("say I thought you were here to rescue us! You stinking "
            + "villain, you are no better than the filthy uruks!");
            break;
        }
    TP->add_prop(ENEMY_OF_PRISONERS, 1);
    }

    if  (BADDIE && !ENEMY)
    {
    switch (random(4))
        {
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            command("say Bring it on, dog! I have nothing left to lose.");
            break;
        }
    }

    start_follow(ob);

    while (!room->query_prop(ROOM_I_IS))
	room = ENV(room);
    arr = filter(all_inventory(room), &->id("_igard_prisoner"));
    arr->notify_ob_attacked_me(TO, ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
   if (objectp(query_attack()))
      return;
   
   if (random(10))
      set_alarm(5.0, 0.0, &help_friend(attacker, TO));
}

void
do_attack(object victim)
{
   object *arr;
   if (objectp(query_attack()) || !objectp(present(victim, ENV(TO))))
       return;

   if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim))
   {
      if (!Attack_Alarm || !sizeof(get_alarm(Attack_Alarm)))
          Attack_Alarm = set_alarm(5.0, 10.0, &test_can_see(victim));
      switch (random(5))
        {
        case 0:
          command("shout Who is there? Come out where I can see you!");
          break;
        case 1:
        case 2:
        case 3:
          break;
        case 4:
          command("smell");
          command("shout Something smells awful! Take a bath, hidden one.");
          break;
        default:
          break;
        }
      return;
   }

   command("kill "+victim->query_real_name());

   if (objectp(query_attack()))
   {
	/* there was some debate re whether to order an attack here,
	 * since the other npcs also are aggressive and should be attacking
	 * on their own. however, since the npcs' awareness can vary
	 * it could be that one of them sees an arriving enemy while the
	 * others do not, so i left this in.  the above check for
	 * query_attack() will prevent the n**2 spam if they don't dare
	 * attack.  -- gnad
	 */
	arr = filter(all_inventory(ENV(TO)), &->id("_igard_prisoner")) - ({ TO });
	arr->order_attack_enemy(TO, victim);
   }
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob, object friend)
{
   if (objectp(ob) && !objectp(query_attack()) &&
       present(ob, ENV(TO)) && F_DARE_ATTACK(TO, ob) &&
       CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, ob))
   {
       command("shout For freedom! Die " + ob->query_race_name() + "!");
       command("kill "+ob->query_real_name());
   }
}

string
alignlook() 
{
   string *alignlooks = ({"grim", "haggard", "tired", "bruised", "cringing",
       "angry", "hollow-eyed", "haunted", "starving", "battered", "crying",
       "sobbing","wailing","helpless", "sickly", "leprous","woeful", "sad",
       "vengeful", "brave", "stubborn", "nervous", "innocent", "trusting",
       "sullen", "bleeding", "tortured", "limping",
       "filthy", "listless", "insane", "frightened", "terrified"});
   return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
   string *alignlooks = ({"short", "tiny", "crippled", "fair-skinned", "blonde",
       "muscular", "brown-haired", "red-haired", "fat", "skinny", "knock-kneed",
       "curly-haired","bald","tall", "slender", "flabby","strong-jawed", 
       "dark-eyed", "blue-eyed", "green-eyed", "young", "old", "ancient",
       "middle-aged", "childish", "pug-nosed", "long-nosed", "gap-toothed",
       "brown-skinned", "light-skinned", "long-haired", "long-legged", "toothless",
       "fat-lipped", "bright-eyed", "one-eared", "four-fingered", "club-footed"});
   return ONE_OF_LIST(alignlooks);
}


void
disguise_msg(object player)
{
   if (!present(player, ENV(TO)))
       return;
      switch (random(5))
        {
        case 0:
            player->catch_msg(BSN(
            "The " + query_nonmet_name() + " looks at you with hope that you "
            + "are here to rescue the people imprisoned below Isengard."));
          break;
        case 1:
        case 2:
        case 3:
          break;
        case 4:
            player->catch_msg(BSN(
            "The " + query_nonmet_name() + " pleads with you to aid "
            + "the prisoners in their uprising."));
          break;
        default:
          break;
        }
      return;
}


int
query_disguised(object player)
{
    if (FRIEND)
   {
	   set_alarm(2.0, 0.0, &disguise_msg(player));
    return 1;
   }
   return 0;
}


/*
 * Function name: check_attack
 * Description:   check if we attack someone we meet:
 *                We do attack if we can see player and if player either
 *                is defined as enemy in friend_or_foe and not disguised or
 *                player is fighting a morgul monster.
 * Argument:      player - the living we just met
 * Returns:       1/0    - attack/no attack
 */
static int
check_attack(object player)
{
   object  attacker = player->query_attack(),
          *arr;
 
   if (!player->query_npc() &&
          CAN_SEE(TO, player) &&
          !query_disguised(player) &&
          player->query_alignment() < 0
          || player->query_prop(ENEMY_OF_PRISONERS) ||
        (objectp(attacker = player->query_attack()) &&
         attacker->id("_igard_prisoner")))
   {
       /* give player (or this npc) time to arrive before attack */
	/* olorin warns that any delay here at all will allow the player
	 * to run thru to safety -- "even an alarm of 0 may be too slow".
	 * try this for now, while i look for a better way to handle
	 * the attacks -- gnadnar
	 */
       set_alarm(0.0, 0.0, &do_attack(player));
       player->add_prop(ENEMY_OF_PRISONERS, 1);
       return 1;
   }
   return 0;
}

public void
init_attack()
{
   if (objectp(query_attack()))
      return;

   if (!interactive(TP))
       return;
   check_attack(TP);
}

void
loot_corpse()
{
   command("get all from corpse");
}

int
notify_you_killed_me(object player)
{
    set_alarm(2.0, 0.0, loot_corpse);
    if (player->query_npc())
	return 1;
    seteuid(getuid(TO));
    write_file(IGARD_KILL_LOG, player->query_name()
      + " (" + player->query_average_stat()
      + ") was killed by " + TO->query_name() +" on "+ ctime(time())
      + " (" + file_name(ENV(TO)) + ").\n");
    return 1;
}

void
test_can_see(object victim)
{
    if (!present(victim,ENV(TO)))
    {
        remove_alarm(Attack_Alarm);
        Attack_Alarm = 0;
        return;
    }
    if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO,victim))
    {
        remove_alarm(Attack_Alarm);
        Attack_Alarm = 0;
        do_attack(victim);
    }
}

void
order_attack_enemy(object commander, object victim)
{
    if (objectp(query_attack()))
	return;

    do_attack(victim);
}

void
say_enemy(string str1, string str2)
{
    object enemy = query_attack();

    if (!objectp(enemy))
	return;
    if (!present(enemy,ENV(TO)))
	return;
    command("say " + str1 + query_attack()->query_race_name() + str2);
}

void
emote_enemy(string str)
{
    object  enemy = query_attack();

    if (!objectp(enemy))
	return;
    if (!present(enemy,ENV(TO)))
	return;
    command(str + " " + enemy->query_real_name());
}

public void
remove_surplus(object ob)
{
    if (!objectp(ob))	/* added to fix errs in debug log -- gnad */
        return;
    if (function_exists("create_heap", ob) == COINS_OBJECT)
    {
	command("sigh");
	return;
    }
    if (ob->query_prop(HEAP_I_IS))
	return;
    // We do not destroy items cloned into this room:
    if (member_array(ob, ENV(TO)->query_cloned_here()) > -1)
	command("drop " + OB_NAME(ob));
    else
    {
	say(QCTNAME(TO) + " slams the " + ob->short() 
     + " repeatedly against the wall until it is shattered beyond "
     + "recognition.\n");
	set_alarm(0.0, 0.0, &ob->remove_object());
    }
}

object
query_max_igard()
{
    int     max_hp = 0,
            hp,
            nmi = -1,
            i;
    object *arr;

    arr = filter(all_inventory(ENV(TO)), &->id("_igard_prisoner"));

    arr -= ({ TO });

    for (i = 0; i < sizeof(arr); i++)
    {
        if ((hp = arr[i]->query_hp()) > max_hp)
        {
            max_hp = hp;
            nmi = i;
        }
    }

    if (nmi >= 0)
        return arr[nmi];
    return 0;
}

int query_attack_me(object x) { return (x->query_attack() == TO); }

void
move_attack(object enemy, object target)
{
    enemy->stop_fight(target);
    enemy->attack_object(target);
}

public void
run_away()
{
    int     hp = query_hp(),
            mhp = query_max_hp();
    object  max_igard,
           *enemies; 


    if ( (100*hp/mhp) > Wimpy_Run)
    {
        if (objectp(max_igard = query_max_igard()))
        {
            enemies = filter(query_enemy(-1), query_attack_me);
            max_igard->remove_prop(OBJ_M_NO_ATTACK);
            map(enemies, "move_attack", TO, max_igard);
            tell_room(ENV(TO),
                QCTNAME(max_igard) + " steps in front of "
                + QTNAME(TO) + " and defends " + HIM_HER(TO)
                + " from harm!\n", ({ TO, max_igard, }) );
            enemies->catch_msg("You turn to attack "+QTNAME(max_igard)+".\n");
            add_prop(OBJ_M_NO_ATTACK, 
                "@@query_is_behind" + ":" + file_name(TO)
                                    + "|" + file_name(max_igard) + "@@");
            return;
        }
    }

    ::run_away();
}

string
query_is_behind(string prot_file)
{
    object  prot = find_object(prot_file);

    if (!objectp(prot) || !living(prot) ||
        !present(prot, ENV(TO)) ||
        (TP->query_attack() != prot) || !CAN_SEE(TO, prot))
    {
        set_alarm(0.0, 0.0, &remove_prop(OBJ_M_NO_ATTACK));
        return 0;
    }

    return process_string("That person is being protected by the "
      + prot->query_nonmet_name()+"!\n");
}

public int
second_life(object killer)
{
    int     kills;
    string  name;

    FIX_EUID
    if (!objectp(killer))
        killer = this_player();

    if (objectp(killer))
    {
        killer->add_prop(IGARD_I_KILLS, kills =
            (killer->query_prop(IGARD_I_KILLS) + 1));
    
        if (!stringp(name = killer->query_name()))
            name = file_name(killer);
    }
    else
    {
        name = "Unknown";
    }

    return 0;
}

public void
check_shields()
{
    object *shields;

    command("wear all");

    shields = filter(all_inventory(TO), &operator(==)(ARMOUR_OBJECT) @
		     &function_exists("create_object", ));
    shields = filter(shields, &operator(==)(A_SHIELD) @
		     &->query_at());
    shields = filter(shields, not @ objectp @ &->query_worn());
    shields -= ({ 0 });
    if (!sizeof(shields))
	return;
    
    say(QCTNAME(TO) + " breaks the " + shields[0]->short() + " by smashing "
        + "it against the wall.\n");
    shields[0]->remove_broken();
    command("drop " + OB_NAME(shields[0]));

    if (sizeof(shields) > 1)
	set_alarm(5.0, 0.0, check_shields);
}

public void
check_weapons(object new)
{
    int     new_type = new->query_wt(),
            new_sk = query_skill(SS_WEP_FIRST + new_type),
            old_sk;
    object *old = query_weapon(-1);

    if (!sizeof(old))
    {
	command("wield all");
	if (!objectp(new->query_wielded()))
	{
	    command("remove shields");
	    command("wield all");
	    set_alarm(5.0, 0.0, check_shields);
	}
	if (!objectp(new->query_wielded()))
	{
	    say(QCTNAME(TO) + " breaks the " + new->short() + " by snapping it "
         + "underfoot.\n");
	    new->remove_broken();
	    command("drop " + OB_NAME(new));
	}
	return;
    }
    if (member_array(new, old) >= 0)
    {
        /* already wielding the new weapon -- probably
         * as a result of a brawl "disarm" expiring
         */
        return;
    }

    old_sk = query_skill(SS_WEP_FIRST + old[0]->query_wt());
    if ( (old_sk * old[0]->query_pen() * old[0]->query_hit()) >
	 (new_sk * new->query_pen() * new->query_hit()) )
	old[0] = new;
    else
    {
	command("unwield " + OB_NAME(old[0]));
	command("wield " + OB_NAME(new));
	// Did we succeed in wielding the weapon?
	if (!objectp(new->query_wielded()))
	{
	    command("remove shields");
	    command("wield " + OB_NAME(new));
	    // Did we succeed in wielding the weapon?
	    if (!objectp(new->query_wielded()))
	    {
		command("wield " + OB_NAME(old[0]));
		old[0] = new;
	    }
	    set_alarm(5.0, 0.0, check_shields);
	}
    }

    say(QCTNAME(TO) + " breaks the " + old[0]->short() + " by jumping up "
        + "and down on it.\n");
    old[0]->remove_broken();
    command("drop " + OB_NAME(old[0]));
}

public void
check_armours(object new)
{
    int     new_type = new->query_at();
    object	old, *old_shields;

    /*
     * If we can wear the new armour in addition to the already worn
     * armours, all if fine. 
     */
    command("wear all");
    if (objectp(new->query_worn()))
    {
	return;
    }

    /*
     * Is the new armour better than the old one we are wearing?
     */
    if (new_type != A_SHIELD)
    {
	old = TO->query_armour(new_type);
    }
    else
    {
	// shields are a pain:
	old_shields = filter(TO->query_armour(new_type),
		     &operator(==)(A_SHIELD) @ &->query_at());
	if (sizeof(old_shields))
	{
	    old = old_shields[0];
	}
    }
    if (!objectp(old))
    {
	// This might happen if we are wielding a two handed
	// weapon, discard the new armour:
	say(QCTNAME(TO) + " breaks the " + new->short() +
	    " with a malicious grin.\n");
	new->remove_broken();
	if (objectp(new))
	{
	    command("drop " + OB_NAME(new));
	}
	return;
    }
	    
    if (new->query_ac() <= old->query_ac())
    {
	old = new;
    }
    else
    {
	command("remove " + OB_NAME(old));
	command("wear " + OB_NAME(new));
	// Did we succeed in wielding the armour?
	if (!objectp(new->query_worn()))
	{
	    command("wear " + OB_NAME(old));
	    old = new;
	}
    }
    /*
     * Break what we cannot use any more:
     */
    say(QCTNAME(TO) + " slams the " + old->short() +
	" into the wall, smashing it beyond use.\n");
    old->remove_broken();
    command("drop " + OB_NAME(old));
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from))
    {
        return;
    }

    if (ob->id("corpse"))
    {
        command("get all from corpse");
        set_alarm(2.0, 0.0, &command("drop corpse"));
        return;
    }

    if (ob->query_prop(OBJ_I_BROKEN))
    {
	// Clean up and remove broken objects that we pick up!
	set_alarm(0.0, 0.0, &ob->remove_object());
        set_alarm(5.0, 0.0, &command("drop broken things"));
        return;
    }

    if (function_exists("create_object", ob) == WEAPON_OBJECT)
    {
	set_alarm(1.0, 0.0, &check_weapons(ob));
        return;
    }

    if (function_exists("create_object", ob) == ARMOUR_OBJECT)
    {
        set_alarm(1.0, 0.0, &check_armours(ob));
        return;
    }

    if ((query_encumberance_weight() > 25) ||
        (query_encumberance_volume() > 25))
    {
        set_alarm(1.0, 0.0, &remove_surplus(ob));
    }
}


int
prisoner_acts()
{
    set_chat_time(15 + random(15));
    add_chat("Please, help us escape!");
    add_chat("We killed most of the guards, but more are coming, you "
        + "can be sure of that.");
    add_chat("Stand with us!");
    add_chat("I have little hope we shall escape. Many of those "
        + "devils will go down with us before all is finished.");
    add_chat("Where is my family? I haven't seen them since we were "
        + "captured!");
    add_chat("You either stand with us or against us, stranger.");
    add_chat("They are coming!");
    add_chat("Please, don't let the uruks beat me again!");
    add_chat("Where are the riders of Rohan? Why do they not rescue us?");
    add_chat("I overheard the guards talking last night. The King of "
        + "the Golden Hall is in for a fight, that much is certain.");
    add_chat("We won't go down without a fight!");
    add_chat("I killed three orcs during the uprising. I'll kill many "
        + "more before this day is through.");
    add_chat("We busted up the prison pretty good. They may kill us all, "
        + "but it will be some time before they repair it enough to hold "
        + "new prisoners!");
    add_chat("This place is a nightmare. Even death is more welcome than "
        + "another day in bondage here.");
    add_chat("I am so hungry, but not hungry enough to take meat handed "
        + "down from an orc.");
    add_chat("The fleas and vermin I can take, but the stench of those "
        + "filthy drooling goblins is unbearable.");
    add_chat("I hope at least one of us can escape to warn the King of "
        + "Rohan.");
    add_chat("Do you have any food, stranger? I have not eaten in weeks.");
    add_chat("The uruks bled this morning, oh yes.");
    add_chat("Saruman is a traitor! Someone must warn Rohan!");


    set_cchat_time(5 + random(10));
    add_cchat("What kind of gutless coward would attack starving prisoners?");
    add_cchat("Die, foul villain!");
    add_cchat("I have nothing to lose. I will gladly die to send your "
        + "black heart to the grave!");
    add_cchat("Your body will rot in this stinking prison.");
    add_cchat("You should not have come here, fool!");
    add_cchat("Help! Foe! Help!");

    set_act_time(15 + random(15));	
    add_act("sigh");
    add_act("worry");
    add_act("pace");
    add_act("fidget");		
    add_act("frown");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("emote shouts for help."); 
    add_cact("growl"); 
    add_cact("frown"); 
    add_cact("cry"); 

    return 1;
}


int
special_attack(object victim)
{
    int     result,
            er,
            wr;
    mixed   hr = ({ -1, 0, 0, 0 });
    string  wmsg = 0,
            vmsg,
            he = TO->query_pronoun(),
            his = TO->query_possessive(),
            vhim = victim->query_objective(),
            vhis = victim->query_possessive();
    string  vphrase, wphrase;

    remove_prop(LIVE_I_ATTACK_DELAY);

    if (random(100) > punch_rate)
        return 0;

    // check if we hit

    result = resolve_task(PUNCH_TASK, PUNCH_SKILLS,
        victim, PUNCH_VICTIM_SKILLS);

    er = (100 - ((2*victim->query_encumberance_weight() +
                    victim->query_encumberance_volume())/3));
    wr = (100 * query_prop(OBJ_I_WEIGHT)) / victim->query_prop(OBJ_I_WEIGHT);
    result += (100 * (wr - er)) / PUNCH_TASK;

    if (result <= 0)
        add_attack_delay(MIN(5, -result/5 + 1), 1);
    else
    {
        if (result < 10)
            result = 10;
        else if (result > 90)
            result = 90;
        hr = victim->hit_me(F_PENMOD(PUNCH_PEN, result), W_BLUDGEON, TO, A_R_FIST);
    }

    switch(random(6))
    {
        case 0:
            vphrase = " feints to the left ";
            wphrase = " glares with calculation at ";
            break;
        case 1:
            vphrase = " feints to the right ";
            wphrase = " stares balefully at ";
            break;
        case 2:
            vphrase = " crouches down low ";
            wphrase = " screams incoherently at ";
            break;
        case 3:
            vphrase = " leaps into the air ";
            wphrase = " curses silently at ";
            break;
        case 4:
            vphrase = " springs into a fighting stance ";
            wphrase = " gestures threateningly at ";
            break;
        case 5:
            vphrase = " ponders the situation carefully ";
            wphrase = " sneers disdainfully at ";
            break;
        default:
            break;
    }

    switch(hr[0])
    {
        case -1:
            vmsg = " crashes into the wall! " + CAP(he) + " shakes "
                + his + " head and resumes a fighting stance.";
            break;
        case 0..4:
            vmsg = " rakes your eyes with " + his + " fingernails.";
            wmsg = " rakes " + vhis + " eyes with " + his + " fingernails.";
            break;
        case 5..9:
            vmsg = " punches you in the stomach.";
            wmsg = " punches " + vhim + " in the stomach.";
            break;
        case 10..19:
            vmsg = " kicks you in the " + hr[1] + ".";
            wmsg = " kicks " + vhim + " in the " + hr[1] + ".";
            break;
        case 20..34:
            vmsg = " manages to bite your " + hr[1] + ".";
            wmsg = " manages to bite " + vhis 
                + " " + hr[1] + ".";
            break;
        case 35..49:
            vmsg = " rips the flesh away from your " + hr[1] + ".";
            wmsg = " rips the flesh away from " + vhis + " " + hr[1] + ".";
            break;
        case 50..59:
            vmsg = " nearly shatters your jaw.";
            wmsg = " nearly shatters " + vhis + " jaw.";
            break;
        case 60..79:
            vmsg = " slams you against the wall with a skull-numbing crunch.";
            wmsg = " slams " + vhim + " against the wall with a skull-numbing "
                + "crunch.";
            break;
        case 80..99:
            vmsg = " smashes your head repeatedly into the stone floor.";
            wmsg = " smashes " + vhis + " head repeatedly into the stone "
                + "floor.";
            break;
        default:
            vmsg = " grabs your head and twists hard. Everything goes numb "
                + "as you feel your neck snap.";
            wmsg = " grabs " + vhis + " head and twists hard. You cringe "
                + "as you hear the neck snap.";
            break;
    }

    if (!strlen(wmsg))
        wmsg = vmsg;
    victim->catch_msg("The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + vphrase + "and" 
        + vmsg + "\n");
    tell_watcher("The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + wphrase 
        + QTNAME(victim) + "," + vphrase + "and" + wmsg + "\n", TO, victim);

    if (victim->query_hp() <= 0)
        victim->do_die(TO);
    return 1;
}


public int
remove_prisoner()
{
    TO->remove_object();
    return 1;
}


public int
remove_func()
{
    tell_room(environment(TO), "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " runs quickly away to alert the other "
        + "prisoners of danger.\n", ({TO}));

    TO->move_living("M", IGARD_ROOM + "temp_location", 1, 0);

    set_alarm(10.0, 0.0, &remove_prisoner());
    return 1;
}

