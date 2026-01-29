#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
inherit "/d/Kalad/std/group_cluster";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";

public void         create_monster();

#define A_BITE  1
#define A_LCLAW 2
#define A_RCLAW 4
#define H_HEAD 1
#define H_BODY 2

void
create_monster()
{
    ::create_monster();
    set_name("serpent");
    add_name("shadowy");
    add_name("demon");
    add_name("_thanar_npc");
    set_race_name("serpent");
    set_adj("ghastly");
    add_adj("black");
    set_long("A serpent summoned from the demonic plains where the Lord "
    +"Thanar makes his home. Black, ghastly, and with huge fangs, this "
    +"creature is not to be trifled with. It serves Lord Thanar and arrive "
    +"at his beckon call.\n");
    set_gender(G_NEUTER);
    set_stats(({125, 125, 125, 125, 125, 125}));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);
    set_act_time(6);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 50);
    add_prop(LIVE_I_SEE_INVIS, 50);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_attack_unarmed(A_BITE, 25, 35, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 20, 15, W_IMPALE, 30, "fangs");
    set_attack_unarmed(A_RCLAW, 20, 15, W_IMPALE, 30, "fangs");
    set_hitloc_unarmed(H_HEAD, ({ 20, 30, 25 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 15, 20, 35 }), 80, "body");
    set_aggressive(1);
    
    set_prospective_cluster(({"_thanar_npc"}));
}

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
 }/*query_my_enemies*/
 
 /* Function:         query_smallest_enemy() : written by Mortricia
  * What's it do:     Allows to easily determine the smallest enemy.
  */
 public object
 query_smallest_enemy()
 {
     object *enemies;
     if (sizeof(enemies = TO->query_my_enemies(1)) == 0) return 0;
     return enemies[0];
 }/*query_smallest_enemy*/

/*
 * Function name: special_attack()
 * Description  : Randomly triggers the special attack
 * Arguments    : Enemy = the enemy of the object
 */
 int
 special_attack(object enemy)
 {
     object *ob;
     object *enemies;
     object kill_enemy, enemy;
     int i;
     int did_push;
     int pen;
     object me;
     mixed* hitresult;
     string how;
     me = this_object();
     
     enemies = query_my_enemies();
     
     if (sizeof(enemies) == 0) return 0;
     
     /* This decides if we shall do anything more... */
     if (random(2))
         return 0;
     
     enemy = me->query_attack();
     
     /*We want this to be hard. So they attack the smallest*/
     if (enemy != me->query_smallest_enemy())
     {   
          enemy = query_smallest_enemy();
          kill_enemy = enemy;
          command("kill "+kill_enemy->query_real_name());
     }
     
     pen = query_pen_by_stat(TO->query_average_stat());
     hitresult = enemy->hit_me(query_pen_by_stat(TO->query_average_stat()) 
     + random(400));
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
             how = "puncturing skin";
             break;
         case 111..140:
             how = "tearing skin away";
             break;
         case 141..170:
             how = "piercing to the bone";
             break;
         default:
             how = "shattering bones";
             break;
     }
     me->catch_msg("You lash out with your fangs striking with giant fangs, "
     +how+"!\n");
     enemy->catch_msg(QCTNAME(me)+" strikes you with giant fangs, "
     +how+"!\n");
     MIR_DEBUG("Serpent Pen " +pen+ ", hitresult: "+hitresult[3]+ ".");
     tell_watcher(QCTNAME(me)+" strikes "+QTNAME(enemy)+" with giant fangs, "
     +how+ "!\n",enemy);
         
     if (enemy->query_hp() <= 0)
     {
         enemy->do_die(me);
         return 1;
     }
 }/*special_attack*/