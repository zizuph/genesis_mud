/*
 *   /d/Gondor/minas/npc/faradan_noquest.c
 *
 *   A farmer of the Lossarnach - alternative before fall of Isengard.
 *
 *   Alto, 13 May 2001
 */


#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/lib/porter_defs.h"

#define INNER_MINAS "/d/Gondor/minas"
#define FANGORN_DIR "/d/Gondor/fangorn"


public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();
    set_adj("hard-natured");
    set_adj("grizzled");
    set_living_name("faradan");
    set_name("Faradan");
    add_name("farmer");
    add_name("faradan");
    set_race_name("human");

    set_title("of the Lossarnach");
    set_long("This is a farmer of the Lossarnach. His skin and hands "
        + "are worn and wrinkled from many years of work under the sun. "
        + "He looks like a pleasant fellow, and he smells of "
        + "good clean earth and oats.\n");

    rnd = random(60);
    default_config_npc(120+rnd/2);
    set_base_stat(SS_DIS, 140 + rnd);
    set_alignment(350+rnd*10);
    set_skill(SS_WEP_CLUB, MIN(100, 75 + rnd));
    set_skill(SS_WEP_POLEARM, MIN(100, 75 + rnd));
    set_skill(SS_PARRY, MIN(100, 75 + rnd));
    set_skill(SS_DEFENCE, MIN(100, 75 + rnd));
    add_prop(CONT_I_HEIGHT,170+rnd);
    add_prop(CONT_I_WEIGHT,85000+rnd*500);
    add_prop(CONT_I_VOLUME,80000+rnd*500); 

    setuid();
    seteuid(getuid());

    clone_object(INNER_MINAS + "/obj/faradan_rake.c")->move(TO);


    set_chat_time(15);
    add_chat("Welcome to my farm! Ahh, but how I love good hard work!");
    add_chat("I grow the finest oats in the South Kingdom!");
    add_chat("My brother Geradan is a big shot up in the city.");
    add_chat("I do not really have all day to stand here jawing with "
        + "strangers. The fields need tilling.");

    set_cchat_time(5);
    add_cchat("Bloody strangers! Why don't you leave an honest man "
        + "in peace?");
    add_cchat("Have you nothing better to do than murder a farmer?");
    add_cchat("Confound you! I'll beat you within an inch of your life!");

    set_act_time(7);
    add_act("scratch head");
    add_act("emote wipes his brow.");
    add_act("smile honestly");
    add_act("peer thoughtfully");
    add_act("emote picks some dirt from beneath a fingernail.");
    add_act("emote puts one finger aside his nose and shows you "
        + "how to use a farmer's hanky. How disgusting!");


    remove_prop(LIVE_I_NEVERKNOWN);

    set_default_answer( ({ "say Excuse me?", "cough incoherently" }) );


    add_ask_item(({"farm", "farming", "fields", "field"}), "say I have "
        + "farmed this land for "
        + "my entire life, as did my father before me and his father "
        + "before him. It is good, clean and honest work. My brother, "
        + "however, always did pine for the city life, and now he lives "
        + "up there.");
    add_ask_item(({"brother", "geradan", "Geradan"}), "say If ever you "
        + "travel to the Sixth Circle of Minas Tirith, perhaps you will "
        + "meet my brother. He is Master of the Royal Stables, you know!");
    add_ask_item(({"father"}), "say He was a good and trusty Lossarnachman.");
    add_ask_item(({"sixth circle", "minas tirith", "city"}), "say Have "
        + "you never visited the great city of Minas Tirith? I've been there "
        + "a few times to visit my brother, and it is quite impressive.");
    add_ask_item(({"stables", "royal stables"}), "say That is where "
        + "my brother works. Quite a fancified operation they have going "
        + "there, if you ask me. More than simple folk need concern "
        + "themselves with, but that is just my own opinion.");
    add_ask_item(({"rake"}), "say I use it to till the soil, but it also "
        + "comes in handy when ruffians come onto my property with "
        + "dishonest intentions.");
    add_ask_item(({"lossarnach", "Lossarnach"}), "say City folks seem "
        + "to look down their noses a bit at us simple people out here "
        + "farming the land. But they will not turn their noses up at our "
        + "grain with the war coming!");
    add_ask_item(({"grain"}), "say Well what did you think we were growing "
        + "out here?");
    add_ask_item(({"fertilizer"}), "say I use it to supplement the growth "
        + "of my oats. I have plenty at the moment.");
    add_ask_item(({"kingdom", "south kingdom", "South Kingdom"}), "say "
        + "Why the kindom of Gondor, of course. Where did you think you "
        + "were?");

    /* formerly quest related asks */

    add_ask_item(({"oat", "oats"}), "say I grow the best oats in the "
        + "South Kingdom!");
    add_ask_item(({"quest", "task", "job", "help"}), "say Thanks for "
        + "asking, Stranger, but I do not need any help at the moment.");
    add_ask_item(({"reward", "for reward", "about reward"}), "say Eh? What "
        + "did you do, catch a bank robber? Well go see the Militia, I have "
        + "nothing to do with such things!");
    add_ask_item(({"branch", "marsh oak", "oak"}), "say I don't really need "
        + "any at the moment, thank you.");
    add_ask_item(({"fangorn", "Fangorn", "forest"}), "say I hear it is "
        + "haunted! Not a safe place to be, especially if you mean harm "
        + "to the trees. Or so I have heard.");


    command("wield all");

    refresh_mobile();

}


public void
return_giggle(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        command("say What a happy soul. You would make a good farmer.");
        break;
    case 1:
        command("grin . "+ actor->query_real_name());
        break;
    case 2:
        command("smile . " + actor->query_real_name());
        break;
    default:
        break;
    }
}

public void
return_laugh(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
  	 return;

    switch (random(3))
    {
    case 0:
        command("say Nothing like a good laugh to make the work go faster.");
	       break;
    case 1:
	       command("grin . " + actor->query_real_name());
	       break;
    case 2:
        command("say You lighten my heart with your laugh, stranger.");
	       command("smile .");
	       break;
    default:
        break;
    }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (!objectp(actor) || !interactive(actor))
        return 0;

    switch (emote)
        {
        case "giggle":
	           set_alarm(2.0, 0.0, &return_giggle(actor));
	           break;
        case "laugh":
	           set_alarm(2.0, 0.0, &return_laugh(actor));
	           break;
    }
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}


public int
query_knight_prestige() { return -30; }

