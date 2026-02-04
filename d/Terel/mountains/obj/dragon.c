/*
 *  Added a check in the enter_env function to see if
 *  the object returns query_no_show() (such as magic spell
 *  objects or shadows) to stop it from dropping them.
 *
 *  27 September 2017, Arman
 *
 *  2021-03-08 - Cotillion
 *  - Fixed hitlocs
 *  
 *  Feb 2022, Lilith: removed the additional magic res since the 
 *     combat system autocalcs it based on AC now.
 *
 *  Oct 2022, Zizuph: added a dragon eye as an additional reward.
 *     readded the resistance - immunity to these elements is
 *     thematic and should stack with the automatic resistance.
 */

#include "/d/Terel/include/Terel.h"


inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/lib/unique";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3
#define A_HORN  4

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

#define TEREL_TRIBUTE "_terel_tribute"
#define TREASURE_ROOM "/d/Terel/mountains/bottom3"
#define GEM_MIN 2000

#define EYE_PATH    "/d/Terel/unique/black_dragon_eye"
#define CLONE_LOG    "/d/Terel/log/blackdragon_clones"

int test_item(object item, object from);
public void drop_it(object item);

void
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
    set_hitloc_unarmed(H_TAIL, ({ 100 }), 10, "tail");


    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(CONT_I_WEIGHT, 18000000);
    add_prop(CONT_I_VOLUME, 18000000);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(NPC_I_NO_RUN_AWAY, 1);


    setuid();
    seteuid(getuid());

    add_prop(MAGIC_I_RES_FIRE, 100);
    add_prop(MAGIC_I_RES_POISON, 100);
    
    string eye = resolve_unique(EYE_PATH, 12);
    
    if (eye)
	{
	    add_leftover(eye, "eye", 1, 0, 0, 1);
        write_file(CLONE_LOG, ctime(time()) +" eye added.\n");	
	}
    else
    {
        write_file(CLONE_LOG, ctime(time()) +" resolve returned 0.\n");	
    }

    LOAD_ERR(TREASURE_ROOM);
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

int
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

            me->catch_tell("You blast forth fire.\n");
            all[i]->catch_msg(QCTNAME(me) + " " + how +
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

    if(item->query_no_show())
	return;

    if (!function_exists("create_gems",item) 
     && !function_exists("create_coins",item))
    {
        set_alarm(1.0, 0.0, &drop_it(item));
        return;
    }
    set_alarm(2.0, 0.0, &test_item(item, from));
}

void
test_item(object item, object from)
{

    object player;
    int    value;
   
    player = from;

    if (!item) return;
    if(function_exists("create_coins",item))
    {
       item->move(TREASURE_ROOM);
       command("sneer");
       return;
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
}
  

public void
drop_it(object item)
{
    if (!item) return;
    item->move(ENV(TO));
    command("emote drops "+item->short()+ ".");
}
