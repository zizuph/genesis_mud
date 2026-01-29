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
	"northwest and southeast."));
    add_item(({"wooden pier","pier"}),
      BSN("A wooden pier extends out into the Vingaard River to your northeast."));
    add_item(({"sky","blue sky"}),
      BSN("Above you is the sky, thankfully right where you last saw it."));
    add_item(({"clouds","fluffy white clouds","white clouds"}),
      BSN("Clouds sail across the sky above you."));
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
    add_item("warehouse",
      BSN("A warehouse stands to your south. It looks pretty empty from here."));
    add_item(({"great vingaard river","Vingaard River","Vingaard river","vingaard river",
	"river"}),
      BSN("You look upon the longest river in Ansalon, " +
	"the mighty Vingaard River, that " +
	"flows from the Turbidus Ocean down past Vingaard Keep into the heartland of " +
	"Solamnia. It is quite a sight."));


    reset_kalaman_room;
    add_exit(KROOM + "road5","northwest",0);
    add_exit(KROOM + "road4","southeast",0);
    add_exit(KROOM + "dock2","northeast",0);
    add_exit(KROOM + "warehouse","south",0);
}

int
no_go()
{
    write("To your northeast a dwarven wizard works frantically repairing ships. You " +
      "decide to leave him to his work and not bothering him by tramping up and " +
      "down the docks.\n");
    return 1;
}

string
long_descr()
{
    string str;

    str = "You are walking down a paved road at the edge of the harbour of Kalaman. " +
    tod_descr1() +
    "A wooden pier leads off to the northeast, and a warehouse stands to the south.";

    return BSN(str);
}

