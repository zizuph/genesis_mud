/*
 *  morph_sh.c
 *
 *  This shadow allows players to move a portion of their currently
 *  experience from a completely new configuration, without having
 *  to suicide all their experience away.
 *
 *  The Thaumaturgist in the palace can place this shadow on the
 *  players based on their desired experience allocations.
 *
 *  Author: Zizuph, Sept 2021.
 *  
 *  Thanks to Cotillion for adding modify_acc_exp to the mudlib
 *  and making this a much cleaner implementation.
 */

#include "../local.h"

inherit "/std/shadow";

#include <macros.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <ss_types.h>

#define LOG_FILE (KRYNN_DIR + "log/morphlog")

// 7.2h per morph
#define REAL_TIME_PER_MORPH      25920

// Cherek asked for no online time requirement.
#define ONLINE_TIME_PER_MORPH    0     
#define MORPH_AMOUNT             1000000    
#define ALARM_RATE               700.0

int in_morph;

int creation_time;
int creation_player_age;
int number_morphs;

float* desired_ratios;

int query_acc_exp_totals() {
    return
        shadow_who->query_acc_exp(0) + shadow_who->query_acc_exp(1) +
        shadow_who->query_acc_exp(2) + shadow_who->query_acc_exp(3) +
        shadow_who->query_acc_exp(4) + shadow_who->query_acc_exp(5);
}

void log_entry(string message)
{
    write_file(LOG_FILE, sprintf("%s %s %s\n",
        ctime(time()), shadow_who->query_real_name(), message));
}

void log_stats(string message)
{
    string status_msg = sprintf("%s: STR %d DEX %d CON %d INT %d WIS "
      + "%d DIS %d Total %d query_exp %d morphs %d.",
    message,
    shadow_who->query_acc_exp(0), shadow_who->query_acc_exp(1),
    shadow_who->query_acc_exp(2), shadow_who->query_acc_exp(3),
    shadow_who->query_acc_exp(4), shadow_who->query_acc_exp(5),
    query_acc_exp_totals(), shadow_who->query_exp(), number_morphs);
    log_entry(status_msg);
}

public void readd_morph_shadow()
{
    shadow_who->add_autoshadow(sprintf(
        "%s:R%1.2f,%1.2f,%1.2f,%1.2f,%1.2f,%1.2f,%d,%d,%d",
        MASTER_OB(this_object()),
        desired_ratios[0], desired_ratios[1],
        desired_ratios[2], desired_ratios[3],
        desired_ratios[4], desired_ratios[5],
        creation_time, creation_player_age,
        number_morphs));
}

void remove_morph_shadow() {
    log_entry("completed morph.");
    shadow_who->catch_msg("Your body is returning to normal, as the " +
        "process of rapid change has now subsided.\n");
    shadow_who->remove_subloc("morph");
    shadow_who->remove_autoshadow(MASTER + ":");
    remove_shadow();
}

void describe_stat_change(int stat, int up)
{
    // Give a message 1/3 of the time for stat 
    // changes.
    if (random(3))
    {
        return;
    }
    
    string msg;
    
    switch (stat)
    {
    case SS_STR:
        if (up)
        {
            msg = one_of_list(({
                "You feel a burst of energy in your arms, as if you " +
                "discovered some long lost inner reserve.",
                "The load on your back starts to feel less burdensome.",
                "There is a tingling in your growing muscles.",
            }));
        }
        else
        {
            msg = one_of_list(({
                "You feel as though your muscles have withered a bit.",
                "You feel weaker in your bones.",
                "Everything is just a bit heavier than before.",
            }));
        }
    break;
    case SS_DEX:
        if (up)
        {
            msg = one_of_list(({
                "You are feeling more agile than ever before.",
                "You feel like your accuracy has improved a bit.",
                "Your joints feel more flexible than just a few minutes ago.",
            }));
        }
        else
        {
            msg = one_of_list(({
                "You feel less agile than you did just moments ago.",
                "Your hands are a little numb.",
                "You feel like your accuracy has lessened.",
            }));
        }
    break;
    case SS_CON:
        if (up)
        {
            msg = one_of_list(({
                "You feel a little bit healthier than before.",
                "You feel like your stamina has improved.",
                "You have a spring in your step, as if you could walk " +
                "for miles.",
            }));
        }
        else
        {
            msg = one_of_list(({
                "You notice that you are tiring out easier than before.",
                "Your next long journey looks more daunting than usual.",
                "Old wounds ache a little more than expected.",
            }));
        }
    break;
    case SS_INT:
        if (up)
        {
            msg = one_of_list(({
                "A long-lost memory returns to your mind, as if you had " +
                "never forgotten it.",
                "You are more than ready to tackle your next problem.",
                "Your mind feels as if it is a step ahead of your body.",
            }));
        }
        else
        {
            msg = one_of_list(({
                "A sense of grogginess pours over you.",
                "You briefly lose track of your surroundings.",
                "You blink, and realize a lost moment has passed you by.",
            }));
        }
    break;
    case SS_WIS:
        if (up)
        {
            msg = one_of_list(({
                "You think back on a prior encounter with new revelations.",
                "An old memory flashes in your head, and you note the " +
                "insight it brings.",
                "You realize that you are coming to a better understanding " +
                "of yourself.",
            }));
        }
        else
        {
            msg = one_of_list(({
                "You feel a bit of a headache coming on.",
                "Random thoughts enter your mind, distracting you from " +
                "the task at hand.",
                "You struggle to recall the details of a recent encounter.",
            }));
        }
    break;
    case SS_DIS:
        if (up)
        {
            msg = one_of_list(({
                "You are feeling a bit more secure in difficult situations.",
                "You notice a marked improvement in your confidence.",
                "You look forward to dealing with your next difficult " +
                "situation.",
            }));
        }
        else
        {
            msg = one_of_list(({
                "What was that noise?  You are suddenly startled, " +
                "though the feeling slowly passes.",
                "You feel less confident about your combat prowess.",
                "You notice you are less calm than usual.",
            }));
        }
    break;
    }
    
    if (msg)        
        shadow_who->catch_msg(msg + "\n");
}


