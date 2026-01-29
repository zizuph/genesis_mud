/*
 * - Manager.c
 *
 * This file and all functions contained herein were re-written from
 * scratch as were all the council functions in room/counmain.c.
 *
 * For further info, refer to the header of that file.
 *
 * NOTE: There is NO security in this file to prevent malicious wizards
 *       from making direct calls to manipulate things.
 *       
 *   --= Lucius Kane
 */
#pragma strict_types
#pragma save_binary
#pragma no_clone
#pragma no_inherit

#include "defs.h"
#include "guruquest.h"

#include <macros.h>
#include <std.h>
#include <time.h>

#ifndef SECURITY
#define SECURITY "/secure/master"
#endif

#define SAVE	save_object(MASTER)
#define MLC(x)	(x = lower_case(x))

void check_activity();

private mapping punish = ([]), brutus = ([]), charge = ([]), guruquest = ([]);
private string *overseers = allocate(OVERSEERS);


public int
query_prevent_shadow()	{ return 1; }


private void
create()
{
    setuid(); seteuid(getuid());
    restore_object(MASTER);

    set_alarm(600.0, 3600.0, &check_activity());
}

varargs mixed
query_overseer(mixed pos)
{
    if (intp(pos))
    {
	if (pos < 0 || pos >= OVERSEERS)
	    return POS_NONE;

	return overseers[pos];
    }

    if (objectp(pos))
	pos = pos->query_real_name();

    if (stringp(MLC(pos)))
    {
	if (SECURITY->query_guild_is_master("gladiator", pos))
	    return POS_WIZ;

	return member_array(pos, overseers);
    }
    return POS_NONE;
}

int
remove_overseer(string who)
{
    int pos;

    if (!strlen(who))
	return 0;

    switch(pos = query_overseer(who))
    {
    case POS_NONE:
	/* Fallthru */
    case POS_WIZ:
	return 0;
	break; /* not reached */

    case POS_HIGH:
	overseers = allocate(OVERSEERS);
	break;

    default:
	overseers[pos] = 0;
	break;
    }

    SAVE; return 1;
}

int
add_overseer(string who, string slot)
{
    int pos;
    string tmp;

    if (!strlen(who) || !strlen(slot))
	return 0;

    MLC(who); MLC(slot);
    pos = member_array(slot, OVERSLOTS);
    tmp = query_overseer(pos);

    /* Is the position already occupied? */
    if (strlen(tmp))
	return 0;

    /* Dont add if they already hold the position */
    if (pos == POS_NONE || tmp == who)
	return 0;

    /* Do some cleanup */
    if (pos == POS_HIGH)
	overseers = allocate(OVERSEERS);
    else
	remove_overseer(who);

    /* Assign and save */
    overseers[pos] = who;
    SAVE; return 1;
}

int
add_punish(mixed who, int type)
{
    if (objectp(who))
	who = who->query_real_name();

    if (!strlen(who) || !type)
	return 0;

    if (punish[MLC(who)] & type)
	return 0;

    punish[who] |= type;
    SAVE; return 1;
}

int
remove_punish(mixed who, int type)
{
    if (objectp(who))
	who = who->query_real_name();

    if (!strlen(who) || !type)
	return 0;

    if (!(punish[MLC(who)] & type))
	return 0;

    if (!(punish[who] ^= type))
	punish = m_delete(punish, who);

    SAVE; return 1;
}

mixed
query_punish(mixed who, int type)
{
    if (objectp(who))
	who = who->query_real_name();

    if (who == "all")
    {
	string *arr = m_indexes(secure_var(punish));
	int sz = sizeof(arr);

	while(sz--)
	{
	    if (query_punish(arr[sz], type) == 0)
		arr[sz] = 0;
	}
	return sort_array(arr -= ({ 0 }));
    }

    return punish[MLC(who)] & type;
}

int
remove_member(string who)
{
    MLC(who);
    punish = m_delete(punish, who);
    charge = m_delete(charge, who);

    SAVE; return 1;
}

int
add_member(string who) { }

