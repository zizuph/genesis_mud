 
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


//inherit "/d/Shire/smiths/forge/base_raw_shop";
//inherit "/sys/global/money";
inherit /d/Shire/smiths/forge/base_merchant_rm";

#include "../local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

//#define STORE_ROOM     (FORGE_STORE)


void create_room() 
{
    ::create_room();
    set_short("Merchant's Hall in Imladris");
    set_long("This is a large room where various items are " +
        "available for sale to skilled smiths. Large shelves " +
        "line the walls with wood, leathers and iron bars for " +
        "sale. A large box sits in one corner of the room.\n");
   add_item(({"box","big box","scrap box"}),
       "This box is filled with broken rusted items to be used " +
       "as raw materials later.\n");
//   set_store_room("/d/Shire/rivendell/room/valley/forge/new_raw_stor");

//   add_exit(FORGE_DIR +"new_raw_stor","up","@@test_storage@@");
    if (!objectp(FORGE_MERCHANT_NPC)) 
        room_add_object(FORGE_MERCHANT_NPC, 1, QCTNAME(TO)+" arrives.\n");
}