/*
 *  Created by Igneous (a.k.a. Chad Richardson)
 *
 *  June 1998
 */

#pragma strict_types
#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include "trickster.h"
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>
#include <wa_types.h>
#include <tasks.h>
#include <formulas.h>
#include <ss_types.h>
#include <language.h>
#include SKILLS_FILE

inherit "/cmd/std/command_driver";

#ifndef NO_TRICKSTER_SHINKICK
#define SHINKICK_PREP_TIME     3
#define SHINKICK_DELAY_TIME    12
#define SHINKICK_PREPARE       "_Shire_i_prepare_shinkick"
#define SHINKICK_DELAY         "_Shire_i_delay_between_shinkicks"
#endif

public mapping
query_trickster_abilities()
{
    return ([
#ifndef NO_TRICKSTER_SHINKICK
      "shinkick"     :   "shinkick",
#endif
#ifndef NO_TRICKSTER_MISCHIEF
      "inspect"      :   "inspect",
      "itchpowder"   :   "itchpowder",
      "laughgas"     :   "laughgas",
      "smokebomb"    :   "smokebomb",
      "sneezepowder" :   "sneezepowder",
      "stinksplash"  :   "stinksplash",
#endif
      "sneaky"       :   "do_sneaky"
    ]);
}

/*************************TRICKSTER SHINKICK********************************/

/* 
 *  Trickster Shinkick combat attack.
 *  combat aid (1.0 / 3.0) * (251.0 / 280.0) = 29.88%
 *  or 4.98% tax.  
 *  Reduced to 2.5% tax because 
 *  1) Based off a skill and we are allowed up to a 50% reduction
 *  2) Uses cb_tohit to see if we make contact
 *  3) Unable to do a shinkick on non-humanoid creatures.
 */

#ifndef NO_TRICKSTER_SHINKICK

/* Function:    get_leg_desc
 * Description: Get a description of what the trickster hit with his
 *              Shinkick.
 * Arguments:   player: Player who we are interested in.
 * Returns:     What the trickster hit with his shinkick.
 */
string
get_leg_desc(object player)
{
    object armour;

    if (!objectp(armour = player->query_armour(TS_LEGS)))
	return (random(2) ? "right" : "left" ) + " shin";

    return armour->short();
}

/* Function:    do_shinkick
 * Description: If all conditions are passed in order to do a shinkick
 *              this function is called. It takes care of damaging the
 *              the player's enemy and the messages of the attack.
 * Arguments:   player: Player doing the shinkick
 *              enemy:  The enemy or target we are doing the shinkick on
 * Returns:     nothing.
 */
