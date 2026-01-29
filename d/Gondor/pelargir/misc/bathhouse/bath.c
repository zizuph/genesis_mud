/*
 * /d/Gondor/pelargir/misc/bathhouse/bath.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * base room for bath, inherited by women's, men's and
 * private bathing rooms
 *
 * N.B. since we intercept the attendant leaving the room in leave_inv()
 *	and return or replace it, we can assume that we always have
 *	an attendant.
 *
 * Modification log:
 *
 * 11/1/03Gwyneth, allowed torque wearers to enter the bath since the
 * torque cannot be removed.
 *
 */

#pragma strict_types


inherit	"/d/Gondor/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h";
#include "bath.h"

static object	Attendant;
static int	Attendant_gender = -1;	 /* -1, G_MALE or G_FEMALE */
static string	Room_dir;	/* direction of this room from entry */

/* prototypes in order of appearance */
public void		create_bath();
nomask void		create_gondor();
public void		reset_room();
public void		restore_attendant();
public void		init();
public int		check_sitting();
public void		leave_inv(object ob, object dest);
public void		enter_inv(object ob, object from);
public string		exa_tubs();
public string		exa_lather();
public int		do_enter(string arg);
public varargs void	do_sit_msgs(object pl, string prep, string name,
				    int definite = 1);
public int		do_stand(string arg);
public int		do_bathe(string arg);
public void		do_stand_msgs(object pl, string name);
public int		do_rinse(string arg);
public int		do_soak(string arg);
public int		do_splash(string arg);
public int		do_dry(string str);
public string		show_subloc(string subloc, object pl,
				    object for_obj);
public mixed		no_theft(object tp);
public mixed		no_fights(object tp);
public void		wrong_gender(object tp);
public int		take_tub(string arg);
public void		set_attendant_gender(int g);
public int		query_attendant_gender();
public object		query_attendant();



/*
 * Function name:	create_bath
 * Description	:	configure your bath here.
 *
 * create_gondor() will likely do most of the set up.
 * create_bath() needs to handle exits, attendant gender,
 * room long, and items specific to this room (if any).
 */
public void
create_bath()
{
} /* create_bath */

/*
 * Function name:	create_gondor
 * Description	:	set up the common bath stuff
 */
nomask void
create_gondor()
{
    FIX_EUID;		/* will be cloning attendants, soap, towels, ... */

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 100);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_MAGIC, 1);
//    add_prop(ROOM_M_NO_MAGIC_ATTACK, no_fights);
//    add_prop(ROOM_M_NO_ATTACK, no_fights);
//    add_prop(ROOM_M_NO_STEAL, no_theft);

    create_bath();

    add_chair(TUB_NAME,
	"[down] [in] [the] [roomy] [wooden] [bath] " +
	"'tub' / 'bathtub' / 'tubs' / 'bathtubs'", 20, "in", 0, 1);
    try_item( ({ "roomy wooden tubs", "wooden tubs", "roomy tubs",
    	"roomy wooden bathtubs", "wooden bathtubs", "roomy bathtubs",
	"tubs", "bathtubs", "roomy wooden tub", "wooden tub", "roomy tub",
    	"roomy wooden bathtub", "wooden bathtub", "roomy bathtub",
	"tub", "bathtub", "large tubs", "large tub", "large wooden tubs",
	"large wooden tub", }),
	exa_tubs);

    try_item( ({ "stone floor", "floor" }),
	BSN("Most of the floor between the tubs is covered with " +
	    "brown mats. Adjacent to each tub, the floor is left " +
	    "clear to expose gratings set into the underlying stone."));
    try_item( ({ "brown mats", "brown mat", "rough-textured brown mats",
	"rough-textured brown mat", "mat", "mats", }),
	BSN("Rough-textured brown mats cover the floor. They " +
	    "appear to be fairly absorbent, and provide secure " +
	    "footing for bare wet feet."));
    try_item( ({ "underlying stone", "grey stone", "stone" }),
	BSN("Grey stone, with a slightly rough surface, is visible " +
	    "around the gratings in the floor."));
    try_item( ({ "slightly rough surface", "rough surface", 
	"surface of stone", "stone surface", }),
	BSN("The surface of the stone has been left slightly rough, " +
	    "no doubt to lessen the chances of someone falling."));
    try_item( ({ "grating", "gratings", }),
	"Gratings are set into the stone floor beside each tub.\n");
    try_item( ({ "steaming hot water", "steaming water", "hot water",
	"bath water", "bathwater", "water" }),
	"Each tub is filled with steaming hot water.\n");
    try_item( ({ "soapy lather", "lather", "froth", "bubbles",
	"froth of bubbles", }),
	exa_lather);
    try_item( ({ "moisture", "plaster wall", "plaster walls", "wall",
	"walls", }),
	BSN("The cream-coloured plaster walls are faintly beaded " +
	    "with moisture from the baths."));
    try_item( ({ "ceiling" }),
	BSN("The ceiling is of plaster, painted the same creamy " +
	    "white as the walls."));
    try_item( ({ "creamy surface", "smooth plaster", "plaster surface",
	"surface of plaster", "creamy plaster", "plaster" }),
	BSN("The plaster is very smooth. No cracks or bumps " +
	    "mar its creamy surface."));
    try_item( ({ "surfaces", "surface", }),
	BSN("The surface of the stone floor is slightly rough, " +
	    "while the surface of the plaster is very smooth."));

    reset_room();

} /* create_gondor */
 
 
/*
 * Function name:	reset_room
 * Description	:	create attendant
 */
