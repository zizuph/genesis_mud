/*
 * Gnome_soul.c
 *
 * This soul holds the general commands and feelings of the Krynn
 * Gnomes.
 * Created by Dajala.
 * March 30, 2000: Fixed bug in measure that was returning the non-vbfc
 * short desc of the item being measured. Line 2063 - Gwyneth
 *
 *13.9.2002 Milan - Fixed (hope) some runtimes and changed on the way
 *		lots calls to functiontype and removed float vars
 * 5Dec2004 - Mercade - Allowed wizards to read quicktalk.
 *
 * May 4 2006 - Navarre, Changed to used remove_shire_dirty_shadow()
 *                       A bug caught by Cotillion. (Thanks Cot!).
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include "../guild.h"
#include "../modules.h"

#define FOOD            "/d/Krynn/gnome/obj/food/"
#define HELP_DIR        GGUILD + "log/help_dir/"

/*****************************************************************************
 * Variables that are specific to each player
 *****************************************************************************/
/* for gflag */
#define GFLAG_MESSAGE(xx)        (xx->query_prop("_gnome_s_gflag_message"))
#define SET_GFLAG_MESSAGE(xx,yy) (xx->add_prop("_gnome_s_gflag_message",yy))
/* for idealight */
#define IDEALIGHT_ON(xx)         (xx->query_prop("_gnome_i_light_on"))
#define SET_IDEALIGHT_ON(xx,yy)  (xx->add_prop("_gnome_i_light_on",yy))
/* for analyze */
#define ANALYZE_ALARM(xx)        (xx->query_prop("_gnome_i_analyze_alarm"))
#define SET_ANALYZE_ALARM(xx,yy) (xx->add_prop("_gnome_i_analyze_alarm",yy))

int analyze(string str);
object  analyze_item;
int     analyze_start;

/* for the recycler */
#define SET_CALL(xx,yy)          (xx->add_prop("_gnome_i_recycler_pass",yy))
#define QUERY_CALL(xx)           (xx->query_prop("_gnome_i_recycler_pass"))
/* for the GestureMatic */
#define QUERY_OPERATIONAL(xx)    (xx->query_prop("_gnome_i_gmaker_on_"))
#define SET_OPERATIONAL(xx,yy)   (xx->add_prop("_gnome_i_gmaker_on_", yy));(xx->add_prop(LIVE_I_CONCENTRATE, yy))
#define UNSET_OPERATIONAL(xx)    (xx->remove_prop("_gnome_i_gmaker_on_"));(xx->remove_prop(LIVE_I_CONCENTRATE))
#define SET_ENTANGLED(xx)        (xx->add_prop("_gnome_i_gmaker_ent_",1))
#define REMOVE_ENTANGLED(xx)     (xx->remove_prop("_gnome_i_gmaker_ent_"))
#define QUERY_ENTANGLED(xx)      (xx->query_prop("_gnome_i_gmaker_ent_"))
#define GEST_SUB		 "_gesturematic_unfolded"
#define GEST_SUB_ENT		 "_gesturematic_unfolded_but_entangled"
#define STORE_BAKE_ALARM(xx,yy)	 (xx->add_prop("_gnome_s_bakealarm_",yy))
#define GET_BAKE_ALARM(xx)	 (xx->query_prop("_gnome_s_bakealarm_"))
#define REMOVE_BAKE_ALARM(xx)    (xx->remove_prop("_gnome_s_bakealarm_"))
/* for the PersonalCleanlinessModule */
#define SET_WASH(xx,yy)          (xx->add_prop("_gnome_i_washing",yy))
#define QUERY_WASH(xx)           (xx->query_prop("_gnome_i_washing"))
#define UNSET_WASH(xx)           (xx->remove_prop("_gnome_i_washing"))
#define SET_WASH_SUCCESS(xx,yy)  (xx->add_prop("_gnome_i_wash_success",yy))
#define QUERY_WASH_SUCCESS(xx)   (xx->query_prop("_gnome_i_wash_success")) 
#define UNSET_WASH_SUCCESS(xx)   (xx->remove_prop("_gnome_i_wash_success"))
/* For the DistillationApparatus */
#define FUNNEL_OPEN(xx)		 (xx->add_prop("_gnome_i_funnel_open", 1))
#define QUERY_FUNNEL_OPEN(xx)	 (xx->query_prop("_gnome_i_funnel_open"))
#define FUNNEL_CLOSED(xx)	 (xx->remove_prop("_gnome_i_funnel_open"))
#define ADD_VALUE(xx,yy)	 (xx->add_prop("_gnome_i_dist_value", \
				    xx->query_prop("_gnome_i_dist_value") + yy))
#define QUERY_VALUE(xx)	 	 (xx->query_prop("_gnome_i_dist_value"))
#define REMOVE_VALUE(xx)	 (xx->remove_prop("_gnome_i_dist_value"))
#define ADD_LIQUID(xx,yy)	 (xx->add_prop("_gnome_i_liquid_amount", \
				    xx->query_prop("_gnome_i_liquid_amount") + yy))
#define QUERY_LIQUID(xx)	 (xx->query_prop("_gnome_i_liquid_amount"))
#define REMOVE_LIQUID(xx)	 (xx->remove_prop("_gnome_i_liquid_amount"))
#define STORE_SPILL_ALARM(xx,yy) (xx->add_prop("_gnome_i_spill_alarm", yy))
#define REMOVE_SPILL_ALARM(xx)	 (xx->remove_prop("_gnome_i_spill_alarm"))
#define QUERY_SPILL_ALARM(xx)	 (xx->query_prop("_gnome_i_spill_alarm"))

/*****************************************************************************
 * Prototypes								     *
 *****************************************************************************/

int wash_me(string str);


/*****************************************************************************
 * Soul identifying and autoloading
 *****************************************************************************/

string get_soul_id() { return "Krynn Gnomes"; }

int query_cmd_soul() { return 1; }

/*****************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 *****************************************************************************/

mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
      "analyze":"analyze",
      "build":"build",
      "check":"check",        /* module, flag 3 */
      "concentrate":"concentrate",
      "con":"concentrate",	
      "gclean":"clean",        /* module, flag 8 */
      "gclose":"close_funnel",      /* module, flag 12 */
      "drain":"drain_dist",	/* module, flag 12 */
      "end":"end_gbake",	/* module, flag 10 */
      "engulf":"engulf",      /* module, flag 3 */
      "flush":"flush",        /* module, flag 7 */
      "fold":"fold",          /* module, flag 9 */
      "gbake":"gbake",	/* module, flag 10 */
      "gbored":"gbored",
      "ggesture":"ggesture",  /* module, flag 9 */
      "gfinger":"gfinger",    /* module, flag 9 */
      "gflag":"gflag",        /* module, flag 1 */
      "gset":"set_message",   /* module, flag 1 */
      "gidea":"idea_light",   /* module, flag 0 */
      "glint":"glint",
      "gmarvel":"gmarvel",
      "gmarv":"gmarvel",
      "gnlist":"gnlist",
      "gnli":"gnlist",
      "gpoint":"gpoint",      /* module, flag 9 */
      "gpoke":"gpoke",        /* module, flag 9 */
      "gsay":"gsay",
      "-":"gsay",
      "gscratch":"gscratch",  /* module, flag 9 */
      "gslap":"gslap",        /* module, flag 9 */
      "gsmile":"gsmile",
      "gthink":"gthink",
      "gthi":"gthink",
      "gtinker":"gtinker",
      "gtink":"gtinker",
      "gwave":"gwave",        /* module, flag 9 */
      "help":"help",
      "ignite":"ignite",      /* module, flag 3 */
      "makecoffee":"makecoffee", /* module, flag 6 */
      "measure":"measure",    /* module, flag 5 */
      "no":"no",
      "gopen":"open_funnel",        /* module, flag 12 */
      "goil":"oil",            /* module, flag 8 */
      "philosophy":"philosophy",
      "philo":"philosophy",
      "gpolish":"polish",      /* module, flag 8 */
      "gpour":"pour_drink",         /* module, flag 12 */
      "gpull":"recycle_2",          /* module, flag 7 and 11 */
      "pull":"pull",                /* Reference to gpull */
      "refresh":"refresh",          /* module, flag 2 */
      "recycle":"recycle",          /* module, flag 7 */
      "switch":"ext_engine",        /* module, flag 3 */
      "toot":"toot",                /* module, flag 3 */
      "travel":"travel",            /* module, flag 4 */
      "unentangle":"unentangle",      /* module, flag 9 */
      "unfold":"unfold",      /* module, flag 9 */
      "gwash":"wash"                /* module, flag 11 */
    ]);
}

static mixed
parse_this(string str, string form)
{
    object   *oblist, *tmplist = ({});
    int      i;

    if (!CAN_SEE_IN_ROOM(TP))
	return tmplist;

    if (!str || (!parse_command(L(str), E(TP), form, oblist)))
	return tmplist;

    oblist = NORMAL_ACCESS(oblist, 0, 0);
    if (!sizeof(oblist))
	return tmplist;

    for (i = 0; i < sizeof(oblist); i++)
    {
	if (objectp(oblist[i]) && (TP != oblist[i]) && CAN_SEE(TP, oblist[i]))
	    tmplist = tmplist + ({ oblist[i] });
    }
    return tmplist;
}


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *  me      - I
 *  for_obj - The looker
 * Returns:  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{   
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if(subloc == GEST_SUB)
    {
	if (for_obj == me)
	    return "Your Gesturematic is operational.\n"; 
	else
	    return C(HE(me)) + " is operating a giant mechanical arm.\n";
    }
    if(subloc == GEST_SUB_ENT)
    {
	if (for_obj == me)
	    return "You are hopelessly entangled into the wires of your "
		    + "Gesturematic.\n";
	else
	    return C(HE(me)) + " is hopelessly entangled into a lot of "
		    + "crossed wires.\n";
    }
    return "";
}




/******************* general funtions *************************************/

/* returns the gizmo 
 * needed to call functions in the gizmo.
 */

object
find_gizmo(object player)
{
    return present("k_gizmo", player);
}


/* checks whether the correct module flag is set in the gizmo 
 * returns 1: module present
 *         0: module not present
 */

int
flag(int number, int break_check_flag)
{
    object gizmo = find_gizmo(TP);

    if(break_check_flag)
	if(gizmo->break_chance(number))
	    return -1;
    return (gizmo->query_flag(number));
}

/* Checks several parameters in the steamengine module as there is 
 * pressure, fire, wood and water.
 * Returns:  Somethings wrong: The failure message
 *           Nothing wrong:    'ok'
 */

string
steamengine_check(object player)
{
    if(!flag(3,0))
	return "What?\n";

    if(!flag(2,0))
	return "You'll need a waterdispenser first!\n";

    if(!(find_gizmo(player)->check_fire()))
	return "You have no fire in the engine.\n";

    if(!(find_gizmo(player)->check_water()))
	return "You have no water left.\n";

    if(!(find_gizmo(player)->check_steam()))
	return "You do not yet have enough pressure.\n";
    return "ok";
}


/* Finds the named targets to do something to.
 */

object*
get_target(string str)
{
    if (!str)
	return 0;
    return parse_this(str, "[at] [the] %i");
}


/* paralyzes the player for some time
 */

void
paralyze_player(object player, string fail_msg, string stop_msg, int time)
{
    object paralyze;
    setuid(); seteuid(getuid(TO));
    paralyze = clone_object("/std/paralyze");
    paralyze->set_name("_paralyzed_by_gnome_soul_");
    paralyze->set_no_show(1);
    paralyze->set_remove_time(time);
    paralyze->set_stop_message(stop_msg);
    paralyze->set_fail_message(fail_msg);
    paralyze->set_stop_verb("depart"); /* No command to stop the paralyze! */
    paralyze->set_stop_object(0);   /* Use the messages set above */
    paralyze->move(player, 1);      /* Now DO the paralyze */
}

int
darkcheck(object player)
{
    if(!CAN_SEE_IN_ROOM(player))
    {
	player->catch_msg("It's too dark to do that.\n");
	return 0;
    }
    return 1;
}


/**************************************************************************
 * Here follow the functions. New functions should be added in alphabetic
 * order.
 **************************************************************************/

/********************* analyze ********************************************/

/*
 * I have changed the Analyze code as it returned a heap of errors // Carnak
 */

void
end(object player)
{
    object heap;

    setuid(); seteuid(getuid(this_object()));
    heap = clone_object(GOBJ + "heap");
    heap->add_prop(OBJ_I_WEIGHT, (analyze_item->query_prop(OBJ_I_WEIGHT)));
    heap->add_prop(OBJ_I_VOLUME, (analyze_item->query_prop(OBJ_I_VOLUME)));
    heap->move(environment(player));
    
    tell_room(environment(player), QCTNAME(player) + " drops a " +
    "heap of parts.\n", player);
    
    player->catch_msg("You drop the now useless parts of the " +
    analyze_item->short() + ".\n");
    
    remove_alarm(ANALYZE_ALARM(player));
    
    analyze_item->remove_object();
    analyze_start = 0;
}

