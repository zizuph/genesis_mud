
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_citadel_guard_1e"))
    {
        object guard;
		guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_1e");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Citadel throne room");
    set_long("You are forced to stop and stand in awe of this vast "+
        "chamber.  You guess that the former lord or other noble of this "+
        "estate held his audiences with courtiers here.  They must have "+
        "been awed at this display of wealth and power, standing in the "+
        "center of this room, facing its owner.  The entire floor here is "+
        "of dark marble, like the rest of the citadel, so shiny you can "+
        "look down and see your face in it.  The walls are that same "+
        "smooth obsidian-like stone, also polished to perfection so that "+
        "your reflection stares back at you as you inspect them.  At "+
        "the head of the room, on the north side, sits a throne of that "+
        "same black stone.  This room is massive, stretching probably "+
        "thirty meters across and a hundred long.  What strikes you most, "+
        "however-- what causes you to stand in dumbfounded awe-- is the "+
        "ceiling.  High above you, perhaps fifteen meters, curves an "+
        "immense dome, black like the rest of this estate.  Upon the "+
        "underside of the dome are drawn thousands upon thousands-- "+
        "perhaps millions-- of tiny, intricate runes, some so detailed "+
        "that your eyes begin to hurt just looking at them.  They are "+
        "arranged in patterns that seem to have meaning, yet are lost on "+
        "you.  The only exit from this massive room leads back out into the"+
        " great hallway to the south.\n");

    AE(RHUN+"citadel/1d","south");

    add_item(({"walls","stone","wall","stones","arch","arches",}),
        "All the walls and ceiling here are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, and very impressive.\n");
    add_item(({"hall","hallway","south"}),"The hallway of black stone, "+
        "decorated along its way with numerous curving arches, stands back "+
        "to the south from here.\n");
    add_item(({"ceiling","dome","up"}),"The ceiling of this massive throne "+
        "room is a vast black dome decorated with perhaps millions of tiny "+
        "rune letters and symbols, though their meaning is lost in the "+
        "endlessness of time and in the memories of a people perhaps long "+
        "gone from Middle Earth.\n");
    add_item(({"rune","runes"}),"The runes are tiny and intricate.  "+
        "From what you can guess from this distance, they were carved "+
        "and molded from gold and then placed upon the dome in the time "+
        "long-forgotten when this place was constructed.\n");

    IN;

    reset_room();

}

