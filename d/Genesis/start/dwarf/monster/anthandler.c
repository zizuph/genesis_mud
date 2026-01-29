/*
 * Changes
 * 10/08/21 Lavellan Now a container rather than a room (!) so doing emotes
 *              on it won't bug. Added "kick" to the destruction methods.
 *              Destroying the hill "normally" doesn't destroy ants too.   
 */
#include "../defs.h"

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

#define MAXNRANTS 15

void new_ant();

object *ants = ({ });
int smashed;

string
mylong()
{
    return "An ant hill, populated by black ants.\n";
}

void
create_container()
{
    if (!IS_CLONE)
        return;

    set_name("hill");
    set_adj("ant");
    set_short("ant hill");
    set_long(VBFC("mylong"));

    add_prop(OBJ_I_NO_GET,
        "You cannot take the ant hill. The ants do not allow it.\n");

    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(CONT_I_REDUCE_WEIGHT,10);
    add_prop(CONT_I_REDUCE_VOLUME,10);
    add_prop(CONT_I_TRANSP,0);
    add_prop(CONT_I_MAX_WEIGHT,1000000);
    add_prop(CONT_I_MAX_VOLUME,1000000);

    add_prop(CONT_I_CLOSED,1);

    set_alarm(10.0, 0.0, new_ant);
}

void
remove_object()
{
    if (!smashed)
        catch(ants->remove_object());
    ::remove_object();
}

void
new_ant()
{
    object ob;

    setuid();
    seteuid(getuid(TO));

    ants -= ({ 0 });
    
    if (sizeof(ants) < MAXNRANTS)
    {
        ob = clone_object(D_MON+"ant");
        ob->move(E(TO));
        
        tell_room(E(TO), "A small ant crawls out of the hill.\n");
        ants += ({ ob });
    }

    set_alarm(itof(120 + random(520)), 0.0, new_ant);
}

void
init()
{
    ::init();

//    add_action("get","get");
//    add_action("get","take");
    add_action("jump","jump");
    add_action("jump","stomp");
    add_action("jump","destroy");
    add_action("jump","ruin");
    add_action("jump","kick");
}

int
jump(string s)
{
    int i;
    object *obs;

    if (s!="on the ant hill" && s != "the hill" && s!="hill" &&
        s!="the ant hill"&&s!="on the hill"&&s!="on hill")
        return 0;
    
    obs = all_inventory();

    say(QCTNAME(TP)+" destroys the ant hill.\n");
    TP->catch_msg("You destroy the ant hill.\n");

    if(sizeof(obs))
    {
        for(i=0;i<sizeof(obs);i++)
            obs[i]->move(E(TO),1);
      
        tell_room(E(TO),"As the ant hill is destroyed, some objects appear from it.\n");
    }
    smashed = 1;
    remove_object();
    return 1;
}

/*void
bortget()
{
    remove_prop(CONT_I_CLOSED);
}

int
get()
{
    add_prop(CONT_I_CLOSED,1);
    set_alarm(1.0, 0.0, bortget);

    return 0;
}*/