void
process_input(string str)
{
    if (!analyze_start && IN_ARRAY(str, ({ "rise", "stand", "stand up" })))
    {
        this_player()->catch_msg("You rise to your feet.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player()) +
        " rises from " + this_player()->query_possessive() + " seated " +
        "position.\n", this_player());
        return;
    }
    
    if (analyze_start && IN_ARRAY(str, ({ "q", "quit", "abort", "exit"})))
    {
        this_player()->catch_msg("You finish your analysis without reaching " +
        "a conclusion, the " + analyze_item->short() + " remains a mystery.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player()) +
        " seems to be finished but looks unhappy.\n", this_player());
        
        end(this_player());
        return;
    }
    
    if (sscanf(str, "analyze %s", str))
    {
        analyze_start = -1;
        analyze(str);
        return;
    }
    
    if (!analyze_start)
        this_player()->catch_msg("You have finished analyzing, perhaps you " +
        "would like to 'stand'?\n");
    else 
        this_player()->catch_msg("You are too absorbed with taking apart " +
        "your " + analyze_item->short() + ", but you could always 'abort' " +
        "if you are bored with it.\n");
    
    input_to(process_input, 1);
}

int
analyze_msg(object player)
{
    string *msg,
            desc;
    int     success,
            level,
            a, i;
    mixed   info;

    if (!objectp(player))
        return 0;
    
    if (!player->query_relaxed_from_combat())
    {
        player->catch_msg("You are interrupted by combat before reaching a " +
        "conclusion, the " + analyze_item->short() + " remains a mystery.\n");
        
        tell_room(environment(player), QCTNAME(player) + " seems to be " +
        "finished but looks unhappy.\n", player);
        
        end(player);
        return 0;
    }
    
    level   = min(player->query_stat(4) - player->query_average_stat(), 35);
    success = ((player->query_skill(SS_BUILD) * (max(a, 5) + 35)) / 100) + 50;
    success = success - (analyze_item->query_prop(OBJ_I_RES_IDENTIFY));
    
    if (time() - analyze_start > 36)
    {
        info = (analyze_item->query_prop(MAGIC_AM_ID_INFO));
        
        if (!info)
        {
            if (analyze_item->query_prop(OBJ_I_IS_MAGIC_ARMOUR) || 
                analyze_item->query_prop(OBJ_I_IS_MAGIC_WEAPON) ||
                analyze_item->query_prop(MAGIC_AM_MAGIC))
            {
                player->catch_msg("You were unable to discern any notable " +
                "information from your analysis, but the " +
                analyze_item->short() + " does appear to possess some " +
                "magical properties.\n");
            }
            else
            {
                player->catch_msg("This object doesn't seem to be magical.\n");
            }
        }
        else
        {
            msg = ({ });
            for (i = 0; i < (sizeof(info) - 1); i += 2)
            {
                if (intp(info[i]))
                {
                    level = info[i];
                    desc  = info[i + 1];
                }
                else if (intp(info[i + 1]))
                {
                    level = info[i + 1];
                    desc  = info[i];
                }
                else
                {
                    break;
                }

                if (level <= min(((success / 3) + random(11)), 50))
                {
                    msg += ({ desc });
                }
            }
            
            if (sizeof(msg))
            {
                player->catch_msg("You learn the following:\n");
                foreach(string m: msg)
                {
                    player->catch_msg(m);
                }
            } else
            {
                player->catch_msg("You were unable to learn anything new.\n");
            }
        }
        
        end(player);
        return 1;
    }
    
    if (min(success, 98) < random(100))
    {
        process_input("quit");
        return 0;
    }
    
    msg = ({"take", " away some parts", "remove", " some bits", "look",
    " at some bits", "check", " some especially interesting parts", 
    "look", " thoughtfully", "put", " aside some parts", "rest",
    " a little bit", "turn", " around one piece", "ponder", 
    " the situation", "throw", " away a seemingly useless part",
    "break", " something in two"});
    a = random(11);
    
    player->catch_msg("You " + msg[a*2] + msg[a*2+1] + ".\n");
    
    tell_room(environment(player), QCTNAME(player) + " " + msg[a*2] +
    "s" + msg[a*2+1] + ".\n", player);
    
    SET_ANALYZE_ALARM(player, set_alarm(6.0, 0.0, &analyze_msg(player)));
    
    return 1;
}

int
analyze(string str)
{
    object *obs, ob;
    
    if ((this_player()->query_skill(SS_BUILD)) < 1)
    {
        notify_fail("You don't know how to do that.\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        notify_fail("Analyze what?\n");
        return 0;
    }
    
    parse_command(str, ({ }), "[the] / [a] / [an] %s", str);
    
    if (!sizeof(obs = FIND_STR_IN_OBJECT(str, this_player())))
    {
        notify_fail("You do not hold " + LANG_ART(str) + " " + str + ".\n");
        return 0;
    }
    
    ob = obs[0];
    
    if (living(ob))
    {
        notify_fail("You cannot analyze " + QTNAME(ob) + ".\n");
        return 0;
    }
    
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        notify_fail("You could not possibly analyze something " +
        "without being able to see it.\n");
        return 0;
    }
    
    if(ob->query_prop(OBJ_I_BROKEN))
    {
        notify_fail("The " + ob->short() + " is too badly damaged to " +
        "be analyzed.\n");
        return 0;
    }
    
    if(ob->query_prop(OBJ_M_NO_DROP))
    {
        notify_fail("You see no way of taking the " + ob->short() +
        " apart.\n");
        return 0;
    }
    
    if(analyze_start > 0)
    {
        notify_fail("You are still busy with another object.\n");
        return 0;
    }
    
    if (!this_player()->query_relaxed_from_combat())
    {
        notify_fail("Your mind needs to settle down from the recent " +
        "combat before you can begin to analyze.\n");
        return 0;
    }
    
    if (this_player()->query_prop("_live_o_forge_"))
    {
        notify_fail("You are too occupied with forging to begin " +
        "analyzing things.\n");
        return 0;
    }
    
    if (analyze_start < 0)
    {
        write("You remain seated and start to take apart the " + ob->short() +
        " with your gizmo.\n");
    
        say(QCTNAME(this_player()) + " remains seated on the ground and " +
        "starts to take apart " + this_player()->query_possessive() + " " +
        ob->short() + ".\n");
        
    } else
    {
        write("You sit down and start to take apart the " + ob->short() +
        " with your gizmo.\n");
    
        say(QCTNAME(this_player()) + " seats " + this_player()->query_objective() +
        "self on the ground and starts to take apart " +
        this_player()->query_possessive() + " " + ob->short() + ".\n");
    }
    
    
    SET_ANALYZE_ALARM(this_player(), set_alarm(6.0, 0.0, &analyze_msg(this_player())));
    
    analyze_item    = ob;
    analyze_start   = time();
    
    input_to(process_input, 1);
    return 1;
}

/******************** gbored **********************************************/

int
gbored()
{
    write("YAWN... Again, there is nothing to do for your superior "
      + "intellect.\n");
    all(" yawns. There is no real challenge for "
      + HIM(TP) + " in this world today.");
    return 1;
}

/******************** build **********************************************/

void
build_msg(object player)
{
    int a;
    string *msg;
    msg = ({"put together some parts","add some springs","add some wheels",
      "happily add a whistle", "add a nicely shaped bell", 
      "frown at your progress then continue working",
      "inspect the internals then give a satisfied nod",
      "rotate a piece so it fits better",
      "wriggle a recently-attached part and look thoughtful"
    });
    a = random(sizeof(msg));
    player->catch_msg("You " + msg[a] + ".\n");
    tell_room(E(player), QCTNAME(player) + " works hard at something"
      + ".\n", player); 
}

void
build_ready(object player, object kit, int alarm)
{
    int skill, min_skill, i;
    string type;

    remove_alarm(alarm);
    tell_room(E(player), QCTNAME(player) + " finished " +
      HIS(player) + " work.\n", player);
    player->catch_msg("You finished your new module!\n");
    skill = (TP->query_skill(SS_BUILD));
    type = (kit->get_type());
    for(i=0;i<sizeof(TYPES);i++)
    {
	if(type == TYPES[i])
	    min_skill = MIN_SKILLS[i];
    }

    if(skill < min_skill)
    {
	kit->is_bomb();
	if(skill > (min_skill - 10))
	    player->catch_msg("But somehow, what you built "
	      + "doesn't look right.\n");
    }
    kit->set_short("readyToAttach" + capitalize(type));
    kit->set_long("This " + capitalize(type) + "-module is ready "
      + "to attach to the gizmo.\n"); 
    kit->set_built();
    kit->set_break_chance(2*skill - min_skill);
    kit->add_name("module");
}

int
build(string str)
{
    int alarm;
    object kit;

    if(!GMEMBER(TP))
	return 0;
    if(!P("kit", TP))
	return 0;
    if(!(kit = P("kit_for_" + str, TP)))
    {
	NF("You don't have that kit.\n");
	return 0;
    }
    if((TP->query_skill(SS_BUILD)) < 1)
    {
	NF("You don't know how to do that.\n");
	return 0;
    }
    if(!darkcheck(TP))
	return 1;
    write("You start assembling the parts.\n");
    say(QCTNAME(TP) + " sits down and starts working on something.\n"
      + C(HE(TP)) + " seems to be completely absorbed.\n");
    paralyze_player(TP, "You are completely absorbed by building " 
      + "the " + str + ".\n", "", 30);
    alarm = set_alarm(6.0, 6.0, &build_msg(TP));
    set_alarm(38.0, -1.0, &build_ready(TP, kit, alarm));
    return 1;
}


/********************* concentrate **************************************/

int
concentrate(string str)
{
    if(!str)
    {
	allbb(" concentrates deeply.");
	write("You concentrate deeply.\n");
	return 1;
    }
    allbb(" concentrates hard on " + str + ".");
    write("You concentrate hard on " + str + ".\n");
    return 1;
}


/**************** Module: DistillationApparatus****************************
 *                           flag:   12                                   *
 **************************************************************************/

void
spill_water(object player, int flag)
{
    int alarm;

    if(QUERY_LIQUID(player) < 1)
	return;
    if(player->query_skill(SS_AWARENESS)/3+random(60) > 50)
    {
	if(flag == 1)
	    player->catch_msg("Some water drips from the open funnel "
	      +"of your DistillationApparatus.\n");
	else
	    player->catch_msg("Some liquid sips from your gizmo.\n");
    }
    if(QUERY_LIQUID(player) < 100)
    {
	REMOVE_LIQUID(player);
	REMOVE_VALUE(player);
    }
    else
    {
	ADD_LIQUID(player, -100);
	ADD_VALUE(player, -100 * QUERY_VALUE(player) / QUERY_LIQUID(player));
    }
    alarm = set_alarm(100.0, -1.0, &spill_water(player,1));
    STORE_SPILL_ALARM(player,alarm);
}

// Called from burn_wood() in the gizmo:

void
distill_contents(string str)
{
    int i, j, boom, water, alk;
    object gizmo, *inv, player;
    string *inherits;

    player = TP;
    if(!(flag(12,0)))
	return;
    if(!QUERY_LIQUID(player))
	return;
    gizmo = find_gizmo(player);
    inv = all_inventory(player);
    for(j=0;j<sizeof(inv);j++)
    {
	inherits = inherit_list(inv[j]);
	for(i=0;i<sizeof(inherits);i++)
	    if(inherits[i] == "/std/torch.c")
		if(inv[j]->query_lit())
		    boom = 1;
    }
    if(boom == 1)
    {
	tell_room(E(player), "BOOOOM!!! " + QCTNAME(player) 
	  + " is the center of an explosion.\n", player);
	player->catch_msg("BOOOOM!!! Your gizmo exploded!\n");
	tell_room(E(player), "Shards of glass are flying everywhere.\n");
	player->heal_hp(-(player->query_max_hp()/10));
	if(player->query_hp < 0)
	    player->do_die();
	REMOVE_LIQUID(player);
	REMOVE_VALUE(player);
	REMOVE_SPILL_ALARM(player);
	gizmo->do_break(12);
	if(flag(3,0))
	    gizmo->do_break(3);
	if(!random(2) && flag(2,0))
	    gizmo->do_break(2);
	if(!random(2) && flag(2,0))
	    gizmo->do_break(2);
	if(!random(4) && flag(4,0))
	    gizmo->do_break(2);
	if(!random(4) && flag(6,0))
	    gizmo->do_break(2);
	if(!random(5) && flag(8,0))
	    gizmo->do_break(2);
	if(!random(3) && flag(10,0))
	    gizmo->do_break(2);
	if(!random(3) && flag(11,0))
	    gizmo->do_break(2);
	return;
    }
    water = (QUERY_LIQUID(player)*2)/10;
    alk = (QUERY_VALUE(player)*2)/10;
    ADD_LIQUID(player, -water);
    ADD_VALUE(player, -alk);
    tell_room(E(player), "A bell rings.\nA bubbling noise emanates from "
      + QTNAME(player) + ".\n", player);
    player->catch_msg("A bell rings.\nA bubbling noise emanates from "
      + "your gizmo.\n");
    water = water / 10;
    if(gizmo->check_water() + water >= 40)
    {
	gizmo->refill_water(40);
	player->catch_msg("A gush of water streams from your gizmo.\n");
	tell_room(E(player), "A stream of water gushes from " + QTNAME(player) 
	  + "'s gizmo.\n", player);
    }	
    else
	gizmo->refill_water(gizmo->check_water() + water);
    alk = alk / 10;
    if(gizmo->check_wood() + alk >= 14)
    {
	gizmo->set_wood(14);
	player->catch_msg("Your gizmo spits out some pure alcohol.\n");
	tell_room(E(player), QCTNAME(player) + "'s gizmo spits out some "
	  + "transparent liquid.\n", player);
    }
    else
	gizmo->set_wood(gizmo->check_wood() + alk);
}

