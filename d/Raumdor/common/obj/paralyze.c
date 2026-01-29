/* 2017-08-31 Malus: Creating a paralyze object for common use */

inherit "/std/paralyze";

void
create_paralyze()
{
    set_name("_raumdor_paralyze_object");
    set_fail_message("You are paralyzed!\n");
    set_stop_message("You manage to regain control of yourself.\n");
}

