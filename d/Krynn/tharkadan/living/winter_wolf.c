#pragma save_binary 
#pragma strict_types 

inherit "/d/Krynn/std/monster"; 
inherit "/std/combat/unarmed"; 

inherit "/std/act/domove"; 
#include <wa_types.h> 
#include <macros.h> 
#include <stdproperties.h> 
#include <ss_types.h> 
#include "/d/Krynn/common/defs.h"
#include "../local.h" 

#define A_BITE 0 
#define A_LPAW 1 
#define A_RPAW 2 

#define H_HEAD 0 
#define H_BODY 1 
#define H_LEGS 2 

int forced_attacktype = 0;

void 
create_krynn_monster() 
{ 
    set_name("wolf");
    set_pname("wolves");
    set_race_name("wolf");
    set_adj("winter"); 
    set_short("winter wolf");
    set_pshort("winter wolves"); 
    set_long("Before you stands a snow-white wolf of massive " +
       "proportions. Eight feet in length and standing almost five feet " +
       "tall at the shoulder, it rivals some warhorses in size. More " +
       "menacing than its size though is its intelligent pale blue eyes " +
       "that look upon you with an evil malevolence.\n"); 

    add_prop(CONT_I_WEIGHT, 40000); 
    add_prop(CONT_I_VOLUME, 37000); 
    add_prop(OBJ_I_NO_INS, 1); 
    set_gender(G_NEUTER); 
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 79);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_HIDE, 100);
    set_skill(SS_SNEAK, 100);
    set_alignment(-700);
    set_knight_prestige(80);
    add_prop(OBJ_I_RES_COLD, 80);
    add_prop(OBJ_I_RES_FIRE, -20);

    if(random(5) == 0)
      add_leftover(ARMOUR + "pelt.c", "pelt", 1, 0, 0, 1);
    else 
      add_leftover(ARMOUR + "pelt_ripped.c", "pelt", 1, 0, 0, 1);

    /* Wep_type,      to_hit,   pen,  Dam_type,   %usage,   attack_desc */ 
    set_attack_unarmed(A_BITE,   40, 40, W_IMPALE, 70, "sharp fangs"); 
    set_attack_unarmed(A_LPAW,  35,  35, W_SLASH,  15, "left paw"); 
    set_attack_unarmed(A_RPAW,  35,  35, W_SLASH,  15, "right paw"); 

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */ 
    set_hitloc_unarmed(H_HEAD, ({ 40, 44, 46,   5 }), 25, "head"); 
    set_hitloc_unarmed(H_BODY, ({ 35, 38, 46,   0 }), 45, "body"); 
    set_hitloc_unarmed(H_LEGS, ({ 35, 38, 46,   0 }), 30, "legs"); 

    set_stats(({120,145,130,100,100,150})); 

    set_act_time(10); 
    add_act("growl"); 
    add_act("hide");
    add_act("emote raises its head and howls eerily!"); 
    add_act("emote snarls aggressively."); 
} 

int
special_attack(object enemy)
{
    int i, attacktype;
    mixed* hitresult;
    object me, *ob;

    int penet = 300 + random(150);

    string breath_weapon = "a cone of frost bursts from " + HIS(TO) + 
        " mouth!\n";
    string * how, how_str;
    string res_prop = MAGIC_I_RES_COLD;

    how = ({ "not harmed", "slightly chilled", "chilled", "chilled to " +
        "the bone", "frozen", "frozen solid" }); 

    me = this_object();

    if (forced_attacktype == 0)   /* no forced special attack this turn */
        attacktype = random(5);
    else
        attacktype = forced_attacktype;

    if (attacktype == 0 || forced_attacktype == 1)
    {
      if (forced_attacktype == 0)
      {
        /* Wolf inhales air, forced next attack to be an ice breath */
        tell_room(E(TO), QCTNAME(TO)+" growls menacingly and breathes " +
            "in deeply...\n", TO, TO);
        forced_attacktype = 1;
        return 1;
      }

      tell_room(E(TO), "As "+QTNAME(TO)+" opens its jaws, " +
           breath_weapon, TO, TO);

    ob = query_enemy(-1);
    for (i = 0; i < sizeof(ob); i++) 
    {
        if(E(ob[i]) != E(TO))
        continue;

        if (ob[i]->query_not_attack_me(me, -1))
        {
            continue; // attack was blocked, move onto the next attack
        }
        
        penet -= penet * ob[i]->query_magic_res(res_prop) /100;
        hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

        how_str = how[0];

        if (hitresult[0] > 0)
            how_str = how[1];
        if (hitresult[0] > 10)
            how_str = how[2];
        if (hitresult[0] > 20)
            how_str = how[3];
        if (hitresult[0] > 40)
            how_str = how[4];
        if (hitresult[0] > 60)
            how_str = how[5];

        ob[i]->catch_msg("You are "+how_str+" by the winter wolf's " +
            "frosty breath!\n");
        tell_watcher(QCTNAME(ob[i]) + " is "+how_str+" by the winter " +
          "wolf's frosty breath!\n", ob[i]);

        if (ob[i]->query_hp() <= 0)
        ob[i]->do_die(me);
    }

    forced_attacktype = 0;
    return 1;

    }

    return 0;
}

public void
check_aggro(object player)
{
    if(TO->query_attack())
      return;

    if(player->query_average_stat() < 150)
    {
      command("growl " + player->query_real_name());
      command("kill " + player->query_real_name());
    }
}

void 
init_living() 
{
    if(CAN_SEE(TO, TP))
      set_alarm(2.5, 0.0, &check_aggro(TP)); 

    ::init_living(); 
}
