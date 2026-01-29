/* created by Aridor 06/19/93 */

#include "../local.h"

inherit MERCH_ROOMBASE;

#include <macros.h>


object proprietor;

query_to_jail()
{
  return "east";
}


query_proprietor()
{
    return proprietor;
}

void
reset_palan_room()
{
    if (proprietor)
        return;
    proprietor = clone_object(MERCH + "living/proprietor");
    proprietor->move_living(0,TO);
}

void
init()
{
  ::init();
    ADA("read");
 
}

void
create_palan_room()
{
    set_short("The office of the Silver Dragon Inn");
    set_long("This is a cozy room with a desk as the only accessory inside."
         +   " It's the office of the inn, where the business parts of owning "
         +   "an inn are handled.\n");
    
    LIGHT;

    add_item(({"table","desk"}),"It's an ordinary desk with a few papers "
        +    "strewn about.\n");
    add_item(({"papers"}),"You can't understand a word that's written on the papers, " +
	     "so you think it's not even worth trying to read them.\n");

    add_exit(MERCH + "inn1", "east",0,0);

    reset_room();
}

int
read(string str)
{
  NF("Read what?\n");
  if (str != "papers")
    return 0;
  write("Of course you cannot understand a word that's written on the papers.\n");
  return 1;
}
