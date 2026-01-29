#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <ss_types.h>
#include <macros.h>

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";
inherit AUTO_TEAM
inherit "/lib/unique";

void
create_da_monster()
{
    set_name("sandibar");
    set_living_name("sandibar");
    set_title("Ruthless Admiral of the Black Fleet");
    set_adj(({"ruthless", "swarthy"}));
    set_long("This human looks very powerful.  From his uniform you "+
      "can see that he is a member of the Black Dragonarmy.  "+
      "By the way he stands and gives orders, it is obvious that " +
      "this man is the captain of this warship.\n");

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_AWARENESS, 70);
    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(CONT_I_HEIGHT, 165);
    set_all_hitloc_unarmed(20);
    set_alignment(-950);

    set_color("black");
    set_dragonarmy_rank(3, 1);

    set_act_time(3);
    add_act("emote sneers at you with contempt.");
    add_act("emote barks: Hard to port! Lets not get caught in the Maelstrom!");
    add_act("assist");
    add_act("say Rumour has it the Gemstone Man is sailing the Bloodseas! If he " +
       "is, i will find him and be high in the favour of the Dark Queen!");

    set_cact_time(10);
    add_cact("emote yells: May Zeboim feast upon your maggot-ridden corpse!");
    add_cact("emote laughs: You dare oppose the Black Dragonarmy?");
    add_cact("emote looks for an opening to take advantage of.");

    set_pick_up_team(({"aurak","sivak","sailor"}));
    set_max_team_size_auto_join(10);
    arm_me();
}

arm_me()
{
    object ob;

    setuid();
    seteuid(getuid());

    if(random(2))
    {
	ob = clone_object("/d/Krynn/solamn/splains/obj/bbattleaxe");
    }
    else
    {
	ob = clone_unique("/d/Krynn/solamn/splains/obj/bclaymore", 5,
	  "/d/Ansalon/balifor/port_balifor/obj/claymore");
    }
    ob->move(TO, 1);

    if(random(3))
    {
	ob = clone_object("/d/Ansalon/balifor/flotsam/obj/armour/bplatemail");
    }
    else
    {
	ob = clone_object("/d/Krynn/solamn/splains/obj/bdragonarm");
    }
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bdragonhelm");
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bshinguard");
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bheavyboots");
    ob->move(TO, 1);

    command("wear all");
    command("wield all");

    clone_object(BOBJ + "swim_potion")->move(TO, 1);
}

void
return_intro(object ob)
{
    if(!present(ob, E(TO)))
    {
	return;
    }
    command("introduce me to "+ob->query_real_name());
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
	set_alarm(3.0, 0.0, &return_intro(ob));
    }
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
