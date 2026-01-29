/* an invisibility object for an herb, coded by Elizabeth Cook/Mouse */
/* October 1996 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "../mouse.h"


void create_object() 
{
     set_name("invis_object");
     set_short("invis_object");
     add_prop(OBJ_M_NO_DROP,1);
     add_prop(OBJ_M_NO_GIVE,1);
     set_no_show();
}

void restore(object victim)
{
     victim->remove_prop(OBJ_I_INVIS);
         victim->catch_msg("You feel your body grow heavier as you "+
           "reappear.\n");
     tell_room(environment(this_player()),QCTNAME(victim)+" reappears "+
           "before your very eyes.\n",victim);   
     remove_object();
}


void init()
{
     set_alarm(60.0,0.0,&restore(this_player()));
     tell_room(environment(this_player()),QCTNAME(TP)+" fades from view.\n",
           TP);
     TP->add_prop(OBJ_I_INVIS,1);
      TP->catch_msg("You feel your body grow lighter as you "+
           "disappear from view.\n");
}


