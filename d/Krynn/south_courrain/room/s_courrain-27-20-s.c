#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include CLOCKH

inherit S_COURRAIN + "s_courrain-s";
inherit "/d/Emerald/blackwall/delrimmon/lib/water_effects.c";

#define HARD_TO_SWIM  45

public void
create_sea_room()
{
    set_special_short("over the dark waters of Leviathan's Deep");

    ::create_sea_room();

    remove_item("sea");

    add_item(({"water", "sea", "ocean", "courrain", "dark waters", 
        "waters", "south courrain ocean" }), 
        "The waters of the South Courrain Ocean here are rough and " +
        "dark, residing over a deep sea trench known as Leviathan's " +
        "Deep.\n");

    add_item(({"deep sea trench", "sea trench", "trench",
        "leviathan's deep", "leviathans deep"}),
        "Beneath the sea here is a deep sea trench known as Leviathan's " +
        "Deep. It is rumoured to be the home of merfolk who fiercely " +
        "protect their realm from intruders.\n");

    add_exit(ROOM + "uw5_1", "down", "@@swim_down", 1, 1);
    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    reset_sea_room();
}

int
swim_down()
{
    if(this_player()->query_skill(SS_SWIM) > HARD_TO_SWIM)
    {
       write("You dive down in to the dark waters, swimming powerfully through " +
          "the strong current.\n");
       say(QCTNAME(TP)+ " dives down in to the dark waters and disappears.\n");
       douse_flames(TP);
       return 0;
    }

    write("You try and dive down in to the dark waters, however the current hinders your " +
          "progress and you quickly return to the surface with a gasp. " +
          "You'll need to improve your swimming if you wish to swim deeper.\n");
    say(QCTNAME(TP) + " tries to dive into the dark sea, however isn't a strong enough " +
          "swimmer to pass through the strong current and returns to the surface with a " +
           "gasp.\n");

    return 1;
}