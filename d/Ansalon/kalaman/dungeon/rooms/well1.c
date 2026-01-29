#include "local.h"

inherit DUNGEON_IN;

#define WELL_UP   CITY + "g2-luna"
#define WELL_DOWN DROOM + "well2"

string get_long_desc();
string get_rope_desc();

create_dungeon_room()
{
   set_short("Just inside the well");
   set_long(get_long_desc);
 
   add_item("rope", get_rope_desc);
   add_item(({"winch","frame","wooden frame"}),
      "The steel winch that is positioned in the center of the well just a few inches " +
      "from your head, it holds a rope that is used to lower and raise the bucket down " +
      "into the well to fetch water to the garden. A bucket hangs from a small hook on " +
      "the side of the frame.\n");
   add_item("bucket", "It is just a normal steel bucket that used to be attached to the " +
      "end of the rope, a few holes in its bottom make it quite useless for bringing up " +
      "any water to the garden.\n");
   add_item(({"wall", "walls", "shaft"}), 
      "The walls of the well are masterly designed and created by the most experienced " +
      "of stone masons, the bricks are neatly stacked on top of each other and have " +
      "been polished by water over the years, making them very slippery. Except for the " +
      "few bricks that stand out just enough from the wall, making it possible to stand " +
      "on them. It seems possible to climb the wall out of here.\n");
   add_item(({"brick", "bricks"}),
      "The bricks are neatly stacked on top of eachother in perfect harmony, only a few " +
      "bricks at the top of the wall are standing out just enough for you to stand on.\n"); 
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
              "seems unclimable without aid of some sort. " +
              "Just above your head is the wooden frame of the winch ontop of the well. "+
              "A few bricks that stand out " +
              "from the wall makes it possible to stand here.";
   }
   else
   {
       text = "A veritcal shaft leading deep down into the ground under Kalaman. The " +
              "walls of the well are made out of neatly placed stones, perfectly " +
              "shaped to fit each other, forming a clean and slippery surface that " +
              "seems unclimable without the aid of the rope that hangs down from above. " +
              "Just above your head is the wooden frame of the winch ontop of the well. "+
              "A few bricks that stand out from the wall makes it possible to stand here.";
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
          text = "The rope is still hangs on the side of the beam up there, perhaps it " +
                 "could prove to be useful down here.";
      break;
      case 1:
          text = "The rope hangs down from the winch, it hangs free in the middle of " +
                 "the well.";
      break;
      default:
          text = "What do you mean by rope?";
   }
   
   return text + "\n";
}

int
climb_rope(string str)
{
   notify_fail("Climb what? Out?\n");

   if (!str) return 0;

   if (parse_command(str, ({ }), "[the] 'up' / 'wall' / 'wall' / 'out'"))
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
   else
   {
      write("You look around yourself, failing to see anything to hold on to " +
       "below the few bricks you are standing on. You realise that without any " +
       "aid of some sort it is impossible to climb anywhere but out of here.\n");
     
      return 1;
   }

   return 0;
}

