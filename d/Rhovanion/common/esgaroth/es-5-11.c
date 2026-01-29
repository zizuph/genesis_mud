inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"
#define O_DIR_O "/d/Rhovanion/common/esgaroth/objects/"
#define W_DIR_W "/d/Rhovanion/common/esgaroth/weapons/"
#define A_DIR_A "/d/Rhovanion/common/esgaroth/armours/"

add_torch()
{
    reset_euid();
    if (!present("_esg_torch", TO))
    {
        object torch;
        torch = clone_object("/std/torch");
         torch->add_name("_esg_torch");
        torch->set_adj("small");
        torch->move(TO);
    }
}

add_stuff()
{
    seteuid(getuid(TO));
    clone_object(O_DIR_O + "gem")->move(TO);
    clone_object(W_DIR_W + "sword")->move(TO);
    clone_object(W_DIR_W + "knife")->move(TO);
    clone_object(A_DIR_A + "boots")->move(TO);
    clone_object(A_DIR_A + "gloves")->move(TO);
    clone_object(A_DIR_A + "helmet")->move(TO);
    add_torch();
}

reset_room()
{
    add_torch();
}

create_room()
{
    set_short("store room");
    set_long("store room\n");
    add_stuff();
}
