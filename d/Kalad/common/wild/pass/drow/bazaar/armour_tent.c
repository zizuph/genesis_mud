inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Inside the armour merchant's tent");
   set_long("This rather overcrowded tent is nearly filled to the brim "+
      "with all manner of drow armour, all of which are crafted from "+
      "adamantine metal, the trademark of drow armourers. Various tables lie "+
      "at the outskirts of the tent, whereupon the said armours lie. Only "+
      "a tiny portion of the carpeted floor is visible, with a path lying "+
      "through the small mountain of drow armour to the back of the tent, "+
      "where there is a small clearing. The tent's flap is behind you, the "+
      "only apparent 'exit' from here.\n"+
      "You notice that the ceiling is lit by the eerie red glow of faerie fire.\n");
   add_item(({"drow armour"}),
      "Numerous types of armour, all fashioned from adamantine in the drow "+
      "manner are strewn about the tent.\n");
   add_item(({"tables","table"}),
      "The black stone tables are nearly buried under a small mountain of "+
      "drow armour.\n");
   add_item(({"path"}),
      "A cleared path through the loads of drow armour that leads to the "+
      "back of the tent.\n");
   add_item(({"small clearing","clearing"}),
      "The largest clear spot in this tent, it appears just large enough for "+
      "one person to occupy.\n");
   add_item(({"tent flap","flap"}),
      "It is open and is the only 'exit' out of here.\n");
   add_item(({"ceiling","faerie fire","fire"}),
      "The top of the tent is glowing an eerie red, apparently ensorcelled "+
      "with a faerie fire spell, which is the sole source of light here.\n");
   add_item(({"carpeted floor","floor","carpet"}),
      "It is barely visible due to the large amounts of drow armour present "+
      "here in the tent.\n");
   add_exit(CPASS(drow/bazaar/b3),"exit",0,-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/armour_merchant));
      ob1 -> move_living("M",TO);
      tell_room(TO,"Some armour shifts slightly, and a single drow crawls "+
         "out from beneath it.\n");
   }
}
