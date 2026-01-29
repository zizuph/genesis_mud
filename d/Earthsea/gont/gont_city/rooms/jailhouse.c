#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define ALEXANDER "/d/Earthsea/gont/gont_city/liv/marshal"

private object marshal;

public void
reset_room()
{
    if(!objectp(marshal))
    {
        marshal = clone_object(ALEXANDER);
        marshal->move(this_object(), 1);
        marshal->command("emote strides in and looks at you "+
            "suspiciously.");
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("The local jailhouse");
    set_long("This building is made from dark granite, "+
        "as strong and impermeable as the city walls. It looks like it "+
        "might be impossible for someone to break through those dark "+
        "walls. There is little light here, from small windows with thick "+
        "iron bars. You see a dark hallway to the north, from where you "+
        "hear the sound of clanking chains and an occasional scream. In the "+
        "center of the room is an official-looking desk. On the wall are "+
        "posted pictures of criminals that are being hunted by the local "+
        "law. You have the feeling you should not hang around here long. "+
        "\n");
    add_item((({"pictures", "pictures of criminals", "criminals"})),
        "Among the hideous pictures on the wall you spot two that are "+
        "particularly ugly:  Under one you see the name, Handy, with a "+
        "picture of a man with shifty evil eyes, wearing a leather cap. "+
        "Beneath the other is written, Jake the Cannibal Pirate. Jake is "+
        "depicted with a black beard nearly covering his face. He almost "+
        "looks like a goblin. Underneath is written in large letters, "+
        "WANTED DEAD OR ALIVE!\n");
    add_item((({"windows", "small windows"})), "The small windows are "+
        "barred with iron, making escape almost impossible.\n");
    add_item((({"floor", "ceiling", "walls", "stone",
        "flagstones", "granite flagstones", "black stone"})),
        "The walls, floor and ceiling are all constructed from the "+
        "same dark stone as the city walls. The large blocks are fitted "+
        "together without mortar.\n");
    add_item("desk", "There are numerous official-looking "+
        "papers on the solid oak desk.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("city_street/city_road28", "south");
    add_exit("dungeon", "north", "@@cannot_enter");
    reset_room();
}

public int
cannot_enter()
{
    this_player()->catch_tell("That area is off limits!\n");
    return 1;
}
