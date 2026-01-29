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
    set_short("Atop a rocky path on the breakwater of Kalaman harbour");
    set_long("@@long_descr");

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
    add_item(({"path","rocky path"}),
      "On top of the breakwater a path winds its way amongst the rocks.\n");
    add_item(({"breakwater","rocks"}),
      BSN("The breakwater of the harbour of Kalaman, there to protect it from the " +
	"elements, as well as from pirates and dragonarmy vessels."));
    add_item(({"harbour","kalaman","pier"}),
      BSN("Looking down upon the harbour of Kalaman, you see many piers stretch out " +
	"like fingers into the Vingaard River."));
    add_item(({"sky","blue sky"}),
      "Looking up, you see the sky, right where it was the last time you looked for it.\n");
    add_item(({"clouds","fluffy white clouds"}),
      BSN("Clouds sail across the sky above you."));

    add_exit(KROOM + "path9","east",0);
    add_exit(KROOM + "path7","west",0);

    reset_kalaman_room;
}

string
long_descr()
{
    string str;

    str = "You stand upon a rocky path that heads along the top of the breakwater " +
    "guarding the harbour of Kalaman. " +
    tod_descr1() +
    "The path continues to your east and west.";

    return BSN(str);
}

