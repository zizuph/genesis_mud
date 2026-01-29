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
    set_short("a small room in the ruins of " +
        CASTLE_NAME);
    set_long("You are in a small, dank room. It's " +
        "shaped perfectly square, with simple stone " +
        "walls each identical to the other. " +
        "Beneath you, the floor is formed from " +
        "tightly placed flagstones, presumably " +
        "placed upon packed earth, and above your " +
        "head low, cracked timbers support a " +
        "shadow-shrouded ceiling. In fact, the only " +
        "really noteworthy feature of the room is " +
        "one point in the northeast corner where " +
        "the joint between the roof and the walls " +
        "has given way entirely, leaving a pile of " +
        "rubble and musty soil on the floor.\n\n");

    add_item(({"walls", "wall"}),
        "Nothing particularly fancy, the walls of this small " +
        "room are simply constructed from blocks of grey stone.\n");
    add_item(({"floor", "flagstones"}),
        "Comprised of tightly packed flagstones, the floor of " +
        "the rooms doesn't look a whole lot different than the " +
        "walls.\n");
    add_item(({"ceiling", "roof", "timbers"}),
        "Above your head, low-hung timbers support a ceiling " +
        "apparently constructed with cross-planks, supporting the " +
         "earthworks above.\n");
    add_item(({"pile", "rubble", "soil"}), 
        "Nothing more than a pile of rocks and " +
        "earth that have fallen through the hole in " +
        "the northeast corner near the ceiling.\n");


    DARK;
    INSIDE;

    add_exit(RUIN + "w_tunnel_1", "west");

    reset_room();
}
