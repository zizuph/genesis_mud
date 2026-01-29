 
/*
 * Tanner's shop
 finwe
 Smith's guild
 * By Finwe January 2001
 * 
 * This file calls the forge in the smiths guild. It also alters
 * some of the routines to make them more 'elvish' and fitting for
 * the valley.
 */


inherit "/d/Shire/smiths/forge/base_raw_stor.c";
#include "../local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

void create_room() 
{
    ::create_room();
    set_short("Raw material storage room");
    set_long("This is the storage room where items to be sold in the raw"+
     " shop are stored. Boxes with all kinds of different items are placed"+
     " all over the room.\n");

   add_item(({"box","big box","scrap box"}),"This box is filled with broken"+
      " rusted items to be used as raw materials later.\n");

   add_exit(FORGE_DIR +"new_raw_shop","down");

}

