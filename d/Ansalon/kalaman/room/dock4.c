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
    set_short("End of a pier within the harbour of Kalaman on the Vingaard River");
    set_long("@@long_descr");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item(({"sign","signpost","wooden sign"}),
      BSN("A wooden sign hangs from slightly tarnished chains from a signpost that " +
	"stands at this pier. The sign swings slightly with the off shore breeze. You notice " +
	"writing on it that you can read."));
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

    add_exit(KROOM + "dock5","southwest",0);

    add_cmd_item(({"wooden sign","sign"}),"read","@@read_sign");

    reset_kalaman_room;
}

string
long_descr()
{
    string str;

    str = "You stand upon a pier within the harbour of the port city of Kalaman. " +
    tod_descr1() +
    "A wooden sign sways from a signpost here.";

    return BSN(str);
}

string
read_sign()
{
    say(QCTNAME(TP) + " reads the wooden sign hanging from the signpost.\n");
    write("\n" +
      "    ________________________________________\n" +
      "   |                                       |\n" +
      "   |                                       |\n" +
      "   |     The boat that docks here will     |\n" +
      "   |     take passengers to the wretched   |\n" +
      "   |     port town of Flotsam.             |\n" +
      "   |                                       |\n" +
      "   |                                       |\n" +
      "   ----------------------------------------\n\n\n");
    return "";
}
