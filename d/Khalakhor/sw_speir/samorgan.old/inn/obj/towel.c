/**********************************************************************
 * - towel.                                                         - *
 * - This object is just for fun.                                   - *
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
 
public void
create_object()
{
	set_name("towel");
	add_name("fluffy");
	add_adj(({"fluffy", "white"}));
	set_short("fluffy white towel");
	set_pname("towels");
	set_pshort("fluffy white towels");
	set_long("The white fluffy white towel that has a soft "+
	"scent. It is used to <dry> many different parts of your body.\n");
	add_prop(OBJ_I_WEIGHT, 1);
	add_prop(OBJ_I_VOLUME, 5);
	add_prop(OBJ_I_VALUE, 1000);	
}

int
dry_it(string str)
{
	if(!strlen(str))
	{
		write("Dry what?\n");
		return 0;
	}
	if((str == "face"))
	{
		write("You dry your face with the fluffy white towel.\n");		
		say(QCTNAME(TP)+" dryes "+HIS(TP)+" face with a fluffy "+
		"white towel.\n");
		return 1;
	}
	if((str == "hands"))
	{
		write("You dry your hands with the fluffy white towel.\n");		
		say(QCTNAME(TP)+" dryes "+HIS(TP)+" hands with a fluffy "+
		"white towel.\n");
		return 1;
	}
	if((str == "neck"))
	{
		write("You dry your neck with the fluffy white towel.\n");		
		say(QCTNAME(TP)+" dryes "+HIS(TP)+" neck with a fluffy "+
		"white towel.\n");
		return 1;
	}
	if((str == "ears"))
	{
		write("You dry your ears with the fluffy white towel.\n");		
		say(QCTNAME(TP)+" dryes "+HIS(TP)+" ears with a fluffy "+
		"white towel.\n");
		return 1;
	}
	if((str == "behind ears"))
	{
		write("You dry your behind your ears with the fluffy "+
		"white towel.\n");		
		say(QCTNAME(TP)+" dryes behind "+HIS(TP)+" ears with a "+
		"fluffy white towel.\n");
		return 1;
	}
	if((str == "feet"))
	{
		write("You dry your feet with the fluffy white towel.\n");		
		say(QCTNAME(TP)+" dryes "+HIS(TP)+" feet with a fluffy "+
		"white towel.\n");
		return 1;
	}
	if((str == "body"))
	{
		write("You dry your body with the fluffy white towel.\n");		
		say(QCTNAME(TP)+" dryes "+HIS(TP)+" body with a fluffy "+
		"white towel.\n");
		return 1;
	}
	if((str == "legs"))
	{
		write("You dry your legs with the fluffy white towel.\n");		
		say(QCTNAME(TP)+" dryes "+HIS(TP)+" legs with a fluffy "+
		"white towel.\n");
		return 1;
	}
	if((str == "toes"))
	{
		write("You dry your toes with the fluffy white towel.\n");		
		say(QCTNAME(TP)+" dryes "+HIS(TP)+" toes with a fluffy "+
		"white towel.\n");
		return 1;
	}
	if((str == "between toes"))
	{
		write("You dry your between your toes with the fluffy "+
		"white towel.\n");		
		say(QCTNAME(TP)+" dryes between "+HIS(TP)+" toes with "+
		"a fluffy white towel.\n");
		return 1;
	}
}
void
init()
{
	::init();
	add_action(dry_it, "dry");
}