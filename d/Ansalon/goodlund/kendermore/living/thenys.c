/* Thenys Thistleknot, Bottle Collector of Kendermore*/
/* Not working */
/* Gwyneth, June 1999 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/act/action.c";
inherit AM_FILE

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("thenys");
    set_short("nimble-fingered red-haired male kender");
    set_living_name("thenys");
    set_race_name("kender");
    set_title("Thistleknot of Kendermore");
    set_adj("nimble-fingered");
    add_adj("red-haired");
    set_gender(G_MALE);
    set_introduce(1);

    set_stats(({80,100,80,90,90,100}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_2H_COMBAT, 50);


    set_alignment(350);
    set_knight_prestige(-40);

    set_act_time(5);
    add_act("smile impishly");
    add_act("emote chatters merrily about all his adventures.");
    add_act("emote chatters: I just love bottles! They're so very " + 
        "interesting!");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_default_answer("He is looking at something in his pouch with " +
        "great interest, and doesn't hear your question.\n"); 
    add_ask(({"bottles", "bottle"}), "emote chatters: I collect them!",1);
    trig_new("%w 'arrives' %s", "intro_delay");
/*    set_alarm(0.0,0.0,"arm_me"); */
}

void
arm_me()
{
    clone_object(KOBJ + "std_knife")->move(TO);
    clone_object(KOBJ + "hoopak")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);
    clone_object(KOBJ + "cloak")->move(TO);
    clone_object(KOBJ + "shirt")->move(TO);

    command("wear all");
    command("wield all");
}

void
give_bottle(object from)
{
    string who;

    who = from->query_real_name();

    command("emote chatters: A bottle! Thank you! Here, take this.");
    MONEY_MAKE_GC(random(2)+2)->move(who); 
    command("give coins to " + who);

}

void
give_it_back(object ob, object from)
{
    string what,
    who;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("yawn");
    command("emote chatters: That's not very interesting to me.");
    command("drop " + what);
}
    
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("bottle"));
    {
        set_alarm(1.0,0.0, &give_bottle(from));
        return;
    }

    if(ob->id("_knife_") || ob->id("_clothes_") || ob->id("_hoopak_"));
        return;

    set_alarm(1.0,0.0, &give_it_back(ob, from));
        return;
}

/* Function name : Introduction delay
 * Description : Gives a second and a half delay before introduction to new
 *     arrivals.
 * Returns : Null
*/

void
intro_delay()
{
    set_alarm(1.5,0.0,"introduce_to_arrival");
}

/* Function name : Introduction
 * Description : Introduces to new arrivals
 * Returns : Null
*/

void
introduce_to_arrival()
{
    command("introduce myself");
}


