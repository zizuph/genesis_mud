/* File         : /d/Terel/mountains/obj/dragon2.c
 * Modifications: Given this 2002 version of Rulucaraz a kill log
 *                Have added 3 leftovers 
 */

#include "/d/Terel/include/Terel.h"

#define KILL_LOG "/d/Terel/log/blackdragon_kills"

inherit STDCREATURE;
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>


#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3
#define A_HORN  4

#define H_HEAD 0
#define H_BODY 1

#define TEREL_TRIBUTE "_terel_tribute"
#define TREASURE_ROOM "/d/Terel/mountains/bottom3"
#define GEM_MIN 2000

int test_item(object item, object from);
public void drop_it(object item);

create_creature()
{
    set_name("rulucaraz"); 
    set_race_name("dragon");
    set_short("black dragon");
    set_adj("sinister");
    add_adj("black");
    set_long("This dreaded ancient black dragon is covered in pitch black adamantite scales. " +
		     "Yet, the scales of its grand figure reflect so well that you can see your own " +
		     "reflection if you would dare to do so. Being one of the larger dragons in the " +
		     "world it still seem graceful and quick in movement, prepared to rip through " +
		     "flesh with the claws and pulverize bones with its tremendous tail.\n");
   
    /*
     *           str, con, dex, int, wis, dis
     */
    set_stats(({ 300, 300, 360, 200, 200, 200}));
    set_exp_factor(200);
   
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_DEFENCE, 100);
    set_alignment(-903);
    set_fatigue(900000);
    set_hp(900000);
    set_mana(900000);

    set_attack_unarmed(A_BITE,  90, 120,   W_IMPALE,  60, "jaws");
    set_attack_unarmed(A_LCLAW,  90,  90,    W_SLASH,  80, "left claw");
    set_attack_unarmed(A_RCLAW,  90,  90,    W_SLASH,  80, "right claw");
    set_attack_unarmed(A_TAIL,   80, 100, W_BLUDGEON,  70, "tail");
   
    set_hitloc_unarmed(H_HEAD, ({ 100 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 100 }), 80, "body");

    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(CONT_I_WEIGHT, 18000000);
    add_prop(CONT_I_VOLUME, 18000000);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON,100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_DEATH,50);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_AIR, 50);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_MAGIC, 50);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_LIFE, 50);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_FIRE, 100);    
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_WATER, 50);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_EARTH, 50);

	add_leftover("claw", "dragon claw", 2 , 1, 0, 1);
	add_leftover("tail", "dragon tail", 1, 0, 1);
	add_leftover("skin", "scaled skin", 1, 0, 1);
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   
    if (aid == A_TAIL)
    {
        tell_object(enemy, "You are crushed by the massive tail!\n");
        if(enemy->query_base_stat(SS_DEX) < random(150)+100)
        {
            enemy->add_attack_delay(8);
        }
   }
   return 0;
}


special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, *all;
    int hurt, i;


    me = TO;
    all = query_my_enemies();

    if(random(9) < 2) 
    {


        for (i=0; i<sizeof(all); i++) 
        {
            hurt = 1200;
            hurt -= hurt * all[i]->query_magic_res(MAGIC_I_RES_FIRE) / 100;


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

            me->catch_msg("You blast forth fire.\n");
            all[i]->catch_msg(QCTNAME(me) + how +
		            " you with a titanic blast of fire.\n");
            if(all[i]->query_hp() <= 0)
                all[i]->do_die(me);
        }
        tell_watcher(QCTNAME(me) + " exhales a titanic fiery cloud.\n");
        return 1;
    }
    return 0;
}


public void
enter_inv(object item, object from)
{
    int     ran;

    ::enter_inv(item, from);
    if (!objectp(from))
        return;

    if (!function_exists("create_gems",item) 
     && !function_exists("create_coins",item))
    {
        set_alarm(1.0, 0.0, &drop_it(item));
        return;
    }
    set_alarm(2.0, 0.0, &test_item(item, from));
    return;
}

int
test_item(object item, object from)
{

    object player;
    int    value;
   
    player = from;

    if(function_exists("create_coins",item))
    {
       item->move(TREASURE_ROOM);
       command("sneer");
       return 1;
    }

    command("emote considers " +item->short()+ ".");

    if (item->query_value() >= GEM_MIN)
    {
       player->add_prop(TEREL_TRIBUTE, 1);
       TO->command("nod thoughtfully " + player->query_name());
       player->catch_tell("The black dragon appears in your mind, and "+
         "seems to stare pointedly at the western wall of the cave.\n");
    }

    item->move(TREASURE_ROOM);
    return 1;
}
  

public void
drop_it(object item)
{
    item->move(ENV(TO));
    command("emote drops "+item->short()+ ".");
    return; 
}


void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    tell_room(ENV(TO), "The sinister black dragon scream in agony as it attempts to gasp for a " +
		  "final breath, but its to late. The fiery eyes darkens as the upper " +
		  "body of the dragon hits the ground with a thunderous thump! The last echo of " +
          "the dragon's heartbeat halt and you stand victorious next to the dead " +
		  "dragon.\n");
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

