/* created by Aridor  07/14/93 */
/* modified by Morrigan and Teth Jan 97 */

#include "../knight/guild.h"
#include <ss_types.h>
#include <macros.h>

inherit OUT_BASE;

void
create_vin_room()
{
    set_short("Drawbridge before Vingaard Keep");
    set_long("@@long_desc");

    AE(VROOM + "gate","north");
    AE("/d/Krynn/solamn/splains/room/xroad", "south", 0);

    AI(({"gate"}),"@@gate");
    AI(({"keep","vingaard keep","fortress","stronghold"}),"@@keep");
    AI(({"bridge","drawbridge"}),"@@drawbridge");
    AI(({"river","vingaard river","Vingaard River"}),"The Vingaard River " +
      "flows slowly past Vingaard Keep, en route to Kalaman.\n");
    AI("peninsula","The peninsula is an ideal site for a military " +
      "stronghold.\n");
    AI("battlements","The battlements of Vingaard Keep stand tall " +
      "against the sky. A flag and banner flutter above the gate.\n");
    AI("knights","The Knights on the battlements seem to be keeping " +
      "constant watch on the lands surrounding Vingaard Keep.\n");
    AI(({"flag","banner"}),"It is too far away to see any detail.\n");
    AI("crossroads","The crossroads to the south seem like an important " +
      "meeting place.\n");
}

string
long_desc()
{
    return tod()+season()+"This is a drawbridge that crosses over " +
    "Vingaard River. Beyond the bridge, to the north, stands Vingaard " +
    "Keep, a stalwart bastion of justice and goodness in a " +
    "land at war. The fortress stands on a type of peninsula, " +
    "such that it is surrounded by the Vingaard River on three sides. " +
    "Knights walk the battlements of the Keep. To the south is a " +
    "crossroads.\n";
}

keep()
{
    write("The keep is very ancient and has withstood the test of time"
      + " just as much as it has withstood numerous battles. The keep is"
      + " the stronghold for the Solamnian Knighthood, a powerful army"
      + " of knights devoted to the cause of good.\n");
    return "";
}

drawbridge()
{
    write("The bridge is about 30 feet long and made of iron. "
      + "If it is drawn, it seems impossible to reach the keep. But now, "
      + "the bridge is down and you can enter.\n");
    return "";
}

gate()
{
    int num_guards;
    object *guards = all_inventory(find_object("/d/Krynn/solamn/vin/room/gate"));
    write("The gate is north from here.");
    num_guards = sizeof((guards->id("knight") - ({ 0 })));
    if (num_guards > 2)
	write(" There are many knights guarding it.");
    else if (num_guards == 2)
	write(" There are two knights guarding it.");
    else if (num_guards == 1)
	write(" There is one knight guarding it.");
    write("\n");
    return "";
}