void
do_shinkick(object player, object enemy)
{
    int hit, pen, skill;
    mixed hit_res;
    string *how = allocate(3), what;

    skill = player->query_skill(SS_SHINKICK);
    hit = W_HAND_HIT + F_UNARMED_HIT(skill, player->query_stat(SS_DEX));
    hit = (3 * hit / 2) + (player->query_stat(SS_LAYMAN) / 10);
    if (player->query_combat_object()->cb_tohit(-1, hit, enemy) > 0)
    {
	pen = W_HAND_PEN + F_UNARMED_PEN(skill, player->query_stat(SS_STR));
	pen += player->query_stat(SS_LAYMAN) / 10;
	pen = F_PENMOD(pen, skill);
	hit_res = enemy->hit_me(pen, W_BLUDGEON, player, -1, TS_LEGS);
	what = get_leg_desc(enemy);
	switch (hit_res[0])
	{
	case -1:
	    // We stubbed our toe badly!
	    player->reduce_hit_point(MAX(10, F_DAMAGE( 
		  random(enemy->query_armour(A_LEGS)->query_ac()),
		  random(player->query_armour(A_FEET)->query_ac()))));
	    how[0] = "Your shinkick failed miserably and you bruise your "+
	    "toe on "+LANG_POSS(enemy->query_the_name(player))+" "+
	    what+", causing you to wince in pain.";
	    how[1] = LANG_POSS(player->query_The_name(enemy)) +" shinkick "+
	    "strikes your "+what+", leaving "+HIM_HER(player)+" wincing "+
	    "in pain from the poorly aimed kick.";
	    how[2] = LANG_POSS(QCTNAME(player)) +" shinkick strikes "+
	    LANG_POSS(QTNAME(enemy))+" "+what+" causing "+QTNAME(player)+
	    " to wince in pain."; 
	    break;
	case 0:
	    // We stubbed our toe!
	    player->reduce_hit_point(MAX(5, F_DAMAGE(
		  random(enemy->query_armour(A_LEGS)->query_ac()),
		  random(player->query_armour(A_FEET)->query_ac()))));
	    how[0] = "You stub your toe on "+
	    LANG_POSS(enemy->query_the_name(player))+" "+what+" in a "+
	    "failed attempt to give "+HIM_HER(enemy)+" a shinkick.";
	    how[1] = player->query_The_name(enemy) +" stubs "+
	    HIS_HER(player)+ " toe on your "+what+" in a failed attempt "+
	    "to kick at it."; 
	    how[2] = QCTNAME(player) +" stubs "+ HIS_HER(player)+ 
	    " toe on "+LANG_POSS(QTNAME(enemy))+" "+ what + " in a "+
	    "failed attempt at a shinkick."; 
	    break;
	case 1..10:
	    how[0] = "Your shinkick barely connects with "+
	    LANG_POSS(enemy->query_the_name(player))+" "+what+
	    " hurting "+HIM_HER(enemy)+" slightly.";
	    how[1] = player->query_The_name(enemy) +" barely connects "+
	    " with your "+what+" with "+HIS_HER(player)+" shinkick "+
	    "hurting you slightly.";
	    how[2] = LANG_POSS(QCTNAME(player)) +" shinkick barely connects "+
	    "with "+LANG_POSS(QTNAME(enemy))+" "+what+" hurting "+
	    QTNAME(enemy) +" slightly.";
	    break;
	case 11..20:
	    how[0] = "You connect with "+
	    LANG_POSS(enemy->query_the_name(player))+" "+what+" with "+
	    "your shinkick, causing "+HIM_HER(enemy)+" a little "+
	    "discomfort.";
	    how[1] = player->query_The_name(enemy)+" connects with your "+
	    what +" with "+HIS_HER(player)+" shinkick, causing you "+
	    "a little discomfort.";
	    how[2] = QCTNAME(player)+ " connects with "+
	    LANG_POSS(QTNAME(enemy))+ " " +what+" with "+HIS_HER(player)+
	    " shinkick, causing "+QTNAME(enemy)+" a little discomfort."; 
	    break;
	case 21..35:
	    how[0] = "Your shinkick connects heavily with "+
	    LANG_POSS(enemy->query_the_name(player))+" "+what+" causing "+
	    HIM_HER(enemy) + " to wince in pain.";
	    how[1] = LANG_POSS(player->query_The_name(enemy)) +
	    " shinkick connects heavily with your "+what+" causing you "+
	    "to wince from the pain.";
	    how[2] = LANG_POSS(QCTNAME(player)) +" shinkick connects "+
	    "heavily with "+LANG_POSS(QTNAME(enemy))+" "+what +" causing "+
	    HIM_HER(enemy)+" to wince in pain.";
	    break;
	case 36..40:
	    how[0] = "Your shinkick strikes "+
	    LANG_POSS(enemy->query_the_name(player)) +" "+ what +" with "+
	    "some force, leaving behind a slight bruise on "+
	    HIS_HER(enemy)+ " leg.";
	    how[1] = LANG_POSS(player->query_The_name(enemy))+" shinkick "+
	    "strikes your "+what+" with some force, leaving behind "+
	    "a slight bruise on your leg.";
	    how[2] = LANG_POSS(QCTNAME(player))+" shinkick strikes "+
	    LANG_POSS(QTNAME(enemy))+" "+what+" with some force, "+
	    "leaving behind a slight bruise on "+HIS_HER(enemy)+" leg.";
	    break;
	case 41..60:
	    how[0] = "Your shinkick hits "+
	    LANG_POSS(enemy->query_the_name(player)) + " " + what + 
	    " with painful accuracy, creating a deep bruise on "+
	    HIS_HER(enemy)+" leg."; 
	    how[1] = LANG_POSS(player->query_The_name(enemy))+" shinkick "+
	    "hits your "+what+" with painful accuracy, creating "+
	    "a deep bruise on your leg.";
	    how[2] = LANG_POSS(QCTNAME(player))+" shinkick hits "+
	    LANG_POSS(QTNAME(enemy))+" "+what+" with painful accuracy, "+
	    "creating a deep bruise on "+HIS_HER(enemy)+" leg.";
	    break;
	case 61..85:
	    how[0] = "A well aimed shinkick strikes "+
	    LANG_POSS(enemy->query_the_name(player))+" "+what+", yielding "+
	    "a deep, painful bruise on "+HIS_HER(enemy)+" leg!";
	    how[1] = LANG_POSS(player->query_The_name(enemy))+" well aimed "+
	    "shinkick strikes your "+what+", yielding a deep, painful "+
	    "bruise on your leg.";
	    how[2] = LANG_POSS(QCTNAME(player))+" well aimed shinkick "+
	    "strikes "+LANG_POSS(QTNAME(enemy))+" "+what+", yielding "+
	    "a deep, painful bruise on "+HIS_HER(enemy)+" leg.";
	    break;
	default: 
	    how[0] = "You hear a loud crack as your shinkick strikes "+
	    LANG_POSS(enemy->query_the_name(player)) +" "+what+".  "+
	    enemy->query_The_name(player) +" yelps in pain as your "+
	    "powerful kick seems to have cracked a bone!";
	    how[1] = "You hear a loud crack as "+
	    LANG_POSS(player->query_the_name())+" shinkick strikes your "+
	    what +".  You yelp out in pain as you realise that the force "+
	    "of the shinkick has cracked a bone!";
	    how[2] = "You hear a loud crack as "+LANG_POSS(QTNAME(player))+
	    " strikes "+LANG_POSS(QTNAME(enemy))+" "+what+".  "+
	    QCTNAME(enemy)+" yelps in pain as "+HE_SHE(enemy)+" feels the "+
	    "pain from the bone cracking shinkick!";
	    break;
	}
	player->catch_tell(how[0] +"\n");
	if (player->query_wiz_level())
	    player->catch_tell("PEN: "+pen+"  DAMAGE:  "+hit_res[3]+".\n");
	if (interactive(enemy))
	    enemy->catch_tell(how[1] +"\n");
	player->tell_watcher(how[2] + "\n", enemy);
	if (enemy->query_hp() < 1)
	    enemy->do_die(player);
	// Because we can stub our toes, we can kill ourselves!
	if (player->query_hp() < 1)
	    player->do_die(enemy);
    }
    else
    {
	player->catch_tell("You miss "+enemy->query_the_name(player)+
	  " completely with your shinkick!\n");
	enemy->catch_tell("You deftly avoid "+
	  LANG_POSS(player->query_the_name(enemy))+" attempt to kick "+
	  "your shin.\n");
	player->tell_watcher_miss(QCTNAME(enemy) +" deftly avoids "+
	  LANG_POSS(QTNAME(player))+" attempt to kick "+HIS_HER(enemy)+
	  " shin.\n", ({enemy}));
    }
    //  Doing a shinkick is tiresome
    player->add_fatigue(-5);
}

