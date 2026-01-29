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
    set_short("paved road before the harbour gates of Kalaman");
    set_long("@@long_descr");

    add_item(({"harbour gates","harbour gate","gates","gate"}),
      BSN("To your southwest stand the guarded gates of Kalaman, the gates that " +
	"allow access to the city from the harbour."));
    add_item(({"paved road","road"}),
      BSN("You stand upon a paved road that leads " +
	"northwest and southeast."));
    add_item(({"sky","blue sky"}),
      BSN("Above you is the sky, thankfully right where you last saw it."));
    add_item(({"clouds","fluffy white clouds","white clouds"}),
      BSN("Clouds sail across the sky above you."));
    add_item(({"harbour","docks"}),
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
    add_item(({"office","office of the harbourmaster"}),
      BSN("To your west is the office of the harbourmaster. It looks kind of quiet."));

    add_exit(KROOM + "road1","northwest",0);
    add_exit(KROOM + "road2","southeast",0);
    add_exit(KROOM + "gate","southwest",0);
    add_exit(KROOM + "charter_room","west","@@go_west");

    reset_kalaman_room;
}

int
go_west()
{
    write("\n\nNote! Due to the imminent threat of the Red Dragonarmy, charter " +
          "costs have increased!\n\n\n");
    return 0;
} 

string
long_descr()
{
    string str;

    str = "You stand on a paved road outside the harbour gate that allows access from " +
    "the docks to the city of Kalaman. " +
    tod_descr1() +
    "The harbour gate is to your southwest, while the office of the harbourmaster " +
    "is to your west.";

    return BSN(str);
}

