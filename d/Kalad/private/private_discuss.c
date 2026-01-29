inherit "/std/room";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void create_room()
{
    set_short("Kalad Wizard's Private Discussion Room");
    set_long(BS(
      "This dark room is where the wizard's of Kalad go " +
      "to discuss topics of a nature private to their " +
      "domain. You almost think you can hear the echos of " +
      "of the many secrets that have been voiced over the " +
      "years, but their meaning seems to elude you.\n"));

    add_prop(ROOM_I_INSIDE,1);

}

