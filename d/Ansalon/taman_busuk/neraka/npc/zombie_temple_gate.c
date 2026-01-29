/* Ashlar, 20 Aug 97 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

#define GRABOBJ_ID  "_zombie_grab_"
#define ONE_OF(x)   (x[random(sizeof(x))])

#define ADJ ({ "decaying", "rotting", "putrid", "foul" })

int closeness;
object grabbed;

int delaycounter;

void
check_status()
{
    object to_kill;
    
    if (query_attack())
    {
        delaycounter = 0;
        return;
    }
    else
    {
        to_kill = E(TO)->find_random_undead_target();
        if (to_kill == 0)
        {
            delaycounter++;

            if (delaycounter == 10)
            {
            	E(TO)->remove_undead(TO);
            	tell_room(E(TO), "With a groan, " + QTNAME(TO) + " crawls " +
            	"down through the cracked flagstones into the ground from " +
            	"whence it came.\n");
            	remove_object();
            }
        }
        else
        {
            command("kill " + to_kill->query_real_name());
        }
    }
}

void
create_krynn_monster()
{
    int k;
    
    set_name("zombie");
    set_adj(ONE_OF(ADJ));
    set_race_name("zombie");

    set_long("This is the decaying corpse of a man, animated by dark " +
    "powers and turned into an undead. Without any volition, it serves " +
    "in aiding the defence of the Temple of Takhisis. " +
    "A foul stench surrounds it, and the stare in " +
    "its deep-set eyes is malevolent.\n");

    set_stats(({230+random(30),50+random(30),170+random(20),
        10, 10, 190+random(40)}));

    k = query_average_stat();
    k = k*k/20;

    set_alignment(-k);
    set_knight_prestige(k);

    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 20);

    add_prop(LIVE_I_QUICKNESS, -40);
    add_prop(LIVE_I_UNDEAD, k/17 + 10);
    add_prop(LIVE_I_SEE_DARK, 3);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_all_hitloc_unarmed( ({ 15, 15, 10, 15 }) );
    set_all_attack_unarmed(20, 10);

    set_act_time(4);
    add_act("moan");
    add_act("emote stares blankly.");

    set_cact_time(2);
    add_cact("moan");
    add_cact("emote reaches for you with its foul hands.");

    /* The zombies will only hit with their fists */
    remove_attack(W_FOOTR);
    remove_attack(W_FOOTL);

    set_alarm(5.0, 30.0, check_status);

}

int
filter_attacks_us(object ob)
{
    if (ob->query_attack() == TO)
        return 1;
    else
        return 0;
}

int
special_attack(object enemy)
{
    object *enemies;
    string *str;
    object grabobj;

    /* First, we decide if anyone is fighting us */
    enemies = FILTER_LIVE(all_inventory(E(TO)));
    enemies = filter(enemies,filter_attacks_us);
    if (sizeof(enemies))
    {
        if (objectp(grabbed) && (grabobj = P(GRABOBJ_ID, grabbed)) &&
            (E(grabbed) == E(TO)))
        {
            grabbed->catch_msg(query_The_name(grabbed) + " lets go of " +
            "you.\n");
            tell_watcher(QCTNAME(TO) + " lets go of " + QTNAME(grabbed) +
                ".\n", grabbed);
        }
        if (grabobj)
            grabobj->remove_object();
        grabbed = 0;    
        closeness = 0;
        return 0;
    }

    switch(closeness++)
    {
        case 0:
            str = ({ query_The_name(enemy) + " moves towards you, its " +
            "arms reaching for you.",
            QCTNAME(TO) + " moves towards " + QTNAME(enemy) + ", arms " +
            "reaching for " + HIM(enemy) + "." });
            break;
        case 1:
            str = ({ "You feel " + query_the_name(enemy) + "'s hands " +
            "around you.",
            QCTNAME(TO) + " has its hands around " + QTNAME(enemy) + "." });
            break;
        case 2:
            str = ({ query_The_name(enemy) + " throws its arms around " +
            "your body, holding you in an iron grip.",
            QCTNAME(TO) + " throws its arms around " + QTNAME(enemy) +
            "'s body, holding " + HIM(enemy) + " in an iron grip." });
            grabobj = clone_object(NOBJ + "zombiegrab");
            grabobj->set_grabber(TO);
            grabobj->move(enemy, 1);
            grabbed = enemy;
            break;
        default:
            if (closeness > 2)
                return 1;
            else
                return 0;
    }
    enemy->catch_msg(str[0]+"\n");
    tell_watcher(str[1]+"\n",enemy);

    return 1;
}

void
grabbed_break_free()
{
    grabbed = 0;
    /* Cannot grab again for a while */
    closeness = -4;
}

void
arm_me()
{
    setuid();
    seteuid(geteuid(this_object()));

    clone_object(NARM + "stud_leather")->move(TO);

    command("wear all");
    command("wield all");

}

void
attack_object(object ob)
{
    closeness = 0;
    ::attack_object(ob);
}

void
attacked_by(object ob)
{
    closeness = 0;
    ::attacked_by(ob);
}
