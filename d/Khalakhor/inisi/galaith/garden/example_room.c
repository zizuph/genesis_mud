inherit "/std/room";



public int
exit_desc()
{
   this_player()->catch_msg("You jump down into the pit before you!\n");
   return 1;
}

public void
create_room()
{

  add_exit("joinroom", "down","@@exit_desc");
}

