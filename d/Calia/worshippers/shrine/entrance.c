
 /* Jaacar 15 MAY 95 

    Bug fixed Maniac 9/10/97 
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"

#define LIVE_O_LAST_WORSHIPPER_ROOM "_live_o_last_worshipper_room"

void
create_room()
{
    set_short("Shrine entrance");
    set_long("You have entered a holy shrine.  The walls are "+
        "made of slabs of white marble swirled with black "+
        "marble, each slab surrounded by a gold border.  It "+
        "is very quiet and peaceful here.  To the west you "+
        "see a large room and to the east you see an arch.  "+
        "You hear a very low volumed buzzing sound coming "+
        "from the arch.\n");

    add_item("arch","The arch is made of solid gold.  Running "+
        "down the inside of the arch is a shimmering glow of "+
        "some sort.  You cannot see through it, but it appears "+
        "that you could enter it.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(WOR_SHRINE+"common","west");
}


int
enter(string str)
{
    object tp, from; 

    if (str != "arch")
    {
        notify_fail("Enter what?\n");
        return 0;
    }
    tp = this_player(); 
    from = tp->query_prop(LIVE_O_LAST_WORSHIPPER_ROOM); 

    write("You close your eyes and concentrate.\n");
    say(QCTNAME(tp)+" closes "+tp->query_possessive()+
        " eyes in concentration, then disappears in a flash of light!\n");
    tp->move_living("M", from);
    tell_room(from, QCTNAME(tp)+" appears in a flash of light!\n", tp);
    tp->remove_prop(LIVE_O_LAST_WORSHIPPER_ROOM); 
    return 1;
}



/* Record the room they came from if it's not in the shrine */ 
void
enter_inv(object ob, object from)
{
    if (interactive(ob) && !wildmatch(WORSHIPDIR + "shrine*", file_name(from)))
        ob->add_prop(LIVE_O_LAST_WORSHIPPER_ROOM, from); 
    if (interactive(ob) && SECURITY->query_wiz_rank(TP->query_real_name()))
    {
        from = find_object("/d/Calia/worshippers/temple/estiroom.c");
        ob->add_prop(LIVE_O_LAST_WORSHIPPER_ROOM, from);
    }
    ::enter_inv(ob, from); 
}


void
init()
{
    ::init();
    add_action(enter, "enter");
}

