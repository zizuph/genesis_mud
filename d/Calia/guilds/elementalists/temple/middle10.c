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
        + "wall along the southern side is bare except for a pair of "
        + "iron braziers flanking an archway. Standing near the "
        + "northeastern circular wall is an imposing gigantic wooden "
        + "pillar, which seems to somehow radiate a gentle light-green "
        + "luminescence throughout the hallway.\n\n");

    try_item( ({ "walls", "wall" }),
        "The walls are hewn from a grey rock material, with crystalline veins "
      + "tightening the structure and covering the surface of the rock wall. "
      + "the surface is very smooth to the touch and you can see your own "
      + "partial reflection upon the grey surface. The wall on the west side "
      + "of the room is bare, except for a pair of iron braziers. A circling "
      + "wall occupies the northeastern area, but is mostly hidden behind the "
      + "massive wooden pillar.\n");
     
    try_item( ({ "floor", "ground", }),
        "The floor beneath you is made of pure shiny crystalline material. "
      + "You can see a faint reflection of yourself among the rainbow colors "
      + "of the refracted ambient light. A large part of the floor is "
      + "dominated by the massive pillar that reaches the full length from the "
      + "floor to the ceiling. You notice the crystalline acting differently "
      + "near the base of the pillar.\n");
    
    try_item( ({ "crystalline", "webbing", "crystalline webbing",
        "green crystalline webbing" }),
        "As in many other parts of the temple, crystalline is ever present "
      + "here. It forms the floor as well as the veins and coating on the "
      + "walls. The crystalline from the floor seems to have grown up around "
      + "the massive pillar, forming a large and delicate webbing that encases "
      + "the pillar. Rather than absorbing the dark brown color of the pillar "
      + "the crystalline seems to ebb with a pulsating pure green light.\n");
    
    try_item( ({ "pillar", "massive pillar", "massive wooden pillar",
        "brown branches", "branches" }),
        "An impressive pillar of an unknown dark brown wood has grown from "
      + "beneath the temple floor all the way up to the ceiling, where it "
      + "branches out and looks to be a main part of the supporting "
      + "structure for the entire temple. Green crystalline webbing "
      + "surrounds the pillar.\n");
    
    try_item( ({ "ceiling", "petrified wooden beams", "beams", "wooden beams" }),
        "The ceiling consists of an interwoven pattern of petrified wooden "
      + "beams, supported by the brown branches from the wooden pillar.\n");
    
    try_item( ({ "archway" }),
        "The archway is adorning the southwest wall. It is a very beautiful "+
        "accent piece in the room.\n");
     
    try_item( ({ "brazier", "braziers", "iron brazier", "iron braziers",
        "tripod", "tripods", "bowl", "coal", "iron tripods", "iron tripod",
        "small tripod", "small iron tripods", "small iron tripoid",
        "small tripods", "coals", "bowls", "circular bowl", "circular bowls" }),
        "The iron braziers are small iron tripods with a circular bowl fastened "
      + "on top. In the bowls, smoldering coals shed some light on the hallway.\n");
    
    add_exit(ELEMENTALIST_TEMPLE + "middle8", "northwest");   
    add_exit(ELEMENTALIST_TEMPLE + "sacristy", "west");  
    add_exit(ELEMENTALIST_TEMPLE + "private_chapel", "east","@@check_ceremony@@");

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