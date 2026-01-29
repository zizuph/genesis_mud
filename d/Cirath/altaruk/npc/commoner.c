/*
 * ghost.c
 * By Skippern
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";   /* for humanoid monsters */

#include "/w/skippern/projects/erech.h"     /* for Erech definitions */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

string* Ghost_adj1 = ({ "transparent", "shadowy", "floating", "shady",
			  "scaring", "foul-looking" });
string* Ghost_adj2 = ({ "headless", "one-eyed", "hair-less", "tooth-less",
			  "young", "adolecent", "adult", "scared",
			  "tired-looking" });

#define G_GENDER random(3)
#define G_ALIGN 400 + random(600)
#define MY_HEIGHT 150 + random(31)
#define MY_WEIGHT 200 + random(1200)
#define MY_VOLUME 60000 + random(30000) + random(30000) + random(40000)

#define G_STR     5 + random(25)
#define G_DEX     150 + random(100)
#define G_CON     20 + random(100)
#define G_WIS     50 + random(200)
#define G_INT     50 + random(200)
#define G_DIS     180 + random(120)

/* Prototypes */
void             create_monster();

/*
 * Function name:    create_monster()
 * Definition   :    Creates the monster
 */
void
create_monster()
{
  set_race_name("ghost");
  set_long("It is realy not much to look at, it is basically a shadow " +
	   "beond horror.\n");
  set_adj(Ghost_adj1);
  add_adj(Ghost_adj2);
 
  set_gender(G_GENDER);
  set_alignment(G_ALIGN);

  add_prop(CONT_I_HEIGHT, MY_HEIGHT);
  add_prop(CONT_I_WEIGHT, MY_WEIGHT);
  add_prop(CONT_I_VOLUME, MY_VOLUME);
  add_prop(LIVE_I_UNDEAD, 1);
  add_prop(LIVE_I_SEE_DARK, 100);
  add_prop(LIVE_I_NO_CORPSE, 1);
  add_prop(LIVE_I_MAX_DRINK, 1);
  add_prop(LIVE_I_MAX_EAT, 1);
  add_prop(LIVE_I_NO_FOOTPRINTS, 1);

  set_base_stat(SS_STR, G_STR); 
  set_base_stat(SS_DEX, G_DEX); 
  set_base_stat(SS_CON, G_CON);
  set_base_stat(SS_WIS, G_WIS);
  set_base_stat(SS_INT, G_INT);
  set_base_stat(SS_DIS, G_DIS); 
}
