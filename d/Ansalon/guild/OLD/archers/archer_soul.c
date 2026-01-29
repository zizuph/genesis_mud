/*
 * Soul for the elven archers guild
 */

#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/std/bow";

#include "guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <files.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <options.h>
#include <cmdparse.h>
#include <wa_types.h> 

#include "./lib/archer_attack.h"
#include "./lib/precision.h"
#include "./lib/fast_draw.h"

string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
}


int 
query_cmd_soul() 
{ 
    return 1; 
}


mapping
query_cmdlist()
{
    return ([
            /* Command name : Function name */
              "forestwalk"  : "forestwalk", 
              "adry"        : "adry",           
              "anarrow"     : "anarrow",
              "araise"      : "araise",
              "ascan"       : "ascan",
              "astern"      : "astern",
              "atest"       : "atest",
              "athink"      : "athink",
              "awarn"       : "awarn",
              "help"        : "help", 
              "ashoot"      : "archer_attack",
              "ashot"       : "archer_attack",
              "precision"   : "precision",
              "fast"        : "fast_draw",
           ]);
}


/* turn auto-sneaking on or off
*/
int
forestwalk(string str)
{
    int old_as = TP->query_autosneak();
    int new_as;
 
    NF("Autosneak how?\n");
    if (!str)
      TP->set_autosneak(!old_as);
    else if (str == "on" || str == "yes")
      TP->set_autosneak(1);
    else if (str == "off" || str == "no")
      TP->set_autosneak(0);
    else
      return 0;
 
    new_as = TP->query_autosneak();
 
    if (new_as)
      write("You get ready to move silently automatically.\n");
    else
      write("You stop moving silently automatically.\n");
 
    return 1;
}


int
anarrow(string str)
{
 
    object *ob;
 
    if(!strlen(str))
    {
        write("Your almond-shaped elven eyes narrow haughtily.\n");
        all("'s almond-shaped elven eyes narrow haughtily.");
        return 1;
    }
 
    ob = parse_this(str, "[at] [the] %l");
 
    if(!sizeof(ob))
    {
        notify_fail("Narrow your eyes at whom?\n");
        return 0;
    }
 
    actor("Your almond-shaped elven eyes narrow haughtily at", ob, ".");
    target("'s almond-shaped elven eyes narrow haughtily at you.", ob);
    all2act("'s almond-shaped elven eyes narrow haughtily at", ob, ".");
    return 1;
}

int
adry(string str)
{
    string weapon;
 
    weapon = TP->query_weapon(-1);
 
    if(strlen(str))
    {
        notify_fail("You do not need to target your bow on anything " + 
          "to dry it!\n");
        return 0;
    }

    if(!weapon->id("bow"))
    {
        notify_fail("You don't have a bow to dry!\n");
        return 0;
    }

    if(!TP->query_weapon(W_BOTH))
    {
        notify_fail("You don't have a bow ready in your hands to dry!\n");
        return 0;
    }

 
    write("You carefully dry all traces of moisture from your " +weapon[0]->short()+ ".\n");
    allbb(" carefully dries all traces of moisture from " +HIS(TP)+ " " +weapon[0]->short()+ ".");
    return 1;
}


int
araise(string str)
{
    string weapon;
 
    weapon = TP->query_weapon(-1);
 
    if(strlen(str))
    {
        notify_fail("You do not think it appropriate to raise your "+
        "bow in readiness at a target. If you do, try awarn!\n");
        return 0;
    }

    if(!weapon->id("bow"))
    {
        notify_fail("You don't have a bow to raise!\n");
        return 0;
    }

    if(!TP->query_weapon(W_BOTH))
    {
        notify_fail("You don't have a bow wielded to raise!\n");
        return 0;
    }

 
    write("You raise your " +weapon[0]->short()+ " indicating your readiness.\n");
    allbb(" raises " +HIS(TP)+ " " +weapon[0]->short()+ " indicating " +HIS(TP)+
      " readiness.");
    return 1;
}


