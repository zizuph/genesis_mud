/* /d/Faerun/guilds/warlocks/rooms/hall02.c
 *
 * Hallway in the guildhall.
 *
 * Nerull, 2018
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Somewhere in a bloody damp claystone corridor");
    
    set_long("Somewhere in a bloody damp claystone corridor. The "
    +"overwhelming stench of decay accompanied with the humidity "
    +"from the blood-soaked dusty ground creates a rather interesting "
    +"atmosphere. Tiny blood imprints of humanoid hands cover the "
    +"beige claystone walls like jewelry, creating rather odd chained "
    +"spiral patterns. Beside a single "
    +"lit black candle inside a small depression in the south wall "
    +"and a rough stone altar in the center of the corridor, only the "
    +"sound of tiny fragments of bone cracking when you step on them truly "
    +"catches your attention.\n");
    
    add_item(({"wall", "walls"}),
    "While the walls are uneven and slightly jagged, the bloody "
    +"spiral hand imprints decorate them all. You see a small "
    +"depression in the south wall with a lit black candle in it.\n");
    
    add_item(({"tiny fragments of bone", "fragments", "fragments of bone", 
    "fragments", "bone", "bones"}),
    "Littered unevenly around the ground, you see various of tiny "
    +"fragments of humanoid bone. You assume they are the results of "
    +"some brutal sacrifices done by daggers and clubs. They give away "
    +"crunchy sounds when stepped on.\n");
    
    add_item(({"rough stone altar", "altar", "stone altar",
    "rough altar"}),
    "In the dead center of the corridor, you see a rough stone "
    +"altar. It's made of a single block of granite, but "
    +"roughly chipped so the top resembles an uneven but "
    +"flat surface. Stains of blood cover the surface from various "
    +"sacrifices and killings.\n");
    
    add_item(({"stain", "stains", "stains of blood"}),
    "The stains of blood decorate the surface of the altar. Some are "
    +"from recent sacrifices while others are old.\n");
    
    add_item(({"black candle", "candle", "lit candle", 
    "lit black candle"}),
    "When you examine the candle in the small depression, you realize "
    +"it's made of a mixture of infant blood and infant fat. It "
    +"slightly illuminates the corridor.\n");
    
    add_item(({"depression", "small depression"}),
    "The small depression is a result of natural erosion. In it, "
    +"you see a lit black candle giving light to the corridor.\n");
    
    add_item(({"south wall"}),
    "The wall is covered with bloody imprints like the other "
    +"walls. You see a small depression in it that contains "
    +"a lit black candle.\n");
    
    add_item(({"tiny blood imprints", "tiny imprints", 
    "blood imprints", "bloody imprints", "tiny bloody imprints",
    "imprints", "patterns", "pattern", "spiral pattern", 
    "odd spiral patterns", "odd spiral pattern"}),
    "Someone seems to have used dismembered infant hands to "
    +"create bloody imprints in spiral patterns on the walls "
    +"here. When you think of it, the patterns make you feel "
    +"comfortable. Cozy.\n");
    
    add_item(({"ground", "blood-soaked dusty ground", "dusty ground",
    "blood-soaked ground"}),
    "Without doubt, there has been a lot of bloodletting here. Old and "
    +"rather fresh blood soaks the dusty ground. giving it a rather "
    +"crimson-black colour. Tiny fragments of bone also litters the "
    +"ground here.\n");
    
    add_item(({"humidity", "atmosphere"}),
    "The air kind of tastes metallic along with the smell of evaporating "
    +"blood on the ground, creating a rather closed or maybe heavier "
    +"atmosphere as normal. Interesting.\n");
    
    add_item(({"corridor"}),
    "The claystone corridor leads to other adjacent areas. You feel the "
    +"slight draft coming from other directions.\n");

    add_exit(WARLOCK_ROOMS_DIR + "shop", "north");
    add_exit(WARLOCK_ROOMS_DIR + "central", "east");
    add_exit(WARLOCK_ROOMS_DIR + "hall01", "west");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}