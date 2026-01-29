#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

private object *guard = allocate(4);

public void
reset_room()
{
    int i = 4;

    while(i--)
    {
        if(!objectp(guard[i]))
        {
            guard[i] = clone_object("/d/Earthsea/gont/gont_city/liv/guard" + (random(4)+1));
            guard[i]->move(this_object());
            guard[i]->command("emote marches in.");
        }
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Narrow cobbled street");
    set_long("You are standing just south of the tunnel"+
        " leading out of the great Port of Gont on a"+
        " narrow cobbled street. The city wall towers"+
        " up above your head, together with numerous"+
        " large three-story stone buildings and high"+
        " towers. You are standing just north of a gate that"+
        " leads into the tall dark tower. A white flag flaps gently"+
        " above it. From the third floor there is a stone"+
        " bridge that joins the city wall to the north.\n");
    add_item("tunnel","Looking north you can see the wide"+
        " tunnel leading through the thick city walls, to"+
        " the fields outside.\n");
    add_item("wall","The mighty wall made by cut dark stone"+
        " towers high above your head here.\n");
    add_item(({"buildings","towers"}),"Large stone buildings"+
        " and high narrow towers form the structure of this"+
        " port city, looming over the narrow streets below.\n");
    add_item("street","The street is cobbled, and littered"+
        " by refuse and other traces of many humans walking by.\n");
    add_item("flag", "Above the gate to the south is"+
        " a white flag flapping in the breeze; the symbol of the"+
        " Lord of Gont.\n");
    add_item("gate", "The gate is set open and you see"+
        " mercenary guards passing to and fro inside the building.\n");
    add_item("tower","Southwards is a tall, narrow tower with"+
        " the white flag of the Lord of Gont flapping over it.\n");
    add_exit("city_road1", "north");
    add_exit("../guard_tower1", "south");
    reset_room();
}
