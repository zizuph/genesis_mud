/*
 * - bottle.c
 *
 * This file handles the various types of bottles that may be
 * contructed to hold various perfumes and colognes.
 *
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#include "perfume.h"


private static int cologne, uses, max_uses;
private static string type, oil, script, design, my_long, perf_str;


public int
set_bottle_type(string str)
{
    if (strlen(type))
    {
	remove_adj(bottles[type][ADJS]);
	remove_name(bottles[type][NAMES]);
	type = 0;
    }

    if (pointerp(bottles[str]))
	type = str;

    return strlen(type);
}

public string
query_bottle_type(void)		{ return type; }

public int
set_perfume_oil(string str)
{
    if (strlen(oil))
    {
	remove_name(oil);
	remove_name("cologne");
	remove_name("perfume");
	oil = uses = 0;
    }

    if (pointerp(perfumes[str]))
	oil = str;

    return strlen(oil);
}

public string
query_perfume_oil(void)		{ return oil; }

public int
query_cologne(void)		{ return cologne; }

public int
set_bottle_script(string str)	{ return strlen(script = str); }

public string
query_bottle_script(void)	{ return script; }

public int
set_bottle_design(string str)	{ return strlen(design = str); }

public string
query_bottle_design(void)	{ return design; }

public int
query_uses(void)		{ return uses; }

public int
query_max_uses(void)		{ return max_uses; }

private void
modify_long(void)
{
    int size;
    string *arr;

    if (!strlen(design))
    {
	my_long = bottles[type][LONG];
	return;
    }

    arr = bottles[type][DESIGN][design];

    switch(sizeof(arr))
    {
    case 1:
	my_long = sprintf(bottles[type][LONG], arr[0]);
	break;
    case 2:
	my_long = sprintf(bottles[type][LONG], arr[0], arr[1]);
	break;
    case 3:
	my_long = sprintf(bottles[type][LONG], arr[0], arr[1], arr[2]);
	break;
    case 4:
	my_long = sprintf(bottles[type][LONG], arr[0], arr[1], arr[2], arr[3]);
	break;
    }
}

public string
how_much(void)
{
    int val = 100;

    if (uses != max_uses)
    {
	float max, cur;

	cur = itof(uses);
	max = itof(max_uses);
	val = ftoi(100.0 - (((max - cur) / max) * 100.0));
    }

    switch(val)
    {
    case 91..100: return "full";
    case 81..90:  return "quite full";
    case 71..80:  return "rather full";
    case 61..70:  return "somewhat full";
    case 51..60:  return "about half full";
    case 41..50:  return "about half empty";
    case 31..40:  return "somewhat empty";
    case 21..30:  return "rather empty";
    case 11..20:  return "close to empty";
    case  0..10:  return "nearly empty";
    default:      return "deceptively full";
    }
}

private string
perfumed_long(void)
{
    string desc = my_long;

    if (!strlen(oil) || (uses < 1))
    {
	desc += " Currently it is empty.";
    }
    else
    {
	desc += " Currently it is "+ how_much() +" of "+
	    LANG_ADDART(perfumes[oil][PDESC]) +" that "+
	    "you recognize as being "+ oil +" "+ perf_str +".";
    }

    if (strlen(script))
	desc += " Inscribed on the bottom are the words:\n    "+ script;

    return desc + "\n";
}

/* Set the flag if this is cologne. */
public int
config_bottle(int flag)
{
    /* We need a bottle and scent at least. */
    if (!strlen(type) || !strlen(oil))
	return 0;

    /* Does bottle require a design? */
    if (m_sizeof(bottles[type][DESIGN]) && !strlen(design))
	return 0;

    /* If this is cologne, make sure scent and container match. */
    if (flag && (!perfumes[oil][PCOLOGNE] || !bottles[type][BCOLOGNE]))
	return 0;

    uses = bottles[type][USES];
    max_uses = uses;
    cologne = flag;

    set_long(perfumed_long);
    set_short(bottles[type][SHORT]);
    set_pshort(LANG_PSENT(bottles[type][SHORT]));

    add_adj(bottles[type][ADJS]);
    add_adj(({"sybarun", "ziggurat"}));    
    set_name(bottles[type][NAMES]);

    if (cologne)
	perf_str = "cologne";
    else
	perf_str = "perfume";

    add_name(perf_str);
    add_name(oil);
    modify_long();

    return 1;
}

static void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("bottle");
    set_short("empty bottle");
    set_long("An empty bottle used to hold colognes or perfumes.\n");

    set_keep(1);

    type = oil = script = design = my_long = perf_str = "";
	
	if (IS_CLONE)
      set_item_expiration();  		
}

public nomask int
perfume_bottle(void)		{ return 1; }

