/* Sarr */
#include "defs.h"
inherit STD_MONSTER;
inherit "/d/Raumdor/lib/intro";

void
create_monster()
{
    string adj, desc;
    ::create_monster();

    if (random(2))
    {
        set_gender(G_FEMALE);
        set_name(one_of_list(({
          "debbie", "nathshik", "jennifer", "elain", "jasmine", "sandra",
          "kristin", "amy", "laura", "sylvia", "sunshine", "effie", "stacey",
          "pamela",
        })));
        set_stats(({40, 60, 40, 80, 90, 80}));
        add_act("emote fixes her hair.");
        add_act("emote checks on the fire.");
        add_act("emote says: Hello, stranger.");
        add_act("blush");
        equip(({
          DRAKMERE_ARM_DIR + "c_skirt", DRAKMERE_ARM_DIR + "c_shirt",
          DRAKMERE_ARM_DIR + "c_sandals", DRAKMERE_ARM_DIR + "c_necklace",
        }));
        desc  = "woman";
        adj = one_of_list(({
          "slim", "buxom", "lovely", "beautiful",
        }));
    }
    else
    {
        set_gender(G_MALE);
        set_name(one_of_list(({
          "rajok", "murtaza", "ajaja", "gren", "tamalon", "zarr", "anthor",
          "similirien", "wong", "uthangton", "ian", "smine", "retron",
          "bobak",
        })));
        set_stats(({80, 90, 90, 50, 44, 80}));
        add_act("emote peers around.");
        add_act("say What are you doing in my house?");
        add_act("emote fastens his boots.");
        add_act("emote mubles a prayer.");
        equip(({
          DRAKMERE_ARM_DIR + "c_pants", DRAKMERE_ARM_DIR + "c_boots",
          DRAKMERE_ARM_DIR + "c_shirt.c", DRAKMERE_ARM_DIR + "c_cross",
          DRAKMERE_WEP_DIR + "c_dagger",
        }));
        desc = "man";
        adj  = one_of_list(({
          "tall", "stout", "strong", "short",
        }));
    }
    add_name(desc);
    add_adj(adj);
    set_race_name("human");
    set_short(adj + " " + desc);
    set_long("@@citizen_long");
    set_title("citizen of Drakmere");
    set_alignment(1000);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_DEFENCE, 40);
}

string
citizen_long()
{
    if (query_gender() == G_FEMALE)
    {
        set_alarm(1.0, 0.0, &command("$smile " + OB_NAME(TP)));
        return "This is one of the many citizens of Drakmere. She seems " +
               "young and healthy, as she moves around with some vigor. She " +
               "notices you and smiles at you.\n";
    }
    else
    {
        set_alarm(1.0, 0.0, &command("$peer " + OB_NAME(TP)));
        return "This is one of the many citizens of Drakmere. He stares at " +
               "you suspiciously. He is strong and healthy looking.\n";
    }
}
