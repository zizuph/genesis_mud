/*
 * /d/Ansalon/guild/society/obj/faerie_find.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * My thanks to Shiva for helping with this.
 *
 * An object to deal with finding a faerie friend.
 * Controls ability to timeout an input_to() request,
 * as well as allowing multiple people to find a
 * faerie at one time, as the variables will be
 * stored in each instance of this object, rather
 * than the faerie room.
 *
 * Coded by Gwyneth on December 6, 2000
 * Some functions borrowed from Shiva's input_to object.
 *
 * Modification log:
 */
inherit "/std/object";

#include <const.h>
#include <options.h>
#include <stdproperties.h>
#include "../guild.h"

#define FAERIE_TREE (KGROOM + "faerie_tree")
#define TIMEOUT 300.0

/* Positions in the gDetails array */
#define ADJ1P    0
#define ADJ2P    1
#define HLENGTHP 2
#define HCOLOURP 3
#define HSTYLEP  4
#define ETYPEP   5
#define ECOLOURP 6
#define NAMEP    7
#define ADORNP   8
#define GENDERP  9

/* Global Variables */
static string *gHairLengthArr = ({ "waist length", "hip length", "short",
		"very short", "shoulder length", "knee length" });
static string *gHairColourArr = ({ "ruby red", "bright red", "auburn",
		"red-brown", "violet red", "bright orange", "golden brown",
		"golden blonde", "platinum blonde", "dark blonde",
		"light blonde", "chocolate brown", "dark brown",
		"light brown", "bright yellow", "yellow blonde",
		"golden yellow", "bright green", "emerald green",
		"moss green", "light green", "jade green",
		"bright blue", "sapphire blue", "ocean blue",
		"light blue", "violet blue", "indigo blue",
		"bright purple", "amethyst purple", "light purple",
		"strawberry blonde", "grey white", "silver grey",
		"metallic silver", "metallic gold", "jet black",
		"raven black", "chestnut brown", "flame red",
		"crimson red", "ginger", "silvery", "snow white" });
static string *gHairStyleArr = ({ "tied into pigtails", "swirled in a bun",
		"hanging loose", "pulled with a pony tail",
		"styled with two braids", "styled in a top-knot", 
		"parted on the side", "sticking straight up", 
		"spiked in a mohawk", "combed down in bangs",
		"bald in the middle", "burned into wisps", "curly", 
		"tied into a french braid", "feathered back into layers", 
		"obscuring the left eye", "draped over the left shoulder", 
		"loosely braided", "tightly braided", 
		"crimped along the side", "loose curled", 
		"styled into dreadlocks", "bushido style", 
		"styled in a flat top", "parted on the left", 
		"parted on the right", "parted in the middle", 
		"spiked like a porcupine", "swept back", "tied back", 
		"very wild and unkempt", "windswept", 
		"obscuring the right eye", "draped over the right shoulder", 
		"straight", "tightly curled", "wavy" });
static string *gEyeTypeArr = ({ "intense", "mischievous", "deep", "sensual",
			"puppy dog", "innocent", "carefree", "thoughtful",
			"wise", "bright", "smiling", "friendly", "flashy",
			"sparkly",  });
static string *gEyeColourArr = ({ "sea green", "emerald green", "ocean blue",
		"sapphire blue", "bright green", "bright blue",
		"sky blue", "dark blue", "forest green", "deep brown",
		"dark brown", "pure black", "brown-green", "blue-green",
		"blue-grey", "rainbow" });