public void
reset_room()
{
    /* using our own restore_attendant(), rather than clone_npc(),
     * because we have to do special setup
     */
    if (!objectp(Attendant))
    {
	restore_attendant();
    }
    if (!objectp(present(BASKET_NAME)))
    {
	clone_object(BASKET_FILE)->move(TO);
    }
    if (!objectp(present(POT_NAME)))
    {
	clone_object(POT_FILE)->move(TO);
    }
} /* reset_room */


/*
 * Function name:	restore_attendant
 * Description	:	clone (if necessary) an attendant for the bath
 *			or return existing attendant here.
 */
public void
restore_attendant()
{
    if (!objectp(Attendant))
    {
	Attendant = clone_object(ATTENDANT_FILE);
	if (Attendant_gender == G_FEMALE ||
	    Attendant_gender == G_MALE)
	{
	    Attendant->set_gender(Attendant_gender);
	}
	else
	{
	    Attendant->set_gender(random(2));
	}
	Attendant->configure();
    }
    if (ENV(Attendant) != TO)
    {
	Attendant->move_living("away", TO);
    }
} /* restore_attendant */


/*
 * Function name:	init
 * Description	:	add all the verbs
 */
public void
init()
{
    ::init();

    if (!interactive(TP))
    {
	/* npcs who work in the baths should be clean :-) */
	TP->add_prop(PLAYER_I_BATH, I_AM_DRY_AND_CLEAN);
	TP->add_subloc(WET_SUBLOC, (BATH_DIR + "bath"));
    }

    /* add the chair verbs ourselves, so we can check for worn/wielded
     * objects first
     */
    add_action(do_enter, "enter");
    add_action(do_enter, "sit");
    add_action(do_stand, "stand");
    add_action(do_stand, "rise");
    add_action(do_stand, "leave");
    add_action(do_stand, "out");

    add_action(no_hide,  "hide");
    if (TP->query_wiz_level())
    {
	add_action(no_hide, "invis");
    }

    add_action(do_bathe,  "wash");
    add_action(do_bathe,  "clean");
    add_action(do_bathe,  "bathe");
    add_action(do_bathe,  "soap");
    add_action(do_bathe,  "lather");
    add_action(do_bathe,  "scrub");
    add_action(do_rinse,  "rinse");
    add_action(do_soak,   "soak");
    add_action(do_soak,   "relax");
    add_action(do_soak,   "loll");
    add_action(do_soak,   "sink");
    add_action(do_splash, "splash");
    add_action(do_dry,    "dry");
    add_action(do_dry,    "towel");


    /* to get something more interesting than
     * "The tub cannot be taken."
     */
    add_action(take_tub, "take");
    add_action(take_tub, "get");
    add_action(take_tub, "pick");

} /* init */


