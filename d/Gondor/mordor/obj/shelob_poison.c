/*
 * /d/Gondor/mordor/obj/shelob_poison.c
 *
 * Shelob paralyze poison.
 *
 * This isn't a normal poison, but rather a paralyze object. For a short
 * period of time, a player is paralyzed and he cannot do a thing. His
 * fighting will be stopped, though his enemy will continue to hack at
 * him/her. You call it unfair? I call it strong poison!
 *
 * It is indeed possible to kill someone while he/she is paralyzed. But
 * then again... Life if tough!
 *
 * /Mercade, 16 july 1993
 *
 * Revision history:
 */

inherit "/std/poison_effect";

#include "/d/Gondor/defs.h"
#include <poison_types.h>
#include <stdproperties.h>
#include <macros.h>

/*
 * This is an array of all commands that mortals can execute as they are
 * paralyzed. If you should change that list, please don't allow any commands
 * that would require any muscle in ones body.... You should only be able
 * to use your mind. The command "look" is especially triggered in the paralyze
 * command trigger itself.
 */
#define ALLOWED_COMMANDS ({ "bug", "commune", "help", "idea", "praise", \
    "quit", "reply", "typo" })

#define POISON_EFFECT_TIME     150
#define POISON_INTERVAL_TIME    20
#define CHECK_ON_POISONEE_TIME  10
#define POISON_STRENGTH         75
#define POISON_TYPE            "spider"
#define POISON_NAME            "_shelob_poison_"
#define POISON_DAMAGE          ({ POISON_FATIGUE, 10 })

/*
 * Global variable.
 */
int wimpy_level; /* The wimpy level of the poisonee */

void
create_poison_effect()
{
    set_name(POISON_NAME);

    set_poison_type(POISON_NAME);
    set_time(POISON_EFFECT_TIME);
    set_interval(POISON_INTERVAL_TIME);
    set_strength(POISON_STRENGTH);
    set_damage(POISON_DAMAGE);
    set_poison_type(POISON_TYPE);
    set_silent(2);

    add_prop(OBJ_I_NO_STEAL,    1);
    add_prop(OBJ_I_NO_TELEPORT, 1);

    add_prop(OBJ_S_WIZINFO, BSN("This object is used to paralyze a player. " +
        "He will also stop fighting if he is fighting. The problem though " +
        "is that his enemy will continue to attack and that you might be " +
        "killed while paralyzed. You are paralyzed by Shelob, the evil " +
        "dark spider, who dwels in Torech Ungol."));
}

/*
 * All commands that a player gives, are to be filtered!
 */
void
init()
{
    ::init();

    add_action("do_paralyze", "", 1);
}

/*
 * This function will prevent mortals to perform most actions. Obviously,
 * wizards aren't affected by the poison. Only the commands in ALLOWED_COMMANDS
 * in the file header are allowed.
 */
varargs int
do_paralyze(string str)
{
    string verb = query_verb();
    object tp = TP;

    /* It never hurts to make some sanity checks. */
    if ((ENV(TO) != tp) || (tp != poisonee) || (tp->query_wiz_level()))
    {
        set_alarm(1.0, 0.0, "remove_object");
        return 0;
    }

    /* Give a special message is the player wants to look */
    if (verb == "look" || verb == "l" || verb == "exa" || verb == "examine")
    {
        write(BSN("You can see nothing but vague shapes in all kinds of " +
            "colours. Those shapes don't make any sense to you though."));
        return 1;
    }

    /* These commands are allowed. */
    if (member_array(verb, ALLOWED_COMMANDS) != -1)
    {
        return 0;
    }

    /* Otherwize give him a fail message. */
    write(BSN("You are paralyzed and cannot move a muscle. However, you are " +
        "able use your mind."));
    return 1;
}

/*
 * This is the function to call when Shelobs bytes someone and poisons him.
 */
