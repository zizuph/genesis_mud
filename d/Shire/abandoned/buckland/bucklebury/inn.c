inherit "/d/Shire/room";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Shire/buckland/buckdefs.h";

#define EXIT1 BB_DIR + "buroad11","north",0,1

void
create_room()
{
    set_short("The Bucklebury Inn");
    set_long("You have entered the Bucklebury Inn. It is the largest one "+
      "in Buckland, and has a great many choices of food and drink for "+
      "hobbits and their friends to choose from. There are tables and "+
      "chairs scattered around the room to sit at. There is a menu on one "+
      "of the walls to see what is available here.\n");

    add_item(({"chair","chairs"}),"There are many chairs scattered around "+
      "the room. They are all made of wood and look very comfortable to "+
      "sit on.\n");
    add_item(({"table","tables"}),"The tables are made of wood and are "+
      "slightly stained and scratched from all of the use that they have "+
      "gotten.\n");
    add_item("menu","The menu is hanging on the wall. Perhaps you'd make "+
      "more progress with your ordering if you read it.\n");
    add_cmd_item("menu","read","@@read");
    add_prop(ROOM_I_INSIDE,1);
    add_exit(EXIT1);

    add_drink(({"beer","beers","small beer","small beers"}),
      "beer","small",200, 8, 16, 0, 0, 
      "It is a small and very tasty beer.\n", 0);
    add_drink(({"glass of Old Winyards","glasses of Old Winyards",
      "Old Winyards","wine","wines"}),({"wine","old winyards","Old Winyards"}),
      "glass of", 150, 15,
      32, "glass of Old Winyards", "glasses of Old Winyards",
      "A strong, red wine from the Southfarthing.\n", 0);
    add_drink(({"brandy","brandies","snifters of brandy","snifter of brandy"}),
      "brandy","smooth", 100, 25, 72, 0, 0, "A smooth, amber brandy.\n", 0);

    add_food(({"cake","cakes","seed-cakes","seed-cake"}),"seed-cake",
      "round", 60, 11, 0, 0, "A tasty, round seed-cake.\n", 0);
    add_food(({"mushrooms","basket of mushrooms","baskets of mushrooms"}),
      ({"mushrooms","basket of mushrooms","baskets of mushrooms"}),"fried",
      100, 21, "basket of mushrooms","baskets of mushrooms",
      "A plate of fried mushrooms.\n", 0);
    add_food(({"corn","plate of corn","plates of corn"}),({"plate of corn",
      "plates of corn"}),
      "sweet", 150, 43, "plate of corn","plates of corn","A plate of "+
      "very sweet corn.\n", 0);
}

void
init()
{
    ::init();
    init_pub();
}

int
read(string str)
{
    write("\n"+

      "BUCKLEBURY INN: EATS & DRINKS\n\n"+
      "A small beer             16cc\n"+
      "A glass of Old Winyards  32cc\n"+
      "A snifter of brandy      72cc\n"+
      "------------------------------\n"+
      "seed-cakes               11cc\n"+
      "A basket of mushrooms    21cc\n"+
      "A plate of corn          42cc\n");
    return 1;
}
