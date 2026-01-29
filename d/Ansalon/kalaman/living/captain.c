#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM
inherit "/std/act/domove";
inherit "/lib/unique";

#define ADMIN     "/d/Krynn/solamn/vin/knight/admin/admin.c"

#define WEP1 KOBJ + "weapon/bastardsword"
#define WEP2 KOBJ + "weapon/iron_bastardsword"
#define WEP3 KOBJ + "weapon/g_bastardsword"
#define WEP4 KOBJ + "weapon/claymore"
#define ARM1 KOBJ + "armour/platemail"
#define ARM2 KOBJ + "armour/c_winged_helmet"
#define ARM3 KOBJ + "armour/gauntlets"
#define ARM4 KOBJ + "armour/leggings"

int gGuardsCalled = 0;

void
reset_monster()
{
    gGuardsCalled = 0;
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
        return;

    set_pick_up_team(({"guard"}));
    set_max_team_size_auto_join(4);

    set_name("baxter");
    add_name("captain");
    set_living_name("baxter");
    set_title("the Captain of the guard");

    set_adj("tall");
    add_adj("well-armoured");
    set_race_name("human");
    set_gender("G_MALE");
    set_long("Before you stands a tall well-armoured captain of the guard, stationed to protect " +
      "Kalaman's harbour and its inhabitants. His stern demeanour gives you the impression " +
      "he takes his job quite seriously. His penetrating eyes never seem to stop scanning his " +
      "surroundings.\n");

    set_stats(({105,145,145+random(10),75,75,118}));
    set_hp(10000);

    set_random_move(random(10) + 30);
    set_restrain_path(CITY);

    set_alignment(700);
    set_knight_prestige(-7);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 80);

    set_act_time(25);
    add_act("emote polishes his shiny armour to a prefect shine.");
    add_act("emote stares at you appraisingly.");
    add_act("say Reports say the red dragonarmy is getting closer.");
    add_act("say Reports say the blue dragonarmy is growing stronger.");
    add_act("emote looks about to check on the guards.");
    add_act("emote looks out towards the harbour.");

}

void
add_introduced(string name)
{
    command("introduce me to " + name);
}

void
arm_me()
{
    seteuid(getuid(TO));

//    clone_object(UNIQUE(WEP1, 3, UNIQUE(WEP2, 5, UNIQUE(WEP3, 5, WEP4))))->move(TO,1);

    if ( random(3) )
        clone_unique(WEP1, 4, ({ ({ WEP2, 80 }), 
                                 ({ WEP4, 40 }) }), 1)->move(TO, 1);
    else
        clone_unique(WEP3, 5, WEP2)->move(TO, 1);

    command("wield all");
    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    clone_object(ARM4)->move(TO,1);
    command("wear all");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

void
delayed_call_guards()
{
    object ob;
    
    ob = clone_object(KNPC + "elite_guard");
    ob->arm_me();
    ob->move(environment(TO));
    
    tell_room(environment(TO), QCTNAME(ob) + " rushes in.\n");
    ob->command("$assist " + OB_NAME(TO));
}

int
special_attack(object enemy)
{
    string str;
    
    if (random(5) || gGuardsCalled >= 4)
        return 0;
    
    switch (random(4))
    {
        case 0:
            str = "Guards! To me!";
            break;
        case 1:
            str = "We are under attack!";
            break;
        case 2:
            str = "Troublemakers in the city!";
            break;
        case 3:
            str = "To arms!";
            break;
    }
    gGuardsCalled++;
    command("emote shouts at the top of his lungs: " + str);
    set_alarm(itof(random(3)) + 1.5, 0.0, &delayed_call_guards());
    
    return 1;
}

public void
do_die(object killer)
{
    killer->set_alignment(killer->query_alignment() -400);

    ::do_die(killer);
}


void
attacked_by(object ob)
{
    if(ob->test_bit("Krynn", 1, 0))
    {
       (ADMIN)->perform_disgrace(ob, "Lord Gunthar","of an attack on Baxter, " +
              "the lawful captain of the guard protecting Kalaman",0);
    }

    ::attacked_by(ob);
}