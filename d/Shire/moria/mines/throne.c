#include "defs.h"
#include <macros.h>

int push_strength;
int opened; 
object *pushers;

void stop_push(object ob);

CONSTRUCT_ROOM {
    set_short("By the throne");
    set_long("You are standing by the throne! At close range you can see "+
	     "a lot of holes where there used to be jewelry, completely " +
	     "destroying the decorations. The hall extends to the east, " +
	     "and to the south there hangs some heavy velvet draperies. " +
	     "There is also a walk-way leading west.\n"); 
    add_item(({"velvet","drapery","draperies","velvet drapery"}),
	     "Well, you might go there, just try south!");
    add_item(({"decorations","holes"}), 
	     "There *used* to be jewelries here, but obviously no more.");
    add_item("throne","@@exathrone@@");
    add_item("hall","It extends eastwards.");
    add_item("walk-way","Might get you somewhat west.");
    EXIT("durhall","east");
    EXIT("draperies","south");
    EXIT("npass2","west");
    opened = 0;
    pushers = ({});
}

RESET_ROOM {
    remove_exit("down");
    opened = 0;
    set_long("You are standing by the throne! At close range you can see "+
	     "that the decorations are destroyed, and a lot of holes where "+
	     "there used to be jewelry. The hall extends east, and to the "+
	     "south hangs some heavy velvet draperies. There is a walk-"+
	     "way to the west.\n"); 
} 

init() {
    ::init();
    add_action("my_down","down");
    add_action("my_down","d");
    add_action("my_move","move");
    add_action("my_move","push");
}


push(str) {
    int i;

    if (opened) {
	write("But it is already opened!\n");
	return 1;
    }

    if (member_array(TP, pushers)>=0) {
	write("You are already pushing the throne!\n");
	return 1;
    }
    if (TP->query_fatigue()<=20) {
	write("You are too tired to do any effect.\n");
	return 1;
    }

    write("You try to push the throne with all your strength.\n");
    tell_room(ETP,
	      QCTNAME(TP)+" tries to push the throne.\n", TP);

    pushers += ({ TP });
    push_strength = calc_strength();

    set_alarm(10.0, 0.0, &stop_push(TP));

    if (push_strength>150) {
	write("You manage to push the throne out of its position!\n");
	write("Underneath you can see a dusty entrance into some stairs.\n");
	say(QCTNAME(TP) + " pushes the throne, thereby revealing "+
	    "a secret entrance!\n", TP);
	opened = 1;
	set_long(
	    "You are standing by the throne! At close range you can see "+
	    "that the decorations are destroyed, and a lot of holes where "+
	    "there used to be jewelry. The hall extends east, and to the "+
	    "south hangs some heavy velvet draperies. There is a a walk-"+
	    "way to the west. There is a dusty entrance under the throne "+
	    "leading downwards.\n");
    }
    else {
	write("You give all your strength, but the throne won't move.\n");
	say(QCTNAME(TP)+" makes a pitiful atempt of moving the "+
	    "throne.\nPerhaps you could help him?\n");
    }
    return 1;
}

int
my_move(string str) 
{
    notify_fail(CAP(query_verb())+" what?\n");
    if (!strlen(str)) 
	return 0;

    if (str == "throne" || str == "seat") {
	push(str);
	return 1;
    }
    if (str == "thrown")
	return notify_fail("Smirk... Now this is a quite typical error.\n"+
			   "Most can laugh at it, but not Xar, because\n" +
			   "he does it all the time. Have fun!\n"+
			   "\nSir Rogon.\n");
    return 0;
}

my_down() {
    if (!opened)
	return 0;
    this_player()->move_living("down",THIS_DIR+"kingsecr");
    return 1;
}

string
exathrone() {
    if (opened)
	return "There is a entrance down under it!\n";
    else 
	return
	    "There *used* to be jewelries here, but long gone into others' "+
		"pockets.\n";
}

int
calc_strength()
{
    int i, s=0;
    
    for(i=0;i<sizeof(pushers);i++)
	s += STR(pushers[i]);
    return s*sizeof(pushers)/3;   /* I.e.: 12 newbies of strength 5
				     each can move it, but not one
				     champion with strength < 450 */
}

stop_push(object who)
{
    if (member_array(who, pushers)==-1)
	return;
    if (!opened) {
	who->catch_msg("In exhaustion, you stop trying to push it.\n");
	who->catch_msg("Perhaps you should try to find someone to help you?\n");
    }
    else {
	who->catch_msg("As you succeded, you stop pushing it.\n");
    }
    pushers -= ({ who });
    who->add_fatigue(-20);
}

void
leave_inv(object what, object dest)
{
    stop_push(what);
    ::leave_inv(what, dest);
}
