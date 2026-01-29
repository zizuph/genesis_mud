#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_short("Harbour road on the Vingaard River outside of Kalaman");
    set_long("@@long_descr");

    add_item(({"paved road","road"}),
      BSN("You stand upon a paved road that leads " +
	"to the northwest. A path branches off it to the east that heads along the " +
	"breakwater of the harbour."));
    add_item("path",
      BSN("A path leads off to the east towards the breakwater of the harbour."));
    add_item("breakwater",
      BSN("The breakwater of Kalaman consists of a great stone wall that extends out " +
	"into the Vingaard River, protecting the harbour."));
    add_item(({"wooden pier","pier"}),
      BSN("A wooden pier extends out into the Vingaard River to your northeast."));
    add_item(({"sky","blue sky"}),
      BSN("Above you is the sky, thankfully right where you last saw it."));
    add_item(({"clouds","fluffy white clouds","white clouds"}),
      BSN("Clouds sail across the sky above you."));
    add_item(({"pier","dock"}),
      "You stand upon a sturdy wooden pier.\n");
    add_item("harbour",
      BSN("The harbour of Kalaman is situated on the deep estuary of the Vingaard River. " +
	"Here white-winged ships from all over the realms lie at anchor."));
    add_item(({"ships","white-winged ships"}),
      BSN("White-winged ships from all over lie at port here. You wouldn't be " +
	"surprised if a few of them would transport you to their next destination for " +
	"a small fee."));
    add_item("walls",
      "Great stone walls surround the city of Kalaman.\n");
    add_item(({"walled port city","port city","kalaman"}),
      BSN("Kalaman, the northeastern jewel of Solamnia, sits on the estuary of the great " +
	"Vingaard River."));
    add_item(({"great vingaard river","Vingaard River","Vingaard river","vingaard river",
	"river"}),
      BSN("You look upon the longest river in Ansalon, " +
	"the mighty Vingaard River, that " +
	"flows from the Turbidus Ocean down past Vingaard Keep into the heartland of " +
	"Solamnia. It is quite a sight."));

    add_exit(KROOM + "road2","northwest",0);
    add_exit(KROOM + "dock3","northeast",0);
    add_exit(KROOM + "path1","east",0);

    reset_kalaman_room;
}

string
long_descr()
{
    string str;

    str = "You are walking down a paved road at the edge of the harbour of Kalaman. " +
    tod_descr1() +
    "A wooden pier leads off to the northeast, while a path heads eastward along " +
    "the breakwater of the harbour.";

    return BSN(str);
}

