inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"


void
create_monster()
{
    set_name("bibbles");
    set_living_name("_bibbles_");

    add_name(({"_old_milk_farmer_","farmer"}));
    set_race_name("hobbit");
    add_adj(({"old","rickety"}));
    set_long("Your heart goes out to this old rickety hobbit named " +
        "Bibbles. He is very very old, and walks with a severe " +
        "limp. It is hard to imagine how he ever gets around in " +
        "his poor condition.\n");

    set_alignment(100 + random(100));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_stats(({39,55,41,34,33,33}));
    set_skill(SS_DEFENCE, 45);
    set_skill(SS_WEP_KNIFE, 65);
    set_skill(SS_HERBALISM, 40);
    set_skill(SS_HIDE, 70);
    set_skill(SS_SNEAK, 63);


    MAKE_MONEY;
    set_act_time(10);
    add_act("emote grimaces as he pulls the cow along behind him.");
    add_act("emote limps quite noticeably.");
    add_act("grumble silently");
    add_act("search here for herbs");

    set_chat_time(4);
    add_chat("It's a shame to have to slaughter such a fine animal.");
    add_chat("I'm going to market.");
    add_chat("She doesn't give any milk anymore, so what can I do?");
    add_chat("Oh, woe is me.");
    add_chat("I've been a dairy farmer all my life.");
    add_chat("Grain is cheap nowadays.");
    add_chat("How are you, stranger?");
    
    add_ask(({"help","job","task","quest","cow","milk"}),VBFC_ME("ask_milk"));
    set_restrain_path(({"/d/Shire/common/hobbiton","/d/Shire/common/michel","/d/Shire/common/eastroad","/d/Shire/common/bree"}));
    set_random_move(5);

}

string
ask_milk()
{
    command("say Nothing can help me, really.");
    command("sigh sadl");
    command("think");
    set_alarm(15.0,0.0,"more_milk");
    return "";
}

string
more_milk()
{
    command("brighten");
    command("say Well, actually, there is something you can do to help.");
    command("say You can milk my cow for me.");
    command("say Otherwise she will die if she isn't milked, and ");
    command("say I can't allow that, so I'm taking her to market.");
    command("say I'm too weak and inflexible these days to milk her.");

    command("smile interest");
    return "";

}
