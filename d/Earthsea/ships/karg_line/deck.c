inherit "/d/Genesis/ship/deck";

#include "/sys/macros.h"
#include "defs.h"
#include "/sys/stdproperties.h"

void
create_deck()
{
    set_short("Inside of small boat");
    set_long("You are inside of a small boat. You see couple of "+
      "benches for passengers and rowing bench for captain. Pair of "+
      "rows lie near the rowing bench.\n");

    set_deck_sound("@@sounds");
    set_bump_sound("The boat stops at some damaged pier.\n");
}

string
sounds()
{
    object cap = present("stam", this_object());
    int i = random(4);

    switch(i)
    {
    case 0:
        return QCTNAME(cap)+" advances the boat through roaming sea.\n";
        break;

    case 1:
        return "You feel sick as boat rides some huge waves.\n";
        break;

    case 2:
        return "You hardly keep your balance as boat is thrown aside "+
          "by sudden gust of wind.\n";
        break;

    default:
        return "The boat sways slightly in the waves.\n";
        break;
    }
}

