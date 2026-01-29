inherit "/d/Gondor/common/npc/npc_ranger";
inherit "/d/Gondor/common/lib/friend_or_foe";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

string *
random_color()
{
    switch(random(7))
    {
    case 0:
      return ({ "scarred", "dark-haired" });
      break;
    case 1:
      return ({ "calm", "grey-eyed" });
      break;
    case 2:
      return ({ "tall", "dunadan" });
      break;
    case 3:
      return ({ "strong", "dunadan" });
      break;
    case 4:
      return ({ "muscular", "dark-eyed" });
      break;
    case 5:
      return ({ "young", "lean" });
      break;
    case 6:
      return ({ "slender", "dunadan" });
      break;
    }
}

public void
test_fighting()
{
    if (!query_attack())
    {
        command("say " + ONE_OF_LIST(({"I am heading out again.",
            "I believe it's safe for me to leave now.", "I will check by later!",})));
        say(QCTNAME(TO) + " leaves out the door.\n");
        remove_object();
    }
    else set_alarm(200.0, 0.0, test_fighting);
}

public void
create_ranger()
{
    string *adjs;
    adjs = random_color();
    set_name("ranger");
    add_name("_ranger_guard");
    set_race_name("human");
    add_adj(adjs);
    set_stats(({ 100 + random(50), 110 + random(50), 110 + random(50),
        90 + random(40), 80 + random(50), 100 + random(40) }));
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENSE, 80);
    set_skill(SS_PARRY, 70);
    set_alignment(1000);
    add_prop(CONT_I_HEIGHT, 215);
    add_prop(CONT_I_WEIGHT, 76000);
    add_cchat("By Gondor!");
    add_cchat("For our friends!");
    add_cchat("For the Steward!");
    add_cchat("Begone, foul creature!");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_company("Ithilien");
    set_agg_ranger();
    set_alarm(200.0, 0.0, test_fighting);
}

public int
arm_me()
{
    object tmp;
    if (random(3))
        tmp = clone_object(WEP_DIR + "r_lsword");
    else
        tmp = clone_object(WEP_DIR + "r_brsword");
    tmp->move(TO);
    command("wield all");
    if (random(3))
        tmp = clone_object(ARM_DIR + "studlarm");
    else
        tmp = clone_object(ARM_DIR + "gchainmail");
    tmp->move(TO);

    command("wear all");
}

void
check_enemy(object tp)
{
    if (!agg_ranger) 
        return;
    if (query_friend_or_foe(tp) < 0)
    {
        if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, TP)) 
        {
            command("battle "+tp->query_real_name());
            command("brawl");
        }
    }
}

public void
init_living()
{
    ::init_living();
    if (!agg_ranger) 
        return;
    set_alarm(0.0, 0.0, &check_enemy(TP));
}

