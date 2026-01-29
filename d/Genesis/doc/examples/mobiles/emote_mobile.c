/*
 * /doc/examples/mobiles/emote_mobile.c
 *
 * In the beginning of time, the honourable Tricky created an alchemist. Nick
 * called this 'an excellent example on how to use triggers' and he stripped
 * the triggering part of it for this example, or rather, Nick stole it as he
 * said ;-) Now we don't use triggers anymore for emotions, but a large hook
 * to 'trigger' on the emotions.
 *
 * Originally coded by Tricky as alchemist for Hobbiton, Genesis.
 * Adapted as emote-trigger-example by Nick.
 * Converted to emote-hook-example by Mercade, March 28 1996.
 */

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
/* cmdparse.h is needed for action classifications */
#include <cmdparse.h>

/* Since we need this check in each emote-reaction, we put it in a simple
 * define for easy coding.
 */
#define CHECK_ACTOR(actor) if (!present(actor, environment())) { return; }

/* Prototypes */
void react_to_offensive_emote(object actor, string adverb);
void spit(object actor, string adverb);

/*
 * Function name: create_monster
 * Description  : Constructor. This function is called to create this monster.
 */
void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_name("alchemist");
    set_adj("town");
    set_race_name("human"); 

    set_short("town alchemist");

    set_long("You are looking at the local alchemist, who is " +
	"known to possess the power to transform certain objects into " +
	"other objects. Simply give him an object, so he can judge it.\n");

    add_prop(CONT_I_WEIGHT, 47000);   /* 47 Kg */
    add_prop(CONT_I_HEIGHT, 87);      /* 87 cm */
    add_prop(LIVE_I_NEVERKNOWN, 1);

    /* str dex con int wis dis */
    set_stats( ({ 22, 27, 21, 70, 70, 34 }) );
}

/*
 * Function name: emote_hook
 * Description  : This hook is called whenever an emotion is performed on this
 *                NPC. If it is an emotion that we hook on, call a little
 *                alarm and then call the return function.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 *                object *targets - the targets of the emotion
 *                int cmd_attrs - the command's attributes (from cmdparse.h)
 */
void
emote_hook(string emote, object actor, string adverb, object *targets,
    int cmd_attrs)
{
    function f;

    /* We could maintain a list of emotes that we react to. Instead,
     * we just look for a function that has the same name as the emote.
     * If one exists, then we have defined a reaction for that emote!
     */
    if (f = mkfunction(emote, this_object()))
    {
        /* We have found a function that matches the emote name, so
         * we wait three seconds before calling the function with
         * the actor and the adverb as arguments. 
         */
        set_alarm(3.0, 0.0, &f(actor, adverb));
    }

    /* In addition to those emotes we want to respond to specifically,
     * we want to respond to offensive emotes which have been targeted
     * at this npc.  To do that, we'll examine the attributes of the
     * action to see if it has been classified offensive.
     */
    if (cmd_attrs & ACTION_OFFENSIVE)
    {
        /* See if this npc was among the targets of the emote */
        if (sizeof(targets) && (member_array(this_object(), targets) >= 0))
	{
            set_alarm(3.0, 0.0, &react_to_offensive_emote(actor, adverb));
	}
    }
}

/*
 * Function name: emote_hook_onlooker
 * Description  : This hook is called whenever an emotion is performed on a
 *                third party in the room. Normally we don't bother to react
 *                on emotions on others, unless someone is spitting. As the
 *                alchemist doesn't like spitting at all, he reacts to it.
 * Arguments    : string emote    - the emotion performed.
 *                object actor    - the actor of the emotion.
 *                string adverb   - the adverb used in the emotion.
 *                object *targets - the targets of the emotion.
 *                int cmd_attrs - the command's attributes (from cmdparse.h)
 */
void
emote_hook_onlooker(string emote, object actor, string adverb, object *targets,
    int cmd_attrs)
{
    /* Only react to spitting. */
    if (emote == "spit")
    {
	/* As we know the function we are going to call, we can use it in
	 * the alarm directly in the form of a function pointer.
	 */
	set_alarm(3.0, 0.0, &spit(actor, adverb));
    }
}

/*
 * Function name: react_to_offensive_emote
 * Description:   This is called after a short delay when an offensive
 *                emote is done on this npc.  See emote_hook() above.
 */
void
react_to_offensive_emote(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    command("frown disapprovingly");
    command("say How rude!");
}

