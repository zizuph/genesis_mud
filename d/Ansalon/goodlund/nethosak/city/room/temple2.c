#include "/d/Ansalon/goodlund/nethosak/city/local.h"#include <stdproperties.h>
inherit MITHAS_IN;

void
create_mithas_room()
{
   set_short("Temple of the Stars");
   set_long("@@long_descr");
   add_item(({"golden", "veines"}),"The veines are thick and "+
              "covers all the walls, it has been made out of "+
              "the purest gold, and it glitters brightly in "+
              "the flickering torchlight.\n"); 
   add_item(({"walls", "murals"}),"The murals on the walls "+
              "are huge. They show some of the famous "+
              "battles that the minotaurs have won.\n"+
              "Other pictures show the different emperors "+
              "that the Empire has had. These were of course "+
              "choosen because they won all the fights in the "+
              "arena.\n");
   add_item(({"shadows"}),"The toches makes the shadows move "+
              "slightly, giving you an unpleasent feeling.\n");

   add_exit(MROOM + "temple4","north",0); 
   add_exit(MROOM + "temple1","west",0);
   add_exit(MROOM + "temple11","northeast",0); 
   add_exit(MROOM + "temple_entrance2","south","@@temple_entry", 0);
}

string
long_descr()
{ 
   return "You are standing inside the Temple of the Stars, "+
          "in Nethosak. This magnificent building seems "+
          "centuries old, it has been made out of pure grey "+
          "marble with golden veines caved into the rock. "+
          "Touches have lit up the hallway, casting "+
          "some suspicious looking shadows on the ground. "+
          "The walls have been decorated with "+
          "murals of the great battles that the minotaurs "+
          "have been in, while others show the different "+
          "emperors that the Empire has had. The temple "+
          "stretches itself into a hallway to the northeast "+
          "and to the north and west the temple continues.\n";
}

int
temple_entry()
{
   write("You descend the stairs to the temple... \n");
   return 0;
}