int
open_funnel(string str)
{
    int alarm;

    if(!(flag(12,0)))
	return 0;
    if(str != "funnel")
    {
	NF("Open what?\n");
	return 0;
    }
    if(!darkcheck(TP))
	return 1;
    if(QUERY_FUNNEL_OPEN(TP))
    {
	NF("The funnel is already open.\n");
	return 0;
    }
    write("You open the funnel of the DistillationApparatus.\n");
    say(QCTNAME(TP) + " opens a funnel on " + HIS(TP)
      + " gizmo.\n");
    alarm = set_alarm(100.0, -1.0, &spill_water(TP,1));
    STORE_SPILL_ALARM(TP,alarm);
    FUNNEL_OPEN(TP);
    return 1;
}

int
pour_drink(string str)
{
    int i, many, inherit_flag = 0;
    string arg, *inherits;
    object drink;

    if(!flag(12,0))
	return 0;
    if(!QUERY_FUNNEL_OPEN(TP))
    {
	NF("The funnel of the Distillationapparatus is still closed.\n");
	return 0;
    }
    if(!parse_command(str, E(TP), "[the] / [a] %d %w 'into' [the] 'funnel' [.]",  many ,arg))
    {
	NF("Pour how many what into the funnel?\n");
	return 0;
    }
    if(!darkcheck(TP))
	return 1;
    if(!(drink = P(arg, TP)))
    {
	NF("You don't have a " + arg + ".\n");
	return 0;
    }
    inherits = inherit_list(drink);
    for(i=0;i<sizeof(inherits);i++)
	if(inherits[i] == "/std/drink.c")
	    inherit_flag = 1;
    if(!inherit_flag)
    {
	NF("You cannot pour the " + drink->short() + " down the funnel.\n");
	return 0;
    }
    if(many >= drink->num_heap())
    {
	many = drink->num_heap(); 
	write("You take carful aim and pour " + drink->short() + " down the funnel.\n");
	say(QCTNAME(TP) + " fills " + drink->short()  + " into " + HIS(TP)
	  + " gizmo.\n"); 
    }
    else
    {
	write("You take carful aim and pour " + many + " " + drink->query_adj() + " " 
	  + drink->query_name() + " down the funnel.\n");
	say(QCTNAME(TP) + " fills " + drink->short()  + " into " + HIS(TP)
	  + " gizmo.\n"); 
    }
    if(QUERY_LIQUID(TP) >= 3000)
    {
	NF("A bell rings.\nA valve opens and your precious drink spills out.\n"
          + "The CentralCavityContainingLiquidsToBeDistilled seems to be already full.\n");
	say("But somehow spilled it to the floor.\n");
	drink->remove_object();
	return 0;
    }
    i = drink->query_soft_amount() * many;
    if(i + QUERY_LIQUID(TP) >= 3000)
    {
	write("A valve opens and spits out some of the liquid you just "
	  + "filled in.\n");	
	say(QCTNAME(TP) + "'s gizmo spits out again some of the liquids.\n");
	i = 3000 - QUERY_LIQUID(TP);
    }
    ADD_VALUE(TP, i * drink->query_alco_amount() / drink->query_soft_amount());
    ADD_LIQUID(TP, i);
    drink->set_heap_size(drink->num_heap() - many);
    return 1;
}

int
close_funnel(string str)
{
    if(!(flag(12,0)))
	return 0;
    if(!darkcheck(TP))
	return 1;
    if(str != "funnel")
    {
	NF("Close what?\n");
	return 0;
    }
    if(!QUERY_FUNNEL_OPEN(TP))
    {
	NF("The funnel is already closed.\n");
	return 0;
    }
    write("You close the funnel.\n");
    say(QCTNAME(TP) + " closes a funnel on " + HIS(TP)
      + " gizmo.\n");
    remove_alarm(QUERY_SPILL_ALARM(TP));
    REMOVE_SPILL_ALARM(TP);
    FUNNEL_CLOSED(TP);
    return 1;
}


/****************** Module: MasterBakerFritter ****************************
 *                           flag:   10                                   *
 **************************************************************************/

void
give_fritter(object fritter, object player, int baking_time)
{
    tell_room(E(player), "A bell rings.\n");
    player->catch_msg("You receive your hot fritter.\n");

    fritter->set_durch(baking_time);
    fritter->move(player);

    REMOVE_BAKE_ALARM(player);
}   

void
smell_fritter(object fritter, object player, int i, int call)
{
    int alarm;

    if(call < 7)
	tell_room(E(player), "You smell a delicious aroma.\n");
    else if(call == 7)
	tell_room(E(player), "Something smells burned.\n");
    else
    {
	tell_room(E(player), "Black clouds gather around " + QTNAME(player)
	  + ".\nIt smells burned.\n", player);
	player->catch_msg("Black clouds gather around you. Is there "
	  + "something burning?\n");		 
    }
    call++;
    if(call < i)
    {
	alarm = set_alarm(20.0, -1.0, &smell_fritter(fritter, player, i, call));
	STORE_BAKE_ALARM(player,alarm);
    }
    else
    {   	
	alarm = set_alarm(20.0, -1.0, &give_fritter(fritter, player, i));
	STORE_BAKE_ALARM(player,alarm);
    }
}

void
end_it(string fruit, object fritter, object player, int call)
{
    int alarm;

    if(call == 0)
    {	
	player->command("$oops");
	player->catch_msg("The closing mechanism jammed! "
	  + "Most of the flour aimed at the " + fruit
	  + " blasts at you and leaves you being a white gnome.\n");	   	
	tell_room(E(player), "Suddenly a white cloud emanates from "
	  + QTNAME(player) + "'s gizmo and engulfs " + HIM(player)
	  + " completely.\n", player);
	find_gizmo(player)->reduce_flour();
	alarm = set_alarm(5.0, -1.0, &end_it(fruit, fritter, player, 1));
	STORE_BAKE_ALARM(player,alarm);
	return;	
    }
    if(call == 1)
    {
	player->catch_msg("The grinder starts working and showeres you "
	  + " in a sticky substance.\nIt then grinds to a halt.\n");
	tell_room(E(player), "Then, " + QTNAME(player) + "'s gizmo starts "
	  + "working again and showers " + HIM(player) + " in "
	  + "a sticky substance.\n", player);
	alarm = set_alarm(10.0, -1.0, &end_it(fruit, fritter, player, 2));
	STORE_BAKE_ALARM(player,alarm);
	player->remove_prop("_gnome_s_fruit_");
	return;
    }
    if(call == 2)
    {
	player->catch_msg("Small trickles of water drip from your gizmo.\n");
	find_gizmo(player)->reduce_water();		
	fritter->remove_object();
	REMOVE_BAKE_ALARM(player);
	return;
    }
}

void
gbake_msg(string fruit, object fritter, object player, int call)
{
    int alarm, i;

    if(call == 0)
    {
	player->catch_msg("The opening begins to close.\nYour gizmo "
	  + "vibrates.\n");
	tell_room(E(player), QCTNAME(player) + "'s gizmo starts to vibrate.\n"
	  ,player);
	if(random(5) == 0)
	    alarm = set_alarm(5.0, -1.0, &end_it(fruit, fritter, player, 0));
	else
	    alarm = set_alarm(5.0, -1.0, &gbake_msg(fruit, fritter, player, 1));
	STORE_BAKE_ALARM(player,alarm);
	return;
    }
    if(call == 1)
    {
	find_gizmo(player)->reduce_flour();
	player->catch_msg("As soon as the opening has closed, flour is blown "
	  + "at the " + fruit + ".\n");
	tell_room(E(player), "A small white cloud gathers.\n");
	alarm = set_alarm(5.0, -1.0, &gbake_msg(fruit, fritter, player, 2));
	STORE_BAKE_ALARM(player,alarm);
	return;	
    }
    if(call == 2)
    {
	player->catch_msg("The grinder activates and a series of gears and "
	  + "mechanisms begin to rotate noisily.\n");
	tell_room(E(player), QCTNAME(player) + "'s gizmo creates some noises "
	  + "making you believe that something is grinded.\n", player);
	player->remove_prop("_gnome_s_fruit_");
	alarm = set_alarm(5.0, -1.0, &gbake_msg(fruit, fritter, player, 3));
	STORE_BAKE_ALARM(player,alarm);
	return;
    }
    if(call == 3)
    {
	tell_room(E(player), "A whistle blows.\n", player);
	player->catch_msg("A whistle blows indicating the beginning of the "
	  + "mixing process.\n");
	alarm = set_alarm(3.0, -1.0, &gbake_msg(fruit, fritter, player, 4));
	STORE_BAKE_ALARM(player,alarm);
	return;
    }
    if(call == 4)
    {
	tell_room(E(player), QCTNAME(player) + "'s gizmo makes WHOOSH. Then "
	  + "clanking and banging noises can be heard.\n", player);
	player->catch_msg("The fine powdery substance sifts through a "
	  + "hose with a WHOOSH while at the same time water "
	  + "drips in.\nClanking and banging noises can be heard as "
	  + "the two are mixed together.\n");
	find_gizmo(player)->reduce_water();
	alarm = set_alarm(4.0 + itof(random(5)), -1.0, 
				&gbake_msg(fruit, fritter, player, 5));
	STORE_BAKE_ALARM(player,alarm);
	return;   
    }
    if(call == 5)
    {
	tell_room(E(player), "A whistle blows.\n", player);
	player->catch_msg("A second whistle blows indicating that the "
	  + "GnomishAutomaticBatterCreamySmoothnessSensor initiates "
	  + "the final phase.\n");
	alarm = set_alarm(5.0, -1.0, &gbake_msg(fruit, fritter, player, 6));
	STORE_BAKE_ALARM(player,alarm);
	return;
    }
    if(call == 6)
    {
	tell_room(E(player), QCTNAME(player) + "'s gizmo makes GlubGlub.\n"
	  , player);
	player->catch_msg("GlubGlub.\nThe batter pours out of the bowl into "
	  + "the CentralCavitiy of the oven.\n");
	alarm = set_alarm(5.0, -1.0, &gbake_msg(fruit, fritter, player, 7));
	STORE_BAKE_ALARM(player,alarm);
	return;
    }
    if(call == 7)
    {
	player->catch_msg("A red light indicates commencing of the baking "
	  + "process.\n");
	i = random(7) + 3;
	alarm = set_alarm(50.0, -1.0, &smell_fritter(fritter, player, i, 0));
	STORE_BAKE_ALARM(player,alarm);
	return;
    }
}  

int
end_gbake(string str)
{
    string fruit;
    object fruit_obj;
    int amount;

    if(!(flag(10,0)))
    {
	NF("What?\n");
	return 0;
    }
    if(str != "baking")
    {
	NF("End what?\n");
	return 0;
    }
    if(!GET_BAKE_ALARM(TP))
    {
	NF("You aren't baking anything.\n");
	return 0;
    }
    remove_alarm(GET_BAKE_ALARM(TP));
    write("You shut down the MasterBakerFritter and ");
    if(fruit = TP->query_prop("_gnome_s_fruit_"))
    {
	if(fruit_obj = P(fruit, TP))
	{
	    amount = fruit_obj->num_heap();
	    amount ++;
	    fruit_obj->set_heap_size(amount);
	    write("retrieve your " + fruit + ".\n");
	    tell_room(E(TP), QCTNAME(TP) + " retrieves something from "
	      + HIS(TP) + " gizmo.\n", TP);
	    TP->remove_prop("_gnome_s_fruit_");
	    REMOVE_BAKE_ALARM(TP);
	    return 1;
	}
    }
    write("clean it thouroughly throwing away the sad remains of your "
      + TP->query_prop("_gnome_s_fruit_") + ".\n");
    say(QCTNAME(TP) + " does something to " + HIS(TP)
      + " gizmo and then cleans it thouroughly.\n");
    TP->remove_prop("_gnome_s_fruit_");
    REMOVE_BAKE_ALARM(TP);
    return 1;
}

int
gbake(string str)
{
    string result, name;
    object gizmo, fruit, fritter;
    int alarm, amount;

    if(!(flag(10,0)))
    {
	NF("You forgot to attach the MasterBakerFritter.\n");
	return 0;
    }
    if(!darkcheck(TP))
	return 1;
    result = steamengine_check(TP);
    if(result == "What?\n")
	result = "You'll need a steamengine first.\n";
    if(result != "ok")
    {
	write(result);
	return 1;
    }
    if(GET_BAKE_ALARM(TP))
    {
	NF("You're still baking something.\n");
	return 0;
    }
    if (!str)
    {
	NF("Gbake what?\n");
	return 0;
    }
    gizmo = find_gizmo(TP);
    if((gizmo->check_flour() < 1) || (!(fruit = P(str, TP))))
    {
	NF("You don't have the necessary ingredients for a " + str + "-fritter.\n");
	return 0;
    }
    if (member_array("/std/food.c", inherit_list(fruit)) == -1)
    {
	NF("You cannot gbake a " + str + ".\n");
	return 0;
    }
    if(gizmo->check_water() < 1)
    {
	NF("You'll need more water first.\n");
	return 0;
    }
    if(flag(10,1) == -1)
	return 1;
    write ("Ok.\nYou put a " + str + " into the opening of the funnel and "
      + "activate the MasterBakerFritter.\n");
    say(QCTNAME(TP) + " puts a " + str + " into " + HIS(TP) + " gizmo.\n");

    setuid();seteuid(getuid());
    fritter = clone_object(GOBJ + "fritter");
    fritter->set_fruit(fruit->query_name());
    fritter->set_amount(fruit->query_amount() * 2);
    name = fruit->query_name();

    if ((amount = fruit->num_heap()) > 1)
	fruit->set_heap_size(amount-1);
    else
	fruit->remove_object();
    alarm = set_alarm(5.0, -1.0, &gbake_msg(name, fritter, TP, 0));
    STORE_BAKE_ALARM(TP,alarm);
    TP->add_prop("_gnome_s_fruit_", str);
    return 1;
}

