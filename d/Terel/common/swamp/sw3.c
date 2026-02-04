#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define PATH "/d/Terel/common/swamp/"

create_room(){
   set_short("Swamp");
   set_long("A dismal swamp spreads out across the craggy land, rocks\n"
      + "jutting up from the brackish waters. Chunks of ice float about,\n"
      + "clusters of snow amass in great spanses. A few shrubs and trees\n"
      + "grow throughout the cold swamp, but mostly thick strands of\n"
      + "grass and lurid moss.\n");

   add_item(({"trees", "shrubs","small trees"}),
     "These are small and dismal foilage. The trees being old conifers\n"
     +"that have mostly rotted away. The shrubs are stinking swamp\n"
     +"plants, they are mostly dead.\n");
   add_item("water", "It is shallow, but cold and brackish.\n");
   add_item("ice", "Large peices of ice, they float through the waters.\n");
   add_item("rocks", "This area is naturally rocky, thus rocks jut out from\n"
     + "water and form small formations.\n");
   add_item("snow", "Huge clusters of unmelted snow, the form large sections.\n");
   add_item("grass", "This is some kind of thick and sharp swamp grass.\n");
   add_item("moss", "It is lurid and looks foul.\n");

   add_exit(PATH + "sw4", "northwest", 0);
   add_exit(PATH + "g1", "northeast", 0);
   add_exit(PATH + "sw1", "southwest", 0);

   set_up_herbs( ({TER_HERB + "whitehorn"}),
                  ({"trees","small trees","shrubs"}) , 
                   3 );


   reset_room();
}


