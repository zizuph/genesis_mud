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
    set_short("At the end of the breakwater before a beacon tower");
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
      "On top of the breakwater a path winds it's way amongst the rocks.\n");
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
    add_item(({"beacon tower","tower"}),
      BSN("Before you stands a great white beacon tower, permanently lit so as to " +
	"guide ships safely into the harbour."));
    add_exit(KROOM + "path9","west",0);

    add_cmd_item(({"beacon tower","tower"}),"climb",
      "@@climb_tower");

    reset_kalaman_room;
}

string
long_descr()
{
    string str;

    str = "You stand at the end of the breakwater before a great white beacon tower. " +
    tod_descr1() +
    "A rocky path leads back towards the harbour to your west.";

    return BSN(str);
}

string
climb_tower()
{
    return BSN("You decide that climbing the beacon tower would be about " +
      "as interesting as listening to a gnome recite his or her full name, and thus " +
      "decide not to climb it.");
}

