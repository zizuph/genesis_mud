// Modifications:
// Lilith, Jan 2022: updated exit for the moors
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
      + "grass and lurid moss.\n"
      + "A large fallen tree lies here, rotting away in the frigid\n"
      + "waters, its roots exposed. The swamp dries up west of here,\n"
      + "leading into a dangerous looking moor.\n");
   
  add_item(({"tree", "fallen tree", "rotten tree"}),
     "It was a large pine, now mostly a rotting trunk.\n");
   add_item("roots", "When the tree fell its roots were exposed\n" +
     "to the air, drying out and becoming a tangled mess.\n");
   add_item("moor", "A large cold expanse, it looks dangerous.\n");
   add_item(({"trees", "shrubs"}),
      "These are small and dismal foilage. The trees being old conifers\n"
      +"that have mostly rotted away. The shrubs are stinking swamp\n"
      +"plants, they are mostly dead.\n");
   add_item("water", "It is shallow, but cold and brackish.\n");
   add_item("ice", "Large pieces of ice, they float through the waters.\n");
   add_item("rocks", "This area is naturally rocky, thus rocks jut out from\n"
      + "water and form small formations.\n");
   add_item("snow", "Huge clusters of unmelted snow, they form large sections.\n");
   add_item("grass", "This is some kind of thick and sharp swamp grass.\n");
   add_item("moss", "It is lurid and looks foul.\n");
   
   add_exit(PATH + "sw1", "southeast", 0);
   add_exit("/d/Terel/common/moor/main/moor5", "west", 0);

   set_up_herbs( ({TER_HERB + "whitehorn"}),
                 ({"fallen tree","tree","rotten tree"}) , 
                   3 );

   reset_room();
   
}
