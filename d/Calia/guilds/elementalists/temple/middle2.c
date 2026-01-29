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

public void
create_temple_room()
{
    set_short("Elemental Temple Middle Circle");
    set_long("This is a broad hallway in the middle circle of the Elemental "
        + "Temple. A circular grey wall to the north houses an archway "
        + "flanked by a pair of iron braziers. A gigantic wooden pillar stands "
        + "near the southern wall and appears to be hollow. Inside of it is a "
        + "stairwell leading upwards to the other floors of the temple. "
        + "Crystalline coating on the outside of the pillar emit a silvery "
        + "shimmer that illuminates the room. The hallway continues to the "
        + "east and the west from here.\n\n");

    try_item( ({ "walls", "wall" }),
        "The walls are hewn from a grey rock material, with crystalline veins "
      + "tightening the structure and covering the surface of the rock wall. "
      + "the surface is very smooth to the touch and you can see your own "
      + "partial reflection upon the grey surface. The wall on the north side "
      + "of the room is bare, except for a pair of iron braziers flanking an "
      + "archway. A circling wall occupies the southern area, but is mostly "
      + "hidden behind the massive wooden pillar.\n");
     
    try_item( ({ "floor", "ground", }),
        "The floor beneath you is made of pure shiny crystalline material. "
      + "You can see a faint reflection of yourself among the rainbow colors "
      + "of the refracted ambient light. A large part of the floor is "
      + "dominated by the massive pillar that reaches the full length from the "
      + "floor to the ceiling. You notice the crystalline acting differently "
      + "near the base of the pillar.\n");
    
    try_item( ({ "crystalline", "webbing", "crystalline webbing",
        "green crystalline webbing", "coating", "crystalline coating" }),
        "As in many other parts of the temple, crystalline is ever present "
      + "here. It forms the floor as well as the veins and coating on the "
      + "walls. The crystalline from the floor seems to have grown up around "
      + "the massive pillar, forming a large and delicate webbing that encases "
      + "the pillar. Rather than absorbing the obsidian blackcolor of the pillar "
      + "the crystalline seems to shimmer with an ambient silvery light.\n");
    
    try_item( ({ "pillar", "massive pillar", "massive wooden pillar",
        "brown branches", "branches" }),
        "An impressive pillar of an unknown obsidian black has grown from "
      + "beneath the temple floor all the way up to the ceiling, where it "
      + "branches out and looks to be a main part of the supporting "
      + "structure for the entire temple. Silver crystalline webbing "
      + "surrounds the pillar.\n");
    
    try_item( ({ "ceiling", "petrified wooden beams", "beams", "wooden beams" }),
        "The ceiling consists of an interwoven pattern of petrified wooden "
      + "beams, supported by the black branches from the wooden pillar.\n");
    
    try_item( ({ "archway", "north" }),
        "The archway leads north to the outer circle of the Temple.\n");
     
    try_item( ({ "brazier", "braziers", "iron brazier", "iron braziers",
        "tripod", "tripods", "bowl", "coal", "iron tripods", "iron tripod",
        "small tripod", "small iron tripods", "small iron tripoid",
        "small tripods", "coals", "bowls", "circular bowl", "circular bowls" }),
        "The iron braziers are small iron tripods with a circular bowl fastened "
      + "on top. In the bowls, smoldering coals shed some light on the hallway.\n");
    
    try_item( ({ "staircase", "stairwell", "steps" }),
        "The black stairwell appears to have been grown rather than been "
      + "carved out of the inside of the pillar. Wooden steps lead to the "
      + "other floors of the temple.\n");
    
    add_exit(ELEMENTALIST_TEMPLE + "middle3", "east"); 
    add_exit(ELEMENTALIST_TEMPLE + "middle1", "west");
    add_exit(ELEMENTALIST_TEMPLE + "psuchae", "north");
    add_exit(ELEMENTALIST_TEMPLE + "pool", "south", "@@cannot_enter_inner_circle", 1, "@@cannot_see_inner_circle");
    add_exit(ELEMENTALIST_TEMPLE + "stairwell2", "up", "@@cannot_enter_worshipper_floor", 1, "@@cannot_see_worshipper_floor");
    add_exit(ELEMENTALIST_TEMPLE + "stairwell4", "down", "@@cannot_enter_worshipper_floor", 1, "@@cannot_see_worshipper_floor");
}
