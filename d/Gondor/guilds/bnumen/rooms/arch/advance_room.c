/*
 *	/d/Gondor/guilds/bnumen/rooms/advance_room.c
 *
 *	Copyright (c) 1994, 1997 by Christian Markus
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	12-Feb-1997, Olorin:	Revision.
 */
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"
#include "/d/Gondor/guilds/bnumen/lib/riddles.h"

#define DL_RIDDLE_SCALE	10
#define DL_EXP_STEPS	({ "a little more", "more", "much more" })
#define MIN_DAYS	 1

public varargs int add_failed(mixed who, int day);
public void    answer_riddle(string str, mixed sol);

static mapping Failed = ([]);

public void
create_cabin()
{
    set_short("the Chamber of Knowledge");
    set_long("The Chamber of Knowledge in the Houses of the Black Numenoreans. "
      + "Here the members of the Houses of the "
      + "Black Numenoreans are tested regarding their knowledge of history and "
      + "lore. Only those who pass the tests gain status in the eyes "
      + "of their fellow bnumen. If you want to take a test, try "
      + "to 'advance' your status.\n");

    add_exit(BNUMEN_DIR + "rooms/join_room", "east", 0, 0);

    walls(1);
    floor(1);
    ceiling(1);

    add_prop(ROOM_I_INSIDE, 1);
}

public varargs int
do_advance(string str, string name = TP->query_name())
{
    int     gs = TP->query_stat(SS_RACE),
            dl = TP->query_bnumen_level(),
            diff,
            size = sizeof(DL_EXP_STEPS),
            seed,
            q,
            i,
            nsol;
    mixed   riddles;
    string  house,
            step,
            result;

    if (strlen(str) && (str != "status"))
    {
        NF("Advance what?\n");
        return 0;
    }

    // Don't demand too high race guild stat!
    // Don't demand additional guild stat for becoming Lord or Lady!
    gs =  (gs * 3) / 2;
    if ((gs < dl) && (dl != DL_SUB_LORD))
    {
        diff = (dl - gs) * size / DL_RIDDLE_SCALE;
        diff = MIN(diff, size - 1);
        step = DL_EXP_STEPS[diff];
	/*
	   write("gs = "+gs+", dl = "+dl+", DL_RIDDLE_SCALE = "+
	   DL_RIDDLE_SCALE+", sizeof(DL_EXP_STEPS) = "+sizeof(DL_EXP_STEPS)+"\n");
	   write("diff = "+diff+"\n");
	 */
        NF("You will have to experience "+step+" before you may try to advance!\n");
        return 0;
    }

    if ((CLOCK->query_third_age_days() - Failed[TP->query_real_name()]) <= MIN_DAYS)
    {
        NF("You have failed a test recently!\n"
         + "Come back another day!\n");
        return 0;
    }
    Failed = m_delete(Failed, TP->query_real_name());

    switch (dl)
    {
    case 0..9:
	riddles = RIDDLES_LEV1;
	break;
    case 10..19:
	riddles = RIDDLES_LEV2;
	break;
    case 20..29:
	riddles = RIDDLES_LEV3;
	break;
    case 30..39:
	riddles = RIDDLES_LEV4;
	break;
    case 40..49:
	riddles = RIDDLES_LEV5;
	break;
    case 50..59:
	riddles = RIDDLES_LEV6;
	break;
    case 60..69:
	riddles = RIDDLES_LEV7;
	break;
    case 70..79:
	riddles = RIDDLES_LEV8;
	break;
    case 80..89:
	riddles = RIDDLES_LEV9;
	break;
    case 90..98:
	riddles = RIDDLES_LEV10;
            break;
    case 99:
	riddles = 0;
	
	house = TP->query_bnumen_house();
	if ((member_array(house, BNUMEN_LIBRARY->query_names()) < 0) &&
	    (member_array(house, PUBLIC_LIBRARY->query_names()) < 0))
	{
	    write("You cannot advance further!\n"
		  + BSN("Before you can become "
			+ (TP->query_gender() ? "Lady":"Lord")
			+ " of the House of " + house
			+ " there has to be a history of the House in the "
			+ "Library of the Black Numenoreans!"));
	    return 1;
	}
	
	result = (BNUMEN_MASTER->promote_to_lord(TP->query_name()));
	if (stringp(result))
	{
	    write(result + "Therefore you cannot advance further!\n");
	    return 1;
	}
	
	result = (TP->query_gender() ? "Lady":"Lord")
	    + " of the House of "+house+"!\n";
	write("You are now "+result);
	say(QCTNAME(TP) + " advances to "+result);
	BNUMEN_MASTER->tell_bnumen("\n\t" + TP->query_name()
	       + " becomes "+result, TP->query_name());
	return 1;
	break;
    default:
	riddles = 0;
	break;
    }

    if (!sizeof(riddles))
    {
        write("There are no tests for you to pass.\n");
        return 1;
    }

    seed = dl;
    for (i = 0; i < strlen(name); i++)
        seed += name[i];

    q = random(sizeof(riddles)/2, seed);
    write(BSN(riddles[q*2]));
    log_file("bnumen_rank", TP->query_name() + ": "
      + riddles[q*2] + "\n");
    input_to("answer_riddle", 0, riddles[q*2+1]);
    if ((nsol = sizeof(riddles[q*2+1])) > 1)
        write("(There are "+LANG_WNUM(nsol)+" parts to the answer.)\n"
            + "Your first answer is: ");
    else
        write("You answer: ");

    return 1;
}

public void
answer_riddle(string str, mixed sol)
{
    int     i, j,
            new_level,
            solved = -1;
    string  ss;

    if (!strlen(str))
        return;

    str = LOW(str);

    for (i = 0; i < sizeof(sol); i++)
        for (j = 0; j < sizeof(sol[i]); j++)
        {
            ss = LOW(sol[i][j]);
            if (ss == str)
            {
                solved = i;
                break;
            }
        }

    if (solved == -1)
    {
        write("You failed.\n");
        log_file("bnumen_rank", TP->query_name() + " failed with "
          + "the answer: "+str+" ("+ctime(time())+").\n");
        Failed[TP->query_real_name()] = CLOCK->query_third_age_days();
        return;
    }

    sol = exclude_array(sol, solved, solved);

    if (!sizeof(sol))
    {
        write("You have answered correctly and passed the test!\n"
            + "You have gained status among the bnumen!\n");
        TP->set_bnumen_level(
            MIN(DL_SUB_LORD, (new_level = (TP->query_bnumen_level() + DL_RIDDLE_SCALE))));
        log_file("bnumen_rank", TP->query_name() + " advanced to level "
          + new_level + " on "+ctime(time())+".\n");
        return;
    }

    input_to(&answer_riddle( , sol), 0);
    write("You continue to answer: ");
    return;
}

public varargs int
add_failed(mixed who, int day)
{
    if (!who)
        who = TP;
    if (objectp(who))
        who = who->query_real_name();

    if (!strlen(who))
        return 0;

    who = LOW(who);

    if (!day)
        day = CLOCK->query_third_age_days();

    Failed[who] = day;

    return 1;
}

public void
init()
{
    ::init();

    add_action(do_advance, "advance");
}

