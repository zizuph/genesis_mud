inherit "/d/Kalad/std/armour";
#include <composite.h>
#include "/d/Kalad/defs.h"
#define UNDERGARMENT_SUBLOC "_undergarment_subloc"

string color;
int worn;

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

void
create_armour()
{
    ::create_armour();
    set_name("belt");
    set_adj("@@query_color@@");
    add_adj("garter");
    add_adj("lacy");
    set_short("@@query_color@@ lacy garter belt");
    set_long("A lacy garter belt that looks very sexy.\n");

    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,15);
    add_prop(OBJ_I_VALUE,120);
}

int
wear(string str)
{
    object *temps;
    NF("Wear what?\n");
    temps = FIND_STR_IN_OBJECT(str,TP);
    if(!sizeof(temps))
        return 0;
    if(temps[0] != TO)
        return 0;
    if(worn == 1)
        return 0;
    write("You slip on the "+short()+" around your waist.\n");
    say(QCTNAME(TP)+" slips on the "+short()+" around "+
    HIS(TP)+" waist.\n");
    worn = 1;
    TP->add_subloc(UNDERGARMENT_SUBLOC,TO);
    move(TP,UNDERGARMENT_SUBLOC);
    return 1;
}

int
remove(string str)
{
    object *temps;
    NF("Remove what?\n");
    temps = FIND_STR_IN_OBJECT(str,TP);
    if(!sizeof(temps))
        return 0;
    if(temps[0] != TO)
        return 0;
    if(worn == 0)
        return 0;
    write("You slide the "+short()+" off.\n");
    say(QCTNAME(TP)+" slides the "+short()+" off.\n");
    worn = 0;
    move(TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(wear,"wear");
    add_action(remove,"remove");
}

int
can_see(object ob)
{
    object me = E(TO);
    if(ob->id("panties"))
    {
        if(me->query_armour(A_LEGS))
            return 0;
        return 1;
    }
    if(ob->id("stockings"))
    {
        if(me->query_armour(A_LEGS))
            return 0;
        return 1;
    }
    if(ob->id("belt"))
    {
        if(me->query_armour(A_LEGS))
            return 0;
        return 1;
    }
    if(ob->id("gloves"))
    {
        if(me->query_armour(A_HANDS))
            return 0;
        return 1;
    }
    if(ob->id("bra"))
    {
        if(me->query_armour(A_TORSO))
            return 0;
        return 1;
    }
    return 0;
}


string
show_subloc(string subloc, object on, object for_ob)
{
    int i;
    string ret;
    object *stuff,*keeps;
    if(query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if(subloc != UNDERGARMENT_SUBLOC)
        return "";
    keeps = ({});
    stuff = on->subinventory(UNDERGARMENT_SUBLOC);
    if(!sizeof(stuff))
        return "";
    if(for_ob == on)
        ret = "You are wearing ";
    else
        ret = C(HE(on))+" is wearing ";
    if(for_ob != on)
    {
        for(i=0;i<sizeof(stuff);i++)
        {
            if(can_see(stuff[i]))
                keeps += ({ stuff[i] });
        }
        if(!sizeof(keeps))
            return "";
        ret += COMPOSITE_DEAD(keeps);
    }
    else
    {
        if(!can_see(stuff[0]))
            ret += LANG_ADDART(stuff[0]->short()+"(hidden)");
        else
            ret += LANG_ADDART(stuff[0]->short());
        for(i=1;i<sizeof(stuff) - 1;i++)
        {
            if(!can_see(stuff[i]))
                ret += ", "+stuff[i]->short()+"(hidden)";
            else
                ret += ", "+stuff[i]->short();
        }
        if(sizeof(stuff) > 1)
        {
            if(can_see(stuff[i]))
                ret += " and "+LANG_ADDART(stuff[i]->short());
            else
                ret += " and "+LANG_ADDART(stuff[i]->short()+"(hidden)");
        }
    }
    return ret+".\n";
}
