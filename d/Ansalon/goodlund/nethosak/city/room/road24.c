#include "/d/Ansalon/goodlund/nethosak/city/local.h"#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Road South of Nethosak");
    set_long("@@long_descr"); 
   
    add_item(({"guardhouse","Guardhouse", "house", "House"}), "The "+
          "guard building is been made out of grey stone.\n");

    add_item(({"vegetation", "plants"}), "The vegetation is scattered "+
          "all over the beach however most of the plants grow near "+
          "the edge of the beach.\n");
  
    add_item(({"footprint", "prints"}), "You "+
        "recognize the footprints as the prints of minotaurs, they "+
        "actually cover the entire trail.\n");

    add_item(({"trail", "road"}), "This trail is very "+
       "worn down, you can see some large footprints in the mud, "+
       "leading both to the east and west.\n");

   add_exit(MROOM + "guardhouse5","southeast",0);
   add_exit(MROOM + "guardhouse6","southwest",0);
   add_exit(MROOM + "road23","north",0);
   add_exit(MROOM + "road25","south",0);  
  
   
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on a worn down "+
          "road near the city of Nethosak. The road "+
          "is very muddy and covered with large "+
          "minotaur footprints. To the southeast "+
          "and southwest a small guardroom has been "+
          "made to protect the city from various "+
          "assults from pirates and potential enemies. "+
          "The road stretches itself to the "+
          "north toward the center of the city and to the "+
          "south to a small forest. " +season_descr()+ "\n";

}

