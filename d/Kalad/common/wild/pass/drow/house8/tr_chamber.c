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
   add_prop(ROOM_M_NO_TELEPORT,1);
   add_prop(ROOM_I_LIGHT,0);
   set_short("The treasure chamber of House Noquar");
   set_long("This black, utterly featureless room contains numerous piles "+
      "of platinum, gold and silver. Several of the piles rise well over "+
      "ten feet into the air, while the majority are but four or five feet "+
      "in height.\n");
   add_item(({"room","here"}),
      "It is black...and that is all that can be discerned concerning it.\n");
   add_item(({"piles","pile"}),
      "Massive mounds of monetary wealth. Enough to put the average surface "+
      "world kingdom to shame.\n");
   add_exit(CPASS(drow/house8/mm_chamber),"south",0,-1,-1);
   set_noshow_obvious(1);
   reset_room();
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
   AA(search,search);
}
int
search(string str)
{
   if(!str || str != "piles")
      return 0;
   if(recently_searched)
      {
      write("You discover nothing you can take within the piles.\n");
      return 1;
   }
   recently_searched = 1;
   write("You start to search the piles.\n");
   say(QCTNAME(TP) + " starts to search the piles.\n");
   set_alarm(6.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   write("After a thorough search, you discover three diamonds!\n");
   write("You also discover a house insignia!\n");
   write("You quickly grab them up.\n");
   say(QCTNAME(TP) + " takes something from one of the piles.\n");
   clone_object(CPASS(obj/diamond))->move(TP);
   clone_object(CPASS(obj/diamond))->move(TP);
   clone_object(CPASS(obj/diamond))->move(TP);
   clone_object(CPASS(drow/obj/h8_insignia))->move(TP);
   return;
}
