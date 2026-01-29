/*
	*Woohoo! A nifty package!!
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
	set_name("package");
	set_pname("packages");
	set_adj("brown");
	set_adj("paper");
	set_short("brown paper package");
	set_pshort("brown paper packages");
	set_long("It is a brown paper package, all tied up " +
	"with string... Isn't that one of your favorite things? " +
	"What could be in this package? Why don't you try to " +
	"'unwrap' it?!\n");
	
		
	add_prop(OBJ_I_WEIGHT, 20); 	
	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_M_NO_STEAL, "Stop it, you thief!\n"); 	

}

void init()
{
	add_action("unwrap_package", "unwrap");
}

int unwrap_package(string str)
{
	TP->catch_msg("You quickly untie the package and " +
	"open it. You then dump its contents into your hand " +
	"toss the wrapping away.\n");
	
	say(QCTNAME(TP) + " quickly unties " + HIS_HER(TP) + " package, " +
	"dumps the contents into " + HIS_HER(TP) + " hand, " +
	"and tosses the wrapping away.\n"); 
	
	clone_object("/w/altrus/obj/toy/yellow_leg.c")->move(TP);
	clone_object("/w/altrus/obj/toy/blue_arm.c")->move(TP);
	clone_object("/w/altrus/obj/toy/green_arm.c")->move(TP);
	clone_object("/w/altrus/obj/toy/violet_head.c")->move(TP);
	clone_object("/w/altrus/obj/toy/red_leg.c")->move(TP);
	clone_object("/w/altrus/obj/toy/rainbow_body.c")->move(TP);
	
	remove_object();
	
	return 1;
}

