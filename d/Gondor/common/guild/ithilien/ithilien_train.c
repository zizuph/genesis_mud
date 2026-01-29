/*
 * /d/Gondor/common/guild/ithilien/ithilien_train
 *
 * Traininghall of the Rangers of Ithilien
 *
 * The train hall of Ithilien Company
 * Modified by Olorin, 30-Oct-1993
 *
 * 26 August 1998, Gnadnar: make real curtain (door) so can
 *	block access to training recess if officers are using it 
 *	for privacy, add some items, tidy up.
 * 13 October 1998, Gnadnar: determine curtain status every time
 *	long is called, rather than storing it and only updating
 *	when it changes. less efficient, but the stored strings
 *	were sometimes getting out of sync. :-(
 *   
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/lib/ranger_train.c";

#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* A few definitions */
#define COMPANY_NO   	2   /* The Ithilien Company is no 2 */
#define	CHAMBER		(RANGER_ITH_DIR + "erockchamber")

/* prototypes */
public void	create_trainhall();
public string	long_func();
public void	reset_room();
public void	leave_inv(object ob, object to);
public int	filter_officers(object pl);
public void	check_mablung_leave();
public void	check_mablung_return();
public string	exa_plaque();
public string	exa_curtain(string arg);
public string	exa_chamber();
public void	change_my_desc(string desc, object ob);
public void	gs_hook_already_meditate();
public void	gs_hook_start_meditate();
public void	gs_hook_rise();

static object	Mablung,
		Curtain;
static int	Is_tied,
		Mablung_alarm;
static string	Tied_by;

/*
 * Function name:	create_trainhall
 * Description	:	set up the hall
 */
public void 
create_trainhall() 
{ 
    object curtain;

    FIX_EUID;

    company_no = COMPANY_NO;

    set_short("Rangers of Ithilien Training Chamber");
    set_long(long_func);
    add_exit((RANGER_ITH_DIR+"erockchamber"), "west", 0, 0);

    add_item( ({ "wooden plaque", "plaque" }), exa_plaque());
    add_item( ({ "opening", "exit", }), &exa_curtain("curtain"));
    add_item( ({ "main chamber", "chamber" }), exa_chamber);

    add_item("banner", BSN(
       "The rich fabric of the banner is deep green, with a soft nap. "+
       "In its center is embroidered a silvery rising moon, the emblem "+
       "of Ithilien."));
    add_item( ({ "rich fabric", "fabric" }), BSN(
	"The deep green fabric of the banner is soft, with a nap like "+
	"velvet."));
    add_item( ({ "silvery rising moon", "silvery moon", "rising moon", "moon",
	"emblem", }), BSN(
	"The Ithilien moon, embroidered in silver, seems almost "+
	"to have a pale light of its own."));
    add_item( "floor", BSN(
	"The floor is stone, bare and clean underfoot."));
    add_item( ({ "rough wall", "rough walls", "wall", "walls", }), BSN(
	"The walls are bare, rough stone. A green and silver banner hangs "+
	"on the inner wall, and a grey curtain partly covers an opening "+
	"in the outer."));
    add_item( ({ "north wall", "south wall", }), BSN(
	"The wall is simply stone, rough and unadorned."));
    add_item( ({ "inner wall", "east wall" }), BSN(
	"Little of the inner wall can be seen behind the banner."));
    add_item( ({ "outer wall", "west wall", }), &exa_curtain("wall"));
    add_item( ({ "roof", "ceiling" }), 
	"Grey stone curves close overhead.\n");
    add_item( ({ "grey stone", "rough stone", "stone", }), BSN(
	"The stone is dark grey and roughly surfaced. Clearly, no effort "+
	"has been expended on adornment."));
    add_item( ({ "smooth heavy grey cloth", "smooth cloth", "heavy cloth",
	"grey cloth", "cloth", }),
	BSN("The grey cloth has a smooth, dull finish. It looks "+
	    "as if it is quite heavy."));
    add_item( ({ "leather", "strips", "strips of leather", 
	"braided cord", "cord" }),
	BSN("The cord is just a few strips of leather braided together."));


    add_cmd_item( ({ "wooden plaque", "plaque" }), "read", exa_plaque());

    /* we deliberately ignore the problem of players who touch
     * things while wearing gauntlets
     */
    add_cmd_item( ({ "nap", "banner", "rich fabric", "fabric" }),
	({ "touch", "feel", }),
	"The banner is very soft to the touch.\n");
    add_cmd_item( ({ "silvery rising moon", "silvery moon", "rising moon",
	"moon", "emblem", }),
	({ "touch", "feel", }),
	BSN("The silvery moon is cool and smooth beneath your fingers."));
    add_cmd_item( ({ "smooth heavy grey cloth", "smooth cloth", "heavy cloth",
	"grey cloth", "cloth", "grey cloth curtain", "grey curtain",
	"cloth curtain", "curtain", }),
	({ "touch", "feel", }),
	BSN("The grey cloth slides easily across your hand."));

    reset_room();
} /* create_trainhall */


