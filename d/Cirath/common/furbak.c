/*
 * Cirath talkline    plus some other stuff
 *
 * Updated mainly by Napture and Vladimir (no doubt)
 *
 *************************************************************************
 *                                                                       *
 * If you change ANYTHING of this, please change the two #defines below. *
 *              __________        ________                               *
 *************************************************************************
 *
 *  Quest information starts at approximately line 1110!
 *
 *  If you do change this file (including the quest info, then please
 *  remember to back the original up first (cp fur.c fur.c.bak)
 *
 *  And make a note in fur.history of what you've changed
 */
/* For non-quest-bit info changes, you may find it easier to ask
 *       Vladimir to make the change for you
 */


/* Last updated on :  (don't use a comma [,] in these strings!) */

#define DATE "Sunday 1.1.95   Happy New Year!"
#define BY   "Napture"


#define DOMAIN "Cirath"


/* 
 * Who else can use the fur?  Must have a good reason!
 * Please give reason below:
 *    Ged & Glindor : Cause  they are the arches
*                  That helped us get the domain.
 *   Vladimir       : Because he was the first lord and will still help.
 *    Napturejr     : For testing
 */

#define OTHER_PLAYERS   ({"Ged", "Glindor", "Napture", "Napturejr", "Vladimir" })
#define IS_OTHER(ob)    (member_array(ob->query_name(), OTHER_PLAYERS)!=-1)


#define DOMAIN_FUR      ("/d/"+DOMAIN+"/common/fur.c")

#define MAX_PATH_LEN   38   /* How much of the path do we want to see? */


inherit "/std/armour.c";

#include "/d/Cirath/common/defs.h"

#include <filepath.h>
#include <language.h>
#include <std.h>
#include <composite.h>
#include <wa_types.h>


#define NOTELOG  "/d/Cirath/log/notes"
#define DONELOG  "/d/Cirath/log/done"
#define QUESTLOG "/d/Cirath/log/quest.log"

#define MORE_OBJ "/std/board/board_more"


#ifndef QUEST_LOGGER
#define QUEST_LOGGER ("/d/Cirath/common/questlogger")
#endif

  /* Some lines have DOMAIN hard-coded for alignment purposes! */
#define HELP \
  "Available fur commands:\n"+                                            \
  "cwiz   <message> Cirath-talkline.                           (cw & ct)\n"+\
  "                 Display <message> to "+DOMAIN+" members only.       \n"+\
  "                 Only goes to those with fur!                        \n"+\
  "cmes   <message> Emote a <message> to "+DOMAIN+" members.            \n"+\
  "                 Only goes to those with fur!  (cwize, cte, cm & cwe)\n"+\
  "cwho             Display members of Cirath.                      (cw)\n"+\
  "                 The three 'X's are for : cbusy, cnotify and busy F  \n"+\
  "cirp             Display players in the "+DOMAIN+" area.             \n"+\
  "cmeet            Teleport directly to the "+DOMAIN+" workroom.       \n"+\
  "                 If used again, will return you to where you came.   \n"+\
  "cbusy   [on/off] Toggle "+DOMAIN+" talkline off and on.              \n"+\
  "                 This status is saved.                               \n"+\
  "cnotify [on/off] Toggle "+DOMAIN+" notifications off and on.         \n"+\
  "                 This status is saved.                               \n"+\
  "cquests  [<who>] Display the "+DOMAIN+" quests <who> has solved.     \n"+\
  "newfur           Update your fur to the latest version.              \n"+\
  "                 Done automatically when you log in.                 \n"+\
  "fixlog <logname> Update a log - any log (enter '?' for a brief help).\n"+\
  "cnote   [<what>] Record what you are involved with, for Lord's info. \n"+\
  "cdone   [<what>] Record what you have done, for Lord's info.         \n"+\
  "                 To view these log files, use cnotelog and cdonelog. \n"+\
  "                                                                     \n"+\
  "The following tail their respective files, or more the entire file.  \n"+\
  "cbugs     cerrors     cideas     clog     cpraise     ctypos         \n"+\
  "cbugsm    cerrorsm    cideasm    clogm    cpraisem    ctyposm        \n"+\
  "                                                                     \n"+\
  "clog             Display the most recent "+DOMAIN+" quest log.       \n"+\
  "clogm            More the entire quest log.                          \n"+\
  "                                                                     \n"+\
  "help fur [m]     Display this message (with more).                   \n"


/* Global variables */

