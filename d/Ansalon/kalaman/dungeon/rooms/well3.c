#include "local.h"
#include <ss_types.h>

inherit DUNGEON_IN;

#define WELL_UP   DROOM + "well2"
#define WELL_DOWN DROOM + "well4"
#define W_OTHER   DROOM + "tun16"

string get_long_desc();
string get_rope_desc();
string get_grate_desc();

create_dungeon_room()
{
   set_short("Close to the bottom");
   set_long(get_long_desc);
 
   add_item("rope", get_rope_desc);
   add_item(({"wall", "walls"}), 
      "The walls of the well are masterly designed and created by the most experienced " +
      "of stone masons, the bricks are neatly stacked on top of each other and have " +
      "been polished by water over the years, making them very slippery. In the northwest " +
      "side of the wall a quite large rusty iron grating can be seen. Except for the " +
      "few bricks that stand out just enough from the wall, making it possible to stand " +
      "on them it seems impossible to climb away from here without aid of some sort.\n");
   add_item("water", "Looking down into the dark you fail to see any water but you hear " +
      "the water quite loudly.\n");
   add_item(({"steel bars", "bars", "rusty bars", "rusty steel bars"}),
      "The bars seems totally covered with rust and will probably not last many " +
      "more years down here.\n");
   add_item(({"brick", "bricks"}),
      "The bricks are neatly stacked on top of eachother in perfect harmony, only a few " +
      "bricks of the wall are standing out just enough for you to stand on.\n");
   add_item(({"hinge", "hinges"}), "These are simple steel hinges that hold the grating " +
      "in place.\n");
   add_item(({"grate", "grating"}), get_grate_desc);
}

init()
{
  ::init();

  add_action("climb_rope", "climb");
  add_action("open_grate", "open");
  add_action("close_grate", "close");
  add_action("enter_grate", "enter");
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

string
get_grate_desc()
{
   string text;
   text = "This is a quite large iron grating, made out of crude iron bars that " +
      "have been here for years, letting the rust eat into them quite badly. The "+
      "grate seems to rest upon three iron hinges. ";

   switch (DMASTER->query_status(S_WGRATE))
   {
      case 1:
        text += "The grating is open.";
      break;
      default:
        text += "The grating is closed.";
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

int
open_grate(string str)
{
    notify_fail("Open what?\n");

    if (!str) return 0;
 
    if (parse_command(str, ({ }), "[the] [iron] / [rusty] 'grate' / 'grating'"))
    {
       if (!DMASTER->query_status(S_WGRATE))
       {

           if (TP->query_stat(SS_STR) < 60)
           {
              write("You pull the bars of the "+ str +" hard but you are unable " +
                    "to open it.\n");
              tell_room(ENV(TP), QCTNAME(TP) + " pulls the bars of the "+ str +" hard "+
                    "but seems unable to open it.\n", TP);
           }
           else
           {
              write("You open the "+ str +", it gives off a loud noise.\n");
              DMASTER->set_status(S_WGRATE, 1);
              tell_room(ENV(TP), QCTNAME(TP) + " opens the "+ str +".\n", TP); 
           }

           return 1;
       }
       else
       {
         write("The grating is already open.\n");
         return 1;        
       }

       return 0;
    } 

    return 0;
}

int
close_grate(string str)
{
    notify_fail("Close what?\n");

    if (!str) return 0;
 
    if (parse_command(str, ({ }), "[the] [iron] / [rusty] 'grate' / 'grating'"))
    {
       if (DMASTER->query_status(S_WGRATE))
       {
         write("You close the "+ str +", the rusty hinges trembles under the weight.\n");
         DMASTER->set_status(S_WGRATE, 0);
         tell_room(ENV(TP), QCTNAME(TP) + " closes the "+ str +", it squeeks as it closes.\n",
           TP);
         return 1; 
       }
       else
       {
         write("The grating is already closed.\n");
         return 1;        
       }
      
       return 0;
    }


    return 0;
}

int
enter_grate(string str)
{
    notify_fail("Enter what?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }),"[the] [rusty] 'grate' / 'grating'"))
    {
        if (DMASTER->query_status(S_WGRATE))
        {
           write("You enter through the grating into the darkness.\n");
           tell_room(ENV(TP), QCTNAME(TP) + " leaves through the open "+ str +" " +
                "and vanishes into the darkness.\n", TP);
           TP->move_living("M", W_OTHER, 1);
           tell_room(ENV(TP), QCTNAME(TP) + " arrives through the "+ str +" from " +
                "the other side.\n", TP);
           
           return 1;
        }
        else
        {
           write("The "+ str +" is closed.\n");
           tell_room(ENV(TP), QCTNAME(TP) + " bangs " + HIS(TP) + " head into the " +
                "massive steel bars of the "+ str +" making some rust to losen and " +
                "float downwards into the darkness.\n", TP);

           return 1;
        }
 
        return 0;
    }
  
    return 0;
}