/*
 * Function name:	long_func
 * Description	:	VBFC for the room desc
 * Returns	:	string -- the description
 */
public string
long_func()
{
    string curtain_extra = "A grey cloth curtain is drawn "+
		           "across the west wall of the recess, ";

    if (objectp(Curtain))
    {
	if (Curtain->query_open())
	{
	    curtain_extra = "A grey cloth curtain partly covers "+
	        "the opening to the main chamber west, ";
	}
	else if (Curtain->query_locked())
	{
	    curtain_extra = "A grey cloth curtain is tied "+
		"across the west wall of the recess, ";
	}
    }

    return(BSN(
	"This small recess, tucked at the back of the rock chamber, has "+
	"rough walls and a low sloping ceiling. "+curtain_extra+
	"and a green banner embroidered with a silver rising moon "+
	"hangs on the inner wall. A wooden plaque is tacked to the wall "+
	"to the left of the curtain, and a poster to the right."));
} /* long_func */


/*
 * Function name:	reset_room
 * Description	:	replace trainer
 */
public void
reset_room()
{
    string *cnames;
    Mablung = clone_npc(Mablung, (RANGER_ITH_DIR+"npc/mablung"));

    if (!objectp(Curtain))
    {
	Curtain = clone_object(RANGER_ITH_DIR + "curtain2");
	Curtain->add_name("ith_curtain");
	Curtain->move(TO);
	cnames = Curtain->query_door_name();
	remove_item(cnames);
	add_item(cnames, &exa_curtain("curtain"));
	Is_tied = 0;
	Tied_by = 0;
    }

} /* reset_room */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to untie curtain if departing
 *			object is last officer present
 * Arguments	:	object ob -- the departing object
 *		:	object to -- its destination
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (Is_tied &&
	interactive(ob) &&
	objectp(Curtain) &&
	!sizeof(filter(all_inventory(TO), filter_officers)))
    {
	Curtain->do_unlock_door("");
	Curtain->query_other_door()->do_unlock_door("");
    }
} /* leave_inv */


/*
 * Function name:	filter_officers
 * Description	:	filter ranger officers
 * Arguments	:	object pl -- the person to test
 * Returns	:	1 if pl is an officer, 0 if not
 */
public int
filter_officers(object pl)
{
    string name = pl->query_real_name();
    return (interactive(pl) &&
	    (R_COUNCIL->is_officer(name) ||
	     pl->query_wiz_level()));
} /* filter_officers */


/*
 * Function name:	check_mablung_leave
 * Description	:	when officer ties the curtain, have
 *			mablung offer to wait outside
 */
public void
check_mablung_leave()
{
    object pl;

    Mablung_alarm = 0;
    if (Is_tied &&
	strlen(Tied_by) &&
	objectp(Mablung) &&
	ENV(Mablung) == TO &&
	objectp(pl = present(Tied_by, TO)))
    {
	/* ok, we fake the untie-tie sequence here. dubious,
	 * but it avoids a lot of overhead, and it makes
	 * it work for wizards, and it gives pl a much
	 * better idea that s/he retied the curtain than
	 * that measly "Ok." from /std/door.c does.
	 */
	Mablung->command("say I'll just wait outside until you're finished.");
	Mablung->command("bow "+Tied_by);
	Mablung->command("emote unties the grey cloth curtain.");
	Mablung->command("emote opens the grey cloth curtain just enough "+
	    "to slip past.");
	tell_room(CHAMBER,
	    "The grey cloth curtain seems to loosen slightly.\n");
	Mablung->move_living("west", CHAMBER);
	tell_room(CHAMBER, "The grey cloth curtain falls shut.\n");
	tell_room(TO, "The grey cloth curtain falls shut.\n");
	tell_object(pl, "You tie the grey cloth curtain shut again.\n");
	SAY(" ties the grey cloth curtain shut.");
	tell_room(CHAMBER,
	    "The grey cloth curtain is pulled more tightly shut.\n");
    }
} /* check_mablung_leave */


/*
 * Function name:	check_mablung_return
 * Description	:	when someone unties the curtain, 
 *			mablung should return
 */
public void
check_mablung_return()
{
    Mablung_alarm = 0;
    if (!Is_tied &&
	objectp(Mablung) &&
	ENV(Mablung) != TO)
    {
	Mablung->command("east");
	if (ENV(Mablung) != TO)
	{
	    Mablung->move_living("away", TO);
	}
    }
} /* check_mablung_return */


/*
 * Function name:	exa_plaque
 * Description	:	gen text for the plaque
 * Returns	:	string -- the text on the plaque
 */
