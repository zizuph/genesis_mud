//
// Hand made candle - made with a candlewraught
// Zima - 5/23/98
//
inherit "/d/Khalakhor/std/obj/candle";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "defs.h"
#include "candle_herbs.h"
string   color, wcolor, herb;
 
string query_color()       { return color;  }
string query_wick_color()  { return wcolor; }
string query_herb()        { return herb;   }
 
void update_desc()
{
   string colored;
   set_short(color+" candle");
   set_long("It is a "+color+" candle hand-made of beeswax with a "+
            wcolor+" wick.\n");
   add_adj(color);
}
 
void   set_color(string c)      { remove_adj(color); color=c; update_desc();}
void   set_wick_color(string c) { wcolor=c; update_desc(); }
void   set_herb(string h)       { herb=h; }
void   set_herb_color(string h)
{
   int i, num=sizeof(KHERB);
   herb=h;
   for (i=0; i<num; i++)
      if (herb==KHERB[i])
         { color=KCOLOR[i]; i=num; }
   update_desc();
}
 
void create_candle()
{
    add_name(HM_CANDLE);
    set_adj(({"hand-made","beeswax"}));
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    wcolor="white";
    color="white";
    update_desc();
}

public string query_torch_recover()
{
   string rs=::query_torch_recover();
   return ("#c_c#"+color+"#c_w#"+wcolor+"#c_h#"+herb+rs);
}
 
public void init_torch_recover(string arg)
{
   string d1,d2;
 
   sscanf(arg, "%s#c_c#%s#%s", d1,color,d2);
   sscanf(arg, "%s#c_w#%s#%s", d1,wcolor,d2);
   sscanf(arg, "%s#c_h#%s#%s", d1,herb,d2);
   update_desc();
   ::init_torch_recover(arg);
}
