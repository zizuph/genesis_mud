/*
 * /d/Gondor/common/npc/faramir.c
 *
 * Revision:
 * Updated code: Boron, May 30. 1996
 * Updated code: Olorin, 14-Feb-1997.
  * Tigerlily, May 31, 2004:  This version of Faramir
  *   is obsolete. Refer to the version under /d/Gondor/guilds/rangers/npc
 */
#pragma strict_types

inherit "/d/Gondor/common/npc/npc_ranger.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public int     test_player(object player);
public void    check_player();
public void    do_blindfold(object player);
public void    reset_faramir();

static int     Busy = 0,
               Check_AID;

public void
create_ranger()
{
    set_name("faramir");
    add_name("man");
    add_name("dunadan");
    set_living_name("faramir");
    set_title("the Master of the Rangers of Ithilien");
    set_company("Ithilien");
    set_race_name("human");
    set_gender(0);
    set_adj("tall");
    set_adj("stern");
    set_long(BSN("He is a pale-skinned tall man, dark of hair, with " +
		 "grey eyes, and a proud and sad face. You realize " +
		 "that he must be one of the Dunedain of the South, " +
		 "a man of the line of the Lords of Westernesse."));
    set_stats( ({ 85+random(10), 
		  95+random(10), 
		  95+random(10), 
		  90+random(10), 
		  90+random(10), 
		  95+random(10) }));

    set_base_stat(SS_OCCUP, 96);

    set_skill(SS_WEP_SWORD,90+random(15));
    set_skill(SS_PARRY,80+random(10));
    set_skill(SS_DEFENCE,90+random(10));
    set_skill(SS_UNARM_COMBAT,90+random(10));
    set_skill(SS_CLIMB,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_BRAWLING,85+random(20));
    set_skill(SS_HEARING,85+random(20));

    set_alignment(700+random(50));

    set_aggressive(1);

    add_prop(CONT_I_HEIGHT,   195);
    add_prop(CONT_I_WEIGHT, 87000);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_chat("Curse the Southrons!");
    add_chat("Of late we have learned that the Enemy has been among the Southrons.");
    add_chat("There was never friendship between Gondor and the kingdoms of Harad in the South.");
    add_chat("The Southrons have gone over to the Enemy, as some many have done in the East.");
    add_chat("The cursed Southrons are marching on the very roads that the craft of Gondor made.");
    add_act("sigh");
    add_act("emote deeply breathes the air, full with the smell of many herbs and flowers.");
    set_cact_time(1);
    add_cact("brawl");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask("name", VBFC_ME("introduce"));
    add_ask("rangers", 
	    QCTNAME(TO) + " says: " +
	    "We Rangers of Ithilien are fighting the armies of the Evil One.\n");
}

public void
arm_me()
{
    FIX_EUID;

    clone_object(ITH_DIR + "obj/rlsword")->move(TO);
    command("wield longsword");
    clone_object(ITH_DIR + "obj/rgauntlets")->move(TO);
    command("wear gauntlets");
    clone_object(ITH_DIR + "obj/rhood")->move(TO);
    command("wear hood");
    command("mask me");
    clone_object(ITH_DIR + "obj/rcloak")->move(TO);
    command("wear cloak");
    clone_object(ITH_DIR + "obj/bow")->move(TO);
    clone_object(ITH_DIR + "obj/quiver")->move(TO);
}

public varargs string
introduce(object player)
{
    if (!objectp(player))
	player = TP;
    if (!objectp(player))
	return "";

    if (query_friend_or_foe(player) < 0)
    {
	command("say Die, foul creature!");
	do_attack(player);
	return "";
    }
    command("unmask me");
    command("say I am Faramir, Captain of Gondor.");
    command("hail " + player->query_real_name());
    command("introduce me to " + player->query_real_name());
    return "";
}

void
attacked_by(object ob)
{
    command("mask me");
    ::attacked_by(ob);
}

static void
do_attack(object victim)
{
    command("mask me");
    ::do_attack(victim);
}

public void
init_attack()
{
    if (objectp(query_attack())) 
	return;
    if ((query_friend_or_foe(TP) < 0) ||
	(TP->query_prop("_arrested") && 
	 !present("damrod",ENV(TO)) &&
	 !present("meneldil", ENV(TO))))
    {
	set_alarm(2.0, 0.0, &do_attack(TP));
    }
}

