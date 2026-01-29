/*
 * A poet for the bazaar. Makes us random poems.
 *
 *    Cirion, June 1997
 */
inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <money.h>

string *people = ({ "man", "woman", "girl", "boy", "nymph", "giant", "bird",
		"lover", "enemy", "goddess", "mother", "cat", "ghost" });

string *places = ({ "water", "boat", "ship", "wind", "flood","vision", "power", 
		"music", "honey","garden", "eternity","pond", "death", "gift", "petal", 
		"place","rock", "rose", "water","spray", "apparatus", "part", "rain", "hill",
		"hillside", "mountain", "rocks", "seashore", "beach", "plains", "river", "forest", "storm" });

string *adjectives = ({ "luscious", "delirious", "sordid", "repulsive", "frantic", "pink", "essential", 
		"rose", "enormous", "languid", "delicate", "bare", "terrible", "treacherous", "wondorous",
		"lovely", "soft", "exquisite", "fast", "silent", "ethereal", "ephemeral", "quiet",
		"long", "lonely", "sad", "verdant", "grey", "discordant", "windy", "fat", "soulless", "thin",
		"black", "red", "blue", "heavy", "living", "deathly", "smooth" });

string *adverbs = ({ "lusciciously", "deliriously", "sordidly", "repulsively", "franticly", "essentially",
		"enormously", "languidly", "delicately", "barely", "fiercely", "angrily", "softly", "longingly",
		"forlornly", "fast", "quiet" });

string *verbs = ({ "recall", "worship", "manipulate", "incubate", "chant", "produce", 
		"think", "run", "heave", "boil", "ache", "shake", "read", "sing", "chain", "urge",
		"take", "moan", "scream", "listen", "walk", "grasp", "tear", "reach", "lift", "bring", "sacrifice",
		"forgive", "lie", "walk", "swim", "need", "live", "play" });

string *conns = ({ "to", "under", "in", "with", "without", "about", "above", "before", "along", 
		"within", "beneath", "of", "behind", "at", "around", "through", "throughout", "above" });

string *pronouns = ({ "she", "he", "it" });
string *ppronouns = ({ "they" });

string *poem = ({});
int poem_alarm;

void
create_monster()
{
    ::create_monster();

    set_name(ONEOF(({"amiz","krast","terli","mulo"})));
    set_adj("thoughtful");
    add_name("poet");
    set_race_name(ONEOF(({"gnome","human"})));
    set_short("thoughtful poet");

    set_act_time(5);
     add_act(VBFC_ME("do_poem"));


    set_stats(({10, 10, 10, 50, 50, 10 }));
    set_skill(SS_UNARM_COMBAT, 2 + random(20));
    set_skill(SS_AWARENESS, 10);
    set_skill(SS_WEP_CLUB, 5 + random(30));
    set_skill(SS_DEFENCE, 10 + random(30));

    set_all_hitloc_unarmed(10 + random(30));
    set_alignment(random(100) - 50);

    set_pick_up(1);

    NEVERKNOWN;

    set_random_move(3, 0);
    set_restrain_path("/d/Avenir/common/bazaar/extr");
    set_monster_home("/d/Avenir/common/bazaar/extr/str3");

    add_ask(({"library"}), "say The library is up north, right across " +
            "the street from the bank.", 1);
    add_ask(({"bank"}), "say The bank is up north, right across " +
            "the street from the library.", 1);
    add_ask(({"postoffice", "post"}), "say The postoffice is up north, " +
            "right across the street from the smith.", 1);
    add_ask(({"smith", "forge"}), "say The smith is up north, " +
            "right across the street from the postoffice.", 1);
    add_ask(({"inn"}), "say The inn is up in the northwest.", 1);
    add_ask(({"pier"}), "say The pier is up northwest.", 1);
    add_ask(({"guild"}), "say The guild is on the west side of the bazaar.", 1);
    add_ask(({"pub"}), "say The pub is on the east side of the bazaar.", 1);
    add_ask(({"garden", "park"}), "say Yes there is a park south of the bazaar.", 1);
    set_default_answer("");

}