void
snuff_gladiator(object poor_glad)
{
    if(find_object(GLAD_ROOM+"counmain"))
    {
	tell_room(GLAD_ROOM+"counmain", 
	  "\nThe terrible beast in the corner stirs, waving its "+
	  "antennas around furiously. Then its form shimmers and melts, "+
	  "flowing like water into the shadows.\n\n");
    }

    tell_room((E(poor_glad)), "A shiver goes up your spine.\n"+
      "Suddenly the shadows twist and flow into the form of a gray "+
      "behemoth, a 5 meter centipede with a single compound eye and "+
      "three sets of vicious mandibles.\n\n");

    tell_room((E(poor_glad)),
      "A cylops hits "+QCTNAME(poor_glad)+" with its first set of fangs!\n"+
      "A cylops hits "+QCTNAME(poor_glad)+" with its second set of fangs!\n"+
      "A cylops hits "+QCTNAME(poor_glad)+" with its third set of fangs!\n",
      poor_glad);

    poor_glad->catch_msg(
      "A cylops hits you with its first set of fangs!\n"+
      "A cylops hits you with its second set of fangs!\n"+
      "A cylops hits you with its third set of fangs!\n");

    tell_room((E(poor_glad)), "\nThe horrible insectoid, its "+
      "hunger apparently sated, once more becomes one with the "+
      "shadows and vanishes.\n\n");

    poor_glad->heal_hp(-poor_glad->query_hp());
    poor_glad->do_die(TO);

    if(find_object(GLAD_ROOM+"counmain"))
    {
	tell_room(GLAD_ROOM+"counmain",
	  "The shadows contort, revealing the dreaded cylops. The "+
	  "five yard insect stretches and moves back to its corner. As it "+
	  "coils up you note that its three sets of mandibles have fresh "+
	  "reddish stains.\n\n");
    }
}

public int
add_brutus_attacker(mixed who)
{
    if (objectp(who))
	who = who->query_real_name();

    if (!strlen(who))
	return 0;

    if (pointerp(brutus[MLC(who)]))
	brutus[who] += ({ ctime(time()) });
    else
	brutus[who]  = ({ ctime(time()) });

    SAVE; return 1;
}

public int
remove_brutus_attacker(mixed who)
{
    if (objectp(who))
	who = who->query_real_name();

    if (!strlen(who) || !brutus[MLC(who)])
	return 0;

    brutus = m_delete(brutus, who);
    SAVE; return 1;
}

public mixed
query_brutus_attacker(mixed who)
{
    if (objectp(who))
	who = who->query_real_name();

    if (!strlen(who))
	return secure_var(brutus);

    if (!brutus[who])
	return 0;

    return secure_var(brutus[who]);
}

public int
set_charge_desc(mixed who, string what)
{
    if (objectp(who))
	who = who->query_real_name();

    if (!strlen(who))
	return 0;

    charge[MLC(who)] = what;
    SAVE; return 1;
}

public string
query_charge_desc(mixed who)
{
    string rval;

    if (objectp(who))
	who = who->query_real_name();

    if (!strlen(who))
	return "<error>";

    rval = charge[MLC(who)];
    return (strlen(rval) ? rval : "charge");
}

public int
guru_quest(string who)
{
    return guruquest[lower_case(who)] & GOT_QUEST;
}

public int
guru_quest_done(string who)
{
    return guruquest[lower_case(who)] == GURU_DONE;
}

public int
guru_quest_clear(string who)
{
    if (!guruquest[MLC(who)])
	return 0;

    guruquest = m_delete(guruquest, who);
    SAVE; return 1;
}

public int
guru_quest_set(string who, int val)
{
    if (!strlen(who) || !val)
	return 0;

    if (guruquest[MLC(who)] & val)
	return 0;

    guruquest[who] |= val;

    write_file(GLAD_LOG +"glad_guru", ctime(time()) +": "+
      capitalize(who) +" got bit "+ val +" giving total "+
      guruquest[who] +".\n");

    SAVE; return 1;
}

/*
 * Check if the High Overseer is active enough to remain,
 * if he isn't remove him to start a new vote.
 */
void
check_activity()
{
    string who;
    int last_login;

    if (who = query_overseer(POS_HIGH))
    {
        last_login = file_time(PLAYER_FILE(who) + ".o");

        if (!last_login)
        {
            remove_overseer(who);
            write_file(LOG_DEMOTE + "demote",
                ctime(time()) + ": Demoted " + who + " who is " +
                "deleted.\n");
            return;
        }
        
        if ((time() - last_login) > DEMOTE_TIME)
        {
            remove_overseer(who);
            write_file(LOG_DEMOTE,
                ctime(time()) + ": Demoted " + who + " after " +
                CONVTIME(time() - last_login) + "\n");
        }
    }
}
   
