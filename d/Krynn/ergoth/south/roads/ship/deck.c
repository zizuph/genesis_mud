#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/std/deck";

string sounds()
{
    switch(random(4))
    {
        case 0:
            return "The ship heels leeward.\n";
            break;
        case 1:
            return "The sharp bow cuts through a large wave.\n";
            break;
        case 2:
            return "The ship changes bearing.\n";
            break;
        case 3:
            return "A gale of wind fills the sails.\n";
            break;
        default:
            return "You feel like puking.\n";
            break;
    }
}       

void create_deck()
{
    set_short("The deck of a short clipper");
    set_long("This small and narrow ship is designed for speed rather than "
        + "freight. Many lengths of rigging run to and from the ship's three "
        + "masts. There is a door to the cabin and a hatch to the cargo "
        + "hold.\n");
    add_item("rigging", "A web of rope and chain is weaved across the ship, "
        + "giving the sailors control of their craft.\n");
    add_item(({"mast","masts"}), "Three masts rise from the deck, providing "
        + "support for the ship's many sails.\n");
    add_item(({"sail", "sails"}), "Despite several patches in plain sight, "
        + "the sails appear to be in good condition. They are quite clean "
        + "and billow pleasantly in the wind.\n");
    add_item(({"sailors"}), "At least half-a-dozen sailors are shouting and "
        + "running about to keep this vessel in operation.\n");
    add_item("door", "The door is closed and apparantly locked from the "
        + "inside.\n");
    add_item("hatch", "The hatch leads below deck, to the cargo hold.\n");
    set_deck_sound("@@sounds@@");
}

int try_open(string args)
{
    if("door" == args)
    {
        write("You tug on the door, but it is locked from the inside.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " tries to open "
            + "the door to the cabin, but it is locked.\n", this_player());
        return 1;
    }

    if("hatch" == args)
    {
        write("You approach the hatch, but a sailor stops you.\nThe sailor "
            + "says: You've got no business below deck.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " approaches the "
            + "hatch, but a sailor stops " + HIM(this_player())
            + " from entering.\n", this_player());
        return 1;
    }

    return 0;
}

void init()
{
    ::init();
    add_action(try_open, "open");
}
