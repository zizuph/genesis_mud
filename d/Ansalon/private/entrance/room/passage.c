#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define RDIR          "/d/Ansalon/private/entrance/room/"
#define DUNGEON_KEY   "/d/Ansalon/private/entrance/obj/dungeon_key"

int found_key = 0;

void
reset_kendermore_room()
{
    found_key = 0;
}

void
create_kendermore_room()
{
    set_short("A secret passageway");
    set_long("This is a secret passageway hidden in the walls of this " + 
        "castle. Torches are mounted on the walls at regular intervals, " + 
        "but it is still difficult to see well. Cobwebs hang down from " + 
        "the ceiling, and some strange looking dust coats the floor. The passageway leads " + 
        "to the south, or you can leave to the east.\n");
    add_item(({"stone", "black stone", "rough stone", "rough black stone",
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this passageway.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",}), "They " + 
        "are made of limestone, and look very sturdy. Torches are " + 
        "mounted on them, lighting the passageway with a dim eerie light.\n");
    add_item(({"floor", "floors"}), "They are made of roughly cut " + 
        "limestone, and covered in dust.\n");
    add_item("dust", "@@dust_desc@@");
    add_item("cobwebs", "They hang down from the ceiling.\n");
    add_item("ceiling", "It is made of roughly cut limestone, and covered " + 
        "with cobwebs.\n"); 
    add_item(({"torch", "torches"}), "The are large tar-drenched " + 
        "torches that light the passageway.\n");
    add_item(({"eerie shadows", "shadows", "eerie shadow", "shadow"}),
        "You can't quite see into the darkest part of the shadowed " + 
        "passageway. This looks like an excellent place to sneak around.\n"); 

    set_tell_time(300);
    add_tell("The sound of something large moving to the south can " +
        "be heard.\n");
    add_tell("A cloud of dust makes you sneeze.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The torches flicker, sending the shadows dancing.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    add_search(({"dust", "floor"}), 0, "find_key", 1);
    add_exit(RDIR + "passage2", "south", "@@passage_message");
    add_exit(RDIR + "q9", "east", "@@leave_message");
    reset_kendermore_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

string
dust_desc()
{
    if (found_key)
        return "It looks like it has been disturbed recently.\n";
    return "The dust hasn't been disturbed in quite some time.\n";
}

string
find_key()
{
    if (found_key)
        return "You don't find anything, but now that you look closer, " + 
            "you can see that the dust has been disturbed lately.\n";

    clone_object(DUNGEON_KEY)->move(TP, 1);
    found_key = 1;
    return "You find a large skeleton key!\n";
}

int
leave_message()
{
    write("You push aside the tapestry and stumble into the office.\n");
    return 0;
}
int
passage_message()
{
    write("Cobwebs brush at your face as you make your way down " +
        "the long passageway. It seems to take a long time to " +
        "travel in this dim light, but finally you reach " +
        "an exit out of the passage.\n");
    return 0;

}
