#include "/d/Emerald/sys/paths.h"

inherit EMERALD_MONSTER;
inherit "/d/Emerald/telberin/npc/aid_npc";

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <const.h>

static int flag, cling;

void check_enemies();

void create_emerald_monster()
{
    set_name("spirit");
    add_name("_curan_gspirit");
    set_short("guardian spirit");
    set_adj("guardian");
    set_race_name("spirit");
    set_long("A powerful guardian-spirit; it is surrounded by " +
	"a brilliant,\nwhite aura, making him difficult to see clearly.\n");
    set_gender(G_NEUTER);
  
    default_config_mobile((random(5) ? 80 : 150));
  
    set_alignment(900);
  
    set_give_aid(1);
  
    log_my_kills(TELBERIN_DIR + "log/curan_kills.log");
  
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(OBJ_I_RES_DEATH, 90);
    add_prop(OBJ_I_RES_MAGIC, 40);
    add_prop(OBJ_I_RES_POISON, 100);
    add_prop(LIVE_I_SEE_INVIS, 99);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_LIGHT, 2);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop("_ranger_i_no_brawl", 1);
    add_prop("_live_i_no_blood", 1);
  
    set_all_attack_unarmed(50, 50);
    set_all_hitloc_unarmed(50);
  
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
  
    if (random(3) == 2)
    {
        cling = 1;
    }

    set_alarm(60.0, 15.0, check_enemies);
}

int
query_skill(int skill)
{
    if (skill < 30)
    {
        return 80;
    }
}

/* Simply block random attacks */
int
query_not_attack_me(object who, int att_id)
{
    return !random(10);
}

mixed 
query_prop(string prop)
{
    object enemy;
  
    if (prop == LIVE_O_ENEMY_CLING && !::query_prop(LIVE_O_ENEMY_CLING) &&
	cling && (enemy = query_attack()) && 
	(enemy->query_prop(LIVE_I_UNDEAD) || 
	(enemy->query_alignment() < -100)))
    {
        return enemy;
    }
  
    return ::query_prop(prop);
}

void
remove_spirit()
{
    tell_room(environment(), query_nonmet_name() + " fades into " +
	"nothingness.\n");
    remove_object();
}

void
check_enemies()
{
    if (!sizeof(query_enemy(-1) & all_inventory(environment())))
    {
    	if (flag)
    	{
	    remove_spirit();
	    return;
    	}
       
    	flag = 1;
    	return;
    }
  
    flag = 0;
}