static string *gFaerieAdj1Arr = ({"child-like", "childish", "energetic", 
		"tidy-looking", "well-groomed", "bouncy", "long-armed", 
		"short-armed", "thin-armed", "chubby", "curvaceous", 
		"delicate", "lean", "light", "petite", "skinny", "slender", 
		"slight", "slim", "small", "spindly", "thin", "tiny", 
		"voluptuous", "wide-hipped", "willowy", "beige-skinned", 
		"black-skinned", "bronze-skinned", "brown-skinned", 
		"copper-skinned", "dark-skinned", "dusky", "ebony-skinned",
		"green-skinned", "ivory-skinned", "light-skinned", 
		"olive-skinned", "pale", "peach-skinned", "pink-skinned", 
		"red-skinned", "smooth-skinned", "tanned", "tawny", 
		"white-skinned", "yellow-skinned", "orange-skinned", 
		"blue-skinned", "silver-skinned", "gold-skinned", 
		"purple-skinned", "dimpled", "freckle-faced", "oval-faced", 
		"pointy-eared", "red-cheeked", "sweet-faced", "round-faced", 
		"square-faced", "thin-faced", "long-fingered", "nimble-fingered", 
		"quick-fingered", "round-fingered",
		"short-fingered", "stubby-fingered", "adventurous", 
		"captivating", "friendly", "hypnotic", "innocent", "lucky", 
		"meek", "mischievous", "mysterious", "strange", "long-legged", 
		"short-legged", "skinny-legged", "square-jawed", 
		"wide-mouthed", "big-nosed", "pointy-nosed", "pert-nosed", 
		"red-nosed", "hook-nosed", "hawkish-nosed", "radiant", 
		"distinguished", "glowing", "sparkly", "shimmering"});
static string *gValidExit = ({ "q", "x", "exit", "quit", "~q", "stop" });

/* Placeholder global variables */
static string gAdj1, gAdj2;
static string gHairLength, gHairColour, gHairStyle;
static string gEyeType, gEyeColour;
static int gGender;
static int gAlarm;

/* Prototypes */
public int find_gender(string str);
public int eye_type(string str);
public int eye_colour(string str);
public int hair_length(string str);
public int hair_colour(string str);
public int hair_style(string str);
public int faerie_adj1(string str);
public int faerie_adj2(string str);

public void
create_object()
{
	set_name(({"finder", "_faerie_find_object_"}));
	set_short("faerie finder");
	set_long("This item shouldn't be visible. Please " +
		"submit a bug report if it is.\n");
	set_no_show();
	add_prop(OBJ_M_NO_DROP, 1);
	add_prop(OBJ_M_NO_GIVE, 1);
	add_prop(OBJ_M_NO_SELL, 1);
	add_prop(OBJ_M_NO_GET, 1);
	add_prop(OBJ_I_WEIGHT, 0);
	add_prop(OBJ_I_VOLUME, 0);
	add_prop(OBJ_I_VALUE, 0);
}

public void
abort_find()
{
	environment()->catch_tell("Perhaps another time then. You cease " +
		"your search for a faerie.\n");
	set_alarm(0.1, 0.0, &remove_object());
	return;
}

public void
leave_env(object from, object to)
{
	::leave_inv(from, to);

	set_alarm(0.1, 0.0, &abort_find());
}

public string
format_output(string *output)
{
	int size, i, scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
	string *output2, formatted = "";

	size = sizeof(output);

	if (!size)
	{
		return "";
	}
	
	output = sort_array(output);

	output2 = ({ output[0] });
	for (i = 1, size = sizeof(output); i < size; i++)
	{
		if (member_array(output[i], output2) == -1)
		{
			output2 += ({ output[i] });
		}
	}

	output = output2;

	scrw = ((scrw >= 40) ? (scrw - 3) : 77);
	formatted += (sprintf("%-*#s\n", scrw, implode(output, "\n")));
	return ("\n" + formatted + "\n");
}

public void
begin_find(object who)
{
	set_this_player(who);
	write("\nYou look all around for a faerie to befriend. You " +
		"see male faeries and female faeries. Which would " +
		"you like to look for? Or 'stop'? ");
	input_to(find_gender);
}

public int
find_gender(string str)
{
	if (!strlen(str))
	{
		write("\nYou aren't very decisive. Do you want to 'stop' " +
			"your search, or do you want to find a " +
			"male faerie or a female faerie? ");
		input_to(find_gender);
		return 1;
	}
	
	if (lower_case(str) == "stop")
	{
		abort_find();
		return 1;
	}

	switch(lower_case(str))
	{
	case "f":
	case "female":
		gGender = G_FEMALE;
		break;
	case "m":
	case "male":
		gGender = G_MALE;
		break;
	default:
		write("\nYou only find male and female faeries. " +
			"Do you want to 'stop' your search, or " +
			"do you want to find " +
			"a male faerie or a female faerie? ");
		input_to(find_gender);
		return 1;
	}

	remove_alarm(gAlarm);
	gAlarm = set_alarm(TIMEOUT, 0.0, &abort_find());
	write("\nThe eyes of the faeries vary widely.\n" +
		"As you look around at the faeries, you see the following:\n" + 
		format_output(gEyeTypeArr) +
		"What type of eyes do you wish to look for? Or 'stop'? ");
	input_to(eye_type);
	return 1;
}

