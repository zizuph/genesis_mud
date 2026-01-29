/*
 * Soul for the elven archers guild
 */

#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <options.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <files.h>

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

public mapping
query_ability_map()
{
    return ([
                "snipe"    : "/d/Krynn/guilds/elven_archers/specials/snipe",
                "quickshot": "/d/Krynn/guilds/elven_archers/specials/quickshot",
            ]);
}

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());
    
    return ([
            /*  Ability name    : Ability function */
                "snipe"         : "do_ability",
                "quickshot"     : "do_ability",
            /*  Command name    : Function name */
                "afocus"        : "focus_snipe",
                "agather"       : "gather_arrows",
                "alist"         : "alist",
                "forestwalk"    : "forestwalk", 
                "aforestwalk"   : "forestwalk", 
                "adry"          : "adry",           
                "anarrow"       : "anarrow",
                "araise"        : "araise",
                "ascan"         : "ascan",
                "astern"        : "astern",
                "atest"         : "atest",
                "athink"        : "athink",
                "awarn"         : "awarn",
                "help"          : "help",
           ]);
}

public int
alist(string str)
{
    object *list;
    list = filter(users(), &->query_guild_member(GUILD_NAME));
    
    if (sizeof(list) > 1)
    {
        list = sort_array(map(list, &->query_presentation()));  
        
        this_player()->more("The " + (sizeof(list) > 2 ? "are" : "is") + " "
        + "currently " + LANG_NUM2WORD(sizeof(list) - 1) + " other "
        + "Elven Archer" + (sizeof(list) > 2 ? "s" : "") + " in the realms:\n" 
        + implode(map(list, &operator(+)("- ",)), "\n") + "\n");
        return 1;
    }
    
    this_player()->catch_msg("There are currently no other Elven Archers in "
    + "the realms.\n");
    return 1;
}

public status
focus_snipe(string str)
{
    notify_fail("What?\n");
    if (!this_player()->query_wiz_level() &&
        this_player()->query_guild_name_occ() != GUILD_NAME)
        return 0;
    
    string name = this_player()->query_real_name();
    int sniping = OPTIONS_MANAGER->query_option("SnipeSetting", name);
    
    if (strlen(str))
    {
        int state = member_array(str, ({"off", "on"}));
        if (state > -1)
        {
            if (state == sniping)
            {
                notify_fail("You are " + (sniping ? "already focusing on "
                + "enemy vulnerabilities." : "not wasting your "
                + "energy on potential vulnerabilities.") + "\n");
                return 0;
            }
        
            this_player()->catch_msg("You will " + (!sniping ? "now focus on "
            + "enemy vulnerabilities." : "no longer spend your energy "
            + "on potential vulnerabilities.") + "\n");
            OPTIONS_MANAGER->set_option("SnipeSetting", name, state);
            return 1;
        }
    }
    
    notify_fail("You can use <afocus on/off> to set your combative "
    + "preference. You are " + (sniping ? "focusing on enemy "
    + "vulnerabilities." : "preserving your energy by not searching "
    + "for potential vulnerabilities.") + "\n");
    return 0;
}

public status
gather_arrows(string str)
{
    object *arrows, *broken, *quiver, *corpses, env;
    string preset, name;
    
    if (!strlen(str) || str != "arrows")
    {
        notify_fail("Gather what? arrows?\n");
        return 0;
    }
    
    env = environment(this_player());
    /* All visible arrows in environment */
    arrows = filter(filter(all_inventory(env), &->is_arrow()),
                    &->check_seen(this_player()));
    /* Find all the corpses */
    corpses = filter(all_inventory(env), &operator(==)(,CORPSE_OBJECT) @
                    &function_exists("create_container",));
    /* All the arrows in nearby corpses */
    foreach(object corpse: corpses)
    {
        arrows += filter(all_inventory(corpse), &->is_arrow());
    }
    /* Only arrows that you've fired. */
    arrows = filter(arrows, &operator(==)(,this_player()) @
                    &->query_prop(OBJ_O_BELONGS_TO_ARCHER));
    
    broken = filter(arrows, &->query_broken());
    
    arrows -= broken;
    
    if (sizeof(arrows))
    {
        write("You gather all of your arrows that are visible to you in the "
        + "vicinity.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + " "
        + "gathers arrows from the vicinity.\n", ({ this_player() }));
        arrows->move(this_player(), 1);
        
        if (sizeof(broken))
            write("You leave the broken arrows behind.\n");
        
        name =  interactive(this_player()) ? this_player()->query_real_name() :
                OB_NAME(this_player());
        if (!strlen(preset = OPTIONS_MANAGER->query_option("quiver", name)) ||
            !sizeof(quiver = FIND_STR_IN_OBJECT(preset, this_player())))
            quiver = FIND_STR_IN_OBJECT(GUILD_EMBLEM_ID, this_player());
        
        arrows->remove_prop(OBJ_I_HIDE);
        
        if (sizeof(quiver) && objectp(quiver[0]))
            arrows->move(quiver[0]);
        
        return 1;
    }
    
    write("You search, but find " + (sizeof(broken) ? "nothing but broken "
    + "arrows" : "none of your arrows") + " in the vicinity.\n");
    return 1;
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
 
    if (!str)
        return 0;

    
    if (sscanf(str, "elven archers %s", subject) != 1)
        if (sscanf(str, "archers %s", subject) != 1)
                return 0;
            
    if (subject == "titles")
    {
        if (this_player()->query_alignment() < -100)
            subject = "evil_arch_titles";
        else
            subject = "good_arch_titles";
    }
    
    if (subject == "commands")
    {
        if (this_player()->query_guild_name_occ() != GUILD_NAME)
            subject = "commands_lay";
        else
            subject = "commands_occ";
    }

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