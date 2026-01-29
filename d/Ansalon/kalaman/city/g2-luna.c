/* 
 * Center of Garden
 *
 * Lunatari of Krynn
 * 2008-01-31:
 * Added a well to lead down into the sewers of Kalaman
 * 2008-02-02:
 * Made the rope lowerable and raisable.
 */ 
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
#include "/d/Krynn/common/herbsearch.h";

/* Dungeon Defines */
#define WELL_DOWN DROOM+"well1"
#define ENV(x) environment(x)

#define KRHERB "/d/Krynn/common/herbs/"
#define H1 KRHERB + "fireweed"
#define H2 "/d/Shire/common/herbs/parsley"
#define H3 "/d/Gondor/common/herbs/mint"
#define H4 KRHERB + "saskatoon"

void
reset_kalaman_room()
{
  set_searched(random(2));
}

string get_long_desc();
string get_well_desc();
string get_rope_desc();
string get_beam_desc();

create_kalaman_room()
{
    set_long(get_long_desc);
    set_short("A private garden in Kalaman");

    add_item(({"stone path","path"}),
      "A neat path, made of small brown stones, weaves its way around the garden.\n");

    add_item(({"well", "stone well"}), get_well_desc);
    add_item(({"rope", "ropes"}), get_rope_desc);
    add_item(({"beam", "beams"}), get_beam_desc);

    add_item("hook", "It is nicely decorated and made out of iron. It is used to " +
      "hold the secure the rope when it is raised.\n");
    add_item("bucket", "It is a normal steel bucket that most likely used to be " +
      "attached to the end of the rope. The bucket has a few holes in the bottom " +
      "making it quite useless for bringing up water from the well with.\n");
    add_item("winch", "The winch has a wooden knob attached that is used to " +
      "either lower or raise the rope and bucket to bring up water from the well.\n");
    add_item(({"roof", "tiles"}), "The wooden frame of the roof is very beaitfully " +
      "decorated with birds and flowers, even the two supporting oak beams have been " +
      "decorated. The tiles of the roof are red in colour.\n");
    add_item(({"great trees","trees","tree"}),
      "Trees of great size and beauty fill the garden. They have been well taken " +
      "care of and are obviously the pride of some local gardener.\n");
    add_item(({"flowers","flower"}),
      "Flowers of all kinds fill the garden.\n");
    add_item("knob", "It is a regular wooden knob attached to the crank of the winch " +
      "as a handle.\n");
    add_item("crank", "This is the crank that turns the winch when lowering or raising " +
      "the rope. The crank has a simple wooden knob attach to its handle. The crank is " +
      "oddly enough quite miskept and very rusty.\n");
    add_item("winch", "This is a classic yet beautiful winch made out of steel. Attached " +
      "to the winch is a very common strong rope. It has crank on the side with that can " +
      "be used to lower or raise the rope and bucket.\n");

    seteuid(getuid(TO));
    set_search_places(({"garden","park","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
/*
    add_exit(CITY + "g1","north",0);
    add_exit(CITY + "g5","south",0);
    add_exit(CITY + "g4","east",0);
    add_exit(CITY + "g3","west",0);
*/
    reset_kalaman_room();
}

init()
{
  ::init();

  add_action("lower_rope", "lower");
  add_action("raise_rope", "pull");
  add_action("raise_rope", "raise");
  add_action("enter_well", "enter");
  add_action("turn_crank", "turn");
}

string
get_long_desc()
{
    return "You find yourself standing in a beautiful garden in the middle " +
    "of Kalaman. " +season_garden()+ "In the center stands a quite large " +
    "and massive stone well. A stone path leads away from here to your " +
    "north, south, east and west." +
    "\n";
}

string
get_well_desc()
{   
    string text;

    text = "This a very beatiful stone creation, not just a common stone well but " +
      "a richly decorated craftsmanship, most likely the pride of some stone mason " +
      "around here. A beautiful tiled roof has been placed on top of the well, the roof " +
      "is supported by two massive oak poles with a classic winch made out of steel " +
      "between them. A steel bucket hangs from one of the poles that hold the winch. ";

    switch (DMASTER->query_status(S_GWELL))
    {
        case 0:
          text += "A long roll of rope hangs on the side of the well. The rope is " +
                  "attached to the steel winch above the well.";
        break;
        case 1:
          text += "A long rope hangs down into the darkness of the well. The rope is " +
                  "attached to the steel winch above the well.";
        break;
        default:
          text += "The well seems very ordinary and booring.";
    }

    return text + "\n";
}

string
get_beam_desc()
{   
    string text;

    switch (DMASTER->query_status(S_GWELL))
    {
        case 0:
           text = "These two massive oak beams support the roof that sits above the well. " +
                  "On the first beam you noticed a hook holding a wound up rope."; 
        break;
        case 1:
           text = "These two massive oak beams support the roof that sits above teh well. " +
                  "On the first beam you notice an empty hook.";
        break;
        default:
           text = "The bems seems very ordinary and booring.";
    }

    return text + "\n";
}

string
get_rope_desc()
{
    string text;

    switch (DMASTER->query_status(S_GWELL))
    {
        case 0:
           text = "Most of the rope is wound up on the winch but some of it hangs " +
                  "on a hook on the side of the beam.";
        break;
        case 1:
           text = "Most of the rope is wound up on the winch but some of it hangs " +
                  "on a hook on the side of the beam.";
        break;
        default:
           text = "The rope is very ordinary and booring.";
    }

    return text + "\n";
}


int
lower_rope(string str)
{
   notify_fail("Lower what?\n");

   if (!str) return 0;

   if (parse_command(str, ({ }), "[the] 'rope'"))
   {
      if(!DMASTER->query_status(S_GWELL))
      {
         write("You take the rope off the hook, unwind it and lower it " +
           "down the well.\n");
         tell_room(ENV(TP), QCTNAME(TP) + " picks up the rope from the hook " +
           "and lowers the rope down into the well.\n", TP);
         DMASTER->set_status(S_GWELL, 1);
         return 1;
      }

      notify_fail("The rope is already lowered into the well.\n");
      
      return 0;       
   }

   return 0;
}

int
raise_rope(string str)
{
   notify_fail("Pull what?\n");

   if (!str)  return 0;

   if (parse_command(str, ({ }), "[the] 'rope'"))
   {
      if(DMASTER->query_status(S_GWELL))
      {
         write("You pull the rope up from the well, wind it up and hang " +
           "it back on the hook.\n");
         tell_room(ENV(TP), QCTNAME(TP) + " pulls the rope up from the well, " +
           "winds it up and hangs it back on the hook.\n", TP);
         DMASTER->set_status(S_GWELL, 0);
         return 1;
      }

       notify_fail("The rope is not lowered into the well.\n");
         
       return 0;
   }

   return 0;
}

int
enter_well(string str)
{
   notify_fail("Enter what? The well?\n");

   if (!str) return 0;
 
   if(parse_command(str, ({ }), "[the] 'well'"))
   {
      write("You notice some bricks on the inside and step onto them.\n");
      tell_room(ENV(TP), QCTNAME(TP) + " steps over the side of the well " +
        "vanished into it.\n", TP);
      TP->move_living("M", WELL_DOWN, 1);
      tell_room(ENV(TP), QCTNAME(TP) + " arrives into the well from above " +
        "and manages to keep " + HIS(TP) + " foothold on the slipper stones.\n", TP);
      
      return 1;
   } 
}

int
turn_crank(string str)
{
  notify_fail("Turn what? The crank?\n");

  if (!str) return 0;

  if(parse_command(str, ({ }), "[the] 'crank'"))
  {
    write("You try to turn the crank around but it seems stuck, the rust " +
      "must have jammed it.\n");
    tell_room(ENV(TP), QCTNAME(TP) + " tries in vain to turn the crank " +
      "around, it seems stuck.\n", TP);
    return 1;
  }
}