string TPN;      /* This Player Name */    /* set in init() and new_info() */
string TDM;      /* This Players Domain */

int busy   = 0;  /* Does this player want to not hear domain messages? */
int notify = 1;  /* Does this player want to be notified of what
                    others are doing? */
                 /* Oops - BAD programming - shouldn't have a function
                    name and a variable name the same!!!  */


/* 
 * ALL the prototypes
 *
 * These aren't needed if declarations aren't made elsewhere,
 * but using these means we can have nice neat looking code!
 * 
 * Macro created (not automatically)
 *
 */
void create_armour();
int query_recover();
string query_version();
string query_update();
string wiz_info();
string new_info();
string query_auto_load();
void init_arg(string arg);
void changed();
void init_err();
void init();
void my_init();
void welcome(int intruder);
int help(string arg);
int my_quit(string str);
int cbusy(string str);
int cnotify(string str);
int q_busy(); 
int q_notify();
int w_busy(object who);
int meet(string str);
string my_break(object objto, string str, string start);
int cw(string msg);
int cwho(string str);
int cirp(string str);
string show_path(object ob, int max_len);
string idle_value(int idle);
void notify(string msg);
int newfur(string str);
int cnote(string str);
int cnote_more(string str);
int tail_file(string str);
int more_file(string str);
int clog(string str);
int fixlog(string str);
int lognext(string cmd);
void promptnext();
void fixlog_help(string logfile);
/* Quest Bits Functions start here! */
int list_quests(string str);
string group_zero(int bit);
string group_one(int bit);
string group_two(int bit);
string group_three(int bit);

/* 
 *  The code starts here!!  (about time!) 
 *
 */

void
create_armour() 
{
    set_name(({ "fur", "cirathfur" }));
    if (!IS_CLONE)
        add_name("master");
    set_short("large fur");
    set_long("A fake fur.\n");    /* Changed later */
    set_default_armour(40, A_ROBE, ({-4, 4, 0}), 0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);

#if 0
    add_prop(OBJ_M_NO_GIVE, "Why do you want to give your fur away?\n");
    add_prop(OBJ_M_NO_SELL, "Your fur is so priceless, it can't be sold!\n");
    add_prop(OBJ_M_NO_DROP, "You decide not to drop your domain fur!\n");  
#endif

    add_prop(OBJ_S_WIZINFO, "@@wiz_info");
}

int
query_recover()
{
  /* It's autoloading, so don't waste time thinking about recover */
    return 0;
}

string
query_version()  /* To be called from Tracer */
{
    return "\nLast updated on " + DATE + " by " + BY + ".\n";
}
string query_update() { return query_version(); }

string
wiz_info()
{
    string str;

    str = "To get the date of the last update, " +
          "call query_version or query_update in the fur. " +
          "If the belongs to information is wrong, call new_info.\n";

    str += "This fur belongs to '"+TPN+"' of '"+TDM+"'.\n";
    return str;
}

string
new_info()  /* To be called from Tracer */
{
    string str;

    if (this_player() != environment(this_object()))  
        return "You can only update the info for your own fur!";
    if (this_player() != this_interactive())
        return "Failed!";

    str = "\nOld Values: '"+TPN+"' of '"+TDM+"'.\n";
    TPN = capitalize(this_player()->query_real_name());
    TDM = "/secure/master"->query_wiz_dom(TPN);
    if (!TDM)
        TDM == "Visitor";
    str += "New Values: '"+TPN+"' of '"+TDM+"'.\n";

    return str;
}    

string
query_auto_load() 
{
  /* Save the busy and notify status */
    return MASTER + ":" + busy + ", " + notify + ", " + 
           worn + ", " + DATE + ", " + BY;
  /* <worn> comes from the inherited /std/armour.c */
}

void
init_arg(string arg)
{
    int bs, nt, wrn;
    string dte, by;
    
  /* Restore the busy and notify status */
    if (sscanf(arg, "%d, %d, %d, %s, %s", bs, nt, wrn, dte, by) == 5)  {
        busy   = bs;
        notify = nt;
        if (dte!=DATE || by!=BY)
            set_alarm(5.0, 0.0, "changed");
    }
    else 
        set_alarm(5.0, 0.0, "init_err");

    set_alarm(1.0, 0.0, "my_init");

    if (wrn != 0)
        set_alarm(4.0, 0.0, "wear_me");
}

/* If it was being worn when quit */
void
changed()
{
    write(my_break(this_player(), "## " + DOMAIN + " Fur : " +
        "Please note, there has been an alteration to the fur by " +
        BY + " on " + DATE + ".\n", "## CF : "));
}

