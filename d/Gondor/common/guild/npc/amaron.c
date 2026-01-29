/*
 *    The master ranger for the Gondor company of the ranger guild
 *
 *    Created by Elessar.
 *
 *    Modified to use the new master ranger file
 *    - Olorin, 20-Jan-1995
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/lib/master_ranger";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

#include "/d/Gondor/defs.h"

#define MASTER_RANGER_FILE RANGER_DIR+"lib/amaron_save"
#define CO_NO    1

public int  Reported = 0;

#define R_BIT(x)   (1 << x)
#define HENNETH_R   R_BIT(1)
#define ORCCAMP_R   R_BIT(2)
#define PELENNOR_R  R_BIT(3)
#define ROHAN_P_R   R_BIT(4)
#define ISENGARD_R  R_BIT(5)
#define PELARGIR_R  R_BIT(6)

#define REP_PLACES ({ "the Ithilien hideout", "the enemy encampment in Ithilien", \
    "the Pelennor fields", "the plains of Rohan", "Isengard", "Pelargir", })

#define DID_VISIT_HENNETH_ANNUN "_ranger_visited_henneth"
#define DID_VISIT_ORCCAMP "_ranger_visited_orccamp"
#define DID_VISIT_HARADCAMP "_ranger_i_did_visit_haradcamp"
#define DID_VISIT_ROHAN   "_ranger_visited_rohan"
#define DID_VISIT_PELARGIR "_ranger_visited_pelargir"
#define DID_VISIT_PELENNOR "_ranger_visited_pelennor"
#define DID_VISIT_ISENGARD "_ranger_visited_isengard"

void setup_chats();
string ask_about_reports();

void
create_master_ranger()
{
    set_living_name("amaron");
    set_name("amaron");
    set_adj("calm");

    set_company_no(CO_NO);
    set_company("Gondor");
    set_master_ranger_file(MASTER_RANGER_FILE);

    set_long(BSN(
        "He is a pale-skinned man, dark of hair, with grey eyes, "
      + "and a proud face. You realize that he must be one of the "
      + "Dunedain of the South, a man of the line of the Lords of "
      + "Westernesse."));

    set_stats(({ 75, 75, 80, 73, 73, 80 }));

    add_prop(CONT_I_HEIGHT,208);
    add_prop(CONT_I_WEIGHT,95000);

    set_skill(SS_WEP_SWORD,83);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,55);
    set_skill(SS_BRAWLING,95);
    set_skill(SS_HEARING,82);
    set_skill(SS_AWARENESS,45);
    set_skill(SS_TRACKING,75);
    set_skill(SS_LOC_SENSE,75);
    set_skill(SS_LANGUAGE,55);
    set_skill(SS_HUNTING,60);
    set_skill(SS_ANI_HANDL,40);
    set_skill(SS_SWIM,62);
    set_skill(SS_CLIMB,38);

    set_alignment(1100);

    setup_chats();

    add_ask(({"about rangers","rangers"}), "say We Rangers have but one "
      + "duty: To protect the Free Peoples from Evil!", 1);
    add_ask(({"about duty","duty"}), "say Our Duty is to protect the Free "
      + "Peoples from the Evil One!", 1);
    add_ask(({"to be quiet", "be quiet",}),
      VBFC_ME("asked_quiet"));
    add_ask(({"to chat", "stop being quiet", "chat", "to talk again", "to chat again"}),
      VBFC_ME("asked_end_quiet"));
    add_ask(({"reports", "report", "about reports", "about report",}),
      VBFC_ME("ask_about_reports"));
    add_ask(({"about ceremony", "ceremony", }), VBFC_ME("ask_ceremony"));
}

string
ask_ceremony()
{
    command("say Oh, ceremonies are so nice!");
    command("say If you want to hold one, just ask me to be quiet, and "
      + "I will be.");
    command("say I'll stay and watch though.");
    return "";
}

void
no_longer_quiet()
{
    command("say I believe I have kept quiet long enough now.");
    command("say If any officers disagree, just ask me to be quiet again.");
    setup_chats();
}

string
asked_quiet()
{
    if ((IS_RANGER(TP) || TP->query_name() == "Elessar") 
        && (TP->query_guild_leader_occ() || TP->query_ranger_mentor()
        || TP->query_wiz_level()))
    {
        command("say As you wish, I'll be quiet for now.");
        command("smile .");
        clear_chat();
        set_alarm(1800.0, 0.0, no_longer_quiet);
    }
    else
    {
        command("say to " + TP->query_real_name() + " I beg your pardon?");
        command("say With what authority do you come here asking me to shut up?");
        ask_about_reports();
    }
    return "";
}

string
asked_end_quiet()
{
    if ((IS_RANGER(TP) || TP->query_name() == "Elessar") && (TP->query_guild_leader_occ() || TP->query_ranger_mentor()
        || TP->query_wiz_level()))
    {
        command("say As you wish, I'll stop being quiet now.");
        command("grin merr");
        setup_chats();
    }
    else
    {
        command("say I only take orders from my officers.");
    }
    return "";
}

string
ask_about_reports()
{
    string  *reps, txt;
    int     i;
    reps = ({ });
    while (i < sizeof(REP_PLACES))
    {
        if (!(Reported & R_BIT(i+1)))
            reps += ({ REP_PLACES[i] });
        i++;
    }
    if (sizeof(reps))
    {
        txt = COMPOSITE_WORDS(reps);
        command("say I need reports about " + txt + ".");
    }
    else command("say I don't need any reports right now.");
    command("smile .");
    return "";
}


void
setup_chats()
{
    clear_chat();
    /* Check the status of the Osgiliath bridge and have a chat about that
     * if it is down */
    if (!(Reported & HENNETH_R))
        add_chat("We still have not heard from the Rangers of Ithilien.");
    if (!(Reported & ORCCAMP_R))
        add_chat("We do need information about the enemy camp in Ithilien.");
    if (!(Reported & PELENNOR_R))
        add_chat("Have you been to the Pelennor? Some have said orcs have "
          + "been seen crossing over the Anduin now.");
    if (!(Reported & ROHAN_P_R))
        add_chat("The plains of Rohan are not safe for travel, rumours from the "
          + "Rohirrim have it that orcs have been seen there in great numbers.");
    if (!(Reported & ISENGARD_R))
        add_chat("I do fear that Saruman the White might be up to something, but "
          + "I have not heard any reports about Isengard in a while.");
    if (!(Reported & PELARGIR_R))
        add_chat("There has been no news from Pelargir for some time. Some people "
          + "fear the Black Fleet may be on the move.");
}

