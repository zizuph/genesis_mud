/*
 *    Faramir, Captain of Gondor and Protector of Ithilien
 *
 *    Original Incarnation:
 *    The master ranger for the Gondor company of the ranger guild
 *
 *    Based upon Elessar's creations of the master_ranger
 *
 *    Modification Log:
 *      Modified to use the new master ranger file
 *      - Olorin, 20-Jan-1995
 *      Moved and modified for new rangers code
 *      - Alto, 24-Feb-2002
 *      Modified by Tigerlily for recode and
 *          placed in /d/Gondor/guilds/rangers/ithilien/window.c
 *          --also removed calls from Damrod to old faramir
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "master_ranger.c";

#define     MASTER_RANGER_FILE (RANGERS_NPC + "faramir_save")
#define     CNO_ITHILIEN        1
#define     MR_I_CEREMONY      "_master_ranger_i_ceremony"

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
    set_living_name("faramir");
    set_name("faramir");
    set_adj(({"proud", "noble"}));
    set_company_no(1);
    set_title("Captain of Gondor and Protector of Ithilien");
    set_long("He is a pale-skinned man, dark of hair with grey eyes " +
      "and a strong face. You realize that he must be one of the " +
      "Dunedain of the South, a man of the line of the Lords of " +
      "Westernesse. Though proud and grim in demeanor, his eyes " +
      "seem full of sorrow.\nHe is wearing a leather pouch attached " +
      "to his belt.\n");

    add_prop(CONT_I_HEIGHT,208);
    add_prop(CONT_I_WEIGHT,95000);
        add_prop(LIVE_I_ALWAYSKNOWN, 1);
    set_size_descs("tall", "lean");

    set_skill(SS_WEP_SWORD,   100);
    set_skill(SS_WEP_MISSILE, 100);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_BRAWLING,    95);
    set_skill(SS_HEARING,     82);
    set_skill(SS_AWARENESS,   100);
    set_skill(SS_TRACKING,    100);
    set_skill(SS_LOC_SENSE,   100);
    set_skill(SS_LANGUAGE,    100);
    set_skill(SS_HUNTING,     60);
    set_skill(SS_ANI_HANDL,   40);
    set_skill(SS_SWIM,        62);
    set_skill(SS_CLIMB,       38);

    set_alignment(1100);

    set_chat_time(60);
    set_act_time(60);
    add_ask(({"about rangers","rangers", "rangers of ithilien",
              "Rangers of Ithilien", "rangers of Ithilien"}), 
        "say The Rangers of Ithilien are dedicated to harrying the " +
        "orcs and evil creatures that have overtaken our lands. " +
        "We protect the White City of Minas Tirith from the " +
        "Shadow in the East!", 1);
    add_ask(({"about duty","duty"}), "say Our Duty is to protect the Free " +
        "Peoples from the Evil One.", 1);

    add_ask(({"about enlisting", "ceremony", "enlistment", 
        "about enlistment", "about ceremony", "enlist" }), 
        &inform_enlist());
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

    set_alarm(5.0, 0.0, &command("say To enlist in Ithilien, " +
        "you must first be at least an approved apprentice " +
        "and without taint of evil in you."));
    set_alarm(10.0, 0.0, &command("say The members of the Ithilien " +
        "Company will vote to determine whether you are worthy " +
        "to join."));
    set_alarm(15.0, 0.0, &command("say If you should pass this test, " +
        "then you must come here with a Ranger of Ithilien who will " +
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

    clone_object(RANGERS_OBJ + "green_cloak")->move(TO);
    clone_object(RANGERS_OBJ + "shortbow")->move(TO);
    clone_object(RANGERS_OBJ + "quiver")->move(TO);
    clone_object(RANGERS_OBJ + "arrows")->move(TO);
    clone_object(RANGERS_OBJ + "ith_gauntlets")->move(TO);
    clone_object(RANGERS_ITH_EMBLEM)->move(TO, 1);
    command("wield sword");
    command("wear all");
    command("wield bow");
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
        "who have applied to the Ithilien company.");
    command("say You may also <view candidates> here to " +
        "list applicants.");
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
    add_act("emote scans the area, constantly vigilant.");
    add_act("rsing gondor");

    return 1;
}

