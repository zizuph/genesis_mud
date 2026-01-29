
 /*    A dragonsaurus for Thalassia

    Reference material: Rifts by Kevin Siembieda
    coder(s):    Jaacar    July 2003
    
    2003/07/29   ?         Previous update?
    2010/09/02   Lavellan  Typos and disabled obsolete tell_watcher func

 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <formulas.h>
#include <composite.h>
#include "defs.h"
#include GLYKDEF
#include MAP_HEADER

object tp = TP;

#define DEATH_LOG "dragonsaurus_death_log"

#define A_BITE  0
#define A_FRONT_FEET 1
#define A_TAIL 2
#define FEET_PEN 500

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

create_creature()
{
    set_name("dragonsaurus",1);
    set_pname("dragonsauri");
    set_short("dark green dragonsaurus");
    set_pshort("dark green dragonsauri");
    set_adj(({"dark","green"}));
    set_race_name("dragonsaurus");
    set_long("This handsome creature looks a lot like a small, "+
        "wingless dragon. It is ten feet long and stands just "+
        "over four feet high. It is dark green in colour, has very "+
        "sharp looking front claws, glowing red eyes, extremely "+
        "large sharp teeth, pointed ears and a long whiplike "+
        "tail. It appears to be quite intelligent, very agile, "+
        "and most likely deadly to tangle with.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(0);
    set_gender(G_NEUTER);
    MONEY_MAKE_GC(random(10))->move(this_object());
    clone_object("/d/Genesis/gems/obj/spinel_red")->move(TO);
    add_prop(OBJ_I_VOLUME, 50000);
    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(LIVE_I_QUICKNESS,125);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_stats(({(120+random(20)),(110+random(20)),
        (115+random(20)),(115+random(20)),
        (115+random(20)),(115+random(20))}));

    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_DEFENCE, 100);

    set_attack_unarmed(A_BITE,35,35,W_SLASH,20,"teeth");
    set_attack_unarmed(A_FRONT_FEET,35,40,W_IMPALE,60,"front feet");
    set_attack_unarmed(A_TAIL,30,30,W_SLASH,20,"tail");

    set_hitloc_unarmed(H_BODY, ({40,40,40,40}), 55, "body");
    set_hitloc_unarmed(H_HEAD, ({15,15,15,15}), 10, "head");
    set_hitloc_unarmed(H_TAIL, ({25,25,25,25}), 35, "tail");

}
/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
/*static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
} */

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("dragonsauri", environment()), attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("tritons",environment()), attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("kings",environment()), attacker);
}

/*
 * Function name: special_attack
 * Description  : Controls the dragonsaurus' special attacks in
 *                combat. Decides which to use, if any.
 * Arguments    : enemy - Object pointer to the living to attack.
 * Returns      : 1 - Made attack, no further attacks this round.
 *                0 - No special attack, continue normal combat round.
 */
public int
special_attack(object enemy)
{
    mixed *hitresult;
    object me;
    int possibilities;
    string how;

    if (random(4))
        return 0;      /* 25% chance of special attack. */

    possibilities=random(100);
    me = this_object();
    hitresult = enemy->hit_me(FEET_PEN, W_IMPALE, TO, -1, A_BODY);

    switch(possibilities)
    {
        case 0..25:
            /* Panic the attacker */
            tell_object(enemy, "The dragonsaurus shifts its glowing "+
                "red eyes on you, piercing your soul with their utter "+
                "hatred for you. It opens its mouth dangerously wide, "+
                "allowing you to see its almost foot long canine teeth. "+
                "It lets out a stream of bubbles from its mouth which "+
                "you quickly interpret as some type of growl. You feel "+
                "panic set in.\n");
            tell_room(environment(enemy), "The dragonsaurus shifts "+
                "its glowing eyes towards " + QTNAME(enemy) + ". It "+
                "opens its mouth dangerously wide, allowing you to "+
                "see it has almost foot long canine teeth. It lets "+
                "out a stream of bubbles from its mouth that you "+
                "quickly interpret to be some type of growl. " +
                QCTNAME(enemy)+" looks panicky.\n", ({enemy}));
            enemy->add_panic(random(50));
            return 1; 
            break;
        default:
            if (hitresult[0] == 0)
                how = "but misses entirely!";
            else if (hitresult[0] < 5)
                how = "but the front claws leave little more "+
                    "than a scratch.";
            else if (hitresult[0] < 20)
                how = "but fortunately, the front claws leave "+
                    "only a few deep scratches.";
            else if (hitresult[0] < 50)
                how = "and the front claws leave a hideous gash!";
            else if (hitresult[0] < 75)
                how = "and the front claws tear a vicious wound!";
            else if (hitresult[0] < 99)
                how = "and the front claws inflict a horrible "+
                    "amount of damage!";
            else
                how = "and the front claws do massive damage, "+
                    "leaving a gaping hole in their place!";

            if (enemy->query_hp() <= 0)
            {
                tell_object(enemy, "The dragonsaurus leaps at your "+
                    "body, grabbing you in its front claws. It claws and "+
                    "tears away at your fleshy chest until finally it "+
                    "tears you literally right in half!\n");
                tell_room(environment(enemy), "The dragonsaurus "+
                    "leaps at " + QTNAME(enemy) + ", clawing and tearing "+
                    "at " +enemy->query_possessive() + " fleshy chest. "+
                    "With a final strike, it literally rips "+QTNAME(enemy)+
                    "right in half!\n", ({enemy}));
                enemy->do_die(TO);
                return 1;
                break;
            }
            else
            {
                tell_object(enemy, "The dragonsaurus leaps forward "+
                    "at you, " + how + "\n");
                enemy->tell_watcher("The dragonsaurus leaps forward "+
                    "at " + QTNAME(enemy) + "'s body, " + how + "\n",
                    enemy);
                return 1;
                break;
            }
    }                
}

public void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    foos -= ({ killer });
    killers = (foos)->query_name();

    log_file(DEATH_LOG, ctime(time())+" Dragonsaurus killed by "+ 
        killer->query_name() +"("+ killer->query_average_stat() +") "+ 
        (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo")+".\n");
    ::do_die(killer);

}
