
#include "../local.h";

inherit SOLACE_ROOM_BASE;

void
create_solace_room() 
{
    set_short("Lakeside Road");
    set_long("As you stroll casually along, you see a butterfly flitting " +
	     "through the air, and some bluejays chasing each other around " +
	     "playfully. You stop to watch for a while, chuckle to " +
	     "yourself, and resume your journey.\n");
    
    add_item(({"bluejays","bluejay","birds","bird"}),
	     "These two birds are having the time of their lives. They " +
	     "soar and dive, and nip at each other playfully.\n");
    add_item("butterfly",
	     "This is the biggest monarch butterfly you have ever seen.\n");
    add_exit(ROOM + "lake9","west",0);
    add_exit(ROOM + "lake7","southeast",0);
}
