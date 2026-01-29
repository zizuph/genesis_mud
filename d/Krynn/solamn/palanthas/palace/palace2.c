/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

string
query_to_jail()
{
  return "west";
}

void
create_palan_room()
{
    set_short("Banquet Hall of the Palace");
    set_long("You stand in an overwhelming Hall. There is a long "
          +  "table here.         "
          +  "      I am very proud of you to have made it this far!"
          +  " Unfortunately, you will have to wait until this is "
          +  "finished so you can venture further against the evil"
          +  " of the world.\n");

    add_exit(PALACE + "palace1","west",0,0);
}
