/* counrcpt.c: Council reception room. 'Spot' the cylops will keep
 *     people out of the main chambers till the council is ready to
 *     go on line, at which point he will let some people through.
 *     Of course what the council names him is there own affair,
 *     but I have a think for the name Spot. - Serpine, 4-24-95.
 * - Revolt limit changed to 9 due to 16 players voted in last 
 *   election. So half the voters plus 1. This will be done manually
 *   until it can be automated. Damaris@Genesis 11/2006
 * - Added recruitment Overseer - Damaris@Genesis 12/2006
 */
#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include <language.h>
#include <macros.h>
#define LCQN(x) (lower_case((x)->query_name()))

#define REVOLT_LIMIT 9

void
create_room()
{
    set_short("hall of the Overseers");
    set_long("   This vaulted chamber is where the Overseers of the "+
	"Gladiators of Athas can speak with their charges without "+
	"letting them into the private hall to the east. The High "+
	"Overseer can also appoint within this room. A stain "+
	"darkens the floor, a crimson stain.\n"+
        "Within this place you may 'list overseers', or even "+
        "'revolt', though this latter should only be done in the "+
        "case of extreme failure by the Overseers.\n");
    add_item(({"stains", "stain", "floor"}), "Think about it.\n");
    INSIDE
    add_exit(GLAD_ROOM+"stairwy3", "north", 0, 1);
    add_exit(GLAD_ROOM+"counmain", "east", "@@spot_block@@", 1);
}

int
revolt()
{
    string name = TP->query_real_name();

    if (!IS_MEMBER(TP))
    {
        notify_fail("Only Gladiators may stage a revolt!\n");
        return 0;
    }

    if (MANAGER->query_revolter(name))
    {
        notify_fail("You are already revolting as it is!\n");
        return 0;
    }

    if(!QUERY_OVERSEER(TI))
    {
        notify_fail("But there is no High Overseer to revolt against!\n");
        return 0;
    }

    MANAGER->add_revolter(name);
    write("POWER TO THE GLADIATORS!\n\n"+
        "You are now revolting.\n"+
	"You may 'regret' this action later.\n");
    say(QCTNAME(TP)+" joins the revolution against the Overseers!\n");
	
    if (sizeof(MANAGER->query_revolters()) >= REVOLT_LIMIT)
    {
        tell_room(TO, "THE OVERSEERS HAVE BEEN OVERTHROWN!\n");
        MANAGER->overthrow_overseers();
    }
    return 1;
}

int
regret()
{
    string name = TP->query_real_name();

    if(!MANAGER->query_revolter(name))
    {
        notify_fail("But you aren't revolutionary!\n");
        return 0;
    }

    MANAGER->remove_revolter(name);
    write("You are no longer revolutionary.\n");
    say(QCTNAME(TP)+" isn't revolutionary anymore.\n");
    return 1;
}

int
do_list(string str)
{
    string *arr = allocate(4);
    string name = TP->query_real_name();
    int count;

    if (str != "overseers")
	return notify_fail("List what?  The overseers perhaps?\n");

    if ((arr[0] = QUERY_OVERSEER(POS_HIGH)) == 0)
	arr[0] = "Not filled: Perhaps you should apply?";
    if ((arr[1] = QUERY_OVERSEER(POS_INT)) == 0)
	arr[1] = "Not filled: Everyone is a suspect.";
    if ((arr[2] = QUERY_OVERSEER(POS_ARENA)) == 0)
	arr[2] = "Not filled: The arena is silent.";
    if ((arr[3] = QUERY_OVERSEER(POS_REC)) == 0)
	arr[3] = "Not filled: Everyone is a suspect.";	
    write ("\n  The Overseers Currently Consist of\n"+
      "  ===========================================================\n\n"+
      "  High Overseer: "+ capitalize(arr[0]) +"\n\n"+
      "  Internal Overseer: "+ capitalize(arr[1]) +"\n\n"+
      "  Arena Overseer: "+ capitalize(arr[3]) +"\n\n"+
      "  Recruitment Overseer: "+ capitalize(arr[2]) +"\n\n"+
      "  ===========================================================\n");
	   
    if (count = sizeof(MANAGER->query_revolters()))
    {
        write("\nThere " + (count == 1 ? "is " : "are ") +
            LANG_NUM2WORD(count) + " gladiator" + (count == 1 ? "" : "s") +
            " revolting to overthrow the Overseers.\n" );
    }
    if (MANAGER->query_revolter(name))
    {
        write("You are among the revolting gladiators.\n");
    }
    
    return 1;
}
/*
 * This function is for the High Overser to control the lesser overseer
 * positions.  Demote, Appoint, etcetera.
 */
