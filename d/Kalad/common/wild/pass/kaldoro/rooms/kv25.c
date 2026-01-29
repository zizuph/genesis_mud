/* 
 * /d/Kalad/common/wild/pass/kaldoro/rooms/kv25.c
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
      "the building to the southwest you can see an "+
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

hear_bell = 1;
   
   add_exit(KALDORO(rooms/kv24),"west");
   add_exit(KALDORO(rooms/kv26),"east");
   add_exit(KALDORO(rooms/bank),"southwest");
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
