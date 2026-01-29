#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

void 
reset_mithas_room()
{
    set_searched(0);
}

void
create_mithas_room()
{
   set_short("edge of a cliff on the isle of Karthay, before the ruins of a great tower");
   set_long("@@long_descr"); 


   add_item(({"black rocky cliffs","black cliffs","rocky cliffs","cliffs","cliff"}),
         "You stand at the top of the great cliffs of Karthay, overlooking the Bloodsea " +
         "of Istar to your south and west.\n");

   add_item(({"isle","island","isle of karthay","karthay"}),
         "You stand on the edge of a cliff on the isle of Karthay, the largest and northernmost " +
         "island of the Bloodsea. This island is known for its barren, hot plains and " +
         "high, rain-forested Worldscap mountains.\n");

   add_item(({"worldscap mountains","mountains"}), 
         "In the far distance to your northeast, the Worldscap mountains rise high into the " +
         "sky. It is rumoured a strange avian race make these mountains their home.\n");

   add_item(({"grasses","hardy grasses"}),
         "Thick and hardy grasses grow tall at the edge of the cliff.\n");

   add_item(({"trail","small trail"}),
         "A small trail between the hardy grasses continues along the edge of the cliff " +
         "to the west towards the ruins of a great tower.\n");

   add_item(({"ruins","tower","great tower","winston's tower","winstons tower","lighthouse"}),
         "To your west rises a prominent 130-foot-tall monolith, the ruins of " +
         "a great lighthouse that onced served as a beacon for travellers across the ancient "+
         "lands of Istar. Once one of the wonders of the world with pilgrims travelling many " +
         "miles to gaze upon this marvel, it in now long abandoned and rumours from " +
         "seafarers have it to be cursed by dark powers. There is a dark opening in the " +
         "wall of the tower here, allowing entry to it.\n"); 
   
   add_item(({"opening","dark opening"}),"There is a dark opening in the side of the ruined " +
         "tower here, allowing entry. A sense of dark and forbidding menace lingers beyond it.\n");

   add_item(({"bloodsea","sea","water","bloodsea of istar"}),
         "Far beneath you to your south and west, stretching out as far as the eye can see " +
         "is the Bloodsea of Istar. You can make out the occasional sail on the horizon, " +
         "however whether it is a minotaur, Saifhum, pirate, or Dragonarmy ship is anyones " +
         "guess.\n");

   add_item("sail","You see a sail in the distance, but can't tell what sort of ship it is.\n");

   add_cmd_item(({"tower","ruin","opening","dark opening","ruins"}),"enter",
      "@@enter_opening");

   add_exit(BISLAND + "cliff02","east",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"trail","beach","sand","sandy beach",
        "coastline","cliff" }), 2);

   reset_mithas_room();     
}

string
long_descr()
{ 
   return "You stand on the edge of a cliff on the isle of Karthay. Far below you " +
     "is the Bloodsea of Istar, stretching out to the south and west as far as the eye " +
     "can see. To your west rises the ruins of a great tower, once a lighthouse in the " +
     "days before the Cataclysm, it is now abandoned and slowly succumbing to the harsh winds " +
     "and weather of the Bloodsea.\n";
}

string
enter_opening()
{
    write("You enter the dark opening in the side of the tower.\n");
    TP->move_living("enters a dark opening in the side of the tower",
      "/d/Ansalon/goodlund/bloodsea/island/tower01",1,0);
 
    return "";
}