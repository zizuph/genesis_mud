#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/goodlund/nethosak/city/obj/door.h"
inherit MITHAS_OUT;

void
create_mithas_room()
{
   object gate;
   set_short("Road to Nethosak");
   set_long("@@long_descr"); 
   add_item(({"note","Note"}), "The note reads:\n"+
                     "  .______________________________________. \n"+
                     "  |  o                                 o | \n"+
                     "  |                                      | \n"+
                     "  | Welcome travellers, to the city of   | \n"+
                     "  | Nethosak. Feel free to look around   | \n"+
                     "  | or browse through our shops.         | \n"+
                     "  | However we will not tolerate any     | \n"+
                     "  | pirates here. If any should be       | \n"+
                     "  | discovered, they will be executed    | \n"+
                     "  | immediately.                         | \n"+
                     "  |                                      | \n"+
                     "  | o                                 o  | \n"+
                     "  |______________________________________| \n");

    add_item(({"guardhouse","Guardhouse", "house", "House"}), "The "+
          "guard building is been made out of grey stone.\n");


    add_item(({"vegetation", "plants"}), "The vegetation is scattered "+
          "all over the beach however most of the plants grow near "+
          "the edge of the beach.\n");


    add_item(({"pier"}), "It's a very old and wooden pier, "+
      "it looks quite sturdy however.\n");

    add_item(({"footprint", "prints"}), "You "+
        "recognize the footprints as the prints of minotaurs, they "+
        "actually cover the entire trail.\n");

    add_item(({"trail", "road"}), "This trail is very "+
       "worn down, you can see some large footprints in the mud, "+
       "leading both to the east and west.\n");

    gate = clone_object(MOBJ + "city_gate1b");
    gate->move(this_object());

    add_exit(MROOM + "guardhouse1","northeast",0);
    add_exit(MROOM + "guardhouse2","southeast",0);
    add_exit(MROOM + "road2","east",0);    
   
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on a worn down "+
          "road near the city of Nethosak. The road "+
          "is very muddy and covered with large "+
          "minotaur footprints. To the northeast "+
          "and southeast a small guardroom has been "+
          "made to protect the city from various "+
          "assults from pirates and potential enemies. "+
          "The road stretches to the "+
          "east toward the center of the city and to the "+
          "west lies the beach." +season_descr()+ "A note "+
          "has been placed on one of the walls here.\n";

}
