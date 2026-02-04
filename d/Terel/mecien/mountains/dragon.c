inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/lib/unique";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>


#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3
#define A_HORN  4

#define H_HEAD 0
#define H_BODY 1
#define TO this_object()
#define ENV environment

#define EYE_PATH    "/d/Terel/unique/black_dragon_eye"
#define CLONE_LOG    "/d/Terel/log/blackdragon_clones"

create_creature()
{
    set_name("rulucaraz"); 
    set_race_name("dragon");
    set_short("black dragon");
    set_adj("sinister");
    add_adj("black");
    set_long("This ancient dragon is mighty. Its ways are evil and\n" +
	     "it has learned the dark arts.\n");
   
    /*
     *           str, dex, con, int, wis, dis
     */
    set_stats(({ 300, 300, 360, 180, 180, 180}));
   
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_DEFENCE, 100);
    set_alignment(-903);
    set_fatigue(900000);
    set_hp(900000);
    set_mana(900000);

    set_act_time(10);
    add_act("@@puff");
    add_act("@@regen");
    set_cact_time(3);
    add_cact("@@beguile");
    add_cact("@@blast");
    set_attack_unarmed(A_BITE,  150, 120,   W_IMPALE,  60, "jaws");
    set_attack_unarmed(A_LCLAW,  90,  90,    W_SLASH,  80, "left claw");
    set_attack_unarmed(A_RCLAW,  90,  90,    W_SLASH,  80, "right claw");
    set_attack_unarmed(A_TAIL,   120, 100, W_BLUDGEON,  70, "tail");
    set_attack_unarmed(A_HORN,   80, 100,   W_IMPALE,  30, "horn");

    set_hitloc_unarmed(H_HEAD, ({ 100 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 100 }), 80, "body");

    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(CONT_I_WEIGHT, 18000000);
    add_prop(CONT_I_VOLUME, 18000000);

    add_prop(MAGIC_I_RES_FIRE, 100);
    add_prop(MAGIC_I_RES_POISON, 75);
    
    string eye = resolve_unique(EYE_PATH, 12);
    
    if (eye)
	{
	    add_leftover(eye, "eye", 1, 0, 0, 1);
        write_file(CLONE_LOG, ctime(time()) +" eye added.\n");	
	}
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   
   if (aid == A_TAIL) {
       tell_object(enemy, "You are crushed by the massive tail!\n");
       enemy->add_attack_delay(8);
   }
   
   return 0;
}

beguile()
{
    object enemy;
    int num;
   
    enemy = TO->query_attack();
    num = random(100) + (TO->query_stat(SS_INT)/10) -
	(enemy->query_stat(SS_DIS)/10);
    if(num > 100){
	enemy->catch_msg(QCTNAME(TO) + " glares at you with demonic eyes!\n");
	tell_room(ENV(TO), QCTNAME(TO) + " glares at " +
		  QCTNAME(enemy) + " with demonic eyes!\n", enemy);
	enemy->add_panic(random(50));
	enemy->command("drop weapon");
	enemy->command("shiver");
    }
    enemy->catch_msg(QCTNAME(TO) + " tries to gaze into your eyes.\n");
    tell_room(ENV(TO), QCTNAME(TO) + " searches for the eyes of " +
	      QCTNAME(enemy) + ".\n", enemy);
}


puff()
{
    tell_room(environment(TO), QCTNAME(TO) +
	      " exhales a puff of smoke from his nostrils.\n");
    return 1;
}

regen()
{
    TO->heal_hp(random(250) + 50);
    return 1;
}

special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;

    me = this_object();
    if(random(5)) return 0;

    int damage = 240+random(240);
    damage = damage * (100 -
        enemy->query_magic_res(MAGIC_I_RES_FIRE)) / 100;

    hitresult = enemy->hit_me(damage, MAGIC_DT, me, -1);
    how = " misses";
    if(hitresult[0] > 0)
	how = " singes";
    if(hitresult[0] > 25)
	how = " burns";
    if(hitresult[0] > 40)
	how = " engulfs";

    me->catch_msg("You blast forth fire.\n");
    enemy->catch_msg(QCTNAME(me) + how +
		     " you with a titanic blast of fire.\n");
    tell_watcher(QCTNAME(me) + " exhales a titanic fiery cloud and" +
		 how + " " + QTNAME(enemy) + ".\n", enemy);

    if(enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}

blast()
{
    object *room_list;
    int i;

    tell_room(ENV(TO), QCTNAME(TO) + " blasts forth a spout of fire "
	      + "and fans it everywhere with its great wings!\n");

    /*
     * don't forget to take TO (the dragon) outof the room list
     */
    room_list = all_inventory(environment(TO)) - ({ TO });
    for (i = 0; i < sizeof(room_list); i++)
	if(living(room_list[i])){
        int damage = 200 + random(75);
        damage = damage * (100 -
            room_list[i]->query_magic_res(MAGIC_I_RES_FIRE)) / 100;
	    room_list[i]->hit_me(damage, MAGIC_DT, TO, -1);
	    room_list[i]->catch_msg("You are burned in the fanning fires!\n");
	    if(room_list[i]->query_hp() <= 0)
		room_list[i]->do_die(TO);
	}
}

