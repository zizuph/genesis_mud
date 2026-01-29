inherit "std/room";
inherit "/d/Cirath/ak_wela/inherit/room_tell";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    object ob;
    set_short("Yinaga's Bank");
    set_long("You have just entered Yinaga's bank, a surprisingly clean "+
             "place,  considering the busy street outside. You can see no " +
             "furniture, exept the huge oak counter running straight accross " +
             "the room. Between the counter and the ceiling there are sturdy " +
             "looking iron bars, from behind which a gnome peers at you. "+
             "A lot of people go north with heavy bags and come back with "+
             "a lot smaller. It appears you can change money there.\n");
    add_exit(AK_WELA_DIR + "szun_moon6", "south", 0, 2);
    add_exit(AK_WELA_DIR + "changeroom", "north",0,2);
    add_item(({"counter","oak counter"}),"The oak counter looks very "+
              "sturdy, and so does the iron bars. Theese gnomes takes "+
              "good care of the money it seems.\n");
 
    add_item("gnome","The gnome sits safely behind the bars, there "+
             "is no way he can be reached there.\n");

    set_tell_time(60);
    add_tell("A greedy looking man with beady eyes hurries past you to the north room.\n");
    add_tell("The gnome behind the counter looks greedily at your purse.\n");
    add_tell("The gnome peers around carefully and then opens the strongroom "+
             "and throws in some bags. He then quickly closes it again.\n");
    add_tell("You feel something bump into you and with horror you check "+
             "your purse. Luckily all is there.\n");
    ob=clone_object("/d/Genesis/obj/deposit.c");
    ob->move(TO);
}


void enter_inv(object what , object from)
{
	start_room_tells(what);
	::enter_inv(what,from);
}
