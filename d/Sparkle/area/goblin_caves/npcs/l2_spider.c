/*
* Level 2 spider 
* Boreaulam, Dec 2012
*
*  Modification log:
*    - April 17th, 2017 (Gorboth): Added logging of players killed by
*                                  this creature.
*/
#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/combat/unarmed";

#include <stdproperties.h>
#include <ss_types.h>
#include <time.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"
void do_damage_special(object enemy);
void do_poison(object enemy);
void do_web(object enemy);
void do_one_of_all(object enemy);
string generate_long_desc();

/*
 * 0 - no special
 * 1 - poison
 * 2 - web stun
 * 3 - damage special
 * 10 - ALL specials (1% of monsters)
 */
int special_type;

/*
 * Function name:        create_creature
 * Description  :        constructor for the object
 */
void
create_creature()
{
    string adj = one_of_list(({"huge", "giant", "scary"}));
    set_adj(adj);
    set_name("spider");
    add_name("_l2_spider");
    set_race_name("spider");
    special_type = random(4);
    if(!random(100))
    {
        special_type = 10;
    }  

    set_short(adj + " spider");
    set_long("@@generate_long_desc");

    set_base_stat(SS_STR, 250 + random(50));
    set_base_stat(SS_DEX, 250 + random(50));
    set_base_stat(SS_CON, 250 + random(50));
    set_base_stat(SS_INT, 150 + random(50));
    set_base_stat(SS_WIS, 150 + random(50));
    set_base_stat(SS_DIS, 250 + random(50));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_attack_unarmed(0, 60, 50, W_IMPALE,  80, "legs");
    set_attack_unarmed(1, 50, 60, W_IMPALE,  60, "mandibles");
    set_hitloc_unarmed(0, ({ 80, 80,  50}),  50, "legs");
    set_hitloc_unarmed(1, ({ 80, 80,  50}),  30, "mandibles");
    set_hitloc_unarmed(2, ({ 50, 50,  80}),  20, "abdomen");
    set_attack_chance(100);
    add_prop(OBJ_I_RES_MAGIC, 80);
    set_aggressive(1);

    set_cact_time(10);
    add_cact("emote twitches its mandibles eagerly.");
    if((special_type == 1) || (special_type == 10))
    {
        add_cact("emote shows poisonous mandibles.");
    }
    if((special_type == 2) || (special_type == 10))
    {
        add_cact("emote waves its stomach and some silk goes out.");
    }
    if((special_type == 3) || (special_type == 10))
    {
        add_cact("emote moves its legs so fast that you lose track of it.");
    }
	
    add_leftover(EQUIP_DIR + "l2_mandible", "mandible", 2, 0, 0, 0);

} /* create_creature */

/*
 * Function name:        generate_long_desc
 * Description  :        long description depends on specials
 */
string
generate_long_desc()
{
    string long_desc = "The " + query_short() + " is a monstrous creature. " +
        "Sharp mandibles and jagged legs make it look incredibly dangerous.";
    switch (special_type )
    {
        case 0:
            return long_desc + "\n";
        case 1:
            return long_desc + " Poisonous liquid drops from its mandibles.\n";
        case 2:
            return long_desc + " Some sticky silk appears from spinnarets.\n";
        case 3:
            return long_desc + " The tips of these spider legs look especially dangerous.\n";
        case 10:
            return long_desc + " This spider is extremely dangerous.\n";
        default:
            return "Wrong special type";
    }
    return "Wrong special type";
 } /* generate_long_desc */

/*
 * Function name:        special_attack
 * Description  :        different special attacks
 */
int
special_attack(object enemy)
{
    if(random(3))
    {
        return 0;
    }

    if(random(2))
    {
        do_damage_special(enemy);
        return 1;
    }

    switch (special_type )
    {
        case 0:
            return 0;       
        case 1:
            do_poison(enemy);
            break;
        case 2:
            do_web(enemy);
            break;
        case 3:
            do_damage_special(enemy);
            break;
        case 10:
            do_one_of_all(enemy);
            break;
    }

    return 1;
} /* special_attack */

/*
 * Function name:        do_damage_special
 * Description  :        damage special
 */
void
do_damage_special(object enemy)
{
    mixed *hitresult;
    string result;

    int pen = 60;
    if ((special_type == 3) || (special_type == 10))
        pen += 30;

    hitresult = enemy->hit_me(pen, W_IMPALE, TO, -1);

    switch (hitresult[0])
    {
        case 0:
            result = "misses";
            break;
        case 1..10:
            result = "hurts you lightly";
            break;
        case 11..20:
            result = "you feel some pain";
            break;
        default:
            result = "crushes into you";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " hits you with its mandibles and " +
                      result + ".\n");
    tell_watcher(QCTNAME(TO) + " hits " +
                 QTNAME(enemy) + " with mandibles!\n", enemy);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
 } /* do_damage_special */

/*
 * Function name:        do_poison
 * Description  :        add poison 
 */
void 
do_poison(object enemy)
{
    object poison = clone_object("/std/poison_effect.c");
    poison->set_strength(20);
    poison->set_time(60);
    poison->set_interval(10);
    poison->move(enemy);
    poison->start_poison();
    enemy->catch_tell(query_The_name(enemy) + " bites you! You feel a " +
        "burning sensation are notice that you have been poisoned.\n");
 } /* do_poison */

/*
 * Function name:        do_web
 * Description  :        stun special
 */
void 
do_web(object enemy)
{
    enemy->add_attack_delay(6, 1);
    enemy->catch_tell(query_The_name(enemy) + " throws a web at you, hindering your movements.\n");
 } /* do_web */

/*
 * Function name:        do_one_of_all
 * Description  :        do random special
 */
void 
do_one_of_all(object enemy)
{
    switch(random(3))
    {
        case 0:
            do_damage_special(enemy);
            break;
        case 1:
            do_poison(enemy);
            break;
        default:
            do_web(enemy);
            break;
    }
 } /* do_one_of_all */

 /*
 * Function name: do_die
 * Description  : log spider deaths
 */
void
do_die(object player)
{
    write_file("/d/Sparkle/area/goblin_caves/log/spider_kills",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " [" + ctime(time())[11..18]
      + "] " + capitalize(player->query_name()) + " (ave: "
      + player->query_average_stat() + ") killed"
      + " the spider!\n");

    ::do_die(player);
} /* do_die */


/*
 * Function name:        notify_you_killed_me
 * Description  :        Called when this npc kills something. We want
 *                       to see who he ends up killing.
 * Arguments    :        object player: the one who was killed
 * Returns      :        1
 */
public int
notify_you_killed_me(object player)
{
    write_file("/d/Sparkle/area/goblin_caves/log/spider_victims",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " [" + ctime(time())[11..18]
      + "] " + capitalize(player->query_name()) + " (ave: "
      + player->query_average_stat() + ") was killed by"
      + " the spider!\n");

    return 1;
} /* notify_you_killed_me */