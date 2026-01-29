/* /d/Ansalon/goodlund/nethosak/docks/room/nest01.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("In the lookout");
    set_long(
       "The large lookout nest slowly rocks back and forth in the " +
       "the strong gusts of wind that are blowing in from the bay.  " +
       "From here, you can see the entire city and bay region.  The " +
       "city stretches out to the north and east, ending where the " +
       "rocky terrain begins.  Roughly a days journey away, mountains " +
       "rise in the east, the snow capped peaks stuck in some of the " +
       "low clouds.  To the south and north the rocky terrain " +
       "continues, broken up by patches of small forest.  The bay " +
       "becomes the Blood Sea to your west, where rough and stormy " +
       "waters await those brave, or foolhardy, enough to meet the " +
       "challenge.\n");

    add_item(({"lookout","nest"}),
      "About 5 feet in width all around, the nest is made from " +
      "a sturdy wood that has been patched up several times.  " +
      "To trust the railing, however would be a mistake, as one " +
      "accidental slip could spell death.  One of the reasons the " +
      "many ropes lie about the nest is to help prevent this.\n");
    add_item("city",
      "The city stretches out to the north and east, ending " +
      "where the rocky terrain begins.  " +
      "All the buildings appear to be of the greatest workmanship and " +
      "labor that could be afforded.  However, a smoggish brown " +
      "undertones everything, giving the city a look of neglect. " +     
      "The massive buildings of stone are spread throughout the " +
      "city.  However, two of them stand out as the most grandiose " +
      "and vast.  One, is a large stone arena styled in that of an " +
      "ancient ampitheater.  The other is a large domed structure " +
      "covered in statues and carvings.\n");
    add_item("terrain",
      "Mostly rocky, the wilderness surrounding the city looks " +
      "far from hospitable.  Travelling would be very treacherous " +
      "and riding a horse over it would be impossible.  In some " +
      "spots a small patch of woods has grown, giving shelter " +
      "to not only the native life, but also foolhardy travellers.\n");
    add_item("mountains",
      "Roughly a days journey away, mountains rise in the east, " +
      "the snow capped peaks stuck in some of the low clouds.  " +
      "From this distance no particulars can be made out, other " +
      "then there treacherous slopes.\n");
    add_item("clouds",
      "Blown in from the sea by the stongs winds, these small " +
      "clouds are dark and pillowy.\n");
    add_item("peaks",
      "From this distance it is hard to make out any particulars, " +
      "other then the peaks are covered in snow.\n");
    add_item("forest",
      "Oddly out of place, these small patches of woods have " +
      "risen up throughout the rocky landscape.\n");
    add_item("bay",
      "The large bay is a natural protection for the port of " +
      "the city.  Not only does it hide the port from others but " +
      "running aground on a reef is a serious hazard for those " +
      "not knowing the layout of the bay.\n");

    add_cmd_item(({"down","out","out of lookout"}),
       "climb","@@climb_down");
}

string climb_down()
{    
   write("You climb down out of the lookout, using the ropes " +
      "to help you down.\n");
   say(QCTNAME(TP) + "climbs out of the lookout.\n");
   tell_room(DROOM + "mast01",QCNAME(TP) + " enters, climbing " +
      "ou of the lookout.\n");
   TP->move_living("out",DROOM + "mast01",1,0);
   return "";
}
