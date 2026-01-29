/* Mountain goat for the foothills in Calia.

   Coded by Maniac and Digit, Aug 95

   History:
   Updated by Maniac 3/4/99
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
#include "monster.h"


#define A_BITE  0
#define A_HORNS 1
#define A_HOOVES 2

#define H_HEAD 0
#define H_BODY 1


void
create_creature()
{
    string *general = ({"haughty", "sturdy", "proud"});

    set_name("goat");
    set_race_name("goat");
    set_adj(({general[random(sizeof(general))],
              "mountain"}));
    set_long("It is one of the curly-horned mountain goats that inhabits "+
             "these foothills, spending most of its time sauntering " +
             "gently around grazing and trying to avoid being eaten " +
             "by mountain cats.\n");
    set_stats(({30,30,30,5,5,30}));
    set_hp(query_max_hp());
    set_skill(SS_DEFENCE,30);
    set_attack_unarmed(A_BITE,20,20, W_IMPALE, 20, "bite");
    set_attack_unarmed(A_HORNS,20,20, W_SLASH, 40, "horns");
    set_attack_unarmed(A_HOOVES,20,20, W_BLUDGEON, 40, "hooves"); 
    set_hitloc_unarmed(H_HEAD, ({12,12,12,12}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({12,12,12,12}), 80, "body");

    set_restrain_path(FOOTHILL); /* restrict it to the foothills  */
    set_random_move(15);

    set_act_time(2);

    add_act("emote looks at you, seeming to ponder whether you are " +
            "wearing anything edible.");
    add_act("emote grazes in leisurely fashion.");
    add_act("emote looks around warily.");
    add_act("emote tosses its head haughtily.");

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_m_in("saunters in");
    set_mm_in("saunters in.");
    set_m_out("saunters");
    set_mm_out("saunters out.");
}




/* goat butts people with its horns */
int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;

    me = this_object();
    if(random(6))
       return 0;
    hitresult = enemy->hit_me(50+random(20), W_IMPALE, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)
       how = "";
    if (hitresult[0] > 10)
       how = " hard";
    if (hitresult[0] > 20)
       how = " very hard";
    enemy->catch_msg(QCTNAME(me)+ " butts you " + how + "!\n");
    tell_watcher(QCTNAME(me)+" butts "+QTNAME(enemy) + how + "!\n", enemy);
    if(enemy->query_hp() <=0)
       enemy->do_die(me);
    return 1;
}
