// Ziggurat  (zig_harness.c)
// creator(s):  Lucius and Zielia 2006
// last update:
// purpose:
// note:
// resources:
//	http://www.bbc.co.uk/dna/h2g2/A594614
//	http://www.elizabethancostume.net/corsets/materials.html
//	http://members.aol.com/fittingrm/busk.htm
//	http://www.fathom.com/course/21701726/sessions.html
//	http://laracorsets.com/History_of_the_corset_001_Start_page.htm
//	http://www.absolutecorsets.com
//	http://www.gothicstyles.com/html/glossary.php
//	http://www.deliciouscorsets.com/DC_ready.html
//	http://www.staylace.com
//	http://www.haabet.dk/patent/Spencer_System_of_Corsetry_1936/7.html
//	http://science.enotes.com/how-products-encyclopedia/corset
//	http://www.villagevoice.com/arts/0203,yeh,31491,12.html
//	http://www.periodcorsets.com/862.html?page=862&PHPSESSID=747ecd8214d6ec9c9def0f83a38fd06e&SESSION=cb068b885e8ff9a2bb6c415ffbaf66f7&s=0
//	http://www.laceembrace.com/custom.shtml
//	http://www.originals-by-kay.com/corsetry/corset_history.html
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "zigg.h"
#include "corset.h"

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#ifndef SECURITY
#define SECURITY  ("/secure/master")
#endif

#define D(x)
//#define D(x)  write(x)

/* A Lot Of Variables. */
private static int value;
private static int material, lining;
private static string mat_colour, lin_colour;
private static int style, length, hip_cut;
private static int straps, bustline;
private static int boning, bone_mat;
private static int busk, busk_mat;
private static int back_lace, front_lace, side_lace;
private static string bl_colour, fl_colour, sl_colour;
private static int fastener, grommets;
private static int ornament, buckle_mat;
private static string bow_colour, pip_colour;
private static string ftrim_colour, ltrim_colour;

/*
 * Helper functions.
 */
public mapping
query_fabrics(void)		{ return fabrics; }

public mapping
query_lacing(void)		{ return lacing;  }

public mapping
query_busking(void)		{ return busking; }

public string *
query_colours(void)		{ return colours; }

/*
 * Corset design variables.
 * The set_ functions are always called when option is picked.
 * The query_ functions below are called as needed.
 */
public int
query_material(void)		{ return material; }

public void
set_material(int i)		{ material = i; }

public string
query_mat_colour(void)		{ return mat_colour; }

public void
set_mat_colour(string s)	{ mat_colour = s; }

public int
query_lining(void)		{ return lining; }

public void
set_lining(int i)		{ lining = i; }

public string
query_lin_colour(void)		{ return lin_colour; }

public void
set_lin_colour(string s)	{ lin_colour = s; }

public int
query_style(void)		{ return style; }

public void
set_style(int i)		{ style = i; }

public int
query_straps(void)		{ return straps; }

public void
set_straps(int i)		{ straps = i; }

/* Bustline depends on style and straps. */
public int
query_bustline(void)		{ return bustline; }

public void
set_bustline(int i)		{ bustline = i; }

/* The following are pseudo functions. */
public int
query_bust_nostrap(void)	{ return bustline; }

public void
set_bust_nostrap(int i)		{ bustline = i; }

public int
query_bust_strap(void)		{ return bustline; }

public void
set_bust_strap(int i)		{ bustline = i; }
/* End pseudo bustline functions. */

public int
query_length(void)		{ return length; }

public void
set_length(int i)		{ length = i; }

public int
query_hip_cut(void)		{ return hip_cut; }

public void
set_hip_cut(int i)		{ hip_cut = i; }

/* Psuedo hip_cut, as longline has an extra option. */
public int
query_hip_cut_long(void)	{ return hip_cut; }

public void
set_hip_cut_long(int i)		{ hip_cut = i; }
/* End psuedo hip_cut functions. */

public int
query_boning(void)		{ return boning; }

public void
set_boning(int i)		{ boning = i; }

public int
query_bone_mat(void)		{ return bone_mat; }

