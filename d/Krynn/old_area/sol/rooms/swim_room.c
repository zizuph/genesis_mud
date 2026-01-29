
#include "../local.h";
#include <ss_types.h>

inherit SOLACE_ROOM_BASE;


void
create_swim_room()
{
}

nomask void
create_solace_room() 
{
    set_short("Lakeside Road");
    set_long("This road continues to wind around the lake. Strangely this " +
	     "area seems quite empty and quiet.  The trees seem extremely " +
	     "dark and sinister adding to the feeling that something is " +
	     "wrong. Even the water on the lake sits motionless as you look " +
	     "into its icy depths. You get the feeling you don't belong " +
	     "here.\n");
    add_item("lake",
	     "You see nothing in the crystal clear waters. Sure looks\n" +
	     "inviting though...great for swimming.\n");   
    add_cmd_item(({"lake","water","in lake"}),({"swim","enter"}),"@@swim_me");
    add_item(({"trees","forest"}),
       "There seem to be hundreds of eyes watching you!\n");
    create_swim_room();
}

string
swim_me()
{
    if (TP->query_skill(SS_SWIM) > 20)
      {
	  write("\n");
	  write("You swim across the lake and back.\n");
	  write("\n");
	  TP->move_living("swimming in lake", ROOM + "lake1",0,0);
	  tell_room(ROOM + "lake1",QCTNAME(TP) + " climbs out of the " +
		    "lake.\n", TP);
          return "That felt great!  You return from your swim with a " +
	    "renewed enthusiasm.\n";
      }
    else 
      return "You don't dare, considering your ability.\n";
  
}
