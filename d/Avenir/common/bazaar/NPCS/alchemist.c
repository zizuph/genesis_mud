// /d/Avenir/common/bazaar/NPCS/alchemist.c
// Lilith 19Feb97
// Based upon: /d/Avenir/common/bazaar/NPCS/herbmerchant.c &
//             /d/Gondor/common/guild/npc/herbalist.c
// note:       
// purpose:    Part of the expansion of the apothecary complex.
//             This npc can identify potions

#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Avenir/inherit/intro";

/* I want to know what people are asking, for add_ask development.
 * Be sure to remove this after a few weeks of implementation. */
inherit "/d/Avenir/inherit/log_asks";

#include "../bazaar.h"
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>

static object  given_aitems;
static int     test_id_alarm_id;
/* Prototypes */
int test_identify(object item, object from);

void not_idscroll(object item, object from);
void not_aitems(object item, object from);
void give_back_immediately(object item, object from);

string
my_long()
{
    string long_str;
    long_str = "This is the alchemist for the Sybarus Bazaar.\n"+
        "There is something about her eyes that makes her seem older "+
        "than she appeared at first glance. A faint tracery of lines "+
        "webs their corners, and a mocking light twinkles in their "+
        "dark depths.";
    return long_str + "\n";
}

void
create_monster()
{
    set_name("liselea");
    add_name(({"alchemist","sorceress"}));
    set_race_name("human");
    set_title("the Veteran Alchemist");
    set_adj("dark-eyed");
    set_adj("slender");
    set_gender(G_FEMALE);
    set_long(my_long());
    set_stats(({ 55, 55, 60, 99, 98, 55 }));

    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT,63000);
    add_prop(CONT_I_HEIGHT,184);
//    add_prop(OBJ_S_WIZINFO, );

    set_skill(SS_AWARENESS, 85);
    set_skill(SS_DEFENCE,   65);
    set_skill(SS_ALCHEMY,   95);
    set_skill(SS_HERBALISM, 65);


    set_chat_time(7);
    add_chat("You would not have any unknown potions, would you?");
    add_chat("I think I have seen most potions in the world by now.");
    add_chat("If you have an unknown potion, you can let me identify it for you.");
    add_chat("I deal exclusively in potions and scrolls.");
    add_chat("I cannot identify a scroll without reading it, and in "+
       "some cases, reading a scroll can destroy it or activate its "+
       "magical properties.");
    add_chat("I was amanuensis to Seer Jisawe for several years. I learned to "+
       "write from him.");
    add_chat("I was apprenticed to the Master on the Holm, and he taught "+
       "me the ways of alchemy and the writing of magical scrolls.");
    add_chat("Lessons are not without their price.");
    add_chat("We serve the gods, all of us, be we highborn or low.");
    add_chat("I heard Plalgus visited Judgement on someone today. Did "+
        "you see him?");
    add_chat("My apprenticeship was arduous and very unpleasant, but "+
       "I learned quickly and so was spared the Master's wrath.");
    add_chat("I'm interested in scrolls from other lands.");

    set_cchat_time(2);
    add_cchat("Beware! Or I shall taunt you a second time!");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"potion","potions"}), VBFC_ME("ask_potions"));
    seteuid(getuid());

}

void
arm_me()
{
   seteuid(geteuid(this_object()));
   MONEY_MAKE_SC(random(40))->move(this_object());

   clone_object(HOLM + "obj/burnous")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pouch_belt")->move(TO, 1);
   command("wear all");
}

public void
enter_inv(object item, object from)
{
    int     ran;

    ::enter_inv(item, from);
    if (!objectp(from))
        return;

    if (!item->id("potion") && !item->id("scroll")) 
    {
        set_alarm(1.0, 0.0, &not_aitems(item, from));
        return;
    }
    if (given_aitems || test_id_alarm_id)
    {
        set_alarm(1.0, 0.0, &give_back_immediately(item, from));
        return;
    }
    if (item->id("scroll"))
    {
        set_alarm(1.0, 0.0, &not_idscroll(item, from));
        return;
    }
    test_id_alarm_id = set_alarm(5.0, 0.0, &test_identify(item, from));
    return;
}

