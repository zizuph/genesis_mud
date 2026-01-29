
#pragma save_binary

inherit "/std/object";
#include "/sys/stdproperties.h";

create_object()
{
	set_name("portal maker");
	set_short("a portable portal maker");
	set_long("Do 'portal' to create a portal to the wizards island in the church.\n");
	add_prop(OBJ_I_NO_DROP, 1);
}

new_portal(str)
{
	object	ob;

	ob = clone_object("/d/Wiz/tech/wiz/w_portal");

	ob->set_name("portal");
	ob->set_short("golden portal");
	ob->set_long("A shimmering gold portal is hovering in the air.\n" +
		"Do 'enter' to travel into the portal and visit the island of wizards.\n");
	ob->add_exit("/d/Wiz/tech/wiz/w_green", "enter");
	ob->move("/d/Genesis/bb/church");
	write("A portal is created in the church!\n");
	tell_room("/d/Genesis/bb/church", "A portal materializes into existence in front of your eyes!\n");
	return 1;
}

init()
{
	if(environment(this_object()) != this_player()) return;

	add_action("new_portal", "portal");
}
