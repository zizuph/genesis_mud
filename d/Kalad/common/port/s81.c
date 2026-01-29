// Ported to new ship system, Tapakah, 05/2009
#include <macros.h>
#include "default.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit PORT_ROOM;
inherit STDPIER;

#define boat (PORT + "shipline1/ship")

void
create_room()
{
  ::create_port_room();
  ::create_pier();
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Small Pier");
    set_long("You are standing at the end of a small wooden pier that sticks out "+
      "into the bay. A large sign has been planted here. The "+
      "wooden planks of the pier seem to creak and groan with the slightest "+
      "movement and the sound of water roughly hitting against the supports awakens "+
      "your senses.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"wooden planks","planks","wooden plank","plank"}),"Although "+
      "they groan and creak with your every movement, the weather-beaten "+
      "wood seems sturdy enough.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the pier "+
      "above the water line.\n");
    add_item(({"large sign","sign"}),"There is lots of legible writing "+
      "on it, maybe you should read it.\n");
    add_exit(PORT + "s80", "west");
    add_pier_entry(MASTER_OB(this_object()), "Kabal", "Passage to Sparkle");
    initialize_pier();
    //boat->start_ship();
}
/*
init()
{
    ::init();
    AA(read_sign,read);
}

string
sign()
{
    return "\n"+
    "                         @@@@@@@@@@@@@@@@@@@@@@@@@\n"+
    "                         @   The clipper ship,   @\n"+
    "                         @       SEALOVER        @\n"+
    "                         @      lands here.      @\n"+
    "                         @      Destination      @\n"+
    "                         @      ~~~~~~~~~~~      @\n"+
    "                         @      Grey Havens      @\n"+
    "                         @     _____________     @\n"+
    "                         @     Passage Price     @\n"+
    "                         @     ~~~~~~~~~~~~~     @\n"+
    "                         @    30 copper coins    @\n"+
    "                         @_______________________@\n"+
    "                         @@@@@@@@@@@@@@@@@@@@@@@@@\n";
}
*/
