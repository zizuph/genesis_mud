/*
 * /d/Gondor/pelargir/docks/dock7.c
 *
 * Destination: ~Kalad/common/port/s100 
 *
 * Modification log:
 * Olorin, 20-Jan-97: added ROOM_I_NO_CLEANUP
   Ported to the new ship system by Tapakah, 06/2009
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/common/lib/gs_include.c"

#include "/d/Gondor/defs.h"
inherit "/d/Genesis/gsl_ships/lib/pier";

object  Ship;

public void
reset_room()
{
  ::reset_room();
  return;
  if (objectp(Ship))
        return;

    Ship = clone_object(SHIP_DIR + "ship5");
    Ship->start_ship();
}

public void
create_room()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("The docks here have begun to extend farther out into "
      + "the river than those farther north. Many fishing boats dock "
      + "here and out in the Anduin to the east a few are plying their "
      + "trade. Many more ships are going about various other business. "
      + "The dock to the northwest is decorated with various Gondorian "
      + "banners and the one to the east is piled with fish. The city "
      + "of Pelargir extends back to the west."));
    add_dockships();
    add_anduin("docks");
    add_exit(PELAR_DIR + "docks/dock6","northwest",0);
    add_exit(PELAR_DIR + "docks/dock8","east",0);
    add_exit(PELAR_DIR + "streets/earnil03", "west", 0);

    // The room may not be unloaded:
    add_prop(ROOM_I_NO_CLEANUP, 1);
    //clone_object(SHIP_DIR + "kalad_sign")->move(TO);

    add_pier_entry(MASTER_OB(TO), "Pelargir", "Connection to Grey Havens");
    initialize_pier();
    reset_room();
}

