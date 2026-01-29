#pragma strict_types
#include "defs.h"

inherit "/std/room";

public int
check_valid_entry(void)
{
    int guru = VALID_GURU(TP);

    if (guru == -1)
    {
	// Player has already solved the quest.
	write("You hear a booming voice in your head: You have already "+
	    "passed through here, " + TP->query_name() + "!\n");
	write("A terrible wind blows out from the passage, preventing "+
	    "you from entering.\n");

	return 1;
    }
    else if (VALID_GURU(TP) != 1)
    {
	// Player not yet eligible to do the quest.
	write("A terrible wind blows out from the passage, preventing "+
	    "you from entering.\n");

	return 1;
    }

    write("You enter into the smooth passage.\n");
    return 0;
}

public void
create_room(void)
{
    set_short("landing");
    set_long("Looking over the dark, still water, this smooth "+
	"ledge is nearly on level with the sea. The massive face "+
	"of the eastern wall of Sybarus cavern rises up to unimaginable "+
	"heights to the east. Carved into the very wall, with exactness "+
	"incongruous to the irregularity of the cavern face, "+
	"is a smooth passageway that slopes downwards.\n");

    add_item(({"sea","water"}), "The sea stretches out to the west, "+
	"its black surface unmarred by a ripple. Faint lights can be "+
	"discerned far to the west and southwest.\n");
    add_item(({"light","lights"}), "The lights over the sea are faint "+
	"and indistinct.\n");
    add_item(({"face","wall","eastern face","cavern"}), "The eastern "+
	"face rised up to dizzying heights, jagged and craggy. Far, far "+
	"above, you can barely make out the laced pattern of the "+
	"Source, providing a soft glow to the area. Carved into "+
	"the wall is a smooth passage that descends to the east.\n");
    add_item(({"passage","hall","east","passageway"}),
	"The passageway is carved into the eastern face of the cavern, "+
	"but seems to by formed, somehow, of a different rock that the "+
	"cavern face itself. The walls of the passage are limestone, and "+
	"the floor constructed from irregular slate tiles.\n");
    add_item(({ "ledge","landing" }), "The ledge upon which you stand "+
	"is smoothed, running to a long lip that curved down into "+
	"the black waters.\n");

    add_cmd_item(({"water","sea"}), "drink", "That would be unwise.\n");
    add_cmd_item(({"wall","face","cavern"}), "climb", "There are no "+
	"outcroppings close enough to the ground for you to be "+
	"able to reach.\n");

    add_exit("entry_passage1", "east", check_valid_entry);
}
