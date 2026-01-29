/*
 * - corpse.c
 *
 * The corpse that a Union member leaves behind.
 * It's flamingtastic!
 *
 * Lucius, May 2007
 */
#pragma strict_types

inherit "/std/corpse";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"
#include "/d/Avenir/include/guilds.h"

private static object died;
private static int aflame, burn_id, was_npc;

#define BURN		5.0
#define BURN_DAMAGE	-(50 + random(50))


/* Give a flaming corpse? */
private mixed
corpse_no_give(void)
{
    if (!aflame)
	return 0;

    return "The blue-black flames make it too difficult to give "+
	"the "+ short() +" away.\n";
}

/* Flame on! */
private void
enflame(void)
{
    string old_state = state_desc;

    tell_object(died, "Blue-black flames erupt around your body as it "+
	"combusts in death, wreathing what's left of it in singing, "+
	"burning flames, searing your remaining vitality from the "+
	"inside out until blackness overtakes you....\n\n");

    state_desc = "dead body of ";

    tell_room(environment(), "Blue-black flames erupt around "+
	"the "+ QSHORT(this_object()) +", searing and burning "+
	"out any remaining vitality.\n", died, died);

    state_desc = old_state;
    aflame = 1;
}

/* Setup our corpse. */
public void
set_died(object who, int npc)
{
    died = who;
    was_npc = npc;

    set_leftover_list(who->query_leftover());

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CORPSE_S_RACE,
	who->query_race_name());

    change_prop(CONT_I_WEIGHT,
	who->query_prop(CONT_I_WEIGHT));
    change_prop(CONT_I_VOLUME,
	who->query_prop(CONT_I_VOLUME));
    change_prop(CONT_I_MAX_WEIGHT,
	who->query_prop(CONT_I_MAX_WEIGHT));
    change_prop(CONT_I_MAX_VOLUME,
	who->query_prop(CONT_I_MAX_VOLUME));

    if (was_npc)
    {
	/* Double first phase decay. */
	set_decay(decay * 2);
	environment(who)->add_prop(
	    UCORPSE_PROP(who->query_real_name()), this_object());
    }

    set_alarm(0.1, 0.0, enflame);
}

/* Flame on! */
public void
create_corpse(void)
{
    state_desc = "enflamed corpse of ";
    pstate_desc = "enflamed corpses of ";

    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_M_NO_GIVE, corpse_no_give);
}

/* Flame on! */
public void
set_name(string name)
{
    ::set_name(name);

    add_name("enflamed corpse");
    add_name(state_desc + met_name);
}

/* We may be aflame. */
public string
long_func(void)
{
    string str;
    object pob = vbfc_caller();

    if (!pob || !query_interactive(pob) || pob == this_object())
       pob = this_player();

    if (pob->query_real_name() == lower_case(met_name))
	str = "This is your own dead body.\n";
    else if (pob->query_met(met_name))
	str = "This is the dead body of " + capitalize(met_name) + ".\n";
    else
	str = "This is the dead body of " + nonmet_name + ".\n";

    if (aflame)
    {
	str += "Blue-black flames enshroud the body, flaring up "+
	    "whenever you draw near and seeking to lick at "+
	    "your extremities as they reach out.\n";
    }

    if (was_npc && IS_MEMBER(pob))
    {
	/* If the player is a member of the Union, looking upon
	 * the corpse will tell them that they need to burn it in
	 * the Jazur Flame before the NPC will reset.
	 */
	str += "\nThe words of Akram ring in your ears as you stand "+
	    "mourfully over the corpse: \"Only after being consumed "+
	    "within the Jazur Flame may we be reborn in shadow\".\n\n";
    }

    return str;
}

/* We are extinguished. */
public void
decay_fun(void)
{
    remove_name("enflamed corpse");
    remove_name(state_desc + met_name);

    ::decay_fun();

    add_name("husk");
    remove_name("heap");

    state_desc = "blackened husk of ";
    pstate_desc = "blackened husks of ";
    
    aflame = 0;

    tell_room(environment(this_object()), "The blue-black flames "+
	"enshrouding the "+ QSHORT(this_object()) +" flicker out.\n");

    /* Halt further decay. */
    if (was_npc)
	remove_alarm(decay_id);
}