string race_sound()
{
    return ONEOF(({"speaks","recites","murmurs","whispers","says"}));
}

int
speaking_poem()
{
    if(!poem_alarm || !sizeof(get_alarm(poem_alarm)))
        return 0;
    else
        return 1;
}

string
verb_tense(string vb)
{
    return LANG_PWORD(vb);
}

varargs void
make_poem(int how_many = 5)
{
    poem = ({});

    while(how_many--)
    {
        poem += ({ sprintf("The %s %s %s %s %s %s %s,", ONEOF(adjectives), 
            ONEOF(people), verb_tense(ONEOF(verbs)),
            ONEOF(adverbs), ONEOF(conns), "the", ONEOF(places)) });

        poem += ({ sprintf("while %s %s %s %s %s the %s", 
            LANG_ADDART(ONEOF(adjectives)), ONEOF(adjectives), 
            ONEOF(people), verb_tense(ONEOF(verbs)), ONEOF(conns), ONEOF(places)) });

        poem += ({ sprintf("and when the %s %s %s %s %s %s %s,", ONEOF(adjectives), 
            ONEOF(people), verb_tense(ONEOF(verbs)),
            ONEOF(adverbs), ONEOF(conns), "the", ONEOF(places)) });

        if(random(2))
            poem += ({ sprintf("%s %s %s the %s.", ONEOF(pronouns),  
                   verb_tense(ONEOF(verbs)), ONEOF(conns), ONEOF(places)) });
        else
            poem += ({ sprintf("%s %s %s the %s.", ONEOF(ppronouns), 
                   ONEOF(verbs), ONEOF(conns), ONEOF(places)) });

        poem += ({ "" });
    }

}

void
speak_poem()
{
    string speak;

    if(!sizeof(poem) || query_attack())
    {
       remove_alarm(poem_alarm);
       return;
    }

    if(strlen(poem[0]))
    {
       speak = CAP(poem[0]);

       if(query_race_name() == "gnome")
          speak = implode(map(explode(speak, " "), capitalize), "");

       command("say " + speak);
    }
    else
       command(ONEOF(({"pstroke","pscratch","pwave happily"})));

    poem = exclude_array(poem, 0, 0);
}


string
do_poem()
{
    if(!sizeof(poem))
        make_poem();

    if(!poem_alarm || !sizeof(get_alarm(poem_alarm)))
        poem_alarm = set_alarm(5.0, 5.0, speak_poem);

    return "";
}

void
arm_me()
{
    object pen;

    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_CC(random(40))->move(this_object());

    clone_object(BAZAAR + "Obj/wield/pclub")->move(TO);
    command("wield all");

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
    command("wear all");

    (pen = clone_object(BAZAAR + "Obj/misc/poet_pen"))->move(TO, 1);
      pen->randomize();
}

void
answer_question(string msg, int cmd)
{
    object env;
 
    if ((env = environment(this_object())) == environment(this_player()) ||
            env == this_player() || (not_here_func &&
                call_other(this_object(), not_here_func, this_player())))
    {
        if(sizeof(get_alarm(poem_alarm)))
        {
            command("shout I'm in the middle of a poem here!");

            command("ppoke " + TP->query_real_name() + " "
                 + ONEOF(({"eye", "ear", "nose", "thorax", "abdomen",
		"shoulder", "ribs"})));

            return;
        }

        if(cmd)
            command(this_object()->check_call(msg, this_player()));
        else
            command("shrug");
    }
}

/*
 * Function name: oke_to_move
 * Description:   Checks whether the npc is fighting someone, if he is in
 *                in combat, the move-command will be delayed till the 
 *                war is over.
 * Arguments:     exit  : the exit that is generated for the monster to take.
 * Returns:       0     : if in combat
 *                string: the exit that the monster takes if not in combat.
 */
mixed
oke_to_move(string exit)
{
    if(speaking_poem())
        return 0;

    return ::oke_to_move(exit);
}