public int
func_lesser(string str)
{
    int slot;
    object who;
    string arg, *arr;

    if (!strlen(str))
	return notify_fail("Usage: lesser <appoint | demote> <name> [position]\n");

    if (sscanf(lower_case(str), "%s %s", str, arg) != 2)
	return notify_fail("Usage: lesser <appoint | demote> <name> [position]\n");

    switch(str)
    {
    case "appoint":
	arr = explode(arg, " ");
	if (sizeof(arr) != 2)
	{
	    str = "Usage: lesser appoint <who> <position>\n";
	    break;
	}

	if ((slot = member_array(arr[1], OVERSLOTS[1..])) == POS_NONE)
	{
	    str = "That is not a valid Lesser Overseer position.\n";
	    break;
	}

        slot++;

	if (strlen(QUERY_OVERSEER(slot)))
	{
	    str = "That Overseer position is already taken.\n";
	    break;
	}
// commented out due to needing wizard intervention to bring mortal to room
// Modified by Damaris@Genesis 01/2005        
//	if (!objectp(who = present(arr[0], environment(TP))))
//	{
//	    str = capitalize(arr[0]) +" is not present.\n";
//	    break;
//	}

	if (!IS_MEMBER(who))
	{
	    str = capitalize(arr[0]) +" is not a Gladiator.\n";
	    break;
	}

	if (QUERY_OVERSEER(who) != POS_NONE)
	{
	    str = capitalize(arr[0]) +" already holds an Overseer "+
	    "position.\n";
	    break;
	}

	if (!ADD_OVERSEER(who->query_real_name(), OVERSLOTS[slot]))
	{
	    str = "An unknown error occured, please make a report.\n";
	    break;
	}

	str = "You appoint '"+ capitalize(arr[0]) +" to the "+
	capitalize(OVERSLOTS[slot]) +" Overseer position.\n";

	WRITE_LOG(LOG_LESSER, TP, ": "+ str);

	tell_object(who, "You have been appointed to the "+
	    capitalize(arr[1]) +" position by "+
	    TP->query_the_name(who) +".\n");

	/* Reset the cuirasse */
	who = present(CUIR_ID, who);
	who->remove_adj(who->query_adj());
	who->configure_cuirasse();
	break;

    case "demote":
	if (!objectp(who = present(arg, environment(TP))))
	{
	    str = capitalize(arg) +" is not present.\n";
	    break;
	}

	if (!IS_MEMBER(who))
	{
	    str = capitalize(arg) +" is not a Gladiator.\n";
	    break;
	}

	if ((slot = QUERY_OVERSEER(who)) == POS_NONE)
	{
	    str = capitalize(arg) +" does not hold an Overseer "+
	    "position.\n";
	    break;
	}

	if (!REM_OVERSEER(who->query_real_name()))
	{
	    str = "An unknown error occured, please make a report.\n";
	    break;
	}

	if (who == TP)
	{
	    str = "You retire your position of High Overseer.\n";
	}
	else
	{
	    str = "You demote '"+ capitalize(arg) +"' from the "+
	    capitalize(OVERSLOTS[slot]) +" Overseer position.\n";
	    tell_object(who, TP->query_The_name(who) +" has stripped "+
	      "you of your Overseer position.\n");
	}

	WRITE_LOG(LOG_LESSER, TP, ": "+ str);

	/* Reset the cuirasse */
	who = present(CUIR_ID, who);
	who->remove_adj(who->query_adj());
	who->configure_cuirasse();
	break;

    default:
	str = "Usage: lesser <appoint | demote> <name> [position]\n";
	break;
    }

    if (strlen(str))
	write(str);
    return 1;
}

int
spot_block()
{
/* just block non-overseers. -R
    if((GLAD_ROOM+"counmain")->query_can_enter(TP->query_name()) || this_player()->query_wiz_level())
	return 0;
*/

    if(TP->query_wiz_level() || QUERY_OVERSEER(TP) != POS_NONE)
        return 0;

    write("Suddenly an area of shadow in the eastern chambers "+
        "seems to take form: A long chitinous shape with two ... no ... "+
        "three sets of gigantic mandibles. Your mind tells you that "+
        "you must fear it: You have no choice in the matter. But as "+
        "you back away the fear subsides and the five yard greyish "+
        "mass again becomes one with the darkness.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("do_list", "list");
    add_action("revolt", "revolt"); 
    add_action("regret", "regret");
}
