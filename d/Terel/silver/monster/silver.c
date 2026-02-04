/* File         : /d/Terel/silver_new/monster/silver.c
 * Creator      : Pasqua
 * Date         : April 2006         
 * Purpose      : Silverback Gorilla
 * Related Files: 
 * Comments     : The White Wolf Boosted! Have used the white wolf's hunt code.
 * Modifications: 
 */

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#define HUNT_SHADOW "/d/Terel/std/follow.c"
#define KILL_LOG SILVER_DIR+"log/silverback_kills"


static object prey = 0;
static int    shadowed = 0;
int           hunt_alarm = 0;
void start_hunting();

//#include "../include/creature_base.h"
#include <wa_types.h>
#include <ss_types.h>
#include <options.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>  

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name("silverback");
	add_name("gorilla");
    set_short("enormous silverback gorilla");
    set_long("This enormous silverback gorilla seems to be the father of the gorilla " +
             "family in the forest. He seems quite powerful and extremly aggressive, " +
             "it wouldn't be wise to start a fight with him at all. The big difference " +
             "between this gorilla and the other is the destinctive patch of silver hair " +
		     "on his back. This monstrous gorilla got a massive set of canine teeth and " +
		     "some powerful jaw muscles to back them up.\n");
    set_adj(({"enormous","silverback"}));
    set_race_name("gorilla");
    set_stats(({130 + random(40), 150 + random(30), 160 + random(40), 120 + random(10), 120 + random(10), 160 + random(30)}));
    PASSIVE;
	set_exp_factor(150);
    set_gender(MALE);
    set_skill(SS_UNARM_COMBAT, 80 + random(20));
    set_skill(SS_DEFENCE, 90 + random(10));
    add_prop(OBJ_I_WEIGHT, 6000000);
    add_prop(OBJ_I_VOLUME, 7000000);
    add_prop(CONT_I_MAX_WEIGHT, 10000000);
    add_prop(CONT_I_MAX_VOLUME, 10000000);
    BRAVE;
    SET_MAX_HP;
	add_leftover(ARMOUR + "silverback","pelt", 1, "", 0,
1);

}




#define A_BITE  0
#define A_LFIST 1
#define A_RFIST  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(55, 60, W_SLASH,    30, A_BITE);
    add_attack(50, 55, W_BLUDGEON, 35, A_RFIST);
    add_attack(50, 55, W_BLUDGEON, 35, A_LFIST);

    add_hitloc( ({ 30, 30, 30 }), 15, "head", H_HEAD);
    add_hitloc( ({ 30, 30, 30 }), 60, "body", H_BODY);
    add_hitloc( ({ 30, 30, 30 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
     case A_BITE: return "vicious canine bite";
     case A_RFIST: return "right fist";
     case A_LFIST: return "left fist";
    }
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int hurt;
    int fire_resist;

    me = TO;
    
    if(random(10) < 4) {

        hurt = F_PENMOD(100, 100 + random(100));
        
        hitresult = enemy->hit_me(hurt, MAGIC_DT, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "hurt";
        if (hitresult[0] > 50)
            how = "injured";
        if (hitresult[0] > 100)
            how = "crushed";
        if (hitresult[0] > 200)
            how = "pulverized";
            
        tell_watcher(QCTNAME(me) + " starts to beats himself in the chest and scream loudly " +
			 "and charges at " + QTNAME(enemy) + ".\n", enemy); 
        enemy->catch_msg(QCTNAME(me) + " starts to beat himself in the chest and scream and charges at you!\n");
        enemy->catch_msg("You feel " + how + " by the charge.\n");

        start_hunting();
      
        return 1;
    }

    return 0;
}

//  Here are the hunting functions :)
public void
attack_object(object ob)
{
    if (!prey && !shadowed && !hunt_alarm)
        hunt_alarm = set_alarm(itof(10 + random(8)),0.0,&start_hunting());
    ::attack_object(ob);
}

public void
attacked_by(object ob)
{
    if (!prey && !shadowed && !hunt_alarm)
        hunt_alarm = set_alarm(itof(8 + random(8)),0.0,&start_hunting());
    ::attacked_by(ob);
}

void
start_hunting()
{
    object *enemies;

    if (hunt_alarm)
    {
        remove_alarm(hunt_alarm);
        hunt_alarm = 0;
    }
    //  Can't hunt if we aren't killing somene ;)
    if (!objectp(query_attack()))

        return;
    //  We already got our prey in our hunting sights
    if (objectp(prey) && shadowed)
        return;
    enemies = query_enemy(-1) & all_inventory(environment());
    //  Make sure there are no npcs in the array.
    enemies = FILTER_PLAYERS(enemies);
    if (!sizeof(enemies))
        return;
    prey = enemies[random(sizeof(enemies))];
    setuid(); seteuid(getuid());
    clone_object(HUNT_SHADOW)->follow(prey,TO);
    shadowed = 1;
}

//  Called from the follow shadow
void
notify_stopped_hunt()
{
    prey = 0;
    shadowed = 0;
}

string
query_hunting()
{
    return prey->query_real_name();
}

int
query_shadowed()
{
    return shadowed;
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
