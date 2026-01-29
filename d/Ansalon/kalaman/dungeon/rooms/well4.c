/* 
 * Bottom of Well
 *
 * Will add a swim exit from here soon.
 *
 * Lunatari of Krynn
 *
 * 2008-02-02
 */
#include "local.h"

inherit DUNGEON_IN;

#define WELL_UP DROOM + "well3"

string get_long_desc();
string get_rope_desc();

create_dungeon_room()
{
   set_short("At the bottom");
   set_long(get_long_desc);
 
   add_item("rope", get_rope_desc);
   add_item(({"wall", "walls"}), 
      "The walls of the well are masterly designed and created by the most experienced " +
      "of stone masons, the bricks are neatly stacked on top of each other and have " +
      "been polished by water over the years, making them very slippery. Except for the " +
      "few bricks that stand out just enough from the wall, making it possible to stand " +
      "on them it seems impossible to climb away from here without aid of some sort.\n");
   add_item(({"brick", "bricks"}),
      "The bricks are neatly stacked on top of eachother in perfect harmony, only a few " +
      "bricks of the wall are standing out just enough for you to stand on.\n");
   add_item("water", "The water is as dark and cold as the slipery rocks in the walls, " +
      "it is so dark that the bottom of the well is unviewable.\n");
}

init()
{
  ::init();

  add_action("climb_rope", "climb");
  add_action("drink_water", "drink");
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
              "seems unclimable without aid of some sort. The water level is quite" +
              "high here and one most focus to not slip and fall.";
   }
   else
   {
       text = "A veritcal shaft leading deep down into the ground under Kalaman. The " +
              "walls of the well are made out of neatly placed stones, perfectly " +
              "shaped to fit each other, forming a clean and slippery surface that " +
              "seems unclimable without the aid of the rope that hangs down from above. " +
              "The high water level here makes it hard not to slip and fall.";
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
          notify_fail("You pull the rope closer and look down, realizing that you " +
            "are already wading in the water.\n");

          return 0;
     }

      notify_fail("Climb up or down the rope?\n");

      return 0;
   }
   return 0;
}

int
drink_water(string str)
{
  if (!str) return 0;

  if (parse_command(str, ({ }), "'water' [from] [the] [well]"))
  {
    if ( TP->drink_soft(2000, 1) )
    {
      write("You carefully bend down and drink of the fresh cold water.\n");
      tell_room(ENV(TP), QCTNAME(TP) + " leans down and drinks of the " +
        "cold dark water of the well.\n", TP);
      TP->drink_soft(2000);
    }
    else if ( TP->drink_soft(1000, 1) )
    {
      write("You carefully bend down and drink some of the fresh cold water.\n");
      tell_room(ENV(TP), QCTNAME(TP) + " leans down and drinks some of the " +
        "cold dark water of the well.\n", TP);
      TP->drink_soft(1000);
    }
    else if ( TP->drink_soft(250, 1) )
    {
      write("You carefully bend down and sip some of the fresh cold water.\n");
      tell_room(ENV(TP), QCTNAME(TP) + " leans down and takes a small sip of the " +
        "cold dark water of the well.\n", TP);
      TP->drink_soft(250);
    }
    else
    {
      write("You are not thirsty.\n");
    }
    return 1;
  }
  return 0;
}