void
reset_report(int report_no)
{
    Reported = Reported - report_no;
    setup_chats();
}

void
add_report(int report_no)
{
    Reported = Reported | report_no;
    set_alarm(3600.0, 0.0, &reset_report(report_no));
    setup_chats();
}

void
enchant_seed()
{
    command("say An old ranger is living in a hut somewhere in this");
    command("say forest - he is our main supply of herbs. I've had");
    command("say word with him, and he said he needed help.");
    command("say Go and seek him out east from the end of the old");
    command("say forgotten road in the forest.");
}

string
inform_gondor()
{
    command("say Gondor is a beautiful land.");
    command("say Our main problem is the Enemy in the East.");
    command("say How can we live peacefully when large armies are "
      + "mustering to attack us?");
    command("sigh");
    return "";
}

public void
fake_report()
{
    command("say Well, you did not have much new to report.");
    command("say Have you really been there recently?");
}

public int
deliver_report(string str)
{
    string  dummy;
    if (!strlen(str))
        NFN0("Report about what?");
    str = LOW(str);
    if (sscanf(str, "about %s", dummy) != 1)
    {
        command("say What did you want to report about?");
        command("eyebrow interest");
        return 1;
    }
    write("You give Amaron a brief report.\n");
    say(QCTNAME(TP) + " gives " + QTNAME(TO) + " a brief report.\n");
    if (R_COUNCIL->query_captain(TP->query_real_name()))
        command("say Thank you, Captain!");
    switch(dummy)
    {
    case "orccamp":
    case "the orccamp":
    case "ithilien":
        if (TP->query_prop(DID_VISIT_HARADCAMP)
            || TP->query_prop(DID_VISIT_ORCCAMP))
        {
            command("say Thank you! I was wondering about that enemy camp.");
            add_report(ORCCAMP_R);
            TP->remove_prop(DID_VISIT_ORCCAMP);
            TP->remove_prop(DID_VISIT_HARADCAMP);
        }
        else
        {
            fake_report();
        }
    break;
    case "the rangers of ithilien":
    case "ithilien hideout":
    case "the ithilien hideout":
    case "rangers of ithilien":
    case "henneth":
    case "henneth annun":
        if (TP->query_prop(DID_VISIT_HENNETH_ANNUN))
        {
            command("say I am glad to hear an update from Henneth Annun.");
            add_report(HENNETH_R);
            TP->remove_prop(DID_VISIT_HENNETH_ANNUN);
        }
        else
        {
            fake_report();
        }
    break;
    case "pelargir":
        if (TP->query_prop(DID_VISIT_PELARGIR))
        {
            command("say Good, Pelargir is still safe.");
            add_report(PELARGIR_R);
            TP->remove_prop(DID_VISIT_PELARGIR);
        }
        else
        {
            fake_report();
        }
    break;
    case "rohan":
    case "rohan plains":
    case "plains of rohan":
        if (TP->query_prop(DID_VISIT_ROHAN))
        {
            command("say I feared the plains were not quite safe. Thanks for the report.");
            add_report(ROHAN_P_R);
            TP->remove_prop(DID_VISIT_ROHAN);
        }
        else
        {
            fake_report();
        }
    break;
    case "isengard":
    case "orthanc":
        if (TP->query_prop(DID_VISIT_ISENGARD))
        {
            command("say That's interesting news from Isengard indeed.");
            add_report(ISENGARD_R);
            TP->remove_prop(DID_VISIT_ISENGARD);
        }
        else
        {
            fake_report();
        }
    break;
    case "pelennor":
    case "pelennor fields":
    case "the pelennor fields":
        if (TP->query_prop(DID_VISIT_PELENNOR))
        {
            command("say Good, the Rammas Echor is still whole.");
            add_report(PELENNOR_R);
            TP->remove_prop(DID_VISIT_PELENNOR);
        }
        else
        {
            fake_report();
        }
    break;
    default:
        ask_about_reports();
    break;
    }  
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(deliver_report, "report");
}