public void
set_bone_mat(int i)		{ bone_mat = i; }

public int
query_back_lace(void)		{ return back_lace; }

public void
set_back_lace(int i)		{ back_lace = i; }

public string
query_bl_colour(void)		{ return bl_colour; }

public void
set_bl_colour(string s)		{ bl_colour = s; }

public int
query_busk(void)		{ return busk; }

public void
set_busk(int i)			{ busk = i; }

/* Busk material requires a busk. */
public int
query_busk_mat(void)		{ return busk_mat; }

public void
set_busk_mat(int i)		{ busk_mat = i; }

/* Pseudo busk_mat functions to handle 1 / 2 busk differences. */
public int
query_busk_mat_one(void)	{ return busk_mat; }

public void
set_busk_mat_one(int i)		{ busk_mat = i; }

public int
query_busk_mat_two(void)	{ return busk_mat; }

public void
set_busk_mat_two(int i)		{ busk_mat = i; }
/* End pseudo busk_mat functions. */

/* Fasteners require 2 busks. */
public int
query_fastener(void)		{ return fastener; }

public void
set_fastener(int i)		{ fastener = i; }

/* Front lacing requires lacing-fastener. */
public int
query_front_lace(void)		{ return front_lace; }

public void
set_front_lace(int i)		{ front_lace = i; }

public string
query_fl_colour(void)		{ return fl_colour; }

public void
set_fl_colour(string s)		{ fl_colour = s; }

public int
query_grommets(void)		{ return grommets; }

public void
set_grommets(int i)		{ grommets = i; }

/* Last process, ornamentation--and sub-types. */

public int
query_ornament(void)		{ return ornament; }

public void
set_ornament(int i)		{ ornament = i; }

/* depends on buckle-ornament. */
public int
query_buckle_mat(void)		{ return buckle_mat; }

public void
set_buckle_mat(int i)		{ buckle_mat = i; }

/* depends on bow-ornament. */
public string
query_bow_colour(void)		{ return bow_colour; }

public void
set_bow_colour(string s)	{ bow_colour = s; }

/* depends on piping-ornament. */
public string
query_pip_colour(void)		{ return pip_colour; }

public void
set_pip_colour(string s)	{ pip_colour = s; }

/* depends on feather-trim ornament. */
public string
query_ftrim_colour(void)	{ return ftrim_colour; }

public void
set_ftrim_colour(string s)	
{ 
    if (s == "rainbow") { s = "iridescent rainbow"; }
    ftrim_colour = s; 
}

/* dependson lace-trim ornament. */
public string
query_ltrim_colour(void)	{ return ltrim_colour; }

public void
set_ltrim_colour(string s)	{ ltrim_colour = s; }

/* depends on side-lace ornament. */
public int
query_side_lace(void)		{ return side_lace; }

public void
set_side_lace(int i)		{ side_lace = i; }

public string
query_sl_colour(void)		{ return sl_colour; }

public void
set_sl_colour(string s)		{ sl_colour = s; }

/* END corset design variable functions. */

/* Value of the corset (in copper). */
public int
query_value(void)		{ return value; }

public void
set_value(int i)		{ value = i; }


