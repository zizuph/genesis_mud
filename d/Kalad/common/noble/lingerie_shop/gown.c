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
    set_name("gown");
    set_adj("silky");
    add_adj("@@query_color@@");
    add_adj("night");
    set_short("silky @@query_color@@ night gown");
    set_long("This is a very beautiful silk night gown. It is "+
    "almost see-through, and it is made of @@query_color@@ colored silk.\n");
    set_ac(1);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,144);
}

mixed
wear()
{
   if (TP->query_gender() != 1)
        return "You would look foolish in it!\n";
   return 1;
}
