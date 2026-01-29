inherit "/std/board";

create_board()
{
    set_board_name("/d/Shire/common/mines/mboard");
    set_num_notes(20);
    set_anonymous(1);
    set_silent(0);
/*    set_show_level(1);
    set_remove_level(10); */
    set_remove_str("Sorry, you are not allowed.");
    set_err_log("/d/Shire/common/mines/ERRLOG");
    set_no_report(1);
    set_keep_discarded(1);
}