void
init_err()
{
    write(my_break(this_player(), "## " + DOMAIN + " Fur : " +
        "There has been an error in restoring your fur's " +
        "busy and notify status!", "## CF : "));
    write(my_break(this_player(), "## " + DOMAIN + " Fur : " +
        "Current status :  " +
        "Busy "   + ((busy) ? "on" : "off") + ", " +
        "Notify " + ((notify) ? "on" : "off") + ".\n", 
        "## CF : "));
    call_out("changed", 1);
}

void
init()
{
    ::init();
    if (!interactive(this_player()) || this_player() != this_interactive())
      /* Has to be a player, not an npc */
        return;
    if (this_player() != environment())
      /* Has to be in a player's inventory */
        return;

    my_init();
}

void
my_init()
{
    TPN = capitalize(this_player()->query_real_name());
    TDM = "/secure/master"->query_wiz_dom(TPN);
    if (!TDM)
        TDM == "Visitor";

    if (TDM != DOMAIN && !IS_OTHER(this_player()))  {
        set_alarm(1.0, 0.0, "welcome", 1);
        return;
    }
    set_alarm(1.0, 0.0, "welcome", 0);

    add_action("my_quit",     "quit");
    add_action("help",        "help");
    add_action("newfur",      "newfur");
    add_action("fixlog",      "fixlog");
    add_action("tail_file",   "cbugs");
    add_action("tail_file",   "cerrors");
    add_action("tail_file",   "cideas");
    add_action("tail_file",   "cpraise");
    add_action("tail_file",   "ctypos");
    add_action("tail_file",   "cruntime");
    add_action("clog",        "clog");
    add_action("more_file",   "cbugsm");
    add_action("more_file",   "cerrorsm");
    add_action("more_file",   "cideasm");
    add_action("more_file",   "cpraisem");
    add_action("more_file",   "ctyposm");
    add_action("more_file",   "cruntimem");
    add_action("cnote",       "cnote");
    add_action("cnote",       "cdone");
    add_action("cnote_more",  "cnotelog");
    add_action("cnote_more",  "cdonelog");
    add_action("cnotify",     "cnotify");
    add_action("cbusy",       "cbusy");
    add_action("cwho",        "cwho");
    add_action("cirp",        "cirp");
    add_action("meet",        "cmeet");
    add_action("cw",          "cm");
    add_action("cw",          "cwe");
    add_action("cw",          "cmes");
    add_action("list_quests", "cquests");

    set_long("A large fur cloak made to be worn around the "+
             "body that seems to be made from an unknown beast. "+
             "There is a small tag on the inside that "+
             "reads: "+TPN+", respected nomad of the wastes.\n");
    set_short("large Cirathian fur");

    setuid();
    seteuid(getuid());
}

/* Called from init() */
void
welcome(int intruder)
{
    string msg;

    if (intruder)  {
        write("Sorry, you are not a member of " + DOMAIN + "!\n");
        write("The stolen fur folds in upon itself until " +
              "there is nothing left!!\n");
        notify(TPN + " tried to steal some fur from "+DOMAIN+"!");
        remove_object();
        return;
    }
    write("Some fur from "+DOMAIN+" appears in your hands.\n");

    if (IS_OTHER(this_player()))  {
        if (TP->query_wiz_level() > 39)
            notify("Proctor "+TPN+" deems the wastes with " +
                   HIS_HER(TP) + " presence.\n");
        else
            notify(TPN+" visits the wastes.\n");
    }
    else  {
     /* Personalised intros!! */
        switch (TPN)  {
            case "Vladimir" :
                msg = TPN+" Tepes ventures into the wastes looking Lordly.\n";
                break;
            case "Astro" :
                msg = TPN+" comes down from the stars to join you in " +
                          "the wastes.\n";
                break;
		 case "Chaos" :
		     msg = TPN+" floats into the wastes like the black fog that he is.\n";
                        break;
            case "Napture" :
                msg = TPN+" enters the wastes looking for something to do.\n";
                break;
            case "Serpine" :
                msg = TPN + " sneaks into the wastes looking as " +
                          "if "+HE_SHE(TP)+" is up to something.\n";
                break;
             case "Milashk" :
     	        msg = TPN + " is.\n";
		break;
            default : 
                msg = TPN+" has ventured into the wastes.\n";
        }
        notify(msg);
    }
}