/******** Module: Cleaning tools for the ReusablePartsModule **************
 *                           flag:   8                                    *
 **************************************************************************/

/* Of course you may clean other things than the ReusablePartsModule
 * but you might well lose the Cleaning Tools in the progress.
 * This module doesn't break if used properly.
 */
void
other_clean(string how, string what)
{
    object ob;
    int i;
    string obj_name;

    what = L(what);
    if(!(ob = P(what, TP)))
    {        
	write(C(how) + " what?\n");
	return;
    }
    obj_name = ob->short();
    for(i=0;i<3;i++)     /* Chance of breaking 3 times as high */
    {
	if(flag(8,1) == -1)
	{
	    write("You start to " + how + " the " + obj_name 
	      + " but ");
	    if(how == "goil")
		write("the feather breaks.\n");
	    else
		write("the cleaning rag tears.\n");

	    write("The cleaning tools have been designed for more "
	      + "delicate purposes.\nAngrily, you dump the now "
	      + "incomplete and thus useless module.\n");
	    return;
	}
    }
    write("Carefully, you " + how + " the " + obj_name + ".\n");
    say(QCTNAME(TP) + " carefully " + how); 
    if(how == "polish") 
	say("e");
    say("s " + HIS(TP) + " " + obj_name + ".\n");
}

int
clean(string str)
{
    object rpm;
    string name;

    str = C(str);
    if(!(flag(8,0)))
    {
	NF("You forgot to attach this module.\n");
	return 0;
    }
    if(!(rpm = P("_reusable_parts_module_", TP)))
    {
	other_clean("clean", str);  /* Wants to clean something else */
	return 1;
    }
    if(str != (C(name = rpm->get_name())) && str != "Reusablepartsmodule"
      && str != "ReusablePartsModule")
    {             
	other_clean("clean", str);  /* Wants to clean something else */
	return 1;
    }
    if(name == "_rpm_")  /* ReusablePartsModule on set_no_show() */
    {
	NF("Clean what?\n");
	return 0;
    }

    write("You carefully clean your ");
    say(QCTNAME(TP) + " carefully cleans " + HIS(TP) + " ");
    if(name == "reusablepartsmodule")
    {     
	write("ReusablePartsModule");
	say("collection of parts");
    }
    else
	tell_room(E(TP), C(name));
    tell_room(E(TP), " inspecting each piece in turn.\n");
    rpm->reduce_wear_out();   
    return 1;
}

int
oil(string str)
{
    object rpm;
    string name;

    str = C(str);
    if(!(flag(8,0)))
    {
	NF("You forgot to attach this module.\n");
	return 0;
    }
    if(!(rpm = P("_reusable_parts_module_", TP)))
    {
	other_clean("goil", str);  /* Wants to oil something else */
	return 1;
    }
    if(str != (C(name = rpm->get_name())) && str != "Reusablepartsmodule"
      && str != "ReusablePartsModule")
    {             
	other_clean("goil", str);  /* Wants to oil something else */
	return 1;
    }
    if(name == "_rpm_")  /* ReusablePartsModule on set_no_show() */
    {
	NF("Oil what?\n");
	return 0;
    }

    write("You squirt some oil onto the feather, then dab it into your ");
    say(QCTNAME(TP) + " squits some oil onto a feather, then dabs it into a ");
    if(name == "reusablepartsmodule")
    {     
	write("ReusablePartsModule.\n");
	say("collection of parts.\n");
    }
    else
	tell_room(E(TP), C(name) + ".\n");
    rpm->reduce_wear_out();
    return 1;
}

int
polish(string str)
{
    object rpm;
    string name;

    str = C(str);
    if(!(flag(8,0)))
    {
	NF("You forgot to attach this module.\n");
	return 0;
    }
    if(!(rpm = P("_reusable_parts_module_", TP)))
    {
	other_clean("polish", str);  /* Wants to polish something else */
	return 1;
    }
    if(str != (C(name = rpm->get_name())) && str != "Reusablepartsmodule"
      && str != "ReusablePartsModule")
    {             
	other_clean("polish", str);  /* Wants to polish something else */
	return 1;
    }
    if(name == "_rpm_")  /* ReusablePartsModule on set_no_show() */
    {
	NF("Polish what?\n");
	return 0;
    }

    write("You meticulously polish your ");
    say(QCTNAME(TP) + " meticulously polishes " + HIS(TP) + " ");
    if(name == "reusablepartsmodule")
    {     
	write("ReusablePartsModule");
	say("collection of parts");
    }
    else
	tell_room(E(TP), C(name));
    tell_room(E(TP), " with a soft cleaning rag.\n");
    rpm->reduce_wear_out();
    return 1;
}

/************* Module: Flag with individual message ***********************
 *                           flag:   1                                    *
 **************************************************************************/
int
gflag(string name)
{
    object ob;
    object *wizards;

    if (!flag(1,0))
    {
	NF("You forgot to attach this module.\n");
	return 0;
    }
    if (!GFLAG_MESSAGE(TP))
    {
	NF("You haven't set a message yet.\n");
	return 0;
    }
    if (!name)
    {
	NF("You have a look at your flag.\nIt reads: " + GFLAG_MESSAGE(TP) + "\n");
	return 0;
    }
    if (!(ob = P(name, E(TP))))
    {
	NF("I cannot see " + name + " here.\n");
	return 0;
    }
    if (!living(ob))
    {
	NF("You want to quicktalk to a " + ob->short() + "?\n");
	return 0;
    }

    if(flag(1,1) == -1)
	return 1;
    if(C(name) == TP->query_name())
    {
	NF("You quicktalk to yourself. Feeling lonesome?\n");
	return 0;   
    }

    actor("You release the little flag to quicktalk to", ({ob})); 
    targetbb(" presses a button on " + HIS(TP) + " gizmo which then "
      + "sproings a little flag at you. There is "
      + "something written on the flag:\n"
      + GFLAG_MESSAGE(TP), ({ob}));
    tell_room(E(TP), QCTNAME(TP) + " quicktalks to " + QTNAME(ob) + " by "
      + "producing a little flag.\n", ({ob, TP}));

    wizards = FILTER_IS_WIZARD(all_inventory(environment(this_player()))) -
        ({ this_player(), ob });
    wizards->catch_tell("As wizard, you read: " + GFLAG_MESSAGE(TP) + "\n");

    return 1;
}

int
set_message(string str)
{
    if (!flag(1,0))
	return 0;

    if (!str)
    {
	NF("Inscribe what message?\n");
	return 0;
    }
    if(!darkcheck(TP))
	return 1;
    if (GFLAG_MESSAGE(TP))
	write("You erase the old inscription and write down the new one.\n");
    else
	write("You inscribe your message onto the little flag.\n");
    say(QCTNAME(TP) + " does something to " + HIS(TP) + " gizmo.\n");
    SET_GFLAG_MESSAGE(TP,str);
    return 1;
}

/********************* glint *********************************************/

int
glint(string str)
{
    object *target;

    if(!str)
    {
	write("A nasty gleam appears in your eyes.\n");
	tell_room(E(TP), "A nasty gleam appears in " + QTNAME(TP)
	  + "'s eyes and you wonder what " + HE(TP) + " might "
	  + "be thinking.\n", TP);
	return 1;
    }
    if(C(str) == TP->query_name() || str == "me")
    {
	NF("You try to glint at yourself but fail.\n");
	return 0;
    }
    if(!(sizeof(target = get_target(str))))
    {
	NF("You don't see " + str + " here.\n");
	return 0;
    }
    if(living(target[0]))
    {
	actor("You look at", target, " with a nasty gleam "
	  + "in your eyes.");
	targetbb(" looks at you with a nasty "
	  + "gleam in " + HIS(TP) + " eyes.", target);
	all2actbb(" looks at", target, " with a nasty gleam in "
	  + HIS(TP) + " eyes.");
	return 1;
    }
    write("You look at the " + target[0]->query_adj() + " "
      + target[0]->query_name() + " with a nasty gleam "
      + "in your eyes.\n");
    tell_room(E(TP), QCTNAME(TP) + " looks at the " + target[0]->query_adj()
      + " " + target[0]->query_name() + " with a nasty gleam "
      + "in " + HIS(TP) + " eyes.\n");
    return 1;
}

/********************* gmarvel *******************************************/

int
gmarvel(string str)
{

    if (!str)
    {
	write("You marvel at the wonder of it all!\n");
	SAY(" is in awe of such a marvellous idea!");
	return 1;
    }
    if (str == "gnome" || str == "gnomes")
    {
	write("You marvel at the intelligence of your fellow "
	  + "gnomes.\n");
	SAY(" marvels at the amazing intelligence of " 
	  + HIS(TP) + " fellow gnomes.\n");
	return 1;
    }
    if (str == "dwarf" || str == "dwarves")
    {
	write("You can't help but laugh at the greed of these silly "
	  + "dwarves.\n");
	SAY(" shakes " + HIS(TP) + " head in disbelief at the greed "
	  + "of dwarves.\n");
	return 1;
    }
    if (str == "elf" || str == "elves")
    {
	write("Ha! Elves think they know everything. How wrong they are!\n");
	SAY(" can't understand why elves think they know everything. How wrong they are!\n");
	return 1;
    }
    if (str == "goblin" || str == "goblins")
    {
	write("Whoever heard of a smart goblin?\n");
	SAY(" smiles sympathetically at the stupidity of most "
	  + "goblins.\n");
	return 1;
    }
    if (str == "human" || str == "humans")
    {
	write("I guess bigger doesn't mean brainier in this case "
	  + "anyway.\n");
	SAY(" wonders if the size of some humans is proportionate "
	  + "to their stupidity!\n");
	return 1;
    }
    if (str == "hobbit" || str == "hobbits")
    {
	write("Ye gods! Are these hobbits really as stupid as they "
	  + "look!\n");
	SAY(" sighs in exasperation at the lack of intelligence to "
	  + "be found in the average hobbit.");
	return 1;
    }
    if (str == "half-elf" || str == "half-elves")
    {
	write("Oh dear! Are half-elves really as dense as they look?\n");
	SAY(" ponders the density of half-elves.\n");
	return 1;
    }
    if (str == "kender" || str == "kenders")
    {
	write("Oh My! Are kenders really as forgetful as they seem?\n");
	SAY(" speculates at the absentminded forgetfulness of kenders.\n");
	return 1;
    }
    if (str == "hobgoblin" || str == "hobgoblins")
    {
	write("Yikes! Intelligence in hobgoblins is nonexistent!\n");
	SAY(" groans at the nonexistent intelligence in hobgoblins!\n");
	return 1;
    }
    NF("Which race?\n");
    return 0;
}

/********************* gnlist ********************************************/

int
gnlist(string str)
{       
    object *players;
    int i;

    players = users();
    write("The following Inventors are currently logged on:\n");
    for (i = 0; i < sizeof(players); i++)
    {
	if (players[i]->query_guild_name_race() == GNOME_NAME && 
	  extract(players[i]->query_name(), -2) != "jr")
	    write(": " + players[i]->query_name() + " the " +
	      players[i]->query_guild_title_race() + "\n");
    }
    return 1;
}

/********************** module: Gesturemaker ******************************
 *                        flag: 9                                         *
 **************************************************************************/

/* Various general checks specific to the GestureMatic.
 * Returns:     "Ok"     (Nothing's wrong)
 *              The fail string
 */

string
check_gest()
{
    if(!flag(9,0))
    {    
	return "What?\n";
    }
    if(!QUERY_OPERATIONAL(TP))
    {    
	return "Your GestureMatic isn't operational.\n";
    }
    if(random(5 + ((TP->query_stat(1)) / 10)) == 0) /* Check for entangling */
    {
	SET_ENTANGLED(TP);
	TP->remove_subloc(GEST_SUB);
	TP->add_subloc(GEST_SUB_ENT, TO);
	return "You have been completely tangled up in the wires and "
	+ "levers of your GestureMatic. Better unentangle it and "
	+ "try again...\n";
    }
    if(QUERY_ENTANGLED(TP))
    {
	return "You are still entangled in the GestureMatic.\n";
    }
    return "Ok";
}

/* Finished with pointing etc? Fold it again!
 */

