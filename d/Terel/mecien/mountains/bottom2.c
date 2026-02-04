inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define NUM 1

reset_room(arg)
{
    object *dragon;
    int i;
    dragon = allocate(NUM);
    if(present("dragon"))
	return;
    for(i = 0; i < NUM; i++)
    {
	dragon[i]=clone_object("/d/Terel/mecien/mountains/dragon");
	dragon[i]->move(this_object());
    }
}

create_room(){
    set_short("Cave");
    set_long(
"This massive cavern is hewn from ice and stone. The floor of the cavern\n"
+"is littered with scales, bones and shards of different objects. There is\n"
+"a great deal of ash about. There are many markings upon the walls.\n"
	     );
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Terel/mecien/mountains/bottom1", "north", 0);
    add_exit("/d/Terel/mecien/mountains/bottom3", "east", "@@guarded");
    add_item(({"walls","wall","marking","markings"}),
	     "The markings on the walls are those of huge claws.\n");
    reset_room();
}

int
guarded()
{
    object dragon;
    string name;

    dragon = present("dragon");
    if(dragon && dragon->query_name()!="corpse")
    {
	write("The dragon is blocking the way.\n");
	say("The dragon blocks " + QTNAME(this_player()) + "'s way.\n");
	return 1;
    }
 return 0;
}

