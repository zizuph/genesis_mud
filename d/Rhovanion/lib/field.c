
/*     The standard Field-of-Gondor-file, made by Elessar for Genesis
*     February 1992. No copyrights, but would like to have my name
*     mentioned if anyone modifies this file for own use.
   *     With modifications made by Daneel for Rhovanion.
   *     Complete rewrite by Randor.
*/

#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"

private int areatype;
private string area, areadesc, areaname, land, grass, extraline, treetype;

create_field() { ; }

create_room()
{
   extraline = "";
   create_field();
   set_short("@@short_func");
   ::set_long("@@describe");
   switch (areatype) {
      case 1:
      add_item("field", "The field is covered by " + grass +
         "grass all over.\n");
      add_item("grass", "The " + grass + "grass grows all over the field.\n");
      break;
      case 2:
      add_item(areadesc, "On the green " + areadesc + " " + grass +
         "grass grows, along with some bushes here and there.\n");
      add_item("bushes", "Some bushes growing here on the " +
         areadesc + ".\n");
      break;
      case 3:
      add_item(areadesc, BS("The " + areadesc + " is overgrown with " +
            grass + "grass, and some trees also stand here.\n"));
      add_item("trees", "A few " + treetype + "trees also grow here.\n");
      break;
      case 4:
      add_item("field", BS("You see a field used for agriculture by " +
            "the people of " + land + ", as there are covered by furrows " +
            "and plough-marks here and there.\n"));
      add_item("furrow","The furrows clearly indicate that this is " +
         "farmland.\n");
      break;
      case 5:
      add_item("ground","The ground is quite rocky and barren.\n");
      add_item(({ "grass", "trees", "bushes", "herbs" }),
         "There's no green growth here, the ground is too rocky and hard.\n");
      break;
      case 6:
      add_item("ground", "The ground is covered with snow here.\n");
      add_item("snow", "The snow is white and cold.\n");
      break;
      case 7:
      add_item("ground", "There's mostly dry leaves and moss on the " +
         "forest floor.\n");
      add_item("leaves", "They have fallen down from the " + treetype +
         "trees.\n");
      add_item(({ treetype, "trees" }), "The " + treetype +
         "trees that grow here make up the most of the forest here.\n");
      break;
      case 8:
      add_item("road", "You're on a dusty road in " + land + ". You're " +
         "not sure where it leads.\n");
      add_item("ground", "You see a dusty road.\n");
      break;
      case 9:
      add_item("ground",
         "The ground is quite barren, so there's not much grows here.\n");
      break;
      case 10:
      add_item("path", "the path is surrounded by a very dense forest, " +
         "the path is rather barren here.\n");
      break;
      case 11:
      add_item("road", "the road is surrounded by a very dense forest, " +
         "and looks rather deserted.\n");
      break;
      default: break;
   }
   
   add_prop(ROOM_I_INSIDE,0);
   add_prop(ROOM_I_LIGHT,"@@check_lightlevel");
   
}


/*
* 1=Grass 2=Bushes 3=Trees 4=Farmland 5=Rocky
* 6=Snow 7=Forest 8=Road 9=Barren 10 = Path
* 11 = Men-i-Naugrim 12 = Riverbank
* (0 means no type-desc)
*
* Look at short_func() for some more information.
*/

set_area_type(int type) { areatype = type; }
query_area_type() { return areatype; }

/* The name of the area. More accurate than land. Always define it. */

set_area_name(string str) { areaname = str; }
query_area_name() { return areaname; }

/* The type of the grass (green, long etc). Use with area types 1-3 */

set_grass_type(string str) { grass = str; }
query_grass_type() { return grass; }

/* Gondor, Rhovanion, Rohan etc... Always define it. */

set_land(string str) { land = str; }
query_land() { return land; }

/* The type of the trees (pine, oak etc). */

set_tree_type(string str) { treetype = str; }
query_tree_type() { return treetype; }

/* Brief area description (field, prairie etc...) Always define it. */

set_area_desc(string str) { areadesc = str; }
query_area_desc() { return areadesc; }

/* Southern, western, whatever... Always define it. */

set_region(string str) { area = str; }
query_region() { return area; }

