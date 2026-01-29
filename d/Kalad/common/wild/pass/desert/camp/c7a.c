inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Inside a luxurious tent");
   set_long("This tent's interior is extremely extravagant, indicating "+
      "that the owner is one not lacking in monetary wealth. A single, "+
      "great sleeping mat, a pair of fine gold lamps and an exotic carpet "+
      "lie on the floor. Aside the floor is a mass of bronze spikes.\n"+
      "A large steel pot.\n");
   add_item(({"luxurious tent","tent"}),
      "It is what you are standing inside of, just look around.\n");
   add_item(({"single sleeping mat","great sleeping mat","sleeping mat","mat"}),
      "Made of the finest of silks, the white fabric must be incredibly "+
      "comfortable to sleep on.\n");
   add_item(({"pair","fine gold lamps","fine lamps","gold lamps","lamps","fine gold lamp","fine lamp","gold lamp","lamp"}),
      "A large lantern made from gold that provides light as well as warmth.\n");
   add_item(({"exotic carpet","carpet"}),
      "A large carpet that covers the ground completely, fashioned as it "+
      "is from silk, it is surprisingly sturdy for not a tear can be seen "+
      "on its shiny surface.\n");
   add_item(({"bronze spikes","bronze spike","spikes","spike"}),
      "A barrier lining the edge of the tent to prevent the arrival of "+
      "unwanted desert animals.\n");
   add_item(({"large steel pot","large pot","steel pot","pot"}),
      "A large metal cauldron used for cooking and heating. Its surface is "+
      "as smooth and shiny as glass.\n");
   add_item(({"floor","ground"}),
      "It cannot be seen because of the carpet that completely covers it.\n");
   add_exit(CPASS(desert/camp/c7),"south",0,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(shop/bed_merchant));
      ob1 -> arm_shopkeeper();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A Bedellin merchant emerges from the sleeping mat.\n");
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/bed_ewar));
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(CPASS(npc/bed_ewar));
      ob3 -> my_stuff();
      ob3 -> move_living("M",TO);
      tell_room(TO,"You notice other people in the tent as well.\n");
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
   }
}
