#include "/d/Ansalon/goodlund/nethosak/city/local.h"#include <stdproperties.h>
inherit MITHAS_IN;

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
       "resembles a big black moon you realise "+
       "that this must be the sign of Nuitari. "+
       "The moon's waxing and waning influences "+
       "the powers of Black-robed mages. "+
       "Only astrologers, navigators, "+
       "black-robed magic users, and others "+
       "who watch the heavens are aware of "+
       "Nuitari's existence, for the moon "+
       "is only detected when it blots out "+
       "the light of stars.\n");

   add_exit(MROOM + "temple8","northeast",0); 
   add_exit(MROOM + "temple6","south",0);
}

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
           "have been placed. The ceiling has been made "+
           "in such a way that it makes a small arch, "+
           "making the hallway seem even bigger. Great "+
           "murals covers the walls, picturing some of "+
           "the gods on Krynn. The halway continues to "+
           "the northeast and south.\n";
}

