
/* 

     ~Calia/gelan/cadet/cadet_shoes.c

     The guild object for the cadets, it adds their soul. 

     Coded by Maniac@Genesis, April 1997

     Copyright (C) Miguel Leith 1997

     Revised, 9/4/98, Maniac
 */ 

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

#include "cadet.h"

string born_to; 


void
create_armour()
{
   set_name("boots");       
   add_name("shoes"); 
   add_name(GC_SHOES_ID); 
   set_adj( ({ "steel-capped", "combat" }) ); 
   set_short("pair of combat boots"); 
   set_pshort("pairs of combat boots"); 
   set_long("A pair of combat boots, as worn by the " + 
            "Cadets of Gelan. " + VBFC_ME("cadet_help") + "\n");  

   set_at(A_FEET); 
   set_ac(12); 
   add_prop(OBJ_M_NO_DROP, 1); 
   add_prop(OBJ_I_VALUE, 0); 
   add_prop(OBJ_M_NO_BUY, 1); 
   add_prop(OBJ_M_NO_SELL, 1); 
   add_prop(OBJ_I_WEIGHT, 500); 
   add_prop(OBJ_I_VOLUME, 500); 
}


string
query_born_to()
{
    return born_to; 
}


void
set_born_to(string new_born_to)
{
    if (calling_object()->query_wiz_level()) 
        return;

    born_to = new_born_to; 
    set_short("pair of combat boots" + (stringp(born_to) ? 
              " with \"born to " + born_to + "\" written on them" : "")); 
    set_long("A pair of combat boots, as worn by the " + 
          "Cadets of Gelan. " +
          (stringp(born_to) ? 
           "Someone has written \"born to " + born_to + "\" on them. " : "") + 
           VBFC_ME("cadet_help") + "\n");  
}


string
cadet_help()
{
    if (IS_GELAN_CADET(this_player()))  
        return 
           ("There is a little inscription on the soles: \"help cadet.\"");  
    else
        return "";
}


string
query_auto_load()
{
    return MASTER + ":" + born_to;
}


void
init_arg(string arg)
{
    if (stringp(arg) && (arg != "0")) 
        set_born_to(arg); 
}

string
query_recover()
{
    return 0;
}

void
check_soul(object tp)
{
    tp->add_cmdsoul(GC_SOUL);  
    tp->update_hooks();  
}


/* Add the cadet soul here. */ 
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old); 

    if (IS_GELAN_CADET(dest)) 
        set_alarm(0.3, 0.0, &check_soul(dest)); 
}


void
remove_object()
{
    object e = environment();

    if (interactive(e)) { 
        e->remove_cmdsoul(GC_SOUL);  
        e->update_hooks();  
    } 
    ::remove_object(); 
}

