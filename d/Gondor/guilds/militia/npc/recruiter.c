/*
 * /d/Gondor/guilds/militia/npc/recruiter.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Recruiter for Thornlin Militia
 *
 * Coded by Auberon and Gwyneth
 */
inherit "/d/Gondor/std/monster";

#include "../attackers.c"
#include "../militia.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

string *gIntroduced = ({});

void
create_gondor_monster()
{
    set_name("mardil");
    set_title("the Toughened Veteran of the Thornlin Militia");
    add_name("recruiter");
    add_name("man");
    set_race_name("human");
    set_long("He is a rather serious, but distracted man. He is the " +
        "recruiter for the Thornlin Militia.\n");
    set_short("serious distracted male human");
    set_adj(({"serious", "distracted"}));
    default_config_npc(100);
    set_skill(SS_WEP_POLEARM, 50);

    set_skill(SS_AWARENESS,   65);
    set_skill(SS_HIDE,        25);
    set_skill(SS_DEFENCE,     50);
    set_skill(SS_PARRY,       50);
    set_skill(SS_APPR_MON,    50);
    set_alignment(350);
    set_money(({ random(20), random(10), random(5), random(2) }));
    set_equipment(({ (TOBJ + "cloak"), (TOBJ + "hauberk"), 
        (TOBJ + "gauntlets") }));
    add_ask_item(({"militia", "thornlin militia"}),
        "say We are the Thornlin Militia! We protect our town from " +
        "invading orcs, goblins and wolves.");
    add_ask_item(({"resign", "leave", "leave militia", "leave guild"}),
        "say If you really wish to leave, you may 'resign'. Of course, " +
        "there will be a penalty.");
    add_ask_item(({"join", "enlist", "join militia", "full", "full time",
        "part", "part time", "layman", "occupational"}), 
        "say We do accept outsiders in our Militia, " +
        "provided they have not attacked our town or otherwise made trouble " +
        "for the free people elsewhere in Middle Earth. We do not admit " +
        "Solamnian Knights, as they are too involved in their own wars " +
        "to worry about Thornlin much. Of course, we can only accept " +
        "trustworthy people into our ranks. To join our ranks part time, " +
        "simply 'enlist part time'. You can also 'enlist full time' if you " +
        "wish to join another part time guild. Full and part time benefits " +
        "are identical. If you are already a member, and wish to switch " +
        "between full and part time, you may 'enlist full/part time'.");
    add_ask_item(({"orcs", "goblins", "wolves", "wolf", "goblin", "orc"}),
        ({"scowl", "say They are servants of the East!", 
          "say There seem to be more of the East's foul servants about lately.",
          "say I've killed many in my day!"})); 
    add_ask_item(({"boots", "guild item", "new boots"}), "say You may " +
        "request new boots from me if you have lost your old ones.\n");
    set_default_answer( ({ "say I'm not sure I know what you're talking about.",
        "say Ask someone else, I can't say.", "emote is lost in thought.",
        "say Are you here to enlist?" }) );
}

void
intro_me(object name)
{
    if (member_array(capitalize(name->query_real_name()), gIntroduced) == -1)
    {
        command("say to " + OB_NAME(name) + " A pleasure to meet you!");
        command("introduce me to " + OB_NAME(name));
        gIntroduced += ({ capitalize(name->query_real_name()) });
    }
}

void
add_introduced(string str)
{
    object who = find_living(str);
    string name = capitalize(who->query_real_name());

    if (member_array(name, gIntroduced) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
