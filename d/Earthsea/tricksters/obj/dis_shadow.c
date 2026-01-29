inherit "/std/shadow";

#define SW shadow_who

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

object *intro;

void add_intro(object *list)
{
 int i;

 for(i=0;i<sizeof(list);i++)
   if(member_array(list[i],intro)==-1) intro+=({list[i]});
}

void clear_intro()
{
 intro=({});
}

object *query_intro()
{
 return intro;
}

int query_introed(object player)
{
 return (member_array(player,intro)==-1 ? 0 : 1);
}

int can_see_disguise(object obj)
{
 int chance,level;

 if(obj==SW) return 1;
 if(query_introed(obj)) return 1;

 chance=obj->query_stat(SS_WIS)/18+
        obj->query_skill(SS_AWARENESS)/8+
        SW->query_prop_setting("_trick_i_disguise_random");
 level=SW->query_trickster_level();

 if(chance>=level) return 1;
 return 0;
}

string disguise_long()
{
 return SW->query_prop_setting("_trick_i_disguise_adj1")+" "+
        SW->query_prop_setting("_trick_i_disguise_adj2")+" "+
        SW->query_gender_string()+" "+SW->query_race_name();
}

public string query_nonmet_name()
{
 return disguise_long();
}

public string query_met_name()
{
 return "the "+disguise_long();
}

public varargs string
query_the_name(object pobj)
{
    string pre = "", aft = "";

    if (!objectp(pobj))
        pobj = previous_object(-1);

    if (!CAN_SEE(pobj, this_object()) || !CAN_SEE_IN_ROOM(pobj))
        return "someone";
    if (SW->query_prop(OBJ_I_HIDE))
    {
        pre = "[";
        aft = "]";
    }
    if (SW->query_prop(OBJ_I_INVIS))
    {
        pre = "(";
        aft = ")";
    }

    if (SW->notmet_me(pobj))
        return pre + "the " + query_nonmet_name() + aft;
    else
        return pre + query_met_name() + aft;
}

public varargs string
query_The_name(object pobj)
{
    return capitalize(query_the_name(pobj));
}

void remove_dis_shadow()
{
 SW->remove_subloc("disguise_subloc");
 remove_shadow();
}

public string show_subloc(string subloc, object on, object for_obj)
{
 if(subloc!="disguise_subloc") return 0;

 if(on==for_obj)
   return "You have disguised yourself as a "+disguise_long()+".\n";

 if(query_introed(for_obj))
  return C(PRO(SW))+" has disguised "+OBJ(SW)+"self as a "+
    disguise_long()+".\n";
}

int never_test()
{
 if(query_introed(TP)) return 0;

 return 1;
}

