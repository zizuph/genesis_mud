

inherit "/std/receptacle";
#include <macros.h>
#include "defs.h"
#include <stdproperties.h>
#define NUM_CLOAKS   20
 
void
load_cabinet_item(string PathName, int Num)
{
   int i;
    object *CObj;
    Num -= sizeof(filter(all_inventory(this_object()), &->id("_wor_cloak_")));
    if (Num <= 0)
        return;

    CObj = allocate(Num);
   for (i=0; i<Num; i++) {
      CObj[i]=clone_object(PathName);
      CObj[i]->move(this_object());
   }
}
 
void load_cabinet(object TObj) {
   TObj->add_prop(CONT_I_CLOSED,0); /* open cabinet to load */
   seteuid(getuid());
    load_cabinet_item((WOR_OBJECTS+"cloak"), NUM_CLOAKS);
   TObj->add_prop(CONT_I_CLOSED,1); /* close after loaded */
}
 
void create_receptacle()
{
    set_name("cabinet");
    set_adj("black");
    add_adj("marble");
    set_long("It is a tall black marble cabinet with golden hinges "+
        "handles.  It appears to be used to store cloaks inside "+
        "for the members of the circle to wear.\n");
 
    add_prop(CONT_I_WEIGHT,      50000);
    add_prop(CONT_I_MAX_WEIGHT, 300000);
    add_prop(CONT_I_VOLUME,      40000);
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 0); /* leave open so can load items */
    add_prop(OBJ_I_NO_GET,1);
    set_alarmv(1.0,0.0,"load_cabinet",({(this_object())}));
    enable_reset(100);
}
 
public void
reset_receptacle()
{
    load_cabinet(this_object());
}

public void
reject(object ob)
{
    tell_room(environment(), "The cabinet rejects " +
        (function_exists("create_object", ob) == "/std/heap" ?
        ob->short() : LANG_ADDART(ob->short())) + ".\n");
}

public void
enter_inv(object ob,object from)
{
    ::enter_inv(ob,from);
    if (!ob->id("_wor_cloak_"))
    {
        set_alarm(0.5,0.0,&reject(ob));
        if (!objectp(from))
            ob->move(environment(),1);
        else
            ob->move(from,1);
    }
}
