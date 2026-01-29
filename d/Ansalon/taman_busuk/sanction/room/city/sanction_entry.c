#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit SANCOUTROOM;

void
create_sanction_room()
{
    set_short("northern pass overlooking Sanction");
    set_extra_long("Here the high cliffs of the Doom Ranges open to " +
      "the south, overlooking the grim port city of Sanction. A path " +
      "leads down in to the narrow valley into the city.");

    add_item(({"hot lava stream","lava stream","river",
	"flow","lava flow",
	"river of molten rock","lava"}),
      "From the east a lava river runs past you to the west and " +
      "into the harbour. The heat from this river is staggering, " +
      "and you feel faint standing at this distance from it.\n");
    add_item(({"stone bridge","bridge"}),
      "A stone bridge crosses the river of lava to your north. " +
      "How it was constructed is anyones guess.\n");
    add_item(({"stone tower","tower"}),
      "This stone tower is of strange design, rising two stories to " +
      "a flat platformed roof. It stands on the very edge of " +
      "the lava flow, so how long it lasts standing there cannot " +
      "be any great time span.\n");

    add_exit(SCITY + "street25","southwest",0);
    add_exit("/d/Krynn/throtyl/rooms/throtyl-16-16-5", "north", 0, 1);

}
