/*
 * kato.c
 *
 * Used in wild/c1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* The black monk Kato. He might give an evil
* player a small task. Made by: Joshua 941225
* with a good deal of help from Glindor among others 
*
* Updated: 950304 Jakob
*
*/

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

int roseq, fatq, grassq;
string *paint_name;

void monk2(object tp);
void monk3(object tp);
void tasks1(object tp);
void tasks2(object tp);
void quest(object tp);
void quest1(object tp);
void quest2(object tp);
void quest3(object tp);
void quest4(object tp);

void
create_monster()
{
    roseq = fatq = grassq = 0;
    paint_name = ({});
    set_name(({"kato", "",}));
    set_title("lesser servant of the Presence");
    set_race_name("human");
    set_adj(({"evil", "smirking", "sadistical"}));
    set_long("This black-clad humanoid only slightly resemble " +
             "a human - his limbs are twisted and grotesque, " +
             "and you can only just make out the contours of his face, " +
             "hidden beneath his dark hood. He is smirking sadistically " +
             "at you, his evil intentions readily apparent.\n");
    set_gender(0);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_2H_COMBAT, 75);
    set_alignment(-600);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    /* str dex con int wis dis */
    set_stats(({110, 110, 110, 70, 70, 75}));

    set_chat_time(5 + random(7));  /* the time between speaking */
    add_chat("he he he");
    add_chat("I am a genius, only a fool would deny that!");
    add_chat("Ah, I need a volunteer...");
    add_chat("I have a task for you.");
    add_chat("Hurumpf, I want to teach those merry monks a lesson. " +
             "I dont like merry people. "); //FIXA
    add_chat("My master will undo the creation, by reverting the " +
             "seven sacraments! ");

    set_cchat_time(3 + random(5));  /* as above, obs random! */

    add_cchat("Fool! Can't you see that even if you kill me there " +
              " will be another one to come.");
    add_cchat("You might be able to kill me, but you " +
              "will never be able to annhilate evilness as such.");

    set_act_time(5 + random(15));
    add_act("grin");
    add_act("laugh");
    add_act("smirk");
    add_act("growl");

    add_ask(({"task", "quest"}), VBFC_ME("tasks"));
    add_ask(({"sacrament", "sacraments"}), QCTNAME(TO) + " says: The"
            + " baptism is the first sacrament. \n");
    add_ask("baptism", QCTNAME(TO) + " says: Once you are baptised you"
            + " are protected... \n");
    add_ask(({"monk", "dragon", "black", "monks", "priest", "priests",
              "lesson"})
            ,VBFC_ME("monk1"));
    trig_new("%w 'introduces' %s", "react_introduce"); //FIXA
    seteuid(getuid());
}

string
monk1()
{
    int i;
    if (this_player()->query_alignment() >= 0)
    {
        command("puke");
        command("say I don't want any help from goodie goodies as you. ");
        command("finger");
        return "";
    }
    set_this_player(TP);
    if (QDONE(ROKEGROUP, PAINTQUEST))
    {
        command("say You have already painted the dragon for me!");
        return "";
    }
    if (member_array(TP->query_real_name(), paint_name) != -1)
    {
        command("say Bah, I have already given you paint!");
        return ("");
    }

    if (TP->query_alignment() < 0)
    {
        say(QCTNAME(TO) + " whispers something to " + QCTNAME(TP) + "\n");
        TP->catch_msg(QCTNAME(TO) + " says: Yes he he we have to make " +
                      "some fun of them " +
                      "...listen carefully now... \n");
        set_alarm(4.0, 0.0, &monk2(this_player()));
        return ("");
    }
}

void
monk2(object tp)
{
    set_this_player(tp);
    say(QCTNAME(TO) + " whispers something to " + QCTNAME(tp) + "\n");
    tp->catch_msg(QCTNAME(TO) + " says: I see a cute dragon " +
                  " and I want it painted black! \n");
    set_alarm(4.0, 0.0, &monk3(tp));
}

void
monk3(object tp)
{
    set_this_player(tp);
    say(QCTNAME(TO) + " whispers something to " + QCTNAME(tp) + "\n");
    tp->catch_msg(QCTNAME(TO) + " says: he he doesn't that sound fun?\n");
    tp->catch_msg(QCTNAME(TO) + " gives you a can with paint.\n");
    clone_object(ROKEDIR + "obj/can")->move(tp);
    paint_name += ({tp->query_real_name()});
    return;
}

