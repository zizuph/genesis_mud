#pragma save_binary

inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/sys/defs.h"


//   Protoypes
void go_away();
void wither();

string color;

create_object() {
    color = ONE_OF_LIST(({"orange","purple","red","white","yellow"
	,"violet","maroon","blue","golden"}));
    set_short("beautiful " + color + " flower");
    set_pshort("beautiful " + color + " flowers");
    set_long(break_string(
	"This is a beautiful " + color + " flower. It smells wonderful and "
	+ "looks like no other flower in this neighbourhood. It looks like it "
	+ "has been put here by divine providence.\n",70));
    set_name("flower");
    set_pname("flowers");
    set_adj(({"beautiful",color}));

    add_prop(OBJ_I_NO_GET,1);
    add_prop(OBJ_I_NO_INS,1);
    set_alarm(300.0,0.0,&wither());
}

get() {
    write("The flower is far too fragile to pick. You decide to leave it alone.\n");
    return 1;
}

void
wither() {
    set_short("withered " + color + " flower");
    set_pshort("withered " + color + " flowers");
    set_long("The once beautiful " + color + " flower is withering slowly.\n");
    set_adj(({"withered",color}));
    set_alarm(400.0,0.0,&go_away());
}

void
go_away() {
    tell_room(environment(), "The withered flower crumbles to dust.\n");
    remove_object();
}
