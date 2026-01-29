/*
	*A fun mechanical toy!
	*Altrus, March 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

void create_object()
{
	set_name("toy");
	set_pname("toys");
	set_adj("simple");
	set_adj("mechanical");
	set_short("simple mechanical toy");
	set_pshort("simple mechanical toys");
	set_long("The toy seems to be made of small metalic " +
	"parts. There are probably cogs, gears and springs " +
	"inside. At first glance, one might think this is gnomish " +
	"made, and that would scare anyone, but a look at " +
	"one of the feet reveals a small engraved message: " +
	"'Made by Altrus'. There is also something engraved " +
	"on the front of the toy: 'For fun, 'wind head', for " +
	"more fun, 'wind arm'!'\n");
	
		
	add_prop(OBJ_I_WEIGHT, 100); 	
	add_prop(OBJ_I_VOLUME, 100);
	add_prop(OBJ_M_NO_STEAL, "Stop it, you thief!\n"); 	
	add_prop(OBJ_M_NO_DROP, "What?! Why would " +
	"you want to get rid of this fun toy you put " +
	"together yourself?\n");
	add_prop(OBJ_M_NO_GIVE, "What?! Why would " +
	"you want to get rid of this fun toy you put " +
	"together yourself?\n");
}

int init()
{
	add_action("wind_toy", "wind");
}

int wind_toy(string str)
{
	if(str == "head")
	{
		TP->catch_msg("You wind the head of the " +
		"toy several times and set it on the ground.\n");
		
		say(QCTNAME(TP) + " winds the head " +
		"of " + HIS_HER(TP) + " toy several times, " +
		"then sets it on the ground.\n"); 
		
		write("\n");
		write("The little metal toy starts to click and " +
		"clank. It slowly begins to walk around " +
		"on the ground.\n");
		write("\n");
		
		say("\n");
		say("The little metal toy starts to click and " +
		"clank. It slowly begins to walk around " +
		"on the ground.\n");
		say("\n");
		
		TP->catch_msg("The toy finally comes to a " +
		"stop in front of you, and you pick it up.\n");
		
		say("The toy finally comes to a stop in front " +
		"of " + QCTNAME(TP) + ", who promptly " +
		"picks it up.\n");
	}
	
	else if(str == "arm")
	{
		TP->catch_msg("You wind the arm of the " +
		"toy several times and set it on the ground.\n");
		
		say(QCTNAME(TP) + " winds the arm " +
		"of " + HIS_HER(TP) + " toy several times, " +
		"then sets it on the ground.\n");
		
		write("\n");
		write("The mechanical toy " +
		"starts making a buzzing sound and starts to spin.\n");
		write("\n");
		write("Just when it " +
		"looks like the toy has wound down, it makes " +
		"a loud BANG!\n");
		write("\n");
		write("A bright flash seems to come " +
		"from its head, and smoke quickly forms " +
		"around it.\n");
		write("\n");
		
		say("\n");
		say("The mechanical toy " +
		"starts making a buzzing sound and starts to spin.\n");
		say("\n");
		say("Just when it " +
		"looks like the toy has wound down, it makes " +
		"a loud BANG!\n");
		say("\n");
		say("A bright flash seems to come " +
		"from its head, and smoke quickly forms " +
		"around it.\n");
		say("\n");
		
		TP->catch_msg("You bend over to pick the up " +
		"the toy, and notice a small piece of red candy " +
		"in its hand. You take the candy from the toy's " +
		"hand as you pick it up.\n");
		
		say("As " + QCTNAME(TP) + " bends over " +
		"to pick up " + HIS_HER(TP) + " toy, you notice " +
		"that " + HE_SHE(TP) + " takes a piece of red " +
		"candy from the hand of the toy. You are certain " +
		"that it wasn't there before.\n");
		
		setuid();
		seteuid(getuid());
		
		clone_object("/w/altrus/obj/toy/toy_candy.c")->move(TP);
	}
	
	else
	{
		TP->catch_msg("Wind what? Head or arm?\n");
	}
	
	return 1;
}

string query_auto_load() 
{
    return MASTER + ":"; 
}