/* Function name: ready_to_shinkick
 * Description:   Notifies a player that they are able to attempt
 *                another shinkick.
 */
void
ready_to_shinkick(object player)
{
    player->remove_prop(SHINKICK_DELAY);
    player->catch_tell("You are ready to try and shinkick your opponent "+
      "once again.\n");
}

/* Function name: secondary_checks
 * Description:   Does all the checks before we execute a shinkick
 *                to see if we are still able to preform a shinkick.
 * Arguments:     player:  The player attempting the shinkick
 *                enemy:   The target of the shinkick
 */
void
secondary_checks(object player, object enemy)
{
    if (!objectp(player))
	return;

    player->remove_prop(SHINKICK_PREPARE);
    if (!objectp(enemy) || !present(enemy, ENV(player)))
    {
	player->catch_tell("Your target seems to have escaped you.\n");
	return;
    }
    if (ENV(player)->query_prop(ROOM_I_TYPE, ROOM_UNDER_WATER))
    {
	player->catch_tell("The aquatic environment renders your "+
	  "shinkick useless.\n");
	return;
    }

    if (enemy->query_prop(OBJ_M_NO_ATTACK) ||
      ENV(player)->query_prop(ROOM_M_NO_ATTACK))
    {
	player->catch_tell("Peacefull surroundings prevent you "+
	  "from completing your shinkick.\n");
	return;
    }
    if (player->query_prop(LIVE_I_STUNNED) || 
      player->query_prop(LIVE_I_ATTACK_DELAY))
    {
	player->catch_tell("You are too stunned to shinkick at the moment.\n");
	return;
    } 
    if (enemy->query_ghost())
    {
	player->catch_tell(enemy->query_The_name(player) +" is quite dead "+
	  "already.\n");
	return;
    }
    player->reveal_me(1);
    if (player->query_attack() != enemy)
    {
	if (!CAN_SEE_IN_ROOM(player) || !CAN_SEE(player, enemy))
	{
	    player->catch_tell("You are unable to see your target anymore so "+
	      "you abandon your shinkick.\n");
	    return;
	}
	player->command("$tgrin at "+OB_NAME(enemy));
	player->catch_tell("You attack "+enemy->query_the_name(player)+"!\n");
	enemy->catch_tell(player->query_The_name(enemy)+" attacks you!\n");
	tell_room(ENV(player), QCTNAME(player)+" attacks "+
	  QTNAME(enemy)+"!\n", ({player, enemy}));
	player->attack_object(enemy);
    } 
    if (enemy->query_prop(LIVE_I_NO_BODY))
    {
	player->catch_tell("Your kick passes right through "+
	  LANG_POSS(enemy->query_the_name(player))+ " legs!\n");
	return;
    }
    if (player->query_fatigue() <= 5)
    {
	player->catch_tell("You are too tired to complete your shinkick.\n");
	return;
    }
    player->add_prop(SHINKICK_DELAY, 1);
    set_alarm(itof(SHINKICK_DELAY_TIME), 0.0, &ready_to_shinkick(player));
    do_shinkick(player, enemy);
}

