/* created by Aridor 08/31/93 */


#include "/ss_types.h"
#include <macros.h>
#include <filter_funs.h>
#include "../local.h"
#include "../quest/innquests.h"


inherit M_FILE

static int ready_for_kustennebel = 0;
static int sells_kustennebel = 0;

string reward(object pers, int exp);
int set_quest_number(object pers);
int has_done_quests(object pers);

void
reset_monster()
{
    object barkeeper;

    if (sells_kustennebel == 0)
    {
        barkeeper = BAR_KEEPER_ROOM->query_barkeeper();
        if (barkeeper)
        {
            barkeeper->remove_drink("kustennebel");
            barkeeper->add_cmd_item(({"kustennebel","schnapps"}),"buy",
                VBFC_ME("sorry_out"));
        }
    }
    else
        sells_kustennebel--;
    if (ready_for_kustennebel > 0)
        ready_for_kustennebel--;
}

void
give_back(object ob, object to)
{
    command("say Please just ask me for a reward if you have done the job " +
        "I gave you.");
    command("give " + OB_NAME(ob) + " to " + OB_NAME(to));
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (from)
        set_alarm(2.0,0.0, &give_back(ob,from));
}


void
create_krynn_monster()
{
    set_name("leiden");
    set_race_name("human");
    set_adj("corpulent");
    add_name("proprietor");

    set_title("Proprietor of the Silver Dragon Inn");
    set_long(BS("This man seems very wealthy. He also looks like he is"
                 +" a good eater and drinker.",SL));

    set_stats(({60, 34, 100, 80, 81, 92}));

    set_alignment(100);
    set_knight_prestige(-50);

    set_default_answer(VBFC_ME("excuse_me"));
    add_ask("[for] [a] 'job' / 'task' / 'work' / 'jobs'",
        VBFC_ME("offer_job"));
    add_ask("[for] 'reward'",
        VBFC_ME("reward_job"));
    add_ask("[for] 'help'",
        "say I'm extremely busy, I have to finish my balancing.", 1);

    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, "@@mobile_deny_objects@@");

    set_introduce(1);

    enable_reset();
}

string
reward_job()
{
    mixed has_hop, has_malt;
    int permit;
    object barkeeper;
    int number_of_job = TP->query_prop(PLAYER_I_ON_INN_QUEST);
    seteuid(getuid(TO));

    if (number_of_job)
    {
        if (number_of_job == 1)
        {
            has_hop = present("hop",TP);
            has_malt = present("malt",TP);
            if (has_hop && has_malt)
            {
                has_hop->remove_object();
                has_malt->remove_object();
                return reward(TP, 250);
            }
            else if (has_hop)
            {
                has_hop->remove_object();
                return reward(TP, 100);
            }
            else if (has_malt)
            {
                has_malt->remove_object();
                return reward(TP, 100);
            }
            else
                return reward(TP, 0);
        }
        else if (number_of_job == 2)
        {
            has_hop = present("peat",TP);
            if (has_hop)
            {
                if (has_hop->query_wet())
                {
                    command("say The peat is not dry. I need it dry!");
                    return reward(TP, -3);
                }
                ready_for_kustennebel = 2;
                has_hop->remove_object();
                return reward(TP, 500);
            }
            else
                return reward(TP, 0);
        }
        else if (number_of_job == 3)
        {
            has_hop = present("form", TP);
            permit = ((has_hop->query_form_type() == "authorization") ||
                (has_hop->query_form_type() == "official authorization")) &&
                capitalize(has_hop->query_form_name()) == "Leiden";
            has_malt =
                has_hop->query_form_slot((has_hop->query_form_num_slots())-1);
            if (has_malt == "Trelloq (Supervisor)" && permit)
            {
                barkeeper = (ROOM + "inn1")->query_barkeeper();
                if (barkeeper && ready_for_kustennebel)
                {
                    barkeeper->command("shout Kustennebel on sale " +
                        "NOW! Special offer! For a " +
                        "limited time only!");
                    barkeeper->remove_cmd_item("kustennebel");
                    barkeeper->add_drink(({"schnapps","kustennebel"}),
                        ({"Kustennebel","kustennebel"}),
                        "",100,40,80,
                        "Kustennebel","Kustennebel",
                        "This is another of " +
                        "Palanthas' specialities: " +
                        "homemade Kustennebel! And " +
                        "it is on sale...\n", 0);
                    /* Kustennebel is available (to everyone) only after someone has solved
                     * quest 2 and 3!! Therefore it is sold cheaper than the standard price:
                     * (80cc, Standard: 170cc)
                     */
                }
                sells_kustennebel = 5;
                /* but it is sold only for 5 resets */
                has_hop->remove_object();
                return reward(TP, 6500);
            }
            else
            {
                if (!permit)
                    return reward(TP, -1);
                else if (!has_malt)
                    return reward(TP, -2);
                else
                    return reward(TP, 0);
            }
        }
    }
    else
    {
        command("say I'm sorry, I cannot remember giving you a job.");
        command("say It is possible that I could offer you work!");
        return "";
    }
}

