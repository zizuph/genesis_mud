#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;


void
create_icewall_room()
{

    set_short("A small clearing in the icy forest");
    set_long("@@long_descr");


    add_exit("east_path3","northwest");
    add_exit("ice_clearing2","southeast","@@southeast",1,1);

    add_item("forest","All around you, the trees stand frozen in " +
     "time. Thick ice chains the bushes, making any further progress " +
     "progress impossible. Better turn back.\n");
    add_item("bushes","The bushes, frozen into a wall of sharp slivers, " +
     "make a journey through this old section of the forest impossible. " +
     "The icy thorn bush to the southeast looks especially deadly.\n");
    add_item(({"icy thorn bush","thorn bush"}),"Hmm... with the ice " +
     "blurring the edges between air and snow, you failed to notice " +
     "that it would be possible to slip southeast around the thorn bush.\n");

    set_tell_time(900);

    add_tell("It is snowing hard... And white flakes begin to " +
     "cover you from head to toe.\n");
    add_tell("You think you have just heard a strange shriek " +
     "carried here by the everpresent freezing wind.\n");
    add_tell("Snow whirls about you, creating myriad of patterns... " +
     "There is a strange beauty in them...\n\n\n" +
     "You shiver and slap your face. It must be the cold.\n");
    add_tell("There is something about this place...\n\n\n" +
     "Something...\n\n\n" +
     "Your sixth sense is pounding hard at the back of your skull.\n");
    add_tell("The dark, icy forest looms above you.\n");

    reset_room();
}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string

long_descr()

{ return ("" +
     "You stand in a small, isolated clearing at the northern edge " +
     "of the ice forest. Frozen trees surround you, as do the " +
     "ice-covered bushes. It appears " +
     "impossible to walk further into the dark and oppresive forest.\n");
}

int
southeast()
{ 
  write("There is something dire hanging in the air... Waiting... " +
    "You feel a strange chill as you walk southeast.\n");
  say(QCTNAME(TP) + " looks uneasy as he walks deeper into the forest.\n");
  return 0;
}
      