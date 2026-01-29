#include "rom.h"

#include <wa_types.h>
#define NO_STEEDS add_prop(ROOM_I_ALLOW_STEED, 0)

int trap_is;	     /* If the trap is installed */
int boulders_block;  /* If the boulders block the entrance. */

create_rom() 
{
    set_short("Big hole");
    set_long("@@long_desc@@");
    add_item(({"hole", "ground", "crack"}),
	 "There isn't much to tell, except that the crack south seems darker.\n");
    add_item("trap",
	"Hmm. It seems like you can't do nothing with it from here..\n");
    trap_is = 1;
    UP("cleft");
    SOUTH("crack");
//add_prop(ROOM_I_ALLOW_STEED, 0);
    NO_STEEDS;
}

init()
{
    ::init();
    add_action("do_climb", "climb");
    add_action("do_climb", "enter");
}

int
do_climb(string str)
{
    if (member_array(str, ({ "up", "boulders", "rock", "rocks", "slope" }))==-1)
        return notify_fail(capitalize(query_verb())+" what?\n");

    TP->command("up");
    return 1;
}

int
trap_installed() { return trap_is; }

void
disarm_trap() {
    trap_is = 0;
}

void
install_trap() {
    trap_is = 1;
}

int
boulders_block_exit()
{
    return boulders_block;
}

string
long_desc()
{
    if(!boulders_block) return
	"You have arrived at the bottom of a big hole in the ground. "+
	"You might be able to climb up again, but an easier way is south, "+
	"through a crack in the mountain. ";
    else return
	"You have arrived at the bottom of a big hole in the ground. "+
	"You might be able to climb up again. You notice that lots of boulders "+
	"might block a south-going passage, but you surely would never be able "+
	"to dig yourself through. ";
}


void
reset_boulders() {
    if(boulders_block) {
	tell_room(TO,
	    "As ridiculous it might seem, suddenly all the slabs of boulders "+
	    "heaves and by some intricate system of ropes is put firmly onto "+
	    "there places further up. You notice now a passage through a crack "+
	    "in the mountain to the south.\n");
	tell_room(STAND_DIR+"crack",
	    "Suddenly you hear scratchings and rumbles as the before blocked "+
	    "exit to the north reveals into an opened passage into a big hole.\n");
	tell_room(STAND_DIR+"cleft",
	    "You are startled to hear scratches and rumbles as all the slabs "+
	    "of boulders are heaved up by intricate ropes and machinery.\n");
	SOUTH("crack");
    }
    boulders_block = 0;
}

boulders_fall(object causer)
{
    object *here = all_inventory(TO);
    int i;

    causer->catch_msg(
	"HELP!!!!\n"+
	"In a sudden moment, you realize that you have stepped on a trap!!\n");
    tell_room(TO,
	"Large boulders releases from above and crashes into your body!\n");
    for(i=0;i<sizeof(here);i++)
	if(here[i] && living(here[i])) {
	    here[i]->catch_msg("A large boulder hits your head, severely!!\n");
	    here[i]->heal_hp(-random(1000));
	    if(here[i]->query_hp()<=0)
		here[i]->do_die();
	}
    remove_exit("south");
    boulders_block = 1;
}

notify_step_on_trap(int stats, object tp)
{

    if(!trap_is)
	return;

    if(stats<random(200)) {
	boulders_fall(tp);
	return;
    } else {
	tp->catch_msg(
	    "You suddenly realize that you were about to step on a "+
	    "trap!! Luckily, you bounce away, thereby avoiding to set "+
	    "it. Hmm. Better try to disarm that trap before you slide down "+
	    "next time!\n");
	tell_room(TO,
	    QCTNAME(tp)+" arrives sliding down into the hole, but lucky for "+
	    "him (and you!) "+HE_SHE(tp)+" manages to bounce off the trap.\n", tp);
	return;
    }
}

