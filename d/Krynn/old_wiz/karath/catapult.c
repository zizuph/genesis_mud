inherit "/std/object";

#include "/d/Emerald/defs.h"

int bombard_workroom(string str);

void
init()
{
	add_action(bombard_workroom, "bombard");
	::init();
}

void
create_object()
{
	set_short("enormous catapult");
	set_name("catapult");
	set_long("This enormous catapult can be used by Karath and "+
		"a trusted few to <bombard> an offending wizard's "+
		"workroom with explosive munition. The results are "+
		"rarely an improvement, even to the most messy of "+
		"workrooms.\n");
	add_prop(OBJ_I_NO_GET, 1);
	add_prop(OBJ_M_NO_GET, 1);
}

int bombard_workroom(string str) {
	object missile;

	mixed arr;

	setuid();
	seteuid(getuid());

	notify_fail(str + " isn't a wizard!");

	if (!str || !find_living(lower_case(str))->query_wiz_level)
	return 0;

	arr = explode(find_living(lower_case(str))->query_default_start_location(), "/");
	if (arr[3] != str || arr[4] != "workroom")
	{
		notify_fail("It doesn't appear " +str+ " is in "+
			"a safe place.\n" +
			"/" + arr[1] + "/" + arr[2] + "/" +
			/*arr[2] + "/" arr[3] +*/
			"\n");
		return 0;
	}

	if (missile = clone_object("/d/Emerald/karath/wiz_missile"))
	{
		missile->set_launcher(this_player());

		missile->move(find_living(lower_case(str))->query_default_start_location());
		write(str + " is being bombarded.\n");
		return 1;
	}
}
