/* Jenna, the candle shopkeeper, Gwyneth, June 1999 */

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

    set_name("jaena");
    set_living_name("jaena");
    set_race_name("kender");
    set_title("Nettlekettle, the Candlemaker of Kendermore");
    set_long("This talkative kender is wearing a wax-covered apron. " + 
             "Her gray hair is tied back in a tight topknot. Despite " + 
             "her slightly disheveled appearance, she seems rather " + 
             "chipper.\n");
    add_name("shopkeeper");
    set_adj("wax-covered");
    add_adj("talkative");
    set_gender(G_FEMALE);
    set_introduce(1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and hands it " +
        "back, saying 'See, sometimes I do remember to return things!'\n");

    set_stats(({80,100,80,90,90,100}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_2H_COMBAT, 50);
    set_skill(SS_CLIMB, 50);

    set_alignment(350);
    set_knight_prestige(-40);

    start_patrol();
    set_patrol_time(2);
    set_patrol_path(({"yawn",180,"w","sw","s","s","w","sw","s","sw",
        "greet vincint","climb wall","wave","ne","n","ne","e","n","n","ne",
        "e","smile all"}));


    set_act_time(5);
    add_act("emote chatters: I have the best deals in Kendermore!");
    add_act("emote chatters: What can I do for you?");
    add_act("smile impishly");
    add_act("emote dips a string into some hot wax.");
    add_act("emote chatters merrily about all her adventures.");

    set_cact_time(4);
    add_cact("emote shouts: Look! An enraged minotaur!\nYou " + 
        "turn to look, and your opponent ducks between your legs, " + 
        "kicking you in the behind.");

    set_default_answer("She seems to be too involved in her candles " + 
        "to answer your question.\n");
    add_ask(" [about] 'candles'", "emote chatters: They are very good " + 
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