int estimate_remaining_morphs()  {
    
    float ratio_sum = 0.0;
    // We don't use shadow_who->query_exp here, because it does
    // not add up to the sum of the stats (it is off by just
    // a little bit).
    int total_exp = 0;
    for (int i = 0; i < SS_NO_EXP_STATS; i++) {
        ratio_sum += desired_ratios[i];
        total_exp += shadow_who->query_acc_exp(i);
    }
    
    // Split up total exp to the ideal values per stat.
    int* expected_exp = allocate(SS_NO_EXP_STATS);
    for (int i = 0; i < SS_NO_EXP_STATS; i++) {
        expected_exp[i] = ftoi(itof(total_exp) 
            * desired_ratios[i] / ratio_sum);
        ratio_sum -= desired_ratios[i];
        total_exp -= expected_exp[i];
    }

    // Determine how much we actually want to modify the stats.
    int total_up = 0;
    int pre_loss_delta;
    for (int i = 0; i < SS_NO_EXP_STATS; i++) {
        pre_loss_delta = expected_exp[i] - shadow_who->query_acc_exp(i);
        total_up += pre_loss_delta > 0 ? pre_loss_delta : 0;
    }
    return total_up / MORPH_AMOUNT + 1;
}

void perform_morph(int xp_amount) {

    if (in_morph)
        return;
    number_morphs++;
    
    // We cannot drop the exp by more than is already available.
    xp_amount = min(xp_amount, shadow_who->query_exp_combat());
    
    float ratio_sum = 0.0;

    // We don't use shadow_who->query_exp here, because it does
    // not add up to the sum of the stats (it is off by just
    // a little bit).
    int total_exp = 0;
    for (int i = 0; i < SS_NO_EXP_STATS; i++) {
        ratio_sum += desired_ratios[i];
        total_exp += shadow_who->query_acc_exp(i);
    }
    
    // Split up total exp to the ideal values per stat.
    int* expected_exp = allocate(SS_NO_EXP_STATS);
    for (int i = 0; i < SS_NO_EXP_STATS; i++) {
        expected_exp[i] = ftoi(itof(total_exp) 
            * desired_ratios[i] / ratio_sum);
        ratio_sum -= desired_ratios[i];
        total_exp -= expected_exp[i];
    }
        
    in_morph = 1;

    // Determine how much we actually want to modify the stats.
    int* pre_loss_delta = allocate(SS_NO_EXP_STATS);
    int total_up = 0;
    int total_down = 0;
    for (int i = 0; i < SS_NO_EXP_STATS; i++) {
        pre_loss_delta[i] = expected_exp[i] - shadow_who->query_acc_exp(i);
        total_up += pre_loss_delta[i] > 0 ? pre_loss_delta[i] : 0;
        total_down += pre_loss_delta[i] < 0 ? pre_loss_delta[i] : 0;
    }

    // If we have less than xp_amount to shift in total, reduce
    // desired shift to that amount.
    xp_amount = min(xp_amount, total_up);   

    log_stats("start of morph");

    int* new_stats = allocate(SS_NO_EXP_STATS);
    int allocatable_up_exp = xp_amount;
    int allocatable_down_exp = -xp_amount;

    // Move xp_amount from the stats that are too high, to the stats
    // that are too low.
    for (int i = 0; i < SS_NO_EXP_STATS; i++) {
        new_stats[i] = shadow_who->query_acc_exp(i);            
        if (pre_loss_delta[i] > 0)
        {
            int delta = pre_loss_delta[i] * allocatable_up_exp / 
               total_up;
            total_up -= pre_loss_delta[i];
            allocatable_up_exp -= delta;
            new_stats[i] += delta;            
            if (pre_loss_delta[i] > 1000)
            {
                set_alarm(itof(random(30) + 30), 0.0, 
                    &describe_stat_change(i, 1));
            }
        }
        if (pre_loss_delta[i] < 0)
        {
            int delta = pre_loss_delta[i] * allocatable_down_exp / 
               total_down;
            total_down -= pre_loss_delta[i];
            allocatable_down_exp -= delta;
            new_stats[i] += delta;            
            if (pre_loss_delta[i] < -1000)
            {
               set_alarm(itof(random(30) + 30), 0.0, 
                    &describe_stat_change(i, 0));
            }
        }
    }
    
    // Debug logging for sanity check.
    //log_entry(sprintf("Remaining up down %d %d %d %d", total_up, 
    //   allocatable_up_exp, total_down, allocatable_down_exp));
    
    int result = shadow_who->modify_acc_exp(new_stats);
    if (result == -2)
    {
        log_entry(sprintf(
            "modify_exp failed, attempted allocation: %d %d %d %d %d %d (%d)",
            new_stats[0], new_stats[1], new_stats[2],
            new_stats[3], new_stats[4], new_stats[5],
            new_stats[0] + new_stats[1] + new_stats[2] +
            new_stats[3] + new_stats[4] + new_stats[5]));
    }
    else if (result == -1)
    {
        log_entry("Invalid modify_acc_exp size");
    }
    else
    {
        log_stats("end of morph");
    }
    in_morph = 0;

    if (xp_amount <= MORPH_AMOUNT / 10) {
        remove_morph_shadow();
        return;
    }

    readd_morph_shadow();
}

