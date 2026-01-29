/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 * Modified and created by Nerull 2018, for boss encounter.
 * Bossencounter ruled against by AoD. Encounter removed.
 * 5 june 2018.
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_MERE;


/*
 * Function name: block_player()
 * Description  : Checks if a monster is present and blocks passage if true
 */
public int
block_player()
{
    if (present("_quest_assassin_"))
    {
        write("A dark clad assassin blocks you from entering the pit!\n");
        
        return 1;
    }
    return 0;
}


void
create_faerun_room()
{
    setuid();
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    
    set_short("You are somewhere in a dark rocky cave");
    
    set_long("You are somewhere in a dark rocky cave. The jagged "
    +"rocky ceiling is filled with cobweb, roots and some moss. It "
    +"seems that the cave is naturally formed by time and erosion, and "
    +"you see some swamp water trickling in from the bottom of the "
    +"walls aswell. This cave has probably sheltered many swamp "
    +"creatures over the time. Near the west "
    +"side of the cave you spot a vertical dark pit that leads "
    +"further down into the darkness.\n");
    
    add_item(({"cobweb", "cobwebs", "spider", "spiders"}),
    "The jagged ceiling is lined with cobwebs. Tiny spiders hang "
    +"in the middle of them, patiently waiting for the next "
    +"meal. Fortunately for you, your kind are not on their menu.\n");
    
    add_item(({"swamp water", "water"}),
    "You see some water from the swamp outside makes its way into "
    +"this cave through tiny eroded holes at the bottom of the rocky "
    +"formation that constitutes the wall of the cave. They seem "
    +"to lead to the dark pit.\n");
    
    add_item(({"swamp water", "water"}),
    "You see some water from the swamp outside makes its way into "
    +"this cave through tiny eroded holes at the bottom of the rocky "
    +"formation that constitutes the wall of the cave. They seem "
    +"to lead to the dark pit.\n");
    
    add_item(({"jagged ceiling", "roof", "ceiling"}),
    "The ceiling in this cave is uneven and naturally jagged. Judging "
    +"by the cobwebs that cover most of it, it houses alot of tiny "
    +"spiders. You spot some moss and roots aswell.\n");
    
    add_item(({"ground", "floor"}),
    "The ground is uneven and littered with pebbles and rocks. The "
    +"only interesting feature here is the natural vertical dark pit "
    +"near the western cave wall.\n");
    
    add_item(({"wall", "walls"}),
    "They are natural and jagged, made of solid rock. Near the western "
    +"wall you see a natural vertical dark pit in the ground.\n");
    
    add_item(({"pit", "dark pit", "vertical pit", 
    "natural vertical dark pit", "vertical dark pit"}),
    "The pit is a natural formed hole in the ground. It leads "
    +"down into darkness and you can't see the bottom. You "
    +"probably don't want to end up in there.\n");
    
    add_item(({"moss", "root", "roots"}),
    "You see some patches of moss and roots through the cobwebs. The "
    +"ceiling is probably porous due to trees and plants growing "
    +"on top of the cave.\n");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "metrail2", "north");
    add_exit(ROOM_DIR + "mepit", "down", block_player);
    
    add_npc(NPC_DIR +"quest_assassin", 2);
}


public void
init()
{
    ::init();
}


void
reset_faerun_room()
{
    set_searched(0);
}
