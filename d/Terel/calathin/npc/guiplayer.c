 /*
    Modified: 29 Apr 2003, by Bleys
        - Changed race name from man to human.

    Modified: 13 June 2003, by Bleys
        - Updated to modern includes.
        - Changed quest logging to the proper logfile.
        - Moved /d/Terel/common/town/guitar.c file to
            /d/Terel/calathin/obj/ and changed the reference
            below.

*/

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <composite.h>

#include "/d/Terel/include/quest_bits.h"

public void
create_monster()
{
    ::create_monster();

    set_name("smike");
    set_race_name("human");
    set_adj(({"long-haired","tall"}));
    set_long("He is the musician in the city, always carrying his guitar.\n");

    seteuid(getuid());
    clone_object( CALATHIN_DIR + "obj/guitar" )->move(TO);
    add_act(({"play guitar","smile","sing","laugh"}));
    set_chat_time(20);
    add_chat("Could you help me, please? I need a certain "+
                 "flower that my beloved wants me to give to her.");
    set_random_move(60);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    enable_intro();
}

public int
do_ask(string what)
{
    object ob;
    string race, name, dum, s;

    if (!what ||
        !parse_command(lower_case(what), ETO, " %o %s ", ob, s) ||
        ob != TO) return 0;

    if (sscanf(s, "about %s", dum) == 1) s = dum;
    if (sscanf(s, "for %s",   dum) == 1) s = dum;

    race = capitalize(TP->query_race_name());
    name = TP->query_real_name();

    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " about something.\n");
    if (s == "quests" || s =="help" || s == "task" || s == "tasks") {
        TP->catch_msg(QCTNAME(TO) +
                  " looks at you, smiles and says: "+
                  "My beloved wishes a certain octarine flower, if I " +
                  "don't get it "+
                  "she will not grant me access to her room. I'm a bit " +
                  "busy now, so could you get it for me, please.\n");
        return 1;
    }
    if (s == "flower" || s == "octarine flower" || s == "certain flower" ||
        s == "certain octarine flower") {
        command("ponder");
        TP->catch_msg(QCTNAME(TO) +
                  " looks you in the eyes and says: "+
                  "The octarine flower grows in the enchanted garden, " +
                  "but remember " +
                  "to check with the gardener that you are allowed to " +
                  "pick the flower.\n");
        return 1;
    }
    if (s == "garden" || s == "enchanted garden" ) {
        command("ponder");
        TP->catch_msg(QCTNAME(TO) + " tells you: "+
                  "I have heard that the enchanted garden lies in " +
                  "the enchanted forest, "+
                  "just follow the path from the harbour.\n");
        return 1;
    }
    if (s == "gardener" || s == "joe" || s == "Joe") {
        command("ponder");
        TP->catch_msg(QCTNAME(TO) + " tells you: " +
                  "He's the main man, he works in the enchanted garden.\n");
        return 1;
    }

    command("shrug");
    command("say Sorry, I don't know about that.");
    return 1;
}

public void
init_living()
{
    ::init_living();
    add_action(do_ask, "ask");
}

public void
right_msg(object ob, object from)
{
    string name;

    if (!from || environment(from) != ETO) {
        command("shrug");
        command("drop " + ob->query_name());
        return;
    }
    
    name = from->query_real_name();
    if (from->test_bit("Terel", QUEST_JJ4_GROUP, QUEST_JJ4_BIT)) {
        command("sigh");
        from->catch_msg("While you where out fooling around someone " +
                        "else, looking much like you, already brought " +
                        "me the flower.\n");
        command("drop " + ob->query_name());
        return;
    }
    command("smile " + name);
    if (from->query_exp() <= QUEST_JJ4_EXP) {
        from->add_exp(from->query_exp());
    } else {
        from->add_exp(QUEST_JJ4_EXP);
    }
    from->set_bit(QUEST_JJ4_GROUP, QUEST_JJ4_BIT);
    command("hug " + name);
    command("thank " + name);
    from->catch_msg("You suddenly hear heavenly music and feel more " +
                    "experienced.\n");
    tell_room(ETO, QCTNAME(from) + " has become more experienced.\n", from);
    /*
    write_file(QUEST_LOG, capitalize(name) +
                   " solved the flower quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " solved the " +
        "musician's flower quest (" + ctime(time()) + ")\n");
    ob->remove_object();
}

public void
wrong_msg(object ob, object from)
{
    command("sniff");
    
    if (!from || environment(from) != ETO) {
        command("shrug");
        command("drop " + ob->query_name());
        return;
    }
    
    if (ob == present("flower")) {
        command("whisper " + from->query_real_name() + " The flower " +
                "appears to be damaged, she won't have this one. Could " +
                "you be more careful the next time you pick it.");
    } else {
        command("shout This is not a flower!");
    }
    command("drop " + ob->query_name());
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!from || !interactive(from)) return;

    if (ob == present("octarine flower") &&
        ob->query_prop("_oflower_finder") == from->query_name() &&
        environment(from) == ETO && CAN_SEE(TO, from)) {
        set_alarm(4.0, -1.0, &right_msg(ob, from));
    } else {
        set_alarm(2.0, -1.0, &wrong_msg(ob, from));
    }
}
