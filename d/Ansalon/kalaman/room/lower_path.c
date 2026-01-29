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
    set_short("Below the breakwater at the base of the city wall");
    set_long("@@long_descr");

    add_item(({"path","paths"}),
      "Look at which path? The thin or unnoticeable path?\n");
    add_item("thin path","A thin path has been fashioned so that one can " +
      "climb the breakwater. Your guess is that it was made by smugglers.\n");
    add_item(({"unnoticeable path","almost unnoticeable path"}),
      "An almost unnoticeable path leads follows the city wall to the southeast.\n");
    add_item(({"walls","city wall","wall"}),
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
    add_item(({"breakwater","rocks"}),
      BSN("You stand at the bottom of the breakwater surrounding the " +
	"harbour of Kalaman. Here a small path has been fashioned, allowing " +
	"people travelling single file up to the top of the breakwater."));
    add_item(({"sky","blue sky"}),
      "Looking up, you see the sky, right where it was the last time you looked for it.\n");
    add_item(({"clouds","fluffy white clouds"}),
      BSN("Clouds sail across the sky above you."));

    add_exit(KROOM + "path1","up",0);
    add_exit(CITY + "o13","southeast",0);

    reset_kalaman_room();

}

string
long_descr()
{
    string str;

    str = "You stand at the bottom of the breakwater surrounding the harbour " +
    "of Kalaman. " +tod_descr1() +
    "A thin path has been fashioned so that people travelling single file can climb " +
    "the breakwater here, and another almost unnoticeable path leads off to the " +
    "southeast along the side of the wall surrounding Kalaman.";

    return BSN(str);
}

