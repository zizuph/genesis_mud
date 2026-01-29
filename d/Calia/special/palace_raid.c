
/* 
   Code for kroug raids on the crystalline palace. 
   This code controls kroug movements and provides all functionality for
   starting raids, terminating raids, giving current status 
   information about raids and initiating raid reports. 
   The palace raid room is the means by which this code is controlled and 
   accessed. This code interfaces with the kroug brain to initiate kroug 
   resets and find out what krougs exist.

   Coded by Maniac, late April/early May 1996 
   New warnings added, Maniac, 3/6/96
   Fixed runtime error with groups > 8, Petros, 10/31/2008
*/

#pragma no_clone
#pragma strict_types
#pragma no_inherit

#include <std.h>
#include <language.h>
#include <composite.h>
#include "/d/Calia/domain.h"
#include CALIAN_GUILD_BASE_DEF
#include "/d/Calia/mountain/defs.h"

inherit "/std/object"; 
inherit "/d/Calia/std/kroug_util"; 
#include "/d/Calia/sys/kroug.h"

#define STEP_DELAY 5 

#define RAID_PRE_BLOCK if (raid_status == RAID_PRE_RAID) \
                   {  notify_fail("Currently in the pre-raid stage.\n"); \
                      return 0;  }

#define ROOM_CHECK_BLOCK if (raid_status == RAID_CHECK_ROOMS) \
                             {  notify_fail("Currently checking rooms.\n"); \
                                return 0;  }

#define RAID_WARNING_BLOCK if (raid_status == RAID_WARNING_PERIOD) \
              {  notify_fail("Currently in the warning period stage.\n"); \
                  return 0;  }

#define RAID_ACTIVE_BLOCK if (raid_status == RAID_ACTIVE) \
                             {  notify_fail("Raid currently active.\n"); \
                                return 0;  }

#define TERMINATING_BLOCK if (raid_status == RAID_TERMINATING) \
            {  notify_fail("Currently terminating raid.\n"); \
               return 0; }

#define TERMINATED_BLOCK if (raid_status == RAID_TERMINATED) \
            {  notify_fail("Raid has been terminated.\n"); \
               return 0; }

#define RAID_OVER_BLOCK if (raid_status == RAID_OVER) \
            {  notify_fail("Raid is over.\n"); \
               return 0; }

#define MEMORY_BLOCK \
       if (SECURITY->query_memory_percentage() >= RAID_MEMLIM) \
            {  notify_fail("Memory is a little high, better not.\n"); \
               return 0; }



#define NOTHING 0
#define OPEN_DOORS "open_doors"
#define CHARM_HURN "charm_hurn"
#define HALF_WAY "half_way"

#define SKIP "skip"
#define END "end"

/* Saveable globals */ 
mapping scores;
int max_strength, strength, raid_status, 
    number_groups, warning_dur, done_note; 
int kr_test_index, countdown, group_cycle, time_start, time_end, hw, hurn; 
string *casualties;
object *krougs; 

int *group_stage; 
mixed kroug_groups; 


/* Static globals */ 

/* 
   Basic possible mission steps. 
   pre-action, move living message, room to move to, post-action.
*/ 
static string *kroug_rooms; 