public int has_morph_shadow()
{
    return 1;
}

public void maybe_perform_morph()
{
    if (time() - creation_time < number_morphs * REAL_TIME_PER_MORPH)
        return;
    if (shadow_who->query_age() - creation_player_age < number_morphs
        * ONLINE_TIME_PER_MORPH)
        return;
    perform_morph(MORPH_AMOUNT);    
}

public string
show_subloc(string subloc, object me, object viewer)
{
    string ret = "";

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return me->show_subloc(subloc, me, viewer);
    
    if (subloc != "morph")
        return me->show_subloc(subloc, me, viewer);

    if (me != viewer)
        return "";
    
    int remaining = estimate_remaining_morphs();
    int total = remaining + number_morphs;
    if (total + remaining == 0)
      return "";
  
    return "You feel you are " + GET_NUM_DESC(total - remaining, 
        total, SD_ADVANCE_DESCS) +
        " finishing your transformation.\n";
        
    return ret;
}


public void configure_sublocs()
{
  shadow_who->add_subloc("morph", this_object());    
}


public void configure_morph_shadow(float str_ratio,
    float dex_ratio, float con_ratio, float int_ratio,
    float wis_ratio, float dis_ratio, object player)
{
    setuid();
	seteuid(getuid());

    creation_time = time();
    creation_player_age = player->query_age();
    number_morphs = 0;
    desired_ratios =  ({str_ratio, dex_ratio, con_ratio,
                        int_ratio, wis_ratio, dis_ratio });
    // Remove an old shadow, if it is there.                        
    player->remove_morph_shadow();
    shadow_me(player);
    readd_morph_shadow();
    
    shadow_who->catch_msg("An uncertain feeling overcomes you, " +
        "as if your body was being stretched in uncomfortable " +
        "ways.  Your mind is scattered, your limbs twitching. " +
        "Your muscles burn as if you had run a marathon.  " +
        "Everything feels off, and the feeling grows in intensity.\n");
        
    string status_msg = sprintf("initiated morph: STR %1.2f DEX %1.2f "
        + "CON %1.2f INT %1.2f WIS %1.2f DIS %1.2f.\n",
        str_ratio, dex_ratio, con_ratio, int_ratio, wis_ratio,
        dis_ratio);
    log_entry(status_msg);
    configure_sublocs();
    set_alarm(ALARM_RATE, ALARM_RATE, maybe_perform_morph);
}

public string stat_living()
{
    string result = shadow_who->stat_living();
    result += "Undergoing stat adjustments.  Ratios:\n";
    result += sprintf("Str: %2.2f, Dex: %2.2f, Con: %2.2f ",
       desired_ratios[0], desired_ratios[1], desired_ratios[2]);
    result += sprintf("Int: %2.2f, Wis: %2.2f, Dis: %2.2f\n",
       desired_ratios[3], desired_ratios[4], desired_ratios[5]);
    result += sprintf("Estimated remaining steps %d\n",
       estimate_remaining_morphs());
    return result;
}

public void
autoload_shadow(mixed arg)
{
	setuid();
	seteuid(getuid());
    desired_ratios = allocate(SS_NO_EXP_STATS);
    if (sscanf(arg,"R%f,%f,%f,%f,%f,%f,%d,%d,%d",
        desired_ratios[0], desired_ratios[1],
        desired_ratios[2], desired_ratios[3],
        desired_ratios[4], desired_ratios[5],
        creation_time, creation_player_age,
        number_morphs)) {
        ::autoload_shadow(arg);
        set_alarm(ALARM_RATE, ALARM_RATE, maybe_perform_morph);
        configure_sublocs();
    }
    else
    {
        write_file(LOG_FILE, sprintf("%s %s failed to load shadow\n",
        ctime(time()), previous_object()->query_real_name()));
    }
}
