/*
 *  /d/Gondor/rhovanion/mirkwood/lib/enchanted_river.c
 *
 *  Library to add commands relevant to the enchanted river. Any interaction
 *  with the river will result in the player being poisoned with a sleeping
 *  poison.
 *
 *  Created by Eowul, June 6th, 2015
 *
north_forest/r05/f28
north_forest/r04/f27
north_forest/r04/f26
north_forest/r03/f25
north_forest/r03/f24
north_forest/r02/f23
north_forest/r02/f22
north_forest/r01/f21
north_forest/r01/f20
north_forest/r00/f19
central_forest/r16/f18
central_forest/r15/f18
central_forest/r14/f19
central_forest/r13/f20
central_forest/r12/f21
central_forest/r11/f22
central_forest/r10/f23
central_forest/r09/f24
central_forest/r08/f25
central_forest/r07/m26

swim river
enter river
cross river
drink from river
search river

*/

#include <macros.h>
#include "../defs.h"

private void 
poison_player(object player)
{
    setuid();
    seteuid(getuid());

    object poison = clone_object(MIRKWOOD_OBJ_DIR + "enchanted_river_poison");
    poison->move(player, 1);
    poison->start_poison(this_object());
}

int
swim_cmd(string args) 
{
    if (!args || !parse_command(args, ({}), "[the] [enchanted] 'river' / 'water'")) {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    write("You prepare to swim the enchanted river, but as you place your "
        + "foot in the water, you feel a sudden numbness run up your leg. "
        + "Before you know it, you tumble back towards the shore, sound "
        + "asleep before you even hit the ground.\n");
    say(QCTNAME(this_player()) + " places " + this_player()->query_possessive()
        + " foot in the river, then suddenly turns pale and falls on the "
        + "ground, as if fast asleep.\n");

    poison_player(this_player());
    return 1;
}

int
drink_cmd(string args)
{
    if (!args || !parse_command(args, ({}), "[water] [from] [the] [enchanted] "
        + "'river' / 'water'")) {
        notify_fail("Drink what from what?\n");
        return 0;
    }

    write("You kneel near the river, but as you touch the water with your "
        + "cupped hand, you feel a coldness run up your arm. You drop to the "
        + "side, sound asleep.\n");
    say(QCTNAME(this_player()) + " kneels near the river, but as " 
        + this_player()->query_pronoun() + " touches the water, "
        + this_player()->query_pronoun() + " suddenly turns pale and "
        + "falls to the ground, as if fast asleep.\n");

    poison_player(this_player());
    return 1;
}

int
search_cmd(string args)
{
    if (!args || !parse_command(args, ({}), "[the] [enchanted] 'river' / 'water'")) {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    write("You quickly scan the river, then kneel at the shore and dip "
        + "in your hand to examine the water more closely. Suddenly a "
        + "numbness runs up your arm and you drop the the ground, "
        + "fast asleep.\n");
    say(QCTNAME(this_player()) + " kneels near the river, but as " 
        + this_player()->query_pronoun() + " touches the water, "
        + this_player()->query_pronoun() + " suddenly turns pale and "
        + "falls to the ground, as if fast asleep.\n");

    poison_player(this_player());
    return 1;
}

void
init_enchanted_river()
{
    add_action(swim_cmd, "swim");
    add_action(swim_cmd, "enter");
    add_action(swim_cmd, "cross");
    add_action(drink_cmd, "drink");
    add_action(search_cmd, "search");
}