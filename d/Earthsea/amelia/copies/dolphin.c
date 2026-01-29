#pragma strict_types

#include "/d/Earthsea/travellers/guild.h"

inherit TRAVELLERS_CARVING_STD;

void
create_carving()
{
    add_name("dolphin");
    set_short("wooden carving of a dolphin");
    set_long("This is a small carving about the size of your "+
      "hand, which depicts a dolphin leaping out of the sea. "+
      "The detail is intricate, and it looks very lifelike. On "+
      "the bottom is an inscription of two crossed axes over a "+
      "map of the world.\n");
}
