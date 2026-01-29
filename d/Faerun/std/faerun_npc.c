/*
 *  faerun/std/faerun_npc.c
 *
 *  General file for all the Faerun NPC's
 *
 *  Created by Wully, 12-2-2004
 */

#include "/d/Faerun/defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit "/d/Faerun/std/team_code";
inherit "/d/Faerun/lib/assist_friend";

int no_unarmed_combat = 0;
static object gWep_func, gArm_func;
static int gWep_patch = 0;

/*
 * Function name: create_faerun_npc
 * Description  : Contruct our monster
 */
void create_faerun_npc()
{
}

/*
 * Function name: create_monster
 * Description  : Construct our standard humanoid like creature
 */
void create_monster()
{
    // Construct our monster
    create_faerun_npc();
}

/*
 * Function name: set_no_unarmed_combat
 * Description  : Turn unarmed combat off
 * Arguments    : 0 for off, 1 for on
 */
varargs void set_no_unarmed_combat(int setting = 1)
{
    no_unarmed_combat = 1;
}

/*
 * Function name: query_no_unarmed_combat
 * Description  : What's our current setting
 */
int query_no_unarmed_combat()
{
    return no_unarmed_combat;
}

/*
 * Function name: query_option
 * Description  : Return the option for unarmed combat
 */
int query_option(int opt)
{
    // We never use unarmed 
    if((opt == OPT_UNARMED_OFF) && no_unarmed_combat)
        return 1;

    return ::query_option(opt);
}

/*  Gives prestige to Knights who kill monsters including this
 *  file.  All npcs in Faerun should include this file, or have
 *  the code in it somewhere.
 */
query_knight_prestige()
{
  int i;
  if(this_object()->query_alignment() <= 0)
  {
    i = this_object()->query_average_stat();
    i = i * i / 10;
    return i;
  }
  else
  {
    i = this_object()->query_average_stat();
    i = -(i * 2 / 100);
    return i;
  }
}
