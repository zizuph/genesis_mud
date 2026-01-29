/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above.
 */

inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "attackers.c"

void
create_monster() 
{
    set_name("proprietor");
    add_name(({"owner", "shopkeeper", "shopowner", "_thornlin_mili"}));
    set_race_name("human");
    set_adj(({"muscular","young"}));
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_long("This is the shopkeeper who runs the General " +
      "Store in Thornlin.  He is surprisingly young for his job, " +
      "but he seems quite competent.\n");
    default_config_npc(130);
    set_base_stat(SS_DEX,195);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    set_skill(SS_WEP_POLEARM, random(10)+90);
    set_skill(SS_DEFENCE, random(10)+90);
    set_skill(SS_PARRY, random(10)+90);
    set_skill(SS_AWARENESS, random(10)+90);
    set_skill(SS_TRADING, random(20)+80);
    set_alignment(550 + random(100));
    set_chat_time(22);
    add_chat("Can I help you?");
    add_chat("Welcome to my shop!");
    add_chat("Have you got anything nice to sell?");
    add_chat("Perhaps you want to buy some excellent equipment?");
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards!  Help!");
}

void
arm_me()
{
    FIX_EUID
    clone_object(THORN_DIR + "obj/spear")->move(TO);
    command("wield spear");
    clone_object(THORN_DIR + "obj/cloak")->move(TO);
    clone_object(THORN_DIR + "obj/shield")->move(TO);
    clone_object(THORN_DIR + "obj/hauberk")->move(TO);
    clone_object(THORN_DIR + "obj/gauntlets")->move(TO);

    command("wear hauberk"); 
    command("wear gauntlets");
    command("wear all");
}

void
do_bow(object tp)
{
    if (!tp->query_npc() && CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, tp))
	command("bow " + OB_NAME(tp));
    /*
    command("bow " + tp->query_real_name());
    */
    command("say What can I do for you?");
    command("say Perhaps you want to buy some excellent equipment?");
}

public int query_knight_prestige() { return -75; }

public void
emote_hook(string emote, object actor, string adverb, int target)
{
    if (emote == "bow")
    {
	set_alarm(2.0, 0.0, &do_bow(actor));
    }
}

void
return_object(object obj, object to)
{
    if (obj->id("coin"))
    {
	command("say Why, thank you!");
	command("smile " + OB_NAME(to));
	return;
    }

    command("say Thanks, but I don't think I need that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (ENV(obj) == TO)
    {
	command("drop " + OB_NAME(obj));
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (objectp(ob) && objectp(from) && living(from))
    {
	set_alarm(0.5, 0.0, &return_object(ob, from));
    }
}

