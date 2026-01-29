/*
 *  The crook in the harbour, who hands out the drug for the drug-quest
 *  Modification log:
 *  30-may-1995, Olorin: small changes to update the code
 */
inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

int     inform_alarm = 0,
        answer_alarm = 0;
object  herb,
        informing;

void
create_monster()
{
    set_name("fredor");
    add_name(({"Fredor Blackhood","fredor blackhood","blackhood"}));
    set_title("Blackhood, the Wanderer");
    set_adj(({"slim","sneaky"}));
    set_race_name("human");
    set_living_name("fredor");
    set_long(BSN("This is a sneaky-looking man, who does not seem to "
      + "have much to do in life, except hanging around. Perhaps you "
      + "could ask him if he needs 'help'?"));
    set_stats(({ 27, 32, 30, 24, 22, 25}));
    set_skill(SS_UNARM_COMBAT, 56);
    set_skill(SS_WEP_KNIFE,    70);
    set_skill(SS_DEFENCE,      64);
    add_prop(CONT_I_WEIGHT, 76000);
    add_prop(CONT_I_HEIGHT,   179);
    set_act_time(7);
    add_act("say Hello there!");
    add_act("snicker");
    add_act("@@ask_for_help");
    add_act("stare");
    add_act("sigh");
    set_default_answer(VBFC_ME("def_answer"));
    add_ask(({"about help","for help","do you need help?","help"}),
        VBFC_ME("inform"));
    add_ask(({"for job","about job","job", }), VBFC_ME("tell_job"));
    add_ask(({"about herb","for herb","herb", }), VBFC_ME("tell_herb"));
    seq_new("do_things");
    seq_addfirst("do_things","@@arm_me");
}

void
init_living()
{
    ::init_living();
    add_action("accept_job","nod");
    add_action("refuse_job","shake");
}

string
inform()
{
    string  who = TP->query_real_name();

    if (TP == informing)
        return "";

    if (objectp(query_attack()))
    {
        command("snarl " + who);
        return "";
    }
    if (TP->query_prop("_gondor_quest_is_smuggler"))
    {
        command("say Well, I already gave you a leaf. What else do you want?");
        command("say Now go and do this little job for me!");
        return "";
    }
    informing = TP;
    if (answer_alarm && sizeof(get_alarm(answer_alarm)))
        remove_alarm(answer_alarm);
    answer_alarm = set_alarm(60.0, 0.0, "got_no_answer");
    command("introduce myself to "+who);
    command("whisper "+who+" I need help with something, hmm...");
    command("whisper "+who+" ...slightly illegal. Would you still like");
    command("whisper "+who+" to help me? Just give me a nod if you will.");
    return "";
}

void
got_no_answer()
{
    command("say Oh well.");
    command("sigh");
    informing = 0;
    answer_alarm = 0;
}

string
tell_job()
{
    command("say My job? Uh...I...watch out for rats.");
    command("say Aye, rat-watcher - that's my job.");
    command("smirk");
    return "";
}

string
tell_herb()
{
    if (TP->query_prop("_gondor_quest_is_smuggler"))
    {
      command("say Never mind that, just deliver it, will you?");
      command("pat "+TP->query_real_name());
      return "";
    }
    if (TP->test_bit("Gondor", GONDOR_GROUP, HERB_SMUGGLER_BIT))
    {
      command("say It's poisonous, so don't be tempted to eat it!");
      command("say It's to be refined by the Shades, then sold");
      command("say to someone, I believe. They smoke it for pleasure.");
      command("chuckle");
      return "";
    }
    command("say Uh..herbs? I don't know anything about that.");
    command("say Excuse me, I have to go watch for rats....");
    run_away();
    set_alarm(1.0, 0.0, "remove_object");
    return "";
}

int
accept_job()
{
    object  tp = TP;

    if (informing != tp)
        return 0;

    if (answer_alarm && sizeof(get_alarm(answer_alarm)))
    {
        remove_alarm(answer_alarm);
        answer_alarm = 0;
    }

    say(QCTNAME(tp)+" nods solemnly at "+QTNAME(TO)+".\n",tp);
    write("You nod at Fredor.\n");

    if (objectp(query_attack()))
    {
        command("snarl " + TP->query_real_name());
        return 1;
    }
    if (TP->query_prop("_gondor_quest_is_smuggler"))
    {
        command("say Well, I already gave you a leaf. What else do you want?");
        command("say Now go and do this little job for me!");
        return 1;
    }

    if (inform_alarm && sizeof(get_alarm(inform_alarm)))
        return 0;

    command("say Good!");
    command("shake "+tp->query_real_name());
    command("say Now listen carefully; I say this only once....");
    inform_alarm = set_alarm(3.0, 0.0, "information", informing);
    return 1;
}

int
refuse_job()
{
    if (informing != TP)
        return 0;
    say(QCTNAME(TP)+" shakes "+TP->query_possessive()+" head.\n",TP);
    write("You shake your head, refusing Fredor's offer.\n");
    command("shrug");
    command("say Good day to you, then.");
    informing = 0;
    return 1;
}

void
information(object helper)
{
    string  name;

    inform_alarm = 0;

    if (!objectp(helper))
        return;

    name = helper->query_real_name();

    seteuid(getuid(TO));
    command("whisper "+name+" You must bring some illegal drugs into "
      + "Minas Tirith for me.");
    command("whisper "+name+" I can't do it, since the guards know my face.");
    command("whisper "+name+" You must bring the herbs to a guy named "
      + "Arindel in the south parts of the First Circle.");
    command("whisper "+name+" He'll reward you for it.");
    command("whisper "+name+" But be careful that the cityguards do not "
      + "see you bringing the herb into the city!");
    command("whisper "+name+" If you are found out, Arindel will be furious!");

    helper->add_prop("_gondor_quest_is_smuggler",1);
    START_QUEST(helper, "HERB SMUGGLER");
    herb = clone_object(HERB_DIR + "angurth");
    herb->add_name("smuggler_quest_herb");
    herb->move(TO);
    command("give leaf to "+helper->query_real_name());
    informing = 0;
}

string
ask_for_help()
{
    if (objectp(query_attack()))
        return "";
    switch(random(5))
    {
        case 0: command("say I could really use help.");              break;
        case 1: command("say How am I supposed to do it?");           break;
        case 2: command("say Hmm. Bloody guards!");                   break;
        case 3: command("say If only someone would ask to help me."); break;
        case 4: command("say So now what do I do?");                  break;
    }
    return "";
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{

    ::attacked_by(ob);
    ob->remove_prop("_gondor_quest_is_smuggler");
}

string
def_answer()
{
    command("say I beg your pardon?");
    command("peer " + TP->query_real_name());
    command("say I'm afraid I didn't understand you.");
    command("say Perhaps you could repeat that in less and simpler words?");
    command("smile charmingly " + TP->query_real_name());
    return "";
}

