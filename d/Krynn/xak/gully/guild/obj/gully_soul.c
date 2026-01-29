
 /*
       Gully Dwarf Command Soul - Karath@Genesis - Andrew Smith Oct 97

       Based on code by Maniac@Genesis, March 1997
       Copyright (C) Miguel Leith 1997

 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include "cadet.h"

string
get_soul_id()
{
    return GULLY_GUILD_NAME;
}

int
query_cmd_soul()
{
    return 1;
}

string
group_desc(object looking, object *group, int cap)
{
    string *qdesc, qd;

    if (member_array(looking, group) > -1) {
        group -= ({looking});
        if (cap)
            qdesc = ({"You"});
        else
            qdesc = ({"you"});
        if (sizeof(group))
            qdesc += map(group, &->query_the_name(looking));
    }
    else {
        if (cap)
            qdesc = ({group[0]->query_The_name(looking) });
        else
            qdesc = ({group[0]->query_the_name(looking) });
        group -= ({group[0]});
        if (sizeof(group))
            qdesc += map(group, &->query_the_name(looking));
    }

    return COMPOSITE_WORDS(qdesc); 
} 

int
ghand(string str)
{
    object tp, *who;

    tp = this_player(); 
    if (!str || str == "") { 
         write("You put your grubby little hand up to ask a question.\n"); 
         all(" gets a confused look on " + tp->query_possessive() + 
		" and puts " + tp->query_possessive() + " grubby little "+
		"hand up to ask a question."); 
         return 1;
    } 

    who = parse_this(str, "%l");
    if (!sizeof(who)) { 
        notify_fail("Put your hand up to ask whom a question?\n"); 
        return 0;
    } 

    actor("You put your hand up to ask", who, " a question."); 
    targetbb(" puts " + tp->query_possessive() + " hand up to " + 
           "ask you a question.", who); 
    all2actbb(" puts " + tp->query_possessive() + " hand up to ask", 
               who," a question.");
    return 1;
}


int
cjump(string str)
{
    if (stringp(str) && strlen(str)) {  
        notify_fail("Cjump requires no argument.\n"); 
        return 0;
    } 

    write("You jump to attention.\n"); 
    allbb(" jumps to attention."); 
    return 1;
}


int
cstand(string str)
{
    if (stringp(str) && strlen(str)) {  
        notify_fail("Cstand requires no argument.\n"); 
        return 0;
    } 

    write("You stand at ease.\n"); 
    allbb(" stands at ease."); 
    return 1;
}


int
cpush(string str)
{
     int t;
     object tp, pr;

     if (stringp(str)) { 
         notify_fail("Cpush requires no argument.\n"); 
         return 0;
     } 

     tp  = this_player(); 

     t = environment(tp)->query_prop(ROOM_I_TYPE);  

     if (stringp(tp->query_prop(LIVE_S_EXTRA_SHORT)) || 
         (t == ROOM_IN_WATER) || (t == ROOM_UNDER_WATER) ||  
         (t == ROOM_IN_AIR)) { 
         notify_fail("You can't do that at the moment.\n"); 
         return 0;
     } 

     if (objectp(tp->query_attack())) { 
         notify_fail("You can't do pushups while you are fighting!\n"); 
         return 0;
     } 

     if (tp->query_fatigue() < 10) {  
         notify_fail("You are too tired to start doing pushups!\n"); 
         return 0;
     } 

     write("You drop to the ground and start doing pushups.\n");  
     allbb(" drops to the ground and starts doing pushups."); 

     setuid(); 
     seteuid(getuid()); 
     pr = clone_object(GC_PUSHUP_OB);
     pr->move(tp); 
     pr->start_pushups(); 
     return 1;
}

int
cpresent(string str)
{
    object tp, *who, *wep; 
    string arms;

    tp = this_player(); 
    wep = tp->query_weapon(-1); 

    if (!sizeof(wep)) 
        arms = "(two fists and two feet)"; 
    else 
        arms = ("(" + COMPOSITE_DEAD(wep) + ")"); 

    if (!str || str == "") { 
         write("You present arms " + arms + ".\n");     
         allbb(" presents arms " + arms + "."); 
         return 1;
    } 

    who = parse_this(str, "%l");
    if (!sizeof(who)) { 
        notify_fail("Cpresent to whom?\n"); 
        return 0;
    } 

    actor("You present arms " + arms + " to", who); 
    targetbb(" presents arms " + arms + " to you.", who); 
    all2actbb(" presents arms " + arms + " to", who);  
    return 1;
}


string
query_shout_address(object pl)
{
    switch (pl->query_gender()) { 
        case G_MALE : return "SIR"; 
                      break;
        case G_FEMALE : return "MA'AM"; 
                        break;
        default : return "THING"; 
                  break;
    } 
}


int
cyes(string str)
{
    object *who; 
    string what;

    notify_fail("Cyes at whom?\n"); 
    if (!str || str == "")  
        return 0;

    who = parse_this(str, "%l");
    if (!sizeof(who)) 
        return 0;

    if (sizeof(who) > 1) { 
        notify_fail("You may only use `cyes' on one person at once.\n"); 
        return 0;
    } 

    what = ("`YES " + query_shout_address(who[0]) + "!'"); 

    actor("You shout " + what + " at", who); 
    target(" shouts " + what + " at you.", who); 
    all2act(" shouts " + what + " at", who);  
    return 1;
}


int
cno(string str)
{
    object *who; 
    string what;

    notify_fail("Cno at whom?\n"); 
    if (!str || str == "")  
        return 0;

    who = parse_this(str, "%l");
    if (!sizeof(who)) 
        return 0;

    if (sizeof(who) > 1) { 
        notify_fail("You may only use `cno' on one person at once.\n"); 
        return 0;
    } 

    what = ("`NO " + query_shout_address(who[0]) + "!'"); 

    actor("You shouts " + what + " at", who); 
    target(" shouts " + what + " at you.", who); 
    all2act(" shouts " + what + " at", who);  
    return 1;
}


int
clisten(string str)
{
    object tp, *who; 

    notify_fail("Clisten to whom?\n"); 
    if (!str || str == "")  
        return 0;

    who = parse_this(str, "%l");
    if (!sizeof(who)) 
        return 0;

    if (sizeof(who) > 1) { 
        notify_fail("You may only `clisten' to one person at once.\n"); 
        return 0;
    } 

    actor("You listen attentively to what", who, " is saying."); 
    targetbb(" listens attentively to what you are saying.", who); 
    all2actbb(" listens attentively to what", who, " is saying.");  
    return 1;
}

int
cfist(string str)
{
    object tp, *who; 

    tp = this_player(); 

    if (!str || str == "") { 
         write("You shake your fist rebelliously.\n");     
         allbb(" shakes " + tp->query_possessive() + " fist rebelliously."); 
         return 1;
    } 

    who = parse_this(str, "%l");
    if (!sizeof(who)) { 
        notify_fail("Cfist at whom?\n"); 
        return 0;
    } 

    actor("You shake your first rebelliously at", who); 
    targetbb(" shakes " + tp->query_possessive() + " fist " +
            "rebelliously at you.", who); 
    all2actbb(" shakes " + tp->query_possessive() + " fist " +
              "rebelliously at", who);  
    return 1;

}


int
cyawn(string str)
{
    if (stringp(str) && strlen(str)) {  
        notify_fail("Cyawn requires no argument.\n"); 
        return 0;
    } 

    write("You stare into space and yawn widely.\n"); 
    all(" stares into space and yawns widely."); 
    return 1;
}


int
csidle(string str)
{
    object tp, *who; 

    tp = this_player(); 

    if (!str || str == "") { 
         write("You sidle slowly away.\n");     
         allbb(" sidles slowly away."); 
         return 1;
    } 

    who = parse_this(str, "%l");
    if (!sizeof(who)) { 
        notify_fail("Csidle from whom?\n"); 
        return 0;
    } 

    actor("You sidle slowly away from", who); 
    targetbb(" sidles slowly away from you.", who); 
    all2actbb(" sidles slowly away from", who);  
    return 1;
}


int
cimit(string str)
{
    object tp, *who; 
    int notice;
    string did_they_notice;

    notify_fail("Cimit whom?\n"); 
    if (!str || str == "")  
        return 0;

    tp = this_player(); 
    who = parse_this(str, "%l");
    if (!sizeof(who)) 
        return 0;

    if (sizeof(who) > 1) { 
        notify_fail("You can only `cimit' one person at once.\n");  
        return 0;
    } 

    if (tp->resolve_task(TASK_ROUTINE, 
                         ({ SS_SNEAK }), 
                          who[0], 
                         ({ SS_AWARENESS })) > 0)
        did_they_notice = ""; 
    else
        did_they_notice = (". " + capitalize(who[0]->query_pronoun()) +  
                           " notices"); 

    actor("You imitate", who, " behind " + 
          who[0]->query_possessive() + " back" + did_they_notice + "."); 

    if (strlen(did_they_notice))  
        targetbb(" imitates you behind your back.", who); 

    all2actbb(" imitates", who, " behind " + who[0]->query_possessive() + 
              " back" + did_they_notice + ".");  
    return 1;
}


int
cbrawl(string str)
{
    string *brawl; 
    object tp, *who; 

    tp = this_player(); 

    if (!str || str == "") { 
        brawl = tp->query_prop(CADET_AS_BRAWL_WITH); 
        tp->catch_msg("You have brawled the following cadets on this login: " + 
            (sizeof(brawl) ? COMPOSITE_WORDS(brawl) : "none") + ".\n");        
        return 1;
    } 

    who = parse_this(str, "[with] %l");
    if (!sizeof(who)) { 
        notify_fail("Cbrawl with whom?\n"); 
        return 0;
    } 

    if (sizeof(who) > 1) { 
        notify_fail("You may only <cbrawl> one person at once!\n"); 
        return 0;
    } 

    if (!IS_GELAN_CADET(who[0])) { 
        notify_fail("The <cbrawl> command is only relevant for cadets!\n"); 
        return 0;
    } 

    brawl = tp->query_prop(CADET_AS_BRAWL_WITH); 
    if (!pointerp(brawl)) 
        brawl = ({ }); 
    if (member_array(who[0]->query_real_name(), brawl) == -1) { 
        brawl += ({ who[0]->query_real_name() });  
        tp->add_prop(CADET_AS_BRAWL_WITH, brawl); 
    } 

    brawl = who[0]->query_prop(CADET_AS_BRAWL_WITH); 
    if (member_array(tp->query_real_name(), brawl) > -1) { 
         actor("You punch", who, "'s fist."); 
         target(" punches your fist.", who); 
         all2act(" punches", who, "'s fist.");  
         tp->command("$kill " + OB_NAME(who[0])); 
         return 1;
    } 

    actor("You punch", who, "'s fist. If " + who[0]->query_pronoun() + 
        " punches you back, the pair of you " + 
        "will be fighting without getting kicked out of the guild."); 
    target(" punches your fist. If you want to attack " + 
        tp->query_objective() + " without being kicked out of the guild, " +
        "use <cbrawl> on " + tp->query_objective() + ".", who); 
    all2act(" punches", who, "'s fist.");  
    return 1;
}


int
clist()
{
    mixed list;

    list = filter(users(),&operator(==)(GC_GUILD_NAME) @
        &->query_guild_name_lay());
    list = filter(list, &operator(!=)(100) @ &->query_invis());
    list = implode(map(list, &->query_presentation()), "\n");  

    this_player()->more("The following Cadets are currently playing:\n"+
                        list + "\n"); 
    return 1;
}


int
donk(string str)
{
    return this_player()->gc_prepare_to_donk(str);  
}


int
cleave(string str)
{
    object tp = this_player();

    if (!objectp(tp))
         return 0;

    if (str != "cadets") {
        notify_fail("Did you want to <cleave cadets>?\n");
        return 0;
    }

    if (!IS_GELAN_CADET(tp)) {
        notify_fail("You are not a cadet!\n");
        return 0;
    }

    if (!tp->query_prop(CADET_I_CONFIRM_LEAVE)) {
        write("Type the <cleave cadets> command again to confirm.\n");
        tp->add_prop(CADET_I_CONFIRM_LEAVE, 1);
        return 1;
    }

    if (environment(tp)->gc_query_private_room())
        tp->move_living("to the cadet training room", GC_TRAINROOM);

    setuid();
    seteuid(getuid());
    if (GC_TRAINROOM->kick_out_cadet(tp)) {
         write("You just left the cadets.\n");
         say(QCTNAME(tp) + " just left the cadets.\n");
         return 1;
    }

    notify_fail("For some reason you can't leave the cadets.\n");
    return 0;
}


int
help(string str)
{
    setuid(); 
    seteuid(getuid()); 
    if (str == "cadet" || str == "cadets") { 
        this_player()->more(read_file(GC_COMMAND_INFO)); 
        return 1; 
    } 
    return 0;
}

mapping
query_cmdlist()
{
    return ([
               "ghand" : "ghand", 
               "cpresent" : "cpresent",  
               "cstand" : "cstand", 
               "cjump" : "cjump", 
               "cyes" : "cyes",
               "cno" : "cno",
               "clisten" : "clisten", 
               "cburp" : "cburp", 
               "cfist" : "cfist", 
               "cyawn" : "cyawn", 
               "csidle" : "csidle",  
               "cimit" : "cimit",  
               "clist" : "clist",  
               "cleave" : "cleave", 
               "cpush" : "cpush", 
               "cskill" : "cskill", 
               "cbrawl" : "cbrawl",
               "help" : "help", 
            ]);
}

