//
// A candle wick - cut from a spool of wick cord; used to make a candle
//                 with a candlewraught
// Zima 5/23/98
//
inherit "/std/object";
#include <stdproperties.h>
 
string color;
 
public string query_color()   { return color; }
 
public void set_color(string c)
{
   if (stringp(color)) remove_adj(color);
   color=c;
   set_short(color+" candle wick");
   set_long("It is a "+color+" candle wick made of wool.\n");
   add_adj(color);
}
 
public void create_object()
{
    set_name("wick");
    add_name("_candle_wick");
    add_adj(({"wool","candle"}));
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_VALUE,0);
    set_color("white");
}
