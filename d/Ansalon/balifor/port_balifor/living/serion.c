/* Based on aurak_leader by Aridor */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/splains/local.h"
#include <ss_types.h>
#include <macros.h>

inherit M_FILE
inherit AUTO_TEAM
inherit "/lib/unique";

void
create_krynn_monster()
{
    set_race_name("human");
    set_name("serion");
    set_living_name("serion");
    set_title("the Captain of the Guard");
    set_gender(0);
    set_adj(({"tall", "commanding"}));
    add_name(({"captain", "Captain", "guard"}));
    set_long("This tall commanding human looks like he " +
      "won't take any nonsense from anyone.\n");
    set_alignment(-1000);
    set_stats(({150,150,150,100,100,119}));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS, 60);
    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);
    set_all_hitloc_unarmed(20);
    set_knight_prestige(1000);

    set_act_time(3);
    add_act("emote glares haughtily at you.");
    add_act("emote growls: Only those in Her service may enter.");
    add_act("emote grins coldly at you, as if daring you to attack.");

    set_cact_time(10);
    add_cact("shout Fool! None can withstand her might!");
    add_cact("shout Soldiers! To me!");
    add_cact("mumbles a prayer to his Queen.");

    set_pick_up_team(({"mercenary"}));
    set_max_team_size_auto_join(6);

    trig_new("%w 'introduces' %s", "react_intro");
    set_alarm(0.0, 0.0, "arm_me");
}

arm_me()
{
    if(random(2) == 1)
	clone_unique("/d/Krynn/solamn/splains/obj/bbattleaxe", 5,
	  "/d/Krynn/icewall/plains/obj/taxe")->move(TO, 1);
    else
	clone_unique("/d/Krynn/solamn/splains/obj/bclaymore", 5,
	  "/d/Ansalon/balifor/port_balifor/obj/claymore")->move(TO);
    if(random(3) == 1)
	clone_unique("/d/Krynn/solamn/splains/obj/bdragonarm", 5,
	  "/d/Ansalon/balifor/flotsam/obj/armour/bplatemail")->move(TO, 1);
    else
	clone_object("/d/Ansalon/balifor/flotsam/obj/armour/bplatemail")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/bdragonhelm")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/bshinguard")->move(TO);

    command("wear all");
    command("wield all");
}

int 
react_intro(string who)
{
    if (who) {
	who = lower_case(who);
	if (find_player(who)) {
	    set_alarm(3.0, 0.0, "return_intro", who);
	}
	return 1;
    }
}

void 
return_intro(string who)
{
    command("introduce me");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

int
special_attack(object enemy)
{
    int attacktype;

    attacktype = random(11);

    if(attacktype == 1)
    {
	enemy->catch_msg(QCTNAME(TO) + " slams you mightily!\n");
	tell_room(E(TO), QCTNAME(TO) + " slams " + QTNAME(enemy) + " mightily.\n",
	  ({ enemy, TO}));

	if(!P("Serion_stun",enemy))
	    clone_object("/d/Ansalon/balifor/port_balifor/obj/serion_stun")->move(enemy);

	return 1;
    }
    return 0;
}
