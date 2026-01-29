inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in a room at the inn");
    set_long(BSN("You are in a room of the Dragon's claw Inn. "+
       "The maid has not been in here yet, as the "+
       "bed is not made and someone has spilled ale on the floor. "+
       "Someone must have left in a hurry, since the door was left "+
       "standing wide open. Besides the bed and the "+
       "standard oak chest there is not anything of note here."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"floor","spilled ale","spilt ale"}),BSN(
       "Upon closer inspection you notice that not only has the maid "+
       "not been here today, but yesterday either, as the ale "+
       "become dried and sticky to the point of catching a few flies. "+
       "Eeeewww... you got a little too close. What a stench!"));
    add_item(({"flies","dead flies"}), "That's disgusting!\n");
    add_item("bed", BSN("Unkempt, unmade, my my.. someone's mother would be upset."));
    add_exit(PELAR_DIR + "homes/inn/innhall2","north",0);
    
    clone_object(PELAR_DIR + "obj/innchest")->move(TO);
}
