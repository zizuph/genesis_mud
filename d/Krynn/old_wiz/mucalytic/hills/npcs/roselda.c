/* Roselda, the guildmistress of the Secret signallers guild. 
 *
 * ~mucalytic/hills/npcs/roselda
 */

inherit "/std/monster";
inherit "/std/act/asking";

#include "../defs.h"

inherit STD + "auto_intro";
inherit STD + "object_add";
inherit "/lib/skill_raise";

#include "/sys/const.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "../../sys/npc_defs.h"

#define	MY_EMOTES ({ "emote looks about.", \
                     "emote looks eastwards.", \
                     "emote looks westwards.", \
                     "emote looks northwards.", \
                     "emote looks southwards.", \
                     "emote scratches her arm.", \
                     "emote scratches her leg.", \
                     "emote rubs her left eye.", \
                     "emote rubs her right eye.", \
                     "emote scratches her neck.", \
                     "emote rummages through the undergrowth.", \
                     "emote whirls round and round doing a silly gypsy dance.", \
                     "think about sex", \
                     "think about finding the right man", \
                     "think about finding a nice place to sleep", \
                     "ponder the sun", \
                     "ponder the moon", \
                     "ponder the stars", \
                     "ponder the clouds", \
                     "ponder the birds in the sky", \
                     "gesture Greetings, initiate.", \
                     "gesture All hail Sir Mucalytic!!!", \
                     "gesture Good to see you again, Signaller.", \
                     "gesture To increase your abilities in language, "+ \
                     "you'll have to 'improve language'.", \
                     "gesture If you get the chance, listen to some "+ \
                     "Skinny Puppy (Try Vivisect VI). They're amazing.", \
                     "gesture If you can understand this totally, you're "+ \
                     "well on your way to being an expert at sign-language." })

void create_monster()
{
    set_name("roselda");
    set_race_name(RACE[5]); // 5 = Human.
    set_gender(G_FEMALE);
    set_adj(ADJ[G_FEMALE][random(14)]);
    add_adj(ADJ[G_FEMALE + 2][random(14)]);
    set_alignment(-200 + random(400));
    set_title("the Guildmistress of the Secret Signallers Guild");
    set_long(break_string("This is a small wizened old woman with leathery "+
        "wrinkled skin and straggly brown hair styled in the way of the "+
        "gypsies. She looks quite old but has a cunningness and wisdom "+
        "deep in her glistening, watchful eyes. Try asking her about "+
        "'skills' or 'guild'.\n", 75));

    add_prop(CONT_I_HEIGHT, 163); // 5 feet 5 inches tall.
    add_prop(CONT_I_WEIGHT, 79000); // 79 kilos weight.

    add_prop(OBJ_M_NO_ATTACK, "@@no_attack"); // Disallow normal attacks.
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "@@no_attack"); // Disallow magical attacks.

    set_stats(({ (30 + random(20)),     /* str */
                 (35 + random(25)),     /* dex */
                 (40 + random(35)),     /* con */
                 (20 + random(15)),     /* int */
                 (20 + random(15)),     /* wis */
                 (25 + random(25)) })); /* dis */

    set_hp(10000); // Heal fully.
    set_restrain_path(LOCATIONS);
    set_random_move(1 + random(3));

    set_skill(SS_DEFENCE, 30 + random(10));
    set_skill(SS_LANGUAGE, 50 + random(20));
    set_skill(SS_AWARENESS, 40 + random(30));
    set_skill(SS_UNARM_COMBAT, 50 + random(10));

    set_chat_time(1 + random(5));
    add_chat("Buh.");
    add_chat("Damn these hills.");
    add_chat("Damn the weather hereabouts.");
    add_chat("Ask me 'about guild', traveller.");
    add_chat("Ask me 'about skills', traveller.");
    add_chat("Join the Secret Signallers Guild.");
    add_chat("I wish somebody would kill that dragon.");
    add_chat("The city of Sha'ang'sei lies eastwards.");
    add_chat("Ah, adventurer. Welcome to the domain of Roselda!");
    add_chat("There's a pleasant little fishing-village to the west.");
    add_chat("I am the guildmistress of the Secret Signallers Guild.");
    add_chat("If you're interesting in joining, you should 'join guild'.");

    add_ask("about guild", VBFC_ME("display_guild"));
    add_ask("about her guild", VBFC_ME("display_guild"));

    add_ask("about skills", VBFC_ME("display_skills"));
    add_ask("about her skills", VBFC_ME("display_skills"));

    set_default_answer(QCTNAME(TO)+" tells you: Try 'ask roselda about "+
        "guild' or 'ask roselda about skills'.\n");

    sk_add_train(SS_LANGUAGE, "speak and understand languages", 
                              "language", (50 + random(50)), 50);

    set_act_time(1 + random(2));
    add_act("@@my_emote_acts@@");
    add_act("@@std_emote_acts@@");

    add_armour(ARMOUR + "dress");
    add_armour(ARMOUR + "shawl");

    add_object(GUILD + "language_autoloader");

    set_tell_active(1);
    command("echoon");
}

string my_emote_acts()
{
    return MY_EMOTES[random(sizeof(MY_EMOTES))];
}

string std_emote_acts()
{
    return FEMOTES[random(sizeof(FEMOTES))];
}

void init_living()
{
    ::init_living();
    ::init_skill_raise();

    add_action("join_guild", "join");
    add_action("leave_guild", "leave");
}

