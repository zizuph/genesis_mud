#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>


inherit MITHAS_OUT;

void
reset_mithas_room()
{
   return;
}

create_mithas_room()
{
   set_short("Swimming in the Bloodsea");
   set_long("You are swimming in the red waters of the Bloodsea "+
            "close to the isle of Mithas. To the east beyond the "+
            "huge rocks that form the beach you see the Imperial city "+
            "of Nethosak, home of the mighty minotaurs. To the southeast "+
            "a small forest stretches itself to the east and south. To the "+
            "west you see the wooden pier. Thick wooden pillars have been "+
            "placed all around you to support the pier and warehouse which "+
            "lies above you. The sea continues in every direction.\n");

   add_item(({"water", "sea"}), "The water within the Blood Sea has "+
         "a strange and reddish color. Rumor has it that the color "+
         "is the result of the blood of many victims who lost their "+
         "lives during Krynn's most terrible hour, though it "+
         "could be the clay stirred up from the sea bottom by the "+
         "maelstrom.\n");

   add_item(({"pillar", "pillars"}), "The thick wooden pillars hold "+
           "the pier and warehouse above the water, small green and "+
           "brown seaweed has attached itself to the sides of the pillars.\n");

   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

   add_invis_exit(MROOM + "nowhere","north","@@no_go");
   add_invis_exit(MROOM + "nowhere","south","@@no_go");
   add_invis_exit(MROOM + "nowhere","west","@@no_go");
   add_invis_exit(MROOM + "nowhere","northeast","@@no_go");
   add_invis_exit(MROOM + "nowhere","northwest","@@no_go");
   add_invis_exit(MROOM + "nowhere","southeast","@@no_go");
   add_invis_exit(MROOM + "nowhere","southwest","@@no_go");
   add_invis_exit(MROOM + "sea2","east",0,4);
   add_exit(MROOM + "warehouse","up","@@enter_warehouse");
   add_invis_exit(MROOM + "nowhere","down","@@no_go");    

   reset_mithas_room();
}

int
no_go()
{
   write("The current is far to strong in that direction, "+
         "it will be too dangerous to swim there.\n");
   return 1;
}

int
enter_warehouse()
{
    write("You get a firm grip on the floor of the warehouse "+
          "and pull yourself up.\n");
    say(QCTNAME(this_player()) + " moves some floor boards, and leaves up.\n");
    return 0;
}

