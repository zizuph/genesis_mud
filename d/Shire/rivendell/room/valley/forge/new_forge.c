 
/*
 * Forge for Smith's guild
 * By Finwe January 2001
 * 
 * This file calls the forge in the smiths guild. It also alters
 * some of the routines to make them more 'elvish' and fitting for
 * the valley.
 */


inherit "/d/Shire/smiths/forge/base_forge.c";
#include "../local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"
//#define SMITHS_NPC +"berim"

void create_room() 
{
    ::create_room();
    set_short("The forge of Imladris");
    set_long("This forge is where elves come to forge items. " +
        "They have forged may items here as the forge looks " +
        "used despite the care the elves have used to protect " +
        "it. The room is clean despite all the work that must " +
        "go on in here. A large forge sits in the center of the " +
        "room with a large bellow next to it. Forging tools are " +
        "next to the forge for experience smiths to use. A sign " +
        "is posted on the wall.\n");
    add_item("sign",
        "It is posted to the wall with something written on it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    add_exit(VALLEY_DIR +"forge_hall", "east");
}

 string read_sign()
{
    return"\n"+    
    "+--------------------------------------------------------------+\n"+
    "|  o O o                                                o O o  |\n"+
    "|    o                                                    o    |\n"+
    "|                                                              |\n"+
    "|                     The Forge of Imladris                    |\n"+
    "|                     --======= 0 ========--                   |\n"+
    "|                                                              |\n"+
    "|   Forging weapons and armours successfully requires great    |\n"+
    "|   skill. It is also tiring work and takes much out of the    |\n"+
    "|   strongest person. Remember this as you will become quite   |\n"+
    "|   thirsty, hungry, and tired.                                |\n"+
    "|                                                              |\n"+
    "|   Broken armours can often be mended.                        |\n"+
    "|                                                              |\n"+
    "|   To get raw materials quickly, melt down useless items.     |\n"+
    "|                                                              |\n"+
    "|   Skilled smiths may forge the following items here:         |\n"+
    "|                                                              |\n"+
    "|     Armours                  Weapons                         |\n"+
    "|   ==========================================                 |\n"+
    "|   - Shirt of chainmail     - Halberds                        |\n"+
    "|   - Shirt of ringmail      - Battle axes                     |\n"+
    "|   - Helms                  - Longswords                      |\n"+
    "|   - Platemails             - Stillettoes                     |\n"+
    "|   - Greaves                - Shortswords                     |\n"+
    "|   - Bracers                - Claymores                       |\n"+
    "|   - Boots                                                    |\n"+
    "|                                                              |\n"+
    "|    o                                                   o     |\n"+
    "|  o O o                                               o O o   |\n"+
    "+--------------------------------------------------------------+\n\n";
}
/*
public void
tools_held(object obj)
 {
    object tools;
    if (tools = present("smiths_forging_tools", obj))
    {
         this_player()->catch_msg(
             "You're unable to leave the forge while holding the forging tools.\n");
    }

 }
 */