/* Notice that it isn't possible to set long() description freely!
* But then again, if you want to redefine the whole description,
   * you should inherit /d/Rhovanion/lib/room instead.
*/

set_long(string str)
{
   extraline = str;
}

short_func()
{
   switch(areatype) {
      case 1:
      return "A grassy " +areadesc+ " in the " +area+ " parts of " +
      areaname;
      case 2:
      return "A bushy " +areadesc+ " in the " +area+ " parts of " +
      areaname;
      case 3:
      return "A " +areadesc+ " with some trees in the " +area+
      " parts of " +areaname;
      case 4:
      return "An agricultural "+areadesc+" in the " +area+ " parts of " +
      areaname;
      case 5:
      return "A rocky " +areadesc+ " in the " +area+ " parts of " +
      areaname;
      case 6:
      return "A snowy "+areadesc+ " in the " +area+ " parts of " +
      areaname;
      case 7:
      return "A " +areadesc+ " in a forest in the " +area+
      " parts of " +areaname;
      case 8:
      return "A road across a " +areadesc+ " in the " +area+
      " parts of " + areaname;
      case 9:
      return "A barren " +areadesc+ " in the " +area+ " parts of " +
      areaname;
      case 10:
      return "A dark " +areadesc+ " in the " +area+ " parts of " +areaname;
      case 11:
      return "On Men-i-Naugrim through " +areadesc+ " parts of " +areaname;
      case 12:
      return "On the riverbank of " +areadesc+ " in "  +area+" "+areaname;
      default:
      return "A " +areadesc+ " in the " +area+ " parts of " +areaname;
   }
}

describe() {
   object clock;
   string time, long_descf;
   clock = find_object("/d/Gondor/elessar/lib/clock");
   time = clock->query_time_of_day();
   long_descf = short_func()+". ";
   if (!clock->query_war()) {
      if (time == "night") {
         long_descf += "Darkness rules the fields of " +
         areaname + " now in the nighttime. ";
         if (clock->query_moon() == 2)
            long_descf += "A full moon sends some light through the leaves ";
         else if (clock->query_moon() == 1)
            long_descf += "The moon gives a little light though. ";
         else
            long_descf += "The sky is covered with dark clouds, and "+
         "not even the moon shines through. ";
       }
      if (time == "afternoon") {
         long_descf += "The light of day shines across " + areaname + ". "+
         "It is afternoon. ";
       }
      if (time == "morning") {
         long_descf += "The sun is on its way up on the morning sky to the east. ";
       }
      if (time == "noon") {
         long_descf += "The sun is almost at its peak on its way " +
         "across the sky. It is the middle of the day in Middle-Earth. ";
       }
      if (time == "evening") {
         long_descf += "The sun is setting in the west, coloring the sky golden red. ";
       }
      if (time == "early morning") {
         long_descf += "The sun is rising in the east, casting long shadows "+
         "across " + areaname + ". ";
       }
   }
   else {
      if (time == "evening" || time == "night" || time == "early morning") {
         long_descf += "Massive dark clouds cover the sky, making it "+
         "difficult to distinguish night and day. The clouds seem to be "+
         "coming from the south, where Mordor lies. You suspect it is "+
         "night now, as it is as dark as it can get. ";
      }
      if (time == "morning") {
         long_descf += "A thick cover of clouds prevent the sun from " +
         "shining on the lands of " + land + ", and it is almost as dark " +
         "as at night. However you gather that it is probably morning, " +
         "as it is getting a bit lighter than earlier. ";
      }
      if (time == "noon") {
         long_descf += "A dark mass of clouds seems to be rolling " +
         "in from the south, covering the sky above "+land+". It is not " +
         "much lighter now than it usually is at night, but still " +
         "you suspect it is the middle of the day. ";
      }
      if (time == "afternoon") {
         long_descf += "A thick mass of clouds cover the sky, making it " +
         "difficult to see far. You suspect that it is afternoon, as it " +
         "is getting a bit darker than earlier. ";
      }
   }
   long_descf += extraline;
   return (BS(long_descf + "\n"));
}

check_lightlevel()
{
   return 1;
}

query_road()
{
   if (areatype == 8) return 1;
   if (areatype == 11) return 1;
   return 0;
}