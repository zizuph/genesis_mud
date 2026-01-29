/*
 *  /d/Gondor/guilds/morgulmage/master/activity.c
 *
 *  This file is part of the Morgul Mage master object. It should
 *  not be loaded or called directly.
 *
 *  This activity meter is based on the original idleness system created
 *  by Chmee, and merely reimplemented to better fit the new structure
 *  of the Morgul Mage master object.
 *
 *  Created by Eowul, August 23rd, 2009
 *
 *  Revision History:
 *    March-19-2014: (Gorboth)  Commented out enforcement of activity to
 *                              retain Nazgul status until game activity
 *                              rises globally. Change back as needed.
 *    December 1, 2017: Finwe   Commented out messages to online GM. I don't 
 *                              need to see this info, and it borders on
 *                              mortal interference, imo.
 *    July 30, 2019: Cotillion  Added access check to some information as it
 *                              appears to only be used for mortal interference.
 */

#define WORKOHOLIC              10000
#define OUTSTANDING             6000
#define EXCELLENT               4000
#define VERY_GOOD               3000
#define GOOD                    2000
#define ABOVE_AVERAGE           1500
#define ACCEPTABLE              1000
#define WORRYING                750 

#define ACTIVITY_LEVEL_NAMES ({ "workoholic", "outstanding", "excellent", \
                                "very good", "good", "above average", \
                                "acceptable", "worrying" })
#define ACTIVITY_LEVELS      ({ WORKOHOLIC, OUTSTANDING, EXCELLENT, VERY_GOOD, \
                                GOOD, ABOVE_AVERAGE, ACCEPTABLE, WORRYING })

#define ACTIVITY_UPDATE_TIME    1800
#define ACTIVITY_TIME_PERIOD    (36 * 3600)
#define ACTIVITY_PERIODS        60

// Determines the time before activity information is purged (only happens 
// for non nazgul)
#define ACTIVITY_TIMEOUT        (90 * 24 * 60 * 60)

int activity_update_timer = 0;
static int activity_timer_id;

int calculate_activity_index(int activity) {
    for(int i = 0; i < sizeof(ACTIVITY_LEVELS) - 1; i++) {
        if(activity >= ACTIVITY_LEVELS[i]) return i;
    }
    return sizeof(ACTIVITY_LEVELS) - 1;
}

private void activity_log(string message) {
    log_file("morgulmage_activity_meter", ctime(time()) + " " +
        message + "\n", 0);
/*     
    object *online_guildmasters = map(
        SECURITY->query_guild_masters("mage"), find_player);
    online_guildmasters->catch_msg("[Morgul Mages] " + message + "\n");
*/
}

static int
check_access()
{
    string who = this_interactive()->query_real_name();
    
    if (SECURITY->query_wiz_rank(who) >= WIZ_ARCH)
        return 1;

    if (member_array(who, SECURITY->query_guild_masters("mage")) >= 0)
        return 1;

    return 0;
}

public int screen_nazgul(object mage) {
    string magename = get_mage_real_name(mage);
    if (member_array("activity_daily", m_indices(member_information[magename])) == -1)
        return 0;
        
    int activity_index = calculate_activity_index(member_information[magename]["activity_daily"]);
    switch(activity_index) {
        case 0: // WORKOHOLIC
        case 1: // OUTSTANDING
        case 2: // EXCELLENT
        case 3: // VERY GOOD
            mage->catch_msg("\nYou feel the Dark Lord's presence and realize He is "
                + "rather pleased with your dedication to the service and the "
                + "Society!\n\n");
            break;
        case 4: // GOOD
            mage->catch_msg("\nYou feel the Dark Lord's presence and realize He is "
                + "pleased with your dedication to the service!\n\n");
            break;
        case 5: // ABOVE_AVERAGE
            mage->catch_msg("\nYou feel the Dark Lord's presence and realize He has "
                + "noticed your dedication to the service!\n\n");
            break;
        case 6: // ACCEPTABLE
            mage->catch_msg("\nThe Dark Lord is somewhat pleased with your "
                + "dedication to the service!\n\n");
            break;
        case 7: // WORRYING
            mage->catch_msg("\nThe Dark Lord is seriously concerned about your "
                + "lack of dedication to the service!\n\n");
            break;
    }
    return 1;
}