/* Player command 'help' */
int
help(string arg)   
{
    string help = HELP;

    seteuid(getuid());
    if (arg != "fur" && arg != "fur m")
        return 0;
#define INSET "\n          "
    help += INSET +"You currently " + (busy ? "ignore" : "listen to") + 
                   " domain messages and " + 
            (notify ? "pay"  + INSET + "attention to" :
                      "take" + INSET + "no interest in") + 
            " other domain members' activities.\n";
    if (arg == "fur")
        write(help);
    else
        clone_object(MORE_OBJ)->more(help, 0);
    return 1;
}

/* Player command 'quit' */
int
my_quit(string str)
{
    notify(TPN + " is leaving the " + DOMAIN + " domain!");
    return 0;    /* Don't want to stop the real quit... */
}

/* Player command 'cbusy' */
int
cbusy(string str)
{ 
    int change = 1;

  /* Reverse logic..if you don't want messages, then you turn busy <on> */
    if (str)  {
        if (str == "on")      busy = 1;
        else
            if (str == "off") busy = 0;
            else
              /* Don't change, report */
                change = 0;
    }
    else  
        change = 0;
    write("Your "+DOMAIN+" talkline is "+(change ? "now" : "currently")+
          (busy ? " off" : " on")+".\n");
    if (change)
        notify(TPN + " has turned "+ this_player()->query_possessive() +
               " talkline "+ ((busy) ? "off" : "on") + "."); 
    return 1;
}

/* Player command 'cnotify' */
int
cnotify(string str)
{
    int change = 1;

   /* Unlike 'cbusy' - on means on */
    if (str)  {
        if (str == "on")       notify = 1;
        else
            if (str == "off")  notify = 0;
            else
              /* Don't change, report */
                change = 0;
    }
    else  
        change = 0;
    write("Your "+DOMAIN+" notification is "+(change ? "now" : "currently") +
          (notify ? " on" : " off") +".\n");
    if (change)
        notify(TPN + " has turned "+ this_player()->query_possessive() +
               " notification "+(notify ? "on" : "off")+".");
    return 1;
}

/* Called by other furs to see if this one if busy/notified */
int q_busy()   { return busy;   }
int q_notify() { return notify; }

/* Called by other furs to see if this player is wiz busy */
int
w_busy(object who)
{
    int wiz_busy;
    
    wiz_busy = (int) who->query_prop(WIZARD_I_BUSY_LEVEL);
    if (wiz_busy & 128)
        return 1;
    if (wiz_busy == 511)  /* Probably redundant */
        return 1;
    return 0;
}

/* Player command 'cmeet' */
int
meet(string str)
{
    string from;
  
  /* Already in the meeting room, so return */
    if (file_name(environment(this_player())) == "/d/"+TDM+"/workroom")  {
        this_player()->move_living("returning", 
            this_player()->query_prop(LIVE_O_LAST_ROOM));
        return 1;
    }

    write("You invoke the power of your fur.\n");
    tell_room("/d/"+TDM+"/workroom",TPN+" arrives by the forces of " +
        this_player()->query_possessive() + " fur.\n");
    say(QCTNAME(this_player()) + " leaves by the power of " +
        this_player()->query_possessive() + " fur.\n");
    this_player()->move_living("M", "/d/"+TDM+"/workroom");
    return 1;
}

string
my_break(object objto, string str, string start)
{
    string *txt, end;
    int i, len;
    
  /* Probably should use objto->query_screen_width() */
    len = objto->query_prop(PLAYER_I_SCREEN_WIDTH) - 5;
    if (len < 1) 
      /* Default value */
        len = 75;
    txt = explode(break_string(str, len), "\n");
    end = txt[0] + "\n";
    for (i=1; i<sizeof(txt); ++i)
        end += start + txt[i] + "\n";
    return end;
}

