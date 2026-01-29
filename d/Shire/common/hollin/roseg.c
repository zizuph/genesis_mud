#include "valley.h"

int roses;

create_valley() {
    set_short("Rose garden");
    set_long("You are in the rose garden!\nRed, white, yellow and multi-"+
	     "coloured roses surround you. A heavy odour hangs over the "+
	     "area, and you can hear birds singing from somewhere. The "+
	     "roses have sharp thorns so I'll recommend you to look, but "+
	     "not touch!  A path from east stops here, but to the west you "+
	     "discover a ledge, and a tall tree reaching up with lots of "+
	     "leaves and strong branches. ");
    EAST("crossing");
    /* WEST("tree"); */

    add_item(({"rose","roses","thorn","thorns"}),
	     "Them roses have sharp thorns!\n");
    add_item(({"path","ledge","tree"}),
	     "It seems safe to go there.\n");
    add_item(({"amount","how many"}),"@@amount@@");
    roses = 3;
}

reset_valley() {
    if(roses < 20)
       roses += 2;
}

/*

init() {
  ::init();
  add_action("my_touch","touch");
  add_action("my_pick","pick");
  add_action("my_amount","amount");
  add_action("my_smell","smell");
}

my_amount() { 
    write("There are "+roses+" left here.\n"); 
    return 1;
}

my_touch(string str) {
    object glove;
    
    glove = present("garden gloves", this_player());
    if(!str) {
	notify_fail("Touch what?\n");
	return 0;
    }
    if(!glove || !glove->query_worn()) {
	write("Aouch! That hurt!\n");
	say(this_player()->query_name()+ 
	    " touches the roses and hurts himself.\n");
	this_player()->reduce_hit_point(3+random(2));
	return 1;
    }
    write("You easily touch the roses without hurting your hands.\n");
    say(this_player()->query_name()+" touches the roses gracefully.\n");
    return 1;
}

my_pick(str) {
    object glove, rose;

    glove = present("garden gloves",this_player());
    if(!str) {
      notify_fail("Pick what?\n");
      return 0;
    }
    if(!glove || !glove->query_worn()) {
	write("You hurt your hands terribly.\n");
	write("You got to wear some protection.\n");
	say(this_player()->query_name()+
	    " tries to pick some roses, but fails.\n");
	this_player()->reduce_hit_point(5+random(15));
	return 1;
    }
    if(!roses) return notify_fail("You can't reach any good ones here.\n");
    write("Ok.\n");
    say(this_player()->query_name()+" picks some roses.\n");
    rose = clone_object("/players/rogon/obj/rose");
    roses--;
    rose->move(this_player());
    return 1;
}
    
my_smell(str) {
  if(!str) {
    notify_fail("Smell what?\n");
    return 0;
  }
  if(str == "rose" || str == "roses") {
    write("Ahh, they smell wonderfully!\n");
    return 1;
  }
}

*/
