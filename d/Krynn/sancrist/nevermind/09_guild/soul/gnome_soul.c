/*
 * Creator: Shadowlynx
 * Date   : July/99
 * File   : /d/Krynn/sancrist/nevermind/09_guild/tinkers/gnome_soul.c
 * Updated:
 * By whom:
 * Special: Taken in part from kgnome_soul.c by Dajala.
 */

#pragma save_binary

inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "../guild.h"
#include "../modules.h"

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
/* for the recycler */
#define SET_CALL(xx,yy)          (xx->add_prop("_gnome_i_recycler_pass",yy))
#define QUERY_CALL(xx)           (xx->query_prop("_gnome_i_recycler_pass"))
/* for the GestureMatic */
#define QUERY_OPERATIONAL(xx)    (xx->query_prop("_gnome_i_gmaker_on_"))
#define SET_OPERATIONAL(xx,yy)   (xx->add_prop("_gnome_i_gmaker_on_", yy));(xx-
>add_prop(LIVE_I_CONCENTRATE, yy))
#define UNSET_OPERATIONAL(xx)    (xx->remove_prop("_gnome_i_gmaker_on_"));(xx-
>remove_prop(LIVE_I_CONCENTRATE))
#define SET_ENTANGLED(xx)        (xx->add_prop("_gnome_i_gmaker_ent_",1))
#define REMOVE_ENTANGLED(xx)     (xx->remove_prop("_gnome_i_gmaker_ent_"))
#define QUERY_ENTANGLED(xx)      (xx->query_prop("_gnome_i_gmaker_ent_"))
#define GEST_SUB                 "_gesturematic_unfolded"
#define GEST_SUB_ENT             "_gesturematic_unfolded_but_entangled"
[32m#define STORE_BAKE_ALARM(xx,yy)  (xx->add_prop("_gnome_s_bakealarm_",yy)) [0m
    [32m#define GET_BAKE_ALARM(xx)       (xx->query_prop("_gnome_s_bakealarm_")) [0m
#define REMOVE_BAKE_ALARM(xx)    (xx->remove_prop("_gnome_s_bakealarm_"))
	/* for the PersonalCleanlinessModule */
#define SET_WASH(xx,yy)          (xx->add_prop("_gnome_i_washing",yy))
#define QUERY_WASH(xx)           (xx->query_prop("_gnome_i_washing"))
#define UNSET_WASH(xx)           (xx->remove_prop("_gnome_i_washing"))
#define SET_WASH_SUCCESS(xx,yy)  (xx->add_prop("_gnome_i_wash_success",yy))
#define QUERY_WASH_SUCCESS(xx)   (xx->query_prop("_gnome_i_wash_success")) 
#define UNSET_WASH_SUCCESS(xx)   (xx->remove_prop("_gnome_i_wash_success"))
	/* For the DistillationApparatus */
#define FUNNEL_OPEN(xx)          (xx->add_prop("_gnome_i_funnel_open", 1))
#define QUERY_FUNNEL_OPEN(xx)    (xx->query_prop("_gnome_i_funnel_open"))
#define FUNNEL_CLOSED(xx)        (xx->remove_prop("_gnome_i_funnel_open"))
#define ADD_VALUE(xx,yy)         (xx->add_prop("_gnome_i_dist_value", \
                                 xx->query_prop("_gnome_i_dist_value") + yy))
#define QUERY_VALUE(xx)          (xx->query_prop("_gnome_i_dist_value"))
#define REMOVE_VALUE(xx)                 (xx->remove_prop("_gnome_i_dist_value"-
      ))
#define ADD_LIQUID(xx,yy)        (xx->add_prop("_gnome_i_liquid_amount", \
                                 xx->query_prop("_gnome_i_liquid_amount") +
    yy))
#define QUERY_LIQUID(xx)         (xx->query_prop("_gnome_i_liquid_amount"))
#define REMOVE_LIQUID(xx)        (xx->remove_prop("_gnome_i_liquid_amount"))
[32m#define STORE_SPILL_ALARM(xx,yy)         (xx->add_prop("_gnome_i_spill_alarm", [0m
	yy))
