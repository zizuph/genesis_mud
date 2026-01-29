inherit "/std/paralyze.c";

void 
create_paralyze()
{
	::create_paralyze();
	set_fail_message("You don't wanna do anything but rest.\n");
}