/* Pieces together the description of a corset. */
public void
make_desc(void)
{
    mapping data = SECURITY->do_debug("get_variables", TO);

    obj_long = "";

    foreach(string val : desc_order)
    {
	int size;
	mixed item = descrip[val];

D("\nDesc:  "+ val +"\n");
	if (mappingp(item))
	{
	    item = data[val];
	    item = descrip[val][item];

	    /* Nested mapping. */
	    if (mappingp(item))
	    {
		string key = item["key"];
D("* Desc:  "+ key +"\n");
		item = item[data[key]];
	    }
	}

	if (!pointerp(item))
	{
D("*** Not needed.\n");
	    continue;
	}

	size = sizeof(item);

	if (size == 1)
	{
D("*** Single entry.\n");
	    val = item[0];

	    if (val[-1..] == ".")
		val += " ";

	    obj_long += val;
	    continue;
	}

	string *arr = allocate(--size);

	while(size)
	{
	    int ix = size--;

	    /* Embedded random choice strings. */
	    if (pointerp(item[ix]))
	    {
		arr[size] = one_of_list(item[ix]);
D("** Ran-item:  "+ arr[size] +"\n");
		continue;
	    }

D("** Sub-item:  "+ item[ix] +"\n");
	    /* This checks for 'colour' strings. */
	    if (stringp(data[item[ix]]))
	    {
		arr[size] = data[item[ix]];
D("**** String:  "+ arr[size] +"\n");
		continue;
	    }

	    /* Looked up value. */
	    mixed tmp = process[item[ix]];

	    if (pointerp(tmp))
	    {
		tmp = tmp[0];

		if (!strlen(tmp) || (tmp[0] != '#'))
		    throw("*Error generating corset description!\n");

		tmp = tmp[1..];

		if (!data[tmp] || !mappingp(data[tmp]))
		    throw("*Error generating corset description!\n");

D("** Redirect:  "+ tmp +"\n");
		tmp = data[tmp];
	    }

	    /* Reverse lookup value. */
	    foreach(string key, mixed vals : tmp)
	    {
		if (vals[0] == data[item[ix]])
		{
		    arr[size] = key;
		    /* This caches the values for future lookups. */
		    data[item[ix]] = key;
D("**** Lookup:  "+ arr[size] +"\n");
		    break;
		}
	    }
	}  // while()

	switch(sizeof(arr))
	{
	case 1:
	    val = sprintf(item[0], arr[0]);
	    break;
	case 2:
	    val = sprintf(item[0], arr[0], arr[1]);
	    break;
	case 3:
	    val = sprintf(item[0], arr[0], arr[1], arr[2]);
	    break;
	case 4:
	    val = sprintf(item[0], arr[0], arr[1], arr[2], arr[3]);
	    break;
	}

	if (val[-1..] == ".")
	    val += " ";

	obj_long += capitalize(val);
    }  // foreach()

    obj_long += "\n";

    set_adj(({ data["mat_colour"], data["material"], "sybarun", "ziggurat",
    	"custom"}));
    set_short(data["mat_colour"] +" "+ data["material"] +" corset");
}

public void
make_random(int no_desc)
{
    string next = BEGIN_PROCESS;

    value = 0;

    while(strlen(next))
    {
	function fun;
	mixed item = process[next];

D(sprintf("Process:  %-15s: ", next));
	/* Lookup item in variable. */
	if (pointerp(item))
	{
	    mixed val;
	    mixed var = item[0];

	    /* Array lookup. */
	    if (var[0] == '@')
	    {
		var = var[1..];
		fun = mkfunction("query_"+ var);
		var = fun();
		val = one_of_list(var);
D("(var-arr) "+ val);
	    }

	    /* Mapping lookup. */
	    if (var[0] == '#')
	    {
		var = var[1..];
		fun = mkfunction("query_"+ var);
		var = fun();
		val = one_of_list(m_indexes(var));
		var = var[val];
D("(var-map) "+ val);
		val = var[0];
		value += var[1];
	    }

	    /* Set and continue. */
	    fun = mkfunction("set_"+ next);
	    next = item[1];
	    fun(val);
	}
	/* Mapping, all item values within. */
	else
	{
	    mixed val = m_indexes(item);
	    mixed var = one_of_list(val);
	    function fun =  mkfunction("set_"+ next);

	    fun(item[var][0]);
	    next = item[var][2];
	    value += item[var][1];
D("(mapping) " + var);
	}
D("\n");
    }  // while()
D("\n");

    /* Transform the value from GOLD -> COPPER */
    value *= 144;

    if (!no_desc)
	make_desc();
}

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"corset","garment"}));
    add_pname(({"clothes", "clothing"}));
    config_wearable_item(A_TORSO, 1, 15, this_object());

    add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
    add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
    add_prop(OBJ_I_VALUE, query_value);

    set_keep(1);
	
}

private void
tighten(object tp)
{
    tp->catch_tell("You deftly tighten the laces at the back of your "+
	short() +" until it is perfectly snug.\n");
    tell_room(ENV(tp), QCTNAME(tp) +" deftly tightens the laces at the "+
	"back of "+ HIS(tp) +" "+ short() +" until it molds "+ HIS(tp) +
	" figure perfectly.\n", ({tp}), TO);
}