#define REMOVE_SPILL_ALARM(xx)   (xx->remove_prop("_gnome_i_spill_alarm"))
#define QUERY_SPILL_ALARM(xx)    (xx->query_prop("_gnome_i_spill_alarm"))

    /*****************************************************************************
     * Prototypes                                                                *
     *****************************************************************************/

    int wash_me(string str);


    /*****************************************************************************
     * Soul identifying and autoloading
     *****************************************************************************/

    [32mstring get_soul_id() { return "Krynn Gnomes"; } [0m

	int query_cmd_soul() { return 1; }

	/*****************************************************************************
	 * The list of verbs and functions. Please add new in alphabetical order.
	 *****************************************************************************/

	mapping
	query_cmdlist()
	{
	    [32m    seteuid(getuid()); [0m

		return ([
		  "analyze":"analyze",
		  "build":"build",
		  "check":"check",        /* module, flag 3 */
		  "concentrate":"concentrate",
		  "con":"concentrate",      
		  "clean":"clean",        /* module, flag 8 */
		  "close":"close_funnel",   /* module, flag 12 */
		  "drain":"drain_dist",     /* module, flag 12 */
		  "end":"end_gbake",        /* module, flag 10 */
		  "engulf":"engulf",      /* module, flag 3 */
		  "flush":"flush",        /* module, flag 7 */
		  "fold":"fold",          /* module, flag 9 */
		  "gbake":"gbake",  /* module, flag 10 */
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
		  [33m      "gsay":"gsay", [0m
		      [33m      "-":"gsay", [0m
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
			  "goil":"goil",            /* module, flag 8 */
			  "philosophy":"philosophy",
			  "philo":"philosophy",
			  "polish":"polish",      /* module, flag 8 */
			  "pour":"pour_drink",      /* module, flag 12 */
			  "pull":"recycle_2",     /* module, flag 7 and 11 */
			  "refresh":"refresh",    /* module, flag 2 */
			  "recycle":"recycle",    /* module, flag 7 */
			  "switch":"ext_engine",  /* module, flag 3 */
			  "toot":"toot",          /* module, flag 3 */
			  "travel":"travel",      /* module, flag 4 */
			  "unentangle":"unentangle",      /* module, flag 9 */
			  "unfold":"unfold",      /* module, flag 9 */
			  "wash":"wash"             /* module, flag 11 */
			]);
		  }

		    static mixed
		    parse_this(string str, string form)
		    {
			object   *oblist, *tmplist;
			int      i;

			tmplist = ({});
			if (!CAN_SEE_IN_ROOM(this_player()))
			    return tmplist;

			if (!str || (!parse_command(lower_case(str), environment(this_player()),
			      form, oblist)))

			    return ({});

			oblist = NORMAL_ACCESS(oblist, 0, 0);

			if (!sizeof(oblist))
			    return ({});

			for (i = 0; i < sizeof(oblist); i++)
			{
			    if (objectp(oblist[i]) &&
			      (this_player() != oblist[i]) &&
			      CAN_SEE(this_player(), oblist[i]))
				tmplist = tmplist + ({ oblist[i] });
			}
			return tmplist;
		    }


		    /*
		     * Function name: show_subloc
		     [35m * Description:   This function is called each time someone looks at us [0m
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
				return C(PRONOUN(me)) + " is operating a giant mechanical arm.\n";
			}
			if(subloc == GEST_SUB_ENT)
			    if (for_obj == me)
				return "You are hopelessly entangled into the wires of your "
				+ "Gesturematic.\n";
			    else
				return C(PRONOUN(me)) + " is hopelessly entangled into a lot of "
				+ "crossed wires.\n";       
			return "";
		    }




		    /******************* general funtions *************************************/

		    /* returns the gizmo 
		     * needed to call functions in the gizmo.
		     */

		    object
		    find_gizmo(object player)
		    {
			object ob;
			ob = present("k_gizmo", player);
			return ob;
		    }


		    /* checks whether the correct module flag is set in the gizmo 
		     * returns 1: module present
		     *         0: module not present
		     */
		    (dialup161-1-3.swipnet.se)]

		  int
		  flag(int number, int break_check_flag)
		  {
		      object gizmo;

		      gizmo = find_gizmo(TP);
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


		  [32m/* Finds the named targets to do something to. [0m
			*/

		    object
		    [32m*get_target(string str) [0m
			{
			    object *who;

			    if(!str)
				return who;
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
			    paralyze->move(player);       /* Now DO the paralyze */
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

			int
			analyze(string str)
			{
			    mixed *info;
			    int success, anzahl, i;

			    float ti;
			    object ob;

			    ti = 42.0;
			    setuid(); seteuid(getuid(TO)); 
			    NF("You don't know how to do that.\n");
			    if((TP->query_skill(SS_BUILD)) < 1)
				return 0;
			    NF("Analyze what?\n");
			    if(!str)
				return 0;
			    if(!darkcheck(TP))
				return 1;
			    NF("You do not hold a " + str + ".\n");
			    ob = P(str, TP);
			    if(!ob)
				return 0;
			    NF("You cannot analyze " + QTNAME(ob) + ".\n");
			    if(living(ob))
				return 0;
			    NF("The " + ob->short() + " is too badly damaged to be analyzed.\n");
			    if(ob->query_prop(OBJ_I_BROKEN))
				return 0;
			    NF("You see no way of taking the " + ob->short() + " apart.\n");
			    if(ob->query_prop(OBJ_M_NO_DROP))
				return 0;

			    NF("You are still busy with another object.\n");
			    if(ANALYZE_ALARM(TP))
				return 0;

			    write("You sit down and start to take apart the " + ob->short()
			      + " with your gizmo.\n");
			    say(QCTNAME(TP) + " seats " + OBJECTIVE(TP) + "self on the ground "
			      + "and starts to take apart " + POSSESSIVE(TP) + " " + ob->short() +
			      ".\n");

			    success = (40 * ((TP->query_skill(SS_BUILD)+10) * (60+random(50))) /100) *
			    ((TP->query_stat(3))/5+(TP->query_stat(4)*2/5)+40) /10000;
			    if (ob->query_prop(OBJ_I_RES_IDENTIFY))
				success =- (ob->query_prop(OBJ_I_RES_IDENTIFY));
			    info = (P(str, TP)->query_prop(MAGIC_AM_ID_INFO));

			    SET_ANALYZE_ALARM(TP, set_alarm(6.0, 6.0, "analyze_msg", TP));
			    set_alarm(110.0, -1.0, "emergency_remove", ob, TP, str);

			    if (!info)
			    {
				set_alarm(40.0, -1.0, "no_magic", TP);
				set_alarm(42.0, -1.0, "end", ob, TP, str, ti);

				return 1;
			    }
			    anzahl = sizeof(info) / 2;
			    if(anzahl == 1)
			    {
				if(success >= info[1])
				    set_alarm(40.0, -1.0, "give_info", info[0], TP); 
				else
				    set_alarm(40.0, -1.0, "fail", TP);
				set_alarm(42.0, -1.0, "end", ob, TP, str);
				return 1;
			    }

			    if(info[1]<info[anzahl*2-1])
			    {
				for (i=0; i<anzahl; i++)
				{
				    if(success>=info[2*i+1])
				    {
					ti = 42.0+itof(i*3);
					set_alarm(40.0+itof(i*3), -1.0, "give_info", info[2*i],
					  TP, ti);
				    }
				}
			    }
			    else
			    {
				for (i=anzahl-1; i>-1; i--)
				{
				    if(success>=info[2*i+1])
				    {
					ti = 42.0+itof(anzahl*3)-itof(i*3);
					set_alarm(40.0+itof(anzahl*3)-itof(i*3), -1.0,
					  "give_info", 
					  info[2*i], TP, ti);
				    }
				}
			    }
			    if (ti < 42.5)
				set_alarm(ti , -1.0, "fail", TP);
			    else
				paralyze_player(TP, "You are too absorbed with taking apart "
				  + "your " + ob->short() + ".\n", "", ftoi(ti));
			    set_alarm(ti, -1.0, "end", ob, TP, str, ti);
			    return 1;
			}

			void
			analyze_msg(object player)
			{
			    int a;
			    string *msg;

			    msg = ({"take", " away some parts", "remove", " some bits", "look",
			      " at some bits", "check", " some especially interesting parts", 
			      "look", " thoughtfully", "put", " aside some parts", "rest",
			      " a little bit", "turn", " around one piece", "ponder", 
			      " the situation", "throw", " away a seemingly useless part",
			      "break", " something in two"});
			    a = random(11);
			    player->catch_msg("You " + msg[a*2] + msg[a*2+1] + ".\n");
			    tell_room(E(player), QCTNAME(player) + " " + msg[a*2] + "'s" 
			      + msg[a*2+1] + ".\n", player);
			}

			void
			give_info(string str, object player, float ti) 
			{
			    if (ti < 42.5)
				player->catch_msg("You get to know the following:\n"); 
			    remove_alarm(ANALYZE_ALARM(player));
			    SET_ANALYZE_ALARM(player,0);
			    player->catch_msg(str);
			}

			void
			fail(object player)
			{
			    player->catch_msg("You couldn't find anything out.\nThis task seems to "
			      + "be beyond your skill.\n");
			    tell_room(E(player), QCTNAME(player) + " seems to be finished but looks"
			      + " unhappy.\n", player);
			    remove_alarm(ANALYZE_ALARM(player));
			    SET_ANALYZE_ALARM(player,0);
			}

			void
			end(object ob, object player, string str, float time)
			{
			    object heap;

			    if(abs(time) > 42.5)
				player->catch_msg("This is all information you could find out.\n");
			    setuid(); seteuid(getuid(TO)); 
			    heap = clone_object(GOBJ + "heap");
			    heap->add_prop(OBJ_I_WEIGHT, (ob->query_prop(OBJ_I_WEIGHT)));
			    heap->add_prop(OBJ_I_VOLUME, (ob->query_prop(OBJ_I_VOLUME)));

			    heap->move(E(player));
			    tell_room(E(player), PRONOUN(player) + " drops something.\n", player);
			    player->catch_msg("You drop the now useless parts of the " 
			      + ob->short() + ".\n");
			    ob->remove_object();
			}

			void
			no_magic(object player)
			{
			    player->catch_msg("This object doesn't seem to be magical.\n");
			    remove_alarm(ANALYZE_ALARM(player));
			    SET_ANALYZE_ALARM(player,0);
			}

			void
			emergency_remove(object ob, object player, string str)
			{
			    if(ANALYZE_ALARM(player))
			    {
				fail(player);
				player->catch_msg("Something seems to be wrong with the item you "
				  + "tried to analyze. Please leave a bugreport where you "
				  + "found it.\n");

				end(ob, player, str, 1.0);
			    }
			}


