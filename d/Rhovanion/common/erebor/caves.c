/* The standard Field-of-Gondor-file, made by Elessar for Genesis
 * February 1992. No copyrights, but would like to have my name
 * mentioned if anyone modifies this file for own use.
 * Rewritten by Daneel for Rhovanion November 1993.
 * Once again modified by GeDe for Erebor in December 1993.
 * And again modified by Dubilex for Erebor in September 1996.
 */

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

private int cavetype;
private string cave, cavedesc, cavename, land, rocktype, extraline;
private string region, cavestype;

create_cave() {;}
     
     create_room()
{
  extraline = "";
  add_prop(ROOM_I_LIGHT,"@@check_lightlevel");
  create_cave();
  set_short("@@short_func");
  ::set_long("@@describe");
  switch (cavetype)
    {
    case 1: /* Corridor */
      add_item(({"wall","walls"}),"The walls are from " + rocktype + ". \n");
      add_item("floor","The floor is smooth from much use. \n");
      add_item("ceiling","The ceiling is from " + rocktype + ". \n");
      add_item(({"torches","torchholder","torchholders"}),"There are "
        + "quality torches in the holders. They will burn for "
        + "hours as it looks from here.\n");
      break;
    case 2: /* Hall */
      add_item(({"wall","walls"}),"The walls are from " + rocktype + ". \n");
      add_item("floor","The floor is smooth from use. \n");
      add_item("ceiling","The ceiling is from " + rocktype + ". \n");
      break;
    case 3: /* Storage room*/
      add_item(({"wall","walls"}),"The walls are from " + rocktype + 
               " and they are covered by shelves in all sizes and shapes. \n");
      add_item("floor","The floor is smooth from much use and it is " +
               "covered by barrels and casks. \n");
      add_item("ceiling","The ceiling is from " + rocktype + ". \n");
      add_item(({"shelf","shelves"}),"The shelves are used to store many " +
               "different things, you see nothing of value here tough. \n");
      add_item(({"barrel","barrels","cask","casks"}),"The barrels and casks " +
               "are empty at the moment. \n");
      break;
    case 4: /* Cells */
      add_item(({"wall","walls"}),"The walls stands of " + rocktype + ".\n");
      add_item("floor","The floor is rough and rugged. \n");
      add_item("bed","The bed looks very uncomfortable. \n");
      break;
    case 5: /* Room */
      add_item(({"wall","walls"}),"The walls are hewn out of the " +
              rocktype + ".\n");
      add_item("floor","The floor is covered with a rug. Cosy!\n");
      add_item("rug","It's an ordinary standard hand-knitted rug.\n");
      break;
    case 6:  /* Tavern */
      add_item(({"wall","walls"}),"The walls stands of " + rocktype + ".\n");
      add_item("floor","The floor is covered with hay. \n");
      add_item("hay","The hay is quite new and clean.\n");
      add_item(({"barrel","barrels","cask","casks"}),"These are normal wooden "
         + "barrels filled with some dark strong smelling liquid.\n"
         + "Probably dwarven beer of some sort.\n");
      break;
    case 7:  /* Guard room */
      add_item(({"wall","walls"}),"The walls stands of " + rocktype + ".\n");
      add_item("floor","The floor is rough and rugged. \n");
      add_item("bed","The bed looks very uncomfortable. \n");
      add_item("racks","The racks are in perfect shape. Small marks of "
         + "spilled oil is all that disturbs their prefectness. Pity "
         + "that they are empty.\n");
      break;
    case 8:  /* Pub */
      add_item(({"wall","walls"}),"The walls stands of " + rocktype + ".\n");
      add_item("floor","The floor is covered with hay. \n");
      add_item("hay","The hay is moist and covered with debris, beer and old  "
         + "puke. \n");
      add_item(({"barrel","barrels","cask","casks"}),"These are normal wooden "
         + "barrels filled with some dark strong smelling liquid.\n"
         + "Probably dwarven beer of some sort.\n");
      break;
    default: 
      break;
    }
  add_prop(ROOM_I_INSIDE,1);
}

/* What kind of cave is it, corridor, hall, cell etc...*/
set_cave_type(int type)
{
  cavetype = type;
  switch (cavetype)
    {
    case 1: cavestype = "corridor";
    case 2: cavestype = "hall";
    case 3: cavestype = "storageroom";
    case 4: cavestype = "cell";
    case 5: cavestype = "room";
    case 6: cavestype = "tavern";
    case 7: cavestype = "guardroom";
    case 8: cavestype = "pub";
    default: break;
    }
}

query_cave_type()
{
  return cavetype;
}

/* The name of the cave. Always define this. */
set_cave_name(string str)
{
  cavename = str;
}

query_cave_name()
{
  return cavename;
}

/* Where is the cave located? Always define */
set_cave(string str)
{
  cave = str;
}

query_cave()
{
  return cave;
}

/* In what part of cave is it located? */
set_region(string str)
{
  region = str;
}

query_region()
{
  return region;
}

/* What kind of rocks does the caves stand of? */
set_rock_type(string str)
{
  rocktype = str;
}

query_rock_type()
{
  return rocktype;
}

string rock()
{
  return rocktype;
}

set_cave_desc(string str)
{
  cavedesc = str;
}

query_cave_desc()
{
  return cavedesc;
}

/* 
 * Notice it is not possible to set long() description freely!
 * But then again, if you want to redefine the whole description, 
 * you instead should inherit /d/Rhovanion/lib/room.
 */
set_long(string str)
{
  extraline = str;
}

short_func()
{
  switch (cavetype)
    {
    case 1:
        return "You are standing in a corridor in the "+region+
          " parts of "+cave;
    case 2:
      return "You are standing in a large hall in the "+region+
        " parts of "+cave;
    case 3:
      return "You are standing in a storage room in the "+region+
        " parts of "+cave;
    case 4:
      return "You are standing in a cell in the "+region+" parts of "+
        cave;
    case 5:
      return "You are standing in a room in the "+region+" parts of "+
        cave;
    case 6:
      return "You are standing in a nice Tavern in the "+region+" parts of "+
      cave;
    case 7:
      return "You are standing in a guardroom in the "+region+" parts of "+
      cave;
    case 8:
      return "You are standing in a smoke filled Pub in the "+region+" parts of "+
      cave; 
    default: "BAD";
    }
}

describe()
{
  object clock;
  string time, long_descf;
  long_descf = short_func() + ". ";
  if (cavetype != 4)
    {
      clock = find_object("/d/Gondor/elessar/lib/clock");
      time = clock -> query_time_of_day();
      if (!clock  -> query_war())
        {
          if (time == "night")
            long_descf += "";
          if (time == "afternoon")
            long_descf += "";
          if (time == "morning")
            long_descf += "";
          if (time == "noon")
            long_descf += "";
          if (time == "evening")
            long_descf += "";
          if (time == "early morning")
            long_descf += "";
        }
    }
  else
    long_descf += " The cell is quite barren except for a bed at one wall.";
  long_descf +=  extraline;
  return (BS(long_descf + "\n"));
}

check_lightlevel()
{
  return 1;
}
