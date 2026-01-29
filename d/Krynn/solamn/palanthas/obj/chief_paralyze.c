
#include "../local.h";

inherit "/std/paralyze";

void
create_paralyze()
{
	set_name("chief_para");
	set_long("The chief's paralytic object.\n");
	set_stop_verb("");
	set_stop_object(0);
	set_stop_message("You feel like you can move again.\n");
	set_fail_message("You are held too fast to be able to do anything.\n");
}