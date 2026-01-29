#include "default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Intersection of Chains Street and Servant Street");
    set_long("You have reached a large intersection in the southwestern "+
      "area of the Caravan district. At this point the Street of Chains, "+
      "which runs north-south meets with Servant street, which heads "+
      "west-east. Many gloomy-looking buildings line this intersection, "+
      "and something in the air seems to cast an atmosphere of despair that "+
      "strikes you to the core of your soul. This heaviness that weighs "+
      "upon your heart seems to emanate from a collection of buildings to "+
      "the southwest. At one corner, a large wooden sign sways in the "+
      "breeze.\n");

    add_item( ({ "gloomy-looking buildings", "buildings" }),
      "Examining the buildings, you notice how drab and dreary they appear. "+
      "They seem to sag in depression, as if they could feel the sadness "+
      "within the air.\n");

    add_item( ({ "collection of buildings", "collection" }),
      "You glimpse a few squat one-story structures and what appears to be "+
      "a raised platform near the center of the collection. However, most "+
      "of your view is blocked out by the wooden fence encircling the "+
      "buildings. You notice a sign in the corner.\n");

    add_item( ({ "fence", "wooden fence" }),
      "It is a dark-colored fence that stretches west and south.\n");

    add_item( ({ "sign", "large sign", "wooden sign" }),
      "There are words on it, maybe you should read it?\n");

    add_exit(CVAN + "servant/s1", "west");
    add_exit(CVAN + "chains/s2", "north");
    add_exit(CVAN + "servant/s2", "east");
    add_exit(CVAN + "chains/s3", "south");
}

string
sign()
{
    return "\n"+
    "          ******************************\n"+
    "          *                            *\n"+
    "          *        SLAVE  MARKET       *\n"+
    "          *   OF THE CARAVAN DISTRICT  *\n"+
    "          *        CITY OF KABAL       *\n"+
    "          *                            *\n"+
    "          ******************************\n"+
    "          ||||||||||||||||||||||||||||||\n";
}

void
init()
{
    ::init();
    AA(read_sign,read);
}
