
 /* Paralyze object for death sequence */

inherit "/std/paralyze";

create_paralyze()
{
    set_name("_paralysis_object_");
    set_fail_message("You cannot move as you are paralyzed.\n");
    set_stop_verb("howthehelldidyougethismessage?");
    set_stop_message("");
}