public string appraise_nazgul(object me, object for_obj) {
    /*
	if (!me->query_nazgul()) return "";
    
    string error = (me == for_obj) ? " actually unable to pry any further information "
        + "on your status.\n" : "";
        
    if (!query_is_mage(me)) return error;
    
    string magename = get_mage_real_name(me);        
    if (member_array("activity_daily", m_indices(member_information[magename])) == -1)
        return error;
        
    int activity_index = calculate_activity_index(member_information[magename]["activity_daily"]);
    
    if ((me == for_obj) && (me->query_nazgul())) {
        string *descriptions = ({
            " feel irreplaceable.\n",
            " feel an immense burden of the ring.\n",
            " feel like competing with fellow Ringwraiths.\n",
            " get known in the Tower for your addiction to perfection.\n",
            " are sure of your place in the Society.\n",
            " are confident of your value for the Dark Lord.\n",
            " are doing fine.\n",
            " should seriously think about retirement.\n",
        });
        return descriptions[activity_index];
    }
    
    if (me->query_nazgul() && (for_obj->query_nazgul() == 2)) {
        string *descriptions = ({ 
            " should be slowed down for "+ me->query_possessive()+
                " own good.\n",
            " is going to burn out soon.\n",
            " should share the duties with fellow Raiders.\n",
            " serves as an example for the Ringwraiths.\n",
            " proved "+ me->query_possessive()+
                " value in the eyes of the Dark Lord.\n",
            " works hard to be noticed by the Dark Lord.\n",
            " is doing fine.\n",
            " feels uncomfortable with the Nazgul's duties.\n",
        });
   
        return capitalize(me->query_pronoun()) + descriptions[activity_index];
    }
    */
    return "";
}

void calculate_activity(string mage) {
    int total_activity = 0;
    
    foreach(int activity : member_information[mage]["activity_averages"]) {
        total_activity += activity;
    }
    
    int average_per_hour = total_activity / 
        sizeof(member_information[mage]["activity_averages"]);
        
    int activity_per_day = average_per_hour * 24;
    member_information[mage]["activity_daily"] = activity_per_day;
    
    activity_log("New activity for " + capitalize(mage) + " is " + activity_per_day 
        + " (" + ACTIVITY_LEVEL_NAMES[calculate_activity_index(activity_per_day)] + ")");
}

void initialize_activity_counter(string mage) {
    if(member_array("activity_averages", m_indices(member_information[mage])) != -1) 
        return;
     
    int *averages = ({ });     
    for(int i = 0; i < ACTIVITY_PERIODS; i++) {
        averages += ({ ftoi(1.1 * itof(ACCEPTABLE)) / 24 });
    }
    
    activity_log("Activity counter initialized for " + capitalize(mage));
    
    member_information[mage]["activity_averages"] = averages;
    member_information[mage]["activity_current"] = 0;
    calculate_activity(mage);
}


void increase_activity(mixed mage, int activity) {
    if (!query_is_mage(mage)) return;
    
    string magename = get_mage_real_name(mage);
    
    if(query_is_nazgul(mage)) initialize_activity_counter(magename);
    else if(member_array("activity_averages", 
        m_indices(member_information[magename])) == -1) return;
    
    member_information[magename]["activity_current"] += activity;
}

public int is_idle( mixed mage ) {
    string magename = get_mage_real_name(mage);        
    if (member_array("activity_daily", m_indices(member_information[magename])) == -1)
        return 0;
    
    return (member_information[magename]["activity_daily"] < WORRYING);
}

void append_average(string mage, int average) {
    int *averages = ({ average });
    int *current_averages = member_information[mage]["activity_averages"];
    
    for(int i = 1; i < MIN(ACTIVITY_PERIODS, sizeof(current_averages)); i++) {
        averages += ({ current_averages[i - 1] });
    }
    
    member_information[mage]["activity_averages"] = averages;
    activity_log("New average " + average + " prepended for " + 
        capitalize(mage) + ": " + implode(map(averages, &sprintf("%d")), ", "));
}

