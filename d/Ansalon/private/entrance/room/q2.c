#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define ODIR      "/d/Ansalon/private/entrance/obj/"
#define HOOPAK    ODIR + "hoopak" 
#define PEBBLE    ODIR + "pebble"
#define CHAINS    ODIR + "chains"
#define KNIFE     ODIR + "knife"
#define POUCH     ODIR + "pouch"
#define LOCKET    ODIR + "locket_right"
#define ROPE      ODIR + "rope"
#define SKELETON  ODIR + "skeleton"

int search_phase = 0;
int disturbed = 0;
object door;

void
reset_kendermore_room()
{
    search_phase = 0;
    disturbed = 0;
}

void
create_kendermore_room()
{
    set_short("A damp dimly lit stone room");
    set_long("You have landed in what seems to be an old damp " + 
        "dungeon! Rough black stone surrounds you, from floor to " + 
        "walls to ceiling. A pile of dirty hay lies in the corner, " + 
        "most likely bedding for the unfortunate prisoners. "); 
    add_item(({"stone", "black stone", "rough stone", "rough black stone",
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this cell. Black mold covers most of the stone.\n");
    add_item(({"mold", "black mold"}), "It looks like it has been growing " + 
        "for centuries.\n");
    add_item(({"hay", "pile of hay", "pile", "hay pile", "bedding"}), "The " + 
        "The hay looks " + 
        "dirty and smelly. @@disturb_hay@@\n");
    add_item(({"wall", "walls", "black wall", "black walls", "stone wall",
        "stone walls", "black stone wall", "black stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",
        "rough black stone wall", "rough black stone walls"}), "They are " + 
        "made of limestone, and covered with a thick layer of black mold.\n");
    add_item(({"layer", "mold", "mold layer", "black mold", "thick layer"}),
        "It looks like it's been growing here for centuries. Some of it " + 
        "has been scraped away near the pile of hay to reveal a surface " + 
        "of grey stone.\n");
    add_item(({"surface", "grey stone"}), "There are some charcoal marks " + 
        "scratched onto the cleared away area.\n");
    add_item(({"marks", "charcoal marks", "cleared area", "area"}), "The " + 
        "marks read:\n\n'My name is Gusslehan Shadowpoker, and I'm about " + 
        "to go on the most exciting journey anyone can ever take. I " + 
        "wonder if I'll see...'\n");
    add_item(({"bone pile", "pile of bones", "bones", "soul", 
        "poor soul", "poor unfortunate soul"}),
        "They look like kender bones!\n");
    add_item(({"floor", "floors"}), "They are a bit slippery, covered " + 
        "with a thick layer of black mold.\n");
    add_item("ceiling", "An occasional drop of water drips down from the " + 
        "ceiling. It is covered in a thick layer of black mold.\n");
    add_item(({"water", "drop"}), "Water drips down from the ceiling " + 
        "into a shallow puddle on the floor.\n");
    add_item(({"puddle", "shallow puddle"}), "Water drips slowly into " + 
        "the puddle on the floor, making a steady and annoying sound.\n"); 
    add_search(({"hay", "pile", "hay pile", "pile of hay", "bedding"}),
        0, "find_bones", 1);
    add_search(({"bones", "kender bones", "soul", "poor soul",
        "unfortunate soul", "poor unfortunate soul", "pile of bones",
        "bone pile"}), 0, "find_junk", 1);
    set_tell_time(300);
    add_tell("A single drop of water separates itself from the ceiling " + 
        "and falls into the puddle, leaving a slight echo in the room.\n");
    add_tell("The sound of something large moving above you can be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("You slip slightly on the mold on the floor.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");
    door = clone_object(ODIR + "qdoor1");
    door->move(TO);
    reset_kendermore_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(interactive(ob))
        start_room_tells();
}

string
find_bones()
{
    log_file("kender/search", TP->query_name() + " searched hay on " +
        ctime(time()) + ".\n");

    if (!disturbed)
    {
        disturbed = 1;
        return "You search through the smelly pile of hay, and find " + 
            "a pile of kender bones. You also get your hands dirty.\n";
    }

    if (disturbed)
        return "You find nothing more in the smelly pile of hay.\n";
}

string
find_junk(object who, string what)
{
    string str;
    switch(search_phase)
    {
    case 0:
        clone_object(HOOPAK)->move(who, 1);
    str = "You find a hoopak in the pile of bones!\nWhat else might possibly be there...\n";
        break;
    case 1:
        clone_object(PEBBLE)->move(who, 1);
        str = "You find a small round pebble in the pile of bones!\n";
        break;
    case 2:
        clone_object(CHAINS)->move(who, 1);
        str = "You find a pair of manacles!\n";
        break;
    case 3:
        clone_object(KNIFE)->move(who, 1);
        str = "You find a knife!\n";
        break;
    case 4:
        clone_object(POUCH)->move(who, 1);
        str = "You find an old tattered pouch!\n";
        break;
    case 5:
        clone_object(LOCKET)->move(who, 1);
        str = "You find a tarnished broken silver locket!\n";
        break;
    case 6:
        clone_object(ROPE)->move(who, 1);
        str = "You find a long sturdy rope!\n";
        break;
    case 7:
        clone_object(SKELETON)->move(who, 1);
        str = "There doesn't seem to be anything left but bones, which " + 
            "you carefully pick up to take out of this horrible place.\n";
        break;
    default:
        str = "There doesn't seem to be anything left in the " +
            "remaining pile of bones. It seems the skeleton was " +
            "only the last of many such victims.\n";
        break;
    }
    search_phase++;
    log_file("kender/search", TP->query_name() + " searched bones " +
        "on " + ctime(time()) + ".\n");
    return str;
}

string
disturb_hay()
{
    if (disturbed)
        return ("It looks recently disturbed. A pile of kender bones " + 
            "lies amidst the hay.");
    else
        return ("It looks like it hasn't been touched in years.");
}
