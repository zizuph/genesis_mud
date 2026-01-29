
#include "../local.h";

inherit SWIM_ROOM;

void
create_swim_room() 
{
    set_short("Lakeside Road");
    set_long("This road continues to wind around the lake. Strangely this " +
	     "area seems quite empty and quiet. The trees seem extremely " +
	     "dark and sinister adding to the feeling that something is " +
	     "wrong. Even the water on the lake sits motionless as you look " +
	     "into its icy depths. You get the feeling you don't belong " +
	     "here.\n");
    add_item("mountains",
        "The mountains on the other side of the lake look majestic and\n" +
        "inspiring. You sigh deeply, hoping beyond hope to LIVE to\n" +
        "visit them some day.\n");
    add_item("wilderness",
        "Just kidding about the wilderness soothing your soul. This\n" +
        "place gives you the creeps. It's dark and nasty. The woods\n" +
	"to the east of you seem to have eyes, and you walk along the\n" +
	"path with your guard up.\n");
    add_item(({"trees","forest"}),
       "There seem to be hundreds of eyes watching you!\n");
    add_item("eyes","Well, maybe they're not really there ...\n");
    add_exit(ROOM + "lake3","southeast",0);
    add_exit(ROOM + "lake5","west",0);
}
