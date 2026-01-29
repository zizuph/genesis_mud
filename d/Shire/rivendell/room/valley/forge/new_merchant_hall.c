 
/*
 * Merchant Room
 *
 * This is where the merchant resides to sell  
 * iron bars, wood, and leathers to smiths.
 *
 * To personalize it, simply change the room descriptions 
 * and exits. Note the VBFC on the exit to the store room. 
 * This must be retained otherwise the store room will be 
 * opened to everyone.
 * 
 * This room clones the npc defined as FORGE_MERCHANT.
 */

inherit "/d/Shire/smiths/forge/base_merchant_hall.c";
inherit "/d/Shire/std/room";

#include "../local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"


void create_room() 
{
    ::create_room();
    set_short("Merchant's Hall in Imladris");
    set_long("This large room is the Merchant's Hall of Imladris. " +
        "Here, players may purchase items necessary for forging " +
        "south of here.\n");
   add_item(({"box","big box","scrap box"}),
       "This box is filled with broken rusted items to be used " +
       "as raw materials later.\n");
       add_exit(VALLEY_DIR +"forge_hall", "south");

 
}