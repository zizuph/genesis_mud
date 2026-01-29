/* The innkeeper for the Scorched Scorpion Inn. Gwyneth, 05/17/99 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("bobbin");
    add_name("innkeeper");
    set_race_name("kender");
    set_adj("loud");
    set_title("Butterberry of Kendermore");
    set_introduce(1);
    add_adj("silver-haired");
    set_gender(G_MALE);
    set_long("You can tell this kender must be very old by his many " + 
             "wrinkles and silvery hair, but he chats as merrily with " + 
             "his patrons as a young kender would. He must find this a " + 
             "very interesting job since he hasn't wandered out of " +
             "Kendermore yet.\n"); 

    set_alignment(300);
    set_knight_prestige(-50);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and hands it " +
        "back, saying 'See, sometimes I do remember to return things!'\n");

    set_skill(SS_DEFENCE, 60);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_AWARENESS, 60);

    set_stats(({150, 150, 150, 70, 70, 150}));
    set_hp(query_max_hp());
    set_act_time(5);
    add_act("emote roars with laughter as a patron tells a joke.");
    add_act("emote chatters to another kender: No money? Well, what's " + 
            "that shiny thing " + 
            "in your pocket? I might be willing to take that instead!");
    add_act("emote picks something up from the floor and casually slips " + 
            "it into one of his pouches.");

    set_cact_time(5);
    add_cact("emote throws a beer in your face.");

    set_default_answer("I don't know about that, but it sounds " + 
        "interesting!\n");

    set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    setuid();
    seteuid(getuid(TO));
    clone_object(KOBJ + "std_knife")->move(TO);
    clone_object(KOBJ + "hoopak")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);
    clone_object(KOBJ + "cloak")->move(TO);
    clone_object(KOBJ + "shirt")->move(TO);
    clone_object(KOBJ + "lime")->move(TO);

    command("wear all");
    command("wield all");
}