public int
f_dab(string str)
{
    int res;
    object *obs, ob;
    string perf, *locs;

    if (!strlen(str))
	return notify_fail("Dab what?\n");

    if (!uses || !oil)
    {
	return notify_fail("The "+ short() +" is empty, how do you "+
	    "expect to do that?\n");
    }

    obs = filter(all_inventory(this_player()), perfume_bottle);
    res = parse_command(str, obs, "%o [onto] / [on] / [to] [my] %w",
	ob, str);

    if (ob != this_object())
	return 0;

    if (this_player()->query_gender() != G_FEMALE)
	locs = MALE_LOCS;
    else
	locs = FEMALE_LOCS;

    if (!res || !IN_ARRAY(str, locs))
    {
	return notify_fail("Dab the "+ perf_str +" onto your what?\n"+
	    "Choices are: "+ COMPOSITE_WORDS(locs) +".\n");
    }

    if (cologne == this_player()->query_gender())
    {
	write("Applying "+ perf_str +" to your skin would destroy its "+
	    "delicate balance.\n");
	return 1;
    }

    if (!strlen(perf = this_player()->query_perfume_oil()))
    {
	object shadow = clone_object(PERFUME_SHADOW);

	if (!objectp(shadow) || !shadow->shadow_me(this_player()))
	{
	    shadow->remove_shadow();

	    write("There seems to be a problem with your bottle, "+
		"make a bug report.\n");
	    return 1;
	}

	shadow->set_perfume_oil(oil, perfumes[oil]);
    }
    else if (perf != oil)
    {
	write("You are already wearing a different kind of "+
	    perf_str +", you should wash it off before applying "+
	    "a different kind.\n");
	return 1;
    }

    write("You dab some "+ perf_str +" onto your "+ str +
	" from the "+ short() +".\n");
    say(QCTNAME(this_player()) +" dabs some "+ perf_str +
	" from "+ LANG_ADDART(short()) +" onto "+
	this_player()->query_possessive() +" "+ str +".\n");

    if (--uses == 0)
    {
	write("You use up the last of the "+
	    perf_str +" in the "+ short() +".\n");
    }

    return 1;
}

public int
f_empty(string str)
{
    int res;
    string perf;
    object *obs, ob;

    if (!strlen(str))
	return notify_fail("Empty what?\n");

    obs = filter(all_inventory(this_player()), perfume_bottle);
    res = parse_command(str, obs, "[the] %o", ob);

    if (!res || !objectp(ob))
	return notify_fail("Empty which bottle?\n");

    if (ob != this_object())
	return 0;

    if (!uses || !oil)
    {
	write("The "+ short() +" is already empty.\n");
	return 1;
    }

    write("You empty the "+ short() +" of "+ oil +" "+ perf_str +".\n");
    say(QCTNAME(this_player()) +" empties "+
	this_player()->query_possessive() +" "+ short() +".\n");

    set_perfume_oil("none");
    return 1;
}

public int
f_help(string str)
{
    if ((str != "perfume") && (str != "cologne"))
	return 0;

    write("Astound yourself and others with the sensorial gift of "+
	"perfumes and colognes with these following commands:\n\n"+
	"    * dab    <which> <where>  -=-  Dab some on you now!\n"+
	"    * empty  <which>          -=-  Empty out your bottle, why?\n"+
	"\n"+
	"    * phold  <who> [how]      -=-  A scented embrace is ace!\n"+
	"    * phug   <who> [how]      -=-  Give the gift of a scented hug.\n"+
	"    * psmell <who> [how]      -=-  Smell out the competition.\n"+
	"    * waft                    -=-  Fill the air with the oil you wear.\n"+
	"\n"+
	"    <which> can be: perfume, cologne, bottle or <scent>.\n"+
	"    <where> is a location, use 'dab <which>' for a list.\n"+
	"\n");

    return 1;
}

private void
delay_write(void)
{
    if (this_player() != environment())
	return;

    write("Your "+ perf_str +" grants you a few additional abilities.\n");
    write("Simply do: help \""+ perf_str +"\" to see them\n");
}

public void
init(void)
{
    ::init();

    if (this_player() != environment())
	return;

    set_alarm(1.0, 0.0, &delay_write());

    add_action(   f_dab, "dab"   );
    add_action(  f_help, "help"  );
    add_action( f_empty, "empty" );
}

public void
hook_smelled(string str)
{
    if (!oil || !uses)
	return;

    this_player()->catch_tell("You catch "+
	LANG_ADDART(perfumes[oil][SCENT]) +" scent.\n");
}

public string
query_recover(void)
{
    return MASTER + ":"+ cologne +"#"+ uses +"#"+ type +"#"+ oil +"#"+
       design +"#"+ script +"*"+ query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    int tmp;

    sscanf(arg, "%d#%d#%s#%s#%s#%s*%s",
	cologne, tmp, type, oil, design, script, arg);

    /* XXX  Temporary fix */
    if (oil == "0")     oil    = "";
    if (type == "0")    type   = "";
    if (script == "0")  script = "";
    if (design == "0")  design = "";

    init_item_expiration_recover(arg);
    config_bottle(cologne);
    uses = tmp;

}
