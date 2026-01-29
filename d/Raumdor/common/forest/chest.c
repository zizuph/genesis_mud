inherit "/std/receptacle.c";
#include "/d/Raumdor/defs.h"
/* SARR */

int trap = 1;

void
create_receptacle()
{
    set_name(({"chest", "_raumdor_scripture_chest"}));
    set_adj("wooden");
    add_adj("black");
    set_cf(TO);
    set_short("black wooden chest");
    add_prop(CONT_I_MAX_WEIGHT,2000);
    add_prop(CONT_I_MAX_VOLUME,2000);
    add_prop(CONT_I_WEIGHT,500);
    add_prop(CONT_I_VOLUME,500);    
    add_prop(CONT_I_CLOSED,1);
    add_prop(OBJ_M_NO_GET, "It seems to be fixed to the ground.\n");
    set_long("This is a small wooden chest made of black oak. The "+
    "top of it is adorned with red runes. It has a large iron lock "+
    "set on it.\n");
}

void
init()
{
    ::init();
    add_action("do_search", "search");
    add_action("do_disarm", "disarm");
}

int
do_disarm(string str)
{
    NF("Disarm what?\n");
    if(str != "trap")
        return 0;
    if(TP->query_skill(SS_FR_TRAP) < 15)
    {
        write("You fail to disarm it and it blows in your face.\n");
        TP->heal_hp(-1000);
        if(TP->query_hp() <= 0)
            TP->do_die(TO);
        say(QCTNAME(TP)+" fidles around with the trap, and sets it "+
        "off... BANG!\n");
        write("You are burned badly.\n");
        trap = 0;   
        return 1;
     }
     else
     {
        write("You disarm it!\n");
        say(QCTNAME(TP)+" disarms the trap.\n");
        trap = 0;
        return 1;
    }
}


int
do_search(string str)
{
    if(str == "chest")
    {
        write("You search the chest.\n");
        set_alarm(3.0,0.0,"trap",TP);
        return 1;
    }
    return 0;
}

void
trap(object ob)
{
    if(ob->query_skill(SS_FR_TRAP) < 10)
    {
        write("You find nothing special on the chest.\n");
        say(QCTNAME(TP)+" finds nothing.\n");
    }
    else
    {
        write("You discover a cleverly hidden bomb trap!\n");
        say(QCTNAME(TP)+" discovers a trap!\n");
    }
}
 


varargs int 
open(object ob)
{
    if(trap)
    {
       write("You open the chest and a magical blast sprays you in "+
       "the face!\n");
       say(QCTNAME(TP)+" opens the chest and a magical blast sprays "+
       "him in the face!\n");
       TP->heal_hp(-1000);
       write("You are burned badly.\n");
       if(TP->query_hp() <= 0)
           TP->do_die(TO);
    }
    return 0;
}

