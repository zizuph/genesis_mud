/* Kender for Kendermore */

inherit "/d/Ansalon/common/monster/new_kender";

#include "../local.h"
#include <stdproperties.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <language.h>

public void
create_kender()
{
    int i = random(70);
    ::create_kender();
    add_act("@@kender_act2");
    set_long("@@kender_long");
    set_stats(({15 + i, 25 + i, 15 + i, 20 + i, 20 + i, 30 + i}));
    add_prop(LIVE_I_NEVERKNOWN, 1);
}

public string
kender_act2()
{
    int num = random(16);
    string beast;
    kender_extra_long();
    if (num == 15)
    {
        switch(random(4))
        {
            case 0:
                beast = "dragon";
                break;

            case 1:
                beast = "griffon";
                break;

            case 2:
                beast = "minotaur";
                break;

            case 3:
                beast = "centaur";
                break;
        }
    }

    switch(num)
    {
        case 0:
            command("emote chatters merrily about nothing in particular.");
            break;

        case 1:
            command("emote begins to look bored, never a good sign " + 
                "considering the mischievous nature of kender.");
            kender_walk();
            break;

        case 2:
            command("emote is filled with wonder about all the nice " + 
                "things here and eyes them curiously.");
            steal_something();
            break;

        case 3:
            if (gAdj == "whistling")
                command("emote whistles an uplifting melody.");
            else
                kender_act();
            break;

        case 4:
            if (gHair == "tied up in a topknot")
                command("emote tosses " + HIS(TO) + " " + gColour + 
                    " topknot over " + HIS(TO) + " shoulder.");
            if (gHair == "tied into a long braid")
                command("emote tosses " + HIS(TO) + " long " + gColour + 
                    " braid over " + HIS(TO) + " shoulder.");
            if (gHair == "pulled back in a pony tail")
                command("emote tosses " + HIS(TO) + " long " + gColour + 
                    " pony tail over " + HIS(TO) + " shoulder.");
            if (gHair == "left loose in a combed mane")
                command("emote tosses " + HIS(TO) + " loose " + 
                    gColour + " hair over " + HIS(TO) + " shoulder.");
            break;

        case 5:
            if (gAdj2 == "chubby")
                command("emote idly chews on a piece of candy.");

            if (gAdj2 == "wrinkled")
                command("emote smiles at you, wrinkles crinkling.");

            if (gAdj2 == "curious")
                command("emote chatters: Everyone says I'm too curious, " + 
                    "even for a kender! That's pretty curious isn't it? " + 
                    "Hey what's that shiny thing in your pocket?");

            if (gAdj2 == "friendly")
                command("emote shakes your hand, greeting you in a " + 
                    "friendly manner. You'd better check your " + 
                    "belongings.");

            if (gAdj2 == "bouncy")
                command("bounce all");

            if (gAdj2 == "talkative")
                command("emote chatters so much that you hold your hands " + 
                    "over your ears.");

            else
            {
                command("emote bumps into you.\nHmmm, are you sure " + 
                    "you're not missing anything?");
            }

            steal_something();
            break;

        case 6:
            if (gHair == "tied up in a topknot")
                command("emote hops up and down, making " + HIS(TO) + 
                    " " + gColour + " topknot fly into disarray.");
            if (gHair == "tied into a long braid")
                command("emote hops up and down, making " + HIS(TO) +
                    " long " + gColour + " braid fly into disarray.");
            if (gHair == "pulled back in a pony tail")
                command("emote hops up and down, making " + HIS(TO) +
                    " long " + gColour + " pony tail fly into disarray.");
            if (gHair == "left loose in a combed mane")
                command("emote hops up and down, making " + HIS(TO) +
                    " loose " + gColour + " hair fly into disarray.");
            break;

        case 7:
            command("emote hops up and down with endless energy.");
            kender_walk();
            break;

        case 8:
            command("emote closes " + HIS(TO) + " " + gEyes +
                " eyes as a cool breeze blows through " + HIS(TO) + 
                " " + gColour + " hair.");
            break;

        case 9:
            command("emote peers curiously at you with " + HIS(TO) + 
                " " + gColour + " eyes.");
            steal_something();
            break;

        case 10:
            command("emote looks up wide-eyed and says that awful word " + 
                "that sends most adventurers experienced with kender " + 
                "running, 'Oops!'.");
            kender_walk();
            break;

        case 11:
            command("emote looks at you with " + HIS(TO) + " wide " + 
                gEyes + " eyes.");
            break;

        case 12:
            command("emote gets a mischievous look in " + HIS(TO) + 
                " big " + gEyes + " eyes.");
            steal_something();
            break;

        case 13:
            command("emote blinks " + HIS(TO) + " bright " + gEyes + 
                " eyes.");
            break;

        case 14:
            command("say Hello there!");
            break;

        case 15:
            command("say Have you ever seen a " + beast + "? I saw one " + 
                "once!");
            break;
    }
    return "";
}

public void
arm_me()
{
    /* Random junk cloned into inventory. Add more in alpha order. */
    string *junk = ({(KOBJ + "bells"), (KOBJ + "brick"),
        (KOBJ + "butterscotch"), (KOBJ + "candle"),
        (KOBJ + "candlestick"), (KOBJ + "caramel"),
        (KOBJ + "carving"), (KOBJ + "cfeather"),
        (KOBJ + "cloth"), (KOBJ + "doll"),
        (KOBJ + "gbead"), (KOBJ + "licorice"),
        (KOBJ + "lollipop"), (KOBJ + "maple"),
        (KOBJ + "metal"), (KOBJ + "pbottle"),
        (KOBJ + "ring"), (KOBJ + "rock"),
        (KOBJ + "sbottle"), (KOBJ + "shell"),
        (KOBJ + "stone"), (KOBJ + "string2"),
        (KOBJ + "taffy"), (KOBJ + "map")});

    setuid();
    seteuid(getuid(TO));
    if (query_stat(1) > 69)
        clone_object(KOBJ + "std_knife")->move(TO);
    if (query_stat(1) > 39)
        if (query_stat(1) < 70)
            clone_object(KOBJ + "medium_knife")->move(TO);
    if(query_stat(1) < 35)
        clone_object(KOBJ + "small_knife")->move(TO);
    clone_object(KOBJ + "hoopak")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);
    clone_object(KOBJ + "cloak")->move(TO);
    clone_object(KOBJ + "vest")->move(TO);
    clone_object(junk[random(24)])->move(TO);
    clone_object(junk[random(24)])->move(TO);

    if (TP->query_gender() == G_FEMALE)
        clone_object(KOBJ + "blouse")->move(TO);
    else
        clone_object(KOBJ + "shirt")->move(TO);
    command("wear all");
    command("wield hoopak");

    seteuid(getuid(TO));
    MONEY_MAKE_SC(random(10)+5)->move(TO); /* A small amount of coins */
}

public string
kender_long()
{
    return("This is " + (LANG_ADDART(TO->short())) + " from " +
        query_kender_origin() + ", possibly just back from a long " + 
        "journey. A race " +
        "known on Krynn to be as bothersome as a mosquito, kender resemble " +
        "young teenage humans. They have childish faces and pointed ears. " +
        "Even after many years, a kender's only sign of age are wrinkles, " +
        "laugh lines, and perhaps a larger selection of taunts and stories. " +
        "Their insatiable curiousity is reminiscent of young children, " +
        "as is their ability to taunt and find mischief.\n");
}

