
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
    set_short("The White Rose Pub");
    set_long("Although most of the businesses in Balinost are closed, "+
      "this one remains open.  In fact, the pub has been getting a fair "+
      "amount of business.  People come here either to drown their "+
      "sorrows, or because they have already packed their nectar for "+
      "when they leave.  The White Rose has enough tables to seat a "+
      "hundred elves, but considering the times, the fifty or so that "+
      "come during peak hours is impressive business.  A menu lists "+
      "the different kinds of drinks available.\n");

    add_item("menu","The menu lists the drinks available at this pub.\n");
    add_cmd_item("menu","read","@@read_menu");

    add_exit(BROOM + "street06","west",0);
}

string
read_menu()
{
    return "This is what the menu says is offered here:\n\n"+
      "          silvanesti wine           10cc\n"+
      "          honey ale                 24cc\n"+
      "          nectar                    70cc\n";
}
