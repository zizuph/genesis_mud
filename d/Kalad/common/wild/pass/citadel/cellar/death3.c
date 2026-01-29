/*
 * Made by Korat
 * november 1996
 *
 * A cellar/dungeon beneath the dwarven citadel
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object snake;

void
create_room()
{
   ::create_room();
   set_short("cellar");
   set_long("You have arrived to a small cavern littered with "+
      "fragments of bones and torn pieces of cloth. A nauseating "+
      "smell pervades the cavern, filling your mind with images "+
      "of death and decay.\n");

   add_item(({"cobweb","web","silky network","silky web"}),
      "They are woven, silky networks spun by spiders through "+
      "time. All of them look to be abandoned by their creators, "+
      "much like this place itself; left alone to slowly be "+
      "grinned down by the sand carried along with the wind.\n");
   add_item(({"wall","walls","ceiling","roof"}),
      "Both the walls and the ceiling looks to be cut out of the "+
      "mountain itself. Through time green moss has managed "+
      "to cover it.\n");
   add_item("floor","The floor is covered with fine-grained, white "+
      "sand that must have been carried in here with the wind from the "+
      "great Kaladian waste.\n");
   add_item(({"boulder","boulders","rock","rocks"}),
      "They litter the area, making it very hard to see any path "+
      "that you can follow.\n");
   add_item(({"path","paths"}), "You have a hard time to see "+
      "any paths here.\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description@@\n");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_exit(CPASS(citadel/cellar/e16),"southwest","@@walk",3,1);
}

/* give a feeling of walking on a path */
int
walk()
{
   TP->catch_msg("You squeeze yourself between the boulders, "+
       "taking you back to the path you were following.\n");
   return 0;
}

/* returns a random darkroom description */
string
dark_description()
{
   string desc;
   switch (random(5))
   {
      case 0:
         desc = "You find yourself inside utter darkness.";
         break;
      case 1:
         desc = "A weak and chilling wind is all breaks the darkness.";
         break;
      case 2:
         desc = "You think you hear some sounds in front of you, but "+
                "without vision you cannot know what it comes from.";
         break;
      case 3:
         desc = "A dark room that envelopes you like a cloak of death.";
         break;
      case 4:
         desc = "You touch the wall to make sure you walk in the right "+
                "direction.";
         break;
      default: break;
   }
   
   return desc;
}

void
init()
{
   object dagger = TP->query_weapon(W_RIGHT);
   ::init();
   
   if (dagger->query_prop("_korat_is_kabal_dagger") == 3)
      set_alarm(2.0,0.0,"right_room",TP);

   set_alarm(2.0,0.0,"wrong_room",TP);
}

void
wrong_room(object player)
{
   if(!objectp(snake))
   {
      snake = clone_object("/d/Kalad/common/wild/pass/citadel/npc/snake");
      snake -> move(TO);
      tell_room(TO,"Out of the darkness you see a slim shape coil up "+
        "like a string on a bow, ready to emit a deadly arrow.\n");
   }
}

void
right_room(object player)
{
   object dagger = player->query_wielded(W_RIGHT);
   object heart;
   if(!objectp(heart))
   {
      heart = clone_object("/d/Kalad/common/wild/pass/dwarf/obj/kabal_heart");
      heart -> move(TO);
      tell_room(TO,"At the edge of the darkness you notice a small red lump.\n");
      dagger->remove_object();
      tell_room(TO,"Suddenly the dagger turns into dust!\n");
   }
}
