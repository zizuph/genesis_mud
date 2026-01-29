/* The Dragonarmy Members kept complaining about
   not having separate racks for BDA and RDA for
   High Officers, so I created two rooms for that.
   They had a shared room before.
   This npc guards those rooms to keep the two
   armies from enter these rooms.
   If someone should decide to be an ass and attack
   the guard to raid the others rack, he might regret
   it. This guard will be blocking, and he will
   have a big amount of extra hitpoints.
   -- Navarre April 2007.
*/


#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>

#define ONE_OF(x)     ((x)[random(sizeof(x))])

inherit AM_FILE

void arm_me();

string* adjs1 = ({"strong", "smelly", "tall", "small",
                  "black-haired", "well-trained",
                  "grinning"});

void
create_krynn_monster()
{
    object sh;

    setuid();
    seteuid(getuid());

    set_race_name("goblin");
    set_adj(({ONE_OF(adjs1),"green"}));
    set_name("guard");
    add_name("_nav_bda_mean_guard");
    set_gender(0);

    set_stats(({160+random(50),160+random(50),160+random(50),160+random(50),160+random(50),160+random(50)}));
    set_base_stat(SS_OCCUP, 300);

    set_skill(SS_AWARENESS, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DRAGONARMY_ATTACK, 100);
    set_alignment(-1200);
    set_all_hitloc_unarmed(60);

    add_prop(CONT_I_HEIGHT, 185);

    add_prop(LIVE_I_QUICKNESS, 200);
    add_prop("_ranger_m_not_disarm",1);
    add_prop(NPC_I_NO_FEAR, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 100);
    add_prop(NPC_I_NO_UNARMED, 100);
    
    set_cact_time(4);
    add_cact("emote explains: That was your last mistake.");

    sh = clone_object(BLUE_SHADOW);
    if(sh->shadow_me(TO, "occupational", GUILD_STYLE, GUILD_NAME) != 1)
    {
	"secure/master"->do_debug("destroy",sh);
    }
    TO->set_promotion_level(3);
    add_cmdsoul(DRAGONARMY_BLUE_SOUL);
    load_command_souls();
    set_alarm(0.0, 0.0, &arm_me());
}

void
arm_me()
{
    object uniform;
 
    clone_object(DRAGONARMY_OCC_EMBLEM)->move(TO, 1);

    clone_object(SOBJ + "weapon/scimitar")->move(TO, 1);
    clone_object(SOBJ + "weapon/sabre")->move(TO, 1);
    clone_object("/d/Krynn/solamn/splains/obj/bdragonarm")->move(TO, 1);
    clone_object("/d/Krynn/solamn/splains/obj/bdragonhelm")->move(TO, 1);
    clone_object("/d/Krynn/solamn/splains/obj/bshinguard")->move(TO, 1);
    uniform = clone_object("/d/Ansalon/guild/dragonarmy/obj/uniform");
    uniform->set_colour("blue");
    uniform->set_dalevel(2);
    uniform->move(TO, 1);
    command("wear all");
    command("wield all");
}

public
int
query_max_hp()
{
    return 15000;
}

int
special_attack(object ob)
{
    if(!query_prop("_dragonarmy_dattack_prop"))
	command("slash");
    return 0;
}


public void attacked_by(object ob)
{
   ::attacked_by(ob);
   ob->add_prop("_don't_let_this_idiot_leave", 1);
}

public void
attack_object(object ob)
{
    ::attack_object(ob);    
    ob->add_prop("_don't_let_this_idiot_leave", 1);
}
