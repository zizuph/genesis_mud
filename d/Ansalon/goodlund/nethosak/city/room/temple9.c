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
       "looks like a small sea-turtle, "+
       "with two emerald eyes. You recognice this "+
       "as being the statue of Zeboim the Sea Queen "+
       "As creator of the sea, tempests, and "+
       "weather, Zeboim receives petitions and "+
       "sacrifices from seamen wishing good weather "+
       "and safe journey. Though some manage to avoid "+
       "her rage, others who displease her through "+
       "some real or imagined slight never see harbor "+
       "again.\n");       

   add_exit(MROOM + "temple10","southeast",0); 
   add_exit(MROOM + "temple8","west",0); 

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
           "A few torches light up this area, casting a "+
           "gloomy glow on the entire hallway. "+
           "A few niches have been carved into the walls "+
           "here, and in them some small stone statues "+
           "have been placed. The ceiling has been made "+
           "in such a way that it makes a small arch, "+
           "making the hallway seem even bigger. The "+
           "halway continues to the southeast and "+
           "west.\n";
}

