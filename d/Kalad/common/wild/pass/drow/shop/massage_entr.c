inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The entrance to the massage parlor.\n");
   set_long("The entrance to the massage parlor.\n"+
      "Incense hangs heavily in the air within this room, its exotic smell "+
      "causing delightful thrills to surge through your body. Vivid "+
      "portraits of half-clothed men and women have been portrayed with "+
      "faerie fire all about the room, decorating the walls and ceiling. "+
      "An archway lie to the east, covered by a spider web covering. A "+
      "single obsidian table lies to the side, while a doorway leads to "+
      "the west.\n");
   add_item(({"portraits","portrait"}),
      "They show several drow males and females engaged in various stages "+
      "of undress.\n");
   add_item(({"faerie fire","fire"}),
      "Glowing magical lights of a red hue.\n");
   add_item(({"walls","wall","floor","ceiling"}),
      "A perfectly smooth surface, so polished it is almost a mirror unto itself.\n");
   add_item(({"archway"}),
      "An exit to the east, covered by a spider web.\n");
   add_item(({"spider web covering","spider web","web","spider covering","covering"}),
      "A delicate substance akin to that of a curtain between rooms.\n");
   add_item(({"single obsidian table","single table","obsidian table","table"}),
      "A plain, unadorned table lying in the corner.\n");
   add_item(({"doorway"}),
      "An exit to the west, leading out to the street.\n");
   add_exit(CPASS(drow/d22),"west","@@msg",-1,-1);
   add_exit(CPASS(drow/shop/massage),"east","@@check",-1,-1);
   set_noshow_obvious(1);
   reset_room();
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/massage_owner));
      ob1 -> move_living("M",TO);
   }
}
msg()
{
   write("You head back towards the streets of Undraeth.\n");
   say(QCTNAME(TP) + " heads back towards the streets.\n");
   return 0;
}
check()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for(i = 0; i < sizeof(ob); i++)
   if(ob[i]->id("_massage_pass"))
      {
      write("You pass through the spider web covering without incident.\n");
      say(QCTNAME(TP) + " passes through the spider web covering.\n");
      ob[i]->remove_object();
      write("Your massage pass dissolves in your hands!\n");
      return 0;
   }
   write("You try to pass through the spider web covering but only "+
      "succeed in getting yourself stuck!\n");
   write("After a brief struggle, you manage to untangle yourself.\n");
   say(QCTNAME(TP) + " tries to pass through the spider web covering "+
      "but only succeeds in getting " + TP->query_objective() + "self stuck!\n");
   say("After a brief struggle, " + TP->query_pronoun() + " manages to "+
      "untangle " + TP->query_objective() + "self.\n");
   return 1;
}
