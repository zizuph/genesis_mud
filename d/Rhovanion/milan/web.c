inherit "/std/room";

#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>

static int web_points = 100;

void
create_room()
{
    set_name("web");
    set_adj( ({ "sticky", "big" }) );
    set_long("@@longdesc@@");
    set_short("@@shortdesc@@");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(ROOM_I_INSIDE,1);	/* This is a real room */
}

string
longdesc()
{
    object *in;
    string text, race;

    if (environment(this_player()) == this_object())
	return "You are inside of a sticky web. The huge thick strands " +
	       "disable almost any of your movement. They are so tight " +
	       "around you that you can hardly breath.\n";
    if (present("spider", environment()))
	text = "This big sticky web is guarded by the black spider.";
    else text = "This is a big sticky web. It must have taken an enormous " +
		"spider to weave this.";
    if (sizeof(in = all_inventory()))
    {
	if (living(in[0]))
	    text += " Something is still wriggling inside and from the "+
		    "shape and size you guess that it is some poor "+
		    in[0]->query_race_name() + ".";
	else if (race = in[0]->query_race())
	    text += " From the shape and size you guess that it contains "+
		    "a corpse of some poor " + race + ".";
    }
    return text + "\n";
}

string
shortdesc()
{
    if (environment(this_player()) == this_object())
	return "In the sticky web";
    return "sticky web";
}

int
outside_cut(string arg)
{
    string withwhat;
    object weapon;

    if (!parse_command(arg, this_player(),
		       "[the] [sticky] 'web' 'with' [the] %s", withwhat))
    {
	notify_fail("Cut what?\n");
	return 0;
    }
    if (present("_spider_paralyze_", this_player()))
    {
        write("You are paralysed by spider poison!\n");
        return 1;
    }
    if (!(weapon = present(withwhat, this_player())))
    {
	write("Cut web with what?\n");
	return 1;
    }
    if (present("spider", environment()))
    {
	write("The spider wont let you close to the web.\n");
	return 1;
    }
    if ((member_array("/std/weapon.c", inherit_list(weapon)) == -1) ||
	!(weapon->query_dt() & W_SLASH))
    {
	write("You can't cut the web with that!\n");
	return 1;
    }
    if (weapon->query_wielded() != this_player())
    {
	write("It might help if you wielded it!\n");
	return 1;
    }
    write("You cut at the web with your " + weapon->short() + ".\n");
    say(QCTNAME(this_player()) + " cuts at the web with " +
	this_player()->query_possessive() + " " + weapon->short() + ".\n");
    tell_room(this_object(), "The web shakes as someone cuts at it.\n");
    web_points -= (random(weapon->query_pen() * 6));
    if (!random(MAX(1, 10 - weapon->query_likely_dull())))
	weapon->set_dull(weapon->query_dull() + 1);
    if (web_points < 1) remove_object();
    return 1;
}

int
outside_tear(string arg)
{
    if ((arg != "web") && (arg != "sticky web"))
    {
	notify_fail("Tear what?\n");
	return 0;
    }
    if (present("_spider_paralyze_", this_player()))
    {
        write("You are paralysed by spider poison!\n");
        return 1;
    }
    if (present("spider", environment()))
    {
	write("The spider wont let you close to the web.\n");
	return 1;
    }
    if (this_player()->query_fatigue() < 10)
    {
	write("You are too tired to tear the web.\n");
	return 1;
    }
    this_player()->set_fatigue(this_player()->query_fatigue() - 7);
    web_points -= 1 + random(this_player()->query_stat(SS_STR) / 5);
    tell_room(this_object(), "The web shakes as someone tries to tear it.\n");
    if (web_points < 1)
    {
	write("You found the strength and rip up the web.\n");
	say(QCTNAME(this_player()) + " rips the web.\n");
	remove_object();
	return 1;
    }
    write("You try to tear the web. It seems like " +
	  "the web gave a little bit.\n");
    say(QCTNAME(this_player()) + " tries to tear the web.\n");
    return 1;
}

int
inside_tear(string arg)
{
    if ((arg != "web") && (arg != "sticky web"))
    {
	notify_fail("Tear what?\n");
	return 0;
    }
    if (present("_spider_paralyze_", this_player()))
    {
        write("You are paralysed by spider poison!\n");
        return 1;
    }
    if (this_player()->query_fatigue() < 10)
    {
	write("You are too tired to do that.\n");
	return 1;
    }
    this_player()->set_fatigue(this_player()->query_fatigue() - 10);
    web_points -= 1 + random(this_player()->query_stat(SS_STR) / 4);
    tell_room(environment(), "Something wiggles in the web trying to " +
			     "tear it.\n");
    if (web_points < 1)
    {
	tell_room(environment(), "The web gives way and...\n");
	write("You found the strength and rip up the web.\n");
	remove_object();
	return 1;
    }
    write("You try to tear the web, but you are still stuck. It seems like " +
	  "the web gave a little bit though.\n");
    return 1;
}

void
remove_object()
{
    object *obs = all_inventory();
    int i;

    remove_prop(CONT_I_CLOSED);
    for (i=0; i<sizeof(obs); i++)
    {
	if (living(obs[i]))
	{
	    tell_room(environment(), QCTNAME(obs[i]) + " falls out of " +
		"the web.\n");
	    obs[i]->catch_msg("You fall out of the web.\n");
	}
	else
	{
	    tell_room(environment(), capitalize(LANG_THESHORT(obs[i])) +
		" falls out of the web.\n");
	}
	obs[i]->move(environment());
    }
    ::remove_object();
}

int
catch_all(string actio)
{
    if (this_player()->query_wiz_level())
    {
	write("You escape the web with your wizardly powers!\n");
	return 0;
    }
    if (present("_spider_paralyze_", this_player()))
    {
	write("You are paralysed by spider poison!\n");
	return 1;
    }
    switch(query_verb())
    {
	case "tear":
	case "vitals":
	case "commune":
	case "reply":
	case "praise":
	case "bug":
	case "typo":
	    return 0; /* commands above are alloved */
	case "look": write("You can't see because of the sticky spider " +
			   "silk in your eyes.\n");
	    return 1;
	case "ask":
	case "whisper":
	case "say":
	case "shout": write("There is too much in your mouth!\n");
	    return 1;
	default: write("You are much too stuck to do anything " +
		       "except try to tear yourself out.\n");
    }
    return 1;
}

void
init()
{
    ::init();
    if (environment(this_player()) == environment())
    {
	add_action(outside_cut, "cut");
	add_action(outside_tear, "tear");
    }
    if (environment(this_player()) == this_object())
    {
	add_action(catch_all, "", 1);
	add_action(inside_tear, "tear");
    }
}

