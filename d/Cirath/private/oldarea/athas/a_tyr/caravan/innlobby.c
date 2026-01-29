/* innlobby: The main room and tavern of the Golden Inix Inn. */

inherit "/std/room";
inherit "/lib/pub";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
  bring_room_mob("jaryx",TYR_NPCS+"jaryx.c",1,1);
}

void
create_room()
{
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
    add_item("menu", "In symbols widely recognised throughout Athas, the "+
             "menu lists:\n  Food                   Drinks\n"+
             "    Bread         30 cc    Broy            25 cc\n"+
             "    Erdlu skewer  75 cc    Tyrian ale      50 cc\n"+
             "    Inix tail    120 cc    Asticles wine  100 cc\n"+
             "While it isn't stated, you can guess that it is possible to "+
             "'buy bread with gold', 'test buy broy', 'buy 8 wine', or "+
             "make other similar clever orders.\n");

    add_cmd_item("menu", "read", "Fortunately the menu is in examinable "+
             "symbols, or many would break the law against literacy.\n");

    add_drink(({"broy", "spiced broy", "broys"}),"broy", "spiced", 50, 10,
             25, 0, 0, "Made from fermented kank nectar, broy is a nice, "+
             "cheap alternative to taste.\n", 0); 
    add_drink(({"ale", "tyrian ale", "ales"}), "ale", "tyrian", 100, 20, 50,
             "Tyrian ale", "Tyrian ales", "Made from the grall cactus, "+
             "the blue Tyrian ale is a strong, bitter favorite.\n", 0);
    add_drink(({"wine", "asticles wine", "wines"}), "wine", "asticles", 200,
             40, 100, "Asticles wine", "Asticles wines", "This tart wine, "+
             "favored by nobles, is as gold and dry as the desert.\n", 0);
    add_food(({"bread", "unleavened bread", "breads"}), "bread",
             "unleavened", 25, 30, 0, 0,
             "Its a flat, heavy, chunk of bread.\n", 0); 
    add_food(({"skewers", "erdlu skewers", "skewer"}), "skewer", "erdlu",
             50, 75, "erdlu skewer", "erdlu skewers", "A sizable hunk of "+
             "steamed erdlu flesh on an edible chitin skewer. Yum!\n", 0);
    add_food(({"tail", "inix tail", "tails"}), "tail", "inix", 100, 120,
             0, 0, "Yes, the entire tail including the bones of a huge, "+
             "flightless Athasian bird, roasted to perfection.\n", 0);

    INSIDE

    add_exit(TZ_CARAVAN+"innrecpt.c", "west", 0, 1);
    add_exit(TZ_CARAVAN+"rd_cw_07.c", "south", 0, 1);

  reset_room();
}

void
init()
{
    ::init();
    init_pub();
}

