/* File         : /d/Khalakhor/se_speir/rannoch/npc/iasgair.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-01      
 * Purpose      : Npc in the Loch Rannoch area.
 * Related Files: 
 * Comments     : 
 * Modifications: Re-written 01-03-23
 */

#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include <ss_types.h>
#include <macros.h> 
#include <stdproperties.h>
#include "npc.h"

inherit "/d/Khalakhor/lib/clan_support";
inherit STDHUMAN;

mapping remembered;
int has_armed;

public void
arm_me()
{
    if (has_armed)
        return;

    seteuid(getuid());

    clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
    clone_object("/d/Khalakhor/se_speir/rannoch/arm/shirt")->move(TO);
    clone_object("/d/Khalakhor/se_speir/rannoch/arm/boots")->move(TO);
    clone_object("/d/Khalakhor/se_speir/rannoch/arm/breeches")->move(TO);

    command("wear all");

    has_armed = 1;
}

public void
create_khalakhor_human()
{

    set_name("iasgair");
    set_living_name("iasgair");
    add_name(({"fisherman","man"}));
    set_gender(G_MALE);
    set_adj(({"rugged","dark-haired"}));
    set_long("This man looks like a fisherman, and certainly smells like "
           + "one. You wonder how he catch his fish, since he has no "
           + "boat, net or fishing pole.\n"
           + "He has friendly brown eyes.\n"
           + "His hair is short, dark, and windswept.\n");

    default_config_npc(80);
 
    add_prop(NPC_I_NO_FEAR, 1); 
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE," says: Naah, you keep it! I don't know "
                                + "where it's been.\n");

    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_PARRY, 30);
    set_skill(SS_DEFENCE, 55);
    set_skill(SS_BLIND_COMBAT, 25);

    set_skill(SS_AWARENESS, 60);

    set_alignment(500);
    set_exp_factor(50);
    set_size_descs("tall", "skinny");
    remembered = ([]);
    set_alarm(0.5, 0.0, arm_me);

    set_default_answer("Take yer questions elsewhere!");

    add_ask(({"fish","fisherman","fishes","catch"}),
              "say Oh, that's what I does. I catch fishes. Sometimes.",1);
    add_ask("wife",
            "say She's waiting for me at home. I hope she's not mad, "
          + "she'll kick me arse!",1);
    add_ask(({"pier","dock","jetty"}),
              "say This thing? I likes ta stands here and, er, catch fishes.",1);
    add_ask(({"boat","boats","fishing boat","fishing boats"}),
              "say I wish I had a boat, darn it.\n"
            + "The rugged dark-haired male human sighs deeply.",1);
    add_ask(({"pole","fishing pole","net","fishing net","tool","tools"}),
              "say I don't needs crap like that!",1);
    add_ask("village",
            "say I lives there, so?",1);
    add_ask(({"macfaolain","clan"}),
              "emote straightens up, smiles proudly, and then sings a "
            + "short song. His voice is horrible, and you are glad you did "
            + "not understand a word.",1);
    add_ask(({"secret","how to catch fish"}),
              "say I guess you'll never know, will you? Heh!",1);
    add_ask(({"bolok","boar","old boar"}),
              "say You don't want to upset that ole bastard, you hear?",1);
    add_ask(({"bandit","bandits","outlaws"}),
              "say Pfeh, let them come, I don't minds a good fight! But "
            + "I wishes they'd just go away.",1);
    add_ask(({"hilltop","hill","top of the hill"}),
              "say Sure, go up there and die. I won't miss you.",1);
    add_ask(({"help","task","quest"}),
              "say Let's see...nope, nothing for you. Now go away.",1);
    add_ask(({"crap","garbage"}),
            "say Your mother knows you better than I does, ask her instead.",1);
    add_ask("blackfish",
            "say Ask Bathar back at the Walkway Pub, he'll be happy to "
          + "tell ye.",1);
    add_ask(({"bathar","landlord","walkway pub"}),
              "Bathar be a nice old man running the Walkway Pub back "
            + "in town. It's in the east half, overlooking the walkway.",1); 
    add_ask(({"captain","captain of the guard","wrestle","wrestled",
              "wrestling match"}),
              "say Well, it sure was no fair fight, but I managed to bite his "
            + "ear off. Heh, he didn't see that one coming! Anyway, I reckon "
            + "he's still a bit upset. But that's not why I'm out here, mind you.",1);
    add_ask("ear",
              "say I hid it! Might come in handy some day.",1);

    set_act_time(30 + random(8));

    add_act("smile hopeful");
    add_act("curse obscenely");
    add_act("stomp");
    add_act("grumble");
    add_act("search it");
    add_act("swear repeatedly");
    add_act("worry");
    add_act("emote scratches his groin.");
    add_act("emote stares at the mountains for a while.");
    add_act("emote looks out across the water and swears loudly.");
    add_act("emote grins at you while examining your equipment.");
    add_act("emote spits far out into the lake.");
    add_act("emote starts to search his pockets.");
    add_act("emote produces a small potato from his pocket, which "
          + "he then eats quickly while glaring greedily at you.");    

    add_chat("Better catch some fish soon, or the wife will be mad!");
    add_chat("Oi, don't just be standing there, help me!");
    add_chat("I won't leave until I catches some fishlings.");
    add_chat("Hey you, bugger off. You scares off the fishes.");
    add_chat("Ahh hell, look at them boats out there.");
    add_chat("I need an ale or five.");
    add_chat("Still here, are ye?");
    add_chat("There's a fine line between fishing and standing at "
           + "the beach like an idiot.");
    add_chat("Did you see that?");
    add_chat("Did I tell you about the time when...nevermind.");
    add_chat("Did I tell you about the time when I wrestled the "
           + "captain of the guard back in town? Hah!");
    add_chat("Perhaps I should get going.");
    add_chat("The lads say I talks too much garbage!");
    add_chat("Watch out if you're going out into the woods, there be "
           + "bandits about, I hear. Unless that boar ate them all, heh.");
 
    set_cact_time(1 + random(1));

    add_cact("scream");
    add_cact("swear repeat");
    add_cact("emote sighs and mumbles to himself."); 

    add_cchat("Now, what have I done to deserve this then?");
    add_cchat("Sod off!");
    add_cchat("I hate you!");
    add_cchat("It's happening...again!");
    add_cchat("Help!");
    add_cchat("Take yer sorry arse and go away!");
    add_cchat("Oh you'll be sorry for this!");
    add_cchat("Leave me be!");
    add_cchat("Know what they does to kids like you back home? Well, "
            + "they'd cut yer gut open and laugh when you hang from "
            + "the cliffs in yer own entrails!");

    arm_me();
}

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

public int
hook_return_intro(string str)
{
    command("say Hah! You wants ta know me name, " + capitalize(str) + "? "
          + "Not bloody likely!");
    command("emote laughs loudly, the laughter echoing through the woods "
          + "and across the lake.");

    return 1;
}

