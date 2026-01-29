#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define GUARD3 "/d/Earthsea/gont/gont_city/liv/guard3"

private object *guards = allocate(3);

public void
reset_room()
{
    int i = 3;

    while(i--)
    {
        if(!objectp(guards[i]))
        {
            guards[i] = clone_object(GUARD3);
            guards[i]->move(this_object(), 1);
            guards[i]->command("emote marches in.");
        }
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Northwest corner of guard tower (second floor)");
    set_long("This is the northwest corner "+
        "of the guard tower. The walls are made of black stone "+
        "carefully fitted together without mortar. Apparently this is "+
        "where the guards sleep, for you see bunk beds stacked one "+
        "above the other against the walls. "+
        "Some light enters in between "+
        "a few small slits in the wall. "+
        "Otherwise the room is very sparsely furnished and "+
        "has no sign of softness or luxury about it whatsoever. "+ 
        "Granite flagstones pave the floor.\n");
    add_item("slits",
        "The slits in the wall serve to allow light to "+
        "enter, but nothing else (such as arrows or spears).\n");
    add_item((({"beds", "bunk beds"})),
        "These are hard cots that the mercenaries sleep on.\n");
    add_item((({"stone", "black stone", "walls", "floor",
        "granite flagstones", "flagstones"})),
        "The walls and floor are made of the same dark rock as "+
        "the city walls.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("tower_2", "southeast");
    reset_room();
}
