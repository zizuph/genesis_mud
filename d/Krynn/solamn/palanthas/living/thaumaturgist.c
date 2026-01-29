//'Perubahan Mayat ' "change body"

#include "../local.h"

#define MY_ARMOUR            MERCH + "arms/larmour"

#define MY_ROBE              MERCH + "arms/daiv_robe"

#define MORPH_SH OBJ + "morph_sh"

#define LOG_DIR (KRYNN_DIR + "log/")
#define RACE_PATH (LOG_DIR + "race_changes")
#define FREE_TRANSFORM_PATH (LOG_DIR + "free_transform_changes")

inherit M_FILE

#include <composite.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <state_desc.h>
#include <formulas.h>
#include <login.h>
#include <std.h>

#define LOG_FILE (KRYNN_DIR + "log/thaumaturgist")

#define CREATION_MAX_TIME 1678829557

int* desired_stats = allocate(SS_NO_EXP_STATS);

static string* EMPHASIS = ({
    "normal",
    "slightly stronger",
    "somewhat stronger",
    "stronger",
    "much stronger", });

mapping race_changes = ([]);
mapping free_transforms = ([]);

string current_player;
int state;

int cancel_alarmId;

void log_entry(string message)
{
    write_file(LOG_FILE, sprintf("%s %s %s\n",
        ctime(time()), current_player, message));
}

public int has_free_transform(object player)
{
    if (player->query_creation_time() >= CREATION_MAX_TIME)
        return 0;
    if (!free_transforms[player->query_real_name()])
    {
        // Free transform to go with race rebalance.
        return 1;
    }
    return 0;
}

public int has_free_race_change(object player)
{
    if (player->query_creation_time() >= CREATION_MAX_TIME)
        return 0;
    if (!race_changes[player->query_real_name()])
    {
        // Free race change
        return 1;
    }
    return 0;
}



public int player_cost(object player)
{
    if (has_free_transform(player))
    {
        // Free transform to go with race rebalance.
        return 0;
    }
    int avg = player->query_average_stat();
    if (avg < 5)
    {
        return 5;
    }
    if (avg <= 50)
    {
        // Up to 50 platinum for 50 average.
        return (avg / 5) * 5;
    }
    if (avg <= 100)
    {
        // Between 50 and 200 platinum for 100 average.
        return 50 + ((avg - 50) / 5) * 15;
    }
    if (avg <= 200)
    {
        // Between 200 and 2000 platinum for 200 average.
        return 200 + ((avg - 100) / 5) * 90;
    }
    // 4000 platinum at 300 average.
    return 2000 + ((avg - 200) / 5) * 100;
}

void cancel_convert()
{
    command("say Such a change is sweeping and impactful, come back " +
       "to me when you have made up your mind.");
    state = 0;
    current_player = 0;
    if (cancel_alarmId)
    {
        remove_alarm(cancel_alarmId);
    }
    cancel_alarmId = 0;
}

void setup_cancel()
{
    if (cancel_alarmId)
    {
        remove_alarm(cancel_alarmId);
    }
    cancel_alarmId=set_alarm(60.0,0.0,cancel_convert);
}

public string offer_convert()
{
    if (current_player)
    {
        if (this_player()->query_real_name() == current_player)
        {
            command("say You have asked me that already, and now I have " +
                "questions for you.");
            return "";
        }
        command("say My services are no triviality, and you must wait " +
        "your turn.");
        return "";
    }
    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say I can help you out, but only if I can see you.");
        return "";
    }
    if (this_player()->has_morph_shadow())
    {
        command("say Your metamorphosis is still in progress, " +
           "pretty butterfly.");
        return "";
    }

    command("say I offer a service that no other can do.");
    command("say I have a spell that can reconstruct your mind and " +
            "body, without repeated visits to Lars.");
    command("say The process however is long, painful " +
            "and expensive - as all potent gifts should be.");
    command("say I will let you choose your new focuses, and your " +
            "mind and body will reform over time.");
    command("say The parchment on my desk can tell you more.");
    int cost = player_cost(this_player());
    command("say The cost for yourself would be " +
            (cost ? cost + " platinum" : "nothing") + ".  " +
            "Is this acceptable?");    
    current_player = this_player()->query_real_name();
    state = 1;
    setup_cancel();
    return "";
}

