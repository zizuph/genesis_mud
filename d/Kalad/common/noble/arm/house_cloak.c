inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR 
 *
 * 2020-12-22 - Cotillion
 * - Fixed armour recovery
 */

string house;
string color;
void set_house_name(string str);
void set_color_name(string str);
string query_house_name();
string query_color_name();

string
query_arm_recover()
{
    return ::query_arm_recover() + "|"+house+"|"+color+"|:";
}

void
init_arm_recover(string arg)
{
    ::init_arm_recover(arg);

    string ho,co,fo;
    sscanf(arg,"%s|%s|%s|%s",fo,ho,co,fo);
    if(ho)
        set_house_name(ho);
    if(co)
        set_color_name(co);
}


void
create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("@@query_color_name@@");
    set_short("@@query_color_name@@ cloak of the house of @@query_house_name@@");
    set_long("This @@query_color_name@@ cloak is made of very soft, "+
    "fine woven cotton. A large emblem, along with the colors of this cloak, "+
    "mark it as property of the house of @@query_house_name@@.\n");
    set_ac(3);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,380);
}

void
set_house_name(string str)
{
    house = str;
}
void
set_color_name(string str)
{
    color = str;
}

string
query_house_name()
{
    return house;
}

string
query_color_name()
{
    return color;
}

