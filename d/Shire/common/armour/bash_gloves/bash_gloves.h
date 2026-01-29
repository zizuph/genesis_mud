/*******************************************************************\
| BASH_GLOVES.H                                                     |
\*******************************************************************/

// We want to use strict typechecking because it seems a cool
// thing to do :-). We also use the save binary pragma to make
// sure the shadow object, which is created and destroyed every
// time the gloves get worn and removed, is not recompiled often.

#pragma strict_types
#pragma save_binary

//-------------------------------------------------------------------

#ifndef FALSE
#define FALSE		0
#define TRUE		1
#endif

// These macros have the same names as the standard macros used
// to query names of objects, except they start with X rather
// than Q. They are to be used when the message is sent to
// a single object and therefore does not need to use
// VBFC functions to be displayed correctly.

#define QOBJ(o)			QMET ("query_objective", (o))
#define XOBJ(m,o)		o->query_objective (m)
#define QPOS(o)			QMET ("query_possessive", (o))
#define XPOS(m,o)		o->query_possessive (m)
#define QPNOUN(o)		QMET ("query_pronoun", (o))
#define XPNOUN(m,o)		o->query_pronoun (m)

#define XTNAME(m,o)		o->query_the_name (m)
#define XCTNAME(m,o)		o->query_The_name (m)
#define XTPNAME(m,o)		o->query_the_possessive_name (m)
#define XCTPNAME(m,o)		o->query_The_possessive_name (m)

//-------------------------------------------------------------------

#define BG_DIR			"/d/Shire/common/armour/bash_gloves"

#define BG_SHADOW_FILE  BG_DIR + "/bash_gloves_shadow"

//-------------------------------------------------------------------

// We use the same name for the stun object as the huge mithril
// club did back when it was created. This makes sure an enemy
// does not get stunned multiple times when fighting a team
// that uses both the club and the gloves (and possibly
// other items that stun using the same stun object
// name). So please resist the temptation to fix
// the typo in the name :-) ...

#define BG_STUN_NAME		"_senceless_by_club_"
#define BG_STUN_FILE		"/std/paralyze"

//-------------------------------------------------------------------
