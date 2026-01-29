/*
* Varian - December, 2016
*/

inherit "/std/monster";
inherit "/d/Shire/common/auto_teaming";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include "../../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/common/lib/logkill.c"

#define ARM "/d/Shire/common/trollsh/arm/"
#define WEP "/d/Shire/common/trollsh/weapon/"
#define HILL_DIR "/d/Shire/common/trollsh/hill/"

int alarm_id;

string *weapons = ({WEP + "dsword", WEP + "dclub", WEP + "daxe"}); 
string *helmets = ({ARM + "dhelm"});
string *body = ({ARM + "dchain" });
string *shield = ({ARM + "dshield"});
string *arms = ({ARM + "dbracers"});
string *legs = ({ARM + "dgreaves"});

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("donald");
    add_name("don");
    set_race_name("troll");
    set_adj("orange-skinned","ugly");
    set_stats(({280, 250, 350, 220, 220, 170}), 20);
    set_alignment(-1000);

    set_restrain_path(({HILL_DIR}));
    set_monster_home(({HILL_DIR + "hill1"}));
    set_random_move(20);

    set_pick_up_team(({"troll"}));

    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_PARRY,90);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_SWIM,90);

    set_gender(G_MALE);

    set_chat_time(14);
    
    add_chat("I am the best fighter! Nobody is better than me!");
    add_chat("I hate those elves!");
    add_chat("This is my forest, whatcher doing here?");
    add_chat("When I sees an elf, I just grabs them by the neck!");
    add_chat("I know a good recipe for squashed elf, but almost anything " +
        "squashed would do!");
    add_chat("There are too many stinking elves passing through my " +
        "forest! I should build a wall, nobody builds walls better than me!");

    add_ask(({"task","tasks"}),VBFC_ME("ask_task"));
    add_ask(({"help", "job"}),VBFC_ME("ask_help"));
    add_ask(({"quest","quests"}),VBFC_ME("ask_quest"));
    add_ask(({"elf","elves"}),VBFC_ME("ask_elf"));
    add_ask(({"troll","trolls","trollshaws","forest"}),VBFC_ME("ask_troll"));

    set_default_answer(VBFC_ME("default_answer"));

    add_prop(NPC_I_NO_UNARMED,1);
    add_prop(LIVE_I_SEE_DARK,4);
    add_prop(NPC_I_NO_FEAR,1);

    set_act_time(16);

    add_act("emote scratches his chin in thoughtful contemplation.");
    add_act("emote turns to the east and stares off in the distance with " +
        "a grim expression on his face.");
    add_act("emote swings his hands in the air, attempting to swat a fly.");
    add_act("emote pauses to look at you, attempting to assess your " +
        "motives.");
    add_act("brood");
    add_act("cough");
    add_act("greet all");
    add_act("ponder");
    add_act("worry");

    equip(({ 
        one_of_list(weapons),
        one_of_list(helmets),
        one_of_list(body),
        one_of_list(shield),
        one_of_list(arms),
        one_of_list(legs),
    }));

}

public int query_knight_prestige() { return 500; }

string
ask_task()
{
    command("say A task? Whatcher means by that?");
    command("ponder");
    command("say It might be fun to squeeze and squish those elves that " +
        "live near the mountains!");
    command("grin evil");
    return "";
}

string
ask_help()
{
    command("say I might need some help killing those blasted elves " +
        "which comes into my forest!");
    command("emote squints his eyes and stares at you intently.");
    return "";
}

string
ask_quest()
{
    command("say Whatcher mean by quests? Can you eats them?");
    return "";
}

string
ask_elf()
{
    command("say Those blasted elves live near the mountains, hidden " +
        "inside their tricksy valley! I would like to squeeze their " +
        "skinny necks!");
    return "";
}

string
ask_troll()
{
    command("say I am a troll and this is my forest! Whatcher want, should " +
        "I squeeze your neck too?");
    return "";
}


public string
default_answer()
{
   string  answer = one_of_list( ({
        "I doesn't know anything like that!",
        "Whatcher mean asking a thing like that?",
        "Stop bothering me! Go away before I squeeze your runty neck!",
        "Nobody but a ninny would ask a question like that!",
        "You talk too much!",
        "Go away now!" }) );
    command("emote looks at you strangely.");
    command("say " + answer);
    return "";
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say Oh ho! Whatcher know, I gots a live one!");
    command("wield all");
    command("wear all");
    /*add_prop(LIVE_O_ENEMY_CLING, obj);*/
}
void
attack_object(object obj)
{
    ::attack_object(obj);
    command("say You isn't going to get away so easily!");
    /*add_prop(LIVE_O_ENEMY_CLING, obj);*/
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}