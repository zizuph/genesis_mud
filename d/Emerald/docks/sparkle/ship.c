inherit "/d/Genesis/ship/ship";
#include <time.h>

#include "../defs.h"
public void
create_ship()
{
    reset_euid();
    set_cabin(DOCK_DIR + "sparkle/cabin");
    set_deck(DOCK_DIR + "sparkle/deck");
    set_captain(clone_object(DOCK_DIR + "sparkle/captain"));
    set_places_to_go( ({
        "/d/Emerald/telberin/dock/telberin_dock",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        "/d/Genesis/start/human/town/pier7",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1" }));
set_time_between_stops(({ 24,2,2,2,2,2,2,2,2,2,24,2,2,2,2,2,2,2,2,2}));
    set_ticket_id(SPARKLE_LINE);
    set_name("ship");
    add_name("boat");
    add_adj("nice");
    set_long("It is a really fine ship.\n");
}


/*
 * Function name: start_ship
 * Description  : Make the ship do its thing
 * Arguments    : where - the location number to start in
 * Returns      : 0 - failed to start the ship
 *                1 - ship started
 */
public varargs int
start_ship(int where)
{
    ::start_ship(where);

    write_file("/d/Emerald/log/shipline",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") SHIP LAUNCHED BY: "
      + file_name(previous_object()) + "\n");
} /* start_ship */
