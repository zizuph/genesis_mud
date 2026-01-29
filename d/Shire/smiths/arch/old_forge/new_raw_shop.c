 
/*
 * Tanner's shop Smith's guild
 * By Finwe January 2001
 * 
 * This file calls the forge in the smiths guild. It also alters
 * some of the routines to make them more 'elvish' and fitting for
 * the valley.
 */


inherit "/d/Shire/smiths/forge/base_raw_shop";
inherit "/lib/shop";
inherit "/sys/global/money";

#include "../local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

void create_room() 
{
    ::create_room();
    set_short("Raw material shop in Imladris");
    set_long("This is a large room where various items are " +
        "available for sale to skilled smiths. Large shelves " +
        "line the walls with wood, leathers and iron bars for " +
        "sale. A large box sits in one corner of the room.\n");
   add_item(({"box","big box","scrap box"}),"This box is filled with broken"+
      " rusted items to be used as raw materials later.\n");

   add_exit(FORGE_DIR +"new_raw_stor","up","@@test_storage@@");
   add_exit(VALLEY_DIR +"forge_hall", "east",0);
}

