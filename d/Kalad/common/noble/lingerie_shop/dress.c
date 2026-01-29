inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

string color;

void
set_color(string str)
{
    color = str;
    set_adj(str);
}

string
query_color()
{
    return color;
}

string
query_arm_recover()
{
    return "|"+color+"|:";
}

void
init_arm_recover(string arg)
{
    string co,fo;
    sscanf(arg,"%s|%s|%s",fo,co,fo);
    if(co)
        set_color(co);
}


void
create_armour()
{
    ::create_armour();
    set_name("dress");
    set_adj("@@query_color@@");
    add_adj("satin");
    set_short("@@query_color@@ satin dress");
    set_long("This dress is made of smooth satin, and it goes "+
    "down all the way to your knees. The front is open wide, "+
    "revealing a teasing amount of your bosom.\n");
    set_ac(1);
    set_at(A_TORSO);
    set_af(TO);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,144);
}

mixed
wear()
{
   if (TP->query_gender() != 1)
        return "You would look foolish in it!\n";
    write("You slip into the "+short()+" with a smile.\n");
    say(QCTNAME(TP)+" slips into the "+short()+" with a smile.\n");
    return 1;
}

int
remove()
{
    write("You slip out of the "+short()+" with a smile.\n");
    say(QCTNAME(TP)+" slips out of the "+short()+" with a smile.\n");
    return 1;
}


