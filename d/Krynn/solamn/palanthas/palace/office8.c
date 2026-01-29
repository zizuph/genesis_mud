/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

object secre;

string
query_to_jail()
{
  return "west";
}

void
reset_palan_room()
{
  seteuid(getuid(TO));
   if (secre)
      return;
   secre = clone_object(LIV + "pers_clerk");
   secre->move_living(0,TO);
 }

void
create_palan_room()
{
    set_short("Personnel Department");
    set_long("This is the Personnel Department. You can see papers "
          +  "ordered neatly on the desk, and files are tucked into "
          +  "folders and stored on the boards.\n");

    add_exit(PALACE + "hall4","west",0,0);

    add_item(({"paper","papers","desk","files","folders","file","folder",
          "board","boards"}),"You can't see anything special.\n");
    reset_palan_room();
}