static mapping raid_steps = 
      ([ "croad1" : ({ NOTHING, "towards the mountain",  
                       (CROAD+"croad1"), NOTHING }), 
         "croad2" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad2"), NOTHING }), 
         "croad3" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad3"), NOTHING }), 
         "croad4" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad4"), NOTHING }), 
         "croad5" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad5"), NOTHING }), 
         "croad6" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad6"), NOTHING }), 
         "croad7" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad7"), NOTHING }), 
         "croad8" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad8"), NOTHING }), 
         "croad9" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad9"), NOTHING }), 
         "croad10" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad10"), NOTHING }), 
         "croad11" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad11"), NOTHING }), 
         "croad12" : ({ HALF_WAY, "further up the mountain", 
                        (CROAD+"croad12"), NOTHING }), 
         "croad13" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad13"), NOTHING }), 
         "croad14" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad14"), NOTHING }), 
         "croad15" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad15"), NOTHING }), 
         "croad16" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad16"), NOTHING }), 
         "croad17" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad17"), NOTHING }), 
         "croad18" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad18"), NOTHING }), 
         "croad19" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad19"), NOTHING }), 
         "croad20" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad20"), NOTHING }), 
         "croad21" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad21"), NOTHING }), 
         "croad22" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad22"), NOTHING }), 
         "croad23" : ({ NOTHING, "further up the mountain", 
                        (CROAD+"croad23"), NOTHING }), 
         "croad24" : ({ NOTHING, "onto the plateau", 
                        (CROAD+"croad24"), NOTHING }), 
         "croad25" : ({ NOTHING, "further along the plateau", 
                        (CROAD+"croad25"), NOTHING }), 
         "croad26" : ({ NOTHING, "further along the plateau", 
                        (CROAD+"croad26"), CHARM_HURN }), 
         "croad27" : ({ NOTHING, "to the palace gates",  
                        (CROAD+"croad27"), NOTHING }), 
         "entrance" : ({ OPEN_DOORS, "into the palace", 
                        (CRPALACE_LIGHT_ROOMS+"entrance"), NOTHING }), 
         "hall" : ({ NOTHING, "towards the hall", 
                        (CRPALACE_LIGHT_ROOMS+"hall"), NOTHING }), 
         "bank" : ({ NOTHING, "towards the bank", 
                        (CRPALACE_LIGHT_ROOMS+"bank"), NOTHING }), 
         "shop" : ({ NOTHING, "towards the shop", 
                        (CRPALACE_LIGHT_ROOMS+"shop"), NOTHING }), 
         "post" : ({NOTHING, "towards the post office", 
                        (CRPALACE_LIGHT_ROOMS+"post"), NOTHING }), 
         "trainroom" : ({NOTHING, "towards the guild room", 
                        (CRPALACE_LIGHT_ROOMS+"trainroom"), NOTHING }), 
         "training" : ({NOTHING, "towards the training room", 
                        (CRPALACE_LIGHT_ROOMS+"training"), NOTHING }), 
         "stairs" : ({NOTHING, "towards the stairs",  
                      (CRPALACE_LIGHT_ROOMS+"stairs"), NOTHING }), 
         "lightroom" : ({NOTHING, "towards the light room",  
                      (CRPALACE_LIGHT_ROOMS+"lightroom"), NOTHING }), 
         "silver" : ({NOTHING, "towards the silver room",  
                      (CRPALACE_LIGHT_ROOMS+"silver"), NOTHING }), 
         "gold" : ({NOTHING, "towards the gold room",  
                      (CRPALACE_LIGHT_ROOMS+"gold"), NOTHING }), 
         "bronze" : ({NOTHING, "towards the bronze room",  
                      (CRPALACE_LIGHT_ROOMS+"bronze"), NOTHING }), 
         "white" : ({NOTHING, "towards the white room",  
                      (CRPALACE_LIGHT_ROOMS+"white"), NOTHING }), 
    ]); 

static string * basic_mission_steps = ({
        "croad1", "croad2", "croad3", "croad4",
        "croad5", "croad6", "croad7", "croad8", "croad9", 
        "croad10", "croad11", "croad12", "croad13", "croad14", 
        "croad15", "croad16", "croad17", "croad18", "croad19", 
        "croad20", "croad21", "croad22", "croad23", "croad24", 
        "croad25", "croad26", "croad27", "entrance" 
    });
    
static string * end_rooms = ({
        "hall",
        "trainroom",
        "training",
        "stairs",
        "silver",
        "bronze",
        "gold",
        "white"
    });

static mixed group_instr = ({ });


void
clean_krougs()
{
    krougs = filter(krougs, objectp); 
}



void
clean_groups()
{
    int i;

    for (i = 0; i < number_groups; i++) 
        if (sizeof(kroug_groups[i])) 
             kroug_groups[i] = filter(kroug_groups[i], objectp);  
}



int
mstr()
{
    clean_krougs(); 
    return sizeof(krougs); 
}


void
raid_log(object tp, string s)
{
    log_file("palace_raid", 
           capitalize(tp->query_real_name()) + " " + s + " " + 
                       ctime(time()) + ".\n"); 
}


void
casualty(string name)
{
    casualties += ({ name });  
    tell_room(PALACE_RAID_ROOM, name + " is casualty number " +
              LANG_WNUM(sizeof(casualties)) + ".\n"); 
}


void
kroug_death(string killer_name, int kt)
{
    mixed t;
    int v;

    tell_room(PALACE_RAID_ROOM,  
              killer_name + " just killed " + 
              LANG_ADDART(KROUG_DESC(kt, 1)) + ".\n");    

    t = scores[killer_name];  
    if (!t)  {
        t = allocate(NUM_KROUG_TYPES); 
        scores += ([ killer_name : t ]); 
    }

    t[kt]++; 
    scores = m_delete(scores, killer_name);  
    scores += ([ killer_name : t ]); 
}


