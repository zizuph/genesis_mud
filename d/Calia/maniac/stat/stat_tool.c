/*
 * The statter tool.
 * A tool that may be used to change one's own stats with any values 
 * one chooses, or the stats of a junior. It also has features to do mass
 * setting of combat-related skills, and to turn death off in juniors.
 * Coded by Maniac
 *
 * History: 
 *         10/6/96     Dropped shadowing              Maniac      
 *         13.4.95            Modified                Maniac
 *         31.3.95            Created                 Maniac
 */


inherit "/cmd/std/command_driver";
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>

#define MAX_STAT 500
#define STAT_TOOL_DIR "/d/Calia/maniac/stat/"

int *armed_skills =
          ({SS_2H_COMBAT, SS_BLIND_COMBAT, SS_PARRY, 
            SS_DEFENCE, SS_MOUNTED_COMBAT, SS_WEP_SWORD, SS_WEP_POLEARM,
            SS_WEP_AXE, SS_WEP_KNIFE, SS_WEP_CLUB, SS_WEP_MISSILE, 
            SS_WEP_JAVELIN });

int *unarmed_skills = ({SS_UNARM_COMBAT, SS_BLIND_COMBAT, SS_DEFENCE,
                        SS_MOUNTED_COMBAT });

mapping 
h_ops = ([ "rstats"   : "rstats",
           "setstats" : "setstats",
           "setall"   : "setall",
           "setstr"   : "setstr",
           "setdex"   : "setdex",
           "setcon"   : "setcon",
           "setint"   : "setint",
           "setwis"   : "setwis",
           "setdis"   : "setdis", 
           "setrace"  : "setrace",
           "setocc"   : "setocc",
           "setlay"   : "setlay",
           "armed"    : "armed",
           "unarmed"  : "unarmed",
         ]);

mapping
stat_of = ([ "setstr" : SS_STR,
             "setdex" : SS_DEX,
             "setcon" : SS_CON,
             "setint" : SS_INT,
             "setwis" : SS_WIS,
             "setdis" : SS_DIS,
             "setrace" : SS_RACE,
             "setocc"  : SS_OCCUP,
             "setlay"  : SS_LAYMAN
          ]);

/*
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "statter";
}


/* 
 * This is a tool soul.
 */
int
query_tool_soul()
{
    return 1;
}


/* 
 * The list of verbs and functions.
 */
mapping
query_cmdlist()
{
    return ([
                "help"       : "help",
                "rstats"     : "rstats",
                "setstats"   : "setstats",
                "setall"     : "setall",
		"setstr"     : "setstat",
                "setdex"     : "setstat",
                "setcon"     : "setstat",
                "setint"     : "setstat",
                "setwis"     : "setstat",
                "setdis"     : "setstat",
                "setrace"    : "setstat",
                "setocc"     : "setstat",
                "setlay"     : "setstat",
                "armed"      : "combat",
                "unarmed"    : "combat",
	    ]);
}



/* Help options for this soul */
int
help(string str)
{
    string s;

    if (!str) return 0; 

    if (str == "statter") {
        setuid();
        seteuid(getuid());
        this_player()->more(read_file(STAT_TOOL_DIR + "statter"));
        return 1;
    } 
    if (sscanf(str, "statter %s", s) == 1) {
        if (!h_ops[s]) {
            notify_fail("No such statter help option.\n");
            return 0;
        }
        setuid();
        seteuid(getuid());
        this_player()->more(read_file(STAT_TOOL_DIR + h_ops[s]));
        return 1;
    }
    return 0;
}


/* Return all stats of the person to normal */
int
rstats(string str)
{
    object *who, tp, *m;
    string nm;
    int i;

    tp = this_player();

    if (!str) {
        notify_fail("rstats who?\n");
        return 0;
    }

    if (!parse_command(str, all_inventory(environment(tp)), "%l", m)) {
        notify_fail("rstats who?\n");
        return 0;
    }
        
    who = m - ({m[0]});
    if (sizeof(who) > 1) {
        notify_fail("You may only use statter commands on one " +
                    "person at a time.\n");
        return 0;
    }

    tp = this_player();
    nm = who[0]->query_name();
    if ((extract(nm, strlen(nm)-2, strlen(nm)-1) != "jr") &&
        (who[0] != tp)) {
        notify_fail("Unauthorised use of the statter tool. " +
                    "Use it only on yourself or juniors.\n");
        log_file("statter", tp->query_name() + " attempts use of " +
                 "rstats on " + nm + " at " + ctime(time()) + ".\n");
        return 0;
    }

    for (i = 0; i < SS_NO_STATS; i++)  
        tp->update_stat(i); 

    tp->catch_msg("Ok, all stats set back to normal levels.\n"); 
    return 1;
}