public string
default_answer()
{
    if (query_friend_or_foe(TP) < 0)
	do_attack(TP);
    else
	command("say I do not know what you are talking about, " +
		TP->query_race_name() + ".\n");
    return "";
}

public void
check_player()
{
    object *cont, 
           *players = ({ });
    int     i;
  
    if (objectp(query_attack()) && 
	(!Check_AID || !sizeof(get_alarm(Check_AID))))
    {
	Check_AID = set_alarm(10.0, 0.0, check_player);
	return;
    }

    cont = FILTER_PLAYERS(all_inventory(ENV(TO)));
    players = filter(cont, &->query_prop("_arrested"));
    players = filter(players, not @ test_player);
    if (!sizeof(players))
	reset_faramir();

    if (!objectp(query_attack()))
    {
	command("say " + CAP(COMPOSITE_LIVE(players)) + ", you are under arrest!");
	command("say You have violated the Law of the Steward of Gondor!");
	command("say I will now bring you back to the Anduin.");
	command("say Do not try to escape!");
	for (i = 0; i < sizeof(players); i++)
	    do_blindfold(players[i]);
	reset_faramir();
    }
    else if (!Check_AID || !sizeof(get_alarm(Check_AID)))
	Check_AID = set_alarm(10.0, 0.0, check_player);

    return;
}

public void
climb_tree()
{
    command("climb rock");
    command("climb tree");
    command("climb up");
    command("climb up");
    introduce();
    set_alarm(4.0, 0.0, check_player);
    return;
}  
  
public void
called_by_damrod(object damrod)
{
    if (!Busy)
    {
	add_prop("_ithilien_ridge_found_rock",1);
	add_prop("_ithilien_ridge_look_branch",1);
	move_living("down", ITH_DIR + "nforest/ridge3");
	Busy = 1;
	set_alarm(4.0, 0.0, climb_tree);
    }
    else
	set_alarm(20.0, 0.0, &called_by_damrod(damrod));
    return;
}

public int
query_busy()
{
    return Busy;
}

public int
set_busy(int x = 1)
{
    Busy = x;
    return Busy;
}

public int
test_player(object player)
{
    object badge;

    if (IS_RANGER(player))
	return 1;
    if (!objectp(badge = present("_ithilien_badge", player)))
	return 0;
    else if (badge->query_prop("_ithilien_leave_name") != 
	     player->query_real_name())
    {
	command("mask me");
	command("say That badge doesn't belong to you!");
	write(QCTNAME(TO) + " takes away your badge.\n");
	badge->move(TO);
	say(QCTNAME(TO) + " takes away a badge from " + QCTNAME(player) + ".\n");
	command("emote breaks the badge.");
	badge->remove_object();
	player->add_prop("_no_pass_to_ithilien",1);
	command("say Die, foul spy!");
	do_attack(player);
	return 0;
    }
    else if (player->query_prop("_no_pass_to_ithilien"))
    {
	command("mask me");
	command("say You are here against the Law of the Steward of Gondor!");
	command("say There is only one punishment, and that is death!");
	do_attack(player);
	command("say Die, traitor!");
	return 0;
    }
    else
	return 1;
}

public void
do_blindfold(object player)
{
    if (!objectp(player) || !present(player, ENV(TO))) 
	return;
    player->catch_msg("You are blindfolded.\n");
    player->catch_msg("Your hands are tied, your feet are hobbled together.\n");
    tell_room(ENV(TO), QCTNAME(player) + " is bound and blindfolded.\n",player);
    player->move_living("M",ITH_DIR + "nforest/captured",1);
    tell_room(ENV(TO), QCTNAME(TO) + " ties a rope around " + QTNAME(player) + "'s body.\n");
    tell_room(ENV(TO), "He then carefully lets " + QTNAME(player) + " down at the end of the rope.\n");
}

/* Solemnian prestige */
int query_knight_prestige() {return (-20);}

public void
reset_faramir()
{
    Busy = 0;
    tell_room(ENV(TO), QCTNAME(TO) + " leaves climbing down.\n");
    TO->move_living("M","/d/Gondor/ithilien/faramir_room",1);
    tell_room(ENV(TO), QCTNAME(TO) + " arrives.\n");
}
