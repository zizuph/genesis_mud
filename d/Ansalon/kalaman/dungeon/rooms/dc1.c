/*
 * Dungeon Corridor 1 (The Entrance)
 *
 * Lunatari of Krynn
 *
 * 2008-01-31: Added search and beginning of entrance code
 */
#include "local.h"
#include <ss_types.h>

inherit DUNGEON_IN;

#define G_SEARCHED "_kdungeon_search_grate"
#define G_DIR      "north"
#define G_OTHER    DROOM + "tun1"

string get_grate_desc();
string get_bars_desc();

create_dungeon_room()
{  
   set_dungeon_type(ROOM_MAIN);
   ::create_dungeon_room();

   add_exit("dc2", "south");
   add_exit("cg1", "west");
   add_exit("cc1", "east");

   add_item(({ "shadows", "shadow", "light" }), 
       "The space between the bars of the grate lets some of the light through " +
       "from the other room, making this room dusky instead of dark.\n");
   add_item(({ "north wall", "northern wall" }), 
       "In the southern wall a man made steel grating covers any possible exit " +
       "to the south.\n");
   add_item(({ "grate", "grating" }), get_grate_desc); 
   add_item(({ "bars" , "rusty bars", "steel bars" }), get_bars_desc);

   add_search(({ "bars","grating","grate"}), 10, "search_grating", 2);
}

init()
{
   ::init();

   add_action("open_grating",  "bend");
   add_action("enter_grating", "enter");
}

mixed
search_grating(object player, string arg)
{
    string found = "Your search and search but find nothing special.";

    if ((player->query_stat(SS_WIS) > 70) && 
        (player->query_skill(SS_AWARENESS) > 20))
    {

       if (!player->query_prop(G_SEARCHED))
       {
          player->add_prop(G_SEARCHED, 1);
          found = "You search the " + arg + " thoroughly and discover a " +
                  "weakness in the rusty steel bars, perhaps they could be " +
                  "bent or pulled apart.";
       }
       else
       {
          found = "You search the " + arg + " again but it reveals " +
                 "you nothing more of interest.";
       }
    }

    return found + "\n";
}

string
get_grate_desc()
{
  string text;

  switch (DMASTER->query_status(S_DGRATE))
  {
      case 0:
        text = "A rusty steel grate blocks any passage to the " + G_DIR + ", the steel bars " +
               "are very rusty and old. ";
      break;
      case 1:
        text = "A rusty steel grate blocks the passage going " + G_DIR + ", the rusty steel " +
               "bars seem to have been slightly bent, creating a narrow opening. "; 
      case 2:
        text = "A rusty steel grate used to blocked the passage to the " + G_DIR + ", now the " +
               "bars seems to have been bent and pulled apart so that one can squeeze " +
               "through. ";
      break;
      default:
        text = "The grate seems broken, please bug report this. ";
   }

   text += "A pale light shines in through the bars, casting " +
           "eerie shadows on the surrounding walls and floor.";

   return text + "\n";
}

string
get_bars_desc()
{
  string text;

  switch (DMASTER->query_status(S_DGRATE))
  {
      case 0:
        text = "The steel bars are covered with rust and covers the exit " + G_DIR + ".";
      break;
      case 1:
        text = "The steel bars have been slightly bent apart but not enough to " +
               "let anyone through.";
      break;
      case 2:
        text = "The steel bars have been totally bent apart, no longer blocking " +
               "anything or anyone.";
      break;
      default:
        text = "They are broken, please make a bug report about this.";
  }  

  return text + "\n";
}

/* Function: open_grating
 * Info:     Open the grating, bending the bars.
 */
int
open_grating(string str)
{
  notify_fail("Bend what?\n");

  if (!str) return 0;
  
  str = lower_case(str);

  if(parse_command(str, ({ }), "[the] 'bars'"))
  {

    notify_fail("You tense your muscles to the bursting point but " +
                "fail to bend the bars even the slightest.\n");

    if (TP->query_stat(SS_STR) < 50) return 0;

    if (!DMASTER->query_status(S_DGRATE))
    {
        write("You muster up all your strenght and you manage " +
              "bend the bars slightly apart!\n");
        tell_room(TO, QCTNAME(TP)+ " get's all worked up and " +
              "manages to slightly bend the bars of the grating.\n", TP, TP);
        DMASTER->set_status(S_DGRATE, 1);

        return 1;
    }
    else if (DMASTER->query_status(S_DGRATE) == 1)
    {
        write("You muster up all your strenght and you manage " +
              "bend the bars slightly apart!\n");
        tell_room(TO, QCTNAME(TP)+ " get's all worked up and " +
              "manages to slightly bend the bars of the grating.\n", TP, TP);
        DMASTER->set_status(S_DGRATE, 2);
        return 1;
    }
    else if (DMASTER->query_status(S_DGRATE) == 2)
    {
        notify_fail("The bars are already bent apart enough for you " +
                    "to enter the grating.\n");

        return 0; 
    }
  }

  return 0;
}

/* Function: enter_grating
 * Info:     Entering the grating, squeezing through the bars.
 */
int
enter_grating(string str)
{
  notify_fail("Enter what?\n");

  if (!str) return 0;

  if (parse_command(str, ({ }), "[the] 'grate' / 'grating'"))
  {
    if (DMASTER->query_status(S_DGRATE) == 2)
    {
       write("You hold your breath and squeeze through the grating.\n");
       tell_room(ENV(TP), QCTNAME(TP) + " bends down and leaves through the " +
          "grating.\n", TP);
       TO->set_dircmd("grating");
       TP->move_living("M", G_OTHER, 1, 0);  
       tell_room(ENV(TP), QCTNAME(TP) + " arrives crawling through the " +
          "grating.\n", TP);
      
       return 1;
    }
    else if ((DMASTER->query_status(S_DGRATE) < 2) &&
             (DMASTER->query_status(S_DGRATE) > 0))
    {
       notify_fail("The steel bars still prevent you from entering.\n");
      
       return 0;
    } 
  
    notify_fail("The steel bars seal the grating closed.\n");
    
    return 0;
  }

  return 0;
}
