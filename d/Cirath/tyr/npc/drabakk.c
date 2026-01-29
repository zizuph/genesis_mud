/* drabakk.c: The guy in charge of the noble restaurant in Tyr.
 *     Drabakk used to Pandora's butler, but he turned her in 
 *       when he had the chance.--Serpine, 4-23-95.
 */
 
#pragma strict_types
 
inherit "/d/Cirath/std/monster";
#include "defs.h"

void
create_monster()
{
    ::create_monster();
    set_name("drabakk");
    set_title("the Manager of the Senators' Hall");
    set_adj("old");
    add_adj("stooped");
    set_race_name("human");
    set_long("This grizzled old soul is dressed in clean clothes. His "+
             "fingers have greenish stains, but otherwise he is extremely "+
             "well-groomed. He is hunched over as if accustomed to working "+
             "on his knees, but tries to hide it by sheer force of will. "+
             "The workers seem to be following his guidance.\n");
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_stats(({50, 40, 60, 30, 10, 50}));
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 40);
    set_skill(SS_WEP_AXE, 70);

    set_alignment(0);
    set_assist_cry("I don't appreciate you killing customers.");
    add_act("emote is handed some money by a noble and pockets it.");
    add_act("emote orders some serving girls around.");
    add_act("emote whispers into a noble's ear.");
    add_act("' This is no place for ruffians.");
    add_act("' If you make trouble I will call the Templars.");
    add_act("' Feel free to sample the cuisine, if you can afford it.");
    add_cact("' Perhaps its better this way.");
    add_cact("shout GUARDS! GUARDS! COME TO THE HALL!");
    add_cact("' You are making some very wealthy enemies.");
    add_cact("' Perhaps you would look better as a newt?");

    set_act_time(8);
    set_cact_time(3);

    set_default_answer("What a naive question.\n");
    add_ask("pandora", "Please don't bring up that name. I would like the "+
            "past to remain dead.\n");
    add_ask(({"fingers", "stains", "stain", "hunch", "knees"}), "There was "+
            "a time I served as an enslaved gardener in a templar's garden. "+
            "Time has a way of changing things.\n");
    add_ask(({"garden","templar's garden"}), "My former employer had a "+
            "love of shrubs...and riddles...curse her.\n");
    add_ask(({"hall", "senators' hall"}), "I bought it with money from...My "+
            "savings...Quite a bargain I must say.\n");

}

void
arm_me()
{
    clone_object(TYR_WEP+"axe_ston.c")->move(TO);
    clone_object(TYR_ARM+"body_fin.c")->move(TO);
    clone_object(TYR_ARM+"legs_lth.c")->move(TO);
    command("wield all");
    command("wear all");
}
