#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include <macros.h>
#include <stdproperties.h>

inherit STDPIER;

#define BERTH_INFO "Berth 5 - Passage to Last Town in Terel"

void
create_room()
{
  ::create_pier();
    set_short(BERTH_INFO);
    set_long("\n"+
      "South pier in Sparkle harbour.\n" +
      "You are standing on the pier just outside a quite modern warehouse.\n" +
      "The south pier extends far to the east where many ships moor.\n"+
	  "On a pole there is a sign that reads: " + BERTH_INFO + ".\n");


    add_item(({"warehouse" }),"It looks quite modern.\n");
    add_item(({"pier" }),"The pier is littered with debris from the ships.\n"+
						 "You can see that it extends far to the east. To\n"+
						 "the north you also see a few berths and the start\n"+
						 "of the shorter north pier.\n");
	add_item(({"pole" }),"A real sturdy wooden pole with a sign nailed to it\n.");
	add_item(({"debris", "litter", "nail" }),"There is nothing strange about it.\n");

    add_exit(TOWN_DIR + "pier4","north");
    add_exit(TOWN_DIR + "ware2","south");
    add_exit(TOWN_DIR + "pier6","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");
    add_pier_entry(MASTER_OB(TO), "Sparkle", "Passage to Last, Terel");
    initialize_pier();
}
