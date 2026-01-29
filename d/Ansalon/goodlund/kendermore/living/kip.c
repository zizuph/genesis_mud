/* Kip, the clothing shopkeeper */

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/act/action.c";
inherit AM_FILE

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("kipp");
    set_living_name("kipp");
    set_race_name("kender");
    set_title("Lightheart of Kendermore");
    set_long("This cheerful looking kender sells clothes that " + 
             "are a favourite of the locals. Her hair is tied up " + 
             "in a topknot, which is decorated with many beads and " + 
             "ribbons. She is concentrating " + 
             "on a pile of items on the counter, probably the contents " + 
             "of her various pockets and pouches.\n");
    add_name("shopkeeper");
    set_adj("brightly-clad");
    add_adj("cheerful");
    set_gender(G_FEMALE);
    set_introduce(1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and hands it " +
        "back, saying 'See, sometimes I do remember to return things!'\n");

    set_stats(({80,100,80,90,90,100}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_2H_COMBAT, 50);
    set_skill(SS_AWARENESS, 75);

    set_alignment(350);
    set_knight_prestige(-40);

    set_act_time(5);
    add_act("emote picks up a shiny object from the counter with a " + 
        "sparkle in her eye.");
    add_act("emote chatters: I sell the best clothes in Kendermore!");
    add_act("emote chatters: What can I do for you?");
    add_act("smile impishly");

    set_cact_time(4);
    add_cact("emote shouts: Look! A purple bellied gynosphynx!\nYou " + 
        "turn to look, and your opponent ducks between your legs, " + 
        "kicking you in the behind.\n");

    set_default_answer("She seems to be too involved in her scattered " + 
        "possessions to answer your question.\n");
    add_ask(" [about] 'clothes'", "emote chatters: They are very good " + 
        "quality! Can I show you something?", 1);
    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : Arm me
 * Description : Clones, wears and wields armours and weapons.
 * Returns : Null
*/

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
    clone_object(KOBJ + "blouse")->move(TO);

    command("wear all");
    command("wield all");
}