public int
eye_type(string str)
{
	if (!strlen(str))
	{       
		write("\nYou aren't very decisive.\n" + 
			format_output(gEyeTypeArr) +
			"Which type of eyes do you wish to look for? Or 'stop'? ");
		input_to(eye_type);
		return 1;
	}

	if (lower_case(str) == "stop")
	{
		abort_find();
		return 1;
	}

	if (member_array(lower_case(str), gEyeTypeArr) == -1)
	{
		write("\nThat's not an option.\n" +
			format_output(gEyeTypeArr) +
			"Which type of eyes do you wish to look for? " +
			"Or 'stop'? ");
		input_to(eye_type);
		return 1;
	}
	else
	{
		remove_alarm(gAlarm);
		gAlarm = set_alarm(TIMEOUT, 0.0, &abort_find());
		gEyeType = lower_case(str);
		write("\nThe eyes of the faeries vary widely.\n" +
			"As you look around at the " +
			"faeries, you see that the colours include " +
			"the following:\n" + 
			format_output(gEyeColourArr) +
			"Which colour of eyes do you wish to look for? " +
			"Or 'stop'? ");
		input_to(eye_colour);
		return 1;
	}
}

public int
eye_colour(string str)
{
	if (!strlen(str))
	{       
		write("\nYou aren't very decisive.\n" +
			format_output(gEyeColourArr) +
			"Which colour eyes do you wish to look for? " +
			"Or 'stop'? ");
		input_to(eye_colour);
		return 1;
	}

	if (lower_case(str) == "stop")
	{
		abort_find();
		return 1;
	}

	if (member_array(lower_case(str), gEyeColourArr) == -1)
	{
		write("\nThat's not an option.\n" +
			format_output(gEyeColourArr) +
			"Which colour eyes do you wish to look for? " +
			"Or 'stop'? ");
		input_to(eye_colour);
		return 1;
	}
	else
	{
		remove_alarm(gAlarm);
		gAlarm = set_alarm(TIMEOUT, 0.0, &abort_find());
		gEyeColour = lower_case(str);
		write("\nThe hair length of the faeries varies widely.\n" +
			"As you look around " +
			"at the faeries, you see that the lengths are:\n" +
			format_output(gHairLengthArr) +
			"Which length of hair do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_length);
		return 1;
	}
}

public int
hair_length(string str)
{
	if (!strlen(str))
	{       
		write("\nYou aren't very decisive.\n" +
			format_output(gHairLengthArr) +
			"Which hair length do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_length);
		return 1;
	}

	if (lower_case(str) == "stop")
	{
		abort_find();
		return 1;
	}

	if (member_array(lower_case(str), gHairLengthArr) == -1)
	{
		write("\nThat's not an option.\n" +
			format_output(gHairLengthArr) +
			"Which hair length do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_length);
		return 1;
	}
	else
	{
		remove_alarm(gAlarm);
		gAlarm = set_alarm(TIMEOUT, 0.0, &abort_find());
		gHairLength = lower_case(str);
		write("\nThe hair colour of the faeries varies widely.\n" +
			"As you look around " +
			"at the faeries, you see that the colours are:\n" +
			format_output(gHairColourArr) +
			"Which colour hair do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_colour);
		return 1;
	}
}

public int
hair_colour(string str)
{
	if (!strlen(str))
	{       
		write("\nYou aren't very decisive.\n" +
			format_output(gHairColourArr) +
			"Which hair colour do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_colour);
		return 1;
	}

	if (lower_case(str) == "stop")
	{
		abort_find();
		return 1;
	}

	if (member_array(lower_case(str), gHairColourArr) == -1)
	{
		write("\nThat's not an option.\n" +
			format_output(gHairColourArr) +
			"Which hair colour do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_colour);
		return 1;
	}
	else
	{
		remove_alarm(gAlarm);
		gAlarm = set_alarm(TIMEOUT, 0.0, &abort_find());
		gHairColour = lower_case(str);
		write("\nThe hair styles of the faeries vary widely.\nAs " +
			"you look around at the faeries, you see " +
			"that the hairstyles include:\n" + 
			format_output(gHairStyleArr) +
			"Which hairstyle do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_style);
		return 1;
	}
}

public int
hair_style(string str)
{
	if (!strlen(str))
	{       
		write("\nYou aren't very decisive.\n" +
			format_output(gHairStyleArr) +
			"Which hair style do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_style);
		return 1;
	}

	if (lower_case(str) == "stop")
	{
		abort_find();
		return 1;
	}

	if (member_array(lower_case(str), gHairStyleArr) == -1)
	{
		write("\nThat's not an option.\n" +
			format_output(gHairStyleArr) +
			"Which hair style do you wish to look for? " +
			"Or 'stop'? ");
		input_to(hair_style);
		return 1;
	}
	else
	{
		remove_alarm(gAlarm);
		gAlarm = set_alarm(TIMEOUT, 0.0, &abort_find());
		gHairStyle = lower_case(str);
		write("\nThe overall appearance of the faeries " + 
			"vary widely.\nAs you look around " +
			"at the faeries, you see the following kinds " +
			"of faeries:\n" + format_output(gFaerieAdj1Arr) + 
			"Which kind of appearance do you wish to look for? " +
			"Or 'stop'? ");
		input_to(faerie_adj1);
		return 1;
	}
}

public int
faerie_adj1(string str)
{
	if (!strlen(str))
	{       
		write("\nYou aren't very decisive.\n" +
			format_output(gFaerieAdj1Arr) +
			"Which appearance do you wish to look for? " +
			"Or 'stop'? ");
		input_to(faerie_adj1);
		return 1;
	}

	if (lower_case(str) == "stop")
	{
		abort_find();
		return 1;
	}

	if (member_array(lower_case(str), gFaerieAdj1Arr) == -1)
	{
		write("\nThat's not an option.\n" +
			format_output(gFaerieAdj1Arr) + 
			"Which appearance do you wish to look for? " +
			"Or 'stop'? ");
		input_to(faerie_adj1);
		return 1;
	}
	else
	{
		remove_alarm(gAlarm);
		gAlarm = set_alarm(TIMEOUT, 0.0, &abort_find());
		gAdj1 = lower_case(str);
		write("\nThe overall appearance of the faeries vary " +
			"widely in more ways than one.\nAs you look around " +
			"at the faeries, you see the following types of " + 
			"faeries:\n" + format_output(gFaerieAdj1Arr) +
			"Which other appearance do you wish to look for? " +
			"Or 'stop'? ");
		input_to(faerie_adj2);
		return 1;
	}
}

public int
faerie_adj2(string str)
{
	if (!strlen(str))
	{       
		write("\nYou aren't very decisive.\n" +
			format_output(gFaerieAdj1Arr) +
			"Which appearance do you wish to look for? " +
			"Or 'stop'? ");
		input_to(faerie_adj2);
		return 1;
	}

	if (lower_case(str) == "stop")
	{
		abort_find();
		return 1;
	}

	if (member_array(lower_case(str), gFaerieAdj1Arr) == -1 ||
	  lower_case(str) == gAdj1)
	{
		write("\nThat's not an option.\n" +
			format_output(gFaerieAdj1Arr) + "Which appearance " +
			"do you wish to look for? Or 'stop'? ");
		input_to(faerie_adj2);
		return 1;
	}
	else
	{
		gAdj2 = lower_case(str);
		environment(environment())->save_faerie(gAdj1, gAdj2, 
		  gHairLength, gHairColour, gHairStyle, gEyeType, gEyeColour, 
		  gGender, environment()->query_real_name());
		environment()->catch_tell("\nYou may 'name' your faerie " +
			"or 'choose adornments' for your faerie here.\n");
		environment(environment())->recall_faerie(environment());
		set_alarm(0.2, 0.0, &remove_object());
		return 1;
	}
}