string
query_raid_room()
{
    return PALACE_RAID_ROOM; 
}


void
remove_object()
{
    object ti;

    /* save state on removal of object. */ 
    save_object(PALACE_RAID_SAVE); 
    ti = this_interactive(); 
    if (objectp(ti)) 
        tell_room(PALACE_RAID_ROOM, "Palace raid code removal " + 
           "caused by " + capitalize(ti->query_real_name()) + ".\n");  

    ::remove_object(); 
}



void
informer_note()
{
     object inf;
     string *possin, ir, ch, *dx;
     int cht, ht, i, j;

     if (raid_status != RAID_OVER)
         return;

     possin = ({ ("Today a body of unrepentantly filthy krougs " +
               "raided the palace."), 
              ("Hear ye! Another nasty influx of raving krougs!"), 
              ("A force of warriors loyal to the foul wizard Kroug "+ 
               "had a go at us again."), 
              ("They caught me in my lunch break this time. It's " +
               "a hard life for a reporter."), 
              ("Hark! Those fetid lunatics from the south are at " +
               "it again!"), 
              ("The defenders of Calia are being kept busy as usual."), 
              ("Gather round and listen to my brief tale " +
               "of swashbuckling heroism."), 
              ("Harken to my statistical analysis of heated battle!"),  
              ("They came, they saw, they had a bit of a look around."), 
              ("Alas for a moments peace in our fair land!"),  
              ("Greetings in the name of Caliana!") }); 

     ir = (possin[random(sizeof(possin))] + 
          " The raid details were as follows."); 

     inf = clone_object("/d/Calia/special/informer"); 
     inf->set_board_room(CRPALACE_LIGHT_ROOMS+"trainroom");   
     inf->set_additional(0); 
     inf->set_intro(ir);   

     /* Establish champion score */ 
     ht = 0; 
     dx = m_indexes(scores); 
     for (i = 0; i < sizeof(dx); i++)  {
         cht = 0;
         for (j = 0; j < sizeof(scores[dx[i]]); j++)  
             cht += (scores[dx[i]][j] * (j+1)); 
         if (cht > ht)  {
             ht = cht; 
             ch = dx[i];  
         }
    }

    tell_room(PALACE_RAID_ROOM, ch + " wins with a score of " + ht + ".\n"); 

    inf->set_champion(ch);  
    inf->set_champion_kills(scores[ch]); 
    inf->set_slayers(dx); 
    inf->set_total_time((time_end - time_start) / 60);  
    inf->set_total_krougs(strength); 
    inf->set_casualties(casualties); 
    inf->activate(); 
    done_note = 1;
}


private void
end_of_raid()
{
    if (raid_status != RAID_OVER)  { 
        tell_room(PALACE_RAID_ROOM, "End of raid code entered " +
                                    "but raid isn't over.\n"); 
        return;
     }

     time_end = time();
     tell_room(PALACE_RAID_ROOM, "\nRaid over.\n"); 
     WARNING_SIGNAL_OBJECT->warn_calians("Informer", 
                          "The raid is over. I'd better get writing!"); 
     KROUG_BRAIN->set_raid_path(0); 
     set_alarm(1.0, 0.0, informer_note); 
}


