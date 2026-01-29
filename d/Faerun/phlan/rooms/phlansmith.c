/*  /d/Faerun/phlan/rooms/phlansmith.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_INDOOR;


void
create_phlan_room()
{
    set_long("The Phlan blacksmith.\n"
        +"The blacksmith shop of Phlan prominently features a sign describing"
        +" the services offered by the blacksmith. He stands near the forge,"
        +" somehow managing to choke up on a massive hammer to use it single-"
        +"handedly to form a piece of glowing metal. The walls and ceiling are"
        +" covered with soot and the air is smoky. A large vent leads to an"
        +" oversized stovepipe going through the ceiling. A pump bellows allows"
        +" the smith to heat the coal beyond its normal range to get the best"
        +" temper on his steel. Sconce mounted lamps on the walls as well as an"
        +" open window to the east provide light. Two deep barrels sit well"
        +" away from the heat source.\n");
    
    set_short("Blacksmith shop");  
    
        
    add_item(({"walls", "wall"}),
        "It is impossible to tell what kind of wood the walls are made of"
        +" beneath the soot. Several sconces with lamps are mounted around"
        +" the room for lighting and a window opens in the eastern wall.\n");

    add_item(({"forge"}),
        "A massive coal fueled forge long enough to heat a claymore"
        +" or zweihander in a single forging, this is the heart of the"
        +" smithy, with the blacksmith providing the heart beat. Several"
        +" stacks of bars, bags of coal, tools and an anvil stand"
        +" nearby.\n");

    add_item(({"floor", "ground"}),
        "Different from every building you have entered in town, this one"
        +" has a dirt floor. This must be a fire control issue. It is"
        +" packed hard from much heavy use.\n");

    add_item(({"soot"}),
        "Thick, black and grimy, soot from the coal coats the"
        +" walls and ceiling. You can't imagine breathing this for"
        +" a long period would be good for you.\n");

    add_item(({"smoke"}),
        "Thick smoke produced by the forge both flows up the vent and"
        +" rolls out into the room, stinging your mouth, nose and eyes.\n");

    add_item(({"ceiling"}),
        "The blackened and sooty ceiling does not have a typical peak,"
        +" but instead is flat with an upward slope to the rear where"
        +" the forge rests. This allows the window in the east wall"
        +" to act as a secondary vent that minimizes the chance of water"
        +" getting in through a peak vent.\n");

    add_item(({"vent"}),
        "A large hood-like vent funnels smoke and heat from the forge"
        +" through an oversized stovepipe and through the roof to the"
        +" external chimney. It is make of soot-blackened tin with"
        +" many dents and dings.\n");

    add_item(({"window"}),
        "The only window is high in the eastern wall easily ten feet"
        +" off the floor. It acts both as a secondary vent and as"
        +" a source of light. The glass itself is as soot coated as"
        +" the wall it is mounted in. It looks like a simple cord and"
        +" pulley system opens and closes the window.\n");
        
    add_item(({"metal", "bar", "bars"}),
        "Several stacks of metal bars, apparently separated by metal"
        +" type and hardness, are piled near the forge. The bar the"
        +" smith is working on now is glowing orange with heat.\n");

    add_item(({"pipe", "stovepipe"}),
        "The oversized tin stovepipe is layered in soot. Several dents"
        +" and dings cover its surface. The pipe leads to the ceiling"
        +" where it enters the chimney.\n");
        
    add_item(({"lamp", "lamps"}),
        "The lamps are of some kind of metal you cannot make out"
        +" beneath the layer of soot. You believe the decorative"
        +" metalwork was done by the smith himself.\n");

    add_item(({"sconce", "sconces"}),
        "The wrought iron sconces are beautiful even under all the"
        +" soot. The graceful curves and twists are a work of art.\n");
        
    add_item(({"bellow", "bellows", "pump bellows"}),
        "The wooden handled pump bellows has a voluminous leather air sack"
        +" fed by large brass valves. It feeds a massive flow of air to"
        +" the forge to superheat the charcoal and metals within.\n");

    add_item(({"coal"}),
        "Bags of anthracite coal are stacked for easy access while forging.\n");
        
    add_item(({"tools"}),
        "A rack of tools for the blacksmith to forge or repair any armour"
        +" or weapon. You can identify hammers, tongs, pliers and an"
        +" anvil, as well as some that are probably of the craftsman's personal"
        +" design.\n");   

    add_item(({"tongs"}),
    "Several pairs of tongs, long and short handled, lean against the"
    +" wall near the forge and anvil.\n"); 

    add_item(({"hammer", "hammers"}),
    "There are hammers of various sizes and designs about the forge."
    +" There are shot-peen, wooden mallets and leather finish-friendly"
    +" shaping tools.\n");  

    add_item(({"pliers"}),
    "Wire cutting, needle nosed, and blunt channel locks help the smith"
    +" employ his craft.\n");          

    add_item(({"anvil"}),
        "A massive iron anvil is the working surface of choice for the"
        +" blacksmith.\n");   

    add_item(({"barrel", "barrels"}),
    "A barrel of water and a barrel of oil serve as cooling agents for"
    +" tempering the metals out of the forge.\n");                

    add_item(({"door"}),
        "The door to the west leads back to the street.\n"); 

/*
*    Sound effects
*/        

    add_room_tell("Waves of heat roll from the forge.");  
    add_room_tell("Sparks fly from the coal in the forge."); 
    add_room_tell("A refreshing breeze comes in through the windo.");     

/*
*    Bring on the blacksmith
*/    
              
        
    add_npc(NPC_DIR + "blacksmith", 1);

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road15", "west");

}


void
reset_faerun_room()
{
    set_searched(0);
}