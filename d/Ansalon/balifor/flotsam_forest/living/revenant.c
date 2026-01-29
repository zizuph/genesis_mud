/* Undead wraith by percy*/

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define WEP WEAPON + "rev_sword"

inherit AM_FILE
inherit "/std/act/attack.c";
inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */


void
create_krynn_monster()
{
    int i;

    set_name("revenant");
    set_short("undead revenant");
    set_pshort("undead revenants");
    set_race_name("wraith");
    set_long("This undead creature is a revenant. It is doomed to " +
      "eternally haunt the land or area it failed to protect when " +
      "it was alive.\n");
    set_adj("undead");

    for (i = 0; i < 6; i++)
	set_stats(({60,60,60,60,60,100}));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_AWARENESS, 40);

    set_knight_prestige(20);

    set_alignment(-10);



    set_aggressive(1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 40);
    add_prop(LIVE_I_SEE_DARK, 1000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 567900);
    add_prop(CONT_I_WEIGHT, 578400);
    add_prop(LIVE_I_NO_BODY, 1);
}

tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->query_see_blood())
	    ob[i]->catch_msg(str);
}



void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP)->move(TO,1);
    command("wield all");
}



