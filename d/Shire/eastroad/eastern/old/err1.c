#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err15","west",0,1
#define EXIT2 ERE_DIR + "err2","southwest",0,2
#define EXIT3 ERE_DIR + "err9","east",0,1
#define EXIT4 "/d/Shire/common/rivendell/ford1","northeast","@@check_good"

void
create_er_room()
{

    area = "near";
    areaname = " the River Bruinen";
    land = "Eriador";
    areatype = 8;
    areadesc = "wooded area";
    grass = "green";

    extraline = "To the northeast is a stone bridge crossing the river "+
    "just above a roaring waterfall. "+
    "To the southwest, the Great East Road zig zags through a "+
    "heavily wooded area, on a very steep rising grade. The "+
    "Misty Mountains loom over three sides of the valley "+
    "across the bridge.";

    add_item(({"river","river bruinen"}),"The River Bruinen rushes "+
      "under the stone bridge with a roar, giving credence to its "+
      "historical name, 'Loudwater'. The river has it's origins in "+
      "the peaks of the Misty Mountains and passes through the "+
      "eastern and southern borders of the valley of Rivendell.\n");

    add_item(({"falls","waterfall"}),"The raging waterfall covers "+
      "the stone bridge and the adjacent road with water from the "+
      "mist it casts high into the air.\n");
    add_item(({"bridge","stone bridge"}),"The stone bridge has no handrails and seems "+
      "rather treacherous to cross. The mist and "+
      "spray from the raging waterfall causes the stones to be very "+
      "slippery.\n");
    add_item(({"mountains","misty mountains"}),"The Misty Mountains mysteriously "+
      "loom over Rivendell. There is a white mist covering their peaks "+
      "giving rise to thier name. One must wonder if there isn't "+
      "much adventure and danger in and over the mountains.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    add_exit(EXIT4);
}
check_good()
{
    if (TP->query_alignment() < 200 )
    {
	write ("The river rises and sweeps you back to the shore.\n");
	return 1;
    }
    return 0;
}
