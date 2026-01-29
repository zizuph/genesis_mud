/* 
 * /d/Kalad/common/wild/pass/kaldoro/rooms/kv08.c
 * Purpose    : A room in the Village of Kaldoro.
 * Located    : 
 * Created By : Rico 01.Jan.95
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std.c";

#include "/d/Kalad/defs.h"

create_room()
{
   ::create_room();
   
   set_short("Treetop village of Kaldoro");
   set_long("   You are standing on a catwalk "+
      "which serves as a bridge between the various "+
      "buildings of Kaldoro. The foliage here is thick "+
      "and you are unable to see very far from where "+
      "you currently stand.\n");

   add_item(({ "foliage", "thick foliage" }),
      "The foliage is very dark and dense here. The only "+
      "way for you to travel is along the various "+
      "catwalks.\n");
   add_item(({ "catwalks", "catwalks", "bridge" }),
      "This catwalk is so old and decrepid it's amazing "+
      "that it still holds people up!\n");
   
   hear_bell = 2;
   
   add_exit(KALDORO(rooms/kv12), "southwest");
   add_exit(KALDORO(rooms/kv19), "east");

   set_alarm(50.0, 0.0, "room_events");
}

room_events()
{
   switch(random(4))
   {
      case 0:
      tell_room(TO, "A grimy stranger brushes past you in "+
         "a rather uncomfortable way. You'd better "+
         "check your belongings.\n");
      break;

      case 1:
      tell_room(TO, "A thief runs past you with a small mob in "+
         "close pursuit!\n");
      break;

      case 2:
      tell_room(TO, "A stranger appears before you, but "+
         "quickly disappears into the darkness behind "+
         "you.\n");
      break;

      case 3:
      tell_room(TO, "A fearsome warrior arrives trudges "+
         "into a friend's home for a visit.\n");
      break;
   
      case 4:
      tell_room(TO, "A fat merchant arrives, takes one "+
         "look at you and runs for his life!\n");
      break;
   }
   set_alarm(50.0, 0.0, "room_events");
}

