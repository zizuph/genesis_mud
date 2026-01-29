/*
 * - murray.c
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

// Delay of the skull movement check.
#define DELAY  3.0
// How many tries before we go poof?
#define TRIES  3
// Delay to drain mana.
#define MANA_DELAY  300.0
// Mana drain / skull.
#define MANA_DRAIN  10
// How much damage we do on death.
#define DEATH_DAMAGE  (random(201) + 100)
// The prop we add to players.
#define SPELL_O_GHOSTLINK "_spell_o_ghostlink"
// Unique identifier for the skulls.
#define SKULL_ID  "ghostlink::skull"

private static object player, *other_skulls = ({ });
private static int master, muted, tries, alarm1, alarm2;

/*
 * Create the basic skull.
 */
private void
create_monster(void)
{
    set_gender(2);
    set_race_name("skull");

    add_prop(LIVE_I_NO_ACCEPT_GIVE, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(LIVE_I_NO_FOOTPRINTS,  1);
    add_prop(LIVE_I_NO_CORPSE,      1);
    add_prop(LIVE_I_NO_BODY,        1);
    add_prop(LIVE_I_UNDEAD,       100);
    add_prop(LIVE_I_SEE_INVIS,     99);
    add_prop(LIVE_I_NEVERKNOWN,     1);
    
    add_prop(LIVE_S_EXTRA_SHORT, " is floating here");

//    add_prop(OBJ_M_NO_ATTACK, "Attack a skull?  Yeah right!\n");
//    add_prop(OBJ_M_NO_MAGIC_ATTACK, "Attack a skull?  Yeah right!\n");

    set_stats(({ 30, 30, 30, 30, 30, 30 }));
    set_skill(SS_AWARENESS, 200);

    set_mm_in("floats in.");
    set_mm_out("floats out.");

    /* Command questions. */
    add_ask("dismiss", this_object()->dismiss_skull, 1);
    add_ask("report", this_object()->report_skulls, 1);
    add_ask("mute", this_object()->mute_skull, 1);

    /* Default response. */
    set_default_answer("glare uninterest", 1);

    /* Some silly actions to have it do. */
    set_act_time(60);
    add_act("emote floats around aimlessly.");
    add_act("emote bobs silently in the air.");
    add_act("emote gives you a baleful look.");
    add_act("emote spins pointlessly in the air.");
    add_act("emote looks like it wants to yawn out of boredom.");

    set_cact_time(30);
    add_cact("glare angrily");
    add_cact("scream");
    add_cact("wail");
}

/*
 * This is how we sound to others.
 */
public string
race_sound(void)
{
    return "intones";
}

/*
 * Skull removal.
 */
public void
remove_object(void)
{
    /* Remove alarms. */
    if (alarm1) remove_alarm(alarm1);
    if (alarm2) remove_alarm(alarm2);

    /* Nuke slave skulls. */
    if (master)
    {
	other_skulls->command("say Master, I have been recalled.");
	other_skulls->remove_object();
    }

    /* Let us know we have been nuked. */
    tell_room(environment(),
	capitalize(LANG_THESHORT(this_object())) +
	" vanishes into the shadows.\n", this_object());

    /* Remove reference prop. */
    player->remove_prop(SPELL_O_GHOSTLINK);

    /* Nuks us. */
    ::remove_object();
}

/*
 * This is where the skull relays the received messages.
 */
public void
broadcast_msg(mixed str, object from)
{
    /* Just in case. */
    if (muted)
	return;

    /* This needs to be split to function properly. */
    tell_room(environment(),
	"The "+ query_short() +" emits: ", this_object(), from);
    tell_room(environment(), str, this_object(), from);
}

/*
 * Masked to capture room spam.
 * Anything captured is then broadcast to
 * the other linked skulls.
 */
public void
catch_msg(mixed str, object from_player)
{
    object *skulls;

    if (!str)
	return;

    /* Filter out muted skulls. */
    skulls = filter(other_skulls, not @ &->query_muted());
    /* Filter out skulls in same room. */
    skulls = filter(skulls, &operator(!=)(environment()) @ environment);
    skulls->broadcast_msg(str, this_object());
}

/*
 * Default reply for non-owners asking the skull things.
 */
private string
not_my_skull(void)
{
    write(capitalize(LANG_THESHORT(this_object())) +
	" glares at you with baleful malevolence.\n");

    say(capitalize(LANG_THESHORT(this_object())) +
	" glares at "+ QTNAME(this_player()) +
	" with baleful malevolence.\n",
	({ this_object(),  this_player() }));

    return "grimace evil";
}

/*
 * Mute / unmute the skull.
 */
public string
mute_skull(void)
{
    if (this_player() != player)
	return not_my_skull();

    if (muted = !muted)
    {
	command("ask "+ OB_NAME(player) + " " +
	    "Master, I shall hush my grisly self.");
    }
    else
    {
	command("ask "+ OB_NAME(player) + " " +
	    "Master, I shall speak freely now.");
    }

    return "grimace amused";
}

/*
 * Ask the skull to report on it's linked skulls.
 */
public string
report_skulls(void)
{
    string *arr;

    if (this_player() != player)
	return not_my_skull();

    if (!master)
    {
	arr = ({ other_skulls[0]->query_linkage()->query_name() });
    }
    else
    {
	arr = map(map(other_skulls, &->query_linkage()),
	    		&->query_name());
    }

    command("ask "+ OB_NAME(player) +
	" Master, I am linked to the following:");
    command("ask "+ OB_NAME(player) + " " +
	COMPOSITE_WORDS(sort_array(arr)));

    return "grimace help";
}

/*
 * Add a skull to the chain.
 */
public void
link_skull(object skull)
{
    /* If we are the master skull, and we already
     * have links to other skulls, connect new skulls
     * to the existing network. */
    if (master)
    {
	int size = sizeof(other_skulls);

	while(size--)
	    skull->link_skull(other_skulls[size]);
    }

    other_skulls += ({ skull });
}

/*
 * Unlink a skull from the chain.
 */
public void
unlink_skull(object skull)
{
    other_skulls -= ({ skull });

    if (master)
    {
	int size = sizeof(other_skulls);

	if (!size)
	{
	    /* The network is gone, remove the master. */
	    command("say Master, my other selves are no more.");
	    set_alarm(0.0, 0.0, &remove_object());
	}
	else
	{
	    /* Let the caster know the network has shrunk. */
	    command("say Master, I have lost contact with one "+
		"of my other selves.");
	}
    }
}

/*
 * Used to dismiss a skull.
 */
public string
dismiss_skull(string str)
{
    int index;
    string *arr = ({ "skull" });

    /* Only the owner may dismiss, or the master skull. */
    if (this_player() != player)
    {
	if (calling_object() != other_skulls[0])
	    return not_my_skull();
	else
	    command("say Master, I have been instructed to depart.");
    }

    if (!strlen(str))
    {
	/* This is for the 'add_ask' bit. */
	str = "skull";
    }
    else if (master)
    {
	/* Add in a list of linked skulls to the master. */
	arr += map(map(other_skulls, &->query_linkage()),
	    		&->query_real_name());
    }

    /* Invalid choice. */
    if ((index = member_array(str, arr)) == -1)
    {
	command("grimace helpless");
	return ""; 
    }

    /* Are we dismissing our own skull? */
    if (str == "skull")
    {
	if (this_player() == player)
	    command("say Master, it shall be as you command.");

	other_skulls->unlink_skull(this_object());
	set_alarm(0.0, 0.0, &remove_object());
    }
    else
    {
	/* The master has dismissed a slave skull. */
	object skull = other_skulls[--index];

	command("say Master, it shall be as you command.");
	skull->dismiss_skull("skull");
    }

    return "grimace forlorn";
}

/*
 * Allow you to selectively dismiss skulls.
 */
public void
catch_question(string str)
{
    string who;

    if (!sscanf(str, "dismiss %s", who))
	::catch_question(str);
    else
	dismiss_skull(who);
}

/*
 * This keeps the skull in range of the player.
 */
public void
move_skull(void)
{
    if (!present(player, environment()))
    {
	move_living("X", environment(player), 1, 1);
	/*
	 * In case the skull gets stuck, we will
	 * try a few times, then auto-dest.
	 */
	if (!present(player, environment()))
	{
	    if (++tries <= TRIES)
		return;

	    other_skulls->unlink_skull(this_object());
	    remove_object();
	    return;
	}
    }
    tries = 0;
}

/*
 * Drain mana from the caster to maintain the skulls.
 */
private void
skull_drain(void)
{
    int mana = (sizeof(other_skulls) * MANA_DRAIN);

    if (player->query_mana() < mana)
    {
	/* Not enough mana, bye bye. */
	command("say Master, you lack the enery to sustain us.\n");
	remove_object();
	return;
    }
    else
    {
	player->catch_tell(capitalize(LANG_THESHORT(this_object())) +
	    "'s eyesockets flare briefly with renewed life.\n");
    }
    player->add_mana(-mana);
}

/*
 * Initializes the skull.
 */
public void
init_skull(object who, int flag)
{
    player = who;
    master = flag;

    if (master)
    {
	/* The master skull. */
	set_name(({ "skull", "master_skull", SKULL_ID }));
	set_adj(({ "floating", "black" }));
	set_short("black skull");
	set_long("This is a transparent black skull of a human.\n");
    }
    else
    {
	/* The slave skulls. */
	set_name(({ "skull", "slave_skull", SKULL_ID }));
	set_adj(({ "floating", "ghostly" }));
	set_short("ghostly skull");
	set_long("This is a transparent ghostly skull of a human.\n");
    }

    /* Add a reference prop to this player. */
    player->add_prop(SPELL_O_GHOSTLINK, this_object());

    /* Start up alarms as necessary. */
    alarm1 = set_alarm(DELAY, DELAY, move_skull);
    if (master && !player->query_wiz_level())
	alarm2 = set_alarm(MANA_DELAY, MANA_DELAY, skull_drain);
}

/*
 * Returns if a skull is muted or not.
 */
public int
query_muted(void)
{
    return muted;
}

/*
 * Returns the player we are linked to.
 */
public object
query_linkage(void)
{
    return player;
}

/*
 * Returns the skulls we are linked to.
 */
public object *
query_other_skulls(void)
{
    return other_skulls;
}

/*
 * Attack notification.
 */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (!master)
    {
	other_skulls[0]->command("say Master, "+
	    "one of my other selves is under attack!");
    }
}

/*
 * Do some damage when we die.
 * Hits all players in the room, plus the caster.
 */
public int
second_life(object killer)
{
    int damage = DEATH_DAMAGE;
    object *whom = filter(all_inventory(environment()), living);

    whom -= ({ this_object() });

    tell_room(environment(),
	capitalize(LANG_THESHORT(this_object())) +
	" wails in rage and torment, flooding the area "+
	"with a psychic backlash.\n", this_object());

    whom->reduce_hit_point(damage);
    whom = filter(whom, not @ &->query_hp());
    whom->do_die(this_object());

    if (!master)
    {
	object who = other_skulls[0]->query_linkage();

	other_skulls[0]->command("say Master, "+
	    "one of my other selves has been slain!");

	who->reduce_hit_point(damage);
	who->catch_tell("You feel a psychic backlash wash over "+
	    "you from across the ghostlink before it can be "+
	    "severed!\n");

	/* Only slave skulls need to do this.
	 * The death of the master will remove all slaves. */
	other_skulls->unlink_skull(this_object());
    }

    return 0;
}
