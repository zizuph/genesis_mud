// Ziggurat galleria (room10.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

inherit ZIG_GARDEN;

public void
zig_room(void)
{
    set_long("The soothing sound of trickling water comes from the aqueduct "+
      "that serves as the railing to the terrace as well as a ready source of "+
      "water to nurture raised planters of blue and white sweetpeas, bluebells "+
      "and bachelor buttons. Brilliant blue borage flowers, delphinium and "+
      "forget-me-nots grow in beds at the planters' feet and near the wall "+
      "of the Ziggurat. White flowering plants cascade down the crevices "+
      "of the wall creating the illusion of a waterfall. Smooth grey river "+
      "rocks define an oval of thick silvery grass east of the white flagstone "+
      "path that looks like a perfect place for a picnic or to lie a while "+
      "and watch the iridescent fluctuations of the Source above.\n");

    add_exit("room11", "south", "@@exit_string");
    add_exit("room9", "north", "@@exit_string");
}

static void
garden_items(void)
{
    ::garden_items();

    add_views("From this side of the "+
      "Ziggurat you can see some of the High Lord Executioner's enclave "+
      "to the northeast, opulent noble houses circle the High Lord's "+
      "palace on the central hill.", "enclave, giving it");

    add_rock("carved three wavy lines", ", the symbol of Hizarbin");

    add_item(({"white plant","flowering plant","white plants",
	"flowering plants","white flowering plants","white flowering plant",}),
      "White flowering plants cascade down the crevices "+
      "of the wall creating the illusion of a waterfall.\n");

    remove_item("grass");

    add_object(ZIG_RLG + "grass_r10", 1, 0 );
}

static void
garden_flowers(void)
{
    add_flower("borage", "bright blue");
    add_flower("delphinium", ({"light blue", "deep blue", "purple-blue", "white"}));
    add_flower("sweetpea", ({"blue", "white",}));
    add_flower("bluebell");
    add_flower("forget-me-not", ({"blue", "white",}));
    add_flower("bachelor's button", ({"blue", "white", "gray-blue"}));
    ::garden_flowers();
}

