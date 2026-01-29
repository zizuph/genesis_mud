/*********************************************************
 * Name : Lord Soth the Knight of the Black Rose         *
 * By   : Elmore                                         *
 * Date : April, 2001                                    *
 * Desc : This is the legendary Lord Soth, who's going   *
 *        to be in the Death Knights Guild in Krynn      *
 *********************************************************/

#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include <filter_funs.h>

inherit "/std/act/action.c";
inherit AM_FILE

int has_been_attacked = 0;
int intro = 0;

void
arm_me()
{
    clone_object(GUILD_ARM + "dbracers")->move(TO,1);
    clone_object(GUILD_ARM + "dplatemail")->move(TO,1);
    clone_object(GUILD_ARM + "dboots")->move(TO,1);
    clone_object(GUILD_ARM + "dcloak")->move(TO,1);
    clone_object(GUILD_ARM + "dgauntlets")->move(TO,1);
    clone_object(GUILD_ARM + "dhelm")->move(TO,1);
    clone_object(GUILD_ARM + "dgreaves")->move(TO,1);
    clone_object(GUILD_WEP + "dsword")->move(TO,1);

    command("wear all");
    command("wield all");
}

void
create_krynn_monster()
{
    set_race_name("human");
    set_name("soth");
    add_name("lord");
    add_name("knight");
    set_adj(({"tall","majestic"}));
    set_short("tall majestic male human is sitting here on his throne");
    set_gender(0);
    set_title("the Knight of the Black Rose");
    set_long("Before you stands a once noble and proud knight of "+
             "solamnia. His entire armour has been charred black "+
             "by a fire many years ago. You realize that this must be "+
             "the Lord of this Keep, Lord Soth himself. The only visible "+
             "sign of his past greatness is a rose that decorates his "+
             "platemail. Rumours has it that he often behaves according "+
             "to the Oath and Measure. However, he adheres to the "+
             "trappings of honor more as a mockery than as an ethos.\n");
    set_knight_prestige(10000);
    trig_new("%w 'introduces' %s", "react_introduce");
    set_stats(({270,190,220,110,100,220}));

    set_skill(SS_AWARENESS, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_alignment(-1500);
    set_all_hitloc_unarmed(40);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000); 
    change_prop(LIVE_I_QUICKNESS, 700);

    add_prop("_ranger_m_not_disarm",1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_act_time(20);
    add_act("emote slowly turn his deep orange eyes at you.");
    add_act("emote quickly pulls his black cloak over his shoulders.");
    add_act("say In death there is no honour.");
    add_act("say Curse those Solamnian Knights!");
    add_act("say Dargaard Keep will never be as grand as it once were.");
    add_act("sigh");
    add_act("emote briefly looks at you with his deep orange eyes.");
    add_act("say I will get my revenge soon.");
    arm_me();
}

void
react_introduce(string person,string who)
{
   if (!intro)
      intro = set_alarm(1.0,0.0,"introduce_me");
}

void
introduce_me()
{
   tell_room(E(TO),QCTNAME(TO) + " introduces himself as:\n" +
      "Lord Loren Soth the Lord of the Black Rose and Lord of Dargaard Keep, male human.\n");
   FILTER_LIVE(all_inventory(E(TO)))->add_introduced("soth");
   intro = 0;
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    int chance;
    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;
    
    chance = random(4);
    if (chance == 1)
        pen = 10000;
    else
        pen = 500;

    enemy->catch_msg(QCTNAME(TO) + 
      " turns his deep orange eyes at you.\n"+
      "For a brief moment his eyes flares up!\n"+
      QCTNAME(TO)+ " points at you and utters the word: DIE!\n");

    tell_room(E(TO), QCTNAME(TO) + " turns his deep orange eyes at " +
      QTNAME(enemy) + "\n."+
      "For a brief moment "+HIS(TO)+ " eyes flares up!\n"+
      QCTNAME(TO)+ " points at "+QTNAME(enemy)+" and utters "+
      "the word: DIE!\n",({enemy, TO}));

    hitres = enemy->hit_me(pen, 40, TO, -1);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(TO);
    }

    return 1;
}

void
attacked_by(object ob)
{
    if (has_been_attacked == 0)
    {
        has_been_attacked = 1;
        command("emote rises from his throne.");
        command("shout For that, you shall die!");
        TO->set_short("tall majestic male human");
        TO->update_state();
    }
    ::attacked_by(ob);
}

