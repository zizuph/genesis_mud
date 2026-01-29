inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 BUCK_DIR + "broad6","northeast",0,1

void
create_room()
{
   
   area = "just east of";
   areaname = "the Brandywine";
   land = "the Shire";
   areatype = 9;
   areadesc = "field";
   grass = "green";


    extraline = "The Brandywine is flowing swiftly beside you.  This barren "+
    "field has not much special about it, but there is an old sign with "+
    "faded writing on it.";

    add_item(({"sign","old sign"}),"This sign has some faded writing on "+
      "it, but it can't be read with just a casual glance.\n");
    add_item(({"writing","faded writing"}),"The writing is much too faded "+
      "to be read with just a quick glance. You should try reading it, not "+
      "just looking at it.\n");
   
    add_cmd_item(({"sign","writing"}),"read","The ferry is currently "+
      "undergoing repairs.\n");
   
   
   add_exit(EXIT1);
   make_the_room();
}
