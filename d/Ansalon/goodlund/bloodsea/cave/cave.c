// Arman Feb 2018: Beach cave

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>   
 
inherit MITHAS_IN;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "beach","intertide", }) );

object skeleton;

void 
reset_mithas_room()
{
    if(!objectp(skeleton))
    {
        skeleton = clone_object("/d/Ansalon/goodlund/bloodsea/cave/sailor_corpse");
        skeleton->move(TO, 1);
    }

    set_searched(0);
}

void
create_mithas_room()
{
   set_short("deep cave overlooking the Vingaard River");
   set_long("@@long_descr"); 

    add_item(({"coastline","estwilde","foothills","rugged foothills",
       "barren coastline","hills", "riverbanks","solamnia"}),
       "From the mouth of the cave you can make out the barren coastline of Estwilde, a " +
       "land of rugged foothills, while far to your northwest you can just make out the " +
       "riverbanks of Solamnia.\n");
    add_item(({"river","vingaard river"}),
       "You find yourself overlooking the longest river in Krynn, the Vingaard River, from " +
       "a cave formed in the steep cliffs on the Estwilde side of the bank.\n");
    add_item(({"steep banks","banks","bank","high cliffs","cliffs","cliffside"}),
       "The banks of the eastern side of the Vingaard River are quite steep here, to the " +
       "point where high cliffs have formed. You stand at the entrance of a deep cave " +
       "formed in the cliffside that overlooks the river not far beneath you.\n");
    add_item(({"deep cave","cave"}),
       "@@long_descr");
    add_item(({"markings","wall","lines"}),
       "Along one wall of the cave it looks like someone has scraped numerous lines, " +
       "as if marking the passage of time. The count reached thirteen before ceasing.\n");
    add_item(({"stench","foul stench"}),
       "The cave is filled with the stench of death and decay. Something or someone " +
       "died in here.\n");

    add_exit("/d/Ansalon/goodlund/bloodsea/room/courrain/1d","out","@@exit_cave");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"cave"}), 2);

   reset_mithas_room();     
}

int
exit_cave()
{
   write("You dive from the entrance of the cave into the river beneath you.\n");
   say("From the entrance of the cave " +QTNAME(TP)+ " jumps into the Vingaard River.\n");
   return 0;
}

string
long_descr()
{ 
   return "You stand in a deep cave formed within the high cliffs overlooking "+
          "the Vingaard River. The cave is largely unremarkable with the exception " +
          "of a wall covered with markings, and that the cave is filled with the foul " +
          "stench of death and decay.\n";
}

