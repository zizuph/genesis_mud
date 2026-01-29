#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/object";

int on;

void
do_horror()
{
    string str;
    switch(random(8))
    {
        case 0:
            str = "wails in horrible despair!\n";
        break;
        case 1:
            str = "screams in agony!\n";
        break;
        case 2:
            str = "suddenly opens its eyes wide and moans!\n";
        break;
        case 3:
            str = "squirms around!\n";
        break;
        case 4:
            str = "moans: Please....help...me....\n";
        break;
        case 5:
            str = "moans: They came...and butchered us....\n";
        break;
        case 6:
            str = "wails: No...please...please spare me....NO!!!\n";
        break;
        case 7:
            str = "gurgles out blood from its mouth.\n";
        break;
    }
    if( living(E(TO) ) )
    {
        tell_object(E(TO),"The "+short()+" you have "+str);
        tell_room(E(E(TO)),"The "+short()+" held by "+QTNAME(E(TO))+
        " "+str,E(TO));
        set_alarm(40.0,0.0,&do_horror());
        return;
    }

    tell_room(E(TO),C(short())+" "+str);

    if(sizeof( FILTER_PLAYERS(all_inventory( E(TO) ))))
    {
        set_alarm(40.0,0.0,&do_horror());
        return;
    }
    on = 0;
}

void
create_object()
{
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    set_alarm(20.0,0.0,&do_horror());
    on = 1;
}

int
do_kill(string str)
{
    NF("Kill what?\n");
    if(str != "head")
        return 0;
    write("You smash the "+short()+" into a pile of mush, which "+
    "slowly dissolves away.\n");
    remove_object();
    return 1;
}

void
init()
{
    ::init();
    if(on == 0)
    {
        set_alarm(40.0,0.0,&do_horror());
    }
    add_action(do_kill,"kill");
}

