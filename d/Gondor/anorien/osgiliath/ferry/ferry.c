/*
 * /d/Gondor/anorien/osgiliath/ferry.c
 *
 * The ferry run by rangers that crosses the Anduin at Osgiliath
 *
 * Modification log:
 * Olorin, June 1995: small fixes
 * Olorin, 22-Nov-1996: General revision, fix movement of the captain.
 * Fysix, Oct 1997: Adjusted code for steeds,
 *                  don't allow any steeds on this ferry.
 * Gnadnar, 22-Jan-98:	fixed fast-forward-mode bug (double alarms)
 *      		I commented each change in case of problems
 * Gnadnar, 9-Oct-98:	fixed bug that prevent teams from following
 *			leader on board
 *
 * This version:
 * Copyright (c) 1996 by Christian Markus
 */
#pragma strict_types

#include "/d/Gondor/defs.h"

inherit "/d/Genesis/ship/ship.c";
inherit STD_DIR + "steed/prevent_steed";

#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#undef DEBUG
#ifdef DEBUG
#define DEBUG_MSG(x) find_player("olorin")->catch_msg("DEBUG ### ferry ### "+x+".\n");
#else
#define DEBUG_MSG(x)
#endif

public string
long_desc()
{
    int     np;
    object *pass;
    string  desc;

    desc = 
	"This is a small rowing boat that is used as a ferry to cross the "
      + "Anduin. The boat has been painted dark so that it will be harder "
      + "to discover in the night. A small part of the boat towards the "
      + "bow has been covered by a tarpaulin to give some cover against "
      + "rain and wind. The boat cannot hold more than four persons, "
      + "including the ferryman.";

    pass = FILTER_LIVE(all_inventory(find_object(query_deck()[0])));

    switch (np = sizeof(pass))
    {
    case 0:
	desc += " Right now, the ferry is empty.";
	break;
    case 1:
	desc += " Right now, there is one person in the ferry.";
	break;
    case 2:
	desc += " Right now, there are two persons in the ferry.";
	break;
    default: desc += " Right now, there are "+LANG_WNUM(np)
	+ " persons in the ferry. Therefore, you cannot board!";
    }
    return desc + "\n";
}

public void
create_ship()
{
    object  cap;

    // This is necessary to prevent getting multiple captains!
    if (!IS_CLONE)
        return;

    seteuid(getuid());
    set_cabin(OSG_DIR + "ferry/tent");
    set_deck(OSG_DIR + "ferry/in_ferry");
    FIX_EUID
    cap = clone_object(OSG_DIR + "ferry/ferryman");
    DEBUG_MSG("Captain: "+file_name(cap));
    set_captain(cap);
    set_places_to_go(({OSG_DIR + "underbridge",
                       ANDUIN_DIR + "wosgbr",
                       ANDUIN_DIR + "wosg1",
                       ANDUIN_DIR + "wosg2",
                       ANDUIN_DIR + "cosg",
                       ANDUIN_DIR + "eosg1",
                       ANDUIN_DIR + "eosg2",
                       ANDUIN_DIR + "eosgbr",
                       ITH_DIR + "osgiliath/underbridge",
                       ANDUIN_DIR + "eosgbr",
                       ANDUIN_DIR + "eosg2",
                       ANDUIN_DIR + "eosg1",
                       ANDUIN_DIR + "cosg",
                       ANDUIN_DIR + "wosg2",
                       ANDUIN_DIR + "wosg1",
                       ANDUIN_DIR + "wosgbr"}));
    set_time_between_stops(({15,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
                             15,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2,
                             2 }));
    set_name("boat");
    add_name("ferry");
    add_name("ship");
    add_adj("small");
    add_adj("old");
    add_adj("rowing");
    set_long(long_desc);
    // Fysix: No steeds are allowed on this ferry.
    set_no_allow_steed(1);
    enable_reset();
}

/*
 * Function name: sail_away_out_on_the_open_sea
 * Description  : The core of the ship; this is called every callout_fq
 *                seconds and will move the ship around at appropiate
 *                intervals
 */