int
ascan(string str)
{
 
    if(strlen(str))
    {
        notify_fail("If you want to scan a target, try examining it instead!\n");
        return 0;
    }
 
    write("You stop momentarily and scan your surroundings with the experienced "+
       "gaze of an elven tracker.\n");
    allbb(" stops momentarily and scans the surroundings with the experienced "+
       "gaze of an elven tracker.");
    return 1;
}


int
astern(string str)
{
 
    if(strlen(str))
    {
        return 0;
    }
 
    write("You become stern, your normally expressive elven features hardening.\n");
    allbb("'s demeanour becomes stern, " +HIS(TP)+ " normally expressive "+
      "elven features hardening.");
    return 1;
}

int
atest(string str)
{
    string weapon;
 
    weapon = TP->query_weapon(-1);
 
    if(strlen(str))
    {
        notify_fail("While garroting someone with your bowstring is one way " +
           "to test it, its probably best not going to help tell you whether " +
           "your bow is taut enough!\n");
        return 0;
    }

    if(!weapon->id("bow"))
    {
        notify_fail("You don't have a bow to test the bowstring of!\n");
        return 0;
    }

    if(!TP->query_weapon(W_BOTH))
    {
        notify_fail("You need to wield the bow to test the tautness of the " +
           "bowstring!\n");
        return 0;
    }

 
    write("You test the tautness of your bowstring with two fingers.\n");
    allbb(" tests the tautness of " +HIS(TP)+ " bowstring with two fingers.");
    return 1;
}


int
athink(string str)
{
 
    if(strlen(str))
    {
        return 0;
    }
 
    write("You stroke your elven chin in quiet contemplation.\n");
    allbb(" strokes " +HIS(TP)+ " distinct elven chin in quiet contemplation.");
    return 1;
}


int
awarn(string str)
{
    object obj, *ob;
    string weapon;
 
    weapon = TP->query_weapon(-1);
 
    if(!strlen(str))
    {
        notify_fail("Who do you wish to warn?\n");
        return 0;
    }

    if(!weapon->id("bow"))
    {
        notify_fail("You don't feel that a warning without a bow wielded "+
          "to back it up would be very effective.\n");
        return 0;
    }

    if(!TP->query_weapon(W_BOTH))
    {
        notify_fail("You don't feel that a warning without a bow wielded "+
          "to back it up would be very effective.\n");
        return 0;
    }

    ob = parse_this(str, "[at] [the] %l");
    if(!sizeof(ob))
    {
        notify_fail("Who do you wish to warn?\n");
        return 0;
    }
    obj = ob[0];
 
    TP->catch_msg("You raise your " +weapon[0]->short()+ ", targetting it "+
      "directly at " +QTNAME(obj)+ " in a clear warning that " +HIS(obj)+ 
      " actions will not be tolerated.\n");
    obj->catch_msg(QCTNAME(TP)+ " raises " +HIS(TP)+ " " +weapon[0]->short()+ 
      " and targets it directly at you in a clear warning that " +
      "your actions will not be tolerated.\n");
    TP->tell_watcher(QCTNAME(TP)+ " raises " +HIS(TP)+ " " +weapon[0]->short()+ 
      " and targets it directly at " +QTNAME(obj)+ " in a clear warning that " 
      +HIS(obj)+ " actions will not be tolerated.\n", obj);

    return 1;
}


int
help(string str)

{
    string subject, filename;
 
    if(!str)
        return 0;

    if(str == "archers titles" || str == "elven archers titles")
    {
        if(TP->query_alignment() < -100)
        {
           setuid();
           seteuid(getuid());
           cat(HELP_DIR + "evil_arch_titles");
           return 1;
        }
        setuid();
        seteuid(getuid());
        cat(HELP_DIR + "good_arch_titles");
        return 1;
     }

 
    if(sscanf(str, "elven archers %s", subject) != 1)
        if(sscanf(str, "archers %s", subject) != 1)
                return 0;
 
    filename = HELP_DIR + subject;
    if(file_size(filename) > 0)
    {
        setuid();
        seteuid(getuid());
        cat(filename);
        return 1;
    }
 

    NF("No help on that subject I'm afraid.\n");
    return 0;
}
