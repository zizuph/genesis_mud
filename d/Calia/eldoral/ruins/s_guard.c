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
    set_short("in a small room in "+CASTLE_NAME);
    set_long("You find yourself in a small, cramped " +
        "room near the southwest courtyard in " +
        CASTLE_NAME+". The entire " +
        "northern half of the room has disappeared " +
        "beneath a pile of broken stone and musty " +
        "earth. What little that is left appears to " +
        "be fairly plain stone surfaces, even the " +
        "ceiling here looks to be made from stone " +
        "blocks. Everything left intact is covered " +
        "in a fairly thick layer of dust and dirt, " +
        "cast into the air probably when the ceiling " +
        "caved in. A simple doorway in the south " +
        "wall serves as the room's only obvious exit.\n\n");

    add_item(({"floor"}),
        "The floor is covered in a thick layer of dust and " +
        "dirt, which doesn't do much for its appearance.\n");
    add_item(({"dust","dirt","layer"}),
        "The entire room is blanketed in a layer of dust and dirt, " +
        "which appears to have settled after the ceiling collapsed.\n");
    add_item(({"wall","walls"}),
        "The walls, or what little of them is visible, appear " +
        "to be constructed from stone blocks, though time has " +
        "worn any signs of good quality construction from their " +
        "surfaces, they appear to be fairly well assembled.\n");
    add_item(({"ceiling"}),
        "It appears as if the ceiling in this room was made " +
        "from stone, and that the stone could have been a little " +
        "thicker, judging from the fact that the entire northern " +
        "part of the ceiling has fallen in.\n");
    add_item(({"pile","rubble","broken stone","earth"}),
        "Here lies what's left of most of the ceiling and several " +
        "barrel's worth of material that the ceiling once held " +
        "up. In fact, you really can't get much further into the " +
        "room than just beyond the doorway.\n");

    DARK;
    INSIDE;

    add_exit(RUIN + "s_tunnel_1", "south");

    reset_room();
}
