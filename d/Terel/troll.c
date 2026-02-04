/* 
 * troll.c
 * Troll north of Terel. Claws and regenerates, sort of.
 * Shinto:
 *
 *  Modified: 6 May 2003, by Bleys
 *      - fixed a typo in the special 
 *
 *            30 June 2008 Lilith
 *      - Removed code that discriminated against people who can
 *        go invis and see or fight in the dark. They pay for
 *        these skills and abilities, why foil them? Also,
 *        lowered the evil align. They do nothing to warrant 
 *        being -700 align.
 *           15 Aug 2008  Lilith
 *      - Lowered the 130 exp modifier to 110
 *      - Added logging of kills
 *           28 Sep 2008  Lilith
 *      -Made it possible for randomly larger sized npcs.
 *      -put exp factor back in, but at 125.   
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>

#define A_BITE   1
#define A_R_CLAW 2
#define A_L_CLAW 4

#define H_HEAD 1
#define H_BODY 2
#define H_R_ARM 3
#define H_L_ARM 4

#define KILL_FILE "/d/Terel/common/moor/tcaves/npc/troll_log"

void
create_creature()
{
    set_name("troll"); 
    add_name("ogre");
    set_race_name("troll");
    set_adj(({ "large", "terrifying", "green-skinned", "disgusting",
	       "sickly", "grotesque", "slimy", "brown-skinned"})[random(8)]);
 
    set_long("A horrible flesh-eating creature. It has thick skin\n"
       +"of putrid gray-green and mottled black. Its mouth lined\n"
       +"with cruel teeth, its hands with dagger-like claws.\n"
       +"Dirty and smelling of rot, its body covered with hides\n"
       +"and tattered clothing, its head draped by thick strands\n"
       +"of gray bestial hair. Its eyes black with yellow slits.\n");
    
    default_config_creature(150 + random(50));
    
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_BLIND_COMBAT, 75);
 
    set_aggressive(1);
    set_alignment(-250);
 
    add_prop(LIVE_I_SEE_DARK, 3);
    add_prop(NPC_I_NO_FEAR, 1); 
 
    set_attack_unarmed(A_BITE,   40, 45, W_IMPALE, 30, "bite");
    set_attack_unarmed(A_R_CLAW, 45, 40, W_SLASH, 35, "right claw");
    set_attack_unarmed(A_L_CLAW, 45, 40, W_SLASH, 35, "left claw");
    
    set_hitloc_unarmed(H_HEAD, ({ 45, 35, 40}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 40, 35, 40}), 40, "body");
    set_hitloc_unarmed(H_R_ARM, ({35, 35, 35 }), 20, "right arm");
    set_hitloc_unarmed(H_L_ARM, ({35, 35, 35 }), 20, "left arm");
    set_exp_factor(125);
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, wuss;
    int hurt;

    me = TO;

    if(random(10) > 7) 
    {
        hurt = F_PENMOD(40 +(random(10)), 40 + (random(20)));

        hitresult = enemy->hit_me(hurt, W_SLASH, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        tell_watcher(QCTNAME(me) + " slashes at " + QTNAME(enemy) + ".\n", enemy);
        enemy->catch_tell(query_The_name(enemy) + " slashes at you!\n" +
            "You feel " + how + ".\n");

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(me);
	}

        heal_hp(50 + random(50));
        wuss = query_smallest_enemy();
        if (wuss != query_attack())
	{
            command("kill " + wuss->query_real_name());
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

    if (query_hp() > 100)
        return 0;

    if (!killer)
        killer = previous_object();

    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) 
    {
      if (enemies[i] != killer)
          str += ", " + enemies[i]->query_name() +
                 "[" + enemies[i]->query_average_stat() + "]";
    }
    write_file(KILL_FILE, ctime(time()) +" by "+ str +"\n");

    ::do_die(killer);

}