void
start_poison()
{
    if (query_recovery())
    {
        /* add 25% time punishment if he quit while he was poisoned. */
        p_time = ((p_time * 5.0) / 4.0);
    }

    ::start_poison();

    /* Don't poison a wizard. */
    if (poisonee->query_wiz_level())
    {
        poisonee->catch_msg(BSN("Shelob just poisoned you. Being a wizard " +
            "though, your power is slightly stronger than the poison and " +
            "the poison doesn't paralyze you, like it would paralyze a " +
            "mortal."));
        set_alarm(1.0, 0.0, "remove_object");
        return;
    }

/*
 * This message I shall only add if LIVE_I_ATTACK_DELAY is reset if someone
 * attackes you while you are paralyzed.
 *
    poisonee->add_prop(LIVE_AS_ATTACK_FUMBLE,
        ({ "Since you are paralyzed, you cannot fight.\n" }) );
 */
 /*
    poisonee->add_prop(LIVE_I_ATTACK_DELAY, POISON_EFFECT_TIME);
  */
    poisonee->add_stun();
    poisonee->add_prop(OBJ_I_NO_TELEPORT,
        (poisonee->query_prop(OBJ_I_NO_TELEPORT) + 1));

    if (!query_recovery())
    {
        wimpy_level = (int)poisonee->query_whimpy();
        poisonee->set_whimpy(0);
    }

    poisonee->catch_msg(BSN("As soon as the fangs hit you, you feel a " +
        "great pain. Shelob forces her poison into the wound and you feel " +
        "your awareness leaving you. You become dizzy and your vision " +
        "starts to blur. Your legs seem to refuse duty so you fall down. " +
        "You are paralyzed and cannot move a muscle any more. You sense " +
        "great dangers and are afraid of what peril is your fate! The " +
        "first visions you get are from Death, reaching for your soul!"));
    LTELL_ROOM(ENV(poisonee), poisonee, "As soon as Shelobs hits ",
        " with her fangs, " + PRONOUN(poisonee) + " falls down paralyzed. " +
        "Every attempt to persuade " + OBJECTIVE(poisonee) +
        " to a reaction fails. In fact you cannot even tell whether " +
        PRONOUN(poisonee) + " is still alive, or whether Death might show " +
        "up to grab another soul!", poisonee);
}

/*
 * This function should take care of the removal of the poison. The player
 * should be able to fight again and his wimpy will be restored.
 */
void
timeout()
{
    /*
    poisonee->remove_prop(LIVE_I_ATTACK_DELAY);
     */
    poisonee->remove_stun();
    poisonee->add_prop(OBJ_I_NO_TELEPORT,
        (poisonee->query_prop(OBJ_I_NO_TELEPORT) - 1));
    poisonee->set_whimpy(wimpy_level);

    poisonee->catch_msg(BSN("Slowly you regain consciousness and are " +
        "able to see your surroundings clearly. You crawl on your feet, " +
        "but stumble and fall down again. At last you manage to control " +
        "your limbs again, even though you are exhausted."));
    LTELL_ROOMBB(ENV(poisonee), poisonee, "Suddenly you see that ",
        " moves slightly. " + CAP(PRONOUN(poisonee)) + " tries to crawl " +
        "back on " + POSSESSIVE(poisonee) + " feet, but " +
        PRONOUN(poisonee) + " fails and falls down again. At last " +
        PRONOUN(poisonee) + " manages to control " + POSSESSIVE(poisonee) +
        " limbs again.", poisonee);

    ::timeout();
}

/*
 * Recovery code. We should save the whimpy level of the player. This means
 * that if a player quits and his autoloadstring is lost, his whimpy level
 * is also lost. Too bad.
 */
string
query_recover_poison()
{
    return ("#wimpy#" + wimpy_level + "#");
}

/*
 * Recover the whimpy level of the poisonee
 */
void
init_recover_poison(string arg)
{
    string foobar;

    sscanf(arg, "%s#wimpy#%d#%s", foobar, wimpy_level, foobar);
}
