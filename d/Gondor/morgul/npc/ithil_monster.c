/*
 * This file is /d/Gondor/morgul/npc/ithil_monster.c
 *
 * some routines follow /doc/examples/mobiles/troll.c
 *
 * Olorin, 14-jul-1993
 * Removed unarmed combat - Dunstable Feb 94
 * Removed LIVE_O_ENEMY_CLING, added do_follow trigger
 *   - Olorin, 2-nov-1994
 * Replaced trigger by specialized catch_all()
 *   - Olorin, 3-feb-1995
 * General revision, Olorin, Feb 1996
 * Replaced catch_all() by follow_shadow.c
 *   - Gnadnar, 3-jun-1998
 * Fixed a runtime err in check_armours()
 *   - Gnadnar, 9-oct-1998
 * Don't break our own weapons if disarmed by brawl.
 * Added uniqueness check for black platemails.
 *   - Stern, 22-apr-2000
 * Allowed for mages to give items to the NPC, which
 * they will then use if better.
 *   - Eowul, 11-apr-2009
  * Morgul Mage robes will no longer be broken if another robe is dropped
 *   - Gorboth, 25-apr-2012
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/morgul/feeling.c";
inherit "/lib/unique.c";

#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/orcmace",MORGUL_DIR + "obj/stabsword"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/blackcap", MORGUL_DIR + "obj/ltunic"}) 
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/mailcoat"})
#define ARM_ARRAY3 ({ })

#define ITHIL_I_KILLS	"_ithil_i_kills"
#define SEQ_PICK        "_mon_pick"

// Prototypes:
void    help_friend(object ob, object friend);
void    test_can_see(object victim);
mixed   accept_from_mage_only();

// Global variables:
static  int     Attack_Alarm,
                Wimpy_Run;
static  object  Victim;
static  string *Wep1,
               *Wep2,
               *Arm1,
               *Arm2,
               *Arm3;

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
create_ithil_monster()
{
    set_race_name("human");
}

nomask void
create_monster()
{
    int rnd     = random(11);

    seteuid(getuid(TO));
    add_name("_morgul_monster");
    add_name("_ithil_monster");

    set_skill(SS_AWARENESS,    55+rnd);
    set_skill(SS_CLIMB,        25+rnd);
    set_skill(SS_BLIND_COMBAT, 80+rnd);

    set_skill(SS_WEP_SWORD,   30);
    set_skill(SS_WEP_POLEARM, 30);
    set_skill(SS_WEP_AXE,     30);
    set_skill(SS_WEP_KNIFE,   30);
    set_skill(SS_WEP_CLUB,    30);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK,   2);
    add_prop(MORGUL_I_SULAMBAR_RES, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, accept_from_mage_only);

    set_whimpy(45);
    set_wimpy_run(20);

    set_learn_pref( ({ 1, 1, 1, 0, 0, 1, }) );

    set_pick_up(75);

    create_ithil_monster();
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

static void
get_money() 
{
   MONEY_MAKE_CC( 10 + random(11))->move(TO);
   MONEY_MAKE_SC(  1 + random( 6))->move(TO);
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
   
   set_arm_arrays();
   
   seteuid(getuid(TO));
   
   if (is = sizeof(Wep1))
   {
      iw = random(is);
      clone_object(Wep1[iw])->move(TO);
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
      if (Arm2[iw] == MORGUL_DIR + "obj/platemail_unique")
      {
          clone_unique(MORGUL_DIR + "obj/platemail_unique", 5, 
                      MORGUL_DIR + "obj/normalplate")->move(TO);
      }
      else
      {
          clone_object(Arm2[iw])->move(TO);
      }
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
    get_money();
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
    start_follow(ob);
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

    start_follow(ob);

    while (!room->query_prop(ROOM_I_IS))
	room = ENV(room);
    arr = filter(all_inventory(room), &->id("_morgul_monster"));
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
      command("shout Where are the enemies? I can't see them!");
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
	arr = filter(all_inventory(ENV(TO)), &->id("_morgul_monster")) - ({ TO });
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
       command("shout You will die for this, stinking " + ob->query_race_name() + "!");
       command("kill "+ob->query_real_name());
   }
}

string
alignlook() 
{
   string *alignlooks = ({"grim", "grumpy", "cruel", "angry", "beastly",
       "mean", "dirty", "foul", "brutal", "battered", "sinister",
       "wicked","evil","savage", "ugly", "fierce","dangerous"});
   return ONE_OF_LIST(alignlooks);
}

void
disguise_msg(object player, object helm, object robe)
{
   if (!present(player, ENV(TO)))
       return;
   player->catch_msg(BSN(
       "The "+query_nonmet_name()+" peers suspiciously at you, but "
     + "since you are wearing the " + robe->query_short() + " and the "
     + helm->query_short() + " bearing the coat of Morgul, "
     + query_pronoun()+ " doesn't attack you."));
}

int
query_disguised(object player)
{
   object helm, robe, arm, enemy;
   
   if (!objectp(player))
      player = TP;
   if (player->query_npc())
      return 1;
   if (objectp(enemy = player->query_attack()) && enemy->id("_morgul_monster"))
      return 0;
   helm = player->query_armour(TS_HEAD);
   robe = player->query_armour(TS_ROBE);
   arm = player->query_armour(TS_TORSO);
   if ((objectp(helm) && helm->id("_ithil_armour")) &&
       ((objectp(robe) && robe->id("_ithil_armour")) ||
        (objectp(arm) && arm->id("_ithil_armour"))))
   {
       // Don't swamp the player in messages!
       if (!random(5))
       {
	   if (!objectp(robe) || !robe->id("_ithil_armour"))
	       robe = arm;
	   set_alarm(2.0, 0.0, &disguise_msg(player, helm, robe));
       }
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
       (((query_feeling(player) > -1) &&
         !query_disguised(player)) ||
        (objectp(attacker = player->query_attack()) &&
         attacker->id("_morgul_monster"))))
   {
       /* give player (or this npc) time to arrive before attack */
	/* olorin warns that any delay here at all will allow the player
	 * to run thru to safety -- "even an alarm of 0 may be too slow".
	 * try this for now, while i look for a better way to handle
	 * the attacks -- gnadnar
	 */
       set_alarm(0.0, 0.0, &do_attack(player));
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
    log_file("evilkill", player->query_name()+" ("+player->query_average_stat()+
	     ") was killed by "+ TO->query_name()+" on "+ctime(time())+" ("+
	     file_name(ENV(TO)) + ").\n");
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

