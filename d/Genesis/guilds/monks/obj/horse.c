/*
 * File:     horse.c
 * Created:  Cirion, 1999.03.06
 * Purpose:  Horse for the monks
 * Modification Log:
 *
 */
#pragma strict_types

#include "defs.h"
inherit "/d/Genesis/steed/steed";
inherit "/d/Genesis/steed/feeding";
inherit MONKLIB;
inherit "/std/act/action";


#define RAND_ONEOF(arr)      arr[random(sizeof(arr))]

void
create_steed()
{
    string  *colors = ({ "black", "brown", "white",
        "grey", "spotted" });
    string *descs = ({ "swift", "old", "lean", "muscular" });
    string  color = colors[random(sizeof(colors))];
    string  desc = descs[random(sizeof(descs))];

    set_race_name("horse");

    if(random(2))
    {
        set_name("horse");
        add_name("horse");
        set_short(desc + " " + color + " horse");
        set_gender(G_MALE);
        set_stats(({ 100, 45, 92, 5, 100, 60 }));
        set_long("It is a " + color + " horse, reliable and strong.\n");
    }
    else
    {
        set_name("mare");
        add_name("mare");
        set_short(desc + " " + color + " mare");
        add_name("horse");
        set_gender(G_FEMALE);
        set_stats(({ 80, 65, 82, 5, 80, 60 }));
        set_long("It is a " + color + " mare.\n");
    }

    set_act_time(10);
    add_act(VBFC_ME("horse_act"));

    set_allowed_food (({ "hay", "oats", "barley",
        "sugar", "grass", "fruit", "apple", "herb",
        "vegetable" }));

}


public int
can_lead(object living)
{
    // all these steeds can be lead
    return 1;
}

string
horse_act()
{
    object env = environment(this_object());

    if(wildmatch(MONK_ROOM + "lawn*", file_name(env)))
    {
        return "emote nibbles at the high grass.";
    }
}


public void
emote_hook(string emote, object actor, string adverb = 0)
{
    switch (emote)
    {
        case "pet":
        case "cuddle":
        case "ruffle":
        case "pat":
        case "kiss":
        case "lick":
        case "fondle":
            command ("emote whinneys " + 
                RAND_ONEOF (({ "happily", "contentedly", "merrily", "joyfully" }))
                + ".");
            break;

        case "poke":
        case "kick":
        case "swear":
        case "swear":
        case "spit":
            command ("emote snorts " +
                RAND_ONEOF (({ "angrily", "ill-temperedly", "unhappily", "menacingly" }))
                + ".");
            break;

        case "chastise":
            command ("emote hangs its head in shame.");
            break;
    }
}