public void 
continue_raid()
{
    int i, gs, gt;
    string *ins; 
    mixed curr_ins; 

    if (raid_status != RAID_ACTIVE) { 
         tell_room(PALACE_RAID_ROOM, 
                   "Stopped continuation of active raid.\n"); 
         return;
    }

    clean_krougs(); 
    if (!sizeof(krougs))  {
        raid_status = RAID_OVER; 
        set_alarm(1.0, 0.0, end_of_raid); 
        return;
    }

    clean_groups(); 
    if (group_cycle >= number_groups) 
        group_cycle = 0; 

    gt = 0; 
    gs = group_stage[group_cycle]; 
    ins = group_instr[group_cycle]; 

    /* Find the correct group to move next. */ 
    while ((gt < number_groups) && 
           (!sizeof(kroug_groups[group_cycle]) || 
            (ins[gs] == SKIP)))  
    {
        if (ins[gs] == SKIP) 
            group_stage[group_cycle]++;  
        gt++;
        group_cycle++;
        if (group_cycle >= number_groups) 
            group_cycle = 0; 
        gs = group_stage[group_cycle]; 
        ins = group_instr[group_cycle]; 
    }

    if (gt == number_groups) { 
        tell_room(PALACE_RAID_ROOM, "Complete group skip!\n"); 
        set_alarm(itof(STEP_DELAY), 0.0, continue_raid); 
        return;
    }

    /* Krougs just wander around after reaching their objectives, 
       assuming they have no enemies present. */ 
    if (gs >= (sizeof(ins)-1))  {  
        for (i = 0; i < sizeof(kroug_groups[group_cycle]); i++)
            kroug_groups[group_cycle][i]->kroug_wander(); 
        set_alarm(itof(STEP_DELAY), 0.0, continue_raid); 
        group_cycle++; 
        return;
    }

    /* Execute the commands in the group of krougs now */

     curr_ins = raid_steps[ins[gs]]; 
     if (sizeof(curr_ins) == 4)  {
         tell_room(PALACE_RAID_ROOM, "Group " + group_cycle + " step " + 
                   ins[gs] + ".\n"); 

         if (stringp(curr_ins[0])) 
                call_other(this_object(), curr_ins[0]); /* pre function */ 

        /* move a group */ 
        for (i = 0; i < sizeof(kroug_groups[group_cycle]); i++)  
            kroug_groups[group_cycle][i]->move_living(curr_ins[1], 
                                                         curr_ins[2]);  

        if (stringp(curr_ins[3])) 
            call_other(this_object(), curr_ins[3]); /* post function */ 
    }
    gs++;
    group_stage[group_cycle] = gs; 

    group_cycle++;
    set_alarm(itof(STEP_DELAY), 0.0, continue_raid); 
}


/* Group krougs together correctly */ 
void
group_the_krougs()
{
    int i, j, l;
    object *remaining, k; 

    if (strength > sizeof(krougs))  {
        tell_room(PALACE_RAID_ROOM, "Strength error!\n");  
        return;
    }

    l = sizeof(krougs) - strength; 

    /* Get rid of unwanted krougs */ 
    for (i = 0; i < l; i++) {  
        j = random(sizeof(krougs)); 
        krougs[j]->remove_object(); 
        krougs = exclude_array(krougs, j, j); 
    }
 
    remaining = krougs;

    while ((j = sizeof(remaining)) > 0) { 
        if (j > number_groups) 
            j = number_groups;
        for (i = 0; i < j; i++) { 
            k = remaining[random(sizeof(remaining))]; 
            if (sizeof(kroug_groups[i])) 
                kroug_groups[i] += ({ k }); 
            else
                kroug_groups[i] = ({ k });  
            remaining -= ({ k }); 
        }
    }
    tell_room(PALACE_RAID_ROOM, "Krougs have been grouped.\n"); 
}


private void 
continue_warning_period()
{
    if (raid_status != RAID_WARNING_PERIOD) { 
         tell_room(PALACE_RAID_ROOM, 
                    "Stopped continuation of warning period.\n"); 
         return;
    }

    if (countdown == 0)  {
        tell_room(PALACE_RAID_ROOM, "Raid starts now!\n"); 
        WARNING_SIGNAL_OBJECT->warn_calians("Informer", 
              "A Kroug Raid on the Palace is beginning now! " +
              capitalize(LANG_WNUM(strength)) + " krougs are advancing!"); 
        raid_status = RAID_ACTIVE; 
        time_start = time(); 
        KROUG_BRAIN->set_raid_path(PALACE_RAID_OB); 
        group_the_krougs(); 
        set_alarm(1.0, 0.0, continue_raid); 
        return;
    }

    tell_room(PALACE_RAID_ROOM, countdown + " minute warning.\n"); 
    WARNING_SIGNAL_OBJECT->warn_calians("Informer",  
            "A Kroug Raid on the Palace is expected in " + 
            LANG_WNUM(countdown) + ((countdown == 1) ? 
                                   " minute! " : " minutes! ") + 
            capitalize(LANG_WNUM(strength)) + " krougs are expected."); 
    countdown--; 
    set_alarm(60.0, 0.0, continue_warning_period); 
}



