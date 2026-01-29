/*
 * Tanner NPC for Smiths Guild.
 * This file is an example/template to create a working
 * npc for the shop that sells materials in the forge.
 *
 * This file is may be customized by changing the respective
 * FORGE_NPC values in forge.h instead of in this file.
 *
 * -- Finwe, January 2001
 */

/* 
 * Start of required inherited and included files.
 * DO NOT REMOVE OR ALTER THESE FILES.
 */
inherit "/sys/global/money";
inherit "/std/monster";
inherit "/d/Shire/smiths/forge/base_forge_tan";

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

   set_name(({FORGE_TANNER_NAME}));
   set_title(FORGE_TANNER_TITLE);
   set_race_name(FORGE_TANNER_RACE);
   set_adj(({FORGE_TANNER_ADJ1,FORGE_TANNER_ADJ2}));

// change the long description here if needed.
   set_long("This is a skilled seller for the Smiths. He is " +
       "responsible for selling items necessary to forge " +
       "weapons and armours. His weather-worn featurs show " +
       "that he has probably been doing this for some time as " +
       "all the items here are hard to get and require time. To " +
       "see what he will sell, you may <list> items here.\n");

}

