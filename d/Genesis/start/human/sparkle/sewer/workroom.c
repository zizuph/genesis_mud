inherit "/std/workroom";

#define ROOM_I_MASTER_HOME "_room_i_master_home"


void
create_workroom()
{
	::create_workroom();
	add_prop(ROOM_I_MASTER_HOME, 0);
	set_long("You find yourself in a softly lit stone chamber. The air " +
		"is warm and dry and filled with the faint fragrance of old " +
		"parchment and vetivert.\n" +
		"Almost sparkling in their slow dance, particles of dust and " +
		"the eddying wisps of smoke illuminated by some indeterminate " +
		"ambient light, drift silently before you. An precedented " +
		"sense of calm and well-being washes over your mind and " +
		"soothes your heart.\n" +
		"Rows upon rows of dusty shelves align the walls, each " +
		"straining under the load of numerous age-old tomes and " +
		"long-forgotten volumes@@desc_master_home@@");

		add_exit("/w/shadowlynx/workroom.c", "aod", "@@is_mortal", 0);
}

string
desc_master_home()
{
  if (this_player()->query_name() == "Erane")
    return ".\n\n"; // add log info here...
  else  
	  return (query_prop(ROOM_I_MASTER_HOME) ?
		  ".\n\nAs you drift into a comforting reverie, a nigh perfect " +
		  "smoke ring sails past your face; you are not alone!\n\n" :
		  "; whoever works here is certainly fond of his books!\n\n");
}

int
is_mortal()
{
  if (this_player()->query_wiz_level())
    return 0;

  this_player()->catch_msg("The aod exit is restricted to members of the " +
    "wizard community!\n\n");
   return 1;
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (ob->query_name() == "Erane")
  {
    add_prop(ROOM_I_MASTER_HOME, 1);
    ob->set_race_name("kender");
  }
}

public void
leave_inv(object ob, object to)
{
  if (ob->query_name() == "Erane")
    remove_prop(ROOM_I_MASTER_HOME);
    
  ::leave_inv(ob, to);
}

