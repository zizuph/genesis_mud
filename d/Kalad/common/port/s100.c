#include <macros.h>
#include "default.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit PORT_ROOM;
inherit LIBPIER;

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Long Pier");
    set_long("You are standing at the end of a long wooden pier that sticks out "+
      "into the bay. A large sign has been planted here. The "+
      "wooden planks of the pier seem to creak and groan with the slightest "+
      "movement and the sound of water roughly hitting against the supports assaults "+
      "your senses. The harsh cry of seagulls fills the air.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"wooden planks","planks","wooden plank","plank"}),"Although "+
      "they groan and creak with your every movement, the weather-beaten "+
      "wood seems sturdy enough.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the pier "+
      "above the water line.\n");
    //    add_item(({"large sign","sign"}),"There is lots of legible writing "+
    //  "on it, maybe you should read it.\n");
    add_item(({"sun"}),"You are nearly blinded for looking straight at it!\n");
    add_exit(PORT + "s99", "north");
    set_alarm(15.0,0.0,"room_events");
    sign = clone_object(SIGN);
    sign->move(TO);
    reset_room();
    add_pier_entry(MASTER_OB(TO), "Kabal", "Pan-Donut Circle");
    initialize_pier();
}

room_events()
{
    switch(random(4))
    {
    case 0:
	tell_room(TO,"A particularly large seagull flies overhead.\n");
	break;
    case 1:
	tell_room(TO,"A fresh sea breeze blows by.\n");
	break;
    case 2:
	tell_room(TO,"A dark cloud momentarily blocks the light of the sun.\n");
	break;
    case 3:
	tell_room(TO,"A flock of seagulls pass overhead.\n");
	break;
    }

    set_alarm(15.0,0.0,"room_events");
}


object
query_sign ()
{
  return sign;
}

init()
{
    ::init();
  //AA(read_sign,read);
}
/*
string
sign()
{
    return "\n"+
    "                        @@@@@@@@@@@@@@@@@@@@\n"+
    "                        @~~~~~~~~~~~~~~~~~~@\n"+
    "                        @ The Kalad-Gondor @\n"+
    "                        @     Shipline     @\n"+
    "                        @                  @\n"+
    "                        @ has been         @\n"+
    "                        @    discontinued  @\n"+
    "                        @ -- GSL           @\n"+
    "                        @__________________@\n"+
    "                        @@@@@@@@@@@@@@@@@@@@\n"+
    "                        ~~~~~~~~~~~~~~~~~~~~\n";
    }*/

