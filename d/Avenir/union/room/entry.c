/*
 * Entry to the Union guildhall
 *  Cirion 032096
 *
 *  Revisions:
 *    Lucius. May 2016: Cleanups and added notification piece.
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

public object gate, nadia, cyrus;


public string
door(void)
{
    if (!present(gate))
	return "";
    else if (gate->query_broken())
	return " A massive black gate lies in ruins on the ground, "+
	    "broken open by some massive force. ";
    else if (gate->query_open())
	return " A massive black metal gate stands open to the "+
	    "east, through which you see a long wide corridor. ";
    else
	return " Rising to the east is a massive black metal gate, its "+
	    "glimmering surface carved with a myriad of tiny, "+
	    "intertwining figures. ";
}

public void
reset_room(void)
{
    /* If the NPC has been slain, then the "union_o_corpse_of_<npc>" */
    /* prop will be set in this room (from the make_corpse())        */
    /* function in NPC + "npc.c". Until the corpse is destroyed,     */
    /* the Union member will not reset.                              */
    if (!nadia)
    {
	if (!objectp(query_prop(UCORPSE_PROP("nadia"))))
	    nadia = clone_here(NPC+"nadia");
    }

    if (!cyrus)
    {
	if (!objectp(query_prop(UCORPSE_PROP("cyrus"))))
	    cyrus = clone_here(NPC+"cyrus");
    }

    if (cyrus && !present(cyrus))
	cyrus->move_living("away", TO);

    if (nadia && !present(nadia))
	nadia->move_living("away", TO);
}

public int
try_west(void)
{
    object who = TP->query_attack();

    if (!interactive(TP))
	return 0;

    if (who != nadia && who != cyrus)
	return 0;

    if (!CAN_SEE(who, TP) || !CAN_SEE_IN_ROOM(who))
	return 0;

    if (random(500) < TP->query_stat(SS_DEX))
	return 0;

    TP->catch_msg(QCTNAME(who) + " blocks your escape.\n");
    say(QCTNAME(who) + " blocks " + QTNAME(TP) + "'s escape.\n");
    return 1;
}

public void
union_room(void)
{
    set_short("before the black gate");
    set_long("Perfectly round and smooth, the tunnel leads "+
	"back into the darkness to the west.@@door@@ "+
	"The floor and walls of the tunnel here seem to "+
	"give off a faint, luminescent glow from "+
	"an indeterminate source.\n");

    add_item(({"wall","walls","tunnel","floor","ground", "ceiling"}),
	"The walls and floor of the tunnel are perfectly smooth, "+
	"formed in an even arc overhead. The tunnel is carved from "+
	"the surrounding rock, and seems to glow with a faint light.\n");
    add_item(({"light","glow","lumiscence"}),
	"The light from the tunnel is very faint, and it "+
	"is impossible to determine its exact source.\n");

    add_exit(L2 + "ut5", "west", try_west);

    add_object(OBJ + "gate_w");
    reset_room();

    /* Outside the gate, allow magic */
    remove_prop(ROOM_M_NO_MAGIC);
}

static void
update_vars(void)	{ gate = present("_union_gate"); }

public void
leave_inv(object who, object dest)
{
    object other;
    string temp = "";

    ::leave_inv(who, dest);

    if (objectp(gate))
	other = environment(gate->query_other_door());

    if ((dest != other) || !query_interactive(who) || IS_MEMBER(who))
	return;

    if (LIST->query_hopeful(who))
	temp = "The Hopeful ";
    else if (FRIEND(who))
	temp = "Friend of the Union ";

    filter(users(), objectp @ &present(TOKEN_ID, ))->catch_tell(
	"A pinging noise emits from your sphere.\n   An image of "+
	LANG_ADDART(who->query_nonmet_name()) +
	" coalesces in your thoughts.\n   "+ temp +
	who->query_cap_name() +" has entered the Halls of Shadow.\n");
}