/********************************************************************
 *
 *  Some reaction functions to make the alchemist more vivid.  Each
 *  function corresponds to the emote with the same name and is called
 *  after a short delay when that emote is used (See emote_hook() and
 *  emote_hook_onlooker() above).
 */

void
sigh(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say Why are you depressed, " + actor->query_nonmet_name() +
		"?");
	return;

    case 1:
	command("comfort " + OB_NAME(actor));
	return;

    default:
	command("say Is life tough for you, " + actor->query_nonmet_name() +
		"?");
    }
}

void
smile(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say Life is great, isn't it, " + actor->query_nonmet_name() +
		"?");
	return;

    case 1:
	command("smile at " + OB_NAME(actor));
	return;

    default:
	/* Here we see the beauty of the adverb-format. If no adverb is used,
	 * the variable will be only "", making the comma follow the word
	 * 'smiling' directly. However, if there is an adverb, is will be
	 * properly separated from by the space that is preceding it.
	 */
	command("say It is great to see you smiling" + adverb + ", " +
		actor->query_nonmet_name() + ".");
    }
}

void
smirk(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say I sense irony, " + actor->query_nonmet_name() + "...");
	return;

    case 1:
	command("smirk");
	return;

    default:
	command("grin at " + OB_NAME(actor));
    }
}

void
grin(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say What cunning plan have you forged, " +
		((actor->query_gender() == G_MALE) ? "master" : "lady") +
		"?");
	return;

    case 1:
	command("grin");
	return;
	
    default:
	command("say Get that grin off your face, " +
		actor->query_race() + ".");
    }
}

void
nod(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say I'm glad you agree, " +
		((actor->query_gender() == G_MALE) ? "master" : "lady") +
		".");
	return;

    case 1:
	command("pat " + OB_NAME(actor));
	return;

    default:
	command("say Indeed, " + actor->query_race() + ".");
    }
}

void
shake(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    /* I must admit that at this time there is no way to see whether the
     * actor is shaking his head in general or shaking the hand of this
     * NPC. For now I shall assume the shake is in general. If you have a
     * good way [that doesn't consume too much CPU] to find out, please
     * let me know. /Mercade.
     */
    switch(random(3))
    {
    case 0:
	command("say So you disagree, " + actor->query_race() + "?");
	return;

    case 1:
	command("say I agree with you, " +
		((actor->query_gender() == G_MALE) ? "master" : "lady") + ".");
	return;

    default:
	command("say Why do " + LANG_PWORD(actor->query_race()) +
		" always disagree?");
    }
}

void
laugh(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say Very funny indeed...");
	return;

    case 1:
	command("laugh");
	return;

    default:
	command("giggle");
    }
}

void
growl(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say You frighten me with your growling, " +
		actor->query_race() + "...");
	return;

    case 1:
	command("say Why so hostile, " + actor->query_race() + "?");
	return;

    default:
	command("frown");
    }
}

void
cackle(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say You sound like a duck, " + actor->query_race() + ".");
	return;

    case 1:
	command("say " + capitalize(LANG_PWORD(actor->query_race())) +
		" cackle very often.");
	return;

    default:
	command("giggle");
    }
}

void
shrug(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say Is there anything you " +
		LANG_PWORD(actor->query_race()) + " do know?");
	return;

    case 1:
	command("say Don't look at me... I don't know either!");
	return;

    default:
	command("shrug");
    }
}

void
bow(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    command("bow to " + OB_NAME(actor));
}

void
wave(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    command("wave to " + OB_NAME(actor));
}

void
frown(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say Is something wrong, " + actor->query_race());
	return;

    case 1:
	command("say It wasn't my fault!");
	return;

    default:
	command("say I had nothing to do with it, I assure you!");
    }
}

void
spit(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say Damn " + LANG_PWORD(actor->query_race()) + "!");
	return;

    case 1:
	command("say Hey! Don't do that! Don't spit in here!");
	return;

    default:
	command("say " + capitalize(LANG_PWORD(actor->query_race())) +
		" are such rude people!");
    }
}

void
giggle(object actor, string adverb)
{
    CHECK_ACTOR(actor);

    switch(random(3))
    {
    case 0:
	command("say Funny, eh " + actor->query_race() + "?");
	return;

    case 1:
	command("say Ah, " + LANG_PWORD(actor->query_race()) +
		" are such merry people.");
	return;

    default:
	command("giggle");
    }
}

