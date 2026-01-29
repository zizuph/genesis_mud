// -*-C++-*-
// file name: Cabin  /d/Avenir/common/ships/faerun/cabin.c
// creator(s):       Lilith, 11/13/97
// last update:      Lucius, 2008: Converted to Faerun line.
// purpose:          Cabin of the Luminous
// note:        
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Genesis/ship/cabin";
#include "../ship.h"

private static string *snd = ({
    "The hammocks sway in rhythm to the gentle rocking of the ship.\n", 
    "The ship creaks softly.\n",
    "You can hear the sails snapping in the breeze.\n",
    "You hear the screech of a seabird.\n",
    "The smell of sea-salt floods the cabin on a puff of wind.\n",
});

private string
sounds(void)	{ return one_of_list(snd); }

public void
create_cabin(void)
{
    set_short("The passenger cabin of the Luminous");
    set_long("A spacious cabin providing comfortable accomodation for "+
        "passengers of the Luminous. Sturdy hemp hammocks padded with "+
        "silken cushions are strung from the beams overhead. The wooden "+
        "panels of the cabin walls gleam from hours of dutiful polish"+
        "ing, as do all of the brass fixtures. From all appearances, "+
        "the captain runs a tight ship.\n");
    add_item(({"hammock", "hammocks", "hemp", "cushion", "cushions", 
        "hemp hammocks", "silken cushions"}), 
        "Hammocks woven from hemp rope and padded with luxurious silken "+
        "cushions. They look quite comfortable.\n");
    add_item(({"wall", "walls", "cabin walls", "wooden panels", "panels"}),
        "The panels gleam with the mellow light of layers of dutifully "+
        "applied wax.\n");
    add_item(({"fixtures", "brass fixtures", "fixture"}),
        "There are brass fixures everywhere. They are heavily coated with "+
        "wax and buffed regularly, to prevent the salt-air from corroding "+
        "the metal.\n");
    add_item(({"beam", "beams"}), "Thick wooden beams support the roof of "+
        "the cabin. Hammocks have been hung from them.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(FRUN_DIR + "deck", "deck", 0);

    set_cabin_sound(sounds);
}