public string offer_rebirth()
{
    if (current_player)
    {
        if (this_player()->query_real_name() == current_player)
        {
            command("say You have asked me that already, and now I have " +
                "questions for you.");
            return "";
        }
        command("say My services are no triviality, and you must wait " +
        "your turn.");
        return "";
    }
    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say I can help you out, but only if I can see you.");
        return "";
    }
    if (!has_free_race_change(this_player()))
    {
        command("say I have done this for you before.  You'll need to use " +
        "the usual way to visit Lars next.");
        return "";
    }

    command("say I offer a service that no other can do.");
    command("say I can let you visit Lars to change your race.");
    command("say I will only do this once for you.");
    command("say Is this acceptable?");
    current_player = this_player()->query_real_name();
    state = 101;
    setup_cancel();
    return "";
   
}

string my_answer()
{
    // Default answer is also called if speech_hook is active.
    // disable it during the transformation process.
    if (!state)
    {
        set_alarm(0.5, 0.0, "command", "say Are you looking for a service?");
    }
    return "";
}

string cost_estimate()
{
    command("say For transforming one of your stature, I would charge "
        + player_cost(this_player()) + " platinum.");
    return "";    
}

string explain_services()
{
    if (has_free_race_change(this_player()))
    {
        command("say I offer two services.  One lets you rechannel your " +
        "past experiences.  The other lets you be reborn in a new body.");
    }
    else
    {
        command("say I offer a service that lets you rechannel your past " +
        "experiences.");
    }
    
    return "";
}

void create_krynn_monster()
{
    seteuid(getuid(TO));


    set_name("vitaro");
    set_short("red-robed male human");
    add_adj("red-robed");
    set_race_name("human");    
    set_title("Thaumaturgist of the First Red Circle");
    
    add_ask( ({ "help", }),
        "say I do not need any help, but perhaps I have provide you a "+
        "service.",1 );

    add_ask( ({ "potential", "magical means", "means" }),
        "say I provide a powerful service that will allow you to rechannel " +
        "all your past experience into a different set of preferences.", 1);
    
    add_ask( ({ "preferences", "preference", "past" }),
        "say You choose your future preferences through meditation, " +
        "but only I can revise your past.", 1);

    add_ask( ({ "service", "services" }),
        explain_services);
    
    add_ask( ({"reborn", "new body", "rebirth", "race change" }),
       offer_rebirth);
    
    add_ask( ({ "conversion", "transformation", "convert", "rechannel"}),
        offer_convert);

    add_ask( ({ "cost", "costs", "price"}),
        cost_estimate);

    set_default_answer("@@my_answer");

    set_act_time(25);

    add_act("say I can provide magical means to bring you to your full "
        + "potential.",1);
        
    add_act("say Some think that repeated death is the only way to "
        + "rebirth.  They are sadly mistaken.", 1);

    add_act("say Give with one hand, take with the other.  That is the "
        + "way of balance.", 1);
        
    set_gender(G_MALE);
    set_size_descs("extremely tall", "of normal width");
    set_appearance(5);
    
    set_stats(({165, 160, 195, 130, 145, 210})); // Champion

    set_skill(SS_AWARENESS,    90);
    set_skill(SS_RIDING,       30);
    set_skill(SS_PARRY,        50);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_WEP_CLUB,     90);
    set_skill(SS_BLIND_COMBAT, 85);

    set_all_attack_unarmed(85, 50);
    set_all_hitloc_unarmed(75);
    
    set_alignment(0);
    set_introduce(1);
    
    set_alarm(1.0, 0.0, "arm_me");
    race_changes = restore_map(RACE_PATH);
    free_transforms = restore_map(FREE_TRANSFORM_PATH);
}

