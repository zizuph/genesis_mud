/*
 * MERCHANT NPC for Smiths Guild.
 *
 * This file is an example/template to create a working
 * npc for the shop that sells materials in the forge.
 *
 * This file is may be customized by changing the respective
 * FORGE_MERCHANT values in forge.h instead of in this file.
 *
 * This npc is called by the Raw Shop.
 *
 * -- Finwe, January 2001
 */

/* 
 * Start of required inherited and included files.
 * DO NOT REMOVE OR ALTER THESE FILES.
 */
inherit "/sys/global/money";
inherit "/std/monster";
inherit "/d/Shire/smiths/forge/base_forge_mer";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
// End of required files

/*
 * Insert domain specific inherited and inlcuded files here.
 */

 // end of domain files


void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({FORGE_MERCHANT_NAME}));
   set_title(FORGE_MERCHANT_TITLE);
   set_race_name(FORGE_MERCHANT_RACE);
   set_adj(({FORGE_MERCHANT_ADJ1,FORGE_MERCHANT_ADJ2}));

// change the long description here if needed.
   set_long("This is a merchant for the Smiths. He is " +
       "responsible for selling items necessary to forge " +
       "weapons and armours. His weather-worn featurs show " +
       "that he has probably been doing this for some time as " +
       "all the items here are hard to get and require time.\n");

}