/* Too close to corpse; burn! */
public int
get_leftover(string arg)
{
    int res = ::get_leftover(arg);

    if (!aflame || !res)
	return res;

    this_player()->heal_hp(BURN_DAMAGE);

    write("The blue-black flames burn you before you are able "+
	"to draw away.\n");
    say("Blue-black flames burn "+ QTNAME(this_player()) +" before "+
	this_player()->query_pronoun() +" is able to draw away.\n");

    return 1;
}

/* Too close to corpse; burn! */
public string
search_for_leftovers(object player, string str)
{
    string res = ::search_for_leftovers(player, str);

    if (!aflame)
	return res;

    str = "You burn yourself searching the "+ short();

    player->heal_hp(BURN_DAMAGE);

    if (!strlen(res))
	return str + " but find nothing.\n";

    return str + " but " + lower_case(res);
}

/* Keep burning until corpse is dropped. */
private void
burn_holder(object who)
{
    burn_id = 0;

    if (who != environment())
	return;

    if (!aflame || !living(who))
	return;

    who->heal_hp(BURN_DAMAGE);

    tell_object(who, "Blue-black flames envelope you "+
	"from the "+ short() +", lashing at you with "+
	"renewed fury.\n");
    tell_room(environment(who), QCTNAME(who) +" is burned by the "+
	"enveloping blue-black flames from the "+ QSHORT(this_object()) +
	" "+ who->query_pronoun() +" carries.\n",
	who, who);

    burn_id = set_alarm(BURN, 0.0, &burn_holder(who));
}

/* See if we should burn the carrier of this corpse. */
private void
pick_up(object who)
{
    /* But not if you're Union. */
    if (who->query_guild_name_occ() == OUNION)
    {
	tell_object(who, "Though the blue-black flames envelope you "+
	    "from the corpse, they feel cool and calming, not hurting "+
	    "you in the least.\n");

	tell_room(environment(who), QCTNAME(who) +" is enveloped with "+
	    "blue-black flames from the corpse, "+ who->query_pronoun() +
	    " seems to be unharmed by them.\n", who, who);

	return;
    }

    who->heal_hp(BURN_DAMAGE);

    tell_object(who, "Blue-black flames envelope you "+
	"from the corpse, lashing at you with singing fury.\n");
    tell_room(environment(who), QCTNAME(who) +" is burned as "+
	"blue-black flames envelope "+ who->query_objective() +".\n",
	who, who);

    burn_id = set_alarm(BURN, 0.0, &burn_holder(who));
}

/* See if we should burn the carrier of this corpse. */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!aflame || !living(to))
	return;

    set_alarm(0.0, 0.0, &pick_up(to));
}

/* Too close to corpse; burn! */
private void
burn_hand(object who)
{
    /* Safeguard. */
    if (who->query_ghost())
	return;

    /* But not if you're Union. */
    if (who->query_guild_name_occ() == OUNION)
    {
	tell_object(who, "The blue-black flames lick at you, "+
	    "chilling your skin but leaving you unharmed.\n");

	tell_room(environment(who), "Blue-black flames lick at "+
	    QTNAME(who) +" but don't seem to be harming "+
	    who->query_objective() +".\n", who, who);

	return;
    }

    who->heal_hp(BURN_DAMAGE);

    tell_object(who, "The blue-black flames burn you before "+
	"you are able to draw away.\n");
    tell_room(environment(who), "Blue-black flames burn "+
	QTNAME(who) +" before "+ who->query_pronoun() +
	" is able to draw away.\n", who, who);
}

/* Too close to corpse; burn! */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!aflame || !living(from) || ob->query_ghost())
	return;

    set_alarm(0.0, 0.0, &burn_hand(from));
}

/* Too close to corpse; burn! */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!aflame || !living(to))
	return;

    set_alarm(0.0, 0.0, &burn_hand(to));
}
