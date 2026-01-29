inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
void reset_room();
void do_search();
int recently_searched;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The chamber of the priestesses of House Claddath");
   set_long("The chamber of the priestesses of House Claddath.\n"+
      "An unsettling feeling of dread seems to grip your soul here, "+
      "as though someone...or something were seeking it out, stalking it "+
      "like a wounded animal, waiting for it to falter so that it may "+
      "devour it. Stark depictions of a cruel and capricous Lolth have been "+
      "emboldened on the walls by eerily dark purple faerie fire, while "+
      "the onyx braziers with their incense veritably choke the air from "+
      "your lungs. A pair of black silk beds lie in a darkened corner, "+
      "appearing like nothing more than a pair of huge spiders. A chest lies "+
      "off to the side, also swathed in darkness.\n"+
      "A single, blood-red column of light penetrates the floor "+
      "and ceiling of the chamber's center.\n");
   add_item(({"chamber"}),
      "A disconcertingly bleak room, its very essence reeks of death and decay...\n");
   add_item(({"stark depictions","depictions","depiction","cruel lolth","capricious lolth","lolth","faerie fire","fire","dark purple faerie fire","dark faerie fire","purple faerie fire"}),
      "A drow woman of incredible and haunting beauty, her strong, exotic "+
      "features suit her well, for they only seem to enhance her already incredible "+
      "attractiveness.\n");
   add_item(({"onyx braziers","braziers","brazier"}),
      "Spread out across the room, the holders of incense steadily fill "+
      "the chamber with their unmistakable presence.\n");
   add_item(({"pair of black silk beds","black silk beds","black beds","silk beds","beds","bed"}),
      "Hideous, spider-like places of sleep that seem to float a little "+
      "off the floor, as though suspended from a spider's web.\n");
   add_item(({"chest"}),
      "The platinum object appears quite firm and durable.\n");
   add_item(({"single column","single light","blood-red column","blood-red light","light","column"}),
      "A five foot wide beam of scarlet energy that rises from the floor "+
      "and up into the ceiling.\n");
   add_item(({"floor","ceiling"}),
      "The black, featureless surface is distinguished only by the single, "+
      "blood-red column of light that punctures it.\n");
   add_item(({"walls","wall"}),
      "They have been decorated with various depictions of Lolth.\n");
   add_exit(CPASS(drow/house7/chapel),"down","@@msg",-1,-1);
   add_exit(CPASS(drow/house7/matron_chamber),"up","@@check",-1,-1);
   set_noshow_obvious(1);
   reset_room();
}
void
reset_room()
{
   recently_searched = 0;
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h7_priest1));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
}
void
init()
{
   ::init();
   AA(search_chest,search);
}
int
search_chest(string str)
{
   if(!str || str != "chest")
      return 0;
   if(recently_searched)
      {
      write("You discover nothing of value within the chest.\n");
      return 1;
   }
   recently_searched = 1;
   write("You start to search the chest.\n");
   say(QCTNAME(TP) + " starts to search the chest.\n");
   set_alarm(6.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   write("After an exhaustive search, you discover a pair of diamonds "+
      "within the chest!\n");
   write("You quickly grab them up.\n");
   say(QCTNAME(TP) + " takes something from the chest.\n");
   clone_object(CPASS(obj/diamond))->move(TP);
   clone_object(CPASS(obj/diamond))->move(TP);
   return;
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Talabrina")
         {
         pres = 1;
       }
   }
   if(pres == 1)
      {
      write("The high priestess prevents you from stepping into the blood red light!\n");
      say(QCTNAME(TP) + " tries to go up but is prevented by the high priestess!\n");
   }
   if(pres != 1)
      {
      write("You step into the blood red light and are transported up.\n");
      say(QCTNAME(TP) + " steps into the blood red light and is transported  up.\n");
   }
   return pres;
}
msg()
{
   write("You step into the red light, and feel yourself grow lighter as "+
      "you are transported by the column.\n");
   say(QCTNAME(TP) + " steps into the red light, and seems to grow lighter "+
      "as " + TP->query_pronoun() + " is transported by the column.\n");
   return 0;
}