/*
 * Function name:	check_sitting
 * Description	:	mask parent to force them to leave tub first.
 *			also divest them of any soap/towels.
 * Returns	:	0 if exit is ok, 1 if are in tub
 */
public int
check_sitting()
{
    object	*inv, *stuff, ob;
    int		s, *res;
    string	tmpstr;

    if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
    {
	write("You should leave the tub and dry off first.\n");
	return 1;
    }
    s = TP->query_prop(PLAYER_I_BATH);
    if (s == I_AM_WET_AND_DIRTY ||
	s == I_AM_WET_AND_CLEAN)
    {
	TP->catch_msg(QCTNAME(Attendant) + " hurries across the room " +
	    "to help you dry off.\n");
	say(QCTNAME(Attendant) + " hurries across the room " +
	    "to help " + QTNAME(TP) + " dry off.\n");
	if (s == I_AM_WET_AND_CLEAN)
	{
	    TP->add_prop(PLAYER_I_BATH, I_AM_DRY_AND_CLEAN);
	}
	else
	{
	    TP->add_prop(PLAYER_I_BATH, I_AM_DRY_AND_DIRTY);
	}
    }
    if (sizeof(inv = deep_inventory(TP)))
    {
	s = sizeof(stuff = filter(inv, &->id(TOWEL_NAME)));
	if (s)
	{
	    tmpstr = (s == 1 ? "towel" : "towels");
	    WRITE("You toss your " + tmpstr + " into the basket.");
	    SAY(" tosses " + POSSESSIVE(TP) + " " + tmpstr +
		" into the basket.");
	    if (!objectp(ob = present(BASKET_NAME, TO)))
	    {
		stuff->remove_object();
	    }
	    res = stuff->move(ob);
	    while (s-- > 0)
	    {
		if (res[s] != 0)
		{
		    /* move for this towel failed -- nuke it */
		    stuff[s]->remove_object();
		}
	    }
	}
	s = sizeof(stuff = filter(inv, &->id(SOAP_NAME)));
	if (s)
	{
	    WRITE("You drop your soap in the copper pot.");
	    SAY(" drops " + POSSESSIVE(TP) + " soap in the copper pot.");
	    if (!objectp(ob = present(POT_NAME, TO)))
	    {
		stuff->remove_object();
	    }
	    res = stuff->move(ob);
	    while (s-- > 0)
	    {
		if (res[s] != 0)
		{
		    /* move for this soap failed -- nuke it */
		    stuff[s]->remove_object();
		}
	    }
	}
    }
    return 0;
} /* check_sitting */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to handle people leaving from tub,
 *			recover from attendant leaving
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    string vb;

    ::leave_inv(ob, dest);
    ::leave_inv_room_chairs(ob, dest);

    if (!interactive(ob))
    {
	if (ob == Attendant)
	{
	    if ((vb = QVB) != "Clean" &&
		vb != "Destruct" &&
		vb != "destruct" &&
		vb != "update")
	    {
		set_alarm(3.0, 0.0, restore_attendant);
	    }
	}
	return;
    }
} /* leave_inv */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to have attendant pick up soap
 *			and towels
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (objectp(ob) &&
	(ob->id(SOAP_NAME) ||
	 ob->id(TOWEL_NAME)))
    {
	set_alarm(3.0, 0.0, &Attendant->pick_up(ob, from));
    }
} /* enter_inv */


/*
 * Function name:	exa_tubs
 * Description	:	VBFC for the tubs
 * Returns	:	string -- the description
 */
public string
exa_tubs()
{
    return BSN("The wooden tubs, each large enough to hold one " +
	"person comfortably, are filled with hot water.") + 
	sitting_on_chair(TUB_NAME, this_player(), 0, 0);
} /* exa_tubs */


/*
 * Function name:	exa_lather
 * Description	:	VBFC for the lather
 * Returns	:	string -- the description
 */
