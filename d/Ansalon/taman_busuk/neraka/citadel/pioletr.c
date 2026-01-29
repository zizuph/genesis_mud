#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#define CITDIR(x) "/d/Ansalon/taman_busuk/neraka/citadel/x"
#define CITADEL_IS_MOVING "citadel_is_moving_"
#define CITADEL_IS_MOVING_HIGH "citadel_is_moving_high_"

inherit "/d/Ansalon/taman_busuk/neraka/citadel/citadel_base.c";

/* The Piolet Room */
/* Sarr */

object cit_obj;

void
create_room()
{
    object *cit_list;
    int i;
    ::create_room();
    add_prop(ROOM_I_INSIDE,1);
    if(sizeof(cit_list = object_clones(find_object(CITDIR(citadel_object)))))
    {
        for(i=0;i<sizeof(cit_list);i++)
            if(cit_list[i]->query_linked() == 0)
            {
                cit_list[i]->link_citadel(TO);
                cit_obj = cit_list[i];
            }
    }
    else
    {
        tell_room(TO,"You must load and clone a citadel_object first.\n");
        remove_object();
        return;
    }
    if(!cit_obj)
    {
        tell_room(TO,"Error: There is already a citadel around.\n");
        remove_object();
        return;
    }
    set_current_room(E(cit_obj));
    set_citadel_direction("north");
    set_citadel_altitude(1);
    set_short("In the Piolet room of the Floating Citadel");
    set_long("You are in a strange, and magical room. The stone walls around "+
    "you seem to glow with magic. In the center of the room, you see a floating "+
    "chair suspended in mid-air over a circle of runes. Light beams down from "+
    "another circle of runes above the chair. There are two discs attached to "+
    "small support pillars in front of the chair. The rest of the room is "+
    "devoid of anything intresting.\n");
    add_item("chair","In front of the chair, you see blue sphere.\n");
    add_item(({"blue sphere","sphere"}),"@@blue_sphere@@");
    add_exit(CITDIR(cit1),"down",0,0);
}

string
blue_sphere()
{
    return query_current_room()->long()+
    C(COMPOSITE_DEAD(FILTER_DEAD(all_inventory(query_current_room()))))+".\n"+
    C(COMPOSITE_LIVE(FILTER_LIVE(all_inventory(query_current_room()))))+".\n";
}

void
init()
{
    ::init();
    add_action("do_set_direction","direction");
    add_action("do_set_altitude","altitude");
    add_action("do_stop","stop");
    add_action("do_thrust","thrust");
}

int
do_thrust()
{
    if(query_prop(CITADEL_IS_MOVING))
    {
        write("You are already moving!\n");
        return 1;
    }
    write("You push the discs forward, and thrust into your current "+
    "direction!\n");
    write("The citadel rumbles and shakes.\n");
    tell_room(E(cit_obj),"The citadel rumbles and shakes as it begins to "+
    "move towards the "+query_current_dir()+".\n");
    add_prop(CITADEL_IS_MOVING,1);
    set_alarm(8.0,0.0,"move_the_citadel");
    return 1;
}

void
move_the_citadel()
{
    mixed *mroom_exit;
    string mdest;
    int i,mindex,prevent;
    mroom_exit = E(cit_obj)->query_exit();
    if(query_prop(CITADEL_IS_MOVING) == 0)
    {
        return;
    }
    for(i=0;i<sizeof(mroom_exit);i++)
    {
        if(mroom_exit[i] == query_current_dir())
        {
            mdest = mroom_exit[i-1];
            prevent = mroom_exit[i+1];
        }
    }
    if(!mdest)
    {
        write("The citadel suddenly rams into a dead end, and the walls "+
        "shake violently.\n");
        tell_room(E(cit_obj),"The citadel suddenly stops and shakes "+
        "violently.\n");
        stop_citadel();
        return;
    }
    if(prevent == 1)
    {
        write("You are not able to go in the direction for some reason.\n");
        stop_citadel();
        return;
    }
    write("The citadel shakes and rumbles as it moves on.\n");
    tell_room(E(cit_obj),"The "+cit_obj->short()+" floats "+
    query_current_dir()+".\n");
    if(cit_obj->move(mdest) != 0)
    {
        write("For some reason, you are not able to go that way.\n");
        stop_citadel();
        tell_room(E(cit_obj),"It fails, however.\n");
        return;
    }
    tell_room(E(cit_obj),"A "+cit_obj->short()+" floats in.\n");
    set_current_room(E(cit_obj));
    set_alarm(8.0,0.0,"move_the_citadel");
}



int
do_stop()
{
    int i;
    i = stop_citadel();
    if(i == 0)
    {
        write("The citadel is unable to stop at the moment. You must wait "+
        "until it has reached its proper destination.\n");
        return 1;
    }
    if(i == 1)
    {
        write("The citadel rumbles to a halt.\n");
        tell_room(E(cit_obj),"The citadel suddenly stops moving.\n");
        return 1;
    }
    if(i == 2)
    {
        write("The citadel is already stopped.\n");
        return 1;
    }
}


int
do_set_altitude(string s)
{
    int i,o,form_set;
    form_set = query_citadel_altitude();
    sscanf(s,"%d",i);
    if(!i)
    {
        write("Invalid altitude.\n");
        return 1;
    }
    if(form_set == i)
    {
        write("You already are at that altitude level!\n");
        return 1;
    }
    o = set_citadel_altitude(i);
    if(o != 1)
    {
        write("The proper altitude levels are 1-3.\n");
        return 1;
    }
    if(form_set < i)
    {
    write("The citadel shakes and rumbles.\n");
    tell_room(E(cit_obj),"The citadel begins to rise higher in the air.\n");
    }
    else
    {
    write("The citadel shakes and rumbles.\n");
    tell_room(E(cit_obj),"The citadel begins to descend lower to the ground.\n");
    }
    write("New altitude level: "+i+".\n");
    return 1;
}

        
int
do_set_direction(string s)
{
    int i;
    i = set_citadel_direction(s);
    if(i == 0)
    {
        write("You cannot set that setting in.\n");
        return 1;
    }
    if(i == 1)
    {
        write("The direction is now set to "+s+"!\n");
        if(query_prop(CITADEL_IS_MOVING))
        {
            write("The citadel shakes and rumbles as it veers into its "+
            "new course.\n");
        }
        return 1;
    }
}


