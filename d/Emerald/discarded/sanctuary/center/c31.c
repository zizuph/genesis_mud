inherit "/std/room";

#include "/d/Emerald/defs.h"

create_room()

{
    
    set_short("A small dirty alley");
    
    set_long("   You enter an even smaller dirty alley hidden among " +
        "the streets of Sanctuary.  You can hear laughter and rough " +
        "voices from a doorway to the north.  Lamplight barely wards " +
        "off the deep shadows surrounding the entrance to this building. " +
"High above the entrance is a coat of arms; the paint cracked and " +
"peeling. \n\n");
    
    add_exit("vulgar", "enter", "@@enter_msg@@");
    
    add_exit("c32", "east", 0, 2);
    
    add_exit("c34", "southwest", 0, 2);
    
    add_item(({"plaque","coat of arms"}), "The coat of arms above " +
        "the entrance looks to be in need of a new coat of paint. A " +
        "leering grey unicorn is depicted against a black and red checked " +
        "background. There seems to be some sort of graffiti written below " +
        "the coat of arms.\n");
    
    add_item(({"unicorn","horse"}), "The unicorn painted on the " +
        "coat of arms seems to be leering evilly at you.\n");
    
    add_item(({"writing", "graffiti"}), "Far from an Angel. " +
        "Upon my death, when the stains of my soul are read " +
        "by HE who sits in judgement, I'll be given my own " +
        "small space in Hell.\n" + 
        "Here the gates of dark Death stand wide.\n");
    
}

int
enter_msg()
{
    write("You enter the Vulgar Unicorn ...\n\n");
    say(QCTNAME(this_player())+ " enters into the Vulgar Unicorn.\n");
    return 0;
}
