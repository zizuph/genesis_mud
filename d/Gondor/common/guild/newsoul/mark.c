/*
 * /d/Gondor/common/guild/soul/mark.c
 *
 * With the command 'mark' a ranger will be able to leave a message for
 * other rangers in the form of leaves, rocks, or whatever. The command
 * can only be used outdoors.
 *
 * The following commands are possible:
 *
 * mark [<exit>] [for <name>] [danger] [anonymous]
 * mark [for <name>] [wait here] [anonymous]
 *
 * /Mercade, 11 April 1994
 *
 * Revision history:
 */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define MARK_OBJECT       (RANGER_DIR + "obj/mark_obj")

#define MARK_I_WAS_HERE   0
#define MARK_WAIT_HERE    1
#define MARK_DANGER_MSG   2
#define MARK_FOLLOW_ME    3

#define MARK_DEFAULT_HIDE 11

#define MARK_DESCRIPTIONS \
    ({ "no message", "wait here", "danger", "follow me" })

#define MARK_ANONYMOUS    "anonymous"
#define MARK_DANGER       "danger"
#define MARK_FOR          "for"
#define MARK_HERE         "here"
#define MARK_POORLY       "poorly"
#define MARK_WAIT         "wait"

#define MARK_MINIMUM_TRACKING 15

/*
 * Function name: is_exit
 * Description  : Check whether a certain word is an exit command in the
 *                room the player is in.
 * Arguments    : exit - the exit command to check
 * Returns      : 1/0  - It is or is not an exit command
 */
static int
is_exit(string exit)
{
    return (member_array(exit, ENV(TP)->query_exit_cmds()) >= 0);
}

/*
 * Function name: mark
 * Description  : Mark an exit with the secret sign of the rangers. Only
 *                other rangers will be able to see what it means. The
 *                sign can have different forms, like explained in the
 *                header of this file.
 * Arguments    : str - the command line argument
 * Returns      : 1/0 - success/failure
 */
int
mark(string str)
{
    object  mark;
    object  tp = TP;
    status  anonymous = 0;
    status  poorly = 0;
    string *words;
    string  exit = 0;
    string  name = 0;
    int     message = MARK_I_WAS_HERE;
    int     skill = tp->query_skill(SS_TRACKING);
    int     index;

    if (!strlen(str))
    {
        str = "here";
    }

    /* Only mark in outside rooms.
     */
    if ((ENV(tp)) && ENV(tp)->query_prop(ROOM_I_INSIDE))
    {
        NFN0("You cannot leave a mark indoors.");
    }

    if (skill < MARK_MINIMUM_TRACKING)
    {
        NFN0("Your tracking skill is not high enough to leave a mark. " +
            "Nobody would understand it.");
    }

    words = explode(str, " ");

    /* You may omit your personal sign if you choose to do so.
     */
    if (member_array(MARK_ANONYMOUS, words) != -1)
    {
        anonymous = 1;
        words -= ({ MARK_ANONYMOUS });
    }

    /* You may omit your personal sign if you choose to do so.
     */
    if (member_array(MARK_POORLY, words) != -1)
    {
	poorly = 1;
        words -= ({ MARK_POORLY });
    }

    /* You may add someone elses sign for a 'personal' message.
     */
    if ((index = member_array(MARK_FOR, words)) != -1)
    {
        name = words[index + 1];
        words = exclude_array(words, index, (index + 1));
    }

    /* You may signal danger.
     */
    if ((index = member_array(MARK_DANGER, words)) != -1)
    {
        message = MARK_DANGER_MSG;
        words = exclude_array(words, index, index);
    }
    /* You may ask someone to wait for you.
     */
    else if ((index = member_array(MARK_WAIT, words)) != -1)
    {
        if (words[index + 1] == MARK_HERE)
        {
            message = MARK_WAIT_HERE;
            words = exclude_array(words, index, (index + 1));
        }
    }

    switch(sizeof(words))
    {
        /* If nothing is left, it is an empty message.
         */
        case 0:
            exit = "here";
            break;
        /* It may be an exit you are signaling.
         */
        case 1:
            exit = words[0];

            if (words[0] == "here")
            {
                break;
            }

            if (!is_exit(words[0]))
            {
                NFN0("Mark which exit?");
                break;
            }

            if (message == MARK_I_WAS_HERE)
            {
                message = MARK_FOLLOW_ME;
            }

            break;
        /* Too many words left. Code didn't understand it.
         */
        default:
            NFN0("Mark which exit?");
            break;
    }

    /* Clone the mark object and set it up.
     */
    setuid();
    seteuid(getuid());
    mark = clone_object(MARK_OBJECT);

    mark->set_my_name( ((anonymous == 1) ? 0 : tp->query_real_name()) );
    mark->set_message(message);
    mark->set_exit(exit);
    mark->set_for_name(name);
    mark->set_skill(skill);

    mark->move(ENV(tp), 1);
    skill = tp->query_skill(SS_HIDE);
    mark->set_hide( ((poorly == 1) ? MIN(skill, MARK_DEFAULT_HIDE) : skill) );

    SAY(" bends to the ground and arranges some small rocks and twigs.");
    WRITE("You leave " +
        ((anonymous == 0) ? "a" : "an anonymous") +
        " mark" +
        (strlen(name) ? (" for " + capitalize(name)) : "") +
        ((strlen(exit) && (exit != "here")) ? (" pointing " + exit) : "") +
        ", saying \"" + MARK_DESCRIPTIONS[message] +
	"\". After arranging the small rocks and twigs, you hide them " +
	((poorly == 1) ? "poorly" : "as good as possible") + ".");
    return 1;
}
