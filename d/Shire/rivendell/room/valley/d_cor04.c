/*
 * Downstairs corridor
 * By Finwe, February 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("A downstairs corridor");
    set_long("You stand in a spacious corridor which veers " +
        "north and south. Large wooden pillars are set into " +
        "the walls to support the ceiling. They are squared and " +
        "are evenly spaced along the walls. The walls are an " +
        "off-white color with lamps evenly spaced on them. A " +
        "large painting hangs on the east wall.\n");
 
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved from thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
    add_item("painting",
        "The painting depicts a terrible battle before a " +
        "dark gate and tower. Before the gate and tower " +
        "many of the First-born and men are laying siege to it " +
        "and battling terrible creatures.\n");
    add_item(({"humans", "men"}),
        "They are arrayed in battle armour, killing orcs, " +
        "trolls, and other terrible creatures and assailing " +
        "the dark gate and tower. Nonetheless, the humans " +
        "look proud and fearless as they defend themselves " +
        "from the scourge of the Dark Lord.\n");
    add_item(({"first-born", "first born"}),
        "With drawn swords and arrayed in battle armour, " +
        "the First-born are attacking the thralls of the Dark " +
        "Lord. They are look proud and fearless as they " +
        "battle the Dark Lord.\n");
    add_item(({"morgul gate", "dark gate", "gate of minas morgul", "gate"}),
        "The gate is large and imposing. It is made of two " +
        "large black wings covered with thick black metal " +
        "plates. Before the gate are countless minions of " +
        "the Dark Lord, defending the gate and attacking " +
        "men and elves.\n");
    add_item(({"dark tower", "tower of minas morgul", 
            "tower of the wraiths", "tower of the moon", 
            "tower of black sorcery", "tower"}),
        "The dark tower rises from behind the gate. It is " +
        "imposing and is as black as the night.\n");        
    add_item(({"terrible creatures", "creatures", "thralls"}),
        "Orcs and trolls can be seen in the painting. Other " +
        "hideous creatures, many you have never seen before " +
        "and doubtlessly without names, battle the First-born " +
        "and humans.\n");
    add_item("battle",
        "The battle is fierce as the First-born fight " +
        "beside the humans. They are triumphantly " +
        "destroying the minions of the Dark Lord.\n");
 
    add_exit(VALLEY_DIR + "d_cor01", "north");
    add_exit(VALLEY_DIR + "d_cor07", "south");
    add_exit(VALLEY_DIR + "d_cor03", "west");
}
