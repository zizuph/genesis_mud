/*     The standard Field-of-Gondor-file, made by Elessar for Genesis   */
/*     February 1992. No copyrights, but would like to have my name     */
/*     mentioned if anyone modifies this file for own use.  :-)         */

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/time.c"

#include "/d/Gondor/elessar/lib/herbsearch.h"
int areatype; /* 1=Grass 2=Bushes 3=Trees 4=Farmland 5=Rocky */
	    /* 6=Snow 7=Forest 8=Road 9=Barren (0 means no type-desc) */
string area,areadesc,areaname,land,grass,extraline,treetype;
string forest,mountain;
int forest_density;

make_the_room(){
  set_short("@@short_func");
  set_long("@@describe");
  if (areatype == 1) {
    add_item("field","The field is covered by "+grass+"grass all over.\n");
    add_item("grass","The "+grass+"grass grows all over the field.\n");
  }
  if (areatype == 2) {
    add_item(areadesc,"On the green "+areadesc+" "+grass+"grass grows, along with some bushes here and there.\n");
    add_item("bushes","Some bushes growing here on the "+areadesc+".\n");
  }
  if (areatype == 3) {
    add_item(areadesc,"The "+areadesc+" is overgrown with "+grass+"grass, and some trees\n"+
	     "also stand here.\n");
    add_item("trees","A few "+treetype+"trees also grow here.\n");
  }
  if (areatype == 4) {
    add_item("field","You see a field used for agriculture by the people of "+land+",\n"+
	     "as there are covered by furrows and plough-marks here and there.\n");
    add_item("furrow","The furrows clearly indicate that this is farmland.\n");
  }
  if (areatype == 5) {
    add_item("ground","The ground is quite rocky and barren.\n");
    add_item(({"grass","trees","bushes","herbs"}),"There's no green growth here, the ground is too rocky and hard.\n");
  }
  if (areatype == 6) {
    add_item("ground","The ground is covered with snow here.\n");
    add_item("snow","The snow is white and cold.\n");
  }
  if (areatype == 7) {
    add_item("ground","There's mostly dry leaves and moss on the forest floor.\n");
    add_item("leaves","They have fallen down from the "+treetype+"trees.\n");
    add_item(({treetype,"trees"}),"The "+treetype+"trees that grow here make up the most of the forest here.\n");
  }
  if (areatype == 8) {
    add_item("road","You're on a dusty road in "+land+". You're not sure where it leads.\n");
    add_item("ground","You see a dusty road.\n");
  }
  if (areatype == 9) {
    add_item("ground","The ground is quite barren, so there's not much grows here.\n");
  }
  add_prop(ROOM_I_INSIDE,0);
  add_prop(ROOM_I_LIGHT,"@@check_lightlevel");
}

short_func()
{
  if (areatype == 1) return "A grassy "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
  if (areatype == 2) return "A bushy "+areadesc+ " in the "+area+" parts of "+areaname+" in "+land;
  if (areatype == 3) return "A "+areadesc+" with some trees in the "+area+" parts of "+areaname+" in "+land;
  if (areatype == 4) return "An agricultural "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
  if (areatype == 5) return "A rocky "+areadesc+ " in the "+area+" parts of "+areaname+" in "+land;
  if (areatype == 6) return "A snowy "+areadesc+ " in the "+area+" parts of "+areaname+" in "+land;
  if (areatype == 7) return "A "+areadesc+" in a forest in the "+area+" parts of "+areaname+" in "+land;
  if (areatype == 8) return "A road across a "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
  if (areatype == 9) return "A barren "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
  else return "A "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
}

describe() {
  object clock;
  string time,long_descf;
  clock = find_object("/d/Gondor/elessar/lib/clock");
  time = clock->query_time_of_day();
  long_descf = short_func()+". ";
  if (!clock->query_war()) {
    if (time == "night") {
      long_descf = long_descf + "Darkness rules the fields of "+areaname+" now in the nightime. ";
      if (clock->query_moon()==2) long_descf = long_descf + "A full moon gives some light though. ";
      else if (clock->query_moon()==1) long_descf = long_descf+"The moon gives a little light though. ";
      else long_descf = long_descf+"The sky is covered with dark clouds, and not even the moon "+
	"shines through. ";
    }
    if (time == "afternoon") {
      long_descf = long_descf+"The light of day shines across "+areaname+". "+
      "It is afternoon. ";
    }
    if (time == "morning") {
      long_descf = long_descf+"The sun is on its way up on the morning sky to the east. ";
    }
    if (time == "noon") {
      long_descf = long_descf + "The sun is almost at its peak on its way across the sky. "+
	"It is the middle of the day in Middle-Earth. ";
    }
    if (time == "evening") {
      long_descf = long_descf+"The sun is setting in the west, coloring the sky golden red. ";
    }
    if (time == "early morning") {
      long_descf = long_descf + "The sun is rising in the east, casting long shadows "+
	"across "+areaname+". ";
    }
  }
  else {
    if (time == "evening"||time=="night"||time=="early morning") {
      long_descf = long_descf + "Massive dark clouds cover the sky, making it "+
	"difficult to distinguish night and day. The clouds seem to be coming from "+
	  "the east, where Mordor lies. You suspect it is night now, as it is as dark "+
	    "as it can get. ";
    }
    if (time == "morning") {
      long_descf = long_descf + "A thick cover of clouds prevent the sun from "+
	"shining on the lands of "+land+", and it is almost as dark as at night. "+
	  "However you gather that it is probably morning, as it is getting a bit "+
	    "lighter than earlier. ";
    }
    if (time == "noon") {
      long_descf = long_descf + "A dark mass of clouds seems to be rolling in from "+
	"the east, covering the sky above "+land+". It is not much lighter now than "+
	  "it usually is at night, but still you suspect it is the middle of the day. ";
    }
    if (time == "afternoon") {
      long_descf = long_descf + "A thick mass of clouds cover the sky, making it "+
	"difficult to see far. You suspect that it is afternoon, as it is getting "+
	  "a bit darker than earlier. ";
    }
  }
 if (extraline) long_descf = long_descf + extraline + "\n";
  else long_descf = long_descf + "\n";
  return (break_string(long_descf,75));
}

check_lightlevel()
{
  return 1;
}

query_road()
{
  if (areatype == 8) return 1;
  return 0;
}
