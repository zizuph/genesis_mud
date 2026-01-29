
#include "../local.h";

inherit SOLACE_ROOM_BASE;

void
create_solace_room() 
{
    set_short("Lakeside Road");
    set_long("Your reverie is totally destroyed, as a huge band of " +
	     "draconians jumps out of the brush at you. They have hidden " +
        "themselves quite well, and you are caught totally unaware. " +
	     "They laugh and jeer at you, and you realize that these are " +
	     "simply adolescents...\nBrrr... NOW you almost believed it! " +
	     "You better don't fall asleep next time while walking along " +
	     "an unguarded road. Looking around, you find that the lake is " +
	     "now south of you and you can see mountains far to the west.\n");
    
    add_item(({"adolescents","adolescent"}),
	     "These draconians may be younger than most warriors, but they " +
	     "definitely are not small or ill-equipped. They are decked out " +
	     "in armor of high quality, and it looks as if they have been " +
	     "sent out by their elders to keep people from finding " +
	     "something out...\nGee... They still are vivid before your " +
	     "eyes.\n");
    add_item("lake",
	     "This is the north shore of Crystalmir lake.\n");
    add_item("mountains",
	     "They're far to the west, but you can see them rising above " +
	     "the trees that are around you.\n");
    add_item(({"brush","trees","undergrowth"}),
	     "The undergrowth is getting dense to the north.\n");

    add_exit(ROOM + "lake10","west",0);
    add_exit(ROOM + "lake8","east",0);
}  