public string
exa_plaque()
{
    return BSN(
	"Here you may <meditate> to set your stat-preferences, and <learn> "+
	"or <improve> your skills. You may also <list guilds> to discover "+
	"information about the guilds of which you are a member. The poster "+
	"shows the level to which you can train skills here if you are "+
	"one of the Rangers of Ithilien.");
} /* exa_plaque */


/*
 * Function name:	exa_curtain
 * Description	:	VBFC for the curtain and west wall
 * Arguments	:	string arg -- "curtain" or "wall"
 * Returns	:	string -- the description
 */
public string
exa_curtain(string arg)
{
    string	desc = "A curtain of smooth heavy grey cloth, with a "+
		       "braided cord attached to one edge, covers the "+
		       "west wall of the recess. It reaches to the floor, "+
		       "and appears fairly heavy.";

    if (objectp(Curtain))
    {
	if (Curtain->query_open())
	{
	    desc = "A curtain of smooth heavy grey cloth, with a "+
		   "braided cord attached to one edge, partly covers "+
		   "the exit from the recess. It reaches to the floor, "+
		   "and appears fairly heavy.";
	}
	else if (Curtain->query_locked())
	{
	    desc = "A curtain of smooth heavy grey cloth, tied with "+
		   "a braided cord, covers the west wall of the recess. "+
		   "It reaches to the floor, and appears fairly heavy.";
	}
    }
    if (arg == "wall")
    {
	desc += " A plaque and a poster hang on either side of the curtain.";
    }
    return BSN(desc);
} /* exa_curtain */


/*
 * Function name:	exa_chamber
 * Description	:	VBFC for the chamber
 * Returns	:	string -- the description
 *
 * N.B. this is only called if the chamber is visible.
 */
public string
exa_chamber()
{
    string	desc;
    object	*in_chamber;

    if (!objectp(Curtain) ||
	!Curtain->query_open())
    {
	return BSN("The curtain is completely drawn, blocking "+
		   "all view of the main chamber.");
    }

    desc = BSN("Beyond the partly drawn curtain lies "+
	"a dim, low-roofed rock chamber.");

    CHAMBER->short();
    in_chamber = FILTER_LIVE(all_inventory(find_object(CHAMBER)));
    switch (sizeof(in_chamber))
    {
    case 0:
    	break;
    case 1:
	desc += BSN(in_chamber[0]->query_Art_name(TP)+
	        " is standing in the chamber.");
	break;
    default:
	desc += BSN(capitalize(COMPOSITE_LIVE(in_chamber))+
	        " are standing in the chamber.");
	break;
    }
    return desc;
} /* exa_chamber */


/*
 * Function name:	change_my_desc
 * Description	:	mask parent to change locked state
 * Arguments	:	string desc -- the new desc
 *			object ob -- the object that changed
 */
public void
change_my_desc(string desc, object ob)
{

    if (!objectp(ob))
    {
	ob = previous_object();
    }
    if (ob->id("ith_curtain"))
    {
	if (desc == "locked")
	{
	    Is_tied = 1;
	    Tied_by = TP->query_real_name();
	    if (TP != Mablung)
	    {
		if (Mablung_alarm)
		{
		    remove_alarm(Mablung_alarm);
		}
		Mablung_alarm = set_alarm(5.0, 0.0, check_mablung_leave);
	    }
	}
	else
	{
	    Is_tied = 0;
	    Tied_by = 0;
	    if (TP != Mablung)
	    {
		if (Mablung_alarm)
		{
		    remove_alarm(Mablung_alarm);
		}
		Mablung_alarm = set_alarm(10.0, 0.0, check_mablung_return);
	    }
	}
    }
    else
    {
	::change_my_desc(desc, ob);
    }
} /* change_my_desc */



/*
 * Function name:	gs_hook_already_meditate
 * Description	:	write a already-meditating msg
 */
public void
gs_hook_already_meditate() 
{
    WRITE(
	"You are already sitting by the green banner, meditating. If you "+
	"wish to finish, you can do so by typing 'rise'. ");
} /* gs_hook_already_meditate */


/*
 * Function name:	gs_hook_start_meditate
 * Description	:	write a start-meditating msg
 */
public void
gs_hook_start_meditate()
{  
    WRITE("Slowly you sit down by the green banner, and "+
	"close your eyes. As you clear your mind for everything else "+
	"and concentrate solely on your mind, a feeling of great ease and "+
	"self control falls upon you. You find yourself able to <estimate> "+
	"your different preferences and <set> them at your own desire. "+
	"Just <rise> when you are done meditating. ");
} /* gs_hook_start_meditate */


/*
 * Function name:	gs_hook_rise
 * Description	:	write a end-meditating msg
 */
public void
gs_hook_rise() 
{
    WRITE("As if ascending from a great depth, you rise to the surface "+
	"of your consciousness. You exhale and feel very relaxed as "+
	"you get up and shake your head to clear it again. ");
} /* gs_hook_rise */
