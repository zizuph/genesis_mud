/**********************************************************************
 * - soap.c                                                         - *
 * - This object removes the dirty_prop                             - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/

#pragma save_binary
#pragma strict_types
 
inherit "/std/object";
#include "../inn.h"
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"

#define LIVE_I_DIRTY   "_live_i_dirty"   /* how dirty is the player? */

public void
create_object()
{
	set_name("soap");
	add_name("bar");
	add_adj(({"bar"}));
	set_short("bar of soap");
	set_pname("soaps");
	set_pshort("bars of soap");
	set_long("The pale white bar of soap that has a soft scent. It "+
	"is used to <wash> many different parts of your body.\n");
	add_prop(OBJ_I_WEIGHT, 1);
	add_prop(OBJ_I_VOLUME, 5);
	add_prop(OBJ_I_VALUE, 560);
}

int
wash_it(string str)
{
	object *ob;
	int i;
	if(!strlen(str))
	{
		write("Wash what?\n");
		return 0;
	}
	if((str == "face"))
	{
		write("You wash your face with the bar of soap.\n");		
		say(QCTNAME(TP)+" washes "+HIS(TP)+" face with a bar "+
		"of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "hands"))
	{
		write("You wash your hands with the bar of soap.\n");		
		say(QCTNAME(TP)+" washes "+HIS(TP)+" hands with a bar "+
		"of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "neck"))
	{
		write("You wash your neck with the bar of soap.\n");		
		say(QCTNAME(TP)+" washes "+HIS(TP)+" neck with a bar "+
		"of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "ears"))
	{
		write("You wash your ears with the bar of soap.\n");		
		say(QCTNAME(TP)+" washes "+HIS(TP)+" ears with a bar "+
		"of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "behind ears"))
	{
		write("You wash your behind your ears with the bar "+
		"of soap.\n");		
		say(QCTNAME(TP)+" washes behind "+HIS(TP)+" ears with "+
		"a bar of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "feet"))
	{
		write("You wash your feet with the bar of soap.\n");		
		say(QCTNAME(TP)+" washes "+HIS(TP)+" feet with a bar "+
		"of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "body"))
	{
		write("You wash your body with the bar of soap.\n");		
		say(QCTNAME(TP)+" washes "+HIS(TP)+" body with a bar "+
		"of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "legs"))
	{
		write("You wash your legs with the bar of soap.\n");		
		say(QCTNAME(TP)+" washes "+HIS(TP)+" legs with a bar "+
		"of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "toes"))
	{
		write("You wash your toes with the bar of soap.\n");		
		say(QCTNAME(TP)+" washes "+HIS(TP)+" toes with a bar "+
		"of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	if((str == "between toes"))
	{
		write("You wash your between your toes with the bar "+
		"of soap.\n");		
		say(QCTNAME(TP)+" washes between "+HIS(TP)+" toes with "+
		"a bar of soap.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
}
void
init()
{
	::init();
	add_action(wash_it, "wash");
}