/* Function name: shinkick
 * Description:   Used to find out who the target of this shinkick is.
 * Arguments:     str:  The string (if any) we use to find our target
 * Returns:       1/0
 */
int
shinkick(string str)
{
    object enemy, *oblist;

    if ((!stringp(str) || !strlen(str)) && !TP->query_attack())
    {
	notify_fail("Shinkick whom?\n");
	return 0;
    }
    if (TP->query_prop(SHINKICK_DELAY))
    {
	notify_fail("You have not recovered from your last shinkick.\n");
	return 0;
    }

    if (TP->query_prop(SHINKICK_PREPARE))
    {
	notify_fail("You are already preparing a shinkick.\n");
	return 0;
    }

    if (TP->query_prop(LIVE_I_STUNNED) || TP->query_prop(LIVE_I_ATTACK_DELAY))
    {
	notify_fail("You are too stunned to shinkick at the moment.\n");
	return 0;
    } 
    if (str)
    {
	if (!sizeof(oblist = parse_this(str, "[on] [the] %l")))
	{   
	    notify_fail("There is no "+str+" here to give a shinkick to.\n");
	    return 0;
	}

	if (sizeof(oblist) != 1)
	{
	    notify_fail("You can only kick one person in the shin at a time!\n");
	    return 0;
	}
	enemy = oblist[0];
    }
    else
	enemy = TP->query_attack();

    if (!objectp(enemy))
    {
	notify_fail("Shinkick whom?\n");
	return 0;
    }
    if (!F_DARE_ATTACK(TP, enemy))
    {
	notify_fail("You don't feel confident enough to give "+
	  enemy->query_the_name(TP)+" a shinkick.\n");
	return 0;
    }
    if (!enemy->query_humanoid())
    {
	NF("You wouldn't know where to give "+
	  enemy->query_the_name(TP) +" a good shinkick because "+
	  " of "+HIS_HER(enemy)+" non-humanoid nature.\n");
	return 0;
    }
    if (enemy->query_not_attack_me(TP, -1))
    {
	notify_fail("");
	return 0;
    }
    if (!objectp(TP->query_attack()) && TP->query_met(enemy) &&
      TP->query_prop(LIVE_O_LAST_KILL) != enemy)
    {
	notify_fail("Shinkick "+enemy->query_the_name(TP)+"??  You sure "+
	  "about that?\n");
	TP->add_prop(LIVE_O_LAST_KILL, enemy);
	return 0;
    }
    TP->add_prop(SHINKICK_PREPARE, 1);
    write("You concentrate on giving "+enemy->query_the_name(TP)+" a shinkick.\n");
    set_alarm(itof(SHINKICK_PREP_TIME), 0.0, &secondary_checks(TP,enemy));
    return 1;
}

