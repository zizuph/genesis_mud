#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;
#define E(ob)        environment(ob)

object temple_guard; 

void 
reset_mithas_room()
{
    if(!objectp(temple_guard))
    {
      temple_guard = clone_object(MNPC + "templeGuard");
      temple_guard->move(this_object());
   }
}

void
create_mithas_room()
{
   set_short("Entrance to the Temple");
   set_long("@@long_descr");
   add_item(({"plaque", "silvery"}),"The plaque reads:\n"+
            "  ______________________________ \n"+
            " |                              |\n"+
            " | The Holy Order of the Stars  |\n"+
            " |------------------------------|\n"+
            " | Visitors must show their     |\n"+
            " | respect to Sargonnas.        |\n"+
            " |                              |\n"+
            " |______________________________|\n");

   add_item(({"columns", "statues"}),"Examine which column?\n");

   add_item(({"first column", "first statue"}),"This huge column "+
     "has been carved in such a way that it looks like a huge "+
     "grey minotaur. He's dressed in a leather armour and he's "+
     "wielding a huge two-handed battle in both his hands. "+
     "His horns are enormous, and it looks like both of them "+
     "are decorated with etchings.\n");

   add_item(({"second column", "second statue"}),"This huge column "+
     "has been carved in such a way that it looks like a huge "+
     "grey minotaur. He's wielding a big serrated halberd in "+
     "both his hands and he is dressed in a robe that covers this "+
     "entire body. Around his waist is a small herb pouch, and "+
     "around his neck you notice the medallion of the High Temple. "+
     "His horns are enormous, and it looks like both of them "+
     "are decorated with etchings.\n");

   add_item(({"third column", "third statue"}),"This huge column "+
     "has been carved in such a way that it looks like a huge "+
     "grey minotaur. He's wielding two large two-handed sword in "+
     "both his hands and he is dressed in a thick banded mail. "+
     "His horns are enormous, and it looks like both of them "+
     "are decorated with etchings.\n");

   add_exit(MROOM + "temple1","north","@@temple_entry", 0); 
   add_exit(MROOM + "temple_entrance2","east",0);
   add_exit(MROOM + "road22","west",0);

   reset_mithas_room();
}

string
long_descr()
{ 
   return tod_descr()+ " You are standing at the entrance to "+
         "a great temple. It is constructed of pure grey "+
         "marble, and constructed in such a way that it "+
         "forms a circle. The temple stretches itself high "+
         "above all over buildings here making it "+
         "seem ever greater. Three large marble columns "+
         "has been placed here. Two at the entrances and one. "+
         "in the middle. All the columns resembles one of the "+
         "great minotaurs, however they are not quite the same. "+
         "To the north are some steps that lead further into "+
         "the temple, and to the east and west the road "+
         "continues. " +season_descr()+ ".\n";
}

int
temple_entry()
{
   if(objectp(temple_guard) && E(temple_guard) == this_object())
   {
       write("The powerful robed minotaur stands "+
             "in your way, blocking that exit.\n");
       return 1;
   }
   write("You assend the stairs to the temple... \n");
   return 0;
}

