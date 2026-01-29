inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/desert/defs.h"
#include "/d/Cirath/gcamp/defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Before the Gith Fortress");
set_long("Looming before you, the massive stone fortress "
	+"resembles a massive stone beetle.  Its tall walls "
	+"gently slope inward near the top, giving anyone "
	+"atop the wall a clear view of anyone who happens to "
	+"be below.  The gaping maw of the entrance tunnel "
	+"stands before you, almost daring you to come in.  "
	+"Through this tunnel you can see what appears to be "
	+"tents and makeshift shelters.  You also are unable to "
	+"avoid the unpleasant smell of unwashed bodies.  "
	+"Someone has certainly been living here.\n");
add_item("fortress","A large stone fortress, most likely built "
	+"in the Age of Champions when war was the favored "
	+"pasttime of most of Athas's people.\n");
add_item("tunnel","A massive tunnel burrows through the wall and "
	+"into the compound.  Any remnants of a gate are gone.\n");
add_item(({"tower","towers","tall towers"}),
	"These towers rise high up above the fortress, clinging "
	+"to the cliff behind them liks some sort of parasitic "
	+"vine.\n");
add_item("walls","They stand roughly fifteen feet tall, and curve "
	+"inwards to provide better angles for any bowmen standing "
	+"across the top.\n");
add_item(({"tent","tents","shelter","shelters"}),
	"The look to be constructed of worn fabrics and scraps "
	+"of wood and rubble.  Only some decrepit creature would "
	+"live in a place such as this.\n");
    add_exit(DESERT + "p7","north");
    add_exit(CAMP + "c1","south");
    set_alarm(1.0,0.0,"reset_room");
}

