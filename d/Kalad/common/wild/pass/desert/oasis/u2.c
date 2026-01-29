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
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_UNDER_WATER,3);
   set_short("At the water-filled bottom of the well");
   set_long("Black, though surprisingly clear water surrounds you, as "+
      "you are now at the very bottom of the well, its surface covered by "+
      "a thick, yet fine layer of sand. Grey stones, the material of which "+
      "the well is made of, wavers before you, no doubt due to distortion "+
      "caused by the water all around you.\n");
   add_item(({"black water","clear water","water"}),
      "Its all around you.\n");
   add_item(({"very bottom","bottom","well"}),
      "This part is completely filled with water.\n");
   add_item(({"sand"}),
      "It is quite deep, nearly two feet thick.\n");
   add_exit(CPASS(desert/oasis/u1),"up","@@msg",5);
   reset_room();
}
msg()
{
   TP->catch_msg("You emerge from the water-filled bottom of the well!\n");
   say(QCTNAME(TP) + " floats upwards and out of the bottom of this well.\n");
   return 0;
}
init()
{
   ::init();
   AA(search_sand,search);
   clone_object("/d/Kalad/common/wild/pass/obj/water_death")->move(TP,1);
}
leave_inv(ob, to)
{
   object wdeath;
   ::leave_inv(ob);
   wdeath = present("water_death", ob);
   if (wdeath) wdeath -> remove_object();
}
void
reset_room()
{
   recently_searched = 0;
}
int
search_sand(string str)
{
   if(!str || str != "sand")
      return 0;
   if(recently_searched)
      {
      write("After a fruitless search, you are rewarded with nothing save for "+
         "sand spread out on you.\n");
      return 1;
   }
   write("You start to search the sand.\n");
   say(QCTNAME(TP) + " starts to search the sand.\n");
   set_alarm(6.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   recently_searched = 1;
   write("You find an urn hidden amongst the sand!\n");
   write("You quickly pluck it from its hiding place.\n");
   say(QCTNAME(TP) + " takes something from amidst the sand.\n");
   clone_object(CPASS(obj/bed_urn))->move(TP);
   return;
}
