#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit M_FILE

string *gAdj1 = ({"burly","sullen","grizzled","slovenly",
  "muscular","broken","dark","tanned", "weather-beaten",
  "scurvy","ragged-eared","pox-scarred","tall","short","lean"});

#define WEP1 "/d/Ansalon/common/wep/sword/sabre"
#define WEP2 "/d/Ansalon/common/wep/sword/cutlass1"
#define WEP3 "/d/Ansalon/common/wep/sword/cutlass2"
#define FARM "/d/Ansalon/balifor/flotsam/obj/armour/"

#define sX 120 + random(20)

#define TAVERN_ENEMY "_reefcutter_tavernkeeper_enemy"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("seadog");
    add_name("_tavern_seadog");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " tavern seadog");
    set_race_name("human");

    set_long("You look upon the human wreckage of a once proud sailor of the " +
      "royal Ergothian navy. This hard figure stands in rags of the gawdy " +
      "garb typical of those who once sailed the Courrain ocean, before being stranded "+
      "ashore.\n");
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
    add_act("peer");
    add_act("emote peers into the dark corners of the tavern.");
    add_act("emote sings a bitter song of the sea into his brew.");
    add_act("say Of all the gin joints in all the Realms... ");
    add_act("emote downs a gin in a single gulp.");
    add_act("emote openly sharpens steel on the stone of the bar.");

    set_cact_time(10);
    add_cact("assist");
    add_cact("shout Storm and 'strom! We'll take ye down!");
    add_cact("say Mind ye the curse lubber!");

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
}

void
attacked_by(object ob)
{    
    ::attacked_by(ob);

    if(!ob->query_prop(TAVERN_ENEMY))
        ob->add_prop(TAVERN_ENEMY, 1);
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
        command("say More curse-chasing lubbers! Back ye all!");
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
        command("say Stupid fish-food! Better you die here than all at sea!");
    command("kill " +enemy->query_name());
    return;
}

void
init_living()
{
    if(this_player()->query_prop(TAVERN_ENEMY))
        set_alarm(3.5, 0.0, &attack_enemy(this_player()));

    ::init_living();
}