public string
exa_lather()
{
    object	*soapy;
    int		s;

    if (TP->query_prop(PLAYER_I_BATH) == I_AM_SOAPY)
    {
	return "You are covered with soapy lather.\n";
    }
    soapy = filter(FILTER_PLAYERS(all_inventory(TO)), 
		&operator(==)(I_AM_SOAPY) @ &->query_prop(PLAYER_I_BATH));
    if ((s = sizeof(soapy)))
    {
	TP->catch_msg(QCTNAME(soapy[random(s)]) +
	    " is covered with soapy lather.\n");
	return "";
    }
    return "You find no " + query_exa_arg() + ".\n";
} /* exa_lather */


/*
 * Function name:	do_enter
 * Description	:	transform "enter tub" to "sit in tub",
 *			check for worn/wielded items
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_enter(string arg)
{
    string	worn_held;
    object	*worn, *weapons;
    int         i;

    if (!strlen(arg) ||
        !parse_command(LOW(arg), ({}),
		       "[down] [in] [one] [of] [the] [a] [roomy] [wooden] " +
		       "[bath] 'tub' / 'bathtub' / 'tubs' / 'bathtubs'"))
    {
	if (QVB == "enter")
	{
	    NF0("Enter what?\n");
	}
	NF0("Sit where?\n");
    }
    if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
    {
	NF0("You are already sitting in one of the wooden tubs.\n");
    }
    /* nothing we can do about people wearing/wielding after entering
     * the bath.
    */
    if (strlen(worn_held = TP->show_held(TP)))
    {
	write("You cannot bathe while you " + worn_held[4..]);
	return 1;
    }
    worn = TP->query_clothing(-1);
    for (i = sizeof(worn) - 1; i >= 0; i--)
    {
        if (MASTER_OB(worn[i]) != "/d/Emerald/torque/torque")
        {
            worn_held = TP->show_worn(TP);
            write("You cannot bathe while you " + worn_held[4..]);
            return 1;
        }
    }
    /* show_held() shows only held, not wielded, so do extra check */
    if (sizeof(weapons = TP->query_weapon(-1)))
    {
	write("You cannot bathe while you are wielding the " +
	    COMPOSITE_WORDS(weapons->short()) + ".\n");
	return 1;
    }

    return do_sit("in tub");
} /* do_enter */


/*
 * Function name:	do_sit_msgs
 * Description	:	do the you-sit and foo-sits msgs
 * Arguments	:	object pl -- the person who's sitting
 *				(unused .. pl == TP)
 *			string prep -- the preposition
 *			string name -- the name of the chair
 *			string definite -- if set, use definite article
 */
public varargs void
do_sit_msgs(object pl, string prep, string name, int definite = 1)
{
    string	plname;

    write("You sit down in a roomy wooden tub.\n");
    SAY(" sits down in a roomy wooden tub.");

    switch (TP->query_prop(PLAYER_I_BATH))
    {
    case I_AM_DRY_AND_DIRTY:
    	TP->add_prop(PLAYER_I_BATH, I_AM_WET_AND_DIRTY);
	break;
    case I_AM_DRY_AND_CLEAN:
    	TP->add_prop(PLAYER_I_BATH, I_AM_WET_AND_CLEAN);
	break;
    /* all others are ok as is */
    }

    plname = OB_NAME(TP);

    Attendant->command("emote hurries across the room with a " +
	"bucket of hot water.");
    TP->catch_msg(QCTNAME(Attendant) + " pours the hot water " +
	"into your tub.\n");
    say(QCTNAME(Attendant) + " pours the hot water into " +
	QTNAME(TP) + "'s tub.\n");
    Attendant->command("say to " + plname + 
	" There, that should be nice and warm now.");

    if (!objectp(present("soap", TP)))
    {
	clone_object(SOAP_FILE)->move(Attendant, 1);
	/* we blithely ignore the possibility of 'give' failing */
	Attendant->command("give soap to " + plname);
    }

    Attendant->command("smile " + plname);
    Attendant->command("emote returns to " + 
	POSSESSIVE(Attendant) + " post by the door.");

} /* do_sit_msgs */


