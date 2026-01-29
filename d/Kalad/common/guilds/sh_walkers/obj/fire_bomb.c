inherit "/std/object";
#include "/d/Kalad/defs.h"

#define KALAD_BOMB_DELAY "_kalad_bomb_delay"
#define LIVE_I_NON_CORPOREAL "_live_i_non_corporeal"
/* Sarr */

int lit;
int f_str;

string
query_auto_load()
{
    return MASTER+":|"+f_str;
}

void
init_arg(string arg)
{
    string foobar;
    sscanf(arg,"%s|%d",foobar,f_str);
}

void
set_fire_str(int i)
{
    f_str = i;
}

int
query_fire_str()
{
    return f_str;
}

void
create_object()
{
    set_name("cocktail");
    set_adj("molotov");
    set_short("molotov cocktail");
    set_long("This is a bottle filled with explosive liquid. You "+
    "see a cloth rag sticking out of the top.\n");
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_M_NO_DROP,"@@my_drop@@");
}

int
my_drop()
{
    if(lit)
    { 
        write("You can't drop it, you must throw it!\n");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    AA(do_throw,throw);
    AA(do_ignite,ignite);
}

int
do_ignite(string str)
{
    object bot;
    NF("Ignite what?\n");
    if(!parse_command("ignite "+str,TP,"'ignite' %o",bot))
        return 0;
    if(!bot)
        return 0;
    if(bot != TO)
        return 0;
    NF("The "+short()+" is already lit.\n");
    if(lit)
        return 0;
    lit = 1;
    write("You ignite the wick on the bottle, and it starts to burn. "+
    "You have only a few moments to throw it before it explodes in "+
    "your face.\n");
    say(QCTNAME(TP)+" ignites the wick on the "+short()+".\n");
    set_alarm(10.0,0.0,"explode",TP,f_str);
    return 1;
}


int
do_throw(string str)
{
    string dir,*dirs,*rooms,room;
    object bot,fire,target,oroom;
    NF("What?\n");
    NF("Throw what?\n");
    if(!parse_command("throw "+str,TP,"'throw' %o ",bot))
          return 0;
    if(!bot)
        return 0;
    if(bot != TO)
        return 0;
    NF("The "+short()+" is not lit.\n");
    if(lit == 0)
        return 0;
    NF("You are not ready to throw another one yet.\n");
    if(TP->query_prop(KALAD_BOMB_DELAY))
        return 0;    
    write("You hurl the "+short()+" to the ground!\n");
    say(QCTNAME(TP)+" hurls the "+short()+" to the ground!\n");
    TP->bomb_attack_delay(TP);
    seteuid(getuid());
    fire = clone_object("/d/Kalad/common/guilds/sh_walkers/obj/fire");
    fire->set_fire_str(query_fire_str());
    fire->move(E(TP));
    tell_room(E(TP),"A "+fire->short()+" starts!\n");
    remove_object();
    return 1;
    
}
