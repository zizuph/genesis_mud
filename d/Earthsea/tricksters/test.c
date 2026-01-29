inherit "/std/room";

void create_room()
{
 set_short("test room");
 set_long("test room.\n");
 add_cmd_item("me","help","@@help_me");
}

int help_me()
{
 write(read_file("/w/ged/tricksters/txt/help/help.txt"));
 return 1;
}