/*
 * Function name:	do_stand
 * Description	:	mask parent so "leave tub" behaves like
 *			"stand up".
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_stand(string arg)
{
    string	vb = QVB;
    if (vb == "out" ||
	(vb == "leave" &&
	 strlen(arg) &&
         parse_command(LOW(arg), ({}),
		      "[the] [roomy] [wooden] [bath] " +
		      "'tub' / 'bathtub' / 'tubs' / 'bathtubs'")))
    {
	arg = "";
    }
    return ::do_stand(arg);
} /* do_stand */


/*
 * Function name:	do_stand_msgs
 * Description	:	do the you-stand and foo-stands msgs
 * Arguments	:	object pl -- the person who's standing
 *			string name -- the name of the chair
 *
 * roll our own you-stand msgs.
 *
 */
public void
do_stand_msgs(object pl, string name)
{
    pl->catch_msg("You step, dripping wet, from the tub and stand over " +
	"the adjacent grating.\n");
    tell_room(TO, 
	QCTNAME(pl) + " steps, dripping wet, from the tub and stands " +
	"over the adjacent grating.\n", pl);

    if (pl->query_prop(PLAYER_I_BATH) == I_AM_SOAPY)
    {
	pl->catch_msg(QCTNAME(Attendant) +
	    " hurries over with a bucket of hot water.\n" +
	    QCTNAME(Attendant) + " pours the water over you, " +
	    "rinsing off any traces of soap.\n");
	tell_room(TO,
	    QCTNAME(Attendant) + " hurries to " + QTNAME(pl) +
	    " with a bucket of hot water.\n" +
	    QCTNAME(Attendant) + " pours the water over " +
	    QTNAME(pl) + 
	    ", rinsing off any traces of soap.\n", pl);
	pl->add_prop(PLAYER_I_BATH, I_AM_WET_AND_CLEAN);
    }
    if (QVB != "rinse" &&
	!objectp(present("towel", pl)))
    {
	Attendant->give_towel(pl);
    }
} /* do_stand_msgs */


/*
 * Function name:	do_bathe
 * Description	:	respond to attempts to bathe
 *			(really handled by the soap object, but
 *			 fall back to here in case they drop the soap)
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_bathe(string arg)
{
    if (objectp(present(SOAP_NAME, TP)))
    {
	/* soap will have handled the verbs, so the only way
	 * we get here is if they're not in a tub, and soap
	 * will already have done the notify_fail().
	 */
	return 0;
    }

    if (TP->query_prop(LIVE_S_SITTING) != TUB_NAME)
    {
	NF0("You cannot " + QVB + " until you enter a tub.\n");
    }
    NF0("You cannot " + QVB + " without soap.\n");
} /* do_bathe */

/*
 * Function name:	do_rinse
 * Description	:	respond to attempts rinse off soap
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
do_rinse(string arg)
{
    if (strlen(arg))
    {
	arg = LOW(arg);
    }
    else
    {
	arg = "me";
    }

    /* rinse off, rinse off the soap, rinse the soap off me,
     * rinse myself off, ... 
     */
    if (parse_command(arg, ({ }),
	"[the] [soap] 'off' / 'me' / 'myself' / '" + 
	TP->query_real_name() + "' [off] [the] [soap] [me] / [myself]"))
    {
	if (TP->query_prop(LIVE_S_SITTING) != TUB_NAME)
	{
	    NF0("You must enter one of the tubs before you " +
		"can rinse yourself.\n");
	}
	if (TP->query_prop(PLAYER_I_BATH) != I_AM_SOAPY)
	{
	    NF0("You don't need to rinse ... there is " +
		"not a speck of soap on your body.\n");
	}
	do_stand_msgs(TP, TP->query_name());
	write("You sit back down in the tub.\n");
	SAY(" sits back down in the tub.");
	return 1;
    }
    NF0("Rinse yourself, perhaps?\n");
} /* do_rinse */


