/* Dwarven camp base file for Haven.
* By Morrigan, Jan 97
*/

#include "/d/Krynn/haven/local.h"

inherit HERBSEARCHNEW
inherit OUT;

string *herbs = HERB_MASTER->query_herbs( ({ "hills", }) );

public void
reset_haven_room()
{
    set_searched(random(2));
}

public void
create_camp()
{

}

nomask void
create_haven_room()
{
    set_place(DWARVES);
    set_long_desc("You are in a dwarven camp, southwest of Haven. The "+
		  "dwarves here have probably come from the Neidar kingdom far to "+
		  "the south to trade with the inhabitants of Haven.");
    
    add_item(({"peaks","twin peaks", "Twin Peaks"}),"The Twin Peaks are the "+
	     "highest Peaks of the mountains around Darken Wood, the road travels "+
	     "between them. They lie to the distant north of you.\n");
    add_item("sky","It's above you.\n");
    add_item(({"road","winding road"}),"The road from Haven to Solace is "+
	     "back to your north, out of the camp.\n");
    add_item(({"Kharolis", "kharolis", "Kharolis Mountains", "mountains",
		 "kharolis mountains"}), "The massive range of mountains known as the "+
	     "Kharolis loom to your west, travelling both northwards and southwards "+
	     "far beyond the range of your vision.\n");
    add_item(({"Haven", "haven"}), "The capital of Abanasina, Haven, lies to "+
	     "your immediate northeast.\n");
    add_item(({"tent","tents"}),"The dwarves inhabit the tents " +
	     "while on their trading mission.\n");
    
    set_tell_time(400);
    add_tell("The dwarves of the camp are bustling around, apparently waiting "+
	     "for something.\n");
    add_tell("A loud cheer erupts from the city of Haven to your northeast, and "+
	     "a nearby dwarf snorts contemptuously and keeps walking.\n");
    add_tell("A few dwarves setting up a tent suddenly burst into roaring "+
	     "laughter.\n");
    add_tell("You see a dwarf carrying boxes of goods back and forth between "+
	     "two of the tents.\n");
    
    OUTSIDE;
    
    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
		       ONE_OF(herbs) }), ({ "hills", }), 3);
    
    create_camp();
    reset_haven_room();
    
}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
      start_room_tells();
}