#endif
/***************************************************************************/


/**************************TRICKSTER MISCHIEF*******************************/

/*   Trickster Mischief Ability code  
 *   Taxed 1% for the smokebomb since it creates a small period
 *   of mulitple level darkness.
 */

#ifndef NO_TRICKSTER_MISCHIEF
int
inspect(string str)
{
    if (str != "stick")
    {
	notify_fail("Inspect your stick moron!\n");
	return 0;
    }
    all(" inspects "+HIS_HER(TP)+" large stick carefully.");
    write("You inspect your stick trying to figure out what you "+
      "have stored in it.\n"+
      "There are "+TP->query_charge(0)+" sneezing powders in your stick.\n"+
      "There are "+TP->query_charge(1)+" itching powders in your stick.\n"+
      "There are "+TP->query_charge(2)+" smokebombs in your stick.\n"+
      "There are "+TP->query_charge(3)+" stinking liquids in your stick.\n"+
      "There are "+TP->query_charge(4)+" laughing gas vials in your stick.\n"+
      "\n");
    return 1;
}

int
itchpowder(string who)
{
    object   itch, *oblist;
    int  index = 1,
    guildstat, targetaware;

    if (!strlen(who))
    {
	NF("Who are you trying to make itchy?\n");
	return 0;
    }
    if (!sizeof(oblist = parse_this(who, "[at] %l")))
    {
	// No players... maybe we tried a piece of armour
	if (!sizeof(oblist = FIND_STR_IN_OBJECT(who, TP)))
	{
	    NF("There is no " +who+ " here to make all itchy!\n");
	    return 0;
	}
    }

    if (TP->query_charge(index) == 0)
    {
	NF("You don't have any itching powder in your stick to use!.\n");
	return 0;
    }

    if (sizeof(oblist) != 1)
    {
	NF("Silly, you can only give make one thing itchy at a time!\n");
	return 0;
    }

    if (!living(oblist[0])) // must be a piece of armour we are trying.
    {
	if (!function_exists("create_armour",oblist[0]))
	{
	    notify_fail("You must place the itching powder on armours!\n");
	    return 0;
	}
	if (oblist[0]->query_worn())
	{
	    notify_fail("You have to remove that "+who+" first before you "+
	      "can put itching powder in it.\n");
	    return 0;
	}
	if (oblist[0]->query_trickster_shadow() == 666)
	{
	    notify_fail("There seems to be a trick already being played "+
	      "on the "+oblist[0]->short()+".\n");
	    return 0;
	}
	//  Okie we have an armour so infect it
	write("You lace the "+oblist[0]->short()+" with itching powder.\n");
	say(QCTNAME(TP)+" does something to the "+oblist[0]->short()+"!\n");
	guildstat = TP->query_stat(SS_LAYMAN);
	setuid(); seteuid(getuid());
	clone_object(TRICK_ARMOUR)->shadow_me(oblist[0]);
	oblist[0]->set_trap_qual(guildstat/15);
	oblist[0]->set_trap_setter(TP->query_real_name());
	oblist[0]->set_trap_type("itch");
	oblist[0]->set_up_trap();
	TP->remove_charge(index);
	return 1;
    }
    guildstat = TP->query_stat(SS_LAYMAN);
    targetaware = oblist[0]->query_skill(SS_AWARENESS);

    target(" bonks you on the head with "+HIS_HER(TP)+" large stick!",oblist);
    if ((guildstat - random(60)) < targetaware)
    {
	oblist[0]->catch_msg("You feel a slight tingle as the large stick "+
	  "hits your head as if something was left there.\n");
    }
    actor("You bonk",oblist," on the head with "+
      "your large stick in such a way that it releases some itching "+
      "powder on "+HIS_HER(oblist[0])+" scalp.");
    all2act(" bonks",oblist," on the " +
      "head with "+HIS_HER(TP)+" large stick!");
    setuid(); seteuid(getuid());
    itch = clone_object(ITCH_OBJ);
    itch->move(oblist[0], 1);
    itch->start_itching(oblist[0] );
    TP->remove_charge(index);
    return 1;
}

