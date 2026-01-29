
/* 
       ~Calia/gelan/cadet/graduate_soul.c 

       Graduates of Cadets of Gelan command soul. 

       Coded by Maniac@Genesis, June 1998

       Copyright (C) Miguel Leith 1998
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <adverbs.h> 
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
#include "common_commands.c"


string
get_soul_id()
{
    return "Graduates of the Cadets of Gelan";
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
chand(string str)
{
    object tp, *who;

    tp = this_player(); 
    if (!str || str == "") { 
         write("You put your hand up to ask a question.\n"); 
         all(" puts " + tp->query_possessive() + " hand up to " +
             "ask a question."); 
         return 1;
    } 

    who = parse_this(str, "%l");
    if (!sizeof(who)) { 
        notify_fail("Chand to whom?\n"); 
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


/* ckill blocks ambiguous target specifications before attempting
   a kill */ 
int
ckill(string str)
{
    int i; 
    object *obs, ob;
    string *amb, rn;  
    mixed arg, tmp; 

    if (!CAN_SEE_IN_ROOM(this_player())) {
        notify_fail("You can't see anything here.\n"); 
        return 0;
    } 

    if (this_player()->query_ghost()) {
        notify_fail("Umm yes, killed. That's what you are.\n");
        return 0;
    }

    if (!stringp(str))   { 
        notify_fail("Ckill what?\n");
        return 0;
    } 

    if (!parse_command(str, all_inventory(environment(this_player())), 
                       "%l", arg)) {  
        notify_fail("Ckill what?\n");
        return 0;
    } 

    obs = arg[1..sizeof(arg)-1]; 

    if (sizeof(obs) > 1) {
        if (arg[0] == 0 || arg[0] > 1)  { 
           	notify_fail("Be specific, you cannot kill " + 
                        COMPOSITE_ALL_LIVE(obs) + " at the same time.\n");
	      return 0;
        } 

        amb = ({ }); 
        for (i = 0; i < sizeof(obs); i++)  {
            rn = obs[i]->query_the_name(this_player()); 
            if (member_array(rn, amb) == -1) 
                amb += ({ rn });  
        } 
        if (sizeof(amb) > 1) { 
            write("Please specify who you want to kill more precisely, " +
                  "the description \"" + str + "\" could conceivably " +
                  "apply to " + COMPOSITE_WORDS(amb) + ".\n");
            return 1;  
        } 
    } 

    if (arg[0] < 0) 
        ob = obs[-arg[0]-1];
    else 
        ob = obs[0];  

    if (ob == this_player())  {
	  write("What? Attack yourself ?\n");
	  return 1;
    }

    if (this_player()->query_attack() == ob) {
	  write("Yes, yes.\n");
	  return 1;
    }

    if (tmp = environment(this_player())->query_prop(ROOM_M_NO_ATTACK)) {
       if (stringp(tmp))
           write(tmp);
       else
           write("You sense a divine force preventing your attack.\n"); 
       return 1;
    }

    if (tmp = ob->query_prop(OBJ_M_NO_ATTACK)) {
        if (stringp(tmp))
            write(tmp);
        else
            write("You feel a divine force protecting this being, your " +
                  "attack fails.\n");
	  return 1;
    }

    if (this_player()->allow_attack(ob))
	  return 1;

    if (!this_player()->query_npc() &&
         this_player()->query_met(ob) &&
	  (this_player()->query_prop(LIVE_O_LAST_KILL) != ob))
    {
	  write("Attack " + ob->query_the_name(this_player()) +
	        "?!? Please confirm by trying again.\n");
	  this_player()->add_prop(LIVE_O_LAST_KILL, ob);
	  return 1;
    }

    if (!F_DARE_ATTACK(this_player(), ob))
    {
	  write("Umum... no. You do not have enough self-discipline to dare!\n");
	  say(QCTNAME(this_player()) + " considers attacking " + QTNAME(ob) +
	      ", though does not dare to do so.\n", ({ ob, this_player() }) );
	  tell_object(ob, this_player()->query_The_name(ob) +
	      " looks at you as if ready to attack, though you see fear in " +
	      this_player()->query_possessive() + " eyes.\n");
	  return 1;
    }

    say(QCTNAME(this_player()) + " attacks " + QTNAME(ob) + ".\n",
        ({ this_player(), ob }) );
    tell_object(ob, this_player()->query_The_name(ob) + " attacks you!\n");

    this_player()->attack_object(ob);
    this_player()->add_prop(LIVE_O_LAST_KILL, ob);

    write("Ok.\n");
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
csalute(string str)
{
    object tp, *who; 

    tp = this_player(); 

    notify_fail("Csalute whom?\n"); 
    if (!str || str == "")  
         return 0;

    who = parse_this(str, "%l");
    if (!sizeof(who)) 
        return 0;

    actor("You snap a crisp cadet salute to", who); 
    targetbb(" snaps a crisp cadet salute to you.", who); 
    all2actbb(" snaps a crisp cadet salute to", who);  
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
cready(string str)
{
    object tp, *who; 

    tp = this_player(); 

    if (!stringp(str) || !strlen(str)) { 
        write("You are ready for anything.\n"); 
        allbb(" is ready for anything.");  
        return 1;
    } 

    who = parse_this(str, "%l");
    if (!sizeof(who)) { 
        notify_fail("Cready whom?\n"); 
        return 0;
    } 

    actor("You are ready for anything", who, " can throw at you."); 
    targetbb(" is ready for anything you can throw at " + 
             tp->query_objective() + ".", who); 
    all2actbb(" is ready for anything", who, " can throw at " +
             tp->query_objective() + ".");  
    return 1;
}


int
check_notebook(object tp, int notes)
{
   object nb;  

   if (!objectp(nb = present(GC_NOTEBOOK_ID, tp))) {  
       notify_fail("You don't have a notebook and quill.\n"); 
       return 0;
   } 

   if (!notes) 
        return 1;

   if (objectp(tp->query_attack())) {  
       notify_fail("You cannot use your quill while fighting!\n"); 
       return 0;
   } 

   if (environment(tp)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) {  
       notify_fail("You cannot use your quill under water!\n"); 
       return 0;
   } 

   return 1;
}



int
cplan(string str)
{
    object *who; 

    notify_fail("Cplan whom?\n"); 
    if (!stringp(str) || !strlen(str))  
        return 0;

    who = parse_this(str, "%l");
    if (!sizeof(who)) 
        return 0;

    if (sizeof(who) > 1) { 
        notify_fail("You can only <cplan> one person at once.\n");  
        return 0;
    } 

    actor("You start planning", who, "'s downfall.");  
    targetbb(" starts planning your downfall.", who); 
    all2actbb(" starts planning", who, "'s downfall.");  
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
check_visual(object tp)
{
    if (!CAN_SEE_IN_ROOM(tp)) { 
        notify_fail("It's too dark to see!\n");  
        return 0;
    } 
    return 1;
}



int
cbite(string str)
{
    string *how;  

    if (!check_notebook(this_player(), 1))  
        return 0;

    how = parse_adverb_with_space(str, "thoughtfully", 0);

    write("You bite" + how[1] + " on your quill.\n");
    allbb(" bites" + how[1] + " on " + 
          this_player()->query_possessive() + " quill.", how[1]);
    return 1;
}



int
study_emote(string str, string verba1, string verba3, string adv,  
                        string verbb1, string verbb3)
{
    object *oblist; 
    string awimn1, awimn3;

    if (!stringp(str) || !strlen(str)) 
        return 0;

    if (stringp(verbb1) && strlen(verbb1)) { 
        awimn1 = (adv + " and " + verbb1 + " in your notebook."); 
        awimn3 = (adv + " and " + verbb3 + " in " + 
                  this_player()->query_possessive() + " notebook."); 
    } 
    else { 
        awimn1 = (adv + "."); 
        awimn3 = (adv + "."); 
    } 

    if ((str == (this_player()->query_real_name())) ||
        (str == "me") ||
        (str == "myself"))
    {
        write("You " + verba1 + " yourself" + awimn1 + "\n");
        allbb(" " + verba3 + " " + this_player()->query_objective() + 
              "self" + awimn3);
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        oblist = FIND_STR_IN_OBJECT(str, environment(this_player()));
        if (!sizeof(oblist))
        {
            if (environment(this_player())->item_id(str))
            {
                write("You " + verba1 + " the " + str + awimn1 + "\n"); 
                allbb(" " + verba3 + " the " + str + awimn3); 
                return 1;
            }
            return 0;
        }
        write("You " + verba1 + " " + LANG_THESHORT(oblist[0]) + awimn1 + "\n");
        allbb(" " + verba3 + " " + LANG_THESHORT(oblist[0]) + awimn3);
        return 1;
    }

    actor("You " + verba1, oblist, awimn1);
    all2actbb(verba3, oblist, awimn3);
    targetbb(" " + verba3 + " you" + awimn3, oblist);
    return 1;
}


int
cobserve(string str)
{
    string *how; 
    string wr1, wr3; 

    if (!check_visual(this_player())) 
        return 0;

    if (check_notebook(this_player(), 1)) {  
        wr1 = "scribble a brief entry"; 
        wr3 = "scribbles a brief entry"; 
    } 

    notify_fail("Cobserve what/whom [how]?\n"); 

    how = parse_adverb_with_space(str, "interestedly", 1);

    return study_emote(how[0], "observe", "observes", how[1], wr1, wr3);  
}


int
cstudy(string str)
{
    string *how; 
    string wr1, wr3; 

    if (!check_visual(this_player())) 
        return 0;

    if (check_notebook(this_player(), 1)) {  
        wr1 = "write an entry"; 
        wr3 = "writes an entry"; 
    } 

    notify_fail("Cstudy what/whom [how]?\n"); 

    how = parse_adverb_with_space(str, "thoughtfully", 1);

    return study_emote(how[0], "study", "studies", how[1], wr1, wr3); 
}


int
cscrut(string str)
{
    string *how; 
    string wr1, wr3; 

    if (!check_visual(this_player())) 
        return 0;

    if (check_notebook(this_player(), 1)) {  
        wr1 = "write a long entry"; 
        wr3 = "writes a long entry"; 
    } 

    notify_fail("Cscrut(inize) what/whom [how]?\n"); 

    how = parse_adverb_with_space(str, "shrewdly", 1);

    return study_emote(how[0], "scrutinize", "scrutinizes", how[1], wr1, wr3); 
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
help(string str)
{
    string content, *files;
    setuid();
    seteuid(getuid());

    if (!stringp(str) || !strlen(str))
        return 0;

    if (str == "graduate") {
        write("See \"help cadet graduate\". You may also still access " +
              "the other cadet help topics through \"help cadet\".\n"); 
        return 1; 
    } 
    if (str == "cadet") {
        if (!pointerp(files = get_dir(GC_HELP_DIR)) || !sizeof(files))
            return 0;
        this_player()->more("Cadet help is available on the following " +
                            "topics e.g. \"help cadet " + files[0] + "\":\n"+
                            sprintf("%#-70s", implode(files, "\n")));
        return 1;
    }

    if (sscanf(str, "cadet %s", str) != 1)
        return 0;

    if (stringp(content = read_file(GC_HELP_DIR + str))) {
        this_player()->more(content);
        return 1;
    }

    notify_fail("There is no cadet help available on that topic.\n");
    return 0;
}


/*
 *  Function:    creputation
 *  Description: Action function to list cadet reputations in the guild
 *               (those considered exemplary and unworthy by dedicated
 *               cadets).
 */
int
creputation(string str)
{
    setuid();
    seteuid(getuid());
    return GC_TRAINROOM->list_reputations(str);
}


mapping
query_cmdlist()
{
    return ([
               "cduel" : "cduel", 
               "ckill" : "ckill", 
               "creputation" : "creputation", 
               "cask" : "cask", 
               "cgive" : "cgive", 
               "cgrant" : "cgrant", 
               "crefuse" : "crefuse", 
/*
               "ckill" : "ckill", 
               "cplan" : "cplan", 
               "cborn" : "cborn", 
               "crunout" : "crunout", 
               "cready" : "cready", 
               "chand" : "chand", 
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
               "cpush" : "cpush", 
               "cbrawl" : "cbrawl",
               "cbite"  : "cbite", 
               "cobserve" : "cobserve",  
               "cstudy" : "cstudy", 
               "cscrut" : "cscrut", 
               "csalute" : "csalute", 
*/
               "help" : "help", 
            ]);
}