/* Player command - used by all domain line 'tells' */
int
cw(string msg) 
{
    object *userlist, *inv;
    int i, n, notsent, sent;
    string dom, verb;
    
    verb = query_verb();
  /* 'cirp' is a different command */
    if (!msg && verb=="cw")  {
        return cwho("");
    }
    notify_fail("What do you want to " + 
                ((verb=="cwiz" || verb=="ct") ? "say" : "emote") +
                " to other " + DOMAIN + " members?\n");
    if (!msg)  return 0;
            
    userlist = users();
    for (i=0; i<sizeof(userlist); i++) {
        
        dom = "/secure/master"->query_wiz_dom(userlist[i]->query_real_name());

        if (dom == DOMAIN || IS_OTHER(userlist[i]))  {
          /* Only write to those with fur! */
            inv = all_inventory(userlist[i]);
            for (n=0; n<sizeof(inv); n++) {
                if (inv[n]->query_name() == "fur") break;
            }
            if (n<sizeof(inv))  
                if (!(inv[n]->q_busy()))  {
                    if (verb=="cw" || verb=="cwiz" || verb=="ct")
                        tell_object(userlist[i], my_break(userlist[i], 
                                    TDM+" ("+TPN+"): "+msg, "Cw: "));
                    else
                        tell_object(userlist[i], my_break(userlist[i],
                                    "("+TDM+"): "+TPN+" "+msg, "Cm: "));
                    sent++;
                }
                else
                    notsent++;
        }
    }
    
    if (busy)
        write("You send your message to the "+ DOMAIN +" talkline.\n");
    else  {
        if (notsent)
            write(capitalize(LANG_WNUM(notsent)) + " member" + 
                  (notsent==1 ? "" : "s") + 
                  " of " + DOMAIN +" did not receive your message!\n");
        if (sent==1)
            write("You sent the message only to yourself!\n");
    }
    
    if (!sent)
        write("Shame no-one heard you.....\n");

    return 1;
}

/* Player command 'cwho' - special output */
int
cwho(string str)
{
    object *userlist, *inv;
    int i, n, num, idle;
    string dom;

    num = 0;   
    userlist = users();
  /* 'cw' doesn't want to include this_player, but 'cwho' does! */
    if (query_verb()!="cwho")  {
        for (i=0; i<sizeof(userlist); i++) {
            dom = "/secure/master"->query_wiz_dom(
                                      userlist[i]->query_real_name());
            if (dom == DOMAIN || IS_OTHER(userlist[i]))
                num++;
        }
        if (num < 2)  {
            write("There are no other "+DOMAIN+
                  " wizards currently logged on.\n");
            return 1;
        }
    }
    num = 0;  
    for (i=0; i<sizeof(userlist); i++)  {
        dom = "/secure/master"->query_wiz_dom(userlist[i]->query_real_name());
        if (dom == DOMAIN || IS_OTHER(userlist[i]))  {
            if (!num)  {
              /* Only write the title for the first member 
               * But also only if one is found! 
               */
                write("--- "+DOMAIN+" wizards currently logged on ---\n");
                if (query_verb()=="cwho")
                    write("  Who    Busy Notified Busy F         Where\n");
                num = 1;
            }
            write(sprintf("%-12s", userlist[i]->query_name()));
            idle = query_idle(userlist[i]);
            
            for (n=0; n<sizeof(inv=all_inventory(userlist[i])); ++n)
                if (inv[n]->query_name() == "fur")
                    break;
            
            if (n<sizeof(inv))  {
                write(((inv[n]->q_busy()) ? "X " : "- ") +
                      ((inv[n]->q_notify()) ? "X " : "- ") +
                      ((w_busy(userlist[i])) ? "X " : "- ") +
                      show_path(userlist[i], MAX_PATH_LEN) + "  " +
                      ((idle>3600)   ? "Dead!      " : 
                       ((idle>1200)  ? "Very Idle  " : 
                        ((idle>300)  ? "Idle       " : 
                         ((idle>60)  ? "A Bit Idle " : "")))) +
                      idle_value(idle) + "\n");
            }
            else
                write("  ** No Fur **\n");
        }
    }
    if (!num)  {
      /* Only get here if verb=='cwho' and this_player() isn't in DOMAIN
       * Shouldn't get this!!!
       */
        write("There isn't anyone from "+DOMAIN+" logged on.");
        write("Not even YOU!!!!\n");
    }
    return 1;
}

