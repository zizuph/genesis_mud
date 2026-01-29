/* A cake of incense; burnt in a censor
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 5/16/98     Zima        Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
int      amt=15;
int      inc_type=SR_INC_BOUGHT;
 
int    query_amt()        { return amt; }
int    query_type()       { return inc_type; }
void   set_amt(int i)     { amt=i; }
void   set_type(int t)    { inc_type=t; }
 
void create_object() {
    set_name("incense");
    add_name(({"cake","cake of incense",SR_CAKE_INCENSE}));
    set_adj(({"fragrant","small"}));
    set_short("cake of incense");
    set_pshort("cakes of incense");
    set_long("It a small cake of hardened incense which produces "+
             "volumes of fragrant white smoke when burned in a "+
             "censor.\n");
    add_cmd_item(({"incense","cake","cake of incense"}),
       ({"burn","light","ignite"}),
       "The incense may only be burned after placing it in a censor.\n");
    add_cmd_item(({"incense","cake","cake of incense"}),
       "eat","The cake of incense is not to be eaten.\n");
    add_prop(OBJ_I_WEIGHT,90);
    add_prop(OBJ_I_VOLUME,55);
}
 
int crush(string cmd)
{
   object *inv=all_inventory(TP);
   notify_fail("Crush what? the cake of incense?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"[the] 'cake' / 'incense' [of] [incense]"))
      return 0;
   write("You crush the cake of incense with your hand.\n");
   tell_room(ENV(TP),QCTNAME(TP)+" crushes a cake of incense with "+
             HIS_HER(TP)+" hand.\n",TP);
   tell_room(ENV(TP),"The incense dust falls to the ground and disappears "+
             "in a fragrant cloud.\n");
   remove_object();
   return 1;
}
 
void init()
{
   ::init();
   add_action(&crush(),"crush");
}
 
// recover if not bought (ie handmade, usually for a quest)
string query_recover()
{
   if (inc_type==SR_INC_BOUGHT) return 0;
   return (MASTER + ":" + "#t=" + inc_type + "#a=" + amt +"#");
}
 
public void init_recover(string arg)
{
   string d1, d2;
   sscanf(arg, "%s#t=%d#%s",   d1, inc_type, d2);
   sscanf(arg, "%s#a=%d#%s",   d1, amt,      d2);
}
