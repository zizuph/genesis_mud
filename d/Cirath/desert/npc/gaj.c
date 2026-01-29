inherit "/std/creature";
inherit "/std/combat/unarmed.c";
inherit "/std/act/attack.c";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <const.h>

#include "../defs.h"

#define A_BITE  0
#define A_STALK1 1
#define A_STALK2 2
#define A_STALK3 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2


void
create_creature()
{
    set_name("gaj");
    set_race_name("gaj");
   set_short("large fearsome gaj");
    set_adj("large");
   add_adj("fearsome");
    set_gender(G_NEUTER);
    set_long("Stetching over 12 feet from its spongy white head to "
        +"the end of its strange body, the gaj is a fearsome, yet "
        +"odd creature.  Six long insected legs protrude from its "
        +"body and support its enormous mass.  Its rust orange "
        +"colored shell is insectlike, but at the same time "
        +"resembles reptile skin.  Sitting atop its head are six "
        +"compound eyes for vision, which probably give the creature "
        +"both excellent day and night vision.  The mouth of this "
        +"creature is terrifying.  A huge set of barbed mandibles "
        +"protrude fromits mouth and are surrounded by six "
        +"fingerlike appendages.  Sprouting from the back of the "
        +"creatures head are three feathery tentacles that writhe "
        +"in the air, searching for prey.\n");

   add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_VOLUME, 30000);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(LIVE_I_QUICKNESS,100);
   add_prop(LIVE_I_SEE_DARK, 1000);
    set_alignment(0);

    set_stats(({170,200,180,240,160,130}));

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);

    set_aggressive(1);

    set_hp(query_max_hp());


   set_attack_unarmed(A_BITE, 70, 70, W_SLASH, 25, "fearsome mandibles");
   set_attack_unarmed(A_STALK1, 55, 55, W_SLASH, 25, "feathery tentacles");
   set_attack_unarmed(A_STALK2, 55, 55, W_SLASH, 25, "feathery tentacles");
   set_attack_unarmed(A_STALK3, 55, 55, W_SLASH, 25, "feathery tentacles");
    set_hitloc_unarmed(H_HEAD, ({39,39,39,39}), 15, "spongy white head");
    set_hitloc_unarmed(H_BODY, ({60,60,60,60}), 70, "large insectid body");
    set_hitloc_unarmed(H_LEGS, ({40,40,40,40}), 15, "insect-like legs");

}

int
special_attack(object enemy)
{
    mixed* hitresult;
     int attacktype, bonk, i;
    string how;
    object *ob, spell;
    attacktype = random(3);
   if (attacktype == 2)
    {
   if(random(3)) return 0;
    hitresult = enemy->hit_me(450 + random(250), W_SLASH, TO, -1);
    how = "insignificantly";
    if (hitresult[0] > 0) how = "barely";
    if (hitresult[0] > 15) how = "slightly";
    if (hitresult[0] > 30) how = "somewhat";
    if (hitresult[0] > 50) how = "majorly";
    if (hitresult[0] > 75) how = "massively";

   enemy->catch_msg("The "+TO->query_short()+ " bites into you, injuring "
   		+"you "+how+".\n");

   tell_watcher("The "+ TO->query_short() + " bites into "+ QCTNAME(enemy)
                +", injuring "+HIM_HER(enemy)+" "+how+".\n",TO,enemy);

                if(enemy->query_hp() <= 0) enemy->do_die(TO);
        return 1;
	}

    if (attacktype == 1)
    {
    if(random(4)) return 0;
        hitresult = enemy->hit_me(50 + random(150), W_BLUDGEON,TO,-1);
    how = "lucky you weren't stunned";
    bonk = 0;
    if (hitresult[0] > 0)  { how = "slightly stunned"; bonk = 20; }
    if (hitresult[0] > 15) { how = "mildly disoriented"; bonk = 30;  }
    if (hitresult[0] > 30) { how = "mentally stunned"; bonk = 40; }
    if (hitresult[0] > 50) { how = "incredibly disoriented"; bonk = 50; }
    if (hitresult[0] > 75) { how = "massively stunned"; bonk = 60; }

        enemy->catch_msg(TO->query_short()+ " brushes one of "
        		+"its feathery stalks against your head "
        		+"lightly, horrible pain spirals through "
        		+"your body.\n");
        enemy->catch_msg("You feel " + how + ".\n");

        tell_watcher(TO->query_short()+ " brushes one of its "
        		+"feathery tentacles against "+QCTNAME(enemy)
        		+"'s head.  "+HE_SHE(enemy)+" reels from "
        		+"the impact.\n",TO,enemy);
    if (bonk>0) { enemy->add_attack_delay(bonk, 1); }

        if(enemy->query_hp() <= 0) enemy->do_die(TO);

        return 1;
    }

    return 0;
}

