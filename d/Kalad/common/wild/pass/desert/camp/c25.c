inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
void reset_room();
void do_search();
int recently_searched;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Inside the central tent");
   set_long("You are at a dead end within the Sheik's tent.\n"+
      "The canvas walls lie on three sides, forming a passage which heads "+
      "off to the north. Several packs have been stacked in a corner.\n");
   add_item(({"tent"}),"Its what you are inside of!\n");
   add_item(({"canvas walls","canvas wall","walls","wall","sides","side","passage"}),
      "Made from strong camel hair, the tent forms a strong barrier against "+
      "the harsh desert wind of the waste. A small hole looks to have been "+
      "cut into the canvas wall.\n");
   add_item(({"hole"}),"A small, barely human-sized hole in the side of the "+
      "tent.\n");
   add_item(({"packs","pack","corner"}),"Large carrying packs used by the "+
      "Bedellin to store perishable goods and other materials have been "+
      "placed in one corner of this passage. Apparently this place is some "+
      "sort of storage area.\n");
   add_cmd_item(({"west","hole"}),"enter","@@enter");
   add_cmd_item("hole","enter","@@enter");
   add_exit(CPASS(desert/camp/c20),"north",0,-1);
   reset_room();
}
enter()
{
   write("You enter the hole in the tent's side.\n");
   set_dircmd("hole");
   TP->move_living("into the hole","/d/Kalad/common/wild/pass/desert/camp/c24");
   return "You've exited the tent and now stand in the open.\n";
}
void
reset_room()
{
   recently_searched = 0;
}
void
init()
{
   ::init();
   AA(search_packs,search);
}
int
search_packs(string str)
{
   if(!str || str != "packs")
      return 0;
   if(recently_searched)
      {
      write("You rummage around the packs for several minutes but only "+
         "succeed in making a mess of things.\n");
      return 1;
   }
   write("You start to search the packs.\n");
   say(QCTNAME(TP) + " searches the packs.\n");
   set_alarm(5.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   recently_searched = 1;
   write("After several minutes you discover a spell book hidden amongst "+
      "the packs!\n");
   write("You quickly grab it from its hiding place.\n");
   say(QCTNAME(TP) + " takes something from amongst the packs.\n");
   clone_object(CPASS(obj/bed_w_sb))->move(TP);
   return;
}
