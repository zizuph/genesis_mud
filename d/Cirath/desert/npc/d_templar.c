#pragma strict_types
#pragma save_binary

inherit "/std/monster";
inherit "/d/Cirath/std/monster2";
#include "defs.h"
#include "/d/Cirath/tyr/tyr.h"
#include <wa_types.h>
#include "/d/Cirath/common/teamfnc.h"
#include "/d/Cirath/std/patrol.c"
#define TDESC ({"cruel", "sadistic", "pale-faced", "bureucratic",  \
	"arrogant", "condescending"})[random(6)]
#define TWEAP ({"g_sword1","g_spear1","g_club1","g_axe1"})[random(4)]
#define TBARM ({"body_std", "body_hid", "body_scl"})[random(3)]
#define TLARM ({"legs_lth", "legs_wod", "legs_hid"})[random(3)]
#define TAARM ({"arms_lth", "arms_wod", "arms_hid"})[random(3)]


void
create_monster ()
{
    ::create_monster();
   set_name("templar");
    set_race_name("curate");
    set_adj(TDESC);
    add_adj("haughty");
    set_gender(random(2));
    set_long("Standing tall and noble, this is one of the elite members "
    	+"of Kalak's templars.  Eyes blazing with power and commanding "
    	+"voice echoing like thunder, its easy to see why the curates "
    	+"hold a special position of power within the hierarchy of "
    	+"Kalak's templars.  This one leads a small patrol through "
    	+"the wastes to ensure the security of Tyr.\n");

    set_stats(({ 130, 130, 150, 110, 150, 120 }));
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 60);
    set_skill(SS_UNARM_COMBAT, 80);
    set_alignment(0);
        set_act_time(3);
    add_act("emote ponders throwing you into the slave pits.");
    add_act("emote prays.");
    add_act("say Don't cause me any trouble.");

    set_cact_time(3);
    add_cact("say You will feel the power of my master!");
    add_cact("emote gazes at you with glowing eyes.");
    add_cact("emote reaches out with an outstretched hand.");
       start_patrol();
   set_patrol_time(30);
   set_patrol_path(({"w", "w", "sw", "e", "e", "e", "se", "w", "w",
        "w", "w", "w", "ne","e", "ne", "e"}));
}
void
arm_me()
{
   clone_object(DES_WEP + TWEAP)->move(TO);
    clone_object(TYR_ARM+TBARM)->move(TO);
    clone_object(TYR_ARM+TLARM)->move(TO);
    clone_object(TYR_ARM+TAARM)->move(TO);
    clone_object(TYR_ARM+"robe_sim")->move(TO);
    command("wield all");
    command("wear all");
}

/* **************** The Templar Casts! ******************** */
int
special_attack(object enemy)
{
    object spell, me;
    mixed* hitresult;
    string how;
    int strength, power_this_time;

    me=this_object();
    strength=(me->query_base_stat(2*SS_WIS));

    power_this_time=(random(strength));

    if(random(6)) return 0;

    if(power_this_time < 75)
    {
        hitresult = enemy->hit_me((2*power_this_time), W_BLUDGEON, me, -1);
        how = "unimpressed";
        if (hitresult[0] > 0) how = "shaken";
        if (hitresult[0] > 15) how = "slightly drained";
        if (hitresult[0] > 30) how = "moderately drained";
        if (hitresult[0] > 50) how = "greatly drained";
        if (hitresult[0] > 75) how = "horribly drained";

        enemy->catch_msg(QCTNAME(me) + " touches you with "+
                         HIS_HER(me) + " outstreched palm.\n");
        enemy->catch_msg("You feel " + how + ".\n");

        tell_watcher(QCTNAME(me)+" touches "+QCTNAME(enemy)+
                     " with " + HIS_HER(me) + " outstretched palm.\n",
                     me, enemy);

        if(enemy->query_hp() <= 0) enemy->do_die(me);

        return 1;
    }

    if (present("_templar_hold_", enemy)) return 0;
    spell=clone_object(TYR_OBJ+"temphold");
    spell->set_remove_time(random(strength+1));
    spell->move(enemy);
    enemy->catch_msg(QCTNAME(me) + " touches you with " + HIS_HER(me)
         +" hand. A sense of helplessness fills you as your "
         +"limbs stiffen.\n");
    tell_watcher(QCTNAME(me)+" touches "+QCTNAME(enemy)+" lightly, "
         +"apparently inducing some sort of paralysis.\n",
         me, enemy);

    return 1;
}