void calculate_averages(int expired_time) {
    int hours_expired = MAX(1, (expired_time / 3600));
    
    activity_log("Recalculation of activity started, " + expired_time 
        + "s since last calculation.");
        
    foreach(string mage : m_indices(member_information)) {
        if(member_array("activity_averages", m_indices(member_information[mage])) == -1)
            continue;
            
        int activity_per_hour = member_information[mage]["activity_current"] /
                                    hours_expired;
        int max_per_hour = (ftoi(itof(WORKOHOLIC) * 1.5)) / 24;

        if (activity_per_hour > max_per_hour) {           
            activity_log("Current activity for " + capitalize(mage) + " was " 
                + member_information[mage]["activity_current"] + " but got "
                + "capped (" + activity_per_hour + " per hour)");
        } else {
            activity_log("Current activity for " + capitalize(mage) + " is " 
                + member_information[mage]["activity_current"] + " (" 
                + activity_per_hour + " per hour)");
        }
            
        
        append_average(mage, activity_per_hour);
        calculate_activity(mage);
        member_information[mage]["activity_current"] = 0;
    }
}


void add_mage_to_activity_meter(mixed mage) {
    string magename = get_mage_real_name(mage);
    if(member_array("activity_averages", m_indices(member_information[magename])) == -1) {
        activity_log(capitalize(magename) + " was newly added to the activity meter.");
        initialize_activity_counter(magename);
    } else {
        activity_log(capitalize(magename) + " was added to the activity meter again.");
        increase_activity(mage, OUTSTANDING);
    }
    m_delkey(member_information[magename], "activity_removal");
    save_data();
}

void remove_mage_from_activity_meter(mixed mage, int removal_time = time() + ACTIVITY_TIMEOUT) {
    string magename = get_mage_real_name(mage);
    
    if (removal_time) {
        activity_log("Activity information for " + capitalize(magename) + " will "
            + "be removed (and measuring will stop) on " + ctime(removal_time) + ".");
            
        member_information[magename]["activity_removal"] = removal_time;
    } else {
        activity_log("Activity information purged for " + capitalize(magename) 
            + ". No more measuring will occur.");
            
        m_delkey(member_information[magename], "activity_removal");
        m_delkey(member_information[magename], "activity_daily");
        m_delkey(member_information[magename], "activity_current");
        m_delkey(member_information[magename], "activity_averages");
    }
    save_data();
}

void purge_activity_meter() {
    foreach(string mage, mapping data : member_information) {
        if (data["activity_removal"] && (data["activity_removal"] < time())) {
            activity_log(capitalize(mage) + "'s purge date ("
                + ctime(data["activity_removal"]) + ") passed.");
            remove_mage_from_activity_meter(mage, 0); 
        }
    }
}

void validate_nazgul_activity() {
    foreach(string mage, mapping data : member_information) {
        if (!query_is_nazgul(mage)) continue;
        
        if (member_array("activity_daily", m_indices(data)) == -1) {
            activity_log(capitalize(mage) + " is listed as Nazgul but has no "
                + "activity information.");
            continue;
        }
        
/* Until the game returns to a much higher level of activity, it does
 * not make sense to enforce such an activity meter. I will thus comment
 * it out. If a future wizard responsible for this content feels it is
 * in the best interests of the guild to re-activate it, by all means,
 * do so. (Gorboth, March 2014)
        if (data["activity_daily"] < WORRYING) {
            activity_log(capitalize(mage) + " is no longer an active Nazgul, "
                + "demoting.");

            send_message(mage, "\nAngered by your lack of dedication the Dark "
                + "Lord takes your powers away!\n\n");
            remove_player_as_nazgul(mage, "inactivity");
        }
 */
    }
}

void activity_timer() {
    activity_update_timer++;
    
    int expired_time = activity_update_timer * ACTIVITY_UPDATE_TIME;
    if (expired_time >= ACTIVITY_TIME_PERIOD) {
        calculate_averages(expired_time);
        validate_nazgul_activity();
        activity_update_timer = 0;
    }
    
    purge_activity_meter();
    save_data();
}

void startup_activity_meter() {
    if (activity_timer_id) remove_alarm(activity_timer_id);
    activity_timer_id = set_alarm(itof(ACTIVITY_UPDATE_TIME), 
                                  itof(ACTIVITY_UPDATE_TIME), activity_timer);
    purge_activity_meter();
    validate_nazgul_activity();
}

string get_standard_activity_information()
{
    mixed alarm_info = get_alarm(activity_timer_id);
    
    return sprintf("Remaining until next period: %s (update in %s)\n", 
        convtime(ACTIVITY_TIME_PERIOD - (activity_update_timer * ACTIVITY_UPDATE_TIME)),
        convtime(ftoi(alarm_info[2])));
}

