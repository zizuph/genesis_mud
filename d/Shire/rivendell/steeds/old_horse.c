// <Shire> Arandir: You will find the horses in my dir, in /w/arandir/_dragons/_monks/npc/horse.c

/*
 * File:     horse.c
 * Created:  Cirion, 1999.03.06
 * Purpose:  Horse for the monks
 * Modification Log:
 *    Manat 26 Dec 2000 Just a few small spelling changes.
 *
 * /d/Shire/rivendell/steeds/horse.c
 * Based on horse outside of Monks and Cavalry steed.
 * Intended for stables of Rivendell and sellable steeds to 
 * good-aligned players, mainly rangers and Noldor. Sorry, evil 
 * players must get their own horses elsewhere. ;)
 * -- Finwe, February 2002
 *
 */
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include "/d/Genesis/steed/new/steed.h"

inherit "/d/Genesis/steed/new/steed";
inherit "/d/Genesis/steed/new/feeding";
inherit "/d/Genesis/steed/new/saddlebag";
//inherit MONKLIB;
inherit "/std/act/action";

#define RAND_ONEOF(arr)      arr[random(sizeof(arr))]
//#define ENV(x)               environment(x)
//#include "/d/Terel/calathin/npc/terel_horse_saddlebag.c"
//#include "/d/Genesis/steed/new/saddlebag.c"
#include "composite.h"
#include "filter_funs.h"

string 
within()
{
    object *stuff;
 
    stuff = FILTER_DEAD(all_inventory(TO));
    if(!sizeof(stuff))
        return "emote twitches its shoulder.";
    else
    return "emote twitches its shoulder, "+
           "shifting "+COMPOSITE_DEAD(stuff)+
            " draped over its withers.";
}

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
        set_long("It is a " + color + " horse, reliable and strong. "+
           "It looks to be both well-fed and well-groomed. If it "+
           "likes you, you might be able to drape a pack over its "+
           "gleaming "+ color +" withers.\n");
    }
    else
    {
        set_name("mare");
        add_name("mare");
        set_short(desc + " " + color + " mare");
        add_name("horse");
        set_gender(G_FEMALE);
        set_stats(({ 80, 65, 82, 5, 80, 60 }));
        set_long("It is a " + color + " mare, reliable and strong. "+
           "She looks to be both well-fed and well-groomed. If she "+
           "likes you, you might be able to drape a pack over her "+
           "gleaming "+ color +" withers.\n");
    }

   set_act_time(10);
    add_act(VBFC_ME("horse_act"));
    add_act(VBFC_ME("within"));

    set_steed_allowed_food (({ "hay", "oats", "barley",
        "sugar", "grass", "fruit", "apple", "herb",
        "vegetable" }));

}


public int
can_lead(object living)
{
    // all these steeds can be lead
    return 1;
}
/*
string
horse_act()
{
    object env = environment(this_object());

    if(wildmatch(MONK_ROOM + "lawn*", file_name(env)))
    {
        return "emote nibbles at the high grass.";
    }
}
*/

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
                 RAND_ONEOF (({ "happily", "contentedly", "merrily",
                                "joyfully" })) +
                 ".");
        break;

    case "poke":
    case "kick":
    case "swear":
    case "swear":
    case "spit":
        command ("emote snorts " +
                 RAND_ONEOF (({ "angrily", "ill-temperedly", "unhappily",
                                "menacingly" })) +
                 ".");
        break;

    case "chastise":
        command ("emote hangs its head in shame.");
        break;
    }
}

void
init_living()
{
  add_action("do_fill", "fill");
  add_action("do_empty","empty");
  add_action("do_drape", "drape");
  add_action("do_remove","remove");
  add_action("do_close", "close");
  add_action("do_open", "open");

  ::init_living();
}