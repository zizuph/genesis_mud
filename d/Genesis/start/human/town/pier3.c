#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include <macros.h>
#include "town.h"

inherit STDPIER;

#define MAX_RODENTS 15

/* global variable to keep some control over the rodents ... */
object *rodents = ({ });

/* Prototype */
public void reset_room();

public void
create_room()
{
  ::create_pier();
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    set_short("Berth 3 - Grey Havens");
    set_long(
      "West pier outside a warehouse.\n" +
      "The harbour is due east, so you better not walk too close\n" +
      "to the edge. Ships and galleys are known to land here.\n" +
      "There is a sign here that reads: Berth 3 - Grey Havens.\n");

    add_exit(THIS_DIR + "pier2","north");
    add_exit(THIS_DIR + "ware3","west");
    add_exit(THIS_DIR + "pier4","south");

    add_item(({"warehouse" }),"It looks old and worn down.\n");

    add_pier_entry(MASTER_OB(TO), "Sparkle", "Pier to Grey Havens");
    initialize_pier();
    reset_room();
}

public void
spawn_rodent()
{
    /* Ratio of rats to mice is 1:2 */
    object rodent = clone_object(OBJ_DIR + (random(3) ? "mouse" : "rat2"));

    rodent->move(TO);
    rodents += ({ rodent });
    
    if (sizeof(rodents) < MAX_RODENTS)
    {
        set_alarm(120.0, 0.0, spawn_rodent);
    }
}

public void
reset_room()
{
    rodents = filter(rodents, objectp);
    if (sizeof(rodents) < MAX_RODENTS)
    {
        set_alarm(15.0, 0.0, spawn_rodent);
    }
}
