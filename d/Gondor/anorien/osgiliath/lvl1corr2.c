inherit "/d/Gondor/common/room";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void    add_stuff();

void
create_room()
{
    set_short("in a dark corridor in the ruins of Central Osgiliath");
    set_long(BSN("You are in a rather dark and damp corridor with stone "
      + "walls. The corridor continues west and northeast, one direction "
      + "as dark as the other. The walls of the corridor are smooth, "
      + "never turning around corners, but rather bending slightly in "
      + "one direction as if forming a round circle. A large door leads "
      + "north here, without any signs as to what awaits behind."));
    add_prop(ROOM_M_NO_TELEPORT, check_teleport);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_item("walls",BSN("The walls are made of smooth white stone, "
      + "though the passage of hundreds of years since repair have left "
      + "solid tracks."));
    add_exit(OSG_DIR+"lvl1corr3","northeast",0,1);
    add_exit(OSG_DIR+"lvl1corr1","west",0,1);
    clone_object(OSG_DIR+"obj/lvl1_ghsdoor2")->move(TO);

    add_stuff();
}

void
add_stuff()
{
    object  tstand;

    tstand = clone_object(OBJ_DIR + "torchstand");
    tstand->set_torch_file(0);
    tstand->set_stand_desc("rusty torch stand");
    tstand->add_adj("rusty");
    tstand->set_long("The torch stand is made of metal rings that "
      + "can hold a torch.\n");
    tstand->move(TO);
}

void
init()
{
    ::init();
    add_action("do_knock", "knock");
}

int
do_knock(string str)
{
    switch(str)
    {
         case "door" :
         case "on door" :
         case "on the door" :
         case "on wooden door" :
         case "on the wooden door" :
         case "on wooden-door" :
         case "on the wooden-door" :
         {
            TP->catch_msg("You knock on the wooden door.\n");
            say(QCTNAME(TP) + " knocks on the wooden door.\n");
            break;
         }
         default :
             NFN0("Knock on what?");
    }
    return 1;
}

