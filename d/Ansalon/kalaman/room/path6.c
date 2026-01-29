#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

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
    add_item(({"beacon tower","tower","beacon"}),
      BSN("Before you stands a great white beacon tower, permanently lit so as to " +
	"guide ships safely into the harbour."));
    add_exit(KROOM + "path5","south",0);

    add_cmd_item(({"beacon tower","tower"}),"climb",
      "@@climb_tower");
    add_cmd_item(({"beacon tower","tower"}),"enter",
      "@@enter_tower");

    reset_kalaman_room;
}

string
long_descr()
{
    string str;

    str = "You stand at the end of the breakwater before a great white beacon tower. " +
    tod_descr1() +
    "A rocky path leads back towards the harbour to your south.";

    return BSN(str);
}

string
enter_tower()
{
    write("There is no way to enter the tower from the "+
      "path... perhaps you could from higher up?\n");
    say(QCTNAME(TP) + " looks for a way to enter "+
      "the beacon tower, but can't find one.\n");
    return "";
}
string
climb_tower()
{
    if(TP->query_skill(SS_CLIMB) > 20)
    {
	write("You skillfully climb up the side " +
	  "of the beacon tower.\n");
	say(QCTNAME(TP) + " skillfully climbs up the side of " +
	  "the beacon tower.\n");
	TP->move_living("M",KROOM + "tower",1,0);
	set_alarm(2.0, 0.0, "upset_seagull");
	return "";
    }
    write("You don't think you are skilled enough " +
      "to climb the beacon tower.\n");
    return "";
}

void
upset_seagull()
{
    write("As you make your way to the top of the " +
      "beacon tower, you surprise a group of seagulls!\n");
    say("As " +QTNAME(TP)+ " makes " +HIS(TP)+ " way up " +
      "the beacon tower, " +HE(TP)+ " upsets some seagulls!\n");
    write("A seagull poops all over you! Yuck!\n");
    say("A seagull poops all over " +QTNAME(TP)+ "! "+
      HE(TP)+ " doesn't look too impressed.\n");
}

