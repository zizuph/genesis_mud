
 /* Digit 03 FEB 95 */

inherit "/std/room";
inherit "/d/Calia/walkers/specials/water_walk";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"
#include FIRE_HEADER


int
is_walker(object living)
{
    return living->query_skill(SS_WALKER_LEVEL);
}

void
create_room()
{
    set_short("On the bank of a boiling river");
    set_long("You are standing on the bank of a boiling river.  It "+
       "stretches out to the east from here.  West of you is a "+
       "large globe of light, hovering in the air.  It gives off "+
       "no heat that you can feel, and sounds like millions of tiny "+
        "bolts of lightning crashing into each other.  The walls "+
        "here have traces of salt formations, most likely from "+
        "the river to the east.\n");

    add_item(({"light","globe","globe of light"}),"The globe is "+
       "large enough for you to step into, if you dare.  The sounds "+
       "coming from the inside of it make you think twice.\n");

#include "banks.h"
    add_exit(CAVE+"room54","east","@@water_walk");

}

void
init()
{
    ::init();
    add_action("ent_light","enter");
    add_action("tch_light","touch");
    add_action("throw","throw");
}

int
ent_light(string str)
{
    NF("Enter what, globe?\n");

    if (!str || str !="globe")
       return 0;

    if (!is_walker(TP))
    {
        write("You jump into the globe!\nYou are hit full force "+
            "by the lightning, pushed back, and burned badly!\n");
        say(QCTNAME(TP)+" tries to jump into the globe but is "+
            "struck by the lightning and burned badly!\n");
        TP->heal_hp(-300);
        return 1;
    }
    write("You leap into the globe!\nYou are engulfed by "+
        "thousands of tiny lightning bolts, each travelling "+
        "harmlessly through your body.  Suddenly you find "+
        "yourself somewhere else.\n");
    TP->move_living("into the globe","/d/Calia/mountain/road/m28",1);
    tell_room(environment(TP),"The air begins to crackle around you.\nSuddenly a "+
        "large ball of electricity appears out of nowhere about a body length "+
        "above the ground!\n"+QCTNAME(TP)+" steps out of the ball and it "+
        "disappears as quickly as it appeared.\n",({TP}));
    return 1;
}

int
tch_light(string str)
{
    NF("Touch what, globe?\n");

       if(!str || str != "globe")
       return 0;

    write("You get burned by the light!\n");
    TP->heal_hp(-100);
    say(QCTNAME(TP)+" touches the globe and gets burned!\n");
    return 1;
}

int
throw(string str)
{
    object *arr;
    int i;

    if (!str)
    {
       NF("Throw what?\n");
       return 0;
    }

    arr = FIND_STR_IN_OBJECT(str,TP);

    if (!sizeof(arr))
    {
       NF("You don't have any '"+str+"'.\n");
       return 0;
    }

    setuid();
    seteuid(getuid());
    (CAVE+"digdead")->load_me();
    for (i=0; i < sizeof(arr); i++)

       arr[i]->move(CAVE+"digdead");

    write("You throw "+COMPOSITE_DEAD(arr)+" at the globe and it "+
       "disintegrates!\n");
    say(QCTNAME(TP)+" throws "+QCOMPDEAD+" at the globe and it "+
       "disintegrates!\n");
    return 1;
}