string no_attack()
{
    string str = QCTNAME(TO)+" raises her hand and you suddenly feel very "+
        "peaceful and good natured.\n";

    TP->catch_msg("You try to attack "+QTNAME(TO)+".\n");
    tell_room(E(TO), QCTNAME(TP)+" tries to attack "+QCTNAME(TO)+"!\n", TP);

    tell_room(E(TO), str);
    return "";
}

string display_guild(string str)
{
    TP->catch_msg(QCTNAME(TO)+" tells you: I am the Guildmistress of the "+
        LANGUAGE_GUILD+". If you join us, you gain the ability to use a "+
        "secret language.\n");

    TO->command("say To join the guild, type 'join guild'.");
    return "";
}

string display_skills(string str)
{
    command("say I teach the 'language' skill, "+RACEN(TP)+".");

    if(TP->query_member_guild(LANGUAGE_GUILD))
        command("say You should improve your language skill to get better "+
            "at understanding our secret hand signals.");
    return "";
}

int sk_hook_improved_max(string skill)
{
    command("congratulate "+RNAME(TP));
    command("say You are as learned in "+skill+" as I am, "+RACEN(TP)+". To "+
        "learn more, you will have to find yourself another teacher.");
    return 1;
}

int sk_hook_unknown_skill(string skill, string verb)
{
    command("say I only teach the 'language' skill, "+RACEN(TP)+". If you "+
        "want to "+verb+" "+skill+", you will have to try elsewhere.");
    return 1;
}

int sk_hook_learn_known(string skill)
{
    command("say You already know the rudimentaries of the "+skill+" "+
        "skill, "+RACEN(TP)+". Try improving it now.");
    return 1;
}

int sk_hook_improve_unknown(string skill)
{
    command("sigh");
    command("say You have to 'learn' a skill before you can 'improve' it, "+
        RACEN(TP)+".");
    return 1;
}

int sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    command("slap "+RNAME(TP));
    command("say You'll learn nothing without money, fool! Come back when "+
        "have some.");
    return 1;
}

int sk_hook_no_list_learn()
{
    command("say There are no more skills that you can learn from me. You "+
        "can now either 'improve' them with me or go elsewhere to learn.");
    command("smile at "+RNAME(TP));
    return 1;
}

int sk_hook_no_list_improve()
{
    command("say You cannot improve your skills any further here, "+RACEN(TP)+
        ". You should now either learn new skills or find another teacher.");
    command("curtsey respectfully to "+RNAME(TP));
    return 1;
}

int join_guild(string str)
{
    int can_join;
    object shadow;

    if(!strlen(str))
    {
        notify_fail("Try 'join guild'.\n");
        return 0;
    }

    if(str != "guild")
    {
        notify_fail("Join what? The guild?\n");
        return 0;
    }

    tell_room(E(TO), QCTNAME(TP)+" tries to join the guild.\n", TP);

    if(TP->query_member_guild(LANGUAGE_GUILD))
    {
        command("cackle hysterically");
        command("say You're already a member of the "+LANGUAGE_GUILD+", "+
            RACEN(TP)+"!");
        return 1;
    }

    shadow   = clone_object(GUILD + "language_shadow");
    can_join = shadow->shadow_me(TP, "layman", "language", LANGUAGE_GUILD);

    switch(can_join)
    {
        case 1:
        {
            command("say Welcome to the "+LANGUAGE_GUILD+", "+C(RNAME(TP))+"!");
            command("say Type 'lhelp' for instructions.");

            TP->init_lay_shadow();
            seteuid(getuid());

            if(!present("sign_language", TP))
                clone_object(GUILD + "language_autoloader")->move(TP);
            break;
        }

        case 0:
        case -1:
        case -2:
        case -3:
        {
            write_file(LOG + "language_guild.error", ctime(time())+": "+
                C(RNAME(TP))+": Guild error "+can_join+".\n");
            command("say Hmmm. Commune to a wizard and tell them that "+
                "there is a problem with you joining the guild. Tell them "+
                "that the explaination should be in the guild log.");
            break;
        }

        case -4:
        {
            command("say You'll have to leave your other layman guild "+
                "before you can join this one, "+RACEN(TP)+".");
            break;
        }
    }
    return 1;
}

int leave_guild(string str)
{
    if(!strlen(str))
    {
        notify_fail("Try 'leave guild'.\n");
        return 0;
    }

    if(str != "guild")
    {
        notify_fail("Leave what? The guild?\n");
        return 0;
    }

    tell_room(E(TO), QCTNAME(TP)+" tries to leave the guild.\n", TP);

    if(!TP->query_guild_member(LANGUAGE_GUILD))
    {
        command("duh");
        command("say How can you leave the guild when you're not a member, "+
            RACEN(TP)+"!!?");
        return 1;
    }

    TP->remove_guild_lay();

    if(TP->query_wiz_level())
        command("curtsey respectfully to "+RNAME(TP));

    switch(random(3))
    {
        case 0:
            command("say It's a shame to see you leave, "+C(RNAME(TP))+". "+
                "Good luck!");
            break;
        case 1:
            command("say May luck go forever with you, "+C(RNAME(TP))+".");
            break;
        case 2:
            command("say It's sad to see you leave "+C(RNAME(TP))+".");
            break;
    }

    command("smile "+(random(2) ? "disappointedly" : "tearfully")+" at "+
        RNAME(TP));

    TP->catch_msg("You leave the "+LANGUAGE_GUILD+".\n");
    tell_room(E(TO), QCTNAME(TP)+" leaves the "+LANGUAGE_GUILD+".\n", TP);
    return 1;
}

