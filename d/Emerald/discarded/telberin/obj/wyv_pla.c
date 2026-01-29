inherit "/std/object";
 
#include "default.h"
#include "/d/Emerald/defs.h"
 
int     polished = 0;
 
int polish(string str);
 
void
create_object()
{
        set_long("@@plate_desc");
        set_name("plate");
        set_adj("wyvern");
        set_short("wyvern plate");
 
        add_prop(OBJ_I_VALUE, 131);
        add_prop(OBJ_I_WEIGHT, 102);
        add_prop(OBJ_I_VOLUME, 238);
}
 
string
plate_desc()
{
        string bright="";
 
        if(polished)
                bright = " It has been polished to a bright shine.";
        return "This is a wyvern's scale, black as ebon and obtained at " +
            "some cost to the fighter's life." + bright + "\n";
}
 
void
init()
{
    ::init();
    add_action(polish, "polish");
    add_action(polish, "shine");
}
 
int
polish(string str)
{
        NF("Polish what?\n");
        if(!strlen(str))
                return 0;
 
        NF("What do you wish to polish?\n");
        if(str != "plate")
                return 0;
 
        else
        {
        write("You polish the plate fastidiously.\n");
        polished = 1;
        tell_room(environment(TP), TP->query_The_name() +
                  " polishes the wyvern plate until it gleams.\n", TP);
        return 1;
        }
}
 
 
