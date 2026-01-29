/* Skeletal warrior by percy*/

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/solace/graves/local.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"

inherit M_FILE

void
create_krynn_monster()
{
    int i;
    
    set_name("Skeleton");
    set_short("skeleton");
    add_name("thing");
    set_race_name("skeleton");
    set_long("This poor creature has been refused rest even in death.\n"
	     + "It now bears a hatred for all living things......\n");
    set_adj("undead");
    
    for (i = 0; i < 6; i++)
      set_base_stat(i, 10 + random(6));
    set_skill(SS_DEFENCE, random(5) + 6);
    set_skill(SS_WEP_SWORD, 45);
    
    set_all_attack_unarmed(6, 6);
    set_all_hitloc_unarmed(6);
    set_alignment(-200);
    set_knight_prestige(150);
    set_monster_home(BASE+"cellw");
    set_restrain_path(BASE+"cellw");
    add_act("emote rattles noisily.");
    add_act("glare");
    set_act_time(10);
    set_aggressive(1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_UNDEAD, 10);
    add_prop(LIVE_I_NO_CORPSE, 1);
    
    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    seteuid(geteuid(this_object()));
    
    clone_object(OBJ + "skel_arm")->move(TO);
    clone_object(OBJ + "skel_wep")->move(TO);
    
    command("wear armour");
    command("wield weapon");
}

void
do_die(object killer)
{
    object ob = clone_object("/std/leftover");
    ob->leftover_init("bone","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("skull","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("bone","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","human");
    ob->move(E(TO));
    ::do_die(killer);
}