int
laughgas()
{
    object   gas;
    int  index = 4;

    if (TP->query_charge(index) == 0)
    {
	NF("You have no laughing gas equiped in your stick!\n");
	return 0;
    }

    write("You fiddle around with your stick until you pry "+
      "a glass vial containing laughing gas from within a hole in "+
      "your stick.\nYou toss it towards the ground, and you better "+
      "run out of this room before you are effected by the gas!\n");
    all(" starts tinkering with "+HIS_HER(TP)+" large stick "+
      "and produces a small glass vial from it. "+CAP(HE_SHE(TP))+" grins "+
      "mischievously as "+HE_SHE(TP)+" throws it to the ground.");
    setuid(); seteuid(getuid());
    gas = clone_object(LAUGH_OBJ);
    gas->move(ENV(TP), 1);
    TP->remove_charge(index);
    return 1;
}

int
smokebomb()
{
    object  bomb;
    int  index = 2;

    if (TP->query_charge(index) == 0)
    {
	NF("You have no smoke bombs to toss!\n");
	return 0;
    }
    write("You fiddle around with your stick until you pry "+
      "a smoke bomb from within a hole of your stick.\nYou promptly "+
      "throw the smoke bomb to the ground so you can make a hasty escape.\n");
    all(" starts fiddling with "+HIS_HER(TP)+" large stick "+
      "and produces a small glass bulb, which "+HE_SHE(TP)+" then quickly "+
      "throws to the ground, where it breaks on impact!");
    setuid(); seteuid(getuid());
    bomb = clone_object(SMOKE_OBJ);
    bomb->move(ENV(TP), 1);
    TP->remove_charge(index);
    return 1;
}

