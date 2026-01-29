#pragma save_binary
#pragma strict_types

#include "../../rooms/forest/_defs.h"
#include <filter_funs.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDCAPTAIN;

static void
create_captain()
{
  ::create_captain();
    set_name("tristran");
    add_name("sailor");
    set_living_name("tristran");
    set_race_name("elf");
    add_adj("young");
    add_adj("calm");

    set_chat_time(25);
    add_chat("The sea is a wonderful place to spend time.");
    add_chat("It's always safer to sail along the shores.");
    add_chat("Be careful when you leave the ship.");
    add_chat("When in Faerie, be sure to visit Menerial, the Chief Delegate. " +
        "He may need help.");
    add_chat("I have heard orcs are slowly moving into Faerie.");

}
