#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    add_prop(ROOM_S_DARK_LONG, "A dark passage.\n");

    set_short("A dark passage");
    set_long("You are travelling down a dark passage.\n"+
      "You can barely see this passageway, lucky for you. "+
      "From what can be seen by the little light visible, you almost wish "+
      "that there was no light...almost. Indescribable filth lies in "+
      "reeking piles across the ground while crawling along the walls and "+
      "ceiling are dozens of bugs. Dark passages lead to the west and east.\n");

    add_item(({ "filth", "reeking piles", "piles", "reeking pile", "pile" }),
      "It is too disgusting to adequately describe. It is scattered across "+
      "the floor.\n");

    add_item(({ "walls", "wall", "ceiling" }),
      "The passage is made entirely of mud, kept wet from some nearby "+
      "water source. It surprises you that the passage manages to stay up, "+
      "despite the lack of supports. Dozens of bugs are swarming along the "+
      "passage walls and ceiling.\n");

    add_item(({ "bugs" }),
      "Filthy creatures! Cockroaches, centipedes and other nasty critters "+
      "are wandering across the passage, probably looking for food.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur", "west");
    add_exit(CVAN + "lot/ur4", "east");
}
