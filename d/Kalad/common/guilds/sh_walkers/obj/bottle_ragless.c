inherit "/std/object";
#include "/d/Kalad/defs.h"

/* Sarr */

int lit;
int f_str;

void
set_fire_str(int i)
{
    f_str = i;
}


void
create_object()
{
    set_name("bottle");
    set_adj("glass");
    set_short("glass bottle");
    set_long("This is a bottle filled with explosive liquid. All "+
    "you need is a rag to stuff it on top.\n");
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_WEIGHT,1000);
}

string
my_drop()
{
    set_alarm(1.0,0.0,"break_bottle");
    return 0;
}

void
break_bottle()
{
    object fire;
    if(lit)
    {
        tell_room(E(TO),"The bottle explodes as it hits the ground!\n");
        tell_room(E(TO),"B A N G ! ! ! \n");
        seteuid(getuid());
        fire = clone_object("/d/Kalad/common/guilds/shadow_walkers/fire.c");
        fire->set_fire_str(f_str);
        fire->move(E(TO));
        tell_room(E(fire),"A "+fire->short()+" starts.\n");
        remove_object();
    }
    else
    {
    tell_room(E(TO),"The bottle breaks on the ground, spilling the "+
    "liquid everywhere!\n");
    remove_object();
    }
}

void
init()
{
    ::init();
    AA(do_stuff,stuff);
}

int
do_stuff(string str)
{
    object bottle, rag,bot;
    NF("Stuff what in what?\n");
    if(!parse_command("stuff "+str,TP,"'stuff' %o 'in' %o",rag,bottle))
        return 0;
    NF("You don't have a rag.\n");
    if(!rag)
        return 0;
    NF("Stuff the rag in what bottle?\n");
    if(!bottle)
        return 0;
    if(bottle != TO)
        return 0;
    write("You stuff the rag in the bottle. Now it is complete, ready "+
    "to ignite.\n");
    say(QCTNAME(TP)+" stuffs a rag in a bottle.\n");
    TP->command("cackle");
    seteuid(getuid());
    bot = clone_object("/d/Kalad/common/guilds/shadow_walkers/fire_bomb");
    bot->set_fire_str(f_str);
    bot->move(TP);
    rag->remove_object();
    remove_object();
    return 1;
}