int
fold(string str)
{
    if(!flag(9,0))
	return 0;
    if(str != "gesturematic")
    {
	NF("Fold what?\n");
	return 0;
    }
    if(!QUERY_OPERATIONAL(TP))
    {
	NF("The GestureMatic is already folded.\n");
	return 0;
    }
    if(QUERY_ENTANGLED(TP))
    {
	NF("You are still entangled in the GestureMatic.\n");
	return 0;
    }
    if(!darkcheck(TP))
	return 1;

    write("You repack the GestureMatic for convenient transport.\n");
    allbb(" pulls a lever and the giant mechanical arm folds back into "
      + HIS(TP) + " gizmo.");
    UNSET_OPERATIONAL(TP);
    P("_g_stopper_", TP)->remove_object();
    TP->remove_subloc(GEST_SUB);
    return 1;
}

/* Unfold the GestureMatic to ready it for action
 */

int
unfold(string str)
{
    if(!flag(9,0))
	return 0;
    if(str != "gesturematic")
    {
	NF("Unfold what?\n");
	return 0;
    }
    if(!darkcheck(TP))
	return 1;
    if(TP->query_attack())
    {
	NF("You are busy fighting.\n");
	return 0;
    }
    if(QUERY_OPERATIONAL(TP))
    {
	NF("The GestureMatic is already operational.\n");
	return 0;
    }

    write("You unfold the GestureMatic for use.\n");
    allbb(" does something to " + HIS(TP)
      + " gizmo and a giant mechanical arm begins to unfold.");
    SET_OPERATIONAL(TP, 1);
    TP->add_subloc(GEST_SUB, this_object());
    setuid();seteuid(getuid());
    clone_object(GOBJ + "stopper")->move(TP);
    return 1;
}

/* Once entangled, unentangle the GestureMatic!
 */

void
rem_entangle(object player)
{
    tell_room(E(player), QCTNAME(player) + " finished unentangling "
      + HIS(player) + " mechanical arm", player);
    if(flag(9,1) == -1)
    {     
	player->catch_msg(" You finished unentangling your mechanical arm "
	  + "destroying it in the process.\n");
	tell_room(E(player), ", but somehow seems unhappy.\n"
	  + HE(player) + " drops something.\n", player);
	UNSET_OPERATIONAL(player);
	P("_g_stopper_", player)->remove_object();
	setuid();seteuid(getuid());
	clone_object(GOBJ + "junk")->move(E(player));
    }
    else
    {     
	player->catch_msg("Your GestureMatic is operational again.\n");   
	tell_room(E(player), " and smiles happily.\n", player);
	player->add_subloc(GEST_SUB, TO);
    }
    REMOVE_ENTANGLED(player);
    player->remove_subloc(GEST_SUB_ENT);
}

int
unentangle(string str)
{
    int time;

    if(!(flag(9,0)))
	return 0;
	
    if(str != "gesturematic")
    {
	NF("Unentangle what?\n");
	return 0;
    }
    if(!QUERY_ENTANGLED(TP))
    {
	if(!(QUERY_OPERATIONAL(TP)))
	{
	    NF("The GestureMatic is neither operational nor entangled.\n");
	}
	else
	{
	    NF("The GestureMatic is not entangled.\n");
	}
	return 0;
    }
    if(!darkcheck(TP))
	return 1;

    write("You sit down and start to unentangle the crossed wires.\n");
    allbb(" sits down and starts to unentangle " + HIS(TP) + 
		" useless mechanical arm.");
    time = 15 - ((TP->query_stat(1)) / 10) + random(10);
    paralyze_player(TP, "You are entangled into the wires of " +
		    "your GestureMatic.\n", "", time);
    set_alarm(itof(time), -1.0, &rem_entangle(TP));
    return 1;
}

int
gpoint(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
	NF(check);
	return 0;
    }

    if(str == "west" || str == "southwest" || str == "south" || 
      str == "southeast" || str == "east" || str == "northeast" || 
      str == "north" || str == "northwest" || str == "up" ||
      str == "down")
    {
	write("You point " + str + " with your GestureMatic.\n");
	tell_room(E(TP), QCTNAME(TP) + " fiddles with " + HIS(TP) 
	  + " gizmo and suddenly the giant mechanical hand is "
	  + "pointing " + str + ".\n", TP);
	return 1;
    }
    who = get_target(str);   
    if(!(sizeof(who)))
    {
	NF("Gpoint at whom?\n");
	return 0;
    }
    targetbb(" fiddles with " + HIS(TP) + " gizmo and suddenly "
      + "the giant mechanical hand is pointing at you.", who);
    actor("You point at", who, " with your GestureMatic.");
    all2actbb(" fiddles with " + HIS(TP) + " gizmo and suddenly "
      + "the giant mechanical hand is pointing at", who, "."); 
    return 1;
}


int
gwave(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
	NF(check);
	return 0;
    }

    if(!str)
    {
	write("You pull the GestureMatic back and forth, waving happily.\n");
	tell_room(E(TP), QCTNAME(TP) + " fiddles a bit with some levers and "
	  + "the giant mechanical hand waves happily.\n", TP);
	return 1;
    }

    who = get_target(str);
    if(!(sizeof(who)))
    {
	NF("Gwave whom?\n");
	return 0;
    }
    actor("You pull the GestureMatic back and forth, waving at", who, ".");
    targetbb(" fiddles a bit with some levers and the giant mechanical "
      + "hand waves at you.", who);
    all2actbb(" fiddles a bit with some levers and the giant mechanical "
      + " hand waves at", who, ".");
    return 1;
}

int
gpoke(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
	NF(check);
	return 0;
    }

    who = get_target(str);   
    if(!(sizeof(who)))
    {
	NF("Gpoke whom?\n");
	return 0;
    }
    actor("You wheel your GestureMatic around and poke", who, " in the "
      + "ribs.");
    target(" wheels around abruptly and pokes you in the ribs "
      + "with " + HIS(TP) + " giant mechanical hand.", who);
    all2actbb(" suddenly pokes", who, " in the ribs with "
      + HIS(TP) + " giant mechanical hand.");
    return 1;
}

int
gslap(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
	NF(check);
	return 0;
    }

    who = get_target(str);   
    if(!(sizeof(who)))
    {
	NF("Gslap whom?\n");
	return 0;
    }
    actor("Suddenly provoked, you yank at the control levers to make "
      + "the GestureMatic slap", who, " hard in the face, "
      + "creating some nasty welts.");
    target(" suddenly looks ticked. " + C(HE(TP)) + " fiddles with "
      + HIS(TP) + " gizmo, and the giant mechanical hand "
      + "blindsides you, slapping you in the face and stunning you "
      + "for a moment.", who);
    all2actbb(" gets an angry look and backhands", who, " with "
      + HIS(TP) + " giant mechanical hand.");
    return 1;
}


int
gfinger(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
	NF(check);
	return 0;
    }

    who = get_target(str);   
    if(!(sizeof(who)))
    {
	NF("Gfinger whom?\n");
	return 0;
    }
    actor("You pull at the control levers closing the GestureMatic "
      + "except for one finger, directing it at", who, ".");
    targetbb(" fiddles with " + HIS(TP) + " gizmo and you find "
      + "yourself face to face with a long, steel finger. Can you "
      + "guess which one?", who);
    all2actbb(" gives", who, " the finger with " + HIS(TP)
      + " giant mechanical hand.");
    return 1;
}

int
gscratch(string str)
{
    string check;

    if((check = check_gest()) != "Ok")
    {    
	NF(check);
	return 0;
    }

    write("You scratch your head with your GestureMatic.\n");
    tell_room(E(TP), QCTNAME(TP) + " pulls at a lever, and " + HIS(TP)
      + " giant mechanical hand scratches thoughtfully at " + HIS(TP)
      + " gnomish noggin.\n", TP);
    return 1;
}

int
ggesture(string str)
{
    string check;

    if((check = check_gest()) != "Ok")
    {    
	NF(check);
	return 0;
    }

    write("You try to show your point with the GestureMatic.\n");
    tell_room(E(TP), QCTNAME(TP) + " flails " + HIS(TP)
      + " mechanical hand around emphatically, apparently trying to "
      + "tell you something.\n", TP);
    return 1;
}


/******************gsay****************************************************/

int
gsay(string str)
{
    return "/d/Genesis/cmd/soul_cmd_gnome"->rsay(str);
}


/********************* gsmile ********************************************/

int
gsmile(string str)
{
    object *target;

    if(!str)
    {
	write("You smile gnomishly.\n");
	allbb(" smiles gnomishly.");
	return 1;
    }
    if((C(str) == TP->query_name()) || (str == "me"))
    {
	write("You gnomishly smile to yourself.\n");
	allbb(" gnomishly smiles to " + HIM(TP) + "self.");
	return 1;
    }
    target = get_target(str);
    if(!sizeof(target))
    {
	NF("Gsmile at whom?\n");
	return 0;
    }
    if(!living(target[0]))
    {
	write("You gnomishly smile at the " + target[0]->query_adj()
	  + " " + target[0]->query_name() + ".\n");
	tell_room(E(TP), QCTNAME(TP) + " gnomishly smiles at the "
	  + target[0]->query_adj() + " "
	  + target[0]->query_name() + ".\n", TP);
	return 1;
    }
    actor("You smile at", target, ", gnomishly.");
    targetbb(" smiles at you, rather gnomishly.", target);
    all2actbb(" smiles at", target, ", rather gnomishly.");
    return 1;
}


/********************* gthink ********************************************/

int
gthink()
{
    write("You think hard for a solution to the problem...\n");
    allbb(" screws " + HIS(TP) + " face up and appears "
      + "to be deep in thought.");
    return 1;
}


/********************* gtinker *******************************************/

int 
gtinker(string str)
{
    object *ob;

    if (!str)
    {
	write("You must say which object to tinker with.\n");
	return 1;
    }
    if(!darkcheck(TP))
	return 1;

    ob = get_target(str);
    if(sizeof(ob))
    {
	if (!living(ob[0]))
	{
	    write("You tinker away at the " 
	      + ob[0]->short() + " with your gizmo.\n");
	    SAY(" gets out a weird device and starts tinkering "
	      + "with the " + ob[0]->short() + ".");
	    return 1;
	}
	actor("You start looking for ways to improve", ob, ".");
	all2actbb(" looks at", ob, " strangely, as if eyeing "
	  + HIM(ob[0]) + " up for some devilish experiment.");
	targetbb(" looks at you strangely, "
	  + "as if eyeing you up for some devilish "
	  + "experiment.", ob);
	return 1;
    }
    NF("I can't see " + str + " here.\n");
    return 0;
}

/********************* help *************************************************/

int
help(string str)
{
    string subject, filename;

    if (!str)
	return 0;

    if (str == "gnomes")
    {
	write("Try 'help gnomes topics' for an overview.\n");
	return 1;
    }
    if (sscanf(str, "gnomes %s", subject) != 1)
	return 0;

    filename = HELP_DIR + subject;
    if (file_size(filename) > 0)
    {
	write("\n");
	setuid();
	seteuid(getuid());
	cat(filename);
	write("\n");
	return 1;
    }

    NF("No help on that subject I'm afraid. You might want to try:\n"
      + "help gnomes topics.\n");
    return 0;
}
/********************* module: coffeemaker ********************************
 *                     flag:   5                                          *
 **************************************************************************/

void
coffee_msg(object player)
{
    int a;
    string *msg = ({"You hear nothing ..", "The coffeemaker rumbles "
      + "dangerously", "The whole gizmo shakes fiercely", "A valve opens "
      + "and releases a cloud of steam", "Something rattles noisily inside "
      + "the gizmo", "A smelly brownish liquid drips from your gizmo",
      "The coffeemaker creates a buzzing sound"}) 
    , *telr = ({"", "Something rumbles dangerously.\n", 
      QCTNAME(player) + "'s gizmo shakes fiercely.\n"
      , QCTNAME(player) + " releases a cloud of steam.\n"
      , QCTNAME(player) + "'s gizmo rattles noisily.\n", QCTNAME(player) 
      + " produces a smelly brownish liquid which drops to the floor.\n"
      , "You hear a buzzing sound.\n"});

    a = random(sizeof(msg));
    player->catch_msg(msg[a] + ".\n");
    tell_room(E(player), telr[a] , player);
}

void
coffee_2(object player, int coffee_alarm)
{
    remove_alarm(coffee_alarm);
    find_gizmo(player)->reduce_water();
    if (!random(5))
    {     
	player->catch_msg("A stream of hot cappuccino splashes into the "
	  + "dispensing chamber. Then a cup arrives. Frustrated you "
	  + "recycle the cup.\n");
	if(!random(5))
	    player->catch_msg("You make a note you want to hand to "
	      + "the responsible committee on next occasion.\n");
	tell_room(E(player), QCTNAME(player) + " receives some hot cappuccino, "
	  + "then a cup.\n", player);
	return;
    }
    player->catch_msg("A cup appears in the dispensing slot which is "
      + "rapidly filling with delicious hot cappuccino.\nYou eagerly "
      + "take the cup.\n"); 
    tell_room(E(player), QCTNAME(player) + " receives a cup of hot cappuccino.\n", player);
    setuid();seteuid(getuid());
    clone_object(FOOD + "coffee.c")->move(player);
}