void
arm_me()
{
    object crobe, cgloves;

    crobe = clone_object(MY_ROBE);
    crobe->set_armour_data("dark" + "&&"
                            + "crimson" + "&&"
                            + "fox" + "&&"
                            + "robe" + "&&"
                            + "noliner" + "&&"
                            + "unused" + "&&"
                            + "unused" + "&&"
                            + "unused");
    crobe->move(TO);

    cgloves = clone_object(MY_ARMOUR);
    cgloves->set_armour_data("light" + "&&"
                            + "grey" + "&&"
                            + "leather" + "&&"
                            + "gloves");
    cgloves->move(TO);

    command("wear all");
    command("wield all");
}

public float* compute_ratios()
{
    int lowest = sizeof(EMPHASIS);
    int sum = 0;
    float* ratios = ({ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0});
    
    for (int i = 0 ; i < SS_NO_EXP_STATS; i++)
    {
        lowest = min(lowest, desired_stats[i]);
        sum += desired_stats[i];
    }
    // At least one stat diffs from the others.
    if (sum > lowest * SS_NO_EXP_STATS)
        {
        float max_baseline = min(6.0, 
            itof(sum - lowest * SS_NO_EXP_STATS));
        // The sum of all bonuses should add up to 6.0
        // The baseline is 6.0, so we are allowing up
        // to 1/2 of combat experience to be used as
        // 'bonus' - this matches what meditation allows
        // as of 2023-02 post race rebalance.
        for (int i = 0 ; i < SS_NO_EXP_STATS; i++)
        {
            ratios[i] += max_baseline * itof(desired_stats[i] - lowest)
              / itof(sum - lowest * SS_NO_EXP_STATS);
        }
    }
    return ratios;
}


public void finalize_racechange(object player)
{
    if (!objectp(player) || environment(player) != environment(this_object())
      || !CAN_SEE(this_object(), this_player()))
    {
        state = 0;
        current_player = 0;
        command("say Fear is the mind killer.");
        return;
    }
    switch(state)
    {
    case 101:
        if (cancel_alarmId)
        {
            remove_alarm(cancel_alarmId);
        }
        log_entry("started race change.");
        command("say Whatever you do, don't move until I am finished.");
        race_changes[player->query_real_name()] = time();
        save_map(race_changes, RACE_PATH);
        player->add_prop("_thau_in_racechange", 1);
        break;
    case 102:    
        command("emote removes a silver silk bag from the shelf.");
        break;
    case 103:
        command("emote opens the bag and pours a small amount of " +
            "dusky black powder into his hand.");
        break;
    case 104:
        tell_room(environment(player), QCTNAME(this_object()) + 
           " blows the black powder into " + QPNAME(player) +
           " face.  " + capitalize(player->query_pronoun()) +
           " falls backwards, paralyzed.\n", ({ player }));       
        player->catch_msg(
           QCTNAME(this_object()) + " blows the black powder into " +
               "your face.  You fall backwards, paralyzed.\n");
         break;
    case 105:
        command("say Perubahan Mayat!");
        tell_room(environment(player), QCTNAME(player) + 
           " vanishes, their body turning into mist.\n");
        player->set_ghost(GP_DEAD | GP_NOSKILL_LOSS);
        catch(SECURITY->store_predeath());

        player->death_sequence();
        player->save_me();
        player->remove_prop("_thau_in_racechange");
        state = 0;
        log_entry("ended race change.");
        current_player = 0;
        return;
    }    
    state++;
    if (state < 106)
    {
        set_alarm(5.0, 0.0, &finalize_racechange(player));
    }
}


