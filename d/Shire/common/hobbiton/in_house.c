inherit "/d/Shire/common/lib/room";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

object hum;

create_room()
{
   set_short("Inside a cottage off the East road");
   set_long("This is a quaint little cottage, and it seems there "+
      "is only one other room, to your west. There is a "+
      "stove and washpan on one side of the room, and a rather large and ornate fireplace "+
      "on the other. There is little furniture here, and none of it "+
      "would appear to hold your weight as it is made for hobbits, and "+
      "small ones at that. A window lets some light in from outside, "+
      "and you smell a lovely fragrance of herbs.\n");
   
   add_item(({"stove","washpan"}),"These seem to constitute the kitchen of this cottage.\n");
   
   add_item(({"window","curtains","light","fragrance","herbs"}),
      "The window is round in the hobbit fashion and partially covered "+
      "by thin white curtains. Light comes through them, day or "+
      "night, you suspect, and the fragrance you smell must be from "+
      "the herbs in the garden.\n");
   
   add_item(({"fire","fireplace","chimney"}),
      "The fireplace holds no burning fire, only ashes. Set into the chimney itself "+
      "is a make-shift mantle with a silver bracelet, some brass figures and a candle "+
      "on it. The fireplace itself seems to take up most of the room, "+
      "but then, all hobbits enjoy a good fire.\n");
   
   add_item(({"mantle","make-shift mantle","figures"}),
      "The mantle is made of unfinished oak, and the brass figurines "+
      "you see on it are probably hobbits at rest, play, and at "+
      "their favorite place of all, the supper-table.\n");
   
   add_item(({"table","supper-table"}),
      "Strange, you don't see where the residents dine. There is no "+
      "table here.\n");
   
   add_item(({"ashes","ash"}),"These are the remains of a fire some time ago.\n");
   add_item(({"bracelet","silver bracelet"}), "This piece of jewelry seems only big enough for a hobbit's arm.\n");
   
   add_item(({"furniture"}),"It is all wooden and of a hobbit make: very fine quality indeed.\n");
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit("/d/Shire/common/hobbiton/newphouse","out",0,1);
   add_exit("/d/Shire/common/hobbiton/bedroom","west",0,1);
   
   reset_room();  
}

reset_room()
{ 
   if (!hum)
      {
      hum = clone_object("/d/Shire/common/hobbiton/npc/petunia");
      hum->move(TO);
   }
}
init()
{
   ::init();
   //     add_action("do_push","push");
   add_action("do_enter","enter");
}

int
do_push(string str)
{
   if (str != "fireplace")
      {
      NF("You push the "+str+", but nothing happens.\n");
      return 0;
   }
   /*    if(present(hum))
      *      {
      *      write("The human won't let you near the fireplace.\n");
      *      return 0;
      *      }
   */
   
   say(QCTNAME(TP) + " falls down into a hole!\n");
   write("You push the fireplace and discover it is a trap!\n");
   write("You fall down into a dark hole.\n");
   TP->move_living("M","/d/Shire/common/hobbiton/h_cellar",1);
   
   return 1;
   
}


int
do_enter(string str)
{
   if (str != "window")
      {
      write("You try to enter the "+str+" but fail.\n");
      say(QCTNAME(TP)+ "tried to enter the "+str+" but failed.\n");
      return 1;
   }
   
   write("You enter the window, and find yourself in a garden.\n");
   say(QCTNAME(TP) + " leaves through the window.\n");
   TP->move_living("M","/d/Shire/common/hobbiton/pet_garden",1);
   return 1;
   
   
}
