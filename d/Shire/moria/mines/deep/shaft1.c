#include "defs.h"
#include <stdproperties.h>

#define ROPE_I_LENGTH "_rope_i_length"

CONSTRUCT_ROOM {
    set_short("In a steep shaft");
    set_long("You are climbing in a steep shaft. The shaft continues "+
	     "further down and looks rather dangerous. You can not "+
	     "continue without the aid of climbing equipment. In the east "+
	     "there is a narrow hole.\n");
    add_item(({"shaft","walls","wall"}),
	     "It is very steep, almost vertical.\n"+
	     "You can see a hook mounted in the sides of the wall.");
    add_item("hook", "The hook is securely fastened in the wall.");
    add_item("hole","You seem to be able to squeeze into it.");
    add_exit(MINES_DIR + "mjunc",   "up");
    add_exit(MINES_DIR + "eelpass", "east");
    add_exit(THIS_DIR  + "bottom",  "down", "@@chk_rope@@");
}

object rope;
object *climbers = ({ });

add_climber(object who)
{
    int i = member_array(who, climbers);
    if (i == -1)
	climbers += ({ who });
}

remove_climber(object who)
{
    climbers -= ({ who });
}

object query_rope() { return rope; }

int
query_rope_length()
{
    if (!rope)
	return 0;
    else if (!rope->query_prop(ROPE_I_LENGTH))
	return 40;
    else
	return rope->query_prop(ROPE_I_LENGTH);
}

int
chk_rope()
{
    if (!rope) {
	write("Uhum.. No, you would fall and break your neck!\n");
	return 1;
    } else {
	add_climber(TP);
	return -10;
    }
}

/*
int
tie_object(object ob, string str)
{
    if (str != "hook") {
	notify_fail("Tie it to what!!?!\n");
	return 0;
    }
    if (rope) {
	notify_fail("There already is a rope fastened to the hook.\n");
	return 0;
    }
    rope = ob;
    if (!rope->query_prop(ROPE_I_LENGTH))
	rope->add_prop(ROPE_I_LENGTH, random(200)+30);
    update_actions();
    return 1;
}

int
untie_object(object ob)
{
    if (sizeof(climbers)) {
        notify_fail("You can't untie it, because the " + rope->short() +
                    " has such a heavy load. Someone must be climbing the " +
                    "rope now.\n");
	return 0;
    }
    rope = 0;
    update_actions();
    return 1;
}
*/
enter_inv(object ob, object from)
{
    if (!living(ob) && ob->query_prop(OBJ_I_WEIGHT)>0 &&
	function_exists("create_object", ob) != "/std/rope")
    {
    (THIS_DIR + "bottom")->teleledningsanka();
	tell_room(TO, "The "+QSHORT(ob)+" drops down into the shaft.\n");
	ob->move(THIS_DIR+"bottom", 1);
	return;
    }
    ::enter_inv(ob, from);
}

init()
{
    ::init();
    if (!rope) return;
    add_action("do_climb", "climb");
    add_action("do_cut",   "cut");
}


do_cut(string what)
{
    int i;

    if (!rope->id(what))
	return 0;
    TP->catch_msg("You cut the "+rope->short()+"!!\n");
    tell_room(TO,
	QCTNAME(TP)+" cuts the "+rope->short()+"!!\n", TP);
    tell_room(TO, "The "+rope->short()+" is cut through and falls down into "+
	"the shaft.\n");
    rope->set_tied_to(0);
    rope->move(THIS_DIR+"bottom");
    rope->remove_prop(OBJ_M_NO_GET);
    rope->remove_prop(OBJ_M_NO_DROP);
    tell_room(THIS_DIR+"bottom", "A "+rope->short()+" falls down!\n");
    for (i = 0; i < sizeof(climbers); i++) {
	climbers[i]->catch_msg("The "+rope->short()+" falls down and you with it!!\n");
	ENV(climbers[i])->do_fall_down(climbers[i]);
    }
    rope = 0;
    return 1;
}


int
do_climb(string what)
{
    if (what == "down" || what == "rope" || rope->id(what))
	return TP->command("down");
    notify_fail("Climb what?\n");
    return 0;
}

object
link_room(string lfile, mixed dest, int pos)
{
    object ob;
    ob = clone_object(THIS_DIR+"shaftcor");
    ob -> setup_pos(pos);
    return ob;
}
