/*
  A haunted room. Mortricia 920927
 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"

void
reset_room()
{
    object creep;

    if (!present("creep", TO)) {
        creep = clone_object(HAUN_DIR + "creep");
        creep -> move(TO);
    }
}

void
create_room()
{
    set_short("Tunnel");
    set_long(BSN(
        "You are no longer surrounded by the canvas of the tent, " +
        "somehow you have entered some kind of under-ground " +
        "world, consisting of tunnels. Down here the walls are " +
        "made of soil, supported here and there by moulded " +
        "wooden boards. To the east is a tunnel that goes " +
        "slightly upwards, and to the west a larger tunnel " +
        "may take you further into this awful place."
    ));
    add_item(({"tunnel", "tunnels"}), BSN(
        "Which tunnel? The eastern or western tunnel?"
    ));
    add_item(({"eastern tunnel", "eastern"}), BSN(
        "It is going somewaht upwards and it seems to be wet " +
        "and very slippery. It's doubtful if you can " +
        "go that way."
    ));
    add_item(({"western tunnel", "western"}), BSN(
        "This tunnel looks dry."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HAUN_DIR + "house_2", "east", "@@going_back");
    add_exit(HAUN_DIR + "house_4", "west", 0);

    reset_room();
}

going_back()
{
    int tp_dex;

    if (TP -> query_wiz_level() > 0) {
        return 0;
    } else {
        tp_dex = (TP -> query_stat(SS_DEX)) + random(4);
        if (tp_dex < 20) {
            write("You try to go back, but you slip!\n");
            write("Going back east seems impossible in " +
                  "your present state.\n");
            return 1;
        }
        write("You manage to crawl back a bit but you find it " +
              "somewhat cumbersome.\n");
        return 0;
    }
}
