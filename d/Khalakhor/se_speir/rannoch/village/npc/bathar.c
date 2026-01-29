/* File         : /d/Khalakhor/se_speir/rannoch/village/npc/bathar.c
 * Creator      : Darragh@Genesis
 * Date         : 00-11-04      
 * Purpose      : Npc in the Loch Rannoch area.
 * Related Files: 
 * Comments     : Based on Murah
 * Modifications: 
 */

#pragma strict_type

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"

inherit STDHUMAN;
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";

mapping remembered;
object pub;
object last_attacker;
string kitchen;
int return_alarm_id,
    attacker_alarm_id,
    has_armed;

public int
my_communicate(string str)
{
    string temp;

    if (temp = TO->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	write(stringp(temp) ? temp : "You are gagged and cannot " +
	  "speak.\n");
    }

    tell_room(environment(), QCTNAME(TO) + " " + VBFC_ME("race_sound") +
      ": " + str + "\n");
}
/*
 * Function name: arm_me
 * Description  : Clones in the landlord's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
arm_me()
{
    if (has_armed)
        return;

    seteuid(getuid());

    clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
    clone_object("/d/Khalakhor/common/arm/apron")->move(TO);
    clone_object("/d/Khalakhor/common/wep/mace")->move(TO);
    command("wield all");
    command("wear all");
    has_armed = 1;
}
public void
create_khalakhor_human()
{
    set_name("bathar");
    set_living_name("bathar");
    add_name("landlord");
    add_name("man");
    set_adj("bearded");
    add_adj("old");
    cs_set_sept("Cormack");
    cs_set_clan("MacFaolain");
    cs_set_title("Landlord of the Walkway Pub");
    set_long("This old man must have lived a rich life, "
           + "by the looks of his scars, and wise eyes. "
           + "The enormous amount of trophies and fishing "
           + "memorabilia on the walls hints at his former "
           + "profession as well as chosen theme for his pub.\n"
           + "He has scars on his nose, left cheek, forehead "
           + "and chin.\n"
           + "He has wise deep blue eyes.\n"
           + "His hair is short, grey, and parting in the middle.\n");  

    default_config_npc(40);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_PARRY, 15);
    set_skill(SS_WEP_CLUB, 50);

    set_alignment(400);
    set_exp_factor(40);
    set_size_descs("short", "lean");
    remembered = ([]);
    set_alarm(0.5, 0.0, arm_me);

    set_m_in("arrives limping");
    set_m_out("limps");

    set_default_answer("Can't help you there, I'm afraid.");
    add_ask(({"pub","bar","walkway pub"}),
              "say This pub? I thought I'd settle down here after "
            + "my brilliant career, running a quiet little pub on "
            + "the edge of the village. But people seem to like "
            + "coming here, sharing fishing stories and having a "
            + "drink while watching the lake from the terrace. "
            + "I'm no rich man, but I'm happy.",1);
    add_ask(({"terrace","balcony"}),
              "say Building that balcony above the walkway was my best "
            + "idea for a long time. Heh, saves me the trouble of "
            + "providing entertainment. It's a nice view, I'll admit.",1);
    add_ask(({"animal","animals","stuffed animal","stuffed animals",
               "fishing trophy","fishing trophies","hunting trophy",
               "hunting trophies"}),
              "say What you see on them walls are some of my most famous "
            + "catches. Aye, people still come here from afar to gaze "
            + "at them too, and I don't mind them buying a drink while "
            + "they're at it.",1);
    add_ask(({"map","maps","tattered map","tattered maps"}),
              "say I'd be surprised if any of those maps were real, "
            + "I hired an artist to get them for me.",1);
    add_ask(({"oar","oars","small oar","smaller oar"}),
              "say The oar that hangs above the bar brings many a "
            + "memory to me. That oar was the one that I used when "
            + "I fought that blackfish, years ago. I nearly lost "
            + "more than half an oar that night.",1);
    add_ask(({"blackfish"}),
              "say It's a long story, and to be honest I don't have the "
            + "time for such. But I found the blackfish, and we "
            + "struggled for a whole night before I had to give up. "
            + "I bet he's out there still, laughing at me.",1);
    add_ask(({"painting","paintings","drawing","drawings"}),
              "say I hired an artist to get me some nice paintings "
            + "along with all the dead fish and all. Most of those "
            + "he gave me showed the usual boats and fish, but some "
            + "looked very odd, just like they came right out of "
            + "ages long gone. I wonder where he got the ideas...",1);
    add_ask(({"artist","painter","ealanta"}),
              "say The artist? He used to come in here every night, "
            + "asking if I needed some art for my walls. To tell "
            + "you the truth, I was a bit sceptical about having "
            + "that on my walls, might ruin the theme I thought. "
            + "But I let him persuade me, and no one seems to bother. "
            + "A lot of people like you take interest in them squiggly "
            + "patterns and stones, don't ask me why. If you want to "
            + "to talk to him, I'm afraid I don't know where he went, "
            + "after getting paid. His name was Ealanta, if that's "
            + "any help. Oh, he always wore a strange helmet, and "
            + "a cloak covering the rest of his body.",1);
    add_ask(({"pattern","patterns","strange pattern","strange patterns",
              "stone formation","stone formations","grand stone formation",
              "grand stone formations"}),
              "say I don't know what they're supposed to be, but "
            + "something tells me that the artist didn't make them "
            + "up in his head. I haven't looked at them much, but "
            + "my granddaughter Seile can spend hours just looking "
            + "at them.",1);
    add_ask(({"granddaughter","seile"}),
              "say Seile is my granddaughter, and she's allowed to walk "
            + "around in the village, but not outside! She's one "
            + "adventurous lass, and I'd hate to lose her to the hands "
            + "of some bandit or goblin up north. She's usually down "
            + "in the marketplace or near the river, with her friends.",1);         

    set_act_time(80 + random(80));
    add_act("yawn");
    add_act("grumble");
    add_act("emote cleans a mug.");
    add_act("emote sneezes into a towel.");
    add_act("emote whistles to himself.");
    add_act("emote drinks a cup of ale.");
    add_act("emote sticks his head into the kitchen.");
    add_act("emote wipes his hands on his apron.");
    add_act("emote gazes thoughtfully at the walls.");    
}
/*
 * Function name: set_pub
 * Description  : Sets landlord's pub object pointer, to make
 *                it easier to see if he's where he's supposed
 *                to be.
 * Arguments    : ob - Object pointer to set as his pub.
 * Returns      : n/a
 */