private void 
continue_terminating()
{
     int i, j;         
     string s;
     object *back_krougs = ({ }); 

     if (raid_status != RAID_TERMINATING) {
         tell_room(PALACE_RAID_ROOM, 
                       "Error! Stopped termination of raid!\n"); 
         return;
     }

     clean_krougs(); 
     
     i = sizeof(krougs); 
     if (i > 5) 
         i = 5; 

     for (j = 0; j < i; j++)  { 
         if (!stringp(s = krougs[j]->query_prop(KROUG_S_HOME_ROOM))) 
             krougs[j]->remove_object();  
         else {
             back_krougs += ({ krougs[j] }); 
             krougs[j]->move_living("angrily back to the foothills", s); 
         }
     }

     krougs -= back_krougs; 
     clean_krougs();  

     i = sizeof(krougs); 
     if (!i) { 
         tell_room(PALACE_RAID_ROOM, "Raid termination completed.\n"); 
         raid_status = RAID_TERMINATED; 
         return;
     }

     tell_room(PALACE_RAID_ROOM, "Raid termination continuing, " + 
                LANG_WNUM(i) + " krougs currently away from home.\n"); 
     set_alarm(5.0, 0.0, continue_terminating); 
}



private void
reset_raid()
{
    raid_status = RAID_PRE_RAID;  
    scores = ([ ]); 
    krougs = ({ }); 
    casualties = ({ }); 
    kroug_groups = allocate(RAID_MAX_GROUPS); 
    group_stage = allocate(RAID_MAX_GROUPS); 
    max_strength = 0; 
    strength = 0; 
    number_groups = 0; 
    time_start = 0;
    time_end = 0; 
    warning_dur = 0;  
    kr_test_index = 0; 
    group_cycle = 0; 
    done_note = 0; 
    hurn = 0; 
    hw = 0; 
}




void
create_object()
{
    setuid();
    seteuid(getuid()); 

    reset_raid(); 

    restore_object(PALACE_RAID_SAVE); 

    clean_krougs(); 

    if ((raid_status == RAID_PRE_RAID) || 
        (raid_status == RAID_OVER) || 
        (raid_status == RAID_TERMINATED)) 
        return;

    if (sizeof(krougs) == 0) { 
         reset_raid(); 
         tell_room(PALACE_RAID_ROOM, 
                   "Raid reset, zero active krougs.\n"); 
         return;
    }

    if (raid_status == RAID_CHECK_ROOMS) {
        reset_raid(); 
        tell_room(PALACE_RAID_ROOM, 
                 "The raid room test will have to be re-done.\n");  
        return;
    } 

    if (raid_status == RAID_TERMINATING) {
        set_alarm(1.0, 0.0, continue_terminating);  
        return;
    }

    if (raid_status == RAID_ACTIVE) {  
        set_alarm(1.0, 0.0, continue_raid); 
        return;
    }

    if (sizeof(krougs) < strength) {
        reset_raid(); 
        tell_room(PALACE_RAID_ROOM, 
                 "Raid reset, kroug strength did not match " +
                 "active krougs.\n"); 
        return;
    }

    if (raid_status == RAID_WARNING_PERIOD) { 
        set_alarm(1.0, 0.0, continue_warning_period); 
        return;
    }
}




void
test_room()
{
    object r, *tk;
    int i;

    if (raid_status != RAID_CHECK_ROOMS) {
        tell_room(PALACE_RAID_ROOM, "Room checks stopped.\n"); 
        return;
    }

    kroug_rooms[kr_test_index]->load_me(); 
    r = find_object(kroug_rooms[kr_test_index]); 

    if (!objectp(r)) 
        tell_room(PALACE_RAID_ROOM, "Hmm, couldn't find the room " + 
                   kroug_rooms[kr_test_index] + "!\n"); 
    else { 
         r->reset_room(); 
         tk = query_krougs(r);
         for (i = 0; i < sizeof(tk); i++)  {
             tk[i]->add_prop(KROUG_S_HOME_ROOM, kroug_rooms[kr_test_index]);  
             tk[i]->move_living("with a gleeful look in its eye", 
                                (KROUG_WAITING_ROOM+((i > 1) ? 2 : i))); 
         }
         if (sizeof(tk)) 
             krougs += tk; 
         max_strength = mstr(); 
         tell_room(PALACE_RAID_ROOM, 
                 "Kroug max strength subtotal after " +
                 "checking room " + kroug_rooms[kr_test_index] + 
                 " is: " + max_strength + ".\n"); 
    }

    kr_test_index++; 
    if (kr_test_index >= sizeof(kroug_rooms)) {
        tell_room(PALACE_RAID_ROOM, "Room checks complete, " + 
                  "maximum strength is: " + max_strength + ".\n"); 
        raid_status = RAID_PRE_RAID;  
        return;
    }

    set_alarm(itof(STEP_DELAY), 0.0, test_room); 
}


