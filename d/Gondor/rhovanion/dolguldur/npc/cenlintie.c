/*
 * Elven book thief - /d/Gondor/rhovanion/dolguldur/npc/cenlintie.c
 * NPC for MM guru quest
 *
 * Varian - January 2021
 */

#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>  
#include <macros.h>
#include <tasks.h>

#define WEP     weapons[0]->short()

void
create_monster()
{
   setuid();
   seteuid(getuid());
   
   set_name("cenlintie");
   add_name("elf");
   add_adj( ({"nimble", "sharp-eyed"}) );
   set_title("Silvernight, Scout of the Woodland Realm");
   set_long("This slender elf appears to be quite nimble and quick, " +
      "dodging through the trees of Mirkwood as he makes his way " +
      "towards the Woodland Realm while carrying the spellbook he " +
      "stole from you.\n");
   set_race_name("elf");
   set_gender(0);
   
   set_skill(SS_WEP_SWORD, 95);
   set_skill(SS_DEFENCE, 95);
   set_skill(SS_PARRY, 95);
   set_skill(SS_BLIND_COMBAT, 95);

   set_stats( ({ 220, 200, 250, 190, 190, 200}) );
   
   set_alignment(900);
   
   equip( ({"../wep/sil_sword.c", "../arm/sil_armour.c", 
      "../arm/elf_shield.c"}) );
}

/*
* Function name: do_die()
* Description  : When Damon dies, he drops the key to the chest.
*/
void
do_die(object killer)
{
    object spellbook;
    
    spellbook = clone_object(RHOVANION_DIR + "dolguldur/obj/spellbook");
    spellbook->move(this_object(), 1);
  
    ::do_die(killer);
}

/* Function:         query_my_enemies() : written by Mortricia
 * What's it do:     Creates an array of enemies to be used 
 *                   for randomizing
 */
public varargs object * 
query_my_enemies(int how_to_sort = 0)
{
    int i, j, swap = 0;
    object foo, *all, *enemies = ({ });
    all = all_inventory(environment(TO)) - ({ TO });
    for (i=0; i<sizeof(all); i++) {
        if (living(all[i]) && member_array(TO, all[i]->query_enemy(-1)) >= 0)
            enemies += ({ all[i] });
    }
    if (how_to_sort == 0) return enemies;
    
    for (i=0; i<sizeof(enemies)-1; i++) {
        for (j=i+1; j<sizeof(enemies); j++) {
            switch (how_to_sort) {
                case -1:     /* Sort in decreasing stat order */
                    if (enemies[i]->query_average_stat() <
                        enemies[j]->query_average_stat()) swap = 1;
                    break;
                case 1:      /* Sort in increasing stat order */
                    if (enemies[i]->query_average_stat() >
                        enemies[j]->query_average_stat()) swap = 1;
                    break;
                default:
                    return enemies;
            }
            if (swap) {
                foo = enemies[i];
                enemies[i] = enemies[j];
                enemies[j] = foo;
                swap = 0;
            }
        }
    }
    return enemies;
}
/*query_my_enemies*/

/*
 * Function name: special_attack()
 * Description  : The special attack for soldiers in Cair Andros
 */
int
special_attack(object enemy)
{
    object me = this_object();
    object *enemies = query_my_enemies();
    object kill_enemy;
    int pen;

    mixed *hitresult, *weapons = this_object()->query_weapon(-1);
    mixed *others = (query_enemy(-1) & all_inventory(environment())) 
        - ({ enemy });
    
    string how;
    string ohow;
    string tar;

    int     n = -1;

    /* We want to randomly switch targets */
    if (!random(9))
    {   
         enemy = enemies[random(sizeof(enemies))];
         kill_enemy = enemy;
         command("kill "+kill_enemy->query_real_name());
    }

    if (random(9))
    {
        return 0;  /* Continue with the normal attacks */
    }

    /* The special, based on average stats. */
    pen = query_pen_by_stat(this_object()->query_average_stat());

    hitresult = enemy->hit_me(query_pen_by_stat(pen) + random(100), 
        W_IMPALE | W_SLASH, me, -1);

    how = " barely scratching them";
    ohow = " barely scratching you";

    if (hitresult[0] >= 0)

    {
        how = " slashing ";
        ohow = " slashing ";
        tar = " body";
    }

    if (hitresult[0] > 10)
    {
        how = " cutting ";
        ohow = " cutting ";
        tar = " body";
    }

    if (hitresult[0] > 20)
    {
        how = " cleaving into ";
        ohow = " cleaving into ";
        tar = " body";
    }

    if (hitresult[0] == -1)
    {
        me->catch_msg("You strike out at " + QCTNAME(enemy)
            + " with your " + WEP + how + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with his " + WEP + "," + how + ".\n");
 
        tell_watcher(QCTNAME(me) + " strikes out at "+ QCTNAME(enemy) 
            + " with his " + WEP + how + ".\n");

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You strike out at " + QCTNAME(enemy)
            + " with your " + WEP +
            how + enemy->query_possessive() + tar + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with his " + WEP + "," +
            ohow + "your" + tar + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at "+ QCTNAME(enemy) 
            + " with his " + WEP + "," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);         
            
        if (enemy->query_hp() <= 0);
            enemy->do_die(me);

        return 1;
    }

    /*  Important! Should not have two attacks in a round. */
    return 1;
}
/*special_attack*/