
inherit "obj/bull_base";

reset(arg)
{
	::reset(arg);
	if (arg)
		return;
	set_board_name("players/Shire/common/guild/shire_board");
	set_num_notes(15);
	set_anonymous(1);
	set_silent(0);
	set_show_lvl(0);
	set_remove_lvl(10);
	set_remove_str("Sorry, you can't do that");
}
