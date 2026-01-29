/*
 *  /d/Shire/gift/fuschia.c
 *
 *  Chief gift wrapper of Frogmorton.
 *  Cloned by /d/Shire/gift/giftshop.c
 *
 *  Author is unknown.
 *
 *  Modification Log:
 *  Deagol, June 2003 - revised, fixed a few bugs.
 *
 * 2003/06/15 Last update
 * 2011/08/01 Lavellan - Fixed spelling of name, made intro/known more normal
 */

#pragma strict_types
#pragma save_binary

inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/*
 *  Prototypes
 */
int	return_sigh(string who);
int	return_smile(string who);
void	return_introduce();
void	greet(object ob);
void	add_acts();

void
create_monster()
{
    if (!IS_CLONE)
    {
        return;
    }

    //set_name("fuschia");
    set_name("fuchsia");
    set_living_name("fuchsia");
    set_title("Mugwort, Chief Gift Wrapper");
    set_race_name("hobbit"); 
    set_adj(({"cheerful","busy"}));
    set_long("@@my_long@@");
    default_config_npc(30);
    set_base_stat(SS_CON, 39);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,30);
    set_pick_up(75);

    set_gender(G_FEMALE);

    set_aggressive(0);
    set_attack_chance(0);

    add_prop(CONT_I_WEIGHT, 80000);	/* 80 kg  */
    add_prop(CONT_I_VOLUME, 80000);	/* 80 ltr */
    //add_prop(LIVE_I_ALWAYSKNOWN, 1);

    add_acts();
}

void
add_acts()
{
    set_act_time(3);
    
    add_act("emote cleans the counter.");
    add_act("chuckle");
    add_act("emote organizes the wrapping paper, bows, and boxes.");
    add_act("emote smiles happily at you.");
    add_act("say Can I wrap something for you?");
    add_act("say Many hobbits come from all over for me to wrap their gifts");
    add_act("smile cheerfully");
    add_act("say I can wrap almost anything for you.");
    add_act("say Everyone loves getting gifts.");
    add_act("emote straightens up the shop.");
    add_act("say If you have any questions, read our sign.");
    add_act("say I can wrap gifts in many colors.");
    add_act("say Colored bows make a gift look very special.");
    add_act("say Can I help you with anything?");
    add_act("emote wraps a wonderful gift and sets it aside.");
    add_act("emote waits patiently for you.");
    add_act("emote sweeps the floor.");
}

void
greet(object ob)
{
    if (!CAN_SEE(this_object(), ob))
    {
        return;
    }

    command("say Hi there " + ob->query_nonmet_name() + ". " +
        "How can I help you?");
}

string
my_long()
{
    //if (notmet_me(this_player()))
    //{
    //    this_player()->add_introduced("fuschia");
    //}

    //return "This is Fuschia Mugwort, Chief Gift Wrapper of Frogmorton. " +
    return "This is Fuchsia Mugwort, Chief Gift Wrapper of Frogmorton. " +
        "She provides a very important service to hobbits because she " +
        "wraps many gifts for them. Because hobbits have so many parties " +
//        "and exchange many gifts, Fuschia decided to open a gift wrapping " +
        "and exchange many gifts, Fuchsia decided to open a gift wrapping " +
        "shop to make a little money. She's now one of the most popular " +
        "hobbits around which keeps her very busy.\n";
}

int
return_smile(string who)
{
    object ob;

    ob = present(who, environment());
    if (!ob)
    {
        return 0;
    }

    switch (random(4))
    {
        case 0 :
            command("smile");
            return 1;
        case 1 :
            command("smile " + who);
            return 1;
        case 2 :
            if (notmet_me(ob))
            {
                command("introduce myself to " + who);
                return 1; 
            }
            
            break;
    }

    return 0;
}

int
return_sigh(string who)
{
    if (!who)
    {
        return 0;
    }

    who = lower_case(who);
    if (random(3))
    {
        return 0;
    }

    command("say May I wrap something for you?");
    return 1;
}

int
add_introduced(string who)
{
    object ob;

    if (!who)
    {
        return 0;
    }

    who = lower_case(who);
    ob = present(who, environment());

    if (!ob)
    {
        return 0;
    }

    if (!CAN_SEE(this_object(), ob))
    {
        return 0;
    }

    if (!notmet_me(ob))
    {
        return 0;
    }

    if (!random(20))
    {
        return 0;
    }

    set_alarm(itof(random(9)), 0.0, &return_introduce());
    return 1;
}

void
return_introduce()
{
    command("introduce myself");
}

void
emote_hook(string emote, object actor, string averb = 0)
{
    string name = actor->query_real_name();

    switch(emote)
    {
        case "sigh"  :
            set_alarm(3.0, 0.0, &return_sigh(name));
            break;
        case "smile" :
            set_alarm(3.0,0.0,&return_smile(name));
            break;
    }
}

void
init_living()
{
    ::init_living();
 
    if (interactive(this_player()))
    {
        set_alarm(1.0,0.0,&greet(this_player()));
    }
}