int
makecoffee(string str)
{
    int coffee_alarm;
    string result;

    if(!flag(6,0))
    {
	NF("You forgot to attach that module.\n");;
	return 0;
    }
    if(!darkcheck(TP))
	return 1;

    result = steamengine_check(TP);
    if(result == "What?\n")
	result = "You'll need a steamengine first.\n";
    if(result != "ok")
    {
	write(result);
	return 1;
    }
    if(flag(6,1) == -1)
	return 1;

    write("You press the button requesting a CupOfHotCappuccino "
      + "and wait ...\n");
    tell_room(E(TP), QCTNAME(TP) + " does something to " + HIS(TP) 
      + " gizmo but nothing seems to happen ... yet.\n", TP);
    coffee_alarm = set_alarm(5.0, 5.0, &coffee_msg(TP));
    set_alarm(26.0, -1.0, &coffee_2(TP, coffee_alarm));
    return 1;
}

/********************* module: measure ************************************
 *                     flag:   5                                          *
 **************************************************************************/

string
measure_2(object target, string str)
{
    string sht;
    if(living(target))
	return QTNAME(target) + ".\n";
    if(strlen(sht = (target->short())) == 0)
	sht = str;
    return "the " + sht + ".\n";
}

int
measure(string str)
{
    object target, *oblist;
    int toflag = 0;

    if (!flag(5,0))
    {
	NF("You forgot to attach that module.\n");;
	return 0;
    }
    if(!darkcheck(TP))
	return 1;

    if (!str)
    {
	NF("Measure what?\n");
	return 0;
    }
    if (str[0..2] == "to ")
    {
	toflag = 1;
	str = str[3..];
    }

    oblist = FIND_STR_IN_OBJECT(str,E(TP));
    if (!oblist || !sizeof(oblist))
    {
	NF("Measure to what?\n");
	return 0;
    }

    if(flag(5,1) == -1) /* Break test */
	return 1;

    target = oblist[0];
    if (!toflag)
    {
	if(target == TP)
	{
	    NF("You don't bother with the tape. You know your size.\n");
	    return 0;
	}
	TP->catch_msg("You get out your convenient measure tape and "
	  + "measure the size of " + measure_2(target, str)
	  + "You calculate the volume to be about " +
	  (target->appraise_volume(50 + TP->query_skill(SS_BUILD) / 2)) +
	  ".\n");
	tell_room(E(TP), QCTNAME(TP) + " gets out a "
	  + "measure tape and quickly measures the size "
	  + "of " + measure_2(target, str), ({TP,target}));
	if(living(target))
	    target->catch_msg(QCTNAME(TP) + " gets out a "
	      + "measure tape and quickly measures your size.\n");
	return 1;
    }
    else
    {
	if(target == TP)
	{
	    NF("The distance between you and you is zero.\n");
	    return 0;
	}
	TP->catch_msg("You get out your convenient measure tape and "
	  + "measure the distance to " + measure_2(target, str));
	tell_room(E(TP), QCTNAME(TP) + " gets out a "
	  + "measure tape and quickly measures the distance between "
	  + HIM(TP) + " and " + measure_2(target, str), ({TP, target}));
	if(living(target))
	    target->catch_msg(QCTNAME(TP) + " gets out a measure "
	      + "tape and quickly measures the distance between you "
	      + "and " + HIM(TP) + ".\n");
	return 1;
    }
    NF("Measure what?\n");
    return 0;
}

/********************* no *************************************************/

int
no()
{
    write("You shake your head firmly and begin to explain...\n");
    all(" shakes " + HIS(TP) + " head firmly "
      + "and begins to explain...");
    return 1;
}

/********************* philosophy *****************************************/

int
philosophy()
{
    write("You think about the universe as such and soon come up with "
      + "a completely new theory.\n");
    all(" pauses to think about the mysteries of the universe, "
      + "and soon comes up with an entirly new theory.");
    return 1;
}

/********************************* module: idea light *********************
 *                                   flag: 0
 **************************************************************************/

void
outout(object player)
{
    player->catch_msg("The light flickers and goes out.\n");
    tell_room(E(player), QCTNAME(player) + "'s light flickers and goes "
      + "out.\n", player);
    find_gizmo(player)->add_prop(OBJ_I_LIGHT, 0);
    SET_IDEALIGHT_ON(player,0);
}

int
idea_light()
{
    if (!flag(0,0))
    {
	NF("You forgot to attach that module.\n");;
	return 0;
    }
    if(IDEALIGHT_ON(TP))
    {
	NF("You're already having a fantastic idea.\n");
	return 0;
    }
    if(!random(10))       /* Fewer break-tests */  
	if(flag(0,1) == -1)
	    return 1;

    write("You switch on your idea light to indicate a fantastic idea.\n");
    all(" switches on a tiny light to indicate that "
      + HE(TP) + " has a great idea.");
    find_gizmo(TP)->add_prop(OBJ_I_LIGHT, 1);
    set_alarm(itof(4+random(6)+TP->query_skill(SS_BUILD)/6), -1.0, &outout(TP));
    SET_IDEALIGHT_ON(TP,1);
    return 1;
}


/******************************* module: water dispenser ******************
 *                                 flag: 2
 **************************************************************************/

void
do_refresh(object player, int amount)
{
    if ((player->query_fatigue()) > ((player->query_max_fatigue()) - amount))
	player->set_fatigue(player->query_max_fatigue());
    else
	player->add_fatigue(amount);
}

int
refresh(string str)
{
    int number;
    object target, *oblist;

    if (!flag(2,0))
    {
	NF("You forgot to attach that module.\n");;
	return 0;
    }
    if(!darkcheck(TP))
	return 1;

    if(!find_gizmo(TP)->check_water())
    {
	NF("You don't have much water left.\n");
	return 0;
    }
    if (!str)
    {
	NF("Refresh whom?\n");
	return 0;
    }
    if(flag(2,1) == -1)
	return 1;

    write("You release a splash of water ");
    tell_room(E(TP), "A splash of water spurts forth out of " + QTNAME(TP)
      + "'s gizmo", TP);
    find_gizmo(TP)->reduce_water();

    str = L(str);
    number = random(5);
    if (str == "me" || str == "myself" || str == L(TP->query_name()))
    {
	if ((TP->query_stat(1)) >= (random(40) + 10) && number)
	{
	    write("and skillfully catch it with your mouth.\n");
	    say(", which " + HE(TP) + " skillfully directs into "
	      + HIS(TP) + " mouth.\n");
	    do_refresh(TP, 20);
	}
	else
	{
	    write("which misses your mouth but hits your nose!\nYou feel refreshed "
	      + "though.\n");
	    say(" and hits " + HIM(TP) + "self in the face.\n");
	    do_refresh(TP, 40);
	}
	return 1;
    }

    if(!number)
    {     
	write("but somehow manage to miss your mouth and hit your nose!\n"
	  + "You feel quite refreshed.\n");
	say(" aims carefully at " + HIS(TP) + " mouth but hits " 
	  + "the nose.\n");
	TP->command("$oops");
	do_refresh(TP, 40);       
	return 1;              
    }

    target = present(str, E(TP));
    if (!target)
    {
	write("but cannot find your target.\n");
	say(".\n");
	return 1;
    }

    if (!living(target))
    {
	write("and soak the " + target->short() + ".\n");
	say(" soaking the " + target->short() + ".\n");
	return 1;
    }

    oblist = ({target, TP});
    if ((target->query_stat(1)) >= (random(140) + 20))
    {
	TP->catch_msg("and refresh " + QTNAME(target) + ".\n");
	tell_room(E(target), " which " + target->query_the_name(target) + " skillfully "
	  + "catches with " + HIS(target) + " mouth.\n"
	  ,oblist);
	target->catch_msg(" which you skillfully catch with your mouth.\n"
	  + "You feel refreshed.\n");
	do_refresh(target, 20);
	return 1;
    }
    TP->catch_msg("and shower " + QTNAME(target) + ".\n");
    tell_room(E(TP), " hitting " + QTNAME(target) + " between the eyes.\n"
      ,oblist);
    target->catch_msg(" hitting you between the eyes!\nYou feel very refreshed.\n");
    do_refresh(target, 40);
    return 1;
}

/********************** module: Recycler **********************************
 *                        flag: 7                                         *
 **************************************************************************/

int
recycle(string str)
{
    int a, i, *count_in, *wep_loc, *arm_loc;
    object *obs, ob, reus;   
    string name;

    count_in = ({0,1,2,3,4});
    arm_loc = ({2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,
      32768,65536});
    wep_loc = ({512,1024,2048,4096,384}); 
    if(!flag(7,0))
    {
	NF("You forgot to attach that module.\n");;
	return 0;
    }
    if (!darkcheck(TP))
	return 1;

    if(!str)
    {
        NF("Recycle what?\n");
        return 0;
    }
    
    parse_command(str, ({ }), "[the] / [a] / [an] %s", str);
    
    if (!sizeof(obs = FIND_STR_IN_OBJECT(str, this_player())))
    {
        notify_fail("You do not hold " + LANG_ART(str) + " " + str + ".\n");
        return 0;
    }
    
    ob = obs[0];
    
    if(reus = P("_reusable_parts_module_", TP))
    {
	name = reus->get_name();
	if(name != "_rpm_")
	{
	    NF("You already own a " + C(name) + ". Why do you need two?\n");
	    return 0;
	}
    }
    if((ob->query_prop(OBJ_M_NO_DROP)) || (ob->query_prop(OBJ_M_NO_GIVE)) ||
      (ob->query_prop(MAGIC_AM_MAGIC)))
    {
	NF("You cannot recycle that.\n");
	return 0;
    }
    if(ob->query_name() == "coin")
    {
	NF("Coins don't give a lot material. It's better if you kept it.\n");
	return 0;
    }
    for(i=0;i<16;i++)
	if(TP->query_armour(arm_loc[i]) == ob)
	{
	    NF("You cannot recycle worn or wielded objects.\n");
	    return 0;
	}
    for(i=0;i<5;i++)
	if(TP->query_weapon(wep_loc[i]) == ob)
	{
	    NF("You cannot recycle wielded objects.\n");
	    return 0;
	}
    if(QUERY_CALL(TP) != 0)
    {
	NF("You are already recycling something.\n");
	return 0;
    }
    if(flag(7,1) == -1)
	return 1;       /* Break test */

    ob->add_prop(OBJ_I_NO_DROP, 1);
    ob->set_no_show();
    ob->add_prop("_obj_i_recycling", 1);
    write("You put the " + ob->short() + " into the "
      + "recycling chamber of the "
      + "gizmo and pull the lever...\nA bell rings and the shutter "
      + "closes the chamber.\n");
    say(QCTNAME(TP) + " does something to " + HIS(TP) 
      + " gizmo causing a bell to ring alarmingly.\n");

    /* Lets get a random order for the messages. */

    for(i=0;i<3;i++)
    {     
	a = random(sizeof(count_in));
	if(count_in[a] != -1)   
	{        
	    TP->add_prop("_recycler_msg_nr_" + i, count_in[a]);
	    count_in[a] = -1;
	}
	else
	    i--;
    }
    SET_CALL(TP, 1);
    return 1;
}

/* We want to know which materials were recycled.
 * add_material() stores the information in reus_par.c
 */
string        
compare_material(string adject)
{
    string *mats = ({"wood", "copper", "metal", "silver", "gold", "bronze",
      "lead", "rust", "leather", "mithril", "adamant", "steel", "iron"});
    int i;

    for(i=0;i<sizeof(mats);i++)
    {
	if((adject == mats[i]) || (adject == mats[i] + "en") || 
	  (adject == mats[i] + "y") || (adject == mats[i] + "n"))
	    return mats[i];
	if(adject == "metallic")
	    return "metal";
	if(adject == "furry")
	    return "fur";
    }
    return "none";
}

void
get_material(mixed adject, object rpm)
{
    mixed result;
    int i;

    if(stringp(adject))
    {
	if((result = compare_material(adject)) != "none")
	    rpm->add_material(result);
	return;
    }
    for(i=0;i<sizeof(adject);i++)
    {   
	if((result = compare_material(adject[i])) != "none")
	    rpm->add_material(result);
    }
}

void
end_recycle(object player)
{
    object rpmod, *inv, ob;
    int i;

    SET_CALL(player, 0);
    if(!(rpmod = present("_reusable_parts_module_", player)))
    {
	setuid(); seteuid(getuid());
	rpmod = clone_object(GOBJ + "reus_par");
	rpmod->move(player);
    }

    inv = all_inventory(player);
    for(i=0;i<sizeof(inv);i++)
	if(inv[i]->query_prop("_obj_i_recycling"))
	    ob = inv[i];

    rpmod->add_prop(OBJ_I_WEIGHT, (rpmod->query_prop(OBJ_I_WEIGHT)) 
      + (ob->query_prop(OBJ_I_WEIGHT))/2);
    rpmod->add_volume((ob->query_prop(OBJ_I_VOLUME))/50);
    get_material(ob->query_adj(), rpmod);
    get_material(explode((ob->short()), " "), rpmod);
    rpmod->check_complete(player);
    ob->remove_object();
    player->catch_msg("You are ready to recycle again.\n");
}