public void finalize_morph(object player)
{
    if (!objectp(player) || environment(player) != environment(this_object())
      || !CAN_SEE(this_object(), this_player()))
    {
        state = 0;
        current_player = 0;
        command("say Fear is the mind killer.");
        return;
    }
    switch(state)
    {
    case 8:
        if (cancel_alarmId)
        {
            remove_alarm(cancel_alarmId);
        }
        int cost = player_cost(this_player());
        if (!cost)
        {
            log_entry("used free morph.");

            free_transforms[player->query_real_name()] = time();
            save_map(free_transforms, FREE_TRANSFORM_PATH);
            command("say This is your one free transformation.");
        }
        else if (MONEY_MOVE_PC(player_cost(this_player()), this_player(), 0))
        {
            command("say Come back when you have the fee on hand.");
            state = 0;
            current_player = 0;
            return;
        }
        log_entry("started morph.");
        command("say Whatever you do, don't move until I am finished.");
        player->add_prop("_thau_in_transformation", 1);
        break;
    case 9:
        break;
    case 10:
        command("emote puts his hands in front of his face, as if " +
          "taking a measurement.");
        break;
    case 11:    
         command("emote takes a dark-red velvet bag from the shelf.");
         break;
    case 12:
        tell_room(environment(player), QCTNAME(this_object()) + 
           " opens the bag and pours out a " +
           "fine white powder in a circle around " + QTNAME(player)
           + ".\n", ({ player }));       
        player->catch_msg(
           QCTNAME(this_object()) + " opens the bag and pours out a " +
           "fine white powder in a circle around you.\n");
         break;
    case 13:
        command("say Perubahan Dalam Bentuk!");
        tell_room(environment(this_object()),
           "A loud thunderclap reverberates through the room, knocking " +
           "the wind out of your lungs.\n");
        break;
    case 14:
        float* ratios = compute_ratios();
        
        object shadow = clone_object(MORPH_SH);
        // This will shadow the player with their desired focus.
        shadow->configure_morph_shadow(
            ratios[0], ratios[1], ratios[2], ratios[3], ratios[4],
            ratios[5], this_player());
        player->remove_prop("_thau_in_transformation");
        log_entry("ended paid morph.");
        break;
     case 15:   
        command("say My work is done, and only your patience stands " +
        "between my efforts and your reward.");
        state = 0;
        current_player = 0;
        return;
    }    
    state++;
    if (state < 16)
    {
        set_alarm(5.0, 0.0, &finalize_morph(player));
    }
}


public void confirm_focus(object player)
{
    int lowest = sizeof(EMPHASIS);
    string* phrases = ({});
    
    for (int i = 0; i < sizeof(EMPHASIS); i++)
    {
        string* stats = ({});
        for (int j = 0 ; j < SS_NO_EXP_STATS; j++)
        {
            if (desired_stats[j] == i)
            {
                lowest = min(i, lowest);
                stats += ({ SD_LONG_STAT_DESC[j] });
            }
        }
        if (sizeof(stats))
        {
            phrases += ({ "a '" + EMPHASIS[i] + "' focus on " +
               COMPOSITE_WORDS(stats) });
        }
    }
    int increase_count = 0;
    for (int j = 0 ; j < SS_NO_EXP_STATS; j++)
    {
        if (desired_stats[j] > lowest)
        {
            increase_count++;
        }
    }
    if (increase_count == 1)
    {
        command("say I am not empowered to let you focus on " +
            "one stat.");
        cancel_convert();
        return;
    }
    command("say For this big change, you have requested " +
        COMPOSITE_WORDS(phrases) + ".");
    if (lowest)
    {
        command("say You asked for a focus of at least '" + EMPHASIS[lowest] +
          "' on every characteristic, so that will be your 'normal'.");
    }
    string* up_stats = ({});
    string* down_stats = ({});
    float* ratios = compute_ratios();
    float sum = reduce(&operator(+)(,), ratios);
    for (int j = 0 ; j < SS_NO_EXP_STATS; j++)
    {
        int desired_exp = ftoi(itof(player->query_exp()) * ratios[j] / sum);
        
        if (itof(player->query_acc_exp(j)) > itof(desired_exp) * 1.02)
        {
            down_stats += ({ SD_LONG_STAT_DESC[j] });
        }
        if (itof(player->query_acc_exp(j)) < itof(desired_exp) * 0.98)
        {
            up_stats += ({ SD_LONG_STAT_DESC[j] });
        }
    }
    if (sizeof(up_stats) && sizeof(down_stats))
    {
        command("say This will cause your " + COMPOSITE_WORDS(up_stats) +
            " to increase and your " + COMPOSITE_WORDS(down_stats) +
            " to decrease.");
    }
    else if (sizeof(up_stats))
    {
        command("say This will cause your " + COMPOSITE_WORDS(up_stats) +
            " to increase.");
    }
    else if (sizeof(down_stats))
    {
        command("say This will cause your " + COMPOSITE_WORDS(down_stats) +
            " to decrease.");
    }
    else
    {
        command("say This will have no real effect on your stats.");
    }
    
    if (player_cost(player))
    {
        command("say Are your choices acceptable?  If so, I will take your money " +
            "and start you on your new road.");
    }
    else
    {
        command("say Are your choices acceptable?  If so, I will " +
            "start you on your new road.");
    }
    state = 8;
    setup_cancel();
}