int
sneezepowder(string who)
{
    object  *oblist, sneeze;
    int  index = 0, guildstat;

    if (!strlen(who))
    {
	NF("Who do you wish to make sneeze?\n");
	return 0;
    }
    if (!sizeof(oblist = parse_this(who, "[at] %l")))
    {
	// No players... maybe we tried a piece of armour
	if (!sizeof(oblist = FIND_STR_IN_OBJECT(who, TP)))
	{
	    NF("There is no "+who+" here for you to throw that at!\n");
	    return 0;
	}
    }

    if (TP->query_charge(index) == 0)
    {
	NF("You have no sneezepowder to throw.\n");
	return 0;
    }
    if (sizeof(oblist) != 1)
    {
	NF("Silly, you can only blow sneeze powder in the face of "+
	  "more than one person.\n");
    }

    if (!living(oblist[0])) // must be a piece of armour we are trying.
    {
	if (!function_exists("create_armour",oblist[0]))
	{
	    notify_fail("You must place the sneezing powder on armours!\n");
	    return 0;
	}
	if (oblist[0]->query_worn())
	{
	    notify_fail("You can't put the sneezing powder in the "+
	      oblist[0]->short()+" since you are wearing it.\n");
	    return 0;
	}
	if (oblist[0]->query_at() != A_HEAD)
	{
	    notify_fail("Puting sneezing powder in armour that doesn't "+
	      "go on one's head seems rather pointless.\n");
	    return 0;
	}
	if (oblist[0]->query_trickster_shadow() == 666)
	{
	    notify_fail("There seems to be a trick already being played "+
	      "on the "+oblist[0]->short()+".\n");
	    return 0;
	}
	//  Okie we have an armour so infect it
	write("You lace the "+oblist[0]->short()+" with sneezing powder.\n");
	say(QCTNAME(TP)+" does something to the "+oblist[0]->short()+"!\n");
	guildstat = TP->query_stat(SS_LAYMAN);
	setuid(); seteuid(getuid());
	clone_object(TRICK_ARMOUR)->shadow_me(oblist[0]);
	oblist[0]->set_trap_qual(guildstat/15);
	oblist[0]->set_trap_setter(TP->query_real_name());   
	oblist[0]->set_trap_type("sneeze");
	oblist[0]->set_up_trap();
	TP->remove_charge(index);
	return 1;
    }
    actor("You tap your stick against your hand, emptying "+
      "sneezing powder into your hand...   As soon as you figure you "+
      "have enough powder, you throw it in the face of",oblist,"!");
    target(" starts to tap "+HIS_HER(TP)+" large stick "+
      "against "+HIS_HER(TP)+" hand.\nThen all of a sudden "+HE_SHE(TP)+
      " jerks "+HIS_HER(TP)+" hand and throws some strange powder "+
      "in your face!!",oblist);
    all2act(" starts to tap "+HIS_HER(TP)+" large stick "+
      "against "+HIS_HER(TP)+" hand.\nThen all of a sudden "+HE_SHE(TP)+
      " jerks "+HIS_HER(TP)+" hand and throws some strange powder in "+
      "the face of",oblist,"!!");
    setuid(); seteuid(getuid());
    sneeze = clone_object(SNEEZE_OBJ);
    sneeze->move(oblist[0], 1);
    sneeze->start_sneezing(oblist[0]);
    TP->remove_charge(index);
    return 1;
}

