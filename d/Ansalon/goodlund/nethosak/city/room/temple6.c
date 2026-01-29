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
       "resembles a five-headed "+
       "dragon which is the sign of Takhisis "+
       "Lady of Chaos. The five heads each "+
       "symbolize each of the elements that "+
       "she controls, those being: Night, "+
       "Evil Dragons, Hatred, Intrigue and "+
       "Chaos.\n");

   add_exit(MROOM + "temple7","north",0); 
   add_exit(MROOM + "temple1","southeast",0); 
  
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
           "A few torches lit up this area, however it's "+
           "still fairly dark, which makes it very hard "+
           "to examine the different corners of the room. "+
           "A few niches have been carved into the walls "+
           "here, and in them some small stone statues "+
           "have been placed. The ceiling has been made "+
           "in such a way that it makes a small arch, "+
           "making the hallway seem even bigger. The "+
           "halway continues to the north, while going "+
           "to the southeast will take you to the "+
           "entrance of the temple.\n";
}

