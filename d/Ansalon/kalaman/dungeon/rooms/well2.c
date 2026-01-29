/*
 * Well Room Nr2
 *
 * Lunatari of Krynn
 *
 * Note: get_descs functions need to be above the room creation.
 *       else it seems they cannot be updated.
 */
#include "local.h"

inherit DUNGEON_IN;

#define WELL_UP   DROOM + "well1"
#define WELL_DOWN DROOM + "well3"

string get_long_desc();
string get_rope_desc();

create_dungeon_room()
{
   set_short("Halfway down the well");
   set_long(get_long_desc);
 
   add_item("rope", get_rope_desc);
   add_item(({"wall", "walls","shaft"}), 
      "The walls of the well are masterly designed and created by the most experienced " +
      "of stone masons, the bricks are neatly stacked on top of each other and have " +
      "been polished by water over the years, making them very slippery. Except for the " +
      "few bricks that stand out just enough from the wall, making it possible to stand " +
      "on them it seems impossible to climb away from here without aid of some sort.\n");
   add_item(({"brick", "bricks"}),
      "The bricks are neatly stacked on top of eachother in perfect harmony, only a few " +
      "bricks of the wall are standing out just enough for you to stand on.\n");
   add_item("water", "Looking down into the dark you fail to see any water but you hear " +
      "the water clucking further down.\n");
}

init()
{
  ::init();

  add_action("climb_rope", "climb");
}

string
get_long_desc()
{
   string text;

   if (!DMASTER->query_status(S_GWELL))
   {
       text = "A veritcal shaft leading deep down into the ground under Kalaman. The " +
              "walls of the well are made out of neatly placed stones, perfectly " +
              "shaped to fit each other, forming a clean and slippery surface that " +
              "seems unclimable without aid of some sort. A few bricks that stands out " +
              "from the wall makes it possible to stand here.";
   }
   else
   {
       text = "A veritcal shaft leading deep down into the ground under Kalaman. The " +
              "walls of the well are made out of neatly placed stones, perfectly " +
              "shaped to fit each other, forming a clean and slippery surface that " +
              "seems unclimable without the aid of the rope that hangs down from above. " +
              "a few bricks that stands out from the wall makes it possible to stand here.";
   }

   return text + "\n";
}

string
get_rope_desc()
{
   string text;
  
   switch(DMASTER->query_status(S_GWELL))
   {
      case 0:
          text = "What rope?";
      break;
      case 1:
          text = "The rope hangs down from above, it hangs free in the middle of this " +
                 "vertical shaft of the well.";
      break;
      default:
          text = "What do you mean by rope?";
   }
   
   return text + "\n";
}

int
climb_rope(string str)
{
   notify_fail("Climb what?\n");

   if (!str) return 0;

   if (parse_command(str, ({ }), "[the] 'wall' / 'walls'"))
   {
      write("Since you are not very far down you easilly manage to "+
        "climb the wall and out from the well.\n");
      tell_room(ENV(TP), QCTNAME(TP) + " pulls " + HIM(TP) + "self up over the edge " +
        "of the wall.\n", TP);
      TP->move_living("M", WELL_UP, 1);
        tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing over the edge of the " +
      "well.\n", TP);

      return 1;
   }

   if(DMASTER->query_status(S_GWELL))
   {
     if (parse_command(str, ({ }), "'up' [the] 'rope'"))
     {
        write("You pull the rope closer and climb upwards.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " pulls the rope closer and leaves " +
            "climbing upwards.\n", TP);
        TP->move_living("M", WELL_UP, 1);
        tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing up the rope from " +
            "the well.\n", TP);

        return 1;
     }
     else if (parse_command(str, ({ }), "'down' [the] 'rope'"))
     {
        write("You pull the rope closer slide downwards.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " pulls the rope closer slides down " +
            "into the dark.\n", TP);
        TP->move_living("M", WELL_DOWN, 1);
        tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing half sliding down " +
            "the rope from above.\n", TP);

        return 1;
     }

      notify_fail("Climb up or down the rope?\n");

      return 0;
   }
   return 0;
}
