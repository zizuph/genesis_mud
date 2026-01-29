/* lake/obj/elf_ship.c cloned by lake/pier3.c */
inherit "/d/Genesis/ship/ship";

#include "../defs.h"

#define GEN_ELF_DIR "/d/Genesis/start/elf/room/"

public void
create_ship()
{
    reset_euid();
    set_cabin(DOCK_DIR + "faerie/cabin");
    set_deck(DOCK_DIR + "faerie/deck");
    set_captain(clone_object(DOCK_DIR + "faerie/captain"));
    set_places_to_go(({ DOCK_DIR + "faerie/dock",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        GEN_ELF_DIR + "outside_harbour_2",
        GEN_ELF_DIR + "outside_harbour_1",
        GEN_ELF_DIR + "cove_2",
        GEN_ELF_DIR + "outside_harbour_1",
        GEN_ELF_DIR + "outside_harbour_2",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1",
        DOCK_DIR + "sea1" }));
    set_ticket_id("the elf-emerald line");
    set_time_between_stops(({ 24, 3, 3, 3, 3, 3, 5, 3, 24, 3, 3,
        5, 3, 3, 3, 3 }));
    set_name("ship");
    add_name("boat");
    add_adj("stream-lined");
    set_long("It is a really fine ship.\n");
}
