inherit "/std/door";

create_door()
{
    set_door_id("gate");
    set_door_desc("It's a sturdy iron gate with thick bars.\n");
    set_open_desc("@@open_description@@");
    set_closed_desc("@@closed_description@@");
    set_pass_command(({ "s", "south" }));
    set_door_name(({ "gate", "iron gate" }));
    set_other_room("/d/Shire/khazad/wcamp/camp_tunnel4");
    set_open(0);
    set_open_command("open");
    set_close_command("close");
}
 
string
open_description()
{
  return "There is an open iron gate leading south.\n";
}
 
string
closed_description()
{
  return "There is a closed iron gate leading south.\n";
}