/* Player command 'cirp' to see who is in the domain (and council) */
/*
int
cirp(string str)
{
    object *userlist, *inv;
    int i, n, num, idle;
    string dom, path, dum;

    num = 0;   
    userlist = users();
    for (i=0; i<sizeof(userlist); i++) {
        dom = "/secure/master"->query_wiz_dom(userlist[i]->query_real_name());
        if (!environment(userlist[i]))
            continue;
        path = file_name(environment(userlist[i]));
        if (dom == DOMAIN || IS_OTHER(userlist[i]) || 
                   COUNCIL_MEM(userlist[i]) || 
                   (sscanf(path, "%sCirath%s", dum, dum)==2))  {
            if (!num)  {
              /* Write the header only for the first person found
               * and only if someone is found
               */
                write("--- People currently in "+DOMAIN+" ---\n");
                write("  Who       What        Where\n");
                num = 1;
            }
            write(sprintf("%-12s", userlist[i]->query_name()));
            if (dom == DOMAIN)
                if (userlist[i]->query_name()=="Vladimir")
                    write("Cirath Lord ");
                else
                    write("Cirath Wiz  ");
            else if (IS_OTHER(userlist[i]))
                write("Wiz Guest   ");
            else if (COUNCIL_MEM(userlist[i]))
                write("Council     ");
            else if (sscanf(path, "%sCirath%s", dum, dum)==2)
                if (userlist[i]->query_wiz_level())
                    write("Visitor     ");
                else
                    write("Mortal      ");
            else
              /* Shouldn't happen!! */
                write("Intruder    ");
                
            idle = query_idle(userlist[i]);
            write(show_path(userlist[i], MAX_PATH_LEN-6) + "  " +
                  ((idle>3600)   ? "Dead!      " : 
                   ((idle>1200)  ? "Very Idle  " : 
                    ((idle>300)  ? "Idle       " : 
                     ((idle>60)  ? "A Bit Idle " : "")))) +
                  idle_value(idle) + "\n");
        }
    }
    return 1;
}
*/

/* Used by cwho() and cirp() to get the path of the player's location */
string
show_path(object ob, int max_len)
{
    string str;
    
    str = RPATH(file_name(environment(ob)));
    if (strlen(str) < max_len)  {
        while(strlen(str) < max_len)
            str += " ";
        return str;
    }
    return str[strlen(str)-max_len..strlen(str)];
}

/* Used by ewho to get a time string - always the same length */
string
idle_value(int idle)
{
    string str;

    if (idle < 60)    
        return "      ";
    if (idle < 3600)
        str = sprintf("%2dm%2ds", idle / 60, idle % 60);
    else
        str = sprintf("%2dh%2dm", idle / 3600, (idle % 3600) / 60);
    return str;
}

/* Used by other functions to notify other people about something */
void
notify(string msg)   
{
    object *userlist, *inv;
    int i, n;
    string dom;
    
    userlist = users();
    for (i=0; i<sizeof(userlist); i++)  {
        dom = "/secure/master"->query_wiz_dom(userlist[i]->query_real_name());
      /* Don't want to notify ourselves of what we do! */  
        if ((dom == DOMAIN || IS_OTHER(userlist[i]))
                    && userlist[i]!=this_player())  {
            for (n=0; n<sizeof(inv=all_inventory(userlist[i])); n++)
                if (inv[n]->query_name() == "fur") 
                    break;
            if (n<sizeof(inv)) 
                if (inv[n]->q_notify())
                    tell_object(userlist[i], my_break(userlist[i], 
                                "## " +DOMAIN+" Fur : " + msg, "## CF : "));
        }
    }
}

/* Player command 'newfur' to update their fur */
int
newfur(string str)
{
    object nf;
    
/* 
 * 'domain' -> update the domain object from the one you have....
 * used if you edit (as you should) the fur in your own directory
 */
/* (TODO) But is this needed/wanted??  */

    seteuid(getuid());
    if (str == "domain")  {
        write("Sorry, you cannot update the domain master fur this " +
              "way yet.\n");
        return 1;
    }
    if (str=="create" || str=="master" || str=="update" || str=="load")  {
        write("Updating the master fur object.\n");
        MASTER->remove_object();
        DOMAIN_FUR->remove_object();
    }
    else
        if (str != "current")
            if (DOMAIN_FUR->query_version() == query_version())  {
                write("You already have the latest fur available!\n");
                return 1;
            }

    write("Updating your fur to the latest version.\n");
    if (!(nf = clone_object(MASTER)))  {
        write("Can't get the Master object!\n");
        return 1;
    }
    nf->move(this_player());
    if (!remove_object())
        write("Failed to remove the old fur!\n");
    return 1;
}

/* Player command to make a domain log - 'cnote' or 'cdone' */
int
cnote(string str)
{
    string header, text, verb;

    verb = query_verb();

    if (!str)  {
        notify_fail("What do you want to log in the domain '" + 
                    extract(verb, 1) + "' log file?\n");
        return 0;
    }
    
    header = extract(ctime(time()), 4, 15)+" "+TP->query_name()+" :\n";
    text = header + break_string(str, 70, 4) + "\n";
    seteuid(getuid());
    if (verb == "cdone")
        write_file(DONELOG, text);
    else
        write_file(NOTELOG, text);
    this_player()->catch_msg(text);
    return 1;
}

