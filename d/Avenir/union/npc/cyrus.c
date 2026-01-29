/* Npc guard for the Union */
/*
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 *  Lilith, Oct 2021: moved order of weapon cloning so npc wields sword.
 *                    added assist Nadia to cact.
 *
 */
#pragma strict_types

#include "../defs.h"
inherit (NPC + "npc");

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>


public string
my_long(void)
{
    string str = "Tall and proud, he stands guarding the gate.\n";

    if (IS_MEMBER(TP))
    {
	str += "He looks as though he is ready to assist "+
	"you in combat, should you ask.\n";
    }

    return str;
}

public void
create_monster(void)
{
    set_name("cyrus");
    set_living_name("cyrus");
    set_race_name("elf");
    set_adj("dark-eyed");
    add_name("guard");

    set_long(my_long);
    set_title("the Protector of Shadows");

    set_alignment(0);
    set_gender(G_MALE);
    set_appearance(75);
    set_base_stat(SS_OCCUP, 100);
    set_stats(({ 244, 385, 295, 195, 191, 194 }));

    set_union_npc();
    TO->set_union_sphere(SPH_PROTECTION);

    set_skill(SS_LANGUAGE,      20);
    set_skill(SS_PARRY,        100);
    set_skill(SS_ACROBAT,      150);
    set_skill(SS_AWARENESS,     85);
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_UNARM_COMBAT,  10);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HERBALISM,     91);
    set_skill(SS_LOC_SENSE,     54);
    set_skill(SS_WEP_KNIFE,     125);
    set_skill(SS_WEP_SWORD,     125);
    set_skill(SS_2H_COMBAT,     125);
    set_skill(SS_SWAY,          125);
    set_skill(SS_FLING,         125);
    set_skill(SS_SLASH,         125);

    add_prop(NPC_I_NO_UNARMED, 1);
    set_all_hitloc_unarmed(75);

    set_act_time(35);
    add_act("kill ogre");
    add_act("ask nadia Who are these people?");
    add_act("brood");
    add_act("rub sphere");
    add_act(({"close gate", "lock gate with sphere"}));
    add_act("flex fingers");
    add_act("mark all");
    add_act("uclean knife");
    add_act("dget");

    set_cact_time(3);
    add_cact("angry");
    add_cact("clash");
    add_cact("cross");
    add_cact("ask nadia assist");
    add_cact("dget");
    add_cact("assist nadia");
    add_cact("wrath");

    add_ask(({"open", "gate","open gate", "to open gate"}),
	VBFC_ME("open_gate"));
    add_ask(({ "door" }), "say Through it shall you find "+
	"either beauty or death.", 1);
    add_ask(({ "elder" }), "say They are the Masters of the Shadows.", 1);
    add_ask(({ "flame" }), "say It surrounds and protects us, "+
	"may it never go out.", 1);
    add_ask(({ "guild" }), "say This place is the Union of Shadow, "+
	"no 'guild' as you say.", 1);
    add_ask(({ "help" }), "say I can offer you none.", 1);
    add_ask(({ "join", "membership", "hopeful", "apply", "application" }),
	"say Provide an application note to our Voice, "+
	"tell us what you think need be known. A meeting will be "+
	"arranged by our choice, and of your life will be no "+
	"unturned stone.", 1);
    add_ask(({ "joining", "unity", "voice" }),
	"say If you desire Unity, seek the Voice.  You may send mail "+
	"to the 'voice' in our post office.", 1);
    add_ask(({ "knife" }),
	"say It is a beautiful weapon, graceful and deadly.", 1);
    add_ask(({ "let me in" }),
	"say You will need to speak with Nadia for that.", 1);
    add_ask(({ "let me join" }),
	"say That is for the Elders to decide.", 1);
    add_ask(({ "member" }),
	"say I am a member of the great and eternal Union of Shadow.", 1);
    add_ask(({ "quest" }), "say You will find many in your life...", 1);
    add_ask(({ "ring" }),
	"say The Fire itself rings all things, binding us "+
	"in a Union of Shadows.", 1);
    add_ask(({ "stone" }), "say Surrounded by stone are we.", 1);
    add_ask(({ "task" }), "say You will find none from me.", 1);
    add_ask(({ "union" }),
	"say The Union lies within, a great and terrible "+
	"entity of Dark and Light.", 1);

    add_prop(CONT_I_HEIGHT, 200);
    add_prop(LIVE_I_QUICKNESS, 200);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    equip(({OBJ+"slash", OBJ+"knife_alt", OBJ+"knife_alt",
	    OBJ+"knife_alt", OBJ+"knife_alt", OBJ+"knife_alt",
	    OBJ+"shirt", OBJ+"pants", OBJ+"boots",
	    OBJ+"cape", OBJ+"gloves", OBJ+"knife_alt",
	    OBJ+"combat_veil"}));

    set_alarm(1.0, 0.0, &command("mark all"));
    set_alarm(1.0, 0.0, &command("veil me"));
}

