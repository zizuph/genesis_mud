/* -*- Mode: C -*-
 *
 * assassin.c
 *
 * Skippern 20(c)02
 * 
 * The assassin is a quest npc.
 */
inherit "/std/monster";

inherit "/d/Gondor/common/lib/binbit"; /* the binbit code */

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

#define EMOTE_ARR   ({ "think", "grin", "sigh", "hide", "smile sini", "nod", \
                       "emote listens for sounds.", "pace", "hide", \
                       "hide", "hide", "hide", "emote looks suspeciusly around." })

/* Prototypes */
         void    do_my_act();
         void    get_armed();
public   int     give_task();
private  void    humptidumpt(object ob);
         void    default_answer();

void
create_monster()
{
    FIX_EUID;

    set_living_name("arguck");
    set_name("arguck");
    add_name( ({ "human", "assassin" }) );
    set_adj("tall");
    add_adj("black-haired");
    set_long("This tall black-haired human looks very suspicious. He hides " +
	     "as best he can and does all he can to be silent.\n");
    set_alignment(-950);
    set_gender(G_MALE);

    default_config_npc(80);
    set_base_stat(SS_DEX, 95);
    set_skill(SS_WEP_SWORD, 45);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_HIDE, 100);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_BACKSTAB, 50);
    set_skill(SS_ACROBAT, 50);


    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(OBJ_I_HIDE, 25);

    set_default_answer(&default_answer());
    add_ask( ({ "task", "quest", "job" }), &give_task(), 1);

    set_restrain_path( ({ DOL_SEWER }) );
    set_monster_home(DOL_SEWER+"g-05");
    set_random_move(10+random(50));

    set_chat_time(500+random(100));
    add_chat("Good the guards are gone, they make me jumpy.");
    set_act_time(10+random(100));
    add_act(&do_my_act());

    get_armed();
}

void
get_armed()
{
    clone_object(DOL_WEP + "dagger")->move(TO);
    clone_object(DOL_ARM + "cloak")->move(TO);
    command("wear all");
    command("wield all");
}

void
default_answer()
{
    command("say I have no idea of what you are talking about.");
    return;
}

/*
 * Function name:    enter_inv
 * Description  :    mask parent to catch herbs.
 * Arguments    :    object ob -- the entering object
 *                   object from -- source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->id("SomethingCutFromANobel"))
    {
	return;
    }
    if (ob->id("ArguckAssassinItem"))
    {
	return;
    }
    set_alarm(1.0, 0.0, &humptidumpt(ob));
}

/* This function is here to delay the hiding of the item */
private void 
humptidumpt(object ob)
{
    command("say I am not interested in your "+ob->query_short()+".");
    //command("give "+ob->query_name()+" to "+from->query_name());
    command("hide "+ob->query_name());
}

void
do_my_act()
{
    command(one_of_list(EMOTE_ARR));
}

void
tell_me_about_task(object tp)
{
    string name = tp->query_name();
    object token;

    command("whisper to "+name+" Now listen carefully. I will " +
	    "say this only once");
    command("emote clears his throat to whisper more clearly.");
    command("whisper to "+name+" Sir Isaac have an my lucky charm. " +
	    "He denies it tough, but I know he have it.");
    command("emote looks around to ensure nobody is listening.");
    command("whisper to "+name+" I would be grateful if you could " +
	    "get it back for me.");
    command("say to "+name+" Now be on your way.");

}

public void
introduce_me(object pl, string name)
{
    command("say Shhhhhh! Not so loud " + capitalize(name) +".");
    command("introduce me to "+name);
    command("grin evil");
    command("whisper to "+name+" Maybe you can do something for me, " + 
	    capitalize(name) +"?");
}

public void
add_introduced(string name)
{
    object    pl;

    command("emote looks up and down the tunnel to ensure nobody is " +
	    "listening.");

    set_alarm(2.2, 0.0, &introduce_me(pl, name) );
}

public int
give_task()
{
    object tp = this_player();
    
    if (present("I_do_quest_token.c", tp))
    {
        command("say I have no more tasks for you.\n");
	return 1;
    }

    set_alarm(4.0, 0.0, &tell_me_about_task(tp));
    command("say Come closer and listen carefully.");

    return 1;
}

/*
 * Function name:    oke_to_move
 * Description  :    Checks whether the npc is fighting someone, if he is in
 *                   in combat, the move-command will be delayed till the
 *                   war is over.
 * Arguments    :    exit  : the exit that is generated for the monster to 
 *                           take.
 * Returns      :    0     : if in combat
 *                   string: the exit that the monster takes if not in combat.
 */
mixed
oke_to_move(string exit)
{
    if (this_object()->query_attack())
        return 0;

    /* By adding sneak before the exit, we make the npc sneak out it instead
     * of its normal behaviour of walking.
     */
    return "sneak "+exit;
}





