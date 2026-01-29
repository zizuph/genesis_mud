/*
 * /doc/examples/mobiles/action_blocking_npc.c
 *
 * A simple npc that demonstrates how to prevent actions from
 * being targeted at a living.
 * It also contains a very simple example showing how to make
 * an npc react to a certain class of actions.
 */

inherit "/std/monster";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

void
create_monster()
{
    set_name("ghost");
    set_adj("pale");
    set_race_name("ghost");

    set_long("A pale ghost.\n");

    set_stats(({ 20, 20, 20, 40, 40, 10 }));

    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 15);
    add_prop(LIVE_I_NEVERKNOWN, 1);
}

/*
 * Function name: block_action
 * Description:   This is called to see if the npc wants to prevent
 *                a certain action from being targeted on it.
 * Arguments:     string cmd - the name of the command that is being used
 *                object actor - the actor
 *                int cmd_attrs - the commands attributes (from cmdparse.h)
 * Returns:       0 - The command is not blocked
 *                1 - The command is blocked, but no failure message should
 *                    be giving.
 *                string - The command is blocked, and the return value
 *                         should be used as the failure message.
 */
mixed
block_action(string cmd, object actor, int cmd_attrs)
{
    /* See if the action is classified as a contact action */
    if (cmd_attrs & ACTION_CONTACT)
    {
        /* The action is contact, so return a failure message */
        return "The ghost is immaterial.  You cannot touch it!\n";
    }

    /* The action isn't classified as a contact action, so let it
     * continue.
     */
    return 0;
}

/*
 * Function name: emote_hook
 * Description  : This is called whenever an emotion is performed on this
 *                npc or a non-targeted emote is performed in the presence
 *                of this npc.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 *                object *targets - the targets of the emotion
 *                int cmd_attrs - the command's attributes (from cmdparse.h)
 */
void
emote_hook(string verb, object actor, string adverb, object *targets,
    int cmd_attrs)
{
    /* Only react to emotes classified as proximate */
    if (cmd_attrs & ACTION_PROXIMATE)
    {
        command("emote floats back for a moment.");
    }
}