/* 
 * Function name:	do_soak
 * Description	:	respond to attempts to soak in the tub
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
do_soak(string arg)
{
    int		tmp;
    string	poss;
    if (strlen(arg))
    {
	arg = LOW(arg);
	/* "soak me" doesn't really parse, but since "bathe me"
	 * and "rinse me" work, lets allow it
	 */
	if (arg == "me" ||
	    arg == "myself" ||
	    arg == TP->query_real_name())
	{
	    arg = "in tub";
	}
    }
    else
    {
	arg = "in tub";
    }

    /* soak in tub/water, ... */
    if (parse_command(arg, ({ }),
	"[down] 'in' [the] [roomy] [wooden] [bath] [warm] [hot] " +
	"'tub' / 'bathtub' / 'tubs' / 'bathtubs' / 'water'"))
    {
	if (TP->query_prop(LIVE_S_SITTING) != TUB_NAME)
	{
	    notify_fail("You must enter one of the tubs before you " +
		"can soak.\n");
	    return 0;
	}
	tmp = random((QVB != "sink") ? 4 : 2);
	poss = POSSESSIVE(TP);
	WRITE( ({
	    "You slide down in the tub until only your head is above " +
		"water. The heat seems to soften your very bones.",
	    "You sink deeply into the steaming hot water. Ahhhhh.",
	    "You loll in the tub, your chin just clearing the surface, " +
		"and let the hot water soak your cares away.",
	    "You relax in the tub and let the steaming water work its magic.",
	    })[tmp] );
	SAY( ({
	    " slides down in the tub until only " + poss +
		" head is above water.",
	    " sinks deeply into the steaming hot water.",
	    " lolls in the hot water, " + poss + 
		" chin just clearing the surface.",
	    " relaxes in the steaming water.",
	    })[tmp] );
	return 1;
    }
    NF0(CAP(QVB) + " in the tub, perhaps?\n");
} /* do_soak */


/* 
 * Function name:	do_splash
 * Description	:	respond to attempts to splash water around
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
do_splash(string arg)
{
    string	tmpstr;
    object	*target;
    int		s;

    if (TP->query_prop(LIVE_S_SITTING) != TUB_NAME)
    {
	NFN0("You can't splash from out here. Perhaps if " +
	    "you entered a tub ...");
    }

    if (!strlen(arg) ||
	(arg = LOW(arg)) == "water" ||
        arg == "me" ||
	arg == "myself" ||
	arg == TP->query_real_name())
    {
	s = random(3);
	write( ({
		"You splash happily in your tub.\n",
		"You splash water high in the air, like a " +
		    "miniature geyser.\n",
		"You splash around in the tub.  A good bit of "+
		    "water lands on the floor.\n",
		})[s]);
	SAY( ({
		" splashes happily in " + POSSESSIVE(TP) +
		    " tub.",
		" splashes water high in the air, like a " +
		    "miniature geyser.",
		" splashes around in " + POSSESSIVE(TP) +
		    " tub.  A good bit of water lands on the floor.",
		})[s]);
	return 1;
    }

    if (!parse_command(arg, all_inventory(TO),
		       "[water] [on] / [at] %l", target))
    {
	    NF0("Splash whom?\n");
    }

    target = NORMAL_ACCESS(target, 0, 0);
    if (!(s = sizeof(target)))
    {
	NF0("Splash whom?\n");
    }
    if (s > 1)
    {
	NF0("You can't splash that many people at once.\n");
    }

    TP->catch_msg("You splash water at "+QTNAME(target[0])+".\n");
    target[0]->catch_msg(QCTNAME(TP)+" splashes water at you.\n");
    say(QCTNAME(TP)+" splashes water at "+QTNAME(target[0])+".\n", 
	({ TP, target[0] }) );
    return 1;
} /* do_splash */


/*
 * Function name:	do_dry
 * Description	:	respond to attempts to dry
 *			(really handled by the towel object, but
 *			 fall back to here in case they drop the towel)
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_dry(string arg)
{
    if (objectp(present(TOWEL_NAME, TP)))
    {
	/* towel will have handled the verbs, so the only way
	 * we get here is if they're not wet or if the towel is soaked.
	 * the towel will already have done the notify_fail().
	 */
	return 0;
    }
    NF0("You cannot " + QVB + " without a towel.\n");
} /* do_dry */


