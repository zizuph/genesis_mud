/* Mountain goat for the foothills in Calia.

   Coded by Maniac and Digit, Aug 95

   Updated 23/7/96, 3/4/99 by Maniac
    
*/

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <options.h>
#include "monster.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1


void
create_creature()
{
    string *general = ({"fierce", "sleek", "hungry"});

    set_name("cat");
    set_race_name("cat");

    set_adj(({general[random(sizeof(general))],
               "mountain"}));

    set_long("This mountain cat is large and vicious looking, " +
             "with sharp teeth and claws.\n");
    set_stats(({60,70,60,20,20,80}));
    set_hp(2500);
    set_skill(SS_DEFENCE,45);
    set_attack_unarmed(A_BITE,25,25, W_IMPALE, 30, "bite");
    set_attack_unarmed(A_LCLAW,25,25, W_SLASH, 35, "left claw");
    set_attack_unarmed(A_RCLAW,25,25, W_SLASH, 35, "right claw");
    set_hitloc_unarmed(H_HEAD, ({10,10,10,10}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({10,10,10,10}), 80, "body");

    set_restrain_path(FOOTHILL); /* restrict it to the foothills  */
    set_random_move(15);

    set_act_time(2);
    add_act("kill goat");
    add_act("emote glares hungrily at you.");
    add_act("emote stalks restlessly around.");
    add_act("emote licks its paws.");

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_appearance(1000);
    set_m_in("stalks in");
    set_mm_in("leaps in.");
    set_m_out("stalks");
    set_mm_out("leaps out.");
}


int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;

    me = this_object();
    if(random(5))
       return 0;
    hitresult = enemy->hit_me(80+random(20), W_IMPALE, me, -1);
    how = ", without effect";
    if (hitresult[0] > 0)
       how = "";
    if (hitresult[0] > 10)
       how = ", leaving a nasty wound";
    if (hitresult[0] > 20)
       how = ", leaving a terrible wound";
    enemy->catch_msg(QCTNAME(me)+ " thrashes you with it's claws" + how + 
                     "!\n");
    tell_watcher(QCTNAME(me)+" claws "+QTNAME(enemy)+how+"!\n",
                 enemy);
    if(enemy->query_hp() <=0)
       enemy->do_die(me);
    return 1;
}
