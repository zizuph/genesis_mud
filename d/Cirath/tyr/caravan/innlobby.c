/* innlobby: The main room and tavern of the Golden Inix Inn.
 * Updated the menu and the pub inherits
 * along with the add_food, add_drink so 
 * they would fit well with the new pub menu
 * For inclusion in Raumdor
 * Damaris 5/2001
 */

#include "defs.h"
inherit "/std/room";
inherit CIRATH_DIR + "lib/pub";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


string
dummy_menu()
{
    read_menu("menu");
    return "";
}
void
reset_room()
{
  bring_room_mob("jaryx",TYR_NPC+"jaryx.c",1,1);
}

void
create_room()
{
  ::create_room();
    set_short("lobby of the golden inix inn");
    set_long("The Golden Inix Inn combines vibrant enthusiasm with the "+
             "sense of impending danger common to the taverns of Athas. "+
             "Serving girls move in and out of a rear curtain, passing a "+
             "small, L-shaped counter which serves as bar to the motley "+
             "assortment of Tyr's riff-raff that frequent this place. A "+
             "few of the more exhausted or intoxicated (or both) patrons "+
             "stagger off through a door west, right past the menu.\n");
             
    add_item(({"curtain","serving girls","serving girl","girl","girls"}),
             "The curtain the girls pass through blocks a small, but "+
             "very busy kitchen.\n");
    add_item(({"riff-raff", "patron", "patrons"}), "As one would expect, "+
             "they don't appreciate being stared at.\n");
    add_item(({"bar", "counter"}), "A simple stone counter, with a decent "+
             "supply of beverages behind it.\n");
    add_item("menu", &dummy_menu());

    add_drink(({ "broy", "cups of broy", "spiced broy", "cups of" }),
      "broy", "spiced cup of", 50, 10, 25, "cup of spiced broy", "cups of spiced broy",
      "Made from fermented kank nectar, broy is a nice, "+
      "cheap alternative to taste.\n", 0); 
    add_drink(({ "ale", "mugs of ale", "tyrian ale", "mugs of" }),
      "ale", "mug of tyrian ", 100, 20, 50, "mug of tyrian ale", "mugs of tyrian ale",
      "Made from the grall cactus, the blue Tyrian ale is a strong, "+
      "bitter favorite.\n", 0);
    add_drink(({ "wine", "glasses of wine", "asticles wine", "glasses of" }),
      "wine", "glass of asticles", 200, 40, 100, "glass of asticles wine", "glasses of asticles wine",
      "This tart wine, favored by nobles, is as gold and dry as the "+
      "desert.\n", 0);
    add_food(({ "bread", "warm bread", "warm unleavened bread", "unleavened bread" }),
      "bread", "unleavened", 20, 30, "warm unleavened bread",
      "warm unleaven breads",
      "Its a flat, heavy, chunk of bread.\n", 0); 
    add_food(({ "erdlu", "hot erdlu", "hot skewered erdlu", "skewered erdlu" }),
      "erdlu", "skewered", 50, 75, "hot skewered erdlu",
      "hot skewered erdlu's",
      "A sizable hunk of steamed erdlu flesh on an edible chitin skewer. "+
      "Yum!\n", 0);
    add_food(({ "tail", "roasted tail", "roasted inix tail", "inix tail" }),
      "tail", "inix", 100, 120, "roasted inix tail",
      "roasted inix tails",
      "Yes, the entire tail including the bones of a huge, "+
      "flightless Athasian bird, roasted to perfection.\n", 0);

    INSIDE

    add_exit(TYR_CARAVAN+"innrecpt.c", "west", 0, 1);
    add_exit(TYR_CARAVAN+"rd_cw_07.c", "south", 0, 1);


  reset_room();

}
void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "The Golden Inix Inn"));
}
int
do_read(string str)
{
    if (str != "menu")
    {
	notify_fail("Read what?\n");
	return 0;
    }

    write("It is forbidden to read in Tyr.\n");
    return 1;
}
   
void
init()
{
    ::init();
    init_pub();
    add_action(do_read, "read");  
}   