private void report_break_action(object ob)
{
    tell_room(environment(this_object()),
        QCTNAME(TO) + " breaks the " + ob->short() + " with a "
	    + "malicious grin.\n");

}

public void
remove_surplus(object ob)
{
    if (!objectp(ob))	/* added to fix errs in debug log -- gnad */
        return;
    if (function_exists("create_heap", ob) == COINS_OBJECT)
    {
	command("smile greedily");
	return;
    }
    if (ob->query_prop(HEAP_I_IS))
	return;
    // We do not destroy items cloned into this room:
    if (member_array(ob, ENV(TO)->query_cloned_here()) > -1)
	command("drop " + OB_NAME(ob));
    else
    {
        report_break_action(ob);
        set_alarm(0.0, 0.0, &ob->remove_object());
    }
}

object
query_max_ithil()
{
    int     max_hp = 0,
            hp,
            nmi = -1,
            i;
    object *arr;

    arr = filter(all_inventory(ENV(TO)), &->id("_morgul_monster"));

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
    object  max_ithil,
           *enemies; 


    if ( (100*hp/mhp) > Wimpy_Run)
    {
        if (objectp(max_ithil = query_max_ithil()))
        {
            enemies = filter(query_enemy(-1), query_attack_me);
            max_ithil->remove_prop(OBJ_M_NO_ATTACK);
            map(enemies, "move_attack", TO, max_ithil);
            tell_room(ENV(TO), 
                QCTNAME(TO)+" cowardly hides behind "
              + QTNAME(max_ithil)+".\n", ({ TO, max_ithil, }) );
            enemies->catch_msg("You turn to attack "+QTNAME(max_ithil)+".\n");
            add_prop(OBJ_M_NO_ATTACK, 
                "@@query_is_behind" + ":" + file_name(TO)
                                    + "|" + file_name(max_ithil) + "@@");
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

    return process_string("The coward is hiding behind the "
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
        killer->add_prop(ITHIL_I_KILLS, kills =
            (killer->query_prop(ITHIL_I_KILLS) + 1));
    
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
    
    report_break_action(shields[0]);
    shields[0]->remove_broken();
    command("drop " + OB_NAME(shields[0]));

    if (sizeof(shields) > 1)
	set_alarm(5.0, 0.0, check_shields);
}

private void return_item_to_mage(object ob, object mage)
{
    command("give " + OB_NAME(ob) + " to " + OB_NAME(mage));
    command("say to " + OB_NAME(mage) + " I do not need "
        + LANG_ADDART(ob->short()) + ", my Liege.");
    command("drop " + OB_NAME(ob));
}

public void
check_weapons(object new, object from)
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
        if (IS_MORGUL_MAGE(from)) {
            return_item_to_mage(new, from);
            return;
        }

        report_break_action(new);
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
    
    if ((old[0] == new) && IS_MORGUL_MAGE(from)) {
        return_item_to_mage(new, from);
        return;
    }

    report_break_action(old[0]);
    old[0]->remove_broken();
    command("drop " + OB_NAME(old[0]));
}

public void
check_armours(object new, object from)
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

    /*
     * Apparently, players had figured out that if they dropped a robe
     * at the foot of a Morgul Mage npc, the morgul mage npc would break
     * their own robe as a result, making it very easy to kill them.
     * Lets put a stop to that. (Gorboth, April 2012)
     */
    if (old->id("Morgul_Spell_Object"))
    {
        command("say Pathetic fool! Did you expect me to fall for this"
          + " old trick? Get out of my sight!");

        return;
    }
    
	// This might happen if we are wielding a two handed
	// weapon, discard the new armour:
    report_break_action(new);
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
    
    if ((old == new) && IS_MORGUL_MAGE(from)) {
        return_item_to_mage(new, from);
        return;
    }
    
    /*
     * Break what we cannot use any more:
     */
    report_break_action(old);
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
	    set_alarm(1.0, 0.0, &check_weapons(ob, from));
        return;
    }

    if (function_exists("create_object", ob) == ARMOUR_OBJECT)
    {
        set_alarm(1.0, 0.0, &check_armours(ob, from));
        return;
    }

    if ((query_encumberance_weight() > 25) ||
        (query_encumberance_volume() > 25))
    {
        set_alarm(1.0, 0.0, &remove_surplus(ob));
    }
}

public mixed accept_from_mage_only()
{
    if (IS_MORGUL_MAGE(this_player())) return 0;
    return " doesn't accept any gifts from you.\n";

}