public void
sail_away_out_on_the_open_sea()
{
    int     time,
            move_flag;
    object  pier,
            captain,
            clock = find_object(CLOCK);
    string  dt = clock->query_time_of_day();

    DEBUG_MSG("called sail_away_out_on_the_open_sea with "
	      +call_no+" at location "+location);
    DEBUG_MSG("Captain = "+file_name(query_captain())
	      + ( objectp(environment(query_captain())) ? 
		 " in "+file_name(environment(query_captain())) :
		 " in the void!"));
    if (call_no < 1)
    {
        board_enabled = 0;
        location++;
        if (location >= sizeof(places_to_go))
            location = 0;
        call_no = time_between_stops[location];

        if (objectp(captain = query_captain()))
        {
	    DEBUG_MSG("sail_...: Captain = "+file_name(captain)+" ok!");
            move_flag = 1;
            if (file_name(pier = ENV(captain)) != query_deck()[0])
            {
		DEBUG_MSG("pier = "+file_name(pier));
                if ((dt == "night" || dt == "evening" || dt == "early morning")
                    && (pier == ENV(TO)))
                {
		    DEBUG_MSG("sail_...: trying to move Captain to "
			      + query_deck()[0]);
                    captain->move_living("boarding the ship", query_deck()[0]);
                    tell_room(pier,
                        CAP(LANG_ADDART(short())) + " starts moving away.\n");
                }
                else 
		{
		    if (pier != ENV(TO))
		    {
			DEBUG_MSG("Captain is in "+file_name(pier));
			if (!objectp(captain->query_attack()) &&
				    (!sizeof(captain->query_enemy(-1)) ||
				     !sizeof(captain->query_enemy(-1) &&
					    all_inventory(ENV(TO)))))
			    captain->move_living("down", ENV(TO));
		    }
		    else
		    {
			DEBUG_MSG("It is day, don't move!");
			captain->command
			    ("say We cannot cross the Anduin during the day.");
			captain->command
                            ("say We will have to wait until darkness falls!");
		    }
		    location--;
                    if (location < 0)
                        location = sizeof(places_to_go);
                    call_no = time_between_stops[0];
		    DEBUG_MSG("call_no reset to "+call_no);
		    move_flag = 0;
		    DEBUG_MSG("move_flag reset to "+move_flag);
                }
            }
	    DEBUG_MSG("move_flag = "+move_flag+", location = "+location);
            if (move_flag)
            {
		DEBUG_MSG("move_flag = "+move_flag);
                call_left(ENV(TO), places_to_go[location]);
                call_arrive(places_to_go[location]);
                move(places_to_go[location]);
            }
            if (places_to_go[location]->query_prop(ROOM_I_TYPE)
		!= ROOM_IN_WATER)
            {
		DEBUG_MSG("no ROOM_IN_WATER");
                if (captain)
                {
		    DEBUG_MSG("captain = "+file_name(captain));
                    if (file_name(ENV(query_captain())) == query_deck()[0])
                        captain->move_living("the ship", places_to_go[location]);
                    if (move_flag)
                    tell_room(places_to_go[location],
                        CAP(LANG_ADDART(short())) + " just came in.\n");
                    if (dt == "night" || dt == "evening" || dt == "early morning")
                    {
                        captain->command("say All aboard!  The "+short()
                          + " leaves in "+(time = query_callout_fq() * call_no)
                          + " seconds!");
                        if (query_ticket_id())
                            captain->command("say Buy your tickets now or stay ashore!");
                        set_alarm(itof(time - 20), 0.0, give_leave_warning);
                    }
                    else if(move_flag)
                    {
                        captain->command("say We cannot cross the Anduin during the day.");
                        captain->command("say We will have to wait until darkness falls!");
                    }
                }
                set_board_enabled(1);
            }
            else
                tell_room(places_to_go[location], 
			  CAP(LANG_ADDART(short()))+" passes by.\n");
        }
        else
        {
            /* 22-Jan-98 Gnadnar
             * added this to prevent ferry-fast-forward-mode.
             * if we continue to set alarms when there's no captain
             * (which is wasteful, anyway, since they have no effect),
             * then when reset fires and a new captain appears we end up
             * with double alarms running.  the results is a boat
             * that moves >>>very<<<< fast ... so fast that players
             * can't board before it departs.
             */
             return;
        }
    }
    else
        call_no--;

    DEBUG_MSG("going to set up call_out");
    if (event_enable)
    {
        if (!(event_enable = !random_event()))
            return;
        /* 22-Jan-98, Gnadnar: remember alarm id so stop_ship()
         * can cancel it.
         */
        alarm_id = set_alarm(itof(query_callout_fq()), 0.0, 
		  sail_away_out_on_the_open_sea);
    }
    else
    {
        /* 22-Jan-98, Gnadnar: remember alarm id so stop_ship()
         * can cancel it.
         */
        alarm_id = set_alarm(itof(query_callout_fq() * call_no), 0.0, 
		  sail_away_out_on_the_open_sea);
        call_no = 0;
    }
    DEBUG_MSG("Exiting sail_away_out_on_the_open_sea now!");
}

