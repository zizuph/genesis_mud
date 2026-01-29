/*
* by Udana, /06
*  
* Modifications:
* October 2009 - Added no-sell property so that people can't use this to
*                gain lots of money. Fixed blind object to work correctly
*                as well. Also reduced the value. (Petros)
* December 2009 - fixed behavior so that "second stick" can be specified.
*                 also added error message so that when stick is broken
*                 already, the player will know.
*/

#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

#define BLIND_OBJECT OBJ + "blind_obj.c"


int broken = 0;
int glowing = 0;
/* handles added action */
int break_stick(string a);

/* when it goes off */
void stop_glowing();

public void create_object()
{
    set_name("stick");
    set_short("@@my_short");
    set_pshort("@@my_pshort");
    set_adj("odd");
    set_long("@@my_long");
    add_prop(OBJ_I_VALUE, 5000);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_M_NO_SELL, "No one would know what to do with this stick!\n");
}

string my_short()
{
    return glowing ? "stick of glowing material" : (broken ? "broken " : "") + "stick of odd material";
}

string my_pshort()
{
    return glowing ? "sticks of glowing material" : (broken ? "broken " : "") + "sticks of odd material";
}

string my_long()
{
    string long_desc;
    
    if(glowing)
    {
        long_desc = "A 20 inches long stick made of some weird substance. "
            + "The very material it is made of is glowing so "
            + "brightly that you can barely look directly at it. It is broken "
            + "in half, but both pieces are still partially glued together.\n";
    }
    else
    {
        long_desc = "A 20 inches long stick made of some weird substance. The "
            + "colour of it is hard to determine, as it changes with every "
            + "move. " + (broken ? "It is broken in half, but both pieces are "
            + "still glued together.\n" : "You have heard that miners in "
            + "northern Terel use sticks such as these as an emergency source "
            + "of light underground. You wonder how they activate them "
            + "though.\n");
    }
    
    return long_desc;
}

public void init()
{
    ::init();
    add_action("break_stick", "break");
}

int break_stick(string str)
{
    object *night_creatures;
    object stick;

    notify_fail("Break what?\n");
    if(!strlen(str))
    {
        return 0;
    }
    
    stick = PARSE_COMMAND_ONE(str, TP, "[the] %i");
    if (!objectp(stick) || stick != TO)
        return 0;

    if (broken)
    {
        write("It is already broken!\n");
        return 1;
    }
    
    tell_room(environment(TP), QCTNAME(TP) + " breaks a weird stick "
        + TP->query_pronoun() + " holds, and it suddenly bursts with extremely "
        + "bright light.\n", ({ TP }));
    write("As you break the stick, it bursts with a sudden glow, filling the "
        + "room with bright light.\n");

    add_prop(OBJ_I_LIGHT, 2);
    environment(TP)->update_light(1);
    
    /* Blind everybody in the room with ability to see in the dark.*/
    night_creatures = filter(all_inventory(E(TP)), &->query_prop(LIVE_I_SEE_DARK));
    setuid();
    seteuid(getuid());
    foreach (object creature : night_creatures)
    {
        object blind_object = clone_object(BLIND_OBJECT);
        blind_object->set_time(random(20) + 15);
        blind_object->move(creature);
    }
    
    glowing = set_alarm(100.0, 0.0, &stop_glowing());
    broken = 1;

    return 1;
}
 
void stop_glowing()
{
    tell_room(environment(TP), QCTPNAME(TP) + " stick suddenly dims.\n",
        ({ TP }) );
    write("The stick that you are holding dims, and stops glowing.\n");
    remove_prop(OBJ_I_LIGHT);
    environment(TP)->update_light(1);

    // Remove glowing alarm reference
    glowing = 0;
}
