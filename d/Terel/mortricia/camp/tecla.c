/* A fortune teller (quest master). Mortricia 920927 */
/*
    Modified: 13 June 2003, by Bleys
        - Updated to use modern includes
        - Quest logging now going to the current logfile

    Modified: 16 June 2003, by Bleys
        - Removed a bogus space from the new log entry.

*/

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include <std.h>

#include "/d/Terel/include/quest_bits.h"

#define CAMP_DIR        MORTRICIA_DIR + "camp/"
#define ALIGN           0
#define NO_OF_QUESTS    7
#define W_NO_OF_QUESTS  6

int q_check(int q_no, object ob);
int f_quest(object ob);
int f_bit(int q_no, object ob);
object check_short(string sh_desc, object ob);
public int tell_hint(string name);

public void
init_living()
{
    ::init_living();
    add_action("do_ask",   "ask");
    add_action("do_view",  "stare");
    add_action("do_offer", "offer");
    add_action("do_reset", "reset");
    add_action("do_set",   "set");
    add_action("do_give",  "give");
}

public void
create_monster()
{
    ::create_monster();

    set_name("tecla");
    add_name("fortune teller");
    add_name("teller");
    set_short("old fortune teller");
    set_long("An old fortune teller. Maybe she can tell you " +
             "about your future. She probably won't mind " +
             "answering any questions about quests either. " +
             "Her teeth are in very bad shape.\n");
    set_adj("old");
    set_gender(1);
    set_race_name("gypsy");
    set_title("the old fortune teller");

    add_item("teeth",
        "Those few that are left are all black. She probably is " +
        "very fond of sweet candy. Why not offer her some?\n");

    set_stats(({20,20,20,100,100,20}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
    set_skill(SS_AWARENESS, 40);

    add_prop(OBJ_I_NO_ATTACK, 1);

    enable_intro();
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

public int
do_ask(string what)
{
    int i, quest_rew;
    int exp_to_give, q_exp;
    string arg1, arg2;
    string str;
    object ob, evidence, q_ring;

    NF("Ask " + short() + " about what?\n");
    if (!what) return 0;

    if (!parse_command(what, environment(),
        " %o [for] / [about] %s ", ob, arg2)) {
        if (sscanf(what, "%s %s", arg1, arg2) !=2 ) {
            arg2 = "";
            return 0;
        }
        if (arg1 != "for" && arg1 != "about") return 0;
    } else {
        if (ob != TO) {
            NF("Ask whom about what?\n");
            return 0;
        }
    }

    if (arg2 == "quest" || arg2 == "quests") {
        tell_room(ETO, QCTNAME(TO) + " stares into the crystal ball.\n", TO);

        q_ring = check_short("iron ring", TP);
        if(!q_ring) q_ring = check_short("gold ring", TP);
        if (q_ring) {
            NF("You already have a quest to solve!\n");
            return 0;
        }

        command("whisper " + TP->query_real_name() + " " +
                "Stare into my crystal, and you will see what your " +
                "quest is. When you have fulfilled it, come back to " +
                "me and ask for reward.");
        return 1;
    }

    if (arg2 == "reward") {

        q_ring = check_short("iron ring", TP);
        if (!q_ring) q_ring = check_short("gold ring", TP);
        if (!q_ring) {
            write("What has happened with your ring?\n");
            return 1;
        }

        quest_rew = q_ring->query_prop("q_number");
        if (quest_rew != f_quest(TP)) {
            write("You have already done this once!\n");
            command("grin");
            return 1;
        }

        if (quest_rew == 1) {
            str = " hat quest";
            evidence = check_short("silly hat", TP);
        }
        if (quest_rew == 2) {
            str = " beard quest";
            evidence = check_short("piece of hair", TP);
        }
        if (quest_rew == 3) {
            str = " belt quest";
            evidence = check_short("black belt", TP);
        }
        if (quest_rew == 4) {
            str = " juggler quest";
            evidence = check_short("bouquet of violets", TP);
        }
        if (quest_rew == 5) {
            str = " tight-rope quest";
            evidence = check_short("bouquet of roses", TP);
        }
        if (quest_rew == 6) {
            str = " magic quest";
            evidence = check_short("large white pearl", TP);
        }
        if (quest_rew == 7) {
            str = " spooky quest";
            evidence = check_short("ghostly treasure", TP);
        }

        if (!evidence) {
            write("You haven't brought back any good evidence!\n");
            say(QCTNAME(TP) + " is a lousy quest-solver.\n");
            command("sigh");
            return 1;
        }
        if (evidence->query_prop("blood_stained")) {
            command("say There are blood stains on the evidence!");
            command("shout You murderer! I will not reward you!");
            return 1;
        }
        evidence->remove_prop("q_solver");

        write("Congratulations you have solved the" + str + ".\n");
        q_exp = f_bit(quest_rew, TP);
        exp_to_give = TP->query_exp();
        if (exp_to_give > q_exp) {
            exp_to_give = q_exp;
            write("Ahh! Suddenly you feel more experienced.\n");
        } else {
            write("Ahh! Suddenly you feel much more experienced.\n");
        }
        TP->add_exp(exp_to_give, 0);
        /*
        write_file(QUEST_LOG, TP->query_name() +
          " solved" + str + " (" + ctime(time()) + ")\n");
        */
        write_file(QUEST_LOG, TP->query_name() + " solved " +
            "the gypsy camp" + str + " (" + ctime(time()) +
            ")\n");
        say(QCTNAME(TP) + " has become more experienced.\n");
        q_ring->inscript("Love, Tecla");
        q_ring->remove_prop("q_solver");
        q_ring->remove_prop("q_number");
        q_ring->remove_prop(OBJ_M_NO_SELL);
        q_ring->add_prop(OBJ_I_VALUE, 25 + quest_rew * 25);
        return 1;
    }

    if (arg2 == "future") {
        command("say You have no future, " +
                TP->query_nonmet_name() + "!");
        command("grin");
        return 1;
    }
    if (arg2 == "help") {
        command("say You certainly need help, " +
                 TP->query_nonmet_name() + "!");
        command("say But, you won't get it from me just like that.");
        command("say I'm very fond of candy though...");
        command("grin");
        return 1;
    }
    return 0;
}

public int
do_view(string what)
{
    int quest_no;
    string intro, who;
    object ring;

    intro = "You take a close view in the crystal. At first, all " +
            "you see is a compact darkness, but suddenly the " +
            "following words appear:\n";

    if (what != "into crystal" && what != "at crystal" &&
        what != "into ball" && what != "at ball" &&
        what != "into crystal ball" && what != "at crystal ball") {
        return 0;
    }
    if (check_short("iron ring", TP) || check_short("gold ring", TP)) {
        write("You already have a quest to solve!\n");
        return 1;
    }

    quest_no = f_quest(TP);

    who = lower_case(TP->query_name());

    if (quest_no == 0) {
        write("You stare into the crystal, but all you see is a " +
              "compact darkness.\n");
    }
    if (quest_no > W_NO_OF_QUESTS) {
        write(intro + "There are no more quests in this " +
              "neighbourhood.\n");
        command("grin");
        return 1;
    }

    if (quest_no >= 1 && quest_no <= NO_OF_QUESTS) {
        ring = clone_object(CAMP_DIR + "q_ring");
        ring->add_prop("q_solver", TP->query_name());
        ring->add_prop("q_number", quest_no);
        ring->add_prop("q_step", 0);
        ring->add_prop(OBJ_M_NO_SELL, 1);
    }

    if (quest_no == 1 ) {
        write(intro + "Fetch the jester's hat.\n");
        ring->inscript("Fetch the jester's hat.");
    }

    if (quest_no == 2) {
        write(intro + "Fetch the beard of the bearded woman.\n");
        ring->inscript("Fetch the beard of the bearded woman.");
    }

    if (quest_no == 3) {
        write(intro + "Fetch the wrestler's belt.\n");
        ring->inscript("Fetch the wrestler's belt.");
    }

    if (quest_no == 4) {
        write(intro + "Go and ask the head of our clan for a " +
              "job. He will tell you what to do. Don't forget " +
              "to bring back the evidence.\n");
        ring->inscript("Ask the head of the gypsies for a job.");
    }

    if (quest_no == 5) {
        write(intro + "Dance on the tight-rope.\n");
        ring->inscript("Dance on the tight-rope.");
    }

    if (quest_no == 6) {
        write(intro + "Fetch the magician's treasure. Be " +
              "careful, this quest is dangerous.\n");
        ring->inscript("Fetch the magician's treasure.");
    }

    if (quest_no == 7) {
        write(intro + "Fetch Spectre's treasure. Be careful, " +
              "this quest is very dangerous, and you better " +
              "bring a trusted friend with you.\n");
        ring->inscript("Fetch Spectre's treasure.");
    }

    if (quest_no >= 1 && quest_no <= NO_OF_QUESTS) {
        ring->add_prop(OBJ_I_VALUE, 1);
        ring->move(TO);
        command("give ring to " + who);
        command("say Don't lose it!");
    }

    say(QCTNAME(TP) + " stares into the crystal.\n");
    return 1;
}

public int
do_offer(string what)
{
    object candy;
    object *obs;
    string name, str, s1, s2;

    if (!what) {
        NF("Offer what?\n");
        return 0;
    }
    if (sscanf(what, "%s to %s", s1, s2) == 2) {
        what = s1;
    }
    obs = FIND_STR_IN_OBJECT(what, TP);
    name = TP->query_real_name();
    if (sizeof(obs) == 0) {
        command("smirk");
        NF("You cannot offer something like that!\n");
        return 0;
    }
    if (obs[0]->query_name() != "candy") {
        command("say I'm not interested in your " +
           obs[0]->short() + "!");
        return 1;
    }
    candy = present("candy", TP);
    if (!candy) {
        command("stare " + name);
        NF("You don't have any sweet candy! How can you offer it?\n");
        return 0;
    }
    candy->move(TO);
    tell_hint(name);
    return 1;
}

public int
tell_hint(string name)
{
    int quest_hint;
    object q_ring;
    string str;

    command("thank " + name);
    command("whisper " + name + " Candy is my weakness.");
    command("eat candy");
    command("giggle");

    q_ring = check_short("iron ring", TP);
    if(!q_ring) q_ring = check_short("gold ring", TP);
    if (!q_ring) {
        return 0;
    }

    quest_hint = q_ring->query_prop("q_number");

    if (quest_hint > NO_OF_QUESTS) {
        str = "You have solved all quests in this neighbourhood!";
    }
    if (quest_hint == 1) {
        str = "Turn the jester's weakness into your advantage!";
    }
    if (quest_hint == 2) {
        str = "The bearded woman is no fake!";
    }
    if (quest_hint == 3) {
        str = "A greasy body isn't much of a target!";
    }
    if (quest_hint == 4) {
        str = "Practicing before performing is always useful!";
    }
    if (quest_hint == 5) {
        str = "Keep your mind clear!";
    }
    if (quest_hint == 6) {
        str = "This one you have to do without hints!";
    }
    if (quest_hint == 7) {
        str = "This one you must do without hints, " +
              "but not without friends!";
    }
    write(str + "\n");
    return 1;
}

int
q_check(int q_no, object ob)
{
    int bit;

    bit = 0;

    if (q_no == 1) {
        bit = ob->test_bit("Terel", QUEST_G1_GROUP, QUEST_G1_BIT);
    }
    if (q_no == 2) {
        bit = ob->test_bit("Terel", QUEST_G2_GROUP, QUEST_G2_BIT);
    }
    if (q_no == 3) {
        bit = ob->test_bit("Terel", QUEST_G3_GROUP, QUEST_G3_BIT);
    }
    if (q_no == 4) {
        bit = ob->test_bit("Terel", QUEST_G4_GROUP, QUEST_G4_BIT);
    }
    if (q_no == 5) {
        bit = ob->test_bit("Terel", QUEST_G5_GROUP, QUEST_G5_BIT);
    }
    if (q_no == 6) {
        bit = ob->test_bit("Terel", QUEST_G6_GROUP, QUEST_G6_BIT);
    }
    if (q_no == 7) {
        bit = ob->test_bit("Terel", QUEST_G7_GROUP, QUEST_G7_BIT);
    }
    if (SECURITY->query_wiz_rank(ob->query_real_name()) >= WIZ_NORMAL) {
        write("Wizinfo: Bit no " + q_no + " is set to " + bit + ".\n");
    }
    return bit;
}

int
f_bit(int q_no, object ob)
{
    if (q_no == 1) {
        ob->set_bit(QUEST_G1_GROUP, QUEST_G1_BIT);
        return QUEST_G1_EXP;
    }
    if (q_no == 2) {
        ob->set_bit(QUEST_G2_GROUP, QUEST_G2_BIT);
        return QUEST_G2_EXP;
    }
    if (q_no == 3) {
        ob->set_bit(QUEST_G3_GROUP, QUEST_G3_BIT);
        return QUEST_G3_EXP;
    }
    if (q_no == 4) {
        ob->set_bit(QUEST_G4_GROUP, QUEST_G4_BIT);
        return QUEST_G4_EXP;
    }
    if (q_no == 5) {
        ob->set_bit(QUEST_G5_GROUP, QUEST_G5_BIT);
        return QUEST_G5_EXP;
    }
    if (q_no == 6) {
        ob->set_bit(QUEST_G6_GROUP, QUEST_G6_BIT);
        return QUEST_G6_EXP;
    }
    if (q_no == 7) {
        ob->set_bit(QUEST_G7_GROUP, QUEST_G7_BIT);
        return QUEST_G7_EXP;
    }
    return 0;
}

int
f_quest(object ob)
{
    int i;

    i = 1;
    while (i<=NO_OF_QUESTS && q_check(i, ob) ) {
        i++;
    }
    return i;
}

public int
do_set(string no)
{
    if (SECURITY->query_wiz_rank(TP->query_real_name()) >= WIZ_NORMAL) {
        switch(no) {
            case "1":
                TP->set_bit(QUEST_G1_GROUP, QUEST_G1_BIT);
                write("The hat quest bit has been set.\n");
                break;
            case "2":
                TP->set_bit(QUEST_G2_GROUP, QUEST_G2_BIT);
                write("The beard quest bit has been set.\n");
                break;
            case "3":
                TP->set_bit(QUEST_G3_GROUP, QUEST_G3_BIT);
                write("The belt quest bit has been set.\n");
                break;
            case "4":
                TP->set_bit(QUEST_G4_GROUP, QUEST_G4_BIT);
                write("The juggler quest bit has been set.\n");
                break;
            case "5":
                TP->set_bit(QUEST_G5_GROUP, QUEST_G5_BIT);
                write("The tight-rope quest bit has been set.\n");
                break;
            case "6":
                TP->set_bit(QUEST_G6_GROUP, QUEST_G6_BIT);
                write("The magic quest bit has been set.\n");
                break;
            case "7":
                TP->set_bit(QUEST_G7_GROUP, QUEST_G7_BIT);
                write("The spooky quest bit has been set.\n");
                break;
            default:
                write(
        "Usage: set [n]\n" +
        "By omitting the argument you get this message.\n" +
        "For test purposes you can set your own quest bits:\n" +
        "    n=1 ...... hat quest bit\n" +
        "    n=2 ...... beard quest bit\n" +
        "    n=3 ...... belt quest bit\n" +
        "    n=4 ...... juggling quest bit\n" +
        "    n=5 ...... tight-rope quest bit\n" +
        "    n=6 ...... magic quest bit\n" +
        "    n=7 ...... spooky quest bit\n\n"
                );
                break;
        }
        return 1;
    }
    return 0;
}

public int
do_reset(string no)
{
    if (SECURITY->query_wiz_rank(TP->query_real_name()) >= WIZ_NORMAL) {
        switch (no) {
            case "1":
                TP->clear_bit(QUEST_G1_GROUP, QUEST_G1_BIT);
                write("The hat quest bit has been reset.\n");
                break;
            case "2":
                TP->clear_bit(QUEST_G2_GROUP, QUEST_G2_BIT);
                write("The beard quest bit has been reset.\n");
                break;
            case "3":
                TP->clear_bit(QUEST_G3_GROUP, QUEST_G3_BIT);
                write("The belt quest bit has been reset.\n");
                break;
            case "4":
                TP->clear_bit(QUEST_G4_GROUP, QUEST_G4_BIT);
                write("The juggler quest bit has been reset.\n");
                break;
            case "5":
                TP->clear_bit(QUEST_G5_GROUP, QUEST_G5_BIT);
                write("The tight-rope quest bit has been reset.\n");
                break;
            case "6":
                TP->clear_bit(QUEST_G6_GROUP, QUEST_G6_BIT);
                write("The magic quest bit has been reset.\n");
                break;
            case "7":
                TP->clear_bit(QUEST_G7_GROUP, QUEST_G7_BIT);
                write("The spooky quest bit has been reset.\n");
                break;
            default:
                write(
        "Usage: reset [n]\n" +
        "By omitting the argument you get this message.\n" +
        "For test purposes you can reset your own quest bits:\n" +
        "    n=1 ...... hat quest bit\n" +
        "    n=2 ...... beard quest bit\n" +
        "    n=3 ...... belt quest bit\n" +
        "    n=4 ...... juggling quest bit\n" +
        "    n=5 ...... tight-rope quest bit\n" +
        "    n=6 ...... magic quest bit\n" +
        "    n=7 ...... spooky quest bit\n\n"
                );
                break;
        }
        return 1;
    }
    return 0;
}

object
check_short(string sh_desc, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for (i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->short() == sh_desc &&
            (ob_arr[i]->query_prop("q_solver") == ob->query_name() ||
             ob_arr[i]->query_prop("blood_stained") == 1) ) {
            r_ob = ob_arr[i];
        }
    }
    return r_ob;
}

public void
do_intro(object who)
{
    if (!who || !present(who, ETO)) return;
    command("introduce myself to " + who->query_real_name());
}

public void
intro_me(string s1, string s2)
{
    object who = present(lower_case(s1), ETO);

    set_alarm(2.0, -1.0, &do_intro(who));
}

public int
do_give(string str)
{
    string s1, s2, who;
    object *obs;
    object ob1, ob2;

    if(!str) return 0;
    if(sscanf(str, "%s to %s", s1, s2) != 2) return 0;

    obs = FIND_STR_IN_OBJECT(s2, environment(TO));
    if (sizeof(obs)==0) return 0;
    ob2 = obs[0];
    if (ob2 != TO) return 0;

    obs = FIND_STR_IN_OBJECT(s1, TP);
    if (sizeof(obs)==0) return 0;
    ob1 = obs[0];

    ob1->move(ob2);
    TP->catch_msg("You give " + LANG_ADDART(ob1->short()) +
                  " to " + QTNAME(TO) + ".\n");
    say(QCTNAME(TP) + " gives "+LANG_ADDART(ob1->short())+
        " to "+QTNAME(TO)+ ".\n");

    if (ob1->query_short() != "handful of sweet candy") {
        set_alarm(3.0, -1.0, "do_drop_all");
        return 1;
    }

    who = lower_case(TP->query_name());
    tell_hint(who);
    return 1;
}

public void
do_drop_all()
{
    command("drop all");
}
