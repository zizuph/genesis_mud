
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "/d/Ansalon/silvanesti/balinost/local.h"
#include <macros.h>

inherit BALINOST_IN;

reset_balinost_room()
{
    return;
}


create_balinost_room()
{
    set_short("Balinost Toy Store");
    set_long("This is the location of the city's toy store.  Toys "+
      "for the children of Silvanesti are hard to come by and very "+
      "difficult to make since the childhood of an elf lasts more "+
      "than seventy years.  The shelves in the store are bare, but "+
      "two decks of cards are sitting on the counter.  A piece of "+
      "paper labelled \"RULES\" is next to the cards.\n");

   add_item(({"deck","decks","cards"}),"The decks are identical, each "+
     "containing seventy-two cards.  Various pictures are on the "+
     "cards representing different units.  If you have a friend "+
     "here you could \"wager <#> against <person>\" and play a"+
     "game together.  (# is a bet in a number of platinum coins)\n");
   add_item(({"paper","rules"}),"These look like the instructions for "+
     "the card game on the counter.\n");
   add_cmd_item(({"paper","rules"}),"read","@@read_rules");
   add_cmd_item("game","play","@@play_game");

    add_exit(BROOM + "street06","east",0);
}
