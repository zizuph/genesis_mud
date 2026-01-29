#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_IN;
 
object priest;

void 
reset_mithas_room()
{
    if(!objectp(priest))
    {
      priest = clone_object(MNPC + "templePriest");
      priest -> move(this_object());
    }
}
void
create_mithas_room()
{ 
   set_short("Temple of the Stars");
   set_long("@@long_descr");
  
   add_item(({"walls", "wall"}),"The walls are "+
       "made out of some strange marble, "+
       "perhaps it has been enchanted in "+
       "some way.\n");

   add_item(({"niches", "niche"}),"The niches "+
       "have been places with regular "+
       "intervals in the walls, and some "+
       "small statues has been placed in "+
       "them.\n");
      add_item(({"statues"}),"The statues looks "+
       "like the different gods in Krynn. "+
       "However one of the statues here has "+
       "been coated with gold and is "+
       "encrusted with jewels.\n");
  
   add_item(({"coated statue",
       "encrusted statue"}),"This statue "+
       "has the form of a skull you know that "+
       "this this the sign of Chemosh, Lord of "+
       "Death. He has control over all the undead "+
       "in Krynn, and he gains power by offering "+
       "the living eternal life. He was drawn by "+
       "Takhisis to Krynn. Because She needed a "+
       "lieutenant to marshal the legions of death.\n");

   add_exit(MROOM + "temple9","east",0); 
   add_exit(MROOM + "temple7","southwest",0); 

   reset_mithas_room();}

string
long_descr()
{ 
   return  "You are in a small hallway in the Temple of "+
           "the Stars in Nethosak. The walls have are "+
           "a bit darkern then the ones at the entrance. "+
           "However it's still remarkable beautiful, the "+
           "walls seems to shimmering slightly, slowly "+
           "changing color from black to grey and white. "+
           "A few niches have been carved into the walls "+
           "here, and in them some small stone statues "+
           "have been placed. Great murals covers the "+
           "walls, picturing some of the gods on Krynn. "+
           "The halway continues to the east and "+
           "southwest.\n";
}

