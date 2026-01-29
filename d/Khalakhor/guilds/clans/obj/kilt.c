/**********************************************************************
 * - kilt.c                                                         - *
 * - Kilts for Clan members                                         - *
 * - Created by Damaris 8/2006                                      - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";

public varargs string
long(string str, object for_obj)
{
	string res = ::long(str, for_obj);
	if (!objectp(for_obj))
	for_obj = this_player();
	if (str || !IS_MEMBER(for_obj))
	return res;
	return res + "You may <tug kilt>, <brush kilt>, <adjust kilt>, "+
	"<flash kilt>.\n";
}

public void
create_object()
{
	set_name( ({"kilt"}) );
	set_layers(1);
	set_looseness(10);
	set_wf(this_object());
	set_slots(A_LEGS);
	add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it "+
	"uninteresting.\n");
	add_prop(OBJ_I_WEIGHT, 400);
	add_prop(OBJ_I_VOLUME, 200);
	add_prop(OBJ_I_VALUE, 100);
}

void
enter_env(object env, object from)
{
	::enter_env(env, from);
	if (IS_MEMBER(env) || env->query_wiz_level());
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
show_subloc(string subloc, object on, object for_obj)
{
	if (subloc != GUILD_SUBLOC)
	return this_player()->show_subloc(subloc, on, for_obj);
	
	if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
	if (for_obj == on)
	{
		return "You proudly wear your " + short() + ", "+
		"displaying your celtic heritage.\n";
	}
	else
	{
		return on->query_The_name(for_obj) + " is wearing "+
		LANG_ADDART(short()) + " of the Clans.\n";
	}
}
int
tug_hem(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "kilt"))
	{
		write("You descreetly tug on the hem of "+
		"your "+ short(TP) +".\n");
		
                say(QCTNAME(TP)+" descreetly tugs on the hem "+
                "of "+ HIS(TP) +" "+ short(TP) +".\n");
                return 1;
                }
                else
                {
			notify_fail("Tug kilt perhaps?\n");
			return 0;
		}
}

int
brush_kilt(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "kilt"))
	{
		write("You brush the dirt from your "+ short(TP) +".\n");
		
                say(QCTNAME(TP)+" brushes the dirt from "+
                "" + HIS(TP) +" "+ short(TP) +".\n");
                return 1;
                }
                else
                {
			notify_fail("Brush kilt perhaps?\n");
			return 0;
		}
}

int
adjust_kilt(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "kilt"))
	{
		write("You adjust your "+ short(TP) +".\n");
		
		say(QCTNAME(TP)+" adjusts "+ HIS(TP) +" "+ short(TP) +".\n");
		return 1;
		}
		else
		{
			notify_fail("Adjust kilt perhaps?\n");
			return 0;
		}
}
int
flash_kilt(string str)
{
	if(this_player() != query_worn())
        return 0;
        if((str == "kilt"))
	{
		write("You swish your "+ short(TP) +" and flash a bit "+
		"of leg.\n");
		
		say(QCTNAME(TP)+" swishes "+ HIS(TP) +" "+ short(TP) +" "+
		"and flashes a bit of leg.\n");
		return 1;
		}
		else
		{
			notify_fail("Flash kilt perhaps?\n");
			return 0;
		}
}


void
init()
{
	mixed tmp;
	::init();
	add_action(tug_hem, "tug");
	add_action(brush_kilt, "brush");
	add_action(adjust_kilt, "adjust");
	add_action(flash_kilt, "flash");
	
	if (!living(environment()))
	return;
	setuid(); seteuid(getuid());
	tmp = (string)SERVER->query_clan(ENV(TO)->query_real_name());
	if (!strlen(tmp))
	{
		set_adj( tmp = ({"soft","brown"}) );
		set_short("soft brown kilt");
		set_pshort("soft brown kilts");
	}
	else
	{
		set_adj(tmp = (string)SERVER->query_clan(tmp)[CLAN_CLRS]);
		set_short(implode(tmp, " and ") + " kilt");
		set_pshort(implode(tmp, " and ") + " kilts");
	}
	add_adj("wool");
	set_long("This woolen kilt is commonly worn by humans from "+
	"Khalakhor. The trim of the kilt is "+
	"" + (tmp[0] == "soft" ? "a soft brown colour" : tmp[0]) + " "+
	"with the rest dyed "+
	(tmp[1] == "brown" ? "brown as well" : tmp[1]) + ".\n");
}
