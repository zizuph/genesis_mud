/*
 * /d/Gondor/pelargir/misc/bathhouse/bath.h
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * definitions for the baths
 */

#ifndef _BATH_DEFS
#define	_BATH_DEFS

#define BATH_DIR	(PELAR_DIR + "misc/bathhouse/")

#define	OWNER_FILE	(BATH_DIR + "npc/kadin")
#define	ATTENDANT_FILE	(BATH_DIR + "npc/attendant")

#define	BASKET_FILE	(BATH_DIR + "obj/basket")
#define	BASKET_NAME	"_pelargir_towel_basket"
#define	POT_FILE	(BATH_DIR + "obj/pot")
#define	POT_NAME	"_pelargir_soap_pot"
#define	SOAP_FILE	(BATH_DIR + "obj/soap")
#define	SOAP_NAME	"_pelargir_bath_soap"
#define	TOWEL_FILE	(BATH_DIR + "obj/towel")
#define	TOWEL_NAME	"_pelargir_bath_towel"

#define	MAX_ITEMS	10	/* max soaps/towels in pot/basket */

#define	ENTRY		(BATH_DIR + "entry")
#define	OUTSIDE_ENTRY	(PELAR_DIR + "streets/beacon04")

/* for msgs re sitting in tub */
#define	TUB_NAME	"roomy wooden tub"

/* hard to know what price to charge for restoring fatigue.
 * ranger rest spell uses ingredient valued at 390 to restore fatigue
 * of 30 plus bonus of 0 - 15, depending on SS_OCCUP of caster.
 * there's a small (30) mana cost, too.
 *
 * soooo .. charging 'em 420 and restoring 30 fatigue points seems 
 * reasonable.
 */
#define	FATIGUE_RESTORED	30
#define	BATH_PRICE_STRING	"35 silver coins"
#define	BATH_PRICE_COPPERS	420
#define	PAY_ME \
    "Just pay me and you'll soon be chin-deep in a nice hot tub."


/* player props & sublocs */
#define	PLAYER_I_PAID	"_player_i_paid"

#define	PLAYER_I_BATH	"_player_i_bath"
/* values for PLAYER_I_BATH */
#define I_AM_DRY_AND_DIRTY	1	/* haven't started yet */
#define I_AM_WET_AND_DIRTY	2	/* wet, but haven't applied soap */
#define I_AM_SOAPY		3	/* have applied soap */
#define I_AM_WET_AND_CLEAN	4	/* have applied soap and rinsed */
#define I_AM_DRY_AND_CLEAN	5	/* all done*/

#define	MIN_TIP			1200
#define	PLAYER_I_TIPPED		"_player_i_tipped"

#define WET_SUBLOC		"wet_subloc"

#ifndef LIVE_I_DIRTY
#define	LIVE_I_DIRTY		"_live_i_dirty"
#endif

#define	KALAD_DIRTY_SUBLOC	"_kalad_dirty_subloc"
#define	GRUNT_STINK		"grunts_stink"
#define	GRUNT_STINK_SUBLOC	"stink_object_subloc"
#define	SIRITH_MUD		(SIRITH_DIR+"sirith/obj/mud")

#endif /* !_BATH_DEFS */
