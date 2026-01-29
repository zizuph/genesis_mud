inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_monster()
{
    if (!IS_CLONE)
	return;
    set_name("guard");
    add_name("rohirrim guard");
    set_race_name("rohirrim"); 
    set_living_name("rohirrim guard");
    set_adj("brave");
    set_short("rohirrim guard");
    set_long(break_string("This brave Rohirrim guard looks strong. His long braided long hair falls down onto his shoulders.\n",70));
    set_stats(({ 100, 115, 105, 90, 85, 140 }));
    set_alignment(150 + random(150));
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY,80);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_2H_COMBAT,60);
    set_skill(SS_AWARENESS, 70);
    seq_new("do_things");
    seq_addfirst("do_things", ({"say Reporting for duty!"}));
    set_chat_time(20);
    add_chat("Welcome to Edoras.");
    add_chat("Greetings traveller.");
add_cchat("Alarm! Invaders in Rohan!");
add_cchat("Help! Foes at the gate!");
add_cchat("Woe to you, deceiving enemy!");
    refresh_mobile();
}

arm_me()
{
    object wep, arm;

    seteuid(getuid(this_object()));

    wep = clone_object("/d/Gondor/rohan/edoras/obj/broadsword");
    wep->move(TO);
    command("wield broadsword");

    arm = clone_object("/d/Gondor/rohan/edoras/obj/chainmail");
    arm->move(this_object());
    command("wear chainmail");
}

/* Solamnian prestige */
query_knight_prestige() {return (-6);}

