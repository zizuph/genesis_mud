/* Redin, the clothing shopkeeper of Kendermore, Gwyneth, May 1999 */

/* Added no attack prop, since the long description says the 
 * shopkeeper is standing behind the counter. This way
 * it also allows people to buy candy all the time.
 * -- Navarre 25th June 2006
 */

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

    set_name("redin");
    set_living_name("redin");
    set_race_name("kender");
    set_title("Piemaker of Kendermore");
    set_long("This chubby looking kender sells various types of " + 
             "candy, a weakness of kender everywhere. Judging by " + 
             "his plump cheeks and the lollipop sticking out of " + 
             "his mouth, he is very fond of sampling his own wares.\n"); 
    add_name("shopkeeper");
    set_adj("chubby");
    add_adj("red-haired");
    set_gender(G_MALE);
    set_introduce(1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and hands it " +
        "back, saying 'See, sometimes I do remember to return things!'\n");

    add_prop(OBJ_I_NO_ATTACK, "No! Who would then supply the candies?\n");

    set_stats(({80,100,80,90,90,100}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 75);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_WEP_KNIFE, 50);

    set_alignment(350);
    set_knight_prestige(-40);

    start_patrol();
    set_patrol_time(2);
    set_patrol_path(({"yawn",180,"say I need a mug of ale!","nw","sw","sw",
        "s","se","greet bobbin","say A mug of ale please!",
        "emote gets a foamy mug of ale.","lick",
        "emote downs a foamy mug of ale in one gulp.",
        "emote wipes the foam from his lips with his sleeve.","wave","out",
        "n","ne","ne","se","say Wow, that was a GOOD mug of ale!","hiccup",
        600}));

    set_act_time(5);
    add_act("crunch lollipop");
    add_act("crack whip");
    add_act("lick lollipop");
    add_act("emote chatters: What can I do for you?");
    add_act("smile impishly");
    add_act("emote chatters merrily about how much he loves candy.");

    set_cact_time(4);
    add_cact("emote shouts: Look! A dragon!\nYou " + 
        "turn to look, and your opponent ducks between your legs, " + 
        "kicking you in the behind.");
    add_cact("crack whip");

    set_default_answer("He seems to be too involved in his lollipop " + 
        "to answer your question.\n");
    add_ask(" [about] 'candy'", "emote chatters: They are the best " + 
        "made candy in Kendermore! Can I show you something?", 1);
    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : Arm me
 * Description : Clones, wears and wields misc. items, armours and weapons.
 * Returns : Null
*/

void
arm_me()
{
    setuid();
    seteuid(getuid(TO));
    clone_object(KOBJ + "lollipop")->move(TO);
    clone_object(KOBJ + "licorice")->move(TO);
    clone_object(KOBJ + "std_knife")->move(TO);
    clone_object(KOBJ + "hoopak")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);
    clone_object(KOBJ + "cloak")->move(TO);
    clone_object(KOBJ + "shirt")->move(TO);

    command("wear all");
    command("wield all");
}

