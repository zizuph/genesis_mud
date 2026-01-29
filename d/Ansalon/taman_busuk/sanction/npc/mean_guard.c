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

int
special_attack(object ob)
{
    if(!query_prop("_dragonarmy_dattack_prop"))
	command("slash");
    return 0;
}


void relate_msg()
{
     tell_room(environment(this_object()), QCTNAME(this_object())+
               " gets aid from his fellow guards, who attacks you.\n");
}

public void attacked_by(object ob)
{
   object* guards;
   ::attacked_by(ob);

   ob->add_prop("_i_attacked_bda_guild_home", 1);
   
   guards = filter(all_inventory(environment(this_object())), &->id("_da_special_guard"));

   if(sizeof(guards))
   {
     set_alarm(0.0, 0.0, &relate_msg());

     for(int i = 0; i<sizeof(guards); i++)
     {
       guards[i]->attack_object(ob);
     }
   }
}

public void
attack_object(object ob)
{
   object* guards;
   ::attack_object(ob);   
   
   ob->add_prop("_i_attacked_bda_guild_home", 1);
   
   guards = filter(all_inventory(environment(this_object())), &->id("_da_special_guard"));

   if(sizeof(guards))
   {
     set_alarm(0.0, 0.0, &relate_msg());

     for(int i = 0; i<sizeof(guards); i++)
     {
       guards[i]->attack_object(ob);
     }
   }
}
