
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "/d/Ansalon/silvanesti/balinost/local.h"
#include <macros.h>

inherit BALINOST_IN;
object ob1;

void
reset_balinost_room()
{
   if(!objectp(ob1))
   {
    ob1 = clone_object(BLIVE + "hemdash");
    ob1->move_living("xxx",TO);
   }
    return;
}

create_balinost_room()
{
    set_short("Balinost Visitor Center");
    set_long("This is the visitor center in Balinost.  It has been relatively "+
      "inactive in the last two thousand years as few people other than "+
      "Silvanesti were allowed into the city.  Now that the darkness creeps "+
      "through the land, the elves are too concerned about leaving to care "+
      "if someone comes to visit.\n");

    clone_object(BOBJ + "balin_board")->move(TO);
    reset_balinost_room();

    add_exit(BROOM + "street10","north",0);
}
