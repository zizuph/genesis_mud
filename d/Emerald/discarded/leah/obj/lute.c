inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
	set_name("lute");
	add_name("instrument");
	set_short("painted lute");
	set_adj("painted");
	set_long("This lute is garishly painted but looks comparatively "+
		"new.\n");
	add_prop(OBJ_I_VALUE, 132);
	add_prop(OBJ_I_WEIGHT, 130);
	add_prop(OBJ_I_VOLUME, 140);
}

init()
{
	::init();
	add_action("play","play");
}

int
play(string str)
{
	if(str != "lute")
	{
		this_player()->catch_msg("Play what?/n");
		return 0;
	}
	else
	{
		this_player()->catch_msg("You strum the lute, but it is not tuned "+
		"properly.\n");
		say(QCTNAME(this_player()) +" strums on the lute, but produces an awful noise.\n");
		return 1;
	}
}


string
query_recover()
{
    return MASTER;
}