/* Set stats of a player up as wanted */
int
setstats(string str)
{
    object tp, *who, *m;
    string nm;
    int *v = ({0, 0, 0, 0, 0, 0, 0, 0, 0}), i;

    if (!str) {
         notify_fail("Set stats of whom to what?\n");
         return 0;
    }
    tp = this_player();

    if (!parse_command(str, all_inventory(environment(tp)),
        "%l %d %d %d %d %d %d %d %d %d",
         m, v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8])) {  
        notify_fail("Incorrect syntax - try `help statter setstats'.\n"); 
        return 0;
    }
    who = m - ({m[0]});
    if (sizeof(who) > 1) {
        notify_fail("You may only use statter commands on one " +
                    "person at a time.\n");
        return 0;
    }
    nm = who[0]->query_name();
    if ((extract(nm, strlen(nm)-2, strlen(nm)-1) != "jr") &&
        (who[0] != tp)) {
        notify_fail("Unauthorised use of the statter tool. " +
                    "Use it only on yourself or juniors.\n");
        log_file("statter", tp->query_name() + " attempts use of " +
                 "setstats on " + nm + " at " + ctime(time()) + ".\n");
        return 0;
    }

    for (i = 0; i < sizeof(v); i++) 
        if (v[i] > MAX_STAT) v[i] = MAX_STAT;  

    for (i = 0; i < sizeof(v); i++) 
        who[0]->set_base_stat(i, v[i]); 

    tp->catch_msg("Ok.\n");
    return 1;
}



/* Set all stats to the same new level */
int
setall(string str)
{
    object tp, *who, *m, sh;
    string nm;
    int v, i, *vals;

    if (!str) {
         notify_fail("setall who to what value?\n");
         return 0;
    }
    tp = this_player();

    if (!parse_command(str, all_inventory(environment(tp)), "%l %d", 
                                                     m, v)) {
        notify_fail("setall who to what value?\n"); 
        return 0;
    }

    who = m - ({m[0]});
    if (sizeof(who) > 1) {
        notify_fail("You may only use statter commands on one " +
                    "person at a time.\n");
        return 0;
    }
    nm = who[0]->query_name();
    if ((extract(nm, strlen(nm)-2, strlen(nm)-1) != "jr") &&
        (who[0] != tp)) {
        notify_fail("Unauthorised use of the statter tool. " +
                    "Use it only on yourself or juniors.\n");
        log_file("statter", tp->query_name() + " attempts use of " +
                 "setall on " + nm + " at " + ctime(time()) + ".\n");
        return 0;
    }

    if (v > MAX_STAT) v = MAX_STAT;  
    for (i = 0; i < SS_NO_STATS; i++) 
        who[0]->set_base_stat(i, v); 

    tp->catch_msg("Ok.\n");
    return 1;
}


/* Set a particular stat to new level */
int
setstat(string str)
{
    object tp, *who, *m, sh;
    string nm, verb;
    int v, i;

    verb = query_verb();
 
    if (!str) {
         notify_fail(verb + " who to what value?\n");
         return 0;
    }
    tp = this_player();
    i = stat_of[verb];

    if (!parse_command(str, all_inventory(environment(tp)), "%l %d", 
                                                     m, v)) {
        notify_fail(verb + " who to what value?\n"); 
        return 0;
    }

    who = m - ({m[0]});
    if (sizeof(who) > 1) {
        notify_fail("You may only use statter commands on one " +
                    "person at a time.\n");
        return 0;
    }
    nm = who[0]->query_name();
    if ((extract(nm, strlen(nm)-2, strlen(nm)-1) != "jr") &&
        (who[0] != tp)) {
        notify_fail("Unauthorised use of the statter tool. " +
                    "Use it only on yourself or juniors.\n");
        log_file("statter", tp->query_name() + " attempts use of " +
                 verb + " on " + nm + " at " + ctime(time()) + ".\n");
        return 0;
    }

    if (v > MAX_STAT) v = MAX_STAT;  
    who[0]->set_base_stat(i, v);
    tp->catch_msg("Ok.\n");
    return 1;
}


/* Set combat-related skills to desired level */
int
combat(string str)
{
    object tp, *who, *m;
    string nm, verb;
    int i, v;

    verb = query_verb();

    if (!str) {
         notify_fail("Set "+verb+" combat skills of who to what value?\n");
         return 0;
    }
    tp = this_player();

    if (!parse_command(str, all_inventory(environment(tp)), "%l %d", 
                                                     m, v)) {
        notify_fail("Set "+verb+" combat skills of who to what value?\n"); 
        return 0;
    }

    who = m - ({m[0]});
    if (sizeof(who) > 1) {
        notify_fail("You may only use statter commands on one " +
                    "person at a time.\n");
        return 0;
    }
    nm = who[0]->query_name();
    if ((extract(nm, strlen(nm)-2, strlen(nm)-1) != "jr") &&
        (who[0] != tp)) {
        notify_fail("Unauthorised use of the statter tool. " +
                    "Use it only on yourself or juniors.\n");
        log_file("statter", tp->query_name() + " attempts use of " +
                 verb + " on " + nm + " at " + ctime(time()) + ".\n");
        return 0;
    }

    if (v > SS_MAX) v = SS_MAX;  
 
    if (verb == "armed") 
        for (i = 0; i < sizeof(armed_skills); i++)
            who[0]->set_skill(armed_skills[i], v);  
    else if (verb == "unarmed") {
        for (i = 0; i < sizeof(unarmed_skills); i++)
            who[0]->set_skill(unarmed_skills[i], v);  
        (who[0]->query_combat_object())->cb_configure();
    }

    tp->catch_msg("Ok.\n");
    return 1;
}

