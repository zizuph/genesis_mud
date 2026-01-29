inherit "/d/Gondor/rohan/edoras/npc/edoras_npc";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/edoras/defs.h"

void
create_citizen()
{
    set_chat_time(30);
    add_chat("The King may be old, but he is not as old as that "
      + "Wormtongue says.");
    add_chat("I would sign up to ride to war if the Red Arrow "
      + "arrived from the Mundburg.");
    add_chat("We owe the Stonelanders our aid if there is war.");
    add_chat("The weather has been good for the harvest.");
    add_chat("I saw a beauty of a horse the other day.");
    add_chat("So many strangers in Rohan lately.");
    add_chat("The King would never pay tribute to Mordor.");
    add_chat("Eomer is a good man, I heard his Eored have killed "
      + "Orcs somewhere in the East Mark.");
    add_cchat("Murderer!");
    add_cact("shout Help! Enemies in Edoras!");
    add_cact("emote backs away.");
    add_cact("emote looks around for help.");
    add_cact("emote slowly retreats.");
}

nomask void
create_edoras_npc()
{
    int     rnd1 = random(21),
            rnd2 = random(21);
    int     rnd3 = random(41);
    string  npc_gender = "";

    set_gender(random(2));

    if (query_gender())
    {
        add_name("woman");
        add_name("female");
        add_adj("female");
        add_pname("women");
    }
    else
    {
        add_name("man");
        add_name("male");
        add_adj("male");
        add_pname("men");
    }

    set_long("This is a regular citizen of Edoras. " + CAP(HE_SHE(TO)) + 
        " has golden hair like all the people of Rohan.");
    
//    set_long("This is a regular citizen of Edoras. "
//      + (query_gender() ? "She" : "He") + " has "
//      + "golden hair like all the people of Rohan.");
    set_adj("tall");
    add_adj("blond-haired");
    add_adj("rohirrim");
    set_stats(({ 25 + rnd3 + rnd1, 25 + rnd3 + rnd2, 25 + rnd3 + rnd1, 20 + rnd3, 10 + rnd3, 20 + rnd3 + rnd2 }));
    set_alignment(450 + random(150));
    set_skill(SS_WEP_KNIFE, 20 + rnd3);
    set_skill(SS_WEP_SWORD, 30 + rnd3);
    set_skill(SS_DEFENCE, 20 + rnd3);
    set_skill(SS_PARRY, rnd3);
    set_skill(SS_AWARENESS, 25 + rnd3);

    set_name("citizen");
    set_race_name("human");
    add_name("rohirrim");

    add_prop(CONT_I_HEIGHT,   170 + rnd1 + rnd2);
    add_prop(CONT_I_WEIGHT, 60000 + rnd1 * 2000);
    add_prop(CONT_I_VOLUME, 55000 + rnd1 * 2000);    

    set_adj(({"blond-haired", "proud"}));
    switch (rnd1+rnd2)
    {
        case 0..10:
            set_adj("short");
            break;
        case 11..29:
            break;
        case 30..40:
            set_adj("tall");
            break;
    }
    switch(rnd1)
    {
        case 0..4:
            set_adj("thin");
            break;
        case 5..15:
            break;
        case 16..20:
            set_adj("stocky");
            break;
    }

    add_prop(LIVE_I_NEVERKNOWN, 1);
    create_citizen();
    MONEY_MAKE_CC(10 + rnd1)->move(TO);
    MONEY_MAKE_SC(1 + rnd2 / 2)->move(TO);
}


void
arm_me()
{
    string *wep1, *arm1;
    FIX_EUID
    wep1 = ({ EDORAS_DIR + "obj/fknife", EDORAS_DIR + "obj/shortsword" });
    clone_object(wep1[random(sizeof(wep1))])->move(TO, 1);
    arm1 = ({ EDORAS_DIR + "obj/leather", EDORAS_DIR + "obj/leathcoat" });
    clone_object(arm1[random(sizeof(arm1))])->move(TO, 1);
    command("wield all");
    command("wear all");
}

/* solamnian prestige */
query_knight_prestige() {return (-5);}