int
recycle_2(string str)                         
{
    string *msg = ({"your gizmo produces a contented 'BURP'.\n", "hear "
      + "a loud 'CRUNCH'.\n", "hear a noisy 'MUNCH ... MUNCH ... MUNCH'.\n" 
      ,"a light blinks indicating that something has just been considerably "
      + "reduced in size.\n"
      ,"the Recycler spits some unusable tiny pieces to the ground.\n"})

    ,*tel_msg = ({" and something makes 'BURP'.\n", " and something makes " +
      "'CRUNCH'.\n", " and something makes 'MUNCH ... MUNCH ... MUNCH'.\n",
      ".\n", ".\n"})
    , *often = ({"second", "third", "last"});
    int call, msg_nr;

    /* We are using the same syntax for the PersonalCleanlinessModule */
    if(QUERY_WASH(TP) > 0)
    {
	NF("Pull what?\n");	
	return wash_me(str);
    }

    if(!flag(7,0))
    {
        NF("You forgot to attach that module.\n");
        return 0;
    }
    
    if(str != "lever")
    {
        NF("Pull what?\n");   
        return 0;
    }

    call = QUERY_CALL(TP);
    if(call < 1 || call > 3)
    {
        NF("The lever of the Recycler is blocked.\n");
        return 0;
    }
    msg_nr = TP->query_prop("_recycler_msg_nr_" + (call - 1));
    TP->remove_prop("_recycler_msg_nr_" + (call - 1));
    TP->catch_msg("You pull the lever for a " + often[call - 1] + " time and "
      + msg[msg_nr]);
    tell_room(E(TP), QCTNAME(TP) + " does something to " + HIS(TP)
      + " gizmo" + tel_msg[msg_nr], TP);

    if(call == 3)
    set_alarm(4.0, -1.0, &end_recycle(TP));
    SET_CALL(TP, call + 1);
    return 1;
}
int
pull(string str)
{
    if (!strlen(str))
        return 0;
    
    if (str == "lever")
        this_player()->catch_msg("It dawns upon you that the new pull " +
        "command for modules is 'gpull'.\n" +
        "You looking around for another lever to pull.\n");
    
    return 0;
}

/* Nobody wants to get rid of a half complete ReusablePartsModule
 * But anyway...
 */

void
flush_2(object rpm, object player)
{
    object junk;

    player->catch_msg("There is a sound like water running down a "   
      + "drain and the recycler ejects something in a splash of "
      + "water.\n");
    tell_room(E(player), "There is a sound like water running down "
      + "a drain and something falls from " + QTNAME(player)
      + " in a splash of water.\n", player);

    setuid();seteuid(getuid());
    junk = clone_object(GOBJ + "junk");
    junk->add_adj("wet");
    junk->set_short("wet gnomish junk");
    junk->set_long("This is a huge junk of different materials with "
      + "no recognisable purpose or design. I guess only a gnome "
      + "could have produced that.\nIt's very wet.\n");
    junk->add_prop(OBJ_I_WEIGHT, rpm->query_prop(OBJ_I_WEIGHT));
    junk->add_prop(OBJ_I_VOLUME, rpm->query_prop(OBJ_I_VOLUME));
    junk->move(E(player));

    rpm->remove_object();
}

int
flush(string str)
{
    object rpm, gizmo;

    if(!flag(7,0))
    {
	NF("You forgot to attach that module.\n");;
	return 0;
    }
    if(str != "recycler")
    {
	NF("Flush what?\n");
	return 0;
    }
    if(!(rpm = P("_rpm_", TP)))
    {
	NF("There is nothing inside the recycler. Yet...\n");
	return 0;
    }
    if(!flag(2,0))
    {
	NF("You'll need a waterdispenser to flush the recycler.\n");
	return 0;
    }
    gizmo = find_gizmo(TP);
    if(gizmo->check_water() < 1)
    {
	NF("Your waterdispenser is empty.\n");
	return 0;
    }
    gizmo->reduce_water();
    write("You pull the handle.\n");
    say(QCTNAME(TP) + " does something to " + HIS(TP) + " gizmo.\n");
    set_alarm(3.0, -1.0, &flush_2(rpm, TP));
    return 1;
}

/********************** module: Steam engine ******************************
 *                        flag: 3                                         *
 **************************************************************************/

int
check(string str)
{
    int res;

    if(str == "distillationapparatus" || str == "Distillationapparatus" ||
      str == "DistillationApparatus")
    {
	if (!darkcheck(TP))
	    return 1;
	if(!(flag(12,0)))
	{
	    NF("You forgot to attach that module.\n");;
	    return 0;
	}
	write("The CentralCavityContainingLiquidsToBeDistilled is ");
	res = QUERY_LIQUID(TP);
	if(res == 3000) write("full.\n");
	if(res > 2300 && res != 3000) write("well filled.\n"); 
	if(res > 1500 && res <= 2300) write("about half full.\n"); 
	if(res > 700 && res <= 1500) write("not yet half full.\n"); 
	if(res > 10 && res <= 700) write("quite empty.\n"); 
	if(res <= 10) write("empty.\n"); 
	return 1;
    }

    if(str == "water" || str == "flour")
    {
	if (!darkcheck(TP))
	    return 1;
	NF("You forgot to attach that module.\n");;
	if(str == "water")
	{
	    if(!(flag(2,0)))
		return 0;
	    write("The tank inside the dispenser is ");
	    res = (find_gizmo(TP)->check_water());
	}
	else
	{
	    if(!(flag(10,0)))
		return 0;
	    write("The storage room for flour is ");
	    res = (find_gizmo(TP)->check_flour());
	}
	allbb(" checks something in " + HIS(TP)
	  + " gizmo.");
	if(res == 40) write("full.\n");
	if(res > 31 && res != 40)write("nearly full.\n");
	if(res > 23 && res < 32) write("well filled.\n");
	if(res > 15 && res < 24) write("about half full.\n");
	if(res > 7  && res < 16) write("quite empty.\n");
	if(res < 8  && res) write("nearly empty.\n");
	if(!res) write ("empty.\n");
	return 1;
    }
    if(str != "engine" && str != "steamengine" && str != "wood")
    {
	NF("Check what?\n");
	return 0;
    }
    if(!(flag(3,0)))
    {
	NF("You forgot to attach that module.\n");;
	return 0;
    }
    if (!darkcheck(TP))
	return 1;

    if(str == "wood")
    {
	write("The storage chamber for wood inside the engine is ");
	allbb(" checks something in " + HIS(TP)
	  + " gizmo.");
	res = (find_gizmo(TP)->check_wood());
	if(res ==14) write("full.\n");
	if(res > 9 && res != 14)write("nearly full.\n");
	if(res > 3 && res <  10) write("about half full.\n");
	if(res < 4 && res) write("nearly empty.\n");
	if(!res) write ("empty.\n");
	return 1;
    }
    write("You check the steamengine:\n");
    allbb(" checks something in " + HIS(TP)
      + " gizmo.");
    if(find_gizmo(TP)->check_fire())
	write("The fire is burning.\n");
    else
    {
	write("The engine is switched off.\n");
	return 1;
    }
    if(find_gizmo(TP)->check_steam())
	write("Pressure of the steam is ok.\n");
    else write("There is not enough pressure yet.\n");
    return 1;
}

int
engulf(string str)
{
    object target, *oblist;
    string result;

    if (!darkcheck(TP))
	return 1;
    result = steamengine_check(TP);
    if(result != "ok")
    {
	write(result);
	return 1;
    }

    write("You open a valve at the engine and release a cloud of steam");
    say(QCTNAME(TP) + " does something to " + HIS(TP) + " gizmo "
      + "and releases a cloud of steam");
    find_gizmo(TP)->reduce_water();

    if((random (10) < 2) || (str == "me") || (str == "myself") || (C(str) == TP->query_name()))
    {
	write(" completely engulfing yourself.\n");
	say(" which engulfs " + HIM(TP) + " completely. "
	  + C(HE(TP)) + " is invisible for a second.\n");
	TP->command("$cough");
	return 1;
    }

    if (!(target = P(str, E(TP))))
    {
	write(" but cannot find your target.\n");
	say(".\n");
	return 1;
    }    

    if (!living(target))
    {
	tell_room(E(TP)," engulfing the " + target->query_adj() + " "
	  + target->query_name() + ".\n");
	return 1;
    }

    oblist = ({target, TP});
    if ((target->query_stat(1)) >= (random(80) - 20))
    {
	TP->catch_msg(" but miss " + QTNAME(target) + ".\n");
	tell_room(E(TP), " which closely misses " + QTNAME(target)
	  + ".\n", oblist);
	target->catch_msg(" in your direction which you easily evade.\n");
	return 1;
    }
    TP->catch_msg(" engulfing " + QTNAME(target) + ". "
      + C(HE(TP)) + " is invisible for a second.\n");
    tell_room(E(TP), " engulfing " + QTNAME(target) + ". " 
      + C(HE(target)) + " is invisible for a second.\n"
      , oblist);
    target->catch_msg(" engulfing you.\n");
    target->command("$cough");
    return 1;
}


int
toot()
{
    string *exits;
    int i;
    string result;

    result = steamengine_check(TP);
    if(result != "ok")
    {
	write(result);
	return 1;
    }

    find_gizmo(TP)->reduce_water();
    write("You open a valve of the steam engine.\n");
    allbb(" does something to " + HIS(TP) + " gizmo.");
    tell_room(E(TP), "Toooooot!!!\n");

    exits = (E(TP)->query_exit());
    for(i=0; i < sizeof(exits); i+=3)
	tell_room(exits[i], "Tooooot!\n");
    return 1;
}

int
ignite(string str)
{
    if(!flag(3,0))
    {
	NF("You forgot to attach that module.\n");
	return 0;
    }
    if (!darkcheck(TP))
	return 1;

    if(str != "engine" && str != "steamengine")
    {
	NF("Ignite what?\n");
	return 0;
    }
    if(find_gizmo(TP)->check_fire())
    {
	NF("The engine has already been ignited.\n");
	return 0;
    }
    if(!(find_gizmo(TP)->check_wood()))
    {
	NF("There isn't any wood left.\n");
	return 0;
    }
    if(flag(3,1) == -1)
	return 1;

    find_gizmo(TP)->burn_wood();
    write("Ok.\n");
    allbb(" does something to " + HIS(TP) + " gizmo.");
    return 1;
}

int
ext_engine(string str)
{
    if(!flag(3,0))
    {
	NF("You forgot to attach that module.\n");
	return 0;
    }
    if (!darkcheck(TP))
    {
	NF("It is too dark to do that!\n");
	return 0;
    }
    if(str != "engine off")
    {
	NF("Switch what off?\n");
	return 0;
    }
    if(!(find_gizmo(TP)->check_fire()))
    {
	NF("The engine is already switched off.\n");
	return 0;
    }
    write("You extinguish the fire and lower the pressure.\n");
    say(QCTNAME(TP) + " does something to " + HIS(TP) + " gizmo.\n");
    find_gizmo(TP)->ext_fire();
    return 1;
}

/********************** module: advanced traveller ************************
 *                        flag: 4                                         *
 **************************************************************************/

string
check_exit(string direction, object player, int flag)
{
    int i;
    mixed *exits;
    string result;

    result = steamengine_check(player);
    if(flag > 0)
	result = "ok";  /* We are already moving */
    if(result != "ok")
    {
	player->catch_msg("Why...? Nothing happened.\n");
	if(result == "What?\n")
	    player->catch_msg("You don't have a steamengine.\n");
	else
	    player->catch_msg(result);
	return "fault";
    }
    result = "no_exit";
    exits = (E(player)->query_exit());
    for(i=0;i<sizeof(exits)/3;i++)
    {
	if(exits[3*i+1] == direction)
	{
	    result = exits[3*i];
	    if(exits[3*i+2] != 0)
		result = "no_exit";
	}
    }
    return result;
}

void
bonk(object player, string direction, int flag)
{
    player->catch_msg("OUCH... you hit something!! Everything goes black"
      + "...\n");
    tell_room(E(player), "A gnome flies past you.\nThe next second you "
      + "hear a terrible crashing sound and see, as you turn, " + QNAME(player)
      + " lying flat on " + HIS(player) + " back.\n", player);
    player->heal_hp(-((player->query_max_hp()) / 20) - flag*5);
    if((player->query_hp()) < 0)
    {
	player->do_die();
	return;
    }
    paralyze_player(player, "Your head is too dizzy for that.\n",
      "You can see again.\n", (10+3*flag));
}

void
do_travel(object player, string direction, int flag)
{
    string exit;

    exit = check_exit(direction, player, flag);
    if(exit == "fault")
	return;
    if(exit == "no_exit" && flag)
    {
	set_alarm(2.0, -1.0, &bonk(player, direction, flag));
	return;
    }
    if(exit == "no_exit")
    {
	player->catch_msg("There is no exit to the " + direction + ".\n");
	return;
    }

    if(!CAN_SEE_IN_ROOM(player))
    {
	player->catch_msg("Oh no! It's dark in here!\nYou loose control.\n");	
	set_alarm(2.0, -1.0, &bonk(player, direction, flag));
    }


    if((find_gizmo(player)->check_water()) > 0)
    {
	if(flag == 0)
	{
	    player->catch_msg("Wwwuussshhh.... Off we go!\n");
	    tell_room(E(player), "Leaving a lot of steam behind, "
	      + QTNAME(player) + " is  flung " + direction + "wards.\n"
	      , player);
	}
	else
	{
	    player->catch_msg("You rush " + direction + "wards.\n");
	    tell_room(E(player), "Leaving a lot of steam behind, a gnome "
	      + "rushes past you to the " + direction + ".\n"
	      + "What an incredible speed!\n", player);
	}
	flag++;
	player->command(direction);
	find_gizmo(player)->reduce_water();
	set_alarm(1.5, -1.0, &do_travel(player, direction, flag));
    }
    else
    {
	player->catch_msg("You suddenly lose control of direction.\n");
	set_alarm(2.0, -1.0, &bonk(player, direction, flag));
    }
}

