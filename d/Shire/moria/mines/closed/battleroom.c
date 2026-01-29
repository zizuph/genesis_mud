#include "defs.h"
#include <macros.h>

inherit "/std/room";

create_room()
{
    set_short("Battleroom.\n");
    set_long("In the midst of Moria, deep under the Mountain, " +
	     "you have entered a room without exits. You wonder " +
	     "why this is, until you see all the leftovers of " +
	     "poor balrogs and orcs lying around. Obviously " +
	     "someone wanted to magically transport them " +
            "here, just for the sake of perversely destroying " +
	     "them. Let's hope you are not a mortal. *grin*\n");
    add_prop(ROOM_M_NO_TELEPORT, "You can't!\n");
}

init()
{
    ::init();
    add_action("npc","npc");
}

#define NPC ([ \
	      "balrog": MORIA_NPC + "balrog", \
	      "orc"   : MORIA_NPC + "orc",    \
	      "bolg"  : MORIA_NPC + "urukcap", \
	      "uruk"  : MORIA_NPC + "uruk", \
	      "hawk"  : MORIA_NPC + "echohawk", \
])

int
npc(string str)
{
    string fname;
    object npc;

    if (!TP->query_wiz_level())
	return 0;
    if (!strlen(str))
	return notify_fail("Which npc?\n");
    
    fname = NPC[str];
    if (!fname)
	return notify_fail("Eh, one of: balrog, orc, bolg, uruk, hawk.\n");

    FIXEUID;
    npc = clone_object(fname);
    npc -> move(TO);
    
    if (str=="orc")
	npc->create_troll_soldier(random(24));

    write("Ok, " + npc->short() + " is ready for battle!\n");
    say(QCTNAME(TP) + " utters some strange words of arcane power, " +
	"and suddenly a " + QNAME(npc) + " stands in front of you!\n", TP);
    return 1;
}

leave_inv(object obj, object to)
{
    if (!obj->query_npc() || !objectp(to))
    {
	::leave_inv(obj, to);
	return;
    }
    
    tell_room(TO, QCTNAME(obj) + " tried to transport out of here.\n");
    obj->remove_object();
}









