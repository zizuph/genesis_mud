/*  This is an NPC named "shan" Jin. He is called by mesg_shop.c as a
 *  shopkeeper.  If he is killed, the shop will not function.  
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;


#include <formulas.h>
#include <wa_types.h>

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>


#define DAB_TOWN "/d/Terel/dabaay/town/"
#define KILL_LOG "/d/Terel/dabaay/log/shan_kills"

void dress_me();

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("Shan Jin");
    add_name("shan");
    add_name("jin");
    set_race_name("human");
    set_adj("shan");
    set_long("Shan Jin appears to be a pleasant sort, with a smile permanently "+
        "fixed to his face.  His eyes are slightly slanted and seem to sparkle "+
        "with an inner humour of their own.  Under all of these pleasant features "+
        "Mr. Jin excudes an air of confidence, that makes you think twice about "+
        "causing any trouble here.\n"); 

    /* Average stat: 92
     */
    default_config_npc(102);

    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 85);
    set_skill(SS_UNARM_COMBAT, 99);
    set_hp(9999);

    set_all_hitloc_unarmed(50);
    set_all_attack_unarmed(60, 50);

    set_chat_time(15);

    add_chat("My lil' friends are best of messengers in all of lands! You try! You see!"); 

    add_chat("You see! You try one of my pets! Never let you down! You see!");

    add_chat("Best in land! My little flying friends get you message to you friend "+
        "fastest of all!\n");

    add_chat("You friend no outside? You try one of my running friends! They get "+
        "you message to anywhere you friend is!\n");

    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 150);
    add_prop(OBJ_M_HAS_MONEY, random(800) + 900);
    dress_me();
}

void
dress_me()
{
    FIX_EUID;
    clone_object(DABAAY_DIR + "armour/l_tunic")->move(TO);
    command("wear all");
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

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how,where;
    object me, wuss;
    int intox,hurt, i;

    intox = enemy->query_intoxicated();

    me = TO;

    if(random(10) > 7)
    {
        hurt = F_PENMOD(45 + (intox / 3), 45 + (intox / 3));

        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, -1);

        if (hitresult[0] >= 0)
        {
            how = "tossed hard";
            where = "square3_4";
        }
        if (hitresult[0] > 20)
        {
            how = "thrown far";
            where = "square3_5";
        }
        if (hitresult[0] > 50)
        {
            how = "hurled wildly";
            where = "square3_6";
        }
        if (hitresult[0] > 100)
        {
            how = "violently flung";
            where = "panchos";
        }

        if (enemy->query_hp() <= 0)
        {
            command("bow " + enemy->query_real_name());
            tell_watcher(QCTNAME(enemy) + " is slammed down hard on the ground.\n",enemy);
            enemy->catch_tell("You are brutally slammed into the ground!\n");
            enemy->do_die(me);
            
        }

        else
        {
           tell_room(ENV(TO), QCTNAME(me) + " grabs hold of " + QCTNAME(enemy) +
               " and flips " + HIM_HER+ " over his shoulder and out "+
               "door!\n",enemy,TO);
           enemy->catch_tell(query_The_name(enemy) + " grabs hold of you and "+
               "flips you over his shoulder!\n" +
               "You are " + how + " out the door!\n");
           enemy->move_living("M",DAB_TOWN + where,0,0); 
           tell_room(ENV(enemy), QCTNAME(enemy)+ " flies in from the west and "+
               "lands in a painful heap on the ground.\n",enemy,TO);
        }
        return 1;
    }


           
    if(random(11) > 7) 
    {
        hurt = F_PENMOD(35 + (intox / 3), 35 + (intox / 3));

        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        tell_watcher(QCTNAME(me) + " spins and kicks at " + QCTNAME(enemy) + ".\n",
                             enemy);
        enemy->catch_tell(query_The_name(enemy) + " spins and kicks at you!\n" +
            "You feel " + how + ".\n");

        if (enemy->query_hp() <= 0)
        {
            command("bow " + enemy->query_real_name());
            enemy->do_die(me);
        }

        return 1;
    }


    return 0;
}


