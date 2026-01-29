inherit "/std/door";

create_door()
{
    set_door_id("door");
    set_door_desc("It's rather tall and made out of brownish rock.\n");
    set_open_desc("@@open_description@@");
    set_closed_desc("@@closed_description@@");
    set_pass_command(({ "n", "north" }));
    set_door_name(({ "door", "stone door" }));
    set_other_room("/d/Shire/khazad/wcamp/camp_tunnel4");
    set_open(0);
    set_open_command("open");
    set_close_command("close");
}
 
string
open_description()
{
  return "There is an open stone door leading north.\n";
}
 
string
closed_description()
{
  return "There is a closed stone door leading north.\n";
}
