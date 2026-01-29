/*
 * Middle Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes
int ceremony_status = 0;

public void
create_temple_room()
{
    set_short("Elemental Temple Middle Circle");
    set_long("This is a broad hallway in "
        + "the middle circle of the Elemental Temple. The circular grey "
        + "wall along the southeastern side is bare except for a pair of "
        + "iron braziers flanking an archway. The most imposing feature "
        + "present is the gigantic white pillar, reaching from the floor "
        + "to the ceiling. "
        + "The walls of this room shine with azure brilliance echoed by "
        + "the crystalline veins on the pillar. The hallway continues to "
        + "the west and northeast of here.\n\n");
                   
    try_item( ({ "walls", "wall" }),
        "The walls are hewn from a grey rock material, with crystalline veins "
      + "tightening the structure and covering the surface of the rock wall. "
      + "the surface is very smooth to the touch and you can see your own "
      + "partial reflection upon the grey surface. The wall on the southeast side "
      + "of the room is bare, except for a pair of iron braziers. A circling "
      + "wall occupies the northwestern area, but is mostly hidden behind the "
      + "massive white pillar.\n");
     
    try_item( ({ "floor", "ground", }),
        "The floor beneath you is made of pure shiny crystalline material. "
      + "You can see a faint reflection of yourself among the rainbow colors "
      + "of the refracted ambient light. A large part of the floor is "
      + "dominated by the massive pillar that reaches the full length from the "
      + "floor to the ceiling. You notice the crystalline acting differently "
      + "near the base of the pillar.\n");
    
    try_item( ({ "crystalline", "webbing", "crystalline webbing",
        "yellow crystalline webbing" }),
        "As in many other parts of the temple, crystalline is ever present "
      + "here. It forms the floor as well as the veins and coating on the "
      + "walls. The crystalline from the floor seems to have grown up around "
      + "the massive pillar, forming a large and delicate webbing that encases "
      + "the pillar. Rather than absorbing the fierce red color of the pillar "
      + "the crystalline seems to explode with a yellow glow.\n");
    
    try_item( ({ "pillar", "massive pillar", "massive wooden pillar",
        "brown branches", "branches", "massive white pillar", "white pillar" }),
        "An impressive pillar of a fierce red wood has grown from "
      + "beneath the temple floor all the way up to the ceiling, where it "
      + "branches out and looks to be a main part of the supporting "
      + "structure for the entire temple. Yellow crystalline webbing "
      + "surrounds the pillar.\n");
    
    try_item( ({ "ceiling", "petrified wooden beams", "beams", "wooden beams" }),
        "The ceiling consists of an interwoven pattern of petrified wooden "
      + "beams, supported by the white branches from the wooden pillar.\n");
    
    try_item( ({ "archway" }),
        "The archway is adorning the southeast wall. It is a very beautiful "+
        "accent piece in the room.\n");
     
    try_item( ({ "brazier", "braziers", "iron brazier", "iron braziers",
        "tripod", "tripods", "bowl", "coal", "iron tripods", "iron tripod",
        "small tripod", "small iron tripods", "small iron tripoid",
        "small tripods", "coals", "bowls", "circular bowl", "circular bowls" }),
        "The iron braziers are small iron tripods with a circular bowl fastened "
      + "on top. In the bowls, sparking embers shed some light on the hallway.\n");

    add_exit(ELEMENTALIST_TEMPLE + "middle9", "northeast");     
    add_exit(ELEMENTALIST_TEMPLE + "private_chapel", "west","@@check_ceremony@@");
    add_exit(ELEMENTALIST_TEMPLE + "seeker_start", "east");  

}

void
set_ceremony(int i)
{
    ceremony_status = i;
}

int
check_ceremony()
{
    if (ceremony_status)
    {
        if (!IS_MEMBER(TP))
        {
            write("The chapel is closed at the moment as there is a "+
                "ceremony taking place. Please come back later.\n");
            return 1;
        }
        else
        {
            write("\n\nThere is a ceremony taking place right now. You are "+
                "permitted to enter but please be quiet.\n\n");
            return 0;
        }
    }

    return 0;
}