void
not_aitems(object item, object from)
{
    command("say I deal in potions and scrolls, nothing else.");
    command("say This is of no interest to me, "+ 
        ((from->query_gender() == G_MALE) ? "mister" : "madam")+ ".");
    command("give " + OB_NAME(item) + " to "+ from->query_real_name());
}

void
give_back_immediately(object item, object from)
{
    command("say Just one moment, "
      + ((from->query_gender() == G_MALE) ? "sir" : "my lady")+".");
    command("give " + OB_NAME(item) + " to "
      + from->query_real_name());
}

void
not_idscroll(object item, object from)
{
    command("say It is unfortunate, but I cannot identify scrolls "+
        "without first reading them...");
    command("say And that can have unforseen consequences for both "+ 
        "of us, "+((from->query_gender() == G_MALE) ? "mister" : "madam")+ ".");
    command("say I cannot identify this scroll, but I would be happy "+
       "to assist you in identifying a potion.");
    command("give " + OB_NAME(item) + " to "+ from->query_real_name());
}

int
test_identify(object item, object from)
{
    object  player;
    string  id_str,
            find_str;

    given_aitems = item;
    player = from;
    tell_room(environment(), QCTNAME(TO)+" looks closely at the "+
       given_aitems->query_short() + ".\n");
    command("ponder");
    switch(given_aitems->query_id_diff() / 10)
    {
        case 0:
            command("smirk");
            id_str = "Child's play.";
            break;
        case 1:
            command("giggle");
            id_str = "You're pulling my leg, right?";
            break;
        case 2:
            command("smile .");
            id_str = "I know this. Some people often mistake "
              + "it for another.";
            break;
        case 3:
            command("smile .");
            id_str = "I've seen this one a lot. Easily mistaken though.";
            break;
        case 4:
            command("smile .");
            id_str = "Ah - I can't blame you for not recognizing "
              + "this one.";
            break;
        case 5:
            command("smile thought");
            id_str = "Ah - I can't blame you for not recognizing "
              + "this one.";
            break;
        case 6:
            command("think");
            id_str = "One must be skilled in alchemy to identify "+
                "this one.";
            break;
        case 7:
            command("think");
            id_str = "One must be skilled in alchemy to identify "+
                "this one.";
            break;
        case 8:
            command("think");
            id_str = "One must be skilled in alchemy to identify "+
                "this one.";
            break;
        case 9:
            command("emote grinds her teeth.");
            id_str = "I'm not positive, mind you, but I'm fairly "+
                "confident I know what it is.";
            break;
        case 10:
            command("scream");
            id_str = "I've never come across this before. I don't "+
                "know if I can identify it!";
    }
    command("say " + id_str);
    if (given_aitems->do_id_check(TO))
        command("say " + given_aitems->query_id_long());
    else
        command("say I can tell you that without a doubt, this "+
            given_aitems->query_short() + " is completely unknown "+
            "to me.");
    command("give " + OB_NAME(given_aitems) + " to "+ 
        player->query_real_name());
    command("say I hope my information has been useful, "+
      ((player->query_gender()==G_MALE) ? "sir" : "madam") + ".");
    command("curtsey");
    given_aitems = 0;
    test_id_alarm_id = 0;
    return 1;
}

string
ask_potions()
{
    command("say Potions?");
    command("say I'm familiar with quite a lot of them.");
    command("say You can buy some from me, and I sell scrolls, too.");
    command("say If you have an unknown potion, I can try to identify"+
        " it for you.");
    return "";
}

string
default_answer()
{
    command("say I am not permitted to discuss that.");
    return "";
}
