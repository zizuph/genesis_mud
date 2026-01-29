/*
 * Inner Circle of the Elemental Temple of Calia
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
    set_short("Elemental Temple Inner Circle");                   
    set_long("This room is part of the third and innermost circle "
             + "of the Elemental Temple. The circular wall surrounding this "
             + "tall chamber is made from grey stone and pure crystalline. "
             + "Looking up, you see that the walls reach high up and form a "
             + "vast dome. Just underneath the domed area you can see small "
             + "windows that let in a small amount of light. On the inner "
             + "side of this room, you see the shrouded crystalline walls "
             + "that make up the inner sanctum of the Temple.\n\n");

    try_item( ({ "wall", "walls" }),
              "Which wall? The circular wall or the shrouded crystalline wall?\n");

    try_item( ({ "circular wall" }),
              "The circular wall of the Inner Circle is hewn from a grey rock "
              + "material, with crystalline veins tightening the structure and "
              + "covering the surface of the rock wall. The surface is very "
              + "smooth to the touch and you can see your own partial reflection "
              + "upon the grey surface. The wall continues all the way up to "
              + "form a massive dome.\n");
    try_item( ({ "shrouded wall", "shrouded crystalline wall", "crystalline wall" }),
              "The shrouded crystalline wall on the northern part of the statue room "
              + "doesn't have the typical clear radiance of crystalline. Instead, the "
              + "material is shrouded, making it impossible to view the inner sanctum "
              + "of the Temple.\n");

    try_item( ({ "dome", "massive dome", "ceiling" }),
              "A dome of massive proportions looms over you, covering the entire Inner "
              + "Circle, which includes the inner sanctum. The dome consists of countless "
              + "glass and crystalline pieces in every possible color of the rainbow. "
              + "When light shines through from above, the entire Inner Circle is bathed "
              + "in a formidable mosaic that coalesces into an eternal dance of colours.\n");

    try_item( ({ "windows", "small windows", "window", "small window", "mosaic" }),
              "The small windows sit beneath the beginning of the massive dome. A small "
              + "amount of light streams through them, hitting the dome and creating "
              + "a beautiful mosaic that coalesces into an eternal dance of colours.\n");
     
    try_item( ({ "floor", "ground", }),
        "The floor beneath you is made of pure shiny crystalline material. "
      + "You can see a faint reflection of yourself among the rainbow colors "
      + "of the refracted ambient light.\n");
    
    try_item( ({ "crystalline", "webbing", "crystalline webbing",
        "green crystalline webbing", "coating", "crystalline coating" }),
        "As in many other parts of the temple, crystalline is ever present "
      + "here. It forms the floor as well as the veins and coating on the "
      + "walls.\n");

    try_item( ({ "inner sanctum", "sanctum" }),
              "The inner sanctum of the Elemental Temple is the central location and "
              + "most sacred of places in this Temple. The base of the circular room "
              + "is made from a shadowy shrouded crystalline that prevents an "
              + "observer from seeing the activities inside.\n");

    add_exit(ELEMENTALIST_TEMPLE + "inner1", "north");
    add_exit(ELEMENTALIST_TEMPLE + "inner5", "south"); 
}
