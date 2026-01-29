#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <ss_types.h>
#include <macros.h>

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";
inherit AUTO_TEAM
inherit "/lib/unique";

void
create_da_monster()
{
    set_name("hullek");
    set_living_name("hullek");
    set_title("Admiral of the Warship Verdigris");
    set_adj(({"huge", "musclebound"}));
    set_race_name("half-ogre");
    set_long("Before you standing comfortably on the shifting deck is a huge " +
      "musclebound half-ogre.  From his uniform you "+
      "can see that he is part of the high command of the Green Dragonarmy.  "+
      "By the way he stands and gives orders, it is obvious that " +
      "this man is the captain of this warship.\n");

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_AWARENESS, 70);
    add_prop(CONT_I_WEIGHT, 95000);
    add_prop(CONT_I_HEIGHT, 215);
    set_all_hitloc_unarmed(20);
    set_alignment(-950);

    set_color("green");
    set_dragonarmy_rank(3, 1);

    set_act_time(9);
    add_act("emote sneers at you with contempt.");
    add_act("emote barks: We will burn the elves out of their stinking forest!");
    add_act("assist");
    add_act("say I used to fight for the Black Dragonarmy, but Salah-Khan " +
      "made me an offer I could not refuse!");

    set_cact_time(10);
    add_cact("emote yells: May Zeboim feast upon your maggot-ridden corpse!");
    add_cact("emote laughs: You dare oppose the Green Dragonarmy?");
    add_cact("emote looks for an opening to take advantage of.");

    add_ask(({"salah-khan","salah khan"}),
      "say Salah-Khan is the Highlord of the Green Dragonarmy. He offered " +
      "me the command of his entire fleet if I joined him from the Black " +
      "Dragonarmy! Lucien of Takar was furious!", 1);
    add_ask(({"lucien","lucien of takar"}),
      "say Don't you know anything? Lucien is the Highlord of the Black " +
      "Dragonarmy!", 1);
    set_default_answer("@@default_answer");

    set_pick_up_team(({"aurak","sivak","sailor"}));
    set_max_team_size_auto_join(10);
    arm_me();

    trig_new("%w 'introduces' %s","react_to_intro");
}

string
default_answer()
{
    command("stare disdain " +TP->query_real_name());
    command("say I don't have time for your questions!");

    return "";
}

arm_me()
{
    object ob;

    setuid();
    seteuid(getuid());


    ob = clone_unique(RSWEAPON + "igraines_folly", 10,
      "/d/Ansalon/kalaman/obj/weapon/w_tessto");
    ob->move(TO, 1);

    if(!random(3))
    {
	ob = clone_unique("/d/Krynn/common/armours/elite_chain", 5, 
	  "/d/Ansalon/balifor/flotsam/obj/armour/bplatemail");
    }
    else
    {
	ob = clone_unique("/d/Krynn/solamn/splains/obj/bdragonarm", 12, 
	  "/d/Ansalon/balifor/flotsam/obj/armour/bplatemail");
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

}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