int query_periods_until_removal(mixed mage) {
    string magename = get_mage_real_name(mage);
    
    if(member_array("activity_averages", m_indices(member_information[magename])) == -1) 
        return 0;
        
    int remaining_buffer = ftoi(itof(member_information[magename]["activity_daily"] - WORRYING) 
        * (itof(ACTIVITY_PERIODS) / 24.0));
    
    for(int days = sizeof(member_information[magename]["activity_averages"]) - 1; days >= 0; days--) {
        int activity_on_day = member_information[magename]["activity_averages"][days];        
        remaining_buffer -= activity_on_day;
        if (remaining_buffer < 0) return ACTIVITY_PERIODS - days;
    }
    
    return 0;
}

public string describe_time_remaining(mixed mage, string *descriptions) {
    int remaining_periods = query_periods_until_removal(mage);
	return GET_NUM_DESC(remaining_periods, ACTIVITY_PERIODS, descriptions);
}

public int query_time_until_removal(mixed mage) {
    int periods_until_removal = query_periods_until_removal(mage);
    int current_period_time_remaining = ACTIVITY_TIME_PERIOD - (activity_update_timer * ACTIVITY_UPDATE_TIME);
    int other_periods = (periods_until_removal - 1) * ACTIVITY_TIME_PERIOD;
    return (current_period_time_remaining + other_periods);
}

string query_activity_report() 
{
    if (!check_access())
        return "";

    string result = "Current performance score for all mages with their activity "
        + "timer enabled:\n\n";
    
    foreach(string mage, mixed data : member_information) {
        if(member_array("activity_daily", m_indices(data)) == -1) continue;
        
        int periods_until_removal = query_periods_until_removal(mage);
		
        string remaining_periods = (query_is_nazgul(mage) && (periods_until_removal < (ACTIVITY_PERIODS / 2))) ? 
            sprintf("%d periods (%s) until demotion", periods_until_removal, 
				convtime(query_time_until_removal(mage))) : "";
            
        string name = (query_is_nazgul(mage) ? "" : "(*) ") + capitalize(mage);
        string removal = data["activity_removal"] ? ctime(data["activity_removal"]) : remaining_periods;
            
        result += sprintf("%15s - %5d %-15s %s\n",
            name, data["activity_daily"],
            "(" + ACTIVITY_LEVEL_NAMES[calculate_activity_index(data["activity_daily"])] + ")",
            removal);
    }
    
    result += "\nNon-nazgul are marked with an asterisk, if a date is mentioned, "
        + "activity information will be purged on that date.\n"
        + get_standard_activity_information();        
        
    return result;
}


string query_activity_for_mage(mixed mage) {
    string magename = get_mage_real_name(mage);

    if(member_array(magename, m_indices(member_information)) == -1)
        return capitalize(magename) + " is not a mage.\n";
        
    if(member_array("activity_averages", m_indices(member_information[magename])) == -1)
        return "No activity information is stored for " + capitalize(magename) + ".\n";
        
    string result = capitalize(magename) + "'s activity history. Most recent addition "
        + "added on top.\nActivity number listed is the average per hour of activity "
        + "during that period.\n\n";
        
    string day_results = "";
    for(int days = 0; days < sizeof(member_information[magename]["activity_averages"]); days++) {
        int activity_on_day = member_information[magename]["activity_averages"][days];
        day_results += sprintf("%3d period ago: %5d (%s)\n", (days + 1), activity_on_day,
            ACTIVITY_LEVEL_NAMES[calculate_activity_index(activity_on_day * 24)]);
    }
    
    int screen_length = 80;
    result += sprintf("%-*#s", screen_length, day_results);
    result += sprintf("\n\n%s's performance score averaged over %d periods: %d per 24 hours (%s).\n", 
            capitalize(magename),
            sizeof(member_information[magename]["activity_averages"]),
            member_information[magename]["activity_daily"],
            ACTIVITY_LEVEL_NAMES[calculate_activity_index(member_information[magename]["activity_daily"])]);
    result += sprintf("Today's score (non averaged): %d\n", member_information[magename]["activity_current"]);
    
    if(query_is_nazgul(magename)) {
        result += sprintf("Periods until demotion: %d (%s)\n", 
			query_periods_until_removal(magename), 
			convtime(query_time_until_removal(magename)));
    }
    
    if(member_information[magename]["activity_removal"]) {
        result += "Activity information will be purged on "
            + ctime(member_information[magename]["activity_removal"]) + ".\n";
    }
    
    result += get_standard_activity_information();
    
    return result;
}
