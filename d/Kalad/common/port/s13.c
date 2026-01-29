#include "default.h"
inherit PORT_ROOM;

#include "/sys/ss_types.h"
#define HARD_TO_MOVE 10
#define DAMAGE 5
string long;

void
create_port_room()
{
    set_short("Street Corner");
    set_long("You are at the base of a huge cliff that towers far above "+
      "you in the north, and continues east and west into the distance. "+
      "A small structure lies directly to the west. "+
      "The street aside the bay ends here, however, a small pier heads east "+
      "from here towards a large wooden platform. The cobblestones beneath "+
      "you are moist and covered with grime. Lying southeast is part of the "+
      "sparkling bay that surrounds the Port District.\n");
    add_item(({"base","huge cliff","cliff"}),"A towering rock face that "+
      "dominates the surrounding area with its imposing size. It looks like "+
      "the edge of a great plateau.\n");
    add_item(({"street"}),"The cobblestoned road heads south.\n");
    add_item(({"small pier","pier"}),"Like a small wooden appendage of "+
      "the district, it stretches into the bay and connects the land with "+
      "an outlying platform.\n");
    add_item(({"large wooden platform","large platform","wooden platform","outlying platform","platform"}),
      "A relatively large construct built of hardwood planks sitting within "+
      "the bay. A large building has been built upon it.\n");
    add_item(({"large building"}),"You can see no details from here.\n");
    add_item(({"cobblestones","cobblestone"}),"They are cracked and "+
      "weathered from the perpetual moisture.\n");
    add_item(({"grime"}),"Little bits of greenish filth is spread over "+
      "the cobblestones.\n");
    add_item(({"sparkling bay","bay"}),"Colored a deep azure, its beauty "+
      "is matched only by the skies above.\n");
    add_item(({"skies","sky"}),"A mirror image of the bay below.\n");
    add_item(({"small structure","structure"}),"It looks to be some sort "+
      "of warehouse.\n");
    add_exit(PORT + "s14", "east","@@move");
    add_exit(PORT + "s29", "south");
}

move()
{
    if(TP->query_skill(SS_SWIM) < random(HARD_TO_MOVE))
    {
	write("You fearfully step onto the pier...\n");
	write("You stumble backwards and hurt yourself for fear of falling off!\n");
	TP->heal_hp(-DAMAGE);
	say(QCTNAME(TP) + " stumbles backwards and gets hurt for fear of falling off the pier!\n");
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }

    write("You bravely step onto the pier.\n");
    return 0;
}

