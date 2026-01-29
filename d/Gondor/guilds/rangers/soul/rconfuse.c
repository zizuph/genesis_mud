/*
 * /d/Gondor/guilds/rangers/soul/rconfuse.c
 *
 * Included in the soul. Ability for Rangers to confuse the trail to
 * make it appear that some other race or animal has been through the room.
 *
 * Original coder unknown, probably Elessar no later than January 1995
 *
 * Modification log:
 * 13 April 2001 Gwyneth: General cleanup and move.
 */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define RACE_ARRAY ({ "half-elf", "wolf", "hobgoblin", "elf", "gnome", \
                      "dwarf", "human", "goblin", "kender", "wraith", \
                      "animal", "horse", "hobbit", "minotaur", "orc" })

/* Function name: rconfuse
 * Description  : Makes the trail appear to be from a random race or
 *                animal if successful.
 * Arguments    : string str - the argument
 * Returns      : 1 on success, 0 on failure
 */
public int
rconfuse(string str)
{
    object room = this_player()->query_prop(LIVE_O_LAST_ROOM);
 
    if (!strlen(str) || !parse_command(str, ({}), "[the] 'trail' [behind] [me]"))
    {
        notify_fail("Confuse the trail?\n");
        return 0;
    }

    if (this_player()->query_skill(SS_TRACKING) +
      this_player()->query_stat(SS_INT) / 10 > 35 + random(66))
    {
        room->add_prop(ROOM_S_DIR,({ one_of_list(room->query_exit_cmds()),
            one_of_list(RACE_ARRAY) }));
    }

    write("You do your best to confuse the trail behind you.\n");
    say(QCTNAME(this_player()) + " bends downs and does something " +
        "to the trail behind " + this_player()->query_objective() + ".\n");
    return 1;
}