string
tasks()
{
    if (this_player()->query_alignment() > -1)
    {
        command("puke");
        command("say I don't want any help from goodie goodies as you. ");
        command("finger");
        return ("");
    }

    say(QCTNAME(TO) + " whispers something to " + QCTNAME(TP) + "\n");
    TP->catch_msg(QCTNAME(TO) + " says: Hmm, you look like the right one " +
                  "...listen carefully now... \n");
    set_alarm(4.0, 0.0, &tasks1(this_player()));
    return ("");
}

void
tasks1(object tp)
{
    set_this_player(tp);
    say(QCTNAME(TO) + " whispers something to " + QCTNAME(tp) + "\n");
    tp->catch_msg(QCTNAME(TO) + " says: Bring me a rose, some " +
                  "hallucinating grass and a piece of fat fom a child not " +
                  "yet being baptised.\n");
    set_alarm(4.0, 0.0, &tasks2(tp));
    return;
}

void
tasks2(object tp)
{
    set_this_player(tp);
    say(QCTNAME(TO) + " whispers something to " + QCTNAME(tp) + "\n");
    tp->catch_msg(QCTNAME(TO) + " says: Do this, and I will reward " +
                  "you handsomely! \n");
    return;
}

void
equip_me()
{
    clone_object(ROKEDIR + "arm/cloak.c")->move(this_object());
    clone_object(ROKEDIR + "wep/orc_knife.c")->move(this_object());//FIXA
    clone_object(ROKEDIR + "wep/orc_knife.c")->move(this_object());//FIXA
    command("wear all");
    command("wield all");
}

void
react_introduce()
{
    set_alarm(2.0, 0.0, "intro");
}

void
intro()
{
    command("introduce myself");
}

void
droppa(object to)
{
    command("drop " + OB_NAME(to));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!from)
        return;
    if (from->query_alignment() > -1)
    {
        command("grin");
        command("say Sorry I dont trust you enough to " +
                "accept things from you.");
        set_alarm(2.0, 0.0, &droppa(ob));
        return;
    }
    
    if (ob->id("grass"))
    {
        grassq = 1;
        command("say He he my favourite grass.");
        command("wink");
    }

    if (ob->id("fat"))
    {
        fatq = 1;
        command("say Poor child.");
        command("grin sad");
    }

    if (ob->id("rose"))
    {
        roseq = 1;
        command("say A thing of beauty is a joy forever!");
        command("laugh evilly");
    }

    if (roseq == 1 && fatq == 1 && grassq == 1)
    {
        roseq = fatq = grassq = 0;
        set_alarm(2.0, 0.0, &quest(TP));
    }
}

void
quest(object tp)
{
    tp->catch_msg(QCTNAME(TO) + " says: Well done " + QCTNAME(tp) + ", well " +
                  "done..\n");
    tell_room(environment(), QCTNAME(TO) + " puts the rose, " +
              "grass and the greasy piece of fat in his " +
              "left palm. He mumbles an incantation...\n");
    set_alarm(4.0, 0.0, &quest1(tp));
}

void
quest1(object tp)
{
    set_this_player(tp);
    tell_room(environment(), QCTNAME(TO) + " closes his left palm.\n");
    command("shiver");
    tell_room(environment(), QCTNAME(TO) + " open his hand again, and " +
              "to your surprise you discern a jewel in his hand!\n");
    set_alarm(4.0, 0.0, &quest2(tp));
}


void
quest2(object tp)
{
    command("say he he The power is mine!\n");
    set_alarm(4.0, 0.0, &quest3(tp));
}


void
quest3(object tp)
{
    set_this_player(tp);
    command("grin " + OB_NAME(tp));
    command("say Fool! Here is your reward! \n");
    say(QCTNAME(TO) + " gives 1 copper coin to " + QCTNAME(tp) + "\n");
    tp->catch_msg(QCTNAME(TO) + " gives 1 copper coin to you. \n");
    MONEY_MAKE_CC(1)->move(tp);

    set_alarm(5.0, 0.0, &quest4(tp));
}

void
quest4(object tp)
{
    set_this_player(tp);
    if (!QDONE(ROKEGROUP, POTIONQUEST))
    {
        tp->catch_msg("You feel more experienced!\n");
        tp->add_exp(POTIONQUESTXP);
        QSET(ROKEGROUP, POTIONQUEST);
        QLOG("Kato quest");
    }
}

int
query_knight_prestige()
{
    return 200;
}
