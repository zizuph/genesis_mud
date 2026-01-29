#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Gilraen;

public void reset_room();

public void 
create_gondor()
{
    set_short("entryhall");
    set_long(BSN("You are standing in the entryhall of the house. Pale stone walls "+
    "look quite emptily back at you. A large table stands here, and a few "+
    "chairs beside it."));
/*
    A doorway leads north, and another leads west. "));
*/
    add_item("walls",BSN("The stone walls bear marks from tapestries that once hung "+
    "there; white squares less yellowed by the sun than the "+
    "rest of the walls. You can't help wondering why the the tapestries are gone. "));
    add_item("table",BSN("The table is large and worn, its best years long past. "));
    add_item("chairs",BSN("They are not exactly new; the seats worn down "+
    "by years of people sitting in them. "));
    add_item("doorways",BSN("The doorways lead into other rooms, you guess. "+
    "Signs of decay are prominent. "));
    clone_object(MINAS_DIR + "obj/wqindoor")->move(TO);
/*
  add_exit(MINAS_DIR+"houses/wqhouse3","north",0,0);
  add_exit(MINAS_DIR+"houses/wqhouse4","west",0,0);
*/

    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

public int 
sit_chair(string str)
{
    if (!strlen(str)) 
    { 
	NF("Sit where?\n"); 
	return 0; 
    }
    if (str != "chair" && str != "in chair" && str != "on chair") 
    {
	NF("Sit in a chair, maybe?\n");
	return 0;
    }
    if (TP->query_prop("_sitting"))
        NFN0("But you are already sitting in one of the chairs!");
    write("You sit down in one of the chairs by the table.\n");
    say(QCTNAME(TP)+" sits down in one of the chairs by the table.\n",TP);
    TP->add_prop("_sitting",1);
    TP->add_prop(LIVE_S_EXTRA_SHORT,", sitting in a chair");
    return 1;
}

public int 
stand_up(string str)
{
    if (str != "up") 
    {
	NF(CAP(query_verb())+" what? Up?\n");
	return 0;
    }
    if (!TP->query_prop("_sitting"))
        NFN0("But you are not sitting!");
    write("You rise up from the chair fearing it could break.\n");
    say(QCTNAME(TP)+" rises up from the chair.\n",TP);
    TP->remove_prop("_sitting");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

public void 
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
	return;
    if (living(ob) && ob->query_prop("_sitting"))
    {
	write("You rise up from the chair you are sitting in.\n");
	tell_room(TO, QCTNAME(TP) + " rises up from the chair.\n", TP);
	TP->remove_prop(LIVE_S_EXTRA_SHORT);
	TP->remove_prop("_sitting");
    }
}

public void 
reset_room()
{
    Gilraen = clone_npc(Gilraen, LEB_DIR + "wolfcave/gilraen");
    Gilraen->command("sit in chair");
}

public void 
init()
{
    ::init();
    add_action(sit_chair, "sit");
    add_action(stand_up,  "stand");
    add_action(stand_up,  "rise");
}