string
reward(object pers, int exp)
{
    int number_of_job;
    if (exp <= 0)
    {
        if (exp == -1)
            write("This doesn't seem to be an authorization form with my name on it.\n");
        else if (exp == -2)
            write("The persons who signed this form don't seem to be authorized to do so.\n");
        else if (exp == -3)
            write("");
        else
            write("You have to carry the desired items with you to get a "
                +  "reward.\n");
        say(QCTNAME(pers) + " tried to get a reward but was not worthy one.\n");
        return "";
    }
    command("thank " + pers->query_real_name());
    command("say Good job!");
    command("smile");
    if (exp < 1000)
        write("You feel more experienced.\n");
    else
        write("You feel much more experienced.\n");
    say(QCTNAME(pers) + " got a nice reward.\n");
    set_quest_number(pers);
    
    pers->add_exp_quest(exp);
    number_of_job = pers->query_prop(PLAYER_I_ON_INN_QUEST);
    pers->remove_prop(PLAYER_I_ON_INN_QUEST);

    if (DO_LOG_QUESTS == 1)
        K_QUEST_LOG("quest", "Palanthas Inn quest " + number_of_job, pers,
            exp);
    return "";
}


excuse_me()
{
    command("say Excuse me?");
    return "";
}


offer_job()
{
    if (TP->query_prop(PLAYER_I_ON_INN_QUEST))
    {
        command("say Maybe you want to ask me for a reward "
            +   "for completing your last job before applying again?");
        command("say In case you haven't done it yet, this is what you "
            +   "were supposed to do: ");
        if (has_done_quests(TP) == 0)
            command("say I need some hop and malt from my garden in " +
                "Palanthas.");
        else if (has_done_quests(TP) == 1)
            command("say You are supposed to bring me some peat from the peat "
                +  "cutter.");
        else
            command("say I need an authorization form with the permission " +
                "to sell highly alcoholic drinks.");
        return "";
    }
    else if (has_done_all_quests(TP))
    {
        command("say I am terribly sorry, but you already helped me a " +
            "lot.\nMaybe in the future I will need your help again, " +
            "who knows?");
        command("bow to " + TP->query_real_name());
        return "";
    }
    else if (has_done_quests(TP) == 0)
    {
        command("say Certainly I have a job for you!");
        command("peer at " + TP->query_real_name());
        command("say And you look just like the right person!");
        command("introduce me to " + TP->query_real_name());
        command("say I am having some problems getting my supplies lately.");
        command("say Unfortunately, I will be running out of our home " +
            "made speciality very soon, so it is your job to bring me " +
            "some hop and malt from my garden in Palanthas, which are " +
            "the essential ingredients for our Pfuschbeer.");
        command("say Oh, but don't delay too long, or I will offer the job "
            +  "to someone else.");
        command("ponder");
        command("say Certainly you will be rewarded afterwards!");
        TP->add_prop(PLAYER_I_ON_INN_QUEST, 1);
        return "";
    }
    else if (has_done_quests(TP) == 1)
    {
        command("introduce me to " + TP->query_real_name());
        command("say Here is what I expect you to do for me this time:");
        command("sigh");
        command("say I'm planning to offer a new speciality here, a "
            +   "strong schnapps, but before I am able to, I need "
            +   "some kind of fuel to operate my distilling flask.");
        command("brighten");
        command("say I have heard there is a peat cutter around selling "
            +   "peat.");
        command("smile " + TP->query_real_name());
        command("say Just bring me some and ask for your reward.");
        TP->add_prop(PLAYER_I_ON_INN_QUEST, 2);
        return "";
    }
    else if (has_done_quests(TP) == 2)
    {
        command("introduce me to " + TP->query_real_name());
        command("sob");
        command("say I'm so depressed!");
        command("say A city officer has just paid me a visit, and what "
            +   "that means... I guess I don't have to tell you.");
        command("sob");
        command("say Yes, I do have another job for you...");
        command("say Please take this seal from me.");
        seteuid(getuid(TO));
        clone_object(OBJ + "lseal")->move(TO);
        command("give seal to " + (TP->query_real_name()));
        command("say I need an authorization form which gives permission " +
            "to sell highly alcoholic drinks.");
        TP->add_prop(PLAYER_I_ON_INN_QUEST, 3);
        return "";
    }

    /* add more quests in here!! ************/

    else
    {
        command("say Sorry, there is no more work for you to do here "
            +  "at this time.");
        return "";
    }
}


int
has_done_all_quests(object pers)
{
    return (has_done_quests(pers) == NUM_OF_QUESTS);
}


int
has_done_quests(object pers)
{
    int i, sum, base;
    base = 1;
    sum = 0;
    for (i = 0; i < NUM_OF_BITS; i++)
    {
        sum += base * (pers->test_bit("Krynn", GROUP, i + FIRST_BIT));
        base *= 2;
    }

    return sum;
}

int
set_quest_number(object pers)
{
    int i, *base, num;
    int number_of_job = pers->query_prop(PLAYER_I_ON_INN_QUEST);
    if (number_of_job < 1)
        return -1;
    base = ({ 1, 2, 4, 8 });
    num = number_of_job;
    for (i = NUM_OF_BITS; i >= 0; i--)
    {
        if ((num / base[i]) > 0)
        {
            pers->set_bit(GROUP, FIRST_BIT + i);
            num -= base[i];
        }
        else
            pers->clear_bit(GROUP, FIRST_BIT + i);
    }
    return has_done_quests(pers);
}

