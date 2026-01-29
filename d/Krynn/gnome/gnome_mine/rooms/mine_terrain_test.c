/* 
    Misc terrain test, 
    to try out setting terrains to ROCKY (to be minable)
    and set terrains to melting (so the pickaxe can draw lava from it)

    Made by: Maelstrom, 2016/05
*/

inherit "/std/room";
#include <stdproperties.h>
#include <terrain.h>

void
create_room()
{
    set_short("Terrain test.");

    set_long("Simple terrain test for rocky and melting.\n");


    set_terrain(TERRAIN_ROCK | TERRAIN_MELTING);


    add_exit("/w/maelstrom/workroom","east",0);

}