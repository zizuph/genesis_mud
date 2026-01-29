/* Navarre Aug 20th 2006, added checks to avoid runtime error */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#define ARM1 ARMOUR + "shield"
#define ARM2 ARMOUR + "l_gauntlets"
#define WEP  WEAPON + "spear"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"centaur"}));
    set_max_team_size_auto_join(4);

    set_name("centaur");
    set_adj("burly");
    add_adj("dull");
    set_race_name("centaur");
    set_gender(G_MALE);
    set_short("burly dull centaur");
    set_long("Before you is a muscular centaur who is " +
      "standing as guard before the entrance to a nearby tent. " +
      "He looks very strong, but not very bright.\n");

    set_stats(({115,100,125,89,89,96}));
    set_hp(10000);
    add_prop(OBJ_M_NO_ATTACK,"You don't think it would be " +
      "wise to attack this centaur considering you are " +
      "surrounded by a tribe of his brethren.\n");
    add_prop(NPC_I_NO_RUN_AWAY,1);
    set_default_answer("The centaur doesn't understand " +
      "what you are talking about.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    set_alignment(500);
    set_knight_prestige(-200);
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 20);

    remove_attack(W_FOOTR);
    remove_attack(W_FOOTL);

    set_act_time(10);
 add_act("emote bows in greeting before you, extending his " +
      "foreleg and touching his hand to his shaggy hair.");
add_act("emote stamps the ground aggressively with his hooves.");
    add_act("say I wish the kender would quit trying to ride me. It is " +
      "quite annoying.");
    add_act("emote flicks his tail at an annoying insect.");
    add_act("chuckle merr");

    set_cact_time(5);
    add_cact("emote booms: Put thy puny weapons down. Ye surely do not have " +
      "a chance against me!");
    add_cact("emote rears up aggressively at you!");
    add_cact("say Leave our glade fiend or thy shall surely die!");
    add_cact("say For the love of Chislev begone!");

    add_ask(({"shaman","tent"}),"say I guard the tent of " +
      "the shaman. The shaman is not to be bothered " +
      "by strangers. That is his orders to me. Still, I guess " +
      "that all depends on my interpretation of what a " +
      "stranger is eh?\n",1);
    add_ask(({"stranger","strangers"}),"say Hmm. I guess " +
      "the shaman means strangers as people who are not " +
      "centaur-friends. If you can bring me a gift that proves " +
      "you are a centaur-friend, I'll let you in to see the " +
      "shaman.\n",1);
    add_ask("gift","say Bring me something that all centaurs are " +
      "fond of. Then I'll let you pass. If you don't know what " +
      "that would be, I guess you cannot be a centaur-friend " +
      "after all.\n",1);
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP)->move(TO,1);
    command("wield all");
    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    command("wear all");
}

int
special_attack(object enemy)
{
    int attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how;

    attacktype = random(5);

    if (attacktype == 1)
    {
	pen = 25 + random(25);
	hitres = enemy->hit_me(pen, 20,TO,-1);

	enemy->catch_msg(QCTNAME(TO) + 
	  " strikes you savagely with his front hooves!\n");
	tell_room(E(TO),QCTNAME(TO) + " strikes out at " +
	  OBJECTIVE(enemy) + " savagely with his hooves!\n",
	  ({enemy, TO }));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

void
return_give_wine(object from)
{
    command("cheer");
    command("say Yep, you are definately a centaur-friend!");
    command("drink all");
    write("The centaur lets you pass into the tent.\n");
    say("The centaur lets " + QTNAME(TP) + " pass!\n");
    TP->move_living("into the tent",FROOM + "tent",1,0);
}

void
give_it_back(object ob, object from)
{
    command("sigh sadly");
    command("say This is not what I was after.");

    if(!ob || !from)
    {
	return;
    }

    if(present(from, environment(this_object())))
    {
      command("give " + OB_NAME(ob) + " to " + OB_NAME(from));
    }
    else
    {
       command("drop "+OB_NAME(ob));
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("wine"))
    {
	set_alarm(1.0,0.0, &return_give_wine(from));
	return;
    }

    set_alarm(1.0,0.0, &give_it_back(ob, from));
    return;
}
