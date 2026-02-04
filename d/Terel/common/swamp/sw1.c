/* added herbs  -- Tomas Dec 1999 */
/* Made the kobold area newbie only, players above great adventurer cant enter - Cherek, feb 2015 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
#include <state_desc.h>

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

#define PATH "/d/Terel/common/swamp/"

public int		 			 check_kobold_entry();

create_room()
{
   set_short("Swamp");
   set_long("A dismal swamp spreads out across the craggy land, rocks\n"
      + "jutting up from the brackish waters. Chunks of ice float about,\n"
      + "clusters of snow amass in great spanses. A few shrubs and trees\n"
      + "grow throughout the cold swamp, but mostly thick strands of\n"
      + "grass and lurid moss.\n");

   add_my_desc("Through some trees you spot a path leading northeast.\n");
   add_my_desc("There is a road to the southeast.\n");

   add_item(({"small trees","trees", "shrubs"}),
     "These are small and dismal foilage. The trees being old conifers\n"
     +"that have mostly rotted away. The shrubs are stinking swamp\n"
     +"plants, they are mostly dead. A few trees look more sturdy\n"
     +"than others however.\n");
   add_item(({"sturdy trees","sturdy tree", "branches", "low hanging branches", "low branches"}),
    "Some hills are visible through the low hanging branches, it might\n"
    +"be possible for someone small enough to go <northeast> here.\n");
   add_item("path", "It leads through some low hanging branches\n");
   add_item("water", "It is shallow, but cold and brackish.\n");
   add_item("ice", "Large pieces of ice, they float through the waters.\n");
   add_item("rocks", "This area is naturally rocky, thus rocks jut out from\n"
     + "water and form small formations.\n");
   add_item("snow", "Huge clusters of unmelted snow, the form large sections.\n");
   add_item("grass", "This is some kind of thick and sharp swamp grass.\n");
   add_item("moss", "It is lurid and looks foul.\n");

   add_prop(ROOM_S_MAP_FILE, "town_last.txt");
   add_exit("/d/Terel/mountains/kfoothills/hills_a0", "northeast", "@@check_kobold_entry");
   add_exit("/d/Terel/common/road/road2", "southeast", "@@check");
   add_exit(PATH + "sw2", "northwest", 0);


   set_up_herbs( ({TER_HERB + "whitehorn"}),
                 ({"trees","small trees"}) , 
                   3 );

   reset_room();
}

check(){
if(this_player()->query_race_name()=="kobold") return 1;
}

public int
check_kobold_entry()
{

    if (this_player()->query_average_stat() < SD_AV_VETERAN || this_player()->query_wiz_level())
    {
		write ("You manage to squeeze through the branches.\n\n");
        return 0;
    }

    write("The low hanging branches impede your progress. It seems impossible\n"
        + "for you to get through here. Perhaps you are simply too big?\n\n");
        return 1;

}


