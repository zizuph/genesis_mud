/*The inside of the charity box.   Styles 920529. */

#pragma save_binary

inherit "/std/room";
#include "/sys/language.h";



mixed box;  /* The environment of the box. */

create_room() {
 
    set_short("Inside the charity box.");
    set_long("\n"+
     "Inside the box.\n"+
     "You are inside a large wodden box.\n");
    
    add_item(({"wood", "box"}),"It looks like a quite normal wooden box.\n");
    box = "/d/Genesis/start/human/town/church";
}

init() {
    add_action("out","out");
    ::init();
}

set_box(box_env) {
    box = box_env;
}

out() { 
    call_out("move_out", 1, ({this_player(), box}));
    write("Hmm... It isn't easy to crawl out of here.\n");
    return 1;
}


move_out(arg) {
    tell_object(arg[0],
	"\nWhith an effort you manage to get out of the box.\n\n");
    arg[0]->move_living("with a major effort", arg[1]);

}