int
do_test()
{
    int s; 

    /* Get details of kroug rooms from kroug brain and work out how 
       many krougs there are potentially. */
    ROOM_CHECK_BLOCK; 
    RAID_ACTIVE_BLOCK; 
    RAID_WARNING_BLOCK;
    TERMINATING_BLOCK;
    TERMINATED_BLOCK;
    RAID_OVER_BLOCK;
    MEMORY_BLOCK; 

    raid_status = RAID_CHECK_ROOMS; 

    tell_room(PALACE_RAID_ROOM, "FInding kroug rooms..\n"); 
    KROUG_BRAIN->load_me(); 
    kroug_rooms = KROUG_BRAIN->query_kroug_rooms(); 

    s = sizeof(kroug_rooms); 
    tell_room(PALACE_RAID_ROOM, "Number of kroug rooms: " + s + ".\n");  

    if (s == 0) {
        tell_room(PALACE_RAID_ROOM, "Well, that didn't get very far!\n"); 
        raid_status = RAID_PRE_RAID; 
        return 1;
    }

    raid_log(this_player(), "initiates room test"); 

    kr_test_index = 0; 
    tell_room(PALACE_RAID_ROOM, "Starting checks..\n"); 
    set_alarm(itof(STEP_DELAY), 0.0, test_room); 
    return 1;
}


int
set_strength(string s)
{
     object tp; 
     int p;

     RAID_ACTIVE_BLOCK; 
     ROOM_CHECK_BLOCK;
     RAID_WARNING_BLOCK;
     TERMINATING_BLOCK;
     TERMINATED_BLOCK;
     RAID_OVER_BLOCK;
     MEMORY_BLOCK; 

     tp = this_player(); 

     max_strength = mstr(); 
     if (!max_strength) { 
         notify_fail("Kroug maximum strength has not yet been tested " +
                     "or is zero.\n"); 
         return 0;
     }

     if (max_strength < RAID_MIN_KROUGS) { 
         notify_fail("Kroug maximum strength is too low " +
                     "for a raid to proceed.\n"); 
         return 0;
     }

     if (!stringp(s)) {
         notify_fail("Set strength of kroug raid to how many krougs?\n"); 
         return 0;
     }

     if (sscanf(s, "%d", p) != 1) { 
         notify_fail("Set strength of kroug raid to how many krougs?\n"); 
         return 0;
     }

     if (p > max_strength) { 
         notify_fail("Not that many krougs!\n"); 
         return 0;
     }

     if (p < RAID_MIN_KROUGS) { 
         notify_fail("That is too few krougs!\n");  
         return 0;
     }

     strength = p; 

     tp->catch_msg("Ok, the strength of the total kroug attack force " + 
                   "has been set to: " + strength + ".\n"); 

     if (number_groups)  {
         number_groups = 0; 
         tp->catch_msg("The number of groups must be set again.\n"); 
     }
    
     return 1;
}



/* Warning duration in minutes */
int
set_warning_dur(string d)
{
     object tp;
     int p;

     RAID_ACTIVE_BLOCK; 
     ROOM_CHECK_BLOCK;
     RAID_WARNING_BLOCK;
     TERMINATING_BLOCK;
     TERMINATED_BLOCK;
     RAID_OVER_BLOCK;
     MEMORY_BLOCK; 

     tp = this_player(); 
     if (!stringp(d)) {
         notify_fail("Set warning duration to how many minutes?\n"); 
         return 0;
     }

     if (sscanf(d, "%d", p) != 1) { 
         notify_fail("Set warning duration to how many minutes?\n"); 
         return 0;
     }

     if (p > RAID_MAX_WARNING_DUR)  {
         notify_fail("That is too long!\n"); 
         return 0;
     }

     if (p < RAID_MIN_WARNING_DUR)  {
         notify_fail("That is too short!\n"); 
         return 0;
     }

     warning_dur = p; 
     tp->catch_msg("Ok, the warning duration has been set to " +  
                   warning_dur + " minutes.\n"); 
     return 1;
}


