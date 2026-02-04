/* This comment tells emacs to use c++-mode  -*- C++ -*- */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;
 
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#define KILL_LOG "/d/Terel/log/red_kills"
#define DRAGONFIRE "_terel_dragonfire"

#define A_BITE    (0)
#define A_LCLAW   (1)
#define A_RCLAW   (2)

#define H_HEAD    (0)
#define H_BODY    (1)

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name(({"dragon"}));
    set_short("huge red dragon");
    set_long("A huge red dragon.\n" +
	     "You can feel the heat from its sulphur-breath.\n"+
	     "The dragon faces you with a calm expression, knowing it " +
	     "has fought many battles against small creatures like you, " +
	     "and won.\n");
    
    set_adj(({"enormous", "red", "vicious"}));
    set_race_name("dragon");
    set_alignment(-400 - random(1200));
    set_gender(NEUTER);    

    set_hitloc_unarmed(H_HEAD, 100, 25, "head");
    set_hitloc_unarmed(H_BODY, 100, 75, "body");

    set_stats(({220, 300, 220, 180, 180, 180}));

    set_attack_unarmed(A_BITE, 80, 80, W_IMPALE, 10, "bite");
    set_attack_unarmed(A_LCLAW, 50, 50, W_SLASH,  40, "left claw");
    set_attack_unarmed(A_RCLAW, 50, 50, W_SLASH,  50, "right claw");

    AGGRESSIVE;
    SET_MAX_HP;
    BRAVE;
    set_skill(SS_AWARENESS,100);
    set_skill(SS_PARRY, 100);

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON,100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_DEATH,50);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_AIR, 50);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_MAGIC, 50);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_FIRE, 100);    
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop("_ranger_i_not_brawl", 1);
    add_prop("_union_i_adjust_diginity", 85);
    if(random(9) > 2)
        add_leftover(ORC_CAVE_DIR +"weapon/dtooth","tooth",1,0,1,1);
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, flame_room, *all;
    int hurt, i;
    int fire_resist;
    flame_room=find_object (ORC_CAVE_DIR+"cave17");

    me = TO;
    all = query_my_enemies();

    if(random(9) < 2) {

        flame_room->bake(me);

        for (i=0; i<sizeof(all); i++) {
            hurt = F_PENMOD(200, 150 + random(50));
            hurt -= hurt * all[i]->query_magic_res(MAGIC_I_RES_FIRE) / 100;
            if(all[i]->query_prop(DRAGONFIRE))
                hurt = 0;
     
            hitresult = all[i]->hit_me(hurt, MAGIC_DT, me, -1);

            how = "misses";
            if (hitresult[0] > 0)
                how = "singes";
            if (hitresult[0] > 20)
                how = "burns";
            if (hitresult[0] > 50)
                how = "ignites";
            if (hitresult[0] > 100)
                how = "incinerates";
            all[i]->catch_msg("The huge red dragon breathess fire throughout the cave!\n");
            all[i]->catch_msg("The fiery breath " + how + " you.\n");
            if(all[i]->query_hp() <= 0)
                all[i]->do_die(me);
            }
     return 1;
    }

    return 0;
}

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) {
       if (enemies[i] != killer)
           str += ", " + enemies[i]->query_name() +
           "[" + enemies[i]->query_average_stat() + "]";
      }
    write_file(KILL_LOG, str + " (" + ctime(time()) + ")\n");
    
    ::do_die(killer);
}

