//Shadow for battle standard, when stuck in the ground
#pragma save_binary
#pragma strict_types

inherit "/std/shadow";
inherit "/lib/commands.c";

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <formulas.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include <time.h>
#include <std.h>
#include <wa_types.h>
#include <options.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <options.h>
#include "orc.h"

void set_commands()
{
	shadow_who->add_cmd_item(shadow_who->query_names(), "extract", "@@extract_standard@@");
	shadow_who->add_cmd_item(shadow_who->query_names(), "break", "@@break_standard@@");
}

string short()
{
    return shadow_who->short() + ", stuck in the ground";
}

string query_short()
{
    return shadow_who->query_short() + ", stuck in the ground";
}

string plural_short()
{
    return shadow_who->plural_short() + ", stuck in the ground";
}

int extract_standard(string str)
{
	if(!IS_MEMBER(TP))
	{
		write("It wouldn't make sense for you to carry around a battle standard that has nothing to do with your cause. You could probably break it though.\n");
		return 1;
	}
	
	shadow_who->remove_prop(OBJ_M_NO_GET);

	write("Using all your strength, you pull the battle standard out of the ground.\n");
	say("Using all " + HIS_HER(TP) + " strength, " + QCTNAME(TP) +" pulls the battle standard out of the ground.\n");

	shadow_who->move(TP);
	remove_shadow();
	
	return 1;
}

int break_standard(string str)
{
	write("You kick the battle standard over, snapping the shaft. You then make quick work of tearing the rest apart, tossing away the remains.\n");
	say(QCTNAME(TP) +" kicks the battle standard over, snapping the shaft in half. " + HE_SHE(TP) + " then makes quick work of tearing the rest apart, tossing away the remains.\n");
	
	shadow_who->remove_object();
	
	return 1;
}