/* 
 * /d/Kalad/common/wild/pass/kaldoro/rooms/kv09.c
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
   set_long("	You are standing on a catwalk "+
      "which serves as a bridge between the various "+
      "buildings of Kaldoro.  Over the entryway to "+
      "the building to the south you can see an "+
      "old and worn out sign gently swaying in the "+
      "breeze.\n");
   
   add_item(({ "sign", "old sign", "worn out sign" }),
      "This sign is very weather beaten.  It's "+
      "a wonder it is still hanging.  You might "+
      "be able to make out the script engraved "+
      "into it.\n");
   add_item(({ "building" }),
      "You are unable to make out what this building's "+
      "purpose is.  It looks very official, though.\n");

   hear_bell = 2;
   
   add_exit(KALDORO(rooms/kv18), "west");
   add_exit(KALDORO(rooms/kv20), "east");
   add_exit(KALDORO(rooms/inn2), "south");

    set_alarm(50.0, 0.0, "room_events");
}

init()
{
   ::init();
   
   add_action("read", "read");
}

int
read(string str)
{
   if(str != "sign")
      {
      write("Perhaps you should try to read "+
         "the sign instead?\n");
      return 1;
   }
   else
      {
      write("You have a hard time making out the "+
         "script which is engraved into the rotting "+
         "wood.  It is witten in a very old form of Common.  "+
         "Fortunately you are able to decipher it "+
         "as :\n\n"+
         "          'The Warrior's Ghost Inn'\n\n");
      say(QCTNAME(this_player()) + " reads the "+
         "ancient sign.\n");
      return 1;
   }
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
