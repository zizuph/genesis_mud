// file name:        /d/Avenir/common/drow/npc/c_e_guard.c
// creator(s):       Antharanos
// revision history: Denis, Nov'96
// purpose:          Cloned at /d/Avenir/common/undraeth/streets/d1&d2
// note:             The guard should block the gate...
// bug(s):           
// to-do:            
/*
 * Re-patriated code back to the Kalad domain.
 * Commented out Guild related code as it is never
 * returning to Kalad or Avenir.
 */
# pragma strict_types
#include "/d/Kalad/defs.h"

# include <macros.h>
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>
# include <wa_types.h>
# include <options.h>

inherit CPASS(drow/npc/drider_std);

public object gate_guarded;

void
find_gate()
{
    int i;
    string *passages;
    gate_guarded = present("gate", environment());

    if (objectp(gate_guarded) &&
	MASTER_OB(gate_guarded) == CPASS(drow/door/c_e_gate1))
    {
	passages = gate_guarded->query_pass_command();
	for (i = 0; i < sizeof(passages); i++)
	    set_restricted_action(passages[i]);
    }
}

public void
react_open(string str)
{
    if (str == "gate")
	attack_object(this_player());
    return 0;
}

void
create_drider()
{
    add_name("guard");
    set_adj("wary");
    add_adj("suspicious");
    set_long("The black-skinned torso of a perfectly conditioned warrior "+
      "melds into the shiny black carapace of a giant spider's body. " +
      "His armoured arachnoid body, holding him high above the ground on long, "+
      "thin legs, fills the passage with an imposing presence. His "+
      "elvish features and posture express vigilance.\n");
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_2H_COMBAT, 90);
    set_act_time(10);
    add_act("emote scans his surroundings carefully.");
    add_act("say Oloth zhah tuth abbil lueth ogglin.");
    add_act("say Sarn.");
    add_act("say Quarvalsharess zhah ultrin!");
    add_act("emote figets, his legs restlessly scittering in place.");
    set_cact_time(5);
    add_cact("say Quarvalsharess plynn dos!");
    add_cact("say Elghinn ulu dos!");
    set_speak("A minimum of one gold coin is required for traders to the "+
      "drow city of Undraeth. Give it to me and you may pass...you are a "+
      "trader, aren't you?\n");
    set_dont_answer_unseen(1);
    add_ask(({"open", "Open"}), VBFC_ME("open_check"), 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_alarm(0.0, 0.0, find_gate);
    set_restricted_action("react_open");
    create_greater_drider();
    set_short("wary drider guard");
}

public void
unseen_hook()
{
    command("dnarrow searchingly");
    command("emote barks: Sarn!");
    command("say Vel'uss zhah ind? Tlu'zhar!");
}

public string
open_check(string str)
{
    if (!guarded_actions)
	return default_answer;
    if (!gate_guarded->query_open())
	command("dsay open");
    return default_answer;
}

public void
shut_gates()
{
//    command("dsay close");
}

static void
pass_living(object who)
{
    if (!gate_guarded->query_open())
	command("dsay open");
    set_alarm(3.0, 0.0, &who->move_living("through the " +
	"black adamantine gate", gate_guarded->query_other_room()));
}

void
return_pay(object who)
{
    if (present(who, environment(this_object())))
    {
	command("nod " + who->query_real_name());
	pass_living(who);
    }
}

void
return_greet(object who)
{
    if (present(who, environment(this_object())))
    {
	command("grin .");
	command("say Abban, elendar wun ulu Undraeth.");
	pass_living(who);
    }
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "open" && adverb == "gate")
	attack_object(actor);

    if (emote == "dgreet")
	if (IS_DROW(actor))
	    set_alarm(1.0, 0.0, &return_greet(actor));
}

public void
enter_inv(object ob, object from)
{
    string coins;

    ::enter_inv(ob, from);
    if (!living(from))
	return;

    coins = ob->query_coin_type();
    if (!coins || coins == "copper" || ob->heap_value() < 144)
    {
	from->catch_tell(TO->query_The_name(from) + "'s widen " +
	  "incredulously at you. Then his lips spread into a hardened sneer " +
	  "of disdainful amusement as he opens his hand and lets the " +
	  ob->short() + " drop from it.\n");
	tell_room(environment(from), QCTNAME(TO) +
	  " sneers disdainfully at " + QTNAME(from) + "`s offering.\n",
	  from);
	command("drop " + ob->query_name());
	return;
    }
    if (coins == "platinum")
	command("emote grins broadly, an avaricious gleam in his eye.");
    command("nod " + from->query_real_name());
    pass_living(from);
}

void
equip_me()
{
    seteuid(getuid(this_object()));
    clone_object(CPASS(arm/dw_chain))->move(this_object());
    clone_object(CPASS(arm/dw_helm))->move(this_object());
    clone_object(CPASS(arm/piwafwi))->move(TO);
    command("wear all");
    clone_object(CPASS(wep/dw_sword))->move(this_object());
    clone_object(CPASS(wep/dw_sword))->move(this_object());
    command("wield all");
    MONEY_MAKE_GC(random(3))->move(this_object(), 1);
}

void
arrive(object *cloned)
{
    switch (sizeof(cloned))
    {
    case 1:
	tell_room(environment(this_object()),
	  "Long, spidery legs appear from the shadows, bearing a drider into view.\n");
	return;

    default:
	tell_room(environment(this_object()),
	  "Several tall figures appear from the shadows, borne on great " +
	  "spider-like bodies.\n");
	return;
    }
}

public void
attack_object(object attacker)
{
    shut_gates();
    ::attack_object(attacker);
}
