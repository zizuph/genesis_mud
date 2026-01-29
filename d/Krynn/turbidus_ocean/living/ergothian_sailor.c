#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit M_FILE

string *gAdj1 = ({"burly","sullen","handsome","excited",
  "muscular","friendly","jovial","dark-skinned",
  "ugly","big-eared","big-nosed","tall","short","fat"});

#define WEP1 "/d/Ansalon/common/wep/sword/sabre"
#define WEP2 "/d/Ansalon/common/wep/sword/cutlass1"
#define WEP3 "/d/Ansalon/common/wep/sword/cutlass2"
#define FARM "/d/Ansalon/balifor/flotsam/obj/armour/"

#define PEARL "/d/Genesis/gems/obj/pearl"
#define sX 100 + random(20)

#define ATTACKED_ERGOTHIANS "_attacked_ergothian_sailors"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("sailor");
    add_name("_ergothian_sailor");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " Ergothian sailor");
    set_race_name("human");
    set_long("You look upon the muscular figure of a sailor of the " +
      "royal Ergothian navy. This dark-skinned human is in a gawdy " +
      "garb typical of all those who sail the Courrain ocean.\n");
    set_stats(({sX,sX,sX,sX,sX,sX}));
    set_hp(10000);

    add_prop(CONT_I_HEIGHT, 180 + random(10));
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 80000);

    set_skill(SS_WEP_CLUB, 50 + random(50));
    set_skill(SS_WEP_SWORD, 50 + random(50));
    set_skill(SS_WEP_AXE, 50 + random(50));
    set_skill(SS_DEFENCE, 50 + random(50));
    set_skill(SS_PARRY, 50 + random(50));

    set_alignment(0);
    set_all_hitloc_unarmed(20); 


    set_act_time(20);
    add_act("ahoy Repel boarders!");
    add_act("assist");
    add_act("peer");
    add_act("shout All hands to deck!");
    add_act("say I can't wait to get this cargo back to Ergoth! " +
            "I could do with a strong drink!");
    add_act("emote trims the sails slightly.");
    add_act("emote tries to dislodge a grappling hook.");

    set_cact_time(10);
    add_cact("assist");
    add_cact("shout To arms! Pirates!");
    add_cact("say By the Blue Phoenix, repel these boarders!");

}

void
arm_me()
{
    int weapon = random(3);
    seteuid(getuid(TO));

    if(weapon == 0)
	clone_object(WEP1)->move(TO,1);
    if(weapon == 1)
	clone_object(WEP2)->move(TO,1);
    if(weapon == 2)
	clone_object(WEP3)->move(TO,1);
    command("wield all");
    clone_object(FARM + "shirt")->move(TO,1);
    clone_object(FARM + "bandana1")->move(TO,1);
    command("wear all");
    if(random(5) == 1)
	clone_object(PEARL)->move(this_object(), 1);
}

void
attacked_by(object ob)
{    
    ::attacked_by(ob);

    if(!ob->query_prop(ATTACKED_ERGOTHIANS))
        ob->add_prop(ATTACKED_ERGOTHIANS, 1);
}

void
attack_enemy_again(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        return;
    }

    if(!random(3))
        command("say More pirates! Attack!");
    command("kill " +enemy->query_name());
    return;
}

void
attack_enemy(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        set_alarm(6.5, 0.0, &attack_enemy_again(enemy));
        return;
    }
    
    if(!random(3))
        command("say More pirates! Attack!");
    command("kill " +enemy->query_name());
    return;
}

void
init_living()
{
    if(this_player()->query_prop(ATTACKED_ERGOTHIANS))
        set_alarm(3.5, 0.0, &attack_enemy(this_player()));

    ::init_living();
}
