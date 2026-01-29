/*
 * /d/Gondor/common/guild/gondor/no_theft.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * Prevent theft in the public rooms of the Gondor guildhall.
 * When someone attempts theft, evicts them and makes them
 * an outlaw.
 *
 * To use, inherit this file and in the room create routine, do:
 *	add_prop(ROOM_M_NO_STEAL, no_theft);
 */

#pragma strict_types

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
    
/*
 * Function name:	no_theft
 * Description	:	evicts and outlaws the thief
 * Returns	:	string "" -- all msgs written before return.
 */
public mixed
no_theft(object tp)
{
    string	logmsg,
		name;
    object	to = TO;

    if (!objectp(tp))
    {
	tp = TP;
    }
    name = tp->query_name();
    tell_room(to,
	"A tall muscular ranger arrives.\n"+
	"A young square-faced ranger arrives.\n"+
	"The tall muscular ranger says: We do not permit theft here, "+
	    name+"!\n");
    tell_object(tp, "The rangers escort you from the room.\n");
    tell_room(to, "The rangers escort "+QTNAME(tp)+" from the room.\n", tp);

    FIX_EUID;
    switch (R_OUTLAW->add_outlaw(tp))
    {
    case 1:
	logmsg = name+" was outlawed for attempted theft, "+
	     ctime(time())+".\n";
	break;
    case 0:
	logmsg = "Failed to outlaw "+name+" for attempted theft, "+
		 ctime(time())+".\n\tAlready was an outlaw.\n";
	/* want to be sure wizzies see this */
	write_file((LOG_DIR)+"bugs", "INTERNAL BUG REPORT:\n"+logmsg+"\n");
	break;
    default:
	logmsg = "Failed to outlaw "+name+" for attempted theft, "+
		 ctime(time())+".\n";
	/* want to be sure wizzies see this */
	write_file((LOG_DIR)+"bugs", "INTERNAL BUG REPORT:\n"+logmsg+"\n");
	break;
    }
    write_file(RANGER_LOG, logmsg);
    write_file(STATUS_LOG, logmsg);

    tp->move_living("M", (DRUEDAIN_DIR+"rangerpath3"));
    tell_room(ENV(tp),
	"Two sturdy rangers escort "+QTNAME(tp)+" in, "+
	"then silently depart.\n", tp);
    return "";
} /* no_theft */
