inherit "/std/object";

#include "default.h"

void
create_object()
{
   set_short("flute");
   set_name("flute");
   add_name("_quest_flute_");
   set_long(break_string("This lovely flute was lovingly carved from ash, "+
        "and is marked where years of loving play have told.\n", 76));
   add_prop(OBJ_I_WEIGHT, 65);
   add_prop(OBJ_I_VOLUME, 62);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_VALUE, 14);
}

void
init()
{
   ::init();
   add_action("do_play","play");
}

int
do_play(string str)
{
   object room1, room2, room3;

   room1 = find_object("/d/Emerald/room/puzzle/level3_1");
   room2 = find_object("/d/Emerald/room/puzzle/level3_2");
   room3 = find_object("/d/Emerald/room/puzzle/level3_3");

   if(!str)
        return 0;
   if(str == "flute")
   {
      if(file_name(ENV(ENV(TO))) == "/d/Emerald/room/puzzle/level3_3")
      {
         write("You play the flute expertly.\n");
         tell_room(ENV(ENV(TO)), QCTNAME(TP)+" plays "+POS(TP)+" flute.\n", TP);
         write("As you continue your song, the eyes of the Sphinxes close.\n");
         room3->set_is_disarmed(1);
         return 1;
      }
      if(file_name(ENV(ENV(TO))) == "/d/Emerald/room/puzzle/level3_2")
      {
         write("You play the flute beautifully.\n");
         tell_room(ENV(TP), QCTNAME(TP)+" palys "+POS(TP)+" flute.\n", TP);
         write("As you play the flute, you notice that the pipe begins to "+
	 	"glow with an\neerie light.\n");
         tell_room(ENV(TP), "The pipe begins to glow.\n", TP);
         room2->set_is_disarmed(1);
         return 1;
      }
      if(file_name(ENV(TP)) == "/d/Emerald/room/puzzle/level3_1")
      {
         write("You play the flute and as you do so a serpent squirms from "+
           "a gap in\nthe stones. It slowly begins to move to the magical "+
           "flutes' music, and\nfalls down to the ground below.\n");
         tell_room(ENV(TP), break_string("A serpent squirms from a gap in the "+
           "stones, sways to the magical song, and then falls to the ground "+
           "below.\n", 76), TP);
         room1->set_is_disarmed(1);
         return 1;
      }
      else
      write("You attempt to play the flute, but somehow this is not the "+
         "right place.\n");
      return 1;
   }
   notify_fail("Play what?\n");
   return 0;
}
