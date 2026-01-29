//
// A Spool of Thread - spun with the spinning wheel
//
// Zima 5/22/98
//
inherit "/std/object";
#include <stdproperties.h>
 
string color;
 
public string query_color()   { return color; }
 
public void set_color(string c)
{
   if (stringp(color)) remove_adj(color);
   color=c;
   set_short("spool of "+color+" thread");
   set_pshort("spools of "+color+" thread");
   set_long("It is a spool of "+color+" thread, homespun of fine wool.\n");
   add_adj(color);
}
 
public void create_object()
{
    set_name("thread");
    add_name(({"spool","spool of thread"}));
    add_adj(({"wool","homespun"}));
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,6);
    set_color("white");
}
