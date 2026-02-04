

#include "../guild.h"

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

inherit "/std/monster";

int Update_alarm_id;
int num_hits;
int total_damage;

public void arm_me()
{
    clone_object(OBJ_DIR+"test_weapon")->move(TO);
    command("wield all");
}

public void create_monster()
{
    ::create_monster();
    
    add_adj("test");
    set_race_name("human");
    set_long("This is a test NPC for testing abilities.\n");
    
    default_config_npc(150);
    set_base_stat(SS_OCCUP,200);
    
    set_all_hitloc_unarmed(40);
    
    set_skill(VAMP_SKILL_BITE,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    //set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    
    object shadow=clone_object(SHADOW_DIR+"occ_shadow");
    if (shadow)
    {
        int result=shadow->shadow_me(TO, "occupational", OCC_GUILD_STYLE, 
        OCC_GUILD_NAME, "");
        TO->add_blood(TO->query_max_blood()*100/100);
    }
    set_alarm(0.1,0.0,arm_me);
    
}


public void add_fatigue(int value)
{
    if (value>0)
    {
        ::add_fatigue(value);
    }
}

public void add_panic(int value)
{
    return;
}

public void show_update()
{
  Update_alarm_id=0;
  if (!num_hits)
  {
    return;
  }
  command("say DPM: "+(total_damage)+", DPH: "+(total_damage/num_hits));
  if (num_hits>0)
    {
        Update_alarm_id=set_alarm(60.0,0.0,show_update);
        
    }
  total_damage=0;
  num_hits=0;  
}

void heal_hp(int hp)
{
    if (hp>=0)
    {
        ::heal_hp(hp);
        return;
    }
    
    total_damage-=hp;
    num_hits++;
    if (!Update_alarm_id)
    {
        Update_alarm_id=set_alarm(60.0,0.0,show_update);
    }
}
