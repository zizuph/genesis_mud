/* The standard Field-of-Gondor-file, made by Elessar for Genesis
 * February 1992. No copyrights, but would like to have my name
 * mentioned if anyone modifies this file for own use.
 * rewritten by Daneel for Rhovanion November 1993.
 */

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

private int catetype;
private string cave, cavedesc, cavename, land, rocktype, extraline;
private string region;

create_cave() {;}

create_room()
{
  extra_line = "";
  create_cave();
  set_short("@@short_func");
  ::set_long("@@describe");
  switch (cavetype)
    {
    case 1: /* Corridor */
      add_item(({"wall","walls"}),"The walls are from " + "@@rock" + ". \n");
      add_item("floor","The floor is smooth from much use. \n");
      add_item("ceiling","the ceiling is from " + "@@rock" + ". \n");
      break;
    case 2: /* Halls */
      add_item(({"wall","walls"}),"The walls are from " + "@@rock" + ". \n");
      add_item("floor","The floors is smooth from use. \n");
      add_item("ceiling","the ceiling is from " + "@@rock" + ". \n");
      break;
    case 3: /* Storage Caves */
      add_item(({"wall","walls"}),"The walls are from " + "@@rock" + 
	       " and they are covered by shelves in all sizes and shapes. \n");
      add_item("floor","The floor is smooth from much use, and it is " +
	       "covered by barrels and casks. \n");
      add_item("celing","The ceiling os from " + "@@rock" + ". \n");
      add_item(({"shelf","shelves"}),"The shelves are used to storage many " +
	       "different things on, you see nothing of value here. \n");
      add_item(({"barrel","barrels","cask","casks"}),"The barrels and casks " +
	       "empty at the moment. \n");
      break;
    case 4: /* Cells */
      add_item(({"wall","walls"}),"The walls stands of " + "@@rock" + ".\n");
      add_item("floor","The floor is smooth. \n");
      add_item("bed","The bed looks very uncomfortable. \n");
      break;
    default: 
      break;
    }
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,"@@check_lightlevel");
}

/* What kind of cave is it, corridor, hall, cell, storage?? */
set_cave_type(int type)
{
  cavetype = type;
  switch (cavetype)
    {
    case 1: cavestype = "corridor";
    case 2: cavestype = "hall";
    case 3: cavestype = "storageroom";
    case 4: cavestype = "cell";
    defaul: break;#include "def.h"
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
  return cavedesc
}

/* 
 * Notice it is not possible to set long() description freely!
 * But then again, if you want to redifine the whole description, 
 * you should inherit /d/Rhovanion/lib/room instead.
 *
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
      return "A large corridor in " + cavename + " in the " + region + 
	" parts of " + cave + ". \n";
    case 2:
      return "A large cave in " + cave_name + " in the " + region +
	" parts of " + cave + ". \n";
    case 3:
      return "A storage cave in " + cave_name + " in the " + region +
	" parts of " + cave + ".\n";
    case 4:
      return "A cell in " + cave_name + " in the " + region + " parts of " +
	cave + ".\n";

    default: "BAD";
    }
}

describe()
{
  object clock;
  string time, long_descf;
  long_descf = short_func()  + ". ";
  if (cavetype != 4)
    {
      clock = find_object("/d/Gondor/elessar/lib/clock");
      if (!clock  -> query_war())
	{
	  if (time == "night")
	    long_descf += "There seems to be very few around in the " +
	      cavestype + " now in the middle of the night. ";
	  if (time == "afternoon")
	    long_descf += "There is a lot of people, who are hurrying " +
	      "around in " + cavestype + " here in the afternoon";
	  if (time == "morning")
	    long_descf += "The people of " + cave + " seems to be getting " +
	      "and about.";
	  if (time == "noon")
	    long_descf += "It is quiet at the moment, it seems that " +
	      "everyone is busy eating.";
	  if (time == "evening")
	    long_descf += "The elves are starting to gather for their " +
	      "eveing singing.";
	  if (time == "early morning")
	    long_descf += "The elves are retirering to their caves, so you " +
	      "suppose it is early morning.";
	}
      long_descf += extraline;
    }
  return (BS(longs_descf + "\n"));
}

check_lightlevel()
{
  return 1;
}
