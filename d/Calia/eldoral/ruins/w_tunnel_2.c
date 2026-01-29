#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
reset_room()
{
    int i,
        num;

    ::reset_room();

    num = sizeof(filter(all_inventory(), &->id(RUBBLE_NAME)));    
    num -= 4;

    setuid();
    seteuid(getuid());

    while (num < 0)
    {
        num ++;
        if (!random(2))
            clone_object(OBJ + "large_rubble")->move(TO);
        else
            clone_object(OBJ + "small_rubble")->move(TO);
        tell_room(TO, "A piece of rubble falls from the " +
            "ceiling.\n");
    }
}

public void
create_room()
{
    set_short("in a tunnel in "+CASTLE_NAME);
    set_long("You're in a dark tunnel somewhere " +
        "under "+CASTLE_NAME+". How deep, you don't " +
        "know, but the walls here seem to be carved " +
        "out of solid stone, rather than laid with " +
        "blocks of stone. The passage isn't really " +
        "cramped though, and appears to have been " +
        "constructed with the idea that it would be " +
        "frequently used, as it's quite wide and the " +
        "walls smoothly finished. It branches " +
        "here, heading north, east and south, though " +
        "from here all the exits look the same. On " +
        "the walls you can see rust-coated iron " +
        "sconces, which once held torches many, many " +
        "years ago.\n\n");

    add_item(({"ceiling", "roof"}),
        "The dark, squared-off ceiling appears to have " +
        "been cut out of the surrounding stone through " +
        "which this tunnel passes.\n");
    add_item(({"floor","ground"}),
        "The ground here is made simply from hard-packed " +
        "earth, now pounded by falling rubble from " +
        "the ceiling and walls.\n");
    add_item(({"walls"}),
        "The smoothly cut walls here look to have been " +
        "cut from the surrounding stone, and the only " +
        "things which break up it's clean surface are " +
        "jagged holes where pieces of stone have fallen " +
        "away, and rusted iron sconces.\n");
    add_item(({"sconces","sconce", "rusty sconces", "iron sconces"}),
        "Heavy iron rings form torch sconces high up on " +
        "the walls.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "w_tunnel_3", "north");
    add_exit(RUIN + "catacomb_1", "east");
    add_exit(RUIN + "w_tunnel_1", "south");

    reset_room();
}