public void
set_pub(object ob)
{
    if (!pub)
        pub = ob;
}

/* Function name: set_kitchen
 * Description  : Sets landlord's kitchen pointer, to make it easier
 *                dealing with him running and hiding from attackers.
 * Arguments    : str - String with the path name to the kitchen.
 * Returns      : n/a
 */
public void
set_kitchen(string str)
{
    if (!kitchen)
        kitchen = str;
}

/*
 * Function name: query_no_deals
 * Description  : Decides whether or not landlord will deal with the
 *                player passed as an argument.
 * Arguments    : ob - Object pointer to the living to check.
 * Returns      : 0 - Deal with the player.
 *                1 - Do not deal with the player.
public int
query_no_deals(object ob)
{
    string name;

    name = ob->query_real_name();
    if (!remembered[name])
        return 0;
    if (remembered[name] == "bad")
        return 1;
    return 0;
}

/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces themselves
 *                to us.
 * Arguments    : str - Name of the player introducing.
 * Returns      : 1
 */
public int
hook_return_intro(string str)
{
    if (!remembered[str])
    {
        command("say Good day, " + capitalize(str) +
            "! I'm " + query_name() + ", " + query_name() + " "
          + query_title() + ", and welcome "
          + "to the Walkway Pub! How can I serve you?");
        command("twinkle " + str);
        remembered[str] = "nice";
    }
    else if (remembered[str] == "bad")
    {
        command("sneer");
        command("say Oh I know you, and I suggest you leave "
              + "my pub!");
    }
    else
    {
        command("ponder");
        command("say I might be old and not as quick of mind, " +
            capitalize(str) + ", but I remember you. What do " +
            "you need this time?");
        command("smile help");
    }
    return 1;
}
/*
 * Function name: attacked_by (MASK)
 * Description  : Allows the npc to call for help when attacked.
 * Arguments    : who - Object pointer to the attacker.
 * Returns      : n/a
 */
public void
attacked_by(object who)
{
    ::attacked_by(who);

    respond_to_attack(who);
}   