public void request_focus(int stat)
{
    if (stat == 0)
    {
        command("say I will ask you how much emphasis you wish to have " +
           "on each of your six characteristics.  You can choose " +
           "'normal', 'slightly stronger', 'somewhat stronger', 'stronger' " +
           "and 'much stronger'.");
        command("say Your focus is relative, so every high " +
          "emphasis will reduce the impact of the other focuses.");
        command("say In other words, six 'much stronger' choices " +
          "will have the same end result as six 'normal' choices.");
        command("say As with meditation, if you choose to focus more " +
          "on one stat, you must focus on at least two.");
        command("say Also remember that your race has not changed, and you " +
           "will still be affected by that regardless of your choice.");
           
    }
    command("say What would you like your emphasis on " +
            SD_LONG_STAT_DESC[stat] + " to be?");
            
    state = stat + 2;
    setup_cancel();
}

/*
 * Function name: speech_hook
 * Description  : This is how the NPC listens for the details of the
 *                auction. At each state it is waiting for information
 *                from the player.
 */
public void
speech_hook(string verb, object actor, string adverb, object *oblist,
    string text, int target)
{
    if (target < 0)
        return;

    if (actor->query_real_name()!=current_player)
        return;

    string str = lower_case(text);

    if (strlen(str) && str[strlen(str)-1]=='.')
        str=str[..strlen(str)-2];

    if (strlen(str) && str[strlen(str)-1]=='?')
        str=str[..strlen(str)-2];

    if (state == 1)
    {
        if (str == "yes")
        {
            request_focus(0);
        }
        if (str == "no")
        {
            cancel_convert();
        }
    }
    else if (state >=2 && state <= 7)
    {
        int index = member_array(str, EMPHASIS);
        if (index != -1)
        {
            desired_stats[state - 2] = index;
            if (state < 7)
            {
                command("say You have chosen a " + EMPHASIS[index] +
                  " focus on " + SD_LONG_STAT_DESC[state - 2] + ".");
                request_focus(state - 1);
            }
            else
            {
                confirm_focus(this_player());
            }
        }
    }
    else if (state == 8)
    {
        if (str == "yes")
        {
            finalize_morph(this_player());
        }
        else if (str == "no")
        {
            cancel_convert();
        }
    }
    else if (state == 101)
    {
        if (str == "yes")
        {
            finalize_racechange(this_player());
        }
        else if (str == "no")
        {
            cancel_convert();
        }
    }
    
}

public void
emote_hook(string emote, object actor, string adverb, object *oblist,
    int cmd_attr, int target)
{
    if (state == 1)
    {
        if (emote == "nod")
        {
            request_focus(0);
        }
        else if (emote == "shake")
        {
            cancel_convert();
        }
    }
    else if (state == 8)
    {
        if (emote == "nod")
        {
            finalize_morph(this_player());
        } 
        else if (emote == "shake")
        {
            cancel_convert();
        }
    }
    else if (state == 101)
    {
        if (emote == "nod")
        {
            finalize_racechange(this_player());
        } 
        else if (emote == "shake")
        {
            cancel_convert();
        }
    }
}

public void notify_options(object player)
{
    if (!player)
        return;
    if (environment(player) != environment(this_object()))
        return;
    if (!player->check_seen(this_object()))
        return;
    if (!interactive(player))
        return;
    string response = "";
    if (has_free_transform(player))
    {
        response += "You have a free transformation if you wish it.  ";
    }
    if (has_free_race_change(player))
    {
        string also = strlen(response) ? "also " : "";
        response += "You " + also + "have a free race change available.";
    }
    if (strlen(response))
    {
        command("say Greetings.  " + response);
    }

}

void init_living()
{
    ::init_living();
    set_alarm(0.5, 0.0, &notify_options(this_player()));
}