/*
 * Function name:	show_subloc
 * Description	:	generate "foo is dripping wet" msg
 *			for living's desc.
 * Arguments	:	string subloc -- the subloc
 *			object pl -- the player
 *			object for_obj -- who's doing the looking
 * Returns	:	string -- the "is sitting" msg
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    int		bathprop;
    string	name,
		desc;

    if (pl->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return ::show_subloc(subloc, pl, for_obj);
    }

    if (subloc == SITTING_S_SUBLOC &&
	pl->query_prop(LIVE_S_SITTING))
    {
	if (for_obj != pl)
	{
	    return capitalize(pl->query_pronoun()) + 
		" is sitting in a " + TUB_NAME + ".\n";
	}
	return "You are sitting in a " + TUB_NAME + ".\n";
    }

    if (subloc != WET_SUBLOC)
    {
	return pl->show_subloc(subloc, pl, for_obj);
    }

    if ((bathprop = pl->query_prop(PLAYER_I_BATH)))
    {
	switch (bathprop)
	{
	case I_AM_DRY_AND_DIRTY:
	    desc = "in need of a bath.\n";
	    break;
	case I_AM_WET_AND_DIRTY:
	    desc = "dripping wet, but not entirely clean.\n";
	    break;
	case I_AM_SOAPY:
	    desc = "covered with a soapy lather.\n";
	    break;
	case I_AM_WET_AND_CLEAN:
	    desc = "dripping wet and quite clean.\n";
	    break;
	case I_AM_DRY_AND_CLEAN:
	    desc = "quite clean.\n";
	    break;
	}
	if (for_obj != pl )
	{
	    return capitalize(pl->query_pronoun()) + " is " + desc;
	}
	return "You are " + desc;
    }
    return ::show_subloc(subloc, pl, for_obj);
} /* show_subloc */


/*
 * Function name:	no_theft
 * Description	:	evicts thief, remember 'em til next reboot
 * Returns	:	mixed -- int 1 if attendant cannot see the fighter
 *				 	(so they just get default msg).
 *				 string "" -- if attendant can see, all msgs
 *					are written before return.
 */
public mixed
no_theft(object tp)
{
    string	name;
    object	entry_room;

    if (!objectp(tp))
    {
	tp = TP;
    }
    name = tp->query_name();
    ENTRY->short();
    entry_room = find_object(ENTRY);
    (entry_room->query_owner())->add_banned(name, "Thieves");
    if (!CAN_SEE_IN_ROOM(Attendant) ||
	!CAN_SEE(Attendant, tp))
    {
	return 1;
    }
    Attendant->command("glare " + OB_NAME(tp));
    Attendant->command("shout We don't like thieves here, " +
	(tp->query_met(Attendant) ?
	     tp->query_name() : tp->query_nonmet_name())
	    + "!");
    if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
    {
	tell_room(TO,
	    QCTNAME(Attendant) + " drags " + QTNAME(tp) +
		" out of the tub and hustles " + OBJECTIVE(tp) +
		" out of the room.\n", tp);
	tp->catch_msg(QCTNAME(Attendant) +
	    " drags you out of your tub and hustles you out " +
	    "of the bathhouse.\n");
    }
    else
    {
	tell_room(TO,
	    QCTNAME(Attendant) + " hustles " + QTNAME(tp) +
		" out of the room.\n", tp);
	tp->catch_msg(QCTNAME(Attendant) +
	    " hustles you out of the bathhouse.\n");
    }
    tell_room(entry_room,
	QCTNAME(Attendant) + " hustles " + QTNAME(tp) +
	    " through the room and out onto the street.\n");
    tp->move_living("M", OUTSIDE_ENTRY);
    tell_room(ENV(tp),
	QCNAME(tp) +
	" is propelled from the building to the north into the street.\n",
	tp);
    return "";
} /* no_theft */


/*
 * Function name:	no_fights
 * Description	:	evicts fighter, remember 'em til next reboot
 * Returns	:	mixed -- int 1 if attendant cannot see the fighter
 *				 	(so they just get default msg).
 *				 string "" -- if attendant can see, all msgs
 *					are written before return.
 */
public mixed
no_fights(object tp)
{
    string	name;
    object	entry_room;

    if (!objectp(tp))
    {
	tp = TP;
    }
    name = tp->query_name();
    ENTRY->short();
    entry_room = find_object(ENTRY);
    (entry_room->query_owner())->add_banned(name, "Bullies");
    if (!CAN_SEE_IN_ROOM(Attendant) ||
	!CAN_SEE(Attendant, tp))
    {
	return 1;
    }
    Attendant->command("glare " + OB_NAME(tp));
    Attendant->command("shout Hey, no fighting in the baths, " +
	(tp->query_met(Attendant) ?
	     tp->query_name() : tp->query_nonmet_name())
	    + "!");
    tell_room(TO,
	QCTNAME(Attendant) + " hustles " + QTNAME(tp) +
	    " out of the room.\n", tp);
    if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
    {
	tell_room(TO,
	    QCTNAME(Attendant) + " drags " + QTNAME(tp) +
		" out of the tub and hustles " + OBJECTIVE(tp) +
		" out of the room.\n", tp);
	tp->catch_msg(QCTNAME(Attendant) +
	    " drags you out of your tub and hustles you out " +
	    "of the bathhouse.\n");
    }
    else
    {
	tell_room(TO,
	    QCTNAME(Attendant) + " hustles " + QTNAME(tp) +
		" out of the room.\n", tp);
	tp->catch_msg(QCTNAME(Attendant) +
	    " hustles you out of the bathhouse.\n");
    }
    tell_room(entry_room,
	QCTNAME(Attendant) + " hustles " + QTNAME(tp) +
	    " through the room and out onto the street.\n");
    tp->move_living("M", OUTSIDE_ENTRY);
    tell_room(ENV(tp),
	QCNAME(tp) +
	" is propelled into the street.\n", tp);
    return "";
} /* no_fights */


/*
 * Function name:	wrong_gender
 * Description	:	eject person w wrong gender
 * Arguments	:	object pl -- the offending person
 */
public void
wrong_gender(object tp)
{
    if (ENV(tp) != TO ||
	!CAN_SEE_IN_ROOM(Attendant) ||
	!CAN_SEE(Attendant, tp))
    {
	return;
    }
    if (tp->query_wiz_level())
    {
	/* this is the likely case */
	Attendant->command("say Excuse me, " +
	    (tp->query_gender() == G_FEMALE ? "my lady" : "my lord") +
	    ", but you really should not be here.");
	Attendant->command("sigh worriedly");
    }
    else
    {
	Attendant->command("frown " + OB_NAME(tp));
	Attendant->command("say You're in the wrong room, " +
	    tp->query_nonmet_name() + ".");
	tell_room(TO,
	    QCTNAME(Attendant) + " hustles " + QTNAME(tp) +
	    " out of the room.\n", tp);
	tp->catch_msg(QCTNAME(Attendant) +
	    " hustles you out of the room.\n");
	tp->move_living("M", ENTRY);
	tell_room(ENV(tp),
	    QCTNAME(tp) + " arrives from the " + Room_dir +
		" in something of a hurry.\n");
    }
} /* wrong_gender */


/*
 * Function name:	take_tub
 * Description:		respond to attempts to take the tubs
 * Arguments:		string arg -- what they tried for.
 * Returns:		int -- 1 if we handle it, 0 not
 */
public int
take_tub(string arg)
{
    mixed	*targets;
    string	tmpstr,
		vb = QVB;

    if (!strlen(arg))
    {
        return 0;
    }

    /* be sure there's not a tub of butter, or the like,
     * lying in the room
     */
    arg = LOW(arg);
    if (parse_command(arg, ({ }),
	"[roomy] [large] [wooden] [bath] " +
	"'tub' / 'tubs' / 'bathtub' / 'bathtubs'") &&
	!objectp(present("tub", TO)))
    {
	write("   The wooden tub is too heavy.\n");
	return 1;
    }
    return 0;
} /* take_tub */


/* and the one-liners */
public void	set_attendant_gender(int g)	{ Attendant_gender = g; }
public int	query_attendant_gender()	{ return Attendant_gender; }
public object	query_attendant()		{ return Attendant; }
