#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include "/d/Shire/cypress/sys/defs.h"

void
create_ship()
{
    object cap;
    
    seteuid(getuid());
//    set_cabin(SHIP_DIR + "cabin");
    set_deck(SHIP_DIR + "deck");
    cap=clone_object(SHIP_DIR + "galin");
    set_captain(cap);
    set_places_to_go(({
        SHIP_DIR + "w6",
		SHIP_DIR + "w5",
        SHIP_DIR + "w4",
        SHIP_DIR + "w3",
        SHIP_DIR + "w2",
        SHIP_DIR + "w1",
        CYPRESS_DIR + "docks/shire_dock",
        SHIP_DIR + "w1",
        SHIP_DIR + "w2",
        SHIP_DIR + "w3",
        SHIP_DIR + "w4",
        SHIP_DIR + "w5",
        SHIP_DIR + "w6",
		CYPRESS_DIR + "docks/cypress_dock1"}));

    set_callout_fq(3);
    set_time_between_stops(({
        2,
		3,
		3,
		2,
		3,
		2,
		30,
		2,
		3,
		2,
		3,
		3,
		2,
		30}));

    set_name("ship");
    add_name("boat");
    add_adj("elegant");
    set_ticket_id("the cypress line");
    set_long("This is a tall zhip with many masts. The sails " +
        "are open, to catch any available wind.\n");
    add_item("sails",
        "They are white and full, billowing in the wind.\n");
    add_item("masts",
        "The masts are tall and made of wood. Sals hang from " +
        "them. The tallest one is as tall as a tree.\n");
}