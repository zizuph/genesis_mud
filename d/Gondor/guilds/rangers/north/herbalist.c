/*
 * RoN Herbalist
 * Varian - January 2016
 */

inherit "/std/room";

#include "../rangers.h"

#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "check_exit.c"

static object inzilanu;

void

create_room()

{
    set_short("A hidden alcove");
    set_long("This alcove has been opened up from the northern corridor " +
        "of the underground hideout of the Rangers of the North. Huddled " +
        "up against the west wall of the alcove is a long wooden table " +
        "which is cluttered with dozens of glass jars, wooden canisters and " +
        "ceramic pots that appear to be filled with an enormous selection " +
        "of various herbs. Fortunately, the wafting aroma of the herbs " +
        "masks the cold musty smell which eminates from the grey stone " +
        "which seems to clad almost every surface of the hideout. You " +
        "can step out of the alcove by passing through the narrow arch " +
        "in the south wall.\n");
  
    add_item(({"herbs", "herb"}),
        "You strongly suspect that there is a great wealth of herbs hiding " +
        "within the various containers on the table here.\n");
    add_item(({"table", "long table", "desk", "wooden table"}),
        "This long sturdy table is made from a dark wood, polished smooth " +
        "from many years of use. There are many containers scattered " +
        "across the surface of the table, each seemingly full of herbs. " +
        "You might want to ask the ranger here if they are for sale!\n");
    add_item(({"canister", "canisters", "wooden canister",
            "wooden canisters"}),
        "Dozens of small wooden canisters rest on the table, their lids " +
        "unable to contain the fresh aroma of the herbs stored within.\n");
    add_item(({"jar", "jars", "glass jar", "glass jars"}),
        "Upon closer examination, you can see that these jars are each " +
        "filled a different herb. You feel reasonably confident that " +
        "you could purchase almost any herb in the world here!\n");
    add_item(({"container", "containers", "other container",
                "other containers"}),
        "There must be over a hundred different containers scattered " +
        "across the wooden table here! Made from wood, glass and even " +
        "ceramic, these containers seem to hold a massive wealth of " +
        "herbs here, all available for purchase.\n");
    add_item(({"pot", "pots", "ceramic pots", "ceramic pot"}),
        "Several ceramic pots have been placed on the table here, each " +
        "one of them stuffed with pungent leaves from various plants " +
        "found across the lands of Genesis.\n");
    add_item(({"ceiling", "up"}),
        "Much like the rest of the hideout, the ceiling has been crafted " +
        "from a dark grey stone.\n");
    add_item(({"down", "floor"}),
        "The dark grey of the stone here is slightly uneven, but still " +
        "smooth enough to walk comfortably upon.\n");
    add_item(({"stone", "grey stone"}),
        "This dark grey stone seems to have been the primary building " +
        "material for the foundation of this hideout.\n");
    add_item(({"west wall", "western wall"}),
        "There is a long table pushed up against the length of the " +
        "western wall, covered with dozens of small containers.\n");
    add_item(({"east wall", "eastern wall"}),
        "A rough grey stone covers the short length of the eastern wall, " +
        "broken up only by an iron torch stand.\n");
    add_item(({"north wall", "northern wall"}),
        "The rough grey stone to the north feels more like an angled " +
        "extension of the eastern wall in this small alcove.\n");
    add_item(({"south wall", "southern wall"}),
        "The southern wall is almost non-existant, there is just enough " +
        "room for the narrow arch which opens up into the corridor.\n");
    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");
    add_item(({"alcove", "here", "niche", "room"}),
        "This alcove has been opened up from the northern corridor " +
        "of the underground hideout of the Rangers of the North. Huddled " +
        "up against the west wall of the alcove is a long wooden table " +
        "which is cluttered with dozens of glass jars, wooden canisters and " +
        "ceramic pots that appear to be filled with an enormous selection " +
        "of various herbs. Fortunately, the wafting aroma of the herbs " +
        "masks the cold musty smell which eminates from the grey stone " +
        "which seems to clad almost every surface of the hideout. You " +
        "can step out of the alcove by passing through the narrow arch " +
        "in the south wall.\n");
    add_item(({"corridor", "northern corridor", "hideout"}),
        "Looking through the narrow arch, you can see a large tapestry " +
        "hanging on the far wall of the long corridor which runs through " +
        "the underground hideout.\n");
    add_item(({"arch", "narrow arch"}),
        "This narrow arch provides access back into the rest of the " +
        "hideout.\n");
    add_item(({"torch", "stand", "iron stand", "iron torch stand",
            "torch stand"}),
        "This iron stand holds a torch to provide a little bit of " +
        "light in this alcove.\n");
    add_item(({"tapestry", "hanging"}), "The tapestry shows one of the "
        + "most beautiful locations of the Second Age. You see a high and "
        + "steep mountain, Meneltarma, on the island of Numenor, the "
        + "ancestral home of the Dunedain. Numenor sank below the waves when "
        + "the last king, Ar-Pharazon, became too arrogant and challenged "
        + "the Valar.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(RANGERS_NOR_DIR + "n_corridor", "south");
    add_prop(ROOM_M_NO_SCRY, 1);

    reset_room();
}

reset_room() 
{
    if(!inzilanu) inzilanu = clone_object(RANGERS_NPC + "inzilanu.c");
    if (!present(inzilanu)) inzilanu->move_living("somewhere", this_object());
}