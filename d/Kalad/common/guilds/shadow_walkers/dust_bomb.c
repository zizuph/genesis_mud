inherit "/std/object";
#include "/d/Kalad/defs.h"

string dmsg;

void
create_object()
{
    set_name("bomb");
    set_adj("dust");
    set_short("dust bomb");
    set_long("This is a small, white egg-shaped container. You see "+
    "a green button on the bottom to press to set off the contraption.\n");
    add_item("button","A large green button to press.\n");
}

void
init()
{
    ::init();
    AA(do_press,press);
}

int
do_press(string str)
{
    NF("Press what? The green button perhaps?\n");
    if(str != "green button")
        return 0;
    NF("You have to have it first.\n");
    if(!present(TO,TP))
        return 0;
    seteuid(getuid());
    write("You press the botton then hurl it to the ground.\n");
    say(QCTNAME(TP)+" hurls something to the ground.\n");
    tell_room(E(TP),"A large white dust cloud forms up, blocking "+
    "your vision!\n");
    clone_object("/d/Kalad/common/guilds/shadow_walkers/white_cloud")->move(E(TP));
    remove_object();
    return 1;
}

