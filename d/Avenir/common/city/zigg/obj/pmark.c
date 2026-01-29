/*                                                                        *
 *  file name:   pmark.c                                                  *
 *  creator(s):  Zielia                                                   *
 *  last update:                                                          *
 *  purpose:     kiss mark made by pomade.c                               *
 *  note:                                                                 *
 *  bug(s):                                                               *
 *  to-do:                                                                */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <adverbs.h>
#include "zigg.h"

#define SUBLOC  "_pomade_kiss_" + part +"_"
#define VAR_NAMES   ({name, "kiss mark", "mark"})

public static string mtinted;
public static string mcolor;
public static string mwhere = "right cheek";
public static string part = "right_cheek";
public static string name;


public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
}

public void
set_part(void)
{
    if (mwhere == "right cheek")
	part = "right_cheek";
    else if (mwhere == "left cheek")
	part = "left_cheek";
    else if (mwhere == "right hand")
	part = "right_hand";
    else if (mwhere == "left hand")
	part = "left_hand";
    else
	part =  mwhere;
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (mwhere == "lips")
    {
	if (for_obj == carrier)
	{
	    str = "You have traces of "+ mcolor +
	    " lip gloss smeared across your lips.\n";
	}
	else
	{
	    str = capitalize(HE(carrier))+" has traces of "+
	    mcolor +" lip gloss smeared across "+
	    HIS(carrier) +" lips.\n";
	}
    }
    else
    {
	if (for_obj == carrier)
	{
	    str = "You have a "+ mtinted +" kiss mark on your "+
	    mwhere +".\n";
	}
	else
	{
	    str = capitalize(HE(carrier))+" has a "+
	    mtinted +" kiss mark on "+ HIS(carrier) +
	    " "+ mwhere +".\n";
	}
    }

    return str;
}

public void
set_vars(string str1, string str2, string str3)
{
    mtinted = str1;
    mcolor  = str2;
    mwhere  = str3;
}

public void
remove_object(void)
{
    if (IS_CLONE)
    {
	ENV(TO)->remove_subloc(SUBLOC);

	if (ENV(TO)->query_npc())
	{
	    tell_room(environment(environment(TO)),
		QCTNAME(environment(TO)) +" wipes the lip gloss "+
		"from "+ HIS(environment(TO)) +" "+ mwhere +
		" leaving no trace behind.\n");
	}
    }

    ::remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    remove_name(query_names());
    name = "pomade::"+ mwhere;
    set_name(VAR_NAMES);

    set_part();
    to->add_subloc(SUBLOC, this_object());

    if (ENV(TO)->query_npc())
	set_alarm(180.0, 0.0, remove_object);
    else
	set_alarm(3600.0, 0.0, remove_object);
}

public int
f_wipe(string str)
{
    string *arr;
    int size;

    if (this_player() != environment(this_object()))
	return 0;

    if (!strlen(str))
	return 0;

    arr = explode(str, " ");
    size = sizeof(arr);

    if (arr[(size - 1)] == "cheek" || arr[(size - 1)] == "hand")
    {
	if(arr[(size - 2)] == "left")
	{
	    arr[(size - 1)] = "left " + arr[(size - 1)];
	}
	else if (arr[(size - 2)] == "right")
	{
	    arr[(size - 1)] = "right " + arr[(size - 1)];
	}
	else
	{
	    return notify_fail("Wipe your left or right "+
	      arr[(size - 1)] +"?\n");
	}
    }

    if (arr[(size - 1)] == mwhere)
    {
	write("You wipe the lip gloss from your "+ mwhere +
	  " leaving no trace behind.\n");

	say(QCTNAME(TP)+" wipes the lip gloss from "+ HIS(TP) +
	  " "+ mwhere + " leaving no trace behind.\n");

	set_alarm(0.0, 0.0, remove_object);
	return 1;
    }

    notify_fail("Wipe what from <where>?");
    return 0;
}

public void
init(void)
{
    ::init();
    add_action(f_wipe,  "wipe");
}

public string
query_recover(void)	{ return 0; }