int
stinksplash(string who)
{
    int guildstat;
    object  *oblist, stink;
    int   index = 3;

    if (!strlen(who))
    {
	NF("Make who all stinky and smelly?\n");
	return 0;
    }

    if (!sizeof(oblist = parse_this(who, "[at] %l")))
    {
	// No players... maybe we tried a piece of armour
	if (!sizeof(oblist = FIND_STR_IN_OBJECT(who, TP)))
	{
	    NF("There is no "+who+" here for you to make all stinky!\n");
	    return 0;
	}
    }

    if (TP->query_charge(index) == 0)
    {
	NF("Curse the luck!  You are all out of stinky liquid!\n");
	return 0;
    }
    if (sizeof(oblist) != 1)
    {
	NF("Covering more than one thing with stinky liquid "+
	  "is a skill you haven't quite mastered yet.\n");
	return 0;
    }
    if (!living(oblist[0])) // must be a piece of armour we are trying.
    {
	if (!function_exists("create_armour",oblist[0]))  
	{
	    notify_fail("You must place the stinky liquid on armours!\n");
	    return 0;
	}
	if (oblist[0]->query_worn())
	{
	    notify_fail("You must remove the "+oblist[0]->short()+" first "+
	      "before you pour stinking liquid all over it.\n");
	    return 0;
	}
	if (oblist[0]->query_trickster_shadow() == 666)
	{
	    notify_fail("There seems to be a trick already being played "+
	      "on the "+oblist[0]->short()+".\n");
	    return 0;
	}
	//  Okie we have an armour so infect it
	write("You lace the "+oblist[0]->short()+" with stinking liquid.\n");
	say(QCTNAME(TP)+" does something to the "+oblist[0]->short()+"!\n");
	guildstat = TP->query_stat(SS_LAYMAN);
	setuid(); seteuid(getuid());
	clone_object(TRICK_ARMOUR)->shadow_me(oblist[0]);
	oblist[0]->set_trap_qual(guildstat/15);
	oblist[0]->set_trap_setter(TP->query_real_name());
	oblist[0]->set_trap_type("stink");
	oblist[0]->set_up_trap();
	TP->remove_charge(index);
	return 1;
    }


    actor("You remove a cork from your stick, revealing a small "+
      "hole containing a foul-smelling liquid.\nYou then swing your stick "+
      "at",oblist,", splashing "+HIM_HER(oblist[0])+" with the "+
      "stinking liquid.");
    target(" removes something from "+HIS_HER(TP)+
      " large stick, then swings the stick towards you!\nA foul liquid "+
      "is spewed forth from the stick and you are covered from head "+
      "to toe with it!",oblist);
    all2act(" removes something from "+HIS_HER(TP)+" large "+
      "stick, then swings the stick towards",oblist,
      " which releases a strange liquid which covers "+HIM_HER(oblist[0])+
      " from head to toe!");
    setuid(); seteuid(getuid());
    stink = clone_object(STINK_OBJ);
    stink->move(oblist[0] , 1);
    stink->start_stinking(oblist[0]);
    TP->remove_charge(index);
    return 1;
}
#endif
/***************************************************************************/

/*  Trickster auto-sneak code 
 *  Not taxed.
 *  Sets the members autosneak variable in the
 *  Trickster shadow.
 */

int
do_sneaky(string str)
{
    if ((str != "on") && (str != "constant") && (str != "off"))
    {
	TP->catch_msg("Sneaky how? on? off? constant?\n");
	return 1;
    }
    if (str == "off")
    {
	TP->set_sneaky(0);
	TP->catch_msg("You will be sneaky no longer.\n");
	return 1;
    }
    if (str == "on")
    {
	TP->set_sneaky(1);
	TP->catch_msg("You will not introduce yourself as a Trickster,"+
	  " nor will you look like one.\n");
	return 1;
    }
    if ((str == "constant") && (TP->query_autosneak()))
    {
	TP->catch_msg("You shall no longer constantly sneak around.\n");
	say(QCTNAME(TP)+" lets out a sigh as "+HE_SHE(TP)+" decides "+
	  "to be less sneaky than before.\n");
	TP->set_autosneak(0);
	return 1;
    }
    if (str == "constant")
    { 
	TP->catch_msg("You are now constantly sneaking.\n");
	say(QCTNAME(TP)+" grins mischievously as "+HE_SHE(TP)+" prepares "+
	  "to sneak around.\n");
	TP->set_autosneak(1);
	return 1;
    }
}
