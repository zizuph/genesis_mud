/* This object is an autoloading object which gives non-knights
 * a knightish award. When there is no more award for the owner
 * of this object, it'll remove itself.
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>

int alrm = 0;

void
create_object()
{
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_name(NON_KN_AWD_ID);
    set_no_show();
}

void
enter_env(object dest, object old)
{
    if (interactive(dest))
      dest->add_subloc("award_subloc",this_object());
    ::enter_env(dest, old);
}

void
leave_env(object from, object to)
{
   if (interactive(from))
      from->remove_subloc("award_subloc");
    ::leave_env(from, to); 
}

string
show_subloc(string subloc, object me, object for_obj)
{
    string str,awards,dummy;
    if (subloc != "award_subloc")
      return me->show_subloc(subloc, me, for_obj);
    
    if (me->query_prop("_temp_subloc_show_only_things"))
      return "";
    
    if (for_obj == me)
      str = "You bear ";
    else
      str = C(PRONOUN(me)) + " bears ";
    
    awards = (ADMIN)->query_award_nice(me);
    if (!awards || awards == "")
      {
	  alrm = set_alarm(1000.0,0.0,"check_again",me);
	  return "";
      }
    else if (alrm)
      {
	  remove_alarm(alrm);
	  alrm = 0;
      }
    return (str + awards + ", honor symbol" +
	    (sscanf(awards,"%sand the%s",dummy,dummy) == 2 ? "s" : "") +
	    " of the Knights of Solamnia.\n");
}

/* Don't remove this object immediately, maybe the admin room is briefly
 * out of order, or whatever. if the award is gone at least 15minutes
 * straight, remove this object, too.
 */
void
check_again(object who)
{
    string awards = (ADMIN)->query_award_nice(who);
    if (!awards || awards == "")
      remove_object();
}

string
query_auto_load()
{
    return MASTER_OB(this_object()) + ":";
}

void
init_arg(string str) { }