string
find_exit(object player)
{
    int a;
    string *exits;

    exits = (E(player)->query_exit());
    a = random((sizeof(exits)/3));
    return exits[a*3+1];
}

void
flung_msg(object player)
{
    player->catch_msg("Then your Traveller determines a direction for you!\n");
}

void
do_whirl(object player, string str)
{
    string exit = str;
    int tries = 0;

    player->catch_msg("... and release too much steam!\nOops! "
      + "Something went wrong!\nYou are flung about the "
      + "room like balloon with a hole in it.\n");
    tell_room(E(player), QCTNAME(player) + " creates a huge cloud "
      + "of steam and is flung about the room like a balloon "
      + "with a hole in it!\n", player);
    while(exit == str && tries < 3)
    {
	exit = find_exit(player);
	tries++;
    }
    set_alarm(7.0, -1.0, &flung_msg(player));
    set_alarm(8.0, -1.0, &do_travel(player, exit, 1));
}

int
travel(string str)
{
    if(!(flag(4,0)))
    {
	NF("You forgot to attach that module.\n");
	return 0;
    }
    if (!darkcheck(TP))
	return 1;

    if(str == "n") str = "north";
    if(str == "ne") str = "northeast";
    if(str == "e") str = "east";
    if(str == "se") str = "southeast";
    if(str == "s") str = "south";
    if(str == "sw") str = "southwest";
    if(str == "w") str = "west";
    if(str == "nw") str = "northwest";

    if(str!="north"&&str!="northeast"&&str!="east"&&str!="southeast"&&
      str!="south"&&str!="southwest"&&str!="west"&&str!="northwest")
    {
	NF("You cannot travel into that direction.\n");
	return 0;       
    }
    if(flag(4,1) == -1)
	return 1;

    TP->catch_msg("You take aim carefully and open the valve...\n");
    allbb(" does something to " + HE(TP) + " gizmo.");
    if(random(100) < 6) 
    {
	set_alarm(4.0, -1.0, &do_whirl(TP, str));
	return 1;
    }
    set_alarm(4.0, -1.0, &do_travel(TP, str, 0));
    return 1;
}


/******************* module: CleanlinessModule ****************************
 *                   flag:   11                                           *
 **************************************************************************/

void
wash_msg()
{
    int a;

    a = random(4);
    if(a == 0)
    {
	write("Your gizmo gives a prolonged rumble.\n");
	say(QCTNAME(TP) + "'s gizmo gives a prolonged rumble.\n");
	return;
    }
    if(a == 1)
    {
	write("A cloud of steam escapes from your gizmo.\n");
	say("A cloud of steam escapes from " + HIS(TP) + " gizmo.\n");
	return;
    }
    if(a == 2)
    {
	write("Soap drips from the bottom of your gizmo.\n");
	say("Soap drips from the bottom of " + HIS(TP) + " gizmo.\n");
	return;
    }
    if(a == 3)
    {
	write("There's a bubbling noise from your gizmo.\n");
	say("There's a bubbling noise from " + HIS(TP) + " gizmo.\n");
	return;
    }
}

int
wash(string str)
{
    if(!flag(11,0))
    {
	NF("You forgot to attach that module.\n");
	return 0;
    }
    if(P(str, E(TP)))
    {
	NF("You may only wash yourself.\n");
	return 0;
    }
    if(str != "myself" && str != "me" && L(str) != (TP->query_real_name()))
    {
	NF("Wash whom?\n");
	return 0;
    }
    if(!CAN_SEE_IN_ROOM(TP))
    {
	UNSET_WASH(TP);
	UNSET_WASH_SUCCESS(TP);
	NF("It's too dark to wash yourself.\n");
	return 0;
    }
    if(QUERY_WASH(TP) > 3)
    {
	NF("Your PersonalCleanlinessAndRefreshmentModule is still busy.\n");
	return 0;
    }
    if(QUERY_WASH(TP))
    {
	NF("Yes, you're already washing yourself.\n");
	return 0;
    }
    SET_WASH(TP, 1);
    write("You prepare yourself for extensive washing.\n");
    say(QCTNAME(TP) + " does something to " + HIS(TP) + " gizmo.\n");
    return 1;
}

void
end_wash(object player)
{
    int success, flag;
    object obj;

    success = QUERY_WASH_SUCCESS(TP);
    UNSET_WASH(player);
    UNSET_WASH_SUCCESS(TP);

    // Dirty from Kalad

    if(player->query_prop("_live_i_dirty"))
    {
	player->add_prop("_live_i_dirty", player->query_prop("_live_i_dirty") 
	  - success * 25);
	if(success > 8 || player->query_prop("live_i_dirty") < 1)
	{
	    player->remove_prop("_live_i_dirty");
	    if(obj = P("dirty", player))
		obj->remove_object();
	}
    }
    // Dirty from the mud puddle in /d/Shire/common/greenway/gw2

    if(success > 7)
	player->remove_shire_dirty_shadow();

    // Stinking from the skunk in Krynn

    if(obj = P("stink", player) && P("spray", player))
    {
	if(success > 8)
	{
	    obj->remove_object();
	    player->catch_msg("Ahh, how refreshing to be clean again. "
	      + "You don't smell of skunk anymore.\n");
	    tell_room(E(player), QCTNAME(player) + " doesn't stink any"
	      + "more.\n", player);
	}
	else
	    player->catch_msg("You feel fresher now but still smell of "
	      + "skunk!\n");
	flag = 1;
    }     

    // General cleanliness

    if(flag)
	return;

    if(success > 8)
	player->catch_msg("Ahh, how refreshing to be clean again.\n");
    if(success == 8)
	player->catch_msg("You feel much fresher now.\n");
    if(success == 7)
	player->catch_msg("You aren't nearly as scruffy as before.\n");
    if(success == 6)
	player->catch_msg("You definitivly smell better now.\n");
    if(success < 6)
	player->catch_msg("You feel a bit fresher now but a second go wouldn't be bad "
	  + "either.\n");
}   

int
wash_me(string str)
{
    int a;
    string result;

    if(str != "lever" && str != "the lever")
	return 0;

    if(QUERY_WASH(TP) > 3)
    {
	write("Your PersonalCleanlinessAndRefreshmentModule is still busy.\n");
	return 1;
    }

    result = steamengine_check(TP);
    if(result == "What?\n")
	result = "You'll need a steamengine first.\n";
    if(result != "ok")
    {
	UNSET_WASH(TP);
	write(result);
	return 1;
    }

    if(!CAN_SEE_IN_ROOM(TP))
    {
	write("It's too dark to do that.\n");
	UNSET_WASH(TP);
	UNSET_WASH_SUCCESS(TP);
	return 1;
    }

    a = random(4);
    if(a > 1)
	if(flag(11,1) == -1)
	{
	    UNSET_WASH(TP);
	    UNSET_WASH_SUCCESS(TP);
	    return 1;
	}

    write("You pull the lever of your PersonalCleanlinessAndRefreshmentModule.\n");
    say(QCTNAME(TP) + " pulls a lever on " + HIS(TP) + " gizmo.\n");
    wash_msg();

    if(QUERY_WASH(TP) == 1)
    {
	if(a == 0)
	{
	    write("A mixture of steaming hot soap and water pours from the DispensingFunnel "
	      + "into your cupped hands. You scrub yourself vigorously.\n");
	    say("A mixture of steaming hot soap and water pours into " + HIS(TP)
	      + " cupped hands. " + C(HE(TP)) + " scrubs " + HIM(TP) + "self "
	      + "vigorously.\n");
	    find_gizmo(TP)->reduce_water();            
	    SET_WASH_SUCCESS(TP, 4);
	}
	if(a == 1)
	{
	    write("A mixture of steaming hot soap and water pours from the DispensingFunnel "
	      + "into your face. You blow bubbles as you leisurously wash yourself.\n");
	    say("A mixture of steaming hot soap and water pours into " + HIS(TP)
	      + " face. " + C(HE(TP)) + " blows bubbles as " + HE(TP) + " leisurely "
	      + "washes " + HIM(TP) + "self.\n");
	    find_gizmo(TP)->reduce_water();            
	    SET_WASH_SUCCESS(TP, 4);
	}
	if(a == 2)
	{
	    write("Hot water streams from the DispensingFunnel. A few moments later, there's a "
	      + "spurt of soap. You quickly mix the two together.\n");
	    say("Hot water streams from a DispensingFunnel on " + HIS(TP) + " gizmo. "
	      + "A few moments later, there's a spurt of soap. " + C(HE(TP)) + " quickly "
	      + "mixes the two together.\n");    
	    find_gizmo(TP)->reduce_water();            
	    SET_WASH_SUCCESS(TP, 2);
	}
	if(a == 3)
	{
	    write("Viscous hot soap oozes from the DispensingFunnel, unfortunately without "
	      + "accompanying water. You're covered with thick soapy goo.\n");
	    say("Viscous hot soap oozes from a DispensingFunnel, unfortunately without "
	      + "accompanying water. " + C(HE(TP)) + " is covered with thick soapy goo.\n");
	    SET_WASH_SUCCESS(TP, 1);
	}
	SET_WASH(TP, 2);
	return 1;
    }

    if(QUERY_WASH(TP) == 2)
    {
	if(a == 0)
	{
	    write("Clean hot water gushes from the DispensingFunnel. You slowly rinse "
	      + "youself, luxurating in the warmth.\n");
	    say("Clean hot water gushes from a DispensingFunnel on " + HIS(TP)
	      + " gizmo. " + C(HE(TP)) + " slowly rinses " + HIM(TP) + "self, "
	      + "luxurating in the warmth.\n");
	    find_gizmo(TP)->reduce_water();            
	    SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 4);
	}
	if(a == 1)
	{
	    write("The gizmo gurgles as hot water pours from the DispensingFunnel. You "
	      + "splash it literally all about your person to remove all traces of "
	      + "soap.\n");
	    say(C(HIS(TP)) + " gizmo gurgles as hot water pours from the DispensingFunnel. "
	      + C(HE(TP)) + " splashes it literally all about " + HIS(TP)
	      + " person to remove all traces of soap.\n");
	    find_gizmo(TP)->reduce_water();
	    SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 3);
	}
	if(a == 2)
	{
	    write("Hot water flows from the DispensingFunnel. Unfortunately it is slightly "
	      + "soapy, so your rinse is only partially effective.\n");
	    say("Hot water flows from a DispensingFunnel on " + HIS(TP) + " gizmo. "
	      + C(HE(TP)) + " rinses " + HIM(TP) + "self.\n");
	    find_gizmo(TP)->reduce_water();
	    SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 2);        }
	if(a ==  3)
	{
	    write("Slightly warm water tickles from the funnel. You manage to rinse off some "
	      + "soap.\n");
	    say("Water tickles from a funnel on " + HIS(TP) + " gizmo. "
	      + C(HE(TP)) + " manages to rinse off some soap.\n");
	    SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 1);
	}
	SET_WASH(TP, 3);
	return 1;
    }        

    if(QUERY_WASH(TP) == 3)
    {
	if(a == 0)
	{
	    write("A mechanical arm extends from the TowelExtrusionUnit and hands you a soft, "
	      + "warm towel. You dry yourself thouroughly and return the towel.\n");
	    say("A mechanical arm extends from " + HIS(TP) + " gizmo and hands "
	      + HIM(TP) + " a soft, warm towel. " + C(HE(TP)) + " dries "
	      + HIM(TP) + "self thouroughly.\n");
	    SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 3);
	}
	if(a == 1)
	{
	    write("A mechanical arm creaks out from the TowelExtrusionUnit and drops a soft "
	      + "towel. You catch it just before it hits the ground, dry yourself and " 
	      + "drape the towel over the mechanical arm which slowly and noisily retracts.\n");
	    say("A mechanical arm creaks out from " + HIS(TP) + " gizmo and drop a "
	      + "soft towel. " + C(HE(TP)) + " catches it just before it hits the ground, "
	      + "dries " + HIM(TP) + "self and drapes the towel over the arm which "
	      + "slowly and noisily retracts.\n");
	    SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 3);
	}
	if(a == 2)
	{
	    write("There's a grinding noise from the TowelExtrusionUnit and a raveled strip of "
	      + "toweling drops into your hands. It disintegrates before you quite finished "
	      + "drying.\n");
	    say("There's a grinding noise from " + HIS(TP) + " gizmo and a strip of "
	      + "toweling drops into " + HIS(TP) + " hands. It disintegrates before "
	      + HE(TP) + " quite finished drying.\n");
	    SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 2);                                          
	}
	if(a == 3)
	{
	    write("There's a load clank from your gimzo but nothing else happens. You shake "
	      + "the water off as best as you can.\n");
	    say("There's a loud clank from " + HIS(TP) + " gizmo but nothing else "
	      + "happens. " + C(HE(TP)) + " shakes " + HIM(TP) + "self like a "
	      + "wet dog to get rid of the water.\n");
	    SET_WASH_SUCCESS(TP, QUERY_WASH_SUCCESS(TP) + 1);
	}
	SET_WASH(TP, 4);
	set_alarm(5.0, -1.0, &end_wash(TP));
    }
    return 1;
}


