
/* ----------------------------------------------------------------- */
/* Thanks to Aleana for letting me use her code as a guide.. and for */
/* All of her help as always!                                        */
/* ----------------------------------------------------------------- */
/* zippers by rum                                                    */

#pragma save_binary
#pragma warnings all
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <language.h>

void
create_armour()
{
	set_name("gown");
	add_name("dress");
	set_short("@@short_desc");
	
	set_long("Green dress. \n");
	set_at(A_BODY);
	set_ac(0);
	set_af(this_object()); 
	
	add_prop(OBJ_I_VALUE,    30);
	add_prop(OBJ_I_WEIGHT, 1350);
	add_prop(OBJ_I_VOLUME, 7250);
}

string
arm_condition_desc()
{
	return "";    /* do not return a condition message */
}

int
remove_other()
{
	remove_me();
	return 1;
}

int
remove()
{
    if(query_verb() == "quit")
	{
	    write("Oops.. you forgot to get undressed!.\n");
		return 1;
	}
    if(this_player() == query_worn())
	{
	write("It would be a LOT more fun to let someone help you "+
	    "out of this.\n");
	return -1;
	}
    this_player()->catch_msg("You remove " + 
	LANG_POSS(QTNAME(environment())) + " flowing green gown " +
	"slowly running your hands over her skin.\n");

    say(QCTNAME(this_player()) + " removes " +
	LANG_POSS(QTNAME(environment())) + " stunning green gown slowly " +
	"and deliberately.\n", ( { environment(), this_player() } ));

    environment()->catch_msg(QCTNAME(this_player()) + " removes " +
	"your lovely green gown, running his hands over your skin.\n");

    environment()->remove_cmd_item("gown");

    remove_prop(OBJ_M_NO_DROP);
    remove_prop(OBJ_M_NO_GIVE);
    return 1;
}

int
wear()
{
    environment()->add_cmd_item(this_object()->query_names(),
	({"remove"}), ({"@@remove_other:" + file_name(this_object()),
			"@@remove_other:" + file_name(this_object()) }) );

    environment()->update_actions(this_object());

    write("You slip into the gown and smooth it over your body.\n");

    say(QCTNAME(this_player()) + " slips into the lovely green gown " +
	"and smoothes it over her body.\n");

    add_prop(OBJ_M_NO_DROP, "You must remove it first!!\n");

    add_prop(OBJ_M_NO_GIVE, "You must remove it first!\n");
	
    return 1;
}

string
short_desc()
{
    if(this_object()->query_worn())
      {
	return "flowing emerald-green sleeveless silk gown, "+
	    "tied at the waist with silk string. ";
      }
    return "gown";
}
