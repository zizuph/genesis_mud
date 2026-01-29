inherit "/std/door";

create_door()
{
set_door_id("tower_hatch");
set_pass_command(({"d","down"}));
set_other_room("/d/Calia/ciryan/workroom/lower_floor.c");
set_open(0);
set_door_name(({"wooden hatch","hatch"}));
set_open_command("open");
set_open_mess("You open the hatch.","Someone just opened the hatch.");
set_fail_open("The hatch is already open.");
set_close_command("close");
set_close_mess("You close the hatch.","Someone just closed the hatch.");
set_fail_close("The hatch is already closed.");
}
