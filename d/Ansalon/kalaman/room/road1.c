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
    set_short("Harbour road on the Vingaard River outside a strangely quiet inn");
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
    add_item(({"strangely quite inn","quite inn","inn"}),
      BSN("To your west an inn stands against the wall of the city of Kalaman, strangely " +
	"quiet. You would expect to hear the sounds of rowdy sailors from it, but you cannot " +
	"even hear the slightest murmer of conversation. A signboard hangs from above " +
	"the entrance to the inn."));
    add_item("signboard",
      BSN("The signboard depicts a stout dwarf reclining on a wooden stool with " +
	"a mug in one hand, and a smoking pipe in the other. Underneath it is scribed " +
	"'The Stout Dwarf Inn'."));

    add_exit(KROOM + "road3","northwest",0);
    add_exit(KROOM + "inn","west",0);
    add_exit(KROOM + "dock5","northeast",0);
    add_exit(KROOM + "road5","southeast",0);


    reset_kalaman_room;
}

string
long_descr()
{
    string str;

    str = "You are walking down a paved road at the edge of the harbour of Kalaman. " +
    tod_descr1() +
    "To your west in the entrance to a strangely quiet inn, while a wooden pier leads out " +
    "onto the Vingaard River to your northeast.";

    return BSN(str);
}

