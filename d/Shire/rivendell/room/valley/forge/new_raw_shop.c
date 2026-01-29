 
/*
 * Raw Material Shop
 *
 * This rooms sells the materials needed to forge items: 
 * iron bars, wood, and leathers.
 *
 * To personalize it, simply change the room descriptions 
 * and exits. Note the VBFC on the exit to the store room. 
 * This must be retained otherwise the store room will be 
 * opened to everyone.
 * 
 * This room clones the npc defined in FORGE_TANNER.
 */


inherit "/d/Shire/smiths/forge/base_raw_shop";
inherit "/sys/global/money";

#include "../local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

#define STORE_ROOM     (FORGE_STORE)


void create_room() 
{
    ::create_room();
    set_short("Raw material shop in Imladris");
    set_long("This is a large room where various items are " +
        "available for sale to skilled smiths. Large shelves " +
        "line the walls with wood, leathers and iron bars for " +
        "sale. A large box sits in one corner of the room.\n");
   add_item(({"box","big box","scrap box"}),
       "This box is filled with broken rusted items to be used " +
       "as raw materials later.\n");
//   set_store_room("/d/Shire/rivendell/room/valley/forge/new_raw_stor");

   add_exit(FORGE_DIR +"new_raw_stor","up","@@test_storage@@");
   add_exit(VALLEY_DIR +"forge_hall", "south",0);
}
