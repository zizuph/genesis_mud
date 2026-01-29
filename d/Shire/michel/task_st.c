inherit "/std/room";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
void add_stuff();
 
create_room() {
   set_short("The stables in Skrombies house");
 set_long("You have entered ths stables belonging to a local hobbit \n" +
     "who is fond of his only pony. Everything is cleaned and tidy.\n");
 
   add_exit(MICH_DIR + "task","back",0,1);
reset_room();
 }

void
reset_room()
{
     add_stuff();
}

void
add_stuff()
{
   object coins;

   coins = clone_object("/std/coins");
   coins->set_coin_type("gold");
   coins->set_heap_size(6);
   coins->move(TO);

}
