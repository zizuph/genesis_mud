/*
 * Shadow for nails done in Palanthas.
 *
 * Inspired by the excellent nail and eye
 * sublocs in Gelan.
 *
 * Mortis 01.2006
 *
 * Revisions:
 *    Lucius, Aug 2016: Added a property check to the subloc code
 *                      to allow items to be exempt from hiding nails.
 *
 *
 * Armours of type A_HANDS may set the property "_obj_i_show_nails"
 * to a non-zero value and the Palanthas Nails subloc shall not be
 * hidden.  -Lucius
 *
 */
#pragma strict_types

#include <macros.h>
#include <wa_types.h>
#include "../../local.h"

inherit "/std/shadow";

#define NAIL_MASTER		(NOBLE + "spa_nails")
#define NAILSTYLE_PROP		"_obj_i_show_nails"
#define NAILSTYLE_SUBLOC	"nails"
#define NAILSTYLE_SHADOW	(NOBLE + "nails/nails_shadow")
#define NAILSTYLE_CMDSOUL	(NOBLE + "nails/nails_cmdsoul")

mapping length_to_desc = (["chewed-down":"chewed down",
	"long":"long", "moderate":"moderately long",
	"modest":"modestly long",
	"nubby":"nubby",
	"short":"short",
	"trimmed":"trimmed",
	"very-short":"very short",
	"very-long":"very long"]);

mapping style_to_desc = (["bloody":"bloody",
	"brittle":"brittle",
	"broken":"broken",
	"cracked":"cracked",
	"curled":"curled",
	"curling":"curling",
	"curved":"curved",
	"curving":"curving",
	"enameled":"that have been enameled",
	"filed":"filed",
	"glossy":"glossy",
	"glass":"glass",
	"hooked":"hooked",
	"icy":"icy",
	"jagged":"jagged",
	"manicured":"manicured",
	"metallic":"metallic",
	"natural":"natural",
	"painted":"that have been painted",
	"pointed":"pointed",
	"recurved":"recurved",
	"rotting":"with shreds of rotting flesh beneath them",
	"serrated":"serrated",
	"shaded":"shaded",
	"sharpened":"that have been sharpened to a point",
	"sparkling":"that sparkle and shine",
	"splintered":"splintered",
	"straight":"straight",
	"thick":"thick",
	"thin":"thin",
	"torn":"torn",
	"two-toned":"two-toned"]);

mapping colour_to_desc = (["black":"black",
	"onyx":"onyx", "shadowy":"shadowy", "white":"white", "ivory":"ivory",
	"natural":"natural coloured", "copper":"copper", "gold":"gold",
	"silver":"silver", "red":"red", "pink":"pink", "ruby":"ruby",
	"orange":"orange", "yellow":"yellow", "yellowed":"yellowed",
	"green":"green", "emerald":"emerald", "jade":"jade", "blue":"blue",
	"night":"night blue", "opal":"opal", "indigo":"indigo",
	"violet":"violet", "purple":"purple", "bone":"bone",
	"glass":"glass"]);

mapping nail_to_desc = (["nails":"nails",
	"nail-claws":"nail claws",
	"claws":"claws",
	"talons":"talons"]);

string length, style, colour, nail, nailstyle, linearstyle;

void set_length(string l)
{ length = l; }
string query_length()
{ return length; }

void set_style(string s)
{ style = s; }
string query_style()
{ return style; }

void set_nails_colour(string c)
{ colour = c; }
string query_colour()
{ return colour; }

void set_nail(string n)
{ nail = n; }
string query_nail()
{ return nail; }

string query_nailstyle()
{ return nailstyle; }

string query_linear_nailstyle()
{ return linearstyle; }

void
set_nailstyle(string l, string s, string c, string n)
{
	string len, sty, col, nai, art;
	len = length_to_desc[l];
	sty = style_to_desc[s];
	col = colour_to_desc[c];
	nai = nail_to_desc[n];
	art = " a ";
	linearstyle = len + " " + s + " " + col + " " + nai;

	if (parse_command(c, ({}), "'onyx' / 'ivory' / 'orange' / 'emerald' / 'opal' / 'indigo'"))
	{
		art = " an ";
	}

	if (parse_command(s, ({}), "'enameled' / 'painted' / 'sparkling'"))
	{
		nailstyle = len + " " + nai + " " + sty + art + col + " hue";
		return;
	}

	if (parse_command(s, ({}), "'rotting' / 'sharpened'"))
	{
		nailstyle = len + " " + col + " " + nai + " " + sty;
		return;
	}

	if (parse_command(s, ({}), "'glass'"))
	{
		nailstyle = len + " " + col + " " + sty + " " + nai;
		linearstyle = len + " " + col + " " + s + " " + nai;
		return;
	}

	nailstyle = len + " " + sty + " " + col + " " + nai;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    string str = "";

    if (subloc != NAILSTYLE_SUBLOC)
	return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    object gloves = me->query_armour(A_HANDS);

    if (!objectp(gloves) || gloves->query_prop(NAILSTYLE_PROP))
    {
	if (for_obj == me)
	    str = "You have ";
	else
	    str = capitalize(HE(me)) + " has ";

	str += nailstyle + ".\n";
    }
    else if (for_obj == me)
	str = "You have " + nailstyle + " (hidden).\n";

    return str;
}

void
destruct_nail_shadow()
{
	if (member_array(NAILSTYLE_CMDSOUL, shadow_who->query_cmdsoul_list()) > -1)
	{
		shadow_who->remove_cmdsoul(NAILSTYLE_CMDSOUL);
		shadow_who->update_hooks();
	}
	destruct();
}

void
shadow_autoshadow_destruct()
{
	shadow_who->remove_autoshadow(NAILSTYLE_SHADOW);
	destruct_nail_shadow(); 
}

/* Add cmdsoul to player */
void
add_nail_commands()
{
	shadow_who->add_cmdsoul(NAILSTYLE_CMDSOUL);
	shadow_who->update_hooks();
}

private void
configure_nail(string l, string s, string c, string n)
{
    setuid(); 
    seteuid(getuid()); 
    set_length(l);
    set_style(s);
    set_nails_colour(c);
	set_nail(n);

    set_nailstyle(l, s, c, n);
    shadow_who->add_subloc(NAILSTYLE_SUBLOC, TO); 
    add_nail_commands(); 
}


public void
autoload_shadow(mixed arg)
{
    string *args;

    ::autoload_shadow(arg);
    args = explode(arg, ",");

    if (!pointerp(args) || sizeof(args) != 4) {
        set_alarm(1.0, 0.0, shadow_autoshadow_destruct);
        return;
    }

    set_alarm(0.1, 0.0, &configure_nail(args[0], args[1], args[2], args[3])); 
}
