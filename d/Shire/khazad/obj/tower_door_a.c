inherit "/std/door";

create_door()
{
    set_door_id("door");
    set_door_desc("A thick stone door.\n");
    set_open_desc("@@open_description@@");
    set_closed_desc("@@closed_description@@");
    set_pass_command(({ "s", "south" }));
    set_door_name(({ "door", "stone door" }));
    set_other_room("/d/Shire/khazad/wcamp/tower2");
    set_open(0);
    set_open_command("open");
    set_close_command("close");
}
 
string
open_description()
{
  return "There is an open stone door leading south.\n";
}
 
string
closed_description()
{
  return "There is a closed stone door leading south.\n";
}
