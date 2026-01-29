#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include "/d/Shire/common/defs.h"

#define ANDUIN_DIR  "/d/Gondor/anduin/"
void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(SHIP_DIR + "osprey_cabin");
    set_deck(SHIP_DIR + "osprey_deck");
    cap=clone_object(SHIP_DIR + "bergil");
    set_captain(cap);
    set_places_to_go(({"/d/Shire/sarnford/dock.c",
                SHIP_DIR    + "mt1",
                SHIP_DIR    + "w6",
                SHIP_DIR    + "gh8",
                SHIP_DIR    + "gh7",
                SHIP_DIR    + "gh6",
                SHIP_DIR    + "gh5",
                SHIP_DIR    + "gh4",
                SHIP_DIR    + "gh3",
                SHIP_DIR    + "gh2",
                SHIP_DIR    + "gh1",
		            "/d/Gondor/minas/harlond/pier3",
		        SHIP_DIR    + "gh1",
                SHIP_DIR    + "gh2",
                SHIP_DIR    + "gh3",
                SHIP_DIR    + "gh4",
                SHIP_DIR    + "gh5",
                SHIP_DIR    + "gh6",
                SHIP_DIR    + "gh7",
                SHIP_DIR    + "gh8",
                SHIP_DIR    + "w6",
                SHIP_DIR    + "mt1"}));
    set_callout_fq(3);
    set_time_between_stops(({45,
                              3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3,
                             45,
                              3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3}));

    set_name("ship");
    add_name("boat");
    add_adj("small");
    add_adj("slender");
    set_ticket_id("the osprey");
    set_board_enabled(1);
    set_long("This small, slender ship rides eagerly on the waves.\n");
}