#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <language.h>
#include <std.h>

#define HAND  LOD_DIR + "obj/thand"

public void
create_monster()
{
    ::create_monster();
    
    set_name("troj");
    set_race_name("human");
    set_adj(({"dark", "old"}));
    set_long("A dark and old human. He must have " +
             "been here since the last of the Avenchirs captured " +
             "him. You wonder what his crime was.\n");

    default_config_npc(60);

    set_skill(SS_DEFENCE, 55);
    set_skill(SS_PARRY, 55);
    set_skill(SS_AWARENESS, 55);
    set_skill(SS_WEP_CLUB, 30);
    set_skill(SS_WEP_AXE, 30);
    set_skill(SS_PICK_POCKET, 60);
    set_hp(9000);
    set_mana(9000);
    set_aggressive(0);

    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(CONT_I_WEIGHT, 78000);
    add_prop(CONT_I_VOLUME, 78000);
    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_MAX_WEIGHT, 143000);
    add_prop(CONT_I_MAX_VOLUME, 123000);
    
    set_all_attack_unarmed(25, 30);
    set_all_hitloc_unarmed(15);
    
    set_chat_time(5);
    add_chat("I'm innocent!");
    add_chat("They called me a thief and a liar.");
    add_chat("I didn't even get a fair trial. That damned Avenchir just " +
             "locked me in here.");
    add_chat("I was just a boy then.");
    add_chat("I survived by eating rats.");
    
    set_act_time(11);
    add_act("sweat");
    add_act("whistle innocently");
    add_act("@@steal");
}

public object
find_victim()
{
    object *all;
        
    if (!ETO)
        return 0;
        
    all = filter(all_inventory(ETO) - ({ TO }), living);
    
    if (!sizeof(all))
        return 0;
    
    return all[random(sizeof(all))];
}

public object
find_loot(mixed where)
{
    object *obs, victim;
    
    if (!where)
        return 0;

    if (stringp(where))
        victim = find_object(where);
    else if (objectp(where))
        victim = where;
    else
        return 0;
    
    obs = all_inventory(victim);
    
    obs -= filter(obs, &->query_no_show());
    obs -= filter(obs, &->query_prop(OBJ_M_NO_STEAL));
    obs -= filter(obs, &->query_prop(OBJ_M_NO_GET));
    obs -= filter(obs, &->query_prop(OBJ_M_NO_GIVE));
    obs -= filter(obs, &->query_prop(OBJ_M_NO_DROP));
    obs -= filter(obs, &->query_worn());
    obs -= filter(obs, &->query_wielded());
    obs -= filter(obs, &operator(<)(,10) @ &->query_prop(OBJ_I_VALUE));
    
    if (!sizeof(obs))
        return 0;
    
    return obs[random(sizeof(obs))];
}

public string
steal()
{
    int suc;
    object ob, victim = find_victim();
    
    if (!victim || !CAN_SEE(TO, victim) || !CAN_SEE_IN_ROOM(TO))
        return "sweat";
    
    ob = find_loot(victim);
    
    if (!ob)
        return "sweat";
        
    suc = random(query_skill(SS_PICK_POCKET)) -
          (2*victim->query_skill(SS_AWARENESS))/3 -
          random(victim->query_skill(SS_AWARENESS)/3);
          
    if (SECURITY->query_wiz_level(victim->query_real_name()))
        suc = -100;
          
    if (suc > 20)
    {
        victim->catch_msg("Something happened to you.\n");
        victim->command("$confused");
        ob->move(TO, 1);
        return "whistle innocently";
    }
    else if (suc > 0)
    {
        victim->catch_msg(QCTNAME(TO) + " stole " +
                          LANG_ADDART(ob->short()) +
                          " from you!\n");
        tell_room(ETO, QCTNAME(TO) + " did something to " + QTNAME(victim) +
                       ".\n", ({TO, victim}));
        ob->move(TO, 1);
        return "emote tries to look innocent.";
    }
    else
    {
        victim->catch_msg(QCTNAME(TO) + " tried to steal " +
                          LANG_ADDART(ob->short()) +
                          " from you! Luckily, he wasn't quick enough.\n");
        tell_room(ETO, QCTNAME(TO) + " tried to steal something from " +
                  QTNAME(victim) + ".\n", ({TO, victim}));
        return "swear";
    }
}

public void
do_die(object killer)
{
    if (query_hp() > 0)
        return;
        
    command("emote looks confused as his hand fall off.");
    
    seteuid(getuid());
    clone_object(HAND)->move(ETO);
    
    ::do_die(killer);
}