int
cnote_more(string str)
{
    string file;
    int size;
    
    seteuid(getuid());
    if (str)
        write("Argument to '"+query_verb()+"' ignored.\n");
    if (query_verb() == "cnotelog")
        file = NOTELOG;
    else
        file = DONELOG;
    size = file_size(file);
    if (size == -1 || size == -2)
        write("Can't find '"+file+"' file.\n");
    else
        if (size == 0)
            write("File '"+file+"' has no size!\n");
        else
            clone_object(MORE_OBJ)->more_file(file, 1);
    return 1;
}

/* 
 * Player commands to look at domain logs 
 */

int
tail_file(string str)
{
    string file;
    int size;
    
    seteuid(getuid());
    if (str)
        write("Argument to '"+query_verb()+"' ignored.\n");
    file = extract(query_verb(), 1);
    size = file_size("/d/" + DOMAIN + "/log/" + file);
    if (size == -1 || size == -2)
        write("Can't find domain '"+file+"' file.\n");
    else
        tail("/d/"+DOMAIN+"/log/" + file);
    return 1;
}

int
more_file(string str)
{
    string file;
    int size;

    seteuid(getuid());
    if (str)
        write("Argument to '"+query_verb()+"' ignored.\n");
    file = query_verb();
    if (strlen(file) < 2) 
        return 0;
    file = extract(file, 1, -2);
    size = file_size("/d/" + DOMAIN + "/log/" + file);
    if (size == -1 || size == -2)
        write("Can't find domain '"+file+"' file.\n");
    else
        clone_object(MORE_OBJ)->more("/d/"+DOMAIN+"/log/"+file, 1);
    return 1;
}

/* Special tail function for quest logs */
int
clog(string str)
{
  /* I didn't write most of this function, so it doesn't work
   * how I would have made it, but left in anyway!
   *                                                 Napture
   */
    string file;

    seteuid(getuid());
    if (!str)
        file = QUESTLOG;
    else
        file = QUEST_LOGGER->create_logdir_name() + "/" + str;
    if (file_size(file) == -1 || file_size(file) == -2)
        write("Can't find file '" + file + "'.\n");
    else
        tail(file);
    return 1;
}

/* Code to fix a logfile (player command) */

int count, size;
string *lines, file, file2;

int
fixlog(string str)
{
    int t;
    string line;

    if (str == "?" || str == "h")  {
        fixlog_help("");
        return 1;
    }
    notify_fail("You need to specify a file name.\n");
    if (!str || strlen(str) == 0)
        return 0;

    seteuid(getuid());
    file  = FTPATH(this_interactive()->query_path(), str);
    file2 = file + "." + this_player()->query_real_name();
    size  = file_size(file);

    if (size == -2) {
        write("Use a file, not a directory.\n");
        return 1;
    }
    if (size == -1)  {
        write("File '"+file+"' doesn't exist.\n");
        return 1;
    }

    if (rename(file, file2))  {
        write("Failed to rename '"+file+"' to '"+file2+"'\n");
        write("Maybe you don't have write access there.\n");
        return 1;
    }

    count = 1;
    lines = ({ });

    while (strlen(line = read_file(file2, count, 1)) > 0)  {
        lines += ({ line });
        count++;
        if (line == "\n") 
            break;
    }
    size = sizeof(lines);

    if (size == 0)  {
        write("No lines in the file : '"+file+"'\n");
        rename(file2, file);  /* Deletes the tmp file - which is blank..err */
        return 1;
    }

    for (t = 0; t < size; t++)
        write(lines[t]);

    promptnext();
    return 1;
}

int
lognext(string cmd)
{
    int t;
    string line;

    if (cmd == "?" || cmd == "h")  {
        fixlog_help(file);
        promptnext();
        return 1;
    }

  /* Don't write the current log back if 'd' or 'q' was selected */
    if (!cmd || (cmd != "d" && cmd != "q"))  {
        for (t = 0; t < size; t++)
            write_file(file, lines[t]);
    }
    else 
        if (cmd == "q")  {
            for (t = 0; t < size; t++)
                write_file(file, lines[t]);
            while (strlen(line = read_file(file2, count++, 1)) > 0)
                write_file(file, line);
            rename(file2, file + ".bak");
            return 1;
        }
    
    lines = ({ });
    
    while (strlen(line = read_file(file2, count, 1)) > 0)  {
        lines += ({ line });
        count++;
        if (line == "\n") break;
    }
    size = sizeof(lines);
    
    if (!size)  {
        write("End of File\n");
        rename(file2, file + ".bak");
    }
    else  {
        for (t = 0; t < size; t++)
            write(lines[t]);
        promptnext();
    }
    return 1;
}

