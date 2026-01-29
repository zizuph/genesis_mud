#include "valley.h"

int rod;

create_valley() {
    rod = 1;
    
    set_short("Crossing");
    set_long("You have arrived at the crossing.\nA small path from the south "+
	     "branches out in a winding path to the north, an obscure track "+
	     "east to a hill and a path to the west. The undergrowth gets "+
	     "denser here, so you can barely see some yards ahead. ");
    add_item(({"path","paths","exit","exits"}),"You see nothing special.\n");
    add_item("hill","It's to the east.\n");
    add_item("undergrowth","@@perhaps@@");
    add_item("branch",
	     "Yes, it is definitely something strange about it! It is "+
	     "loose, and it is black\n.");
    NORTH("greenh");
    SOUTH("winding");
    EAST("hill");
    WEST("roseg");
}

reset_valley() {
    rod = 1;
}

init() {
    ::init();
    add_action("my_staff","grab");
    add_action("my_staff","fetch");
    add_action("my_staff","get");
    add_action("my_staff","take");
}

perhaps() {
  if(random(3) || !rod)
    write("You can`t see an inch ahead of you.\n");
  else
    write("What is that? Isn't that branch kind of odd looking?\n");
  return 1;
}

my_staff(arg) {
    if(!arg) {
      notify_fail(capitalize(query_verb())+ " what?\n");
      return 0;
    }
    if(member_array(arg,({"branch","out branch","branch out",
			    "branch from undergrowth"})) < 0)
      return 0;
          
    if(!rod) {
	write("Ah, it's just another useless branch.\n");
	write("You throw it back again.\n");
	return 1;
    }
/*
    make("obj/staff", this_player());
    write("You grab the branch, and find out it's really a black rod!\n");
    say(this_player()->query_name()+" found something in the bushes.\n");
    rod = 0;
    return 1;
*/
    return 0;
}
