// -*-C++-*-
// file name: Deck   /d/Avenir/common/ships/faerun/deck.c
// creator(s):       Lilith, 11/3/97
// last update:      Lucius 2008: Converted to Faerun line.
// purpose:          Deck of the Luminous
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "../ship.h"
#include "/d/Avenir/smis/sys/statserv.h"

inherit "/d/Genesis/ship/deck";

private static string *snd = ({
    "Salt-spray stings your eyes.\n",
    "The wind caresses your cheek and leaves its salty flavour on your lips.\n", 
    "The sails ripple and snap in the sea breeze.\n",
    "The ship keels gently to port.\n",
    "You hear the screech of a seabird.\n",
    "Waves slam against the starboard side, spraying you with water.\n",
    "The ship rolls soothingly side-to-side.\n",
});

private string
sounds(void)	{ return one_of_list(snd); }

public void
create_deck(void)
{
    set_short("On the G.S. Luminous");
    set_long("The deck of this sailing ship was recently swabbed and "+
        "waxed, by the look of it. The sun glints off the brass railings "+
        "and the wind pulls strongly at the sails, making them ripple and "+
        "and snap with seeming impatience.\n");

    add_item(({"sails", "sail", "lateen sail"}),
        "The large, triangular sails are purest white. They billow in the "+
        "sea breeze.\n");
    add_item(({"deck"}),"It glows mellowly beneath its layers of wax.\n");
    add_item(({"mast", "masts", "yard", "yards", "rigging"}), 
        "There are two masts, each supporting two yards rigged "+
        "with lateen sails.\n");

    add_prop(OBJ_M_NO_ATTACK, "An eerie feeling overcomes you, raising"+
        "the hackles on your neck.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "An eerie feeling overcomes you, "+
        "raising the hackles on your neck.\n");

    add_exit(FRUN_DIR +"cabin", "cabin", 0);

    set_deck_sound(sounds);
}

public varargs int
disembark(string what)
{
    int res = ::disembark(what);

    if (res && file_name(environment(this_player()))[0..8] == "/d/Avenir")
	STATSERV_LOG_EVENT("avisits", "Port14 through ship to Faerun");

    return res;
}