public int
ranger_test(object tp)
{
    int iranger;
    if(!objectp(tp))
        return 0;

    if (!IS_RANGER(tp))
        return 0;

#if 0
    don't do this -- calling command() here will wipe out the player's
    verb "board", and then teams won't follow their leader onto the ferry
    if (interactive(tp))
        query_captain()->command("unmask me");
#endif
    return 1;
}

int
badge_test(object tp)
{
    object badge, cap;

    if (objectp(cap = query_captain()))
        return cap->badge_test(tp);

    if (!objectp(badge = present("_ithilien_badge",tp)))
        return 0;

    if(badge->query_prop("_ithilien_leave_name") != tp->query_real_name())
        return 0;

    return 1;
}

int enemy_test(object tp) { return IS_EVIL(tp); }

/*
 * Function name: board
 * Description  : Allow a player to board the ferry if he is a ranger or has the
 *                leave of the Steward to go to Ithilien
 * Arguments    : what - what we want to enter
 * Returns      : 1 - success
 *                0 - wrong parameters
 */
varargs public int
board(mixed what)
{
    object ticket, *tmp, cap, *pass;

    if (!board_enabled)
        return 0;
    if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what,
                ENV(TP))) || TO != tmp[0]))
        return 0;

    ENV(TP)->set_dircmd(what);
                      /* This will allow team members to do exactly the
                       * same command their leader did.*/

    if (enemy_test(TP))
    {
        if (objectp(cap = query_captain()))
        {
            tell_room(ENV(TO), QCTNAME(TP) + " tries to board the "
              + short() + ", but " + QTNAME(cap) + " stops "
              + TP->query_objective() + ".\n", TP);
            write(cap->query_The_name(TP) + " stops you.\n");
            cap->command("say Forget it, creature of Morgoth!");
        }
        else
        {
            write("A Ranger aboard the ferry pushes you back, "
              + "preventing you from boarding.");
        }
    }
    else if (ranger_test(TP) || badge_test(TP) ||
        (file_name(ENV(TP)) == places_to_go[sizeof(places_to_go)/2]))
    {
        pass = FILTER_LIVE(all_inventory(find_object(query_deck()[0])));
        if (sizeof(pass) >= 3)
        {
            write("The ferry is already full! You cannot board!\n");
            tell_room(ENV(TO), QCTNAME(TP)+" tries to board the "+short()
              + ",\nbut then "+TP->query_pronoun()+" realizes that the "
              + short() + " is already full. \n", TP);
        }
        else
        {
            ::board(what);
/* Previous code, replace by code above
                tell_room(ENV(TO), QCTNAME(TP) + " boards the "+ short() + ".\n", TP);
                write("You board the " + short() + ".\n");
    DEBUG_MSG("board: trying to move Captain to "+query_deck()[0]);
                TP->move_living("boarding the ship", query_deck()[0]);
 */
        }
    }
    else
    {
        if (cap = query_captain())
        {
            tell_room(ENV(TO), QCTNAME(TP) + " tries to board the "
              + short() + ",\nbut " + QTNAME(cap) + " scowls menacingly "
              + "at " + TP->query_objective() + " and blocks " 
              + TP->query_possessive() + " way.\n", TP);
            write(CAP(cap->query_the_name(TP)) + " scowls at you.\n");
            cap->command("say You have no business in Ithilien, "+
                TP->query_nonmet_name() + ".");
        }
        else
        {
            write("A ranger prevents you from boarding the "+ short() + ".\n");
            tell_room(ENV(TO), QCNAME(TP) + " tries to "+
              "board the " + short() + ", but is stopped.\n", TP);
        }
    }
    return 1;
}

void
reset_ship()
{
    object  cap = query_captain();

    if (!objectp(cap))
    {
DEBUG_MSG("Trying to clone a new captain!");
        FIX_EUID
        cap=clone_object(OSG_DIR + "ferry/ferryman");
DEBUG_MSG("cloned "+file_name(cap));
        set_captain(cap);
        cap->move_living("down", query_deck()[0]);
DEBUG_MSG("moved "+file_name(cap)+" to "+query_deck()[0]);
        start_ship(location);
DEBUG_MSG("started ship at location "+location);
    }
}


/* Function name: query_prevent_board_ship
 * Description:   prevent a player from boarding. This function
 *                should handle all messages itself.
 * Arguments:     object player
 * Returns:       int 1 if not allowed to board
 */
public int
query_prevent_board_ship(object player)
{
    object  cap = query_captain();
    if (objectp(cap) &&
	cap->did_attack(player->query_name()))
    {
	cap->command("say I remember you -- you attacked me!");
	cap->command("say Leave while you have the chance!");
	return 1;
    }
}
