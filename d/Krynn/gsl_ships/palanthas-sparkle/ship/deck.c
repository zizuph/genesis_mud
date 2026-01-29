#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit "/d/Krynn/std/gsl_deck";

#define NO_FISHING_LOCATION  "_live_i_no_fish"

void
create_room()
{
    ::create_shiproom();
    set_short("On the Palanthas-Sparkle airship");
    set_long("This is the open air deck of the airship, \"Omembo\". The wind "
        + "blows gustily shaking ropes and creaking the leather of the "
        + "huge, long leatherbound bladder of air above you. Steps lead "
        + "down into the cruising deck below. The view of the sky is "
        + "unprecedented.\n");

    add_prop(NO_FISHING_LOCATION, "You don't have the right bait or " +
        "equipment to catch the fabled flying fish!\n");
  
    add_item("wind", "You are completely exposed to the wind here and wonder "
        + "if a gust couldn't blow you off to your demise below.\n");
    add_item("deck", "The deck has a simple wooden design to keep it light. "
        + "Silk ropes keep the leather bladder in place above, and a steering "
        + "wheel is mounted aft near the wooden blades.\n");
    add_item("bladder", "The leatherbound bladder above has a surprising heat "
        + "emanating from it. Silk ropes bind it in place securely above.\n");
    add_item(({"wheel", "steering wheel"}), "A wooden steering wheel, not "
        + "unlike those of water bound ships, is mounted aft near wooden "
        + "blades.\n");
    add_item(({"wooden blades", "propeller"}), "Long wooden blades have been "
        + "affixed to the aft of the ship behind the steering wheel. They "
        + "turn swiftly by some means you cannot see and apparently push air "
        + "to drive the airship.\n");
    add_item(({"step", "steps", "cabin", "cruising deck"}), "Steps lead down "
        + "into the cruising deck below where travellers can take refuge from "
        + "the wind and elements.\n");
    add_item(({"sky"}), "The view of the sky is truly astounding. "
        + "Flying is truly the superior way to travel.\n");
  
    add_exit(ROWINGDECK, "down", 0);

    set_deck_sound("@@sounds");
    set_is_deck(1);
}

sounds()
{
    if(random(3))
    {
        return "A gust of wind creaks the leather of the ship as it groans in "
            + "response to maintain its flight path.\n";
    }

    return "The airship creaks as it floats effortlessly through the wind.\n";
}

public int
query_no_time()
{
    return 1;
}