int
set_number_groups(string s)
{
     object tp;
     int p;

     RAID_ACTIVE_BLOCK; 
     ROOM_CHECK_BLOCK;
     RAID_WARNING_BLOCK;
     TERMINATING_BLOCK;
     TERMINATED_BLOCK;
     RAID_OVER_BLOCK;
     MEMORY_BLOCK; 

     if (!strength) { 
         notify_fail("Kroug strength has not been set yet.\n"); 
         return 0;
     }

     tp = this_player(); 
     if (!stringp(s)) {
         notify_fail("Set number of groups to what?\n"); 
         return 0;
     }

     if (sscanf(s, "%d", p) != 1) { 
         notify_fail("Set number of groups to what?\n"); 
         return 0;
     }

     if (p > RAID_MAX_GROUPS)  {
         notify_fail("That is too many groups!\n"); 
         return 0;
     }

     if (p < RAID_MIN_GROUPS)  {
         notify_fail("That is too few groups!\n"); 
         return 0;
     }

     if ((strength/p) < RAID_MIN_GROUP_SIZE) { 
          notify_fail("That would leave some groups too small!\n"); 
          return 0;
     }

     if (((strength/p) > RAID_MAX_GROUP_SIZE) || 
         (((strength/p) == RAID_MAX_GROUP_SIZE) && ((strength % p) > 0))) { 
          notify_fail("That would leave some groups too big!\n"); 
          return 0;
     }

     number_groups = p; 
     tp->catch_msg("Ok, the number of groups has been set to: " +  
                   number_groups + ".\n");
     
     // Need to set up the group_instr array so that each group follows
     // each other out of their waiting rooms.
     group_instr = allocate(number_groups);
     for (int group_num = 0; group_num < number_groups; ++group_num)
     {
         group_instr[group_num] = ({ });
         for (int skip_index = 0; skip_index < group_num; ++skip_index)
         {
            group_instr[group_num] += ({ SKIP });
         }
         group_instr[group_num] += basic_mission_steps;
         if (group_num < sizeof(end_rooms))
         {
            group_instr[group_num] += ({ end_rooms[group_num] });
         }
         else
         {
            group_instr[group_num] += ({ one_of_list(end_rooms) });
         }
         group_instr[group_num] += ({ END });
     }
    
     return 1;
}



/* 
   List the status of this palace raid configuration. 
*/
int
check_configuration()
{
    object tp;
    string str;

    tp = this_player(); 
    str = ""; 
     
    str = "Configuration is set as follows:\n"; 
 
    max_strength = mstr(); 
    if (!max_strength) 
        str += ("Maximum kroug strength is unknown.\n"); 
    else 
        str += ("Maximum kroug strength: " + max_strength + " krougs.\n");  

    if (!strength) 
        str += ("Kroug strength is not set.\n"); 
    else 
        str += ("Kroug strength is set to: " + strength + " krougs.\n"); 

    if (!number_groups) 
        str += ("Number of kroug groups is not set.\n"); 
    else 
        str += ("Number of kroug groups is set to: " + number_groups + ".\n"); 

    if (!warning_dur) 
        str += ("Warning duration is not set.\n"); 
    else 
        str += ("Warning duration is set to: " + warning_dur + 
                " minutes.\n"); 

    tp->catch_msg(str); 

    return 1; 
}


int
start_raid()
{
     RAID_ACTIVE_BLOCK; 
     ROOM_CHECK_BLOCK;
     RAID_WARNING_BLOCK;
     TERMINATING_BLOCK;
     TERMINATED_BLOCK;
     RAID_OVER_BLOCK;
     MEMORY_BLOCK; 

     if ((!strength) || (!warning_dur) || (!number_groups)) { 
          notify_fail("The raid has not been configured.\n"); 
          return 0;
     }

     tell_room(PALACE_RAID_ROOM, "Warning period initiated.\n"); 
     raid_log(this_player(), "initiates warning period"); 
     countdown = warning_dur; 
     raid_status = RAID_WARNING_PERIOD; 
     set_alarm(1.0, 0.0, continue_warning_period); 
     return 1;
}



/* Attempts to terminate a raid */ 
int
terminate(string str)
{
    TERMINATING_BLOCK;
    TERMINATED_BLOCK; 
    RAID_OVER_BLOCK;
 
    this_player()->catch_msg("Ok, starting to terminate the raid.\n"); 
    set_alarm(2.0, 0.0, continue_terminating); 
    KROUG_BRAIN->set_raid_path(0); 
    raid_status = RAID_TERMINATING; 
    raid_log(this_player(), "initiates termination of raid"); 
    return 1; 
}



