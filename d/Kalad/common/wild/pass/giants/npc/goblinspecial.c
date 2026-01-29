/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/
*   Created by Meton - 2020
*/

#pragma strict_types
#pragma save_binary

inherit "/d/Kalad/std/active_monster_base.c";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#define C_OVERWHELMED   "_c_overwheldmed"

/* Function:         query_my_enemies() : written by Mortricia
 * What's it do:     Creates an array of enemies to be used for randomizing
 */
 public varargs object *
 query_my_enemies(int how_to_sort = 0)
 {
     int i, j, swap = 0;
     object foo, *all, *enemies = ({ });
     all = all_inventory(environment(TO)) - ({ TO });
     for (i=0; i<sizeof(all); i++) {
         if (living(all[i]) && member_array(TO, all[i]
            ->query_enemy(-1)) >= 0)
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
 }/*query_my_enemies*/


/*
 * Function name: special_attack()
 * Description  : 25% triggers the special attack
 * Arguments    : Enemy = the enemy of the object
 */
 int
 special_attack(object enemy)
 {
    if (random(100) >= 25)
    {
        return 0;
    }
    else
    {
    object *ob;
    object *enemies;
    object enemy;
    int i;
    int pen;
    int enemysize2,mysize2,teameffect,propeffect;
    string overwhelmed_message;
    object me;
    mixed* hitresult;
    string how;
    me = this_object();
     
    enemies = query_my_enemies();
    
    if (sizeof(enemies) == 0) return 0;

    enemy = TO->query_attack();
     
    //getting the amount of teammembers, and setting prop
    enemysize2 = (sizeof(enemy->query_team_others()) + 1);
    mysize2 = (sizeof(TO->query_team_others()) + 1);
    teameffect = mysize2 - enemysize2;

    switch (teameffect)
    {
        case -10..0:
            overwhelmed_message = " after charging.";
            break;
        case 1:
            propeffect = 5;
            overwhelmed_message = " while " + HIS(TO) + " friend roar.";
            break;
        case 2..3:
            propeffect = 10;
            overwhelmed_message = " while "+ HIS(TO) +" friends bellow a "
            + "disctraction.";
            break;
        case 4..10:
            propeffect = 15;
            overwhelmed_message = " while "+ HIS(TO) +" teammembers "
            + "swarms all around.";
            break;
        default:
        overwhelmed_message = "Please make a bug report.\n";
            break;
    }
    command("special");
    /* Adding a bit damage if playerteam<npcteam.*/
    pen = query_pen_by_stat(TO->query_average_stat());
    pen += propeffect;
    hitresult = enemy->hit_me(pen);
     
     switch (hitresult[3])
     {
         case 0..20:
             how = "without effect";
             break;
         case 21..50:
             how = "softly";
             break;
         case 51..80:
             how = "hard";
             break;
         case 81..110:
             how = "very hard";
             break;
         case 111..140:
             how = "extremely hard";
             break;
         case 141..170:
             how = "smashingly";
             break;
         default:
             how = "smashingly";
             break;
    }
    me -> catch_msg("You strike your opponent in the stomach,"+how+"!\n");
    enemy->catch_msg(QCTNAME(me)+ " strikes you " + how + " in your "
        + "stomach," + overwhelmed_message + "\n");
    
    tell_watcher(QCTNAME(me)+" strikes "+QTNAME(enemy)+" "+how+
        " in the stomach, " + overwhelmed_message +"\n",enemy);
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(me);
        return 1;
    }
    return 1;
    }
}