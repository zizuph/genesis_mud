#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include "/d/Shire/common/defs.h"

#define ANDUIN_DIR  "/d/Gondor/anduin/"
void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(SHIP_DIR + "har_cabin");
    set_deck(SHIP_DIR + "har_deck");
    cap=clone_object(SHIP_DIR + "ilderril");
    set_captain(cap);
    set_places_to_go(({"/d/Shire/common/greyhaven/pier8",
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
		        ANDUIN_DIR  + "harlond",
		        ANDUIN_DIR  + "sriver1",
		        ANDUIN_DIR  + "sriver3",
		        ANDUIN_DIR  + "pelargir",
                    "/d/Gondor/minas/harlond/pier3",
		        ANDUIN_DIR  + "pelargir",
		        ANDUIN_DIR  + "sriver3",
		        ANDUIN_DIR  + "sriver1",
		        ANDUIN_DIR  + "harlond",
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
    add_adj("elegant");
    set_ticket_id("the harlond line");
    set_board_enabled(1);
    set_long("This is an elegant ship in perfect condition.\n");
}