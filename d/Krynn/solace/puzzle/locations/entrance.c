/* The entrance room. ~solace/puzzle/locations/entrance */

#include "../defs.h"
#include "/sys/macros.h"

inherit ROOM_DEFS;

object occupied;

void load_puzzle_area()
{
    int i;
    string *tmp, *rooms = ({ });

    tmp = get_dir(LOCATIONS + "*.c");

    for(i = 0; i < sizeof(tmp); i++)
        rooms += ({ extract(tmp[i], 0, strlen(tmp[i]) - 3) });

    for(i = 0; i < sizeof(rooms); i++)
        if(!objectp(find_object(LOCATIONS + rooms[i])))
            (LOCATIONS + rooms[i])->teleledningsanka();
}

void create_puzzle_room()
{
    set_short("A small entrance room");
    set_long("You find yourself in a coarsely built stone-walled room. Two "+
        "small barred alcoves at head-height in the walls contain lighted, "+
        "red-flamed torches to give off a little light. On the nearest wall, "+
        "you notice a sign. To the south, an exit leads away from here. ");

    add_exit(LINK_ROOM, "south", 0, 1);

    add_item(({"light", "small light"}), "@@light_desc");

    add_item(({"room", "coarsely built stone-walled room", "stone-walled room",
        "coarsely built room"}), "You are standing in it.\n");

    add_item("ceiling", "The ceiling is made from the same medium-sized "+
        "rectangular blocks of smooth cold grey stone as the walls.\n");

    add_item(({"wall", "walls", "north wall"}), "The walls are made from "+
        "medium-sized blocks of cold grey stone. In the north wall is a "+
        "solidly built metal door.\n");

    add_item("sign", "The sign is made from a dark, harshly grained wood. "+
        "Angular writing has been carved carefully into it. You think you "+
        "may just be able to understand what it says.\n");

    add_item(({"alcove", "alcoves", "barred alcoves","small alcoves", "small "+
        "barred alcoves", "two small barred alcoves"}), "Alcoves in the "+
        "walls. Each one is barred and contains a softly burning torch.\n");

    add_item(({"torches", "red-flamed torches"}), "Softly glowing torches "+
        "crackling and giving off a red glow that lights the room enough "+
        "for you to be able to see properly. They are placed in barred "+
        "alcoves so nobody can reach in and take them.\n");

    add_item(({"blocks of cold grey stone", "medium-sized block of cold stone",
        "stone", "blocks of stone", "medium-sized blocks of stone", "blocks "+
        "of cold stone", "blocks of grey stone", "cold stone", "grey stone",
        "cold grey stone", "medium-sized blocks of cold grey stone", "medium-"+
        "sized blocks of grey stone"}), "You don't see anything of particular "+
        "interest about them.\n");

    add_item(({"floor", "ground"}), "The floor consists of many small "+
        "coloured pebbles joined together to form a mosaic of a tall, "+
        "disturbing human cowled by a dark cloak. His shadowed face is "+
        "pale and scarred and bears a look of torturous longing for escape "+
        "from some unbearable pain inflicted up him. His hands are cast above "+
        "his head and sparks of electricity play between them magically while "+
        "a dark, cloud filled sky plays overhead.\n");

    room_add_object(DOORS + "ent_door");
}

void init()
{
    ::init();

    add_action("do_read", "read");

    load_puzzle_area();
}

/* Extra check for people who return from Link Death! */
void enter_inv(object ob, object from)
{
  object hands = present("hands", ob);
  
  if(objectp(hands))
  {
    hands->remove_prop(OBJ_M_NO_DROP);
    hands->move(find_object(LOCATIONS + "entrance"));
  }

  ::enter_inv(ob, from);    
}

string light_desc()
{
    return "A light above the door in the north wall. It glows with a "+
        "faint "+(objectp(occupied) ? "red" : "green")+" light.\n";
}

object query_occupied()
{
    return occupied;
}

void set_occupied(object obj)
{
    occupied = obj;

    tell_room(TO, "The light above the door switches from "+(objectp(occupied) ?
        "green to red" : "red to green")+".\n");
}

int do_read(string what)
{
    string str, border = "      [:]=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="+
                                "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-[:]\n";
    if(!strlen(what))
        return 0;

    if(what == "sign")
    {
        str  = (objectp(occupied) ? C(RNAME(occupied)) : "Nobody");
        str += " is present in the area beyond the metal door.";

        write("The sign reads:\n\n");
        write(border + "      |*| "+sprintf("%|60s", str)+" |*|\n" + border);

        if(!TP->query_invis())
            say(QCTNAME(TP)+" reads the sign on the wall nearby.\n");
        return 1;
    }
    else
        write("Read what? IE: 'read sign'.\n");

    return 1;
}