public string *snds = ({
    "cries", "yells", "says"
});

public string
race_sound(void)
{
    return one_of_list(snds);
}

public string
open_gate(void)
{
    if (query_attack())
	return "";

    if (!CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
    {
	command("peer");
	command("say Who said that?");
	return "";
    }

    if (ENEMY(TP))
    {
	command("say Not a chance, "+ TP->query_race_name() +".");
	return "";
    }

    if (!present("nadia", ENV(TO)))
    {
	command("say Hmm ... Nadia takes care of the gate, but she is gone.");
	command("say Sorry, I can't let you in myself.");
	return "";
    }

    command("say You'll have to ask Nadia.");
    command("nod brief nadia");
    return "";
}

public void
init_living(void)
{
    ::init_living();
#ifdef BLOCK_ESCAPE
    add_action("stop",   "west");
#endif
    add_action("stop",   "east");
}

public int
stop(string str)
{
    if (!CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
	return 0;

    if (query_attack() == TP)
    {
	if (TP->query_stat(SS_DEX) < random(300))
	{
	    TP->catch_msg(QCTNAME(TO)+" moves to block your retreat.\n");
	    say(QCTNAME(TO)+" stands in "+QTNAME(TP)+"'s path, "+
		"blocking "+HIS(TP)+" retreat.\n", ({TP, TO}) );
	    return 1;
	}
	return 0;
    }

    if (query_verb() != "east")
	return 0;

    if (ENEMY(TP))
    {
	command("say Not a chance, scum.");
	TP->catch_tell("He stands in your way.\n");
	return 1;
    }

    if (TP->query_bit(GUILD_GROUP, PROHIBIT))
    {
	if (!FRIEND(TP))
	{
	    command("say You have betrayed us. There is no way you "+
		"will get past me alive.");
	    TP->catch_tell("He stands in your way.\n");
	    return 1;
	}
	return 0;
    }

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOENTER))
    {
	TP->catch_msg(QCTNAME(TO) +" stands in your way.\n");
	command("us I don't think so, "+ TP->query_name() +".");
	return 1;
    }

    return 0;
}

public void
attacked_by(object enemy)
{
    object friend = present("nadia", environment());

    if (!friend || !friend->query_npc() || friend->query_attack())
	return;

    friend->command("kill "+ OB_NAME(enemy));
}

public void
warn_no_spells(void)
{
    command("say Take care, though. Any magic will bring "+
	"down the wrath of the Flame.");
}

public int
is_spellcaster(object who)
{
    return (who->query_guild_style_occ() == "magic" ||
	    who->query_guild_style_lay() == "magic" ||
	    who->query_guild_style_occ() == "cleric" ||
	    who->query_guild_style_lay() == "cleric" ||
	    who->query_guild_style_occ() == "ranger" ||
	    who->query_guild_style_lay() == "ranger");
}

public void
unpc_hook_passing_player(object who)
{
    if (is_spellcaster(who))
	set_alarm(1.0, 0.0, &warn_no_spells(who));
}

private void 
return_unwanted(object what, object who)
{
    if (!objectp(what))
	return;

    if (present(who, environment()))
	command("usto "+ who->query_real_name() +" That is not for me.");

    if (!command("give "+ OB_NAME(what) +" to "+ OB_NAME(who)))
	what->remove_object();  
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
	return;

    if (obj->query_wt() == W_KNIFE)
	return;

    set_alarm(2.0, 0.0, &return_unwanted(obj, from));
}
