#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR +"err1","northeast",0,1
#define EXIT2 ERE_DIR +"err10","west",0,1

void
create_er_room()
{

    area = "not very far from";
    areaname = "Rivendell";
    land = "Eriador";
    areatype = 8;
    areadesc = "wooded area";
    grass = "green";

    extraline = ("The huge pine trees on each side of the road "+
      "meet overhead, forming a canopy that makes it feel like this "+
      "is a tunnel. Bends in the road make it difficult to see "+
      "what lays ahead.");

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
    add_item(({"tower","bell tower"}),"The bell tower rises high above the trees "+
      "in the valley of Rivendell.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
}