public int
wear(object ob)
{
    object tp = TP;

    if (TP != environment(ob))
	return 0;

    if (query_busk() == 2)
    {
	if (query_front_lace())
	{
	    write("You wrap your "+ short() +" around your torso and lace "+
		"up the front.\n");

	    say(QCTNAME(TP) +" wraps "+ HIS(TP) +" "+ short() +" around "+
		HIS(TP) +" torso and laces up the front.\n");
	}
	else
	{
	    write("You wrap your "+ short() +" around your torso and fasten "+
		"the front.\n");

	    say(QCTNAME(TP) +" wraps "+ HIS(TP) +" "+ short() +" around "+
		HIS(TP) +" torso and fastens the front.\n");
	}
    }
    else
    {
	write("You slip your "+ short() +" on over your head and pull "+
	    "it down into place.\n");

	say(QCTNAME(TP) +" slips "+ HIS(TP) +" "+ short() +" on over "+
	    HIS(TP) +" head and pulls it down into place.\n");
    }

    set_alarm(2.0, 0.0, &tighten(tp));
    return 1;
}

public int
remove(object ob)
{
    if (TP != environment(ob))
	return 0;

    if ((query_busk() == 2) && !query_front_lace())
    {
	if (query_front_lace())
	{
	    write("You loosen the front and back laces of your "+ short() +
		" and give a faint sigh of relief as you slip it off.\n");

	    say(QCTNAME(TP)+" loosens the front and back laces of "+
		HIS(TP) +" "+ short() +" and gives a faint sigh of relief "+
		"as "+ HE(TP) +" slips it off.\n");
	}
	else
	{
	    write("You loosen the laces of your "+ short() +" and give "+
		"a faint sigh of relief as you unfasten the front and "+
		"slip it off.\n");

	    say(QCTNAME(TP)+" loosens the laces of "+ HIS(TP) +" "+
		short() +" and gives a faint sigh of relief as "+ HE(TP) +
		" unfastens the front and slips it off.\n");
	}
    }
    else
    {
	write("You loosen the laces of your "+ short() +", giving a "+
	    "sigh of relief as you slip it off overhead.\n");

	say(QCTNAME(TP)+" loosens the laces of "+ HIS(TP) +" "+ short()+
	    ", giving a sigh of relief as "+ HE(TP) +
	    " slips it off overhead.\n");
    }

    return 1;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover() + "#!" +
	value +"!"+ material +"!"+ lining +"!"+
	mat_colour +"!"+ lin_colour +"!"+
	style +"!"+ length +"!"+ hip_cut +"!"+ straps +"!"+
	bustline +"!"+ boning +"!"+ bone_mat +"!"+
	busk +"!"+ busk_mat +"!"+ back_lace +"!"+
	front_lace +"!"+ side_lace +"!"+
	bl_colour +"!"+ fl_colour +"!"+ sl_colour +"!"+
	fastener +"!"+ grommets +"!"+ ornament +"!"+
	buckle_mat +"!"+ bow_colour +"!"+ pip_colour +"!"+
	ftrim_colour +"!"+ ltrim_colour +
	"!#";
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    sscanf(arg, "%s#!%d!%d!%d!%s!%s!%d!%d!%d!%d!%d!%d!%d!%d!%d" +
	        "!%d!%d!%d!%s!%s!%s!%d!%d!%d!%d!%s!%s!%s!%s!#%s", arg,
	value, material, lining, mat_colour, lin_colour,
	style, length, hip_cut, straps, bustline, boning,
	bone_mat, busk, busk_mat, back_lace, front_lace,
	side_lace, bl_colour, fl_colour, sl_colour,
	fastener, grommets, ornament, buckle_mat,
	bow_colour, pip_colour, ftrim_colour, ltrim_colour,
	arg);

    /* Just in case? */
    if (catch(make_desc()))
	remove_object();

    will_not_recover = (random(100) < RECOVERY_LOST);
}

