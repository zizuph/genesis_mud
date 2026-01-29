/*
 *  /d/Gondor/guilds/rangers/npc/aragorn.c
 *
 *  Aragorn, son of Arathorn, Chieftain of the Rangers of the North.
 *
 *  Coded by Alto, 15 July 2001
 *
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "master_ranger.c";

#define MASTER_RANGER_FILE RANGERS_NPC + "aragorn_save"
#define CO_NO              2
#define MR_I_CEREMONY               "_master_ranger_i_ceremony"


void           equip_me();
public string  inform_enlist();
public string  inform_member_vote();
public string  default_response();
public int     set_ceremony(int i);
public int     shut_up_mr();
public int     restart_chats();
public int     query_in_ceremony();

void
create_master_ranger()
{
    set_living_name("aragorn");
    set_name("aragorn");
    set_adj("long-shanked");

    set_company_no(CO_NO);
    set_master_ranger_file(MASTER_RANGER_FILE);
    set_title("the son of Arathorn, Chieftain of the Rangers of the North");

    set_long("This is the leader of the Rangers of the North. His features "
        + "are weathered by many long years living under the stars, and yet "
        + "he is handsome in an almost regal way. He has dark hair and "
        + "clever grey eyes, and when he looks at you it seems as though "
        + "he is looking straight into your heart. When he is not sitting "
        + "near the fire smoking a pipe, he can be seen striding around the "
        + "hideout at great pace on his long legs.\nHe is wearing a leather "
        + "pouch attached to his belt.\n");

    set_stats(({ 175, 175, 180, 173, 173, 180 }));

    add_prop(CONT_I_HEIGHT, 208);
    add_prop(CONT_I_WEIGHT, 95000);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY,     100);
    set_skill(SS_DEFENCE,   100);
    set_skill(SS_BRAWLING,  100);
    set_skill(SS_HEARING,   100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_TRACKING,  100);
    set_skill(SS_LOC_SENSE, 100);
    set_skill(SS_LANGUAGE,  100);
    set_skill(SS_HUNTING,   100);

    set_alignment(1100);

    set_company_no(CO_NO);
    add_ask(({"about rangers","rangers", "rangers of the north",
              "Rangers of Ithilien", "rangers of the North",
              "grey company", "Grey Company"}), 
        "say The Rangers of the North are dedicated to harrying the " +
        "orcs and evil creatures that have overtaken our lands. " +
        "We protect the people of the Shire and the lost realms.", 1);
    add_ask(({"about duty","duty"}), "say Our Duty is to protect the Free " +
        "Peoples from the Evil One.", 1);
    add_ask(({"about enlisting", "ceremony", "enlistment", 
        "about enlistment", "about ceremony" }), &inform_enlist());
    add_ask(({"about member vote", "voting for members", "apprentices", 
        "member vote", "vote", "voting", "member voting" }), 
        &inform_member_vote());
    set_default_answer(&default_response());
    restart_chats();

    equip_me();


}
string
inform_enlist()
{
    //don't answer if in the middle of ceremony
    if (query_in_ceremony())
    {
        write(TO->query_The_name(TP) + " signals to you for " +
            "silence.\n");
        return "";
    }

    set_alarm(5.0, 0.0, &command("say To enlist in the Grey Company, " +
        "you must first be at least an approved apprentice " +
        "and without taint of evil in you."));
    set_alarm(10.0, 0.0, &command("say The members of the Rangers of the " +
        "North will vote to determine whether you are worthy " +
        "to join."));
    set_alarm(15.0, 0.0, &command("say If you should pass this test, " +
        "then you must come here with a Ranger of the North who will " +
        "witness your oath."));
    set_alarm(20.0, 0.0, &command("say When you are ready, " +
        "you may <enlist in the company>."));
    return "";
}

void
init_living()
{
    ::init_living();
    set_stats(({ 150, 75, 250, 200, 150, 150}));
    set_hp(query_max_hp());
    set_ceremony(0);
}

int
equip_me()
{
    seteuid(getuid(TO));
    clone_object(RANGERS_OBJ + "grey_cloak")->move(TO,1);
    arm_me();
    command("wield sword");
    command("remove cloak");
    command("wear grey cloak");
    command("wear all");
}
    

string
inform_member_vote()
{
    //don't answer if in the middle of ceremony
    if (query_in_ceremony())
    {
        write(TO->query_The_name(TP) + " signals to you for " +
            "quiet.\n");
        return "";
    }
    command("say You may vote here for apprentices " +
        "who have applied to the Grey Company.");
    command("say You may also <view candidates> here to " +
        "see a list of current applicants.");
    return "";
}

string
default_response()
{
    //don't answer if in the middle of ceremony
    if (query_in_ceremony())
    {
        write(TO->query_The_name(TP) + " signals to you for " +
            "quiet.\n");
        return "";
    }
    command("say I have no information on that right now.");
    command("hmm");

    return "";
}

public int
set_ceremony(int i)
{
// either 0 = not in ceremony
// 1 = in ceremony at the moment
// so behave quietly.

    add_prop(MR_I_CEREMONY, i);

    if (i == 0)
        TO->restart_chats();
    else
        TO->shut_up_mr();
    return 1;
}

public int
query_in_ceremony()
{
    return query_prop(MR_I_CEREMONY);
}

public int
shut_up_mr()
{
    clear_chat();
    clear_act();
    write(TO->query_The_name(TP) + " signals to you for " +
            "silence.\n");
    return 1;
}


public int
restart_chats()
{
    clear_chat();
    clear_act();

    add_chat("We pay a high price for our freedom.");
    add_chat("Always be sure to cover your tracks when you approach the "
        + "hideout! The Enemy is searching for rumours of us.");
    add_chat("It is our way to travel incognito. Best that the Enemy does "
        + "not guess our true nature .. or our true numbers.");
    add_chat("The shadow in the East is growing.");
    add_act("emote looks at you piercingly, seeming to read your thoughts.");
    add_act("ponder");
    add_chat("Have a care when you travel today, my friend. Strange "
        + "customers have been calling on the Pony in Bree.");
    add_chat("I have seen many things in my travels. The shadow is "
        + "growing, never doubt that.");

    add_chat("I shall soon be departing on a mission of the gravest "
        + "importance to our cause. Keep the company vigilant in my "
        + "absence and be ready to ride at a moment's notice!");
    add_chat("Always be sure to cover your tracks when you approach the "
        + "hideout! The Enemy is searching for rumours of us.");
    add_chat("It is of the greatest importance that the little people "
        + "of the Shire do not know our true purpose. Protect them, but "
        + "leave them the peace of ignorance. Give them your true identity "
        + "in only the most dire of circumstances!");
    add_chat("It is our way to travel incognito. Best that the Enemy does "
        + "not guess our true nature .. or our true numbers.");
    add_chat("Keep the borders of the Shire safe. Always! We must never "
        + "drop our guard!");
    add_act("rsing gondor");
    add_act("rsing valimar");

    add_cchat("So, you think you can best me? Run while you can!");
    add_cchat("Scoundrel! How did you get in here?");
    add_cchat("Guards! Foe in the hideout!");
    return 1;
}
