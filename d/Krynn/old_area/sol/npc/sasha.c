/*
 * Sasha Westan
 * modified from Toede.
 * by Teth
 * Apr 28,'96 
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE

inherit "/std/act/domove";     /* Allows Sasha to move */
inherit "/std/act/action";     /* Allows Sasha to act  */

public void
create_krynn_monster()
{
    string str;

    set_name("sasha");
    set_living_name("sasha");
    set_race_name("human");
    set_title("Westan, Teacher and Skillswoman of Solace");
    set_long("This woman has wavy brown hair that flows down to her " +
             "shoulders. Her face has a hawkish look about it, and it " + 
             "appears she possesses both a keen mind and a strong body to " +
             "go with it. Her walnut-brown eyes glimmer with a " +
             "confident self-assurance.\n"); 
    add_name(({"westan","teacher","skillswoman","woman"}));
    set_adj("wavy-haired");
    add_adj("hawkish"); 
    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_stats(({90,106,68,96,106,74}));
    set_skill(SS_DEFENCE,        30);
    set_skill(SS_PARRY,          30);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);
    set_skill(SS_UNARM_COMBAT,   75);

    set_alignment(623);
    set_knight_prestige(-2);

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] [animal] 'animals' / 'handling'", "say " +
            "The training and handling of animals can be a very useful " +
            "skill. For example, I have used it in the past to help " +
            "capture rabbits and call birds. It's also helpful when " +
            "calming pigeons, so that they do not fly away so fast.",1);
    add_ask(" [about] 'climb' / 'climbing'", "say When I was " +
            "young, I often found it helpful to be able to climb well. " +
            "It can be important for climbing trees, walls, or even " +
            "mountains and cliffs!",1);
    add_ask(" [about] [appraise] 'enemy' / 'object' / 'appraising'",
            "say Knowing the qualities of an object, friend " +
            "or foe can be very helpful. You should be aware that when " +
            "you are relatively unskilled in these attributes, you may " +
            "make some wild and unbelievable estimates.",1);
    add_ask(" [about] 'club'","say Learning how to better fight " +
            "with a club is good if you want to use most blunt objects " +
            "that can be wielded as weapons. Not only does this include " +
            "maces and clubs, but also some bones, frying pans, and " + 
            "such.",1);
    add_ask(" [about] 'defence' / 'defense'","say Knowing " +
        "defensive maneuvers can keep you alive in battle! I " +
        "recall one time a troll nearly took my head off, but " +
        "a quick sidestep saved me, then I lopped off his head.", 1);
    add_ask(" [about] [location] 'sense' / 'locating'","say " +
            "Oft are the times when I wish I knew " +
            "how to find my way around better. I've gotten lost in " +
            "forests, more forests, and even more forests.",1);
    add_ask(" [about] [open] [opening] 'locks'","say " +
            "Ah yes, learning how to open locks. I was taught " +
            "that skill several years ago, by a kender who resided here " +
            "in Solace. He was always chattering about some sort of large " +
            "creature ... a mammoth I believe it was. Anyway, if I sat " +
            "through his stories, he'd show me a few tricks.",1);
    add_ask(" [about] 'kender'","say I wonder whatever happened to him. " +
            "Hmmm, I think his name was, let me see ... " +
            "Hasslehoff Baywatcher? No, that's not it. Ah yes! Tasslehoff " +
            "Burrfoot! What a character.",1);
    add_ask(" [about] 'polearm'", "Sasha suggests: A polearm is a long " +
            "weapon, typically a blade of various design set upon a two " +
            "meter or longer pole. It's usually a two-handed weapon. " +
            "Polearms include such things as halberds and tridents.\n");
    add_ask(" [about] 'swim' / 'swimming'","say Swimming " +
            "is one of the most important general skills one can learn. " +
            "It is important not to drown when you have to swim across " +
            "lakes and under water!",1);
    add_ask(" [about] 'sneak' / 'sneaking'","say Sneaking " +
            "is a useful skill, especially if you are good at it. " +
            "You can use it to get past hostile enemies, or to avoid " +
            "certain undesirable situations. It can also be useful for " +
            "gaining information.",1);
    add_ask(" [about] 'sword'","say " +
            "Sword fighting is a very useful skill for any youngster. " +
            "Most humanoid enemies find the sword a preferable weapon, " +
            "so that if you manage to vanquish them, you'll find as often " +
            "as not a sword among the loot. Considering how commonplace " +
            "the weapon is, it is a good idea to be proficient in this " +
            "skill.",1);
    add_ask(" [about] [fewmaster] 'toede' / 'fewmaster'","say " +
            "Toede thinks he rules this town! Well, he'll have it coming " +
            "to him one day.",1);
    add_ask(" [about] 'tasslehoff'","say I haven't " +
            "seen that fellow in years. He went on some sort " +
            "of quest, I think.",1);
    add_ask(" [about] 'quest'","say I wouldn't know " +
            "anything about that.",1);

    set_act_time(5);
    add_act("emote brushes the lock of hair back that was in her eyes.");
    add_act(({"say I hope that lousy Fewmaster Toede takes a long walk on " +
            "a short Crystalmir Lake pier.", "emote sighs wistfully."}));
    add_act("emote hums a tune that you are not familiar with.");
    add_act("say I've trained the best!");
    add_act("say Otik has the best potatoes on this side of the Newsea!");
    add_act("emote looks at you with her walnut-brown eyes, appraising " +
            "you.");
    add_act("emote rubs her chin thoughtfully.");

    set_cact_time(4);
    add_cact("shout Help me! I'm being attacked!");
    add_cact("say Someone will have their revenge on you, fool!");
    add_cact("emote tries to protect herself."); 
    add_cact("say Just another fine example of Toede not doing his job!");
}

/*
public void
arm_me()
{
    clone_object(OBJ + "tsword")->move(TO);
    clone_object(OBJ + "tarmour")->move(TO);
    clone_object(OBJ + "tshinguard")->move(TO);
    clone_object(OBJ + "tboots")->move(TO);
    clone_object(OBJ + "tgauntlets")->move(TO);
    clone_object(OBJ + "thelmet")->move(TO);
    command("wear all");
    command("wield all");
}
*/

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Sasha Westan", killer);
    return 0;
}