/* Action to reset the raid if it's over or terminated. */
int
do_reset(string str)
{
     RAID_PRE_BLOCK;
     RAID_ACTIVE_BLOCK; 
     ROOM_CHECK_BLOCK;
     RAID_WARNING_BLOCK;
     TERMINATING_BLOCK;

     this_player()->catch_msg("Ok, resetting raid.\n"); 
     reset_raid(); 
     raid_log(this_player(), "resets raid"); 
     return 1;
}


/* check scores */  
int
check_scores(string str)
{
    string *n, res;
    int i, j;

    n = m_indexes(scores);  
    if (!sizeof(n)) {  
        notify_fail("No scores at the moment.\n");  
        return 0;
    }

    res = "Player scores:\n"; 
    res += "(Order is from weakest to strongest kroug type)\n"; 
    for (i = 0; i < sizeof(n); i++)  {  
        res += n[i];  
        res += ": "; 
        for (j = 0; j < sizeof(scores[n[i]]); j++) 
            res += (scores[n[i]][j] + "  ");  
        res += "\n";  
    }
    this_player()->catch_msg(res); 
    return 1;
}



/* Dumps the whereabouts of the players in the palace vicinity. */ 
int
whereabouts(string str)
{
     int i, j;
     object *u, e, tp;
     mixed rc;
     string troom, tn, *id, res, tline; 
     mapping pr = ([ ]); 
     mapping kr = ([ ]); 

     tp = this_player(); 
     u = users(); 
     clean_krougs(); 

     for (i = 0; i < sizeof(u); i++) { 
         if (!objectp(e = environment(u[i])))
             continue; 
         troom = file_name(e); 
         if (wildmatch(CROAD+"*", troom) ||  
             wildmatch(CRPALACE_LIGHT_ROOMS+"*", troom)) {
             id = explode(troom, "/"); 
             tn = id[sizeof(id)-1]; 
             rc = pr[tn]; 
             if (pointerp(rc))  {
                 pr = m_delete(pr, tn); 
                 pr += ([ tn : (rc + ({u[i]->query_name()})) ]); 
             }
             else 
                 pr += ([ tn : ({ u[i]->query_name()}) ]);  
         }
    }

    res = ""; 
    for (i = 0; i < sizeof(krougs); i++) {
        if (!objectp(e = environment(krougs[i])))   
            continue; 
        troom = file_name(e); 
        id = explode(troom, "/"); 
        tn = id[sizeof(id)-1]; 
        rc = kr[tn]; 
        if (intp(rc) && (rc > 0))  {
            kr = m_delete(kr, tn); 
            kr += ([ tn : (rc + 1) ]); 
        }
        else 
            kr += ([ tn : 1 ]);  
    }

    id = m_indexes(pr); 
    for (i = 0; i < sizeof(id); i++) { 
        tline = ""; 
        tline += (id[i] + ": ");
        if (kr[id[i]]) 
            tline += COMPOSITE_WORDS(pr[id[i]] + 
                                 ({ LANG_WNUM(kr[id[i]]) + " krougs"})); 
        else
            tline += COMPOSITE_WORDS(pr[id[i]]);  

        tline += ".\n"; 
        res += tline;  
    }

    id = m_indexes(kr); 
    for (i = 0; i < sizeof(id); i++) {   
        if (pointerp(pr[id[i]])) 
            continue; 
        tline = ""; 
        tline += (id[i] + ": ");
        tline += (LANG_WNUM(kr[id[i]]) + " krougs"); 
        tline += ".\n"; 
        res += tline;  
    }

    if (!strlen(res)) 
        res = "No whereabouts to report.\n"; 
    tp->catch_msg(res); 
    return 1;
}


void
open_doors()
{
    (CROAD+"croad27")->kroug_raid_open_door(); 
}


void
charm_hurn()
{
   if (hurn)  
       return;

   tell_room(PALACE_RAID_ROOM, "Krougs reach Hurn.\n"); 
   WARNING_SIGNAL_OBJECT->warn_calians("Informer", 
          "The kroug vanguard has reached Hurn!"); 
   hurn = 1;  
   (CROAD+"croad26")->kroug_raid_charm_statue(); 
}


void
half_way()
{
   if (hw)
       return;

   tell_room(PALACE_RAID_ROOM, "Krougs are half way up mountain.\n"); 
   WARNING_SIGNAL_OBJECT->warn_calians("Informer", 
          "The kroug vanguard is half way up the mountain!"); 
   hw = 1;  
}

public void
print_group_instructions()
{
    dump_array(group_instr);
}