void
promptnext()
{
    write("---- next / done / quit ----  (none, d, q): ");
    input_to("lognext");
}

void
fixlog_help(string log)
{
    string str;
    
    if (log == "")
        log = "the log file";
    else
        log = "'"+log+"'";

    str = "This is a very easy to use command\n" +
  "For each entry in "+log+", you will be prompted to either\n" +
  "do nothing, tag as done or quit - enter nothing, 'd' or 'q'.\n" +
  "All entries marked as done will be removed from "+log+",\n" +
  "all other entries will remain as they are.  To finish, either\n" +
  "enter 'q' when prompted or keep going until you reach the final entry.\n";
    write(str);
}

/* ---- End of main code, Quest stuff only below ----- */








/* 
 * QUEST BITS!!   
 *
 * This is the bit where you add your quest bit....
 *
 * You shouldn't need to change anything in list_quests()
 * other than adding new special cases.  Make your changes in
 * the function corrsponding to the bit.
 *
 * Don't forget to change the BY and DATE defines at the top of
 * the file, so that other people don't delete your changes!
 * (and so everyone knows that a change has been made....)
 */

/* Player command 'cquests' */
int
list_quests(string str)
{
    int i, grp, bit, found = 0;
    object ob;

    notify_fail("Are you sure you should be trying this??\n");
    if (this_player()->query_wiz_level() < 1) 
        return 0;  /* Why would they be in Cirath as an apprentice?  Napture */
    if ("/secure/master"->query_wiz_dom(this_player()->query_name())
                                        != DOMAIN && !IS_OTHER(this_player())) 
        return 0;
    if (!str)
        ob = this_player();
    else
        ob = find_player(str);
    if (ob)
        write("Object: " + file_name(ob) + " (interactive)\n");
    else  {
      /* No need to take care of (str=="") as this_player() should
       * always be defined....should!
       */
        write("Couldn't locate '" + str + "'.\n");
        return 1;
    }

    write("\t" + ob->query_name() + " has solved:\n");
    write("-----------------------------------------------------------\n");
    for (grp=0; grp<=4; grp++)  {
        for (bit=0; bit<=19; bit++)  {
            if (ob->test_bit(DOMAIN, grp, bit))  {
                found = 1;
                write("Group: "+grp+"   Bit: "+sprintf("%2d", bit)+"  ");
                if (grp==0)
                    write(group_zero(bit)  + "\n");
                if (grp==1)
                    write(group_one(bit)   + "\n");
                if (grp==2)
                    write(group_two(bit)   + "\n");
                if (grp==3)
                    write(group_three(bit) + "\n");
            }
        }
    }

/* 
 *  Quests that require special attention go here...
 */

    if (!found)
        write("\t\tNo quests solved or bits set!\n");
    write("-----------------------------------------------------------\n\n");
    return 1;
}

/* 
 * Remember - if you change anything, please change the DATE and BY defines
 * at the beginning - thank you.
 */
 
string
group_zero(int bit)
{
  /* Follow this pattern for new bits - if your bits use bit-wise
   * calculations to work out how far along a quest a player is, then
   * the workings should go at the end of list_quests() and the
   * following case inserted here (replace n with bit number) : 
   *
        case  n : return "See below";
   *
   */

    switch(bit)  {
        case  0 : return "Gladiator Member";
        case  1 : return "Master Axe";
        case  2 : return "Guru Axe";
        case  3 : return "Axe Quest";
        default :   return "    Unknown Quest / Bit";
    }
}

string
group_one(int bit)
{
    switch(bit)  {
        default : return " Group one bits not supported yet!\n" +
                         "\tThis bit should NOT be set yet!!";
#if 0
        default :   return "    Unknown Quest / Bit";
#endif
    }
}

string
group_two(int bit)
{
    switch (bit)  {
        default : return " Group two bits not supported yet!\n" +
                         "\tThis bit should NOT be set yet!!";
#if 0
        default :   return "    Unknown Quest / Bit";
#endif
    }
}

string
group_three(int bit)
{
    switch(bit)  {
        default : return " Group three bits not supported yet!\n" +
                         "\tThis bit should NOT be set yet!!";
#if 0
        default :   return "    Unknown Quest / Bit";
#endif
    }
}
