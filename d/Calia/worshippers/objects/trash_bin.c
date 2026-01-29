/*   trash_bin.c
 *
 *  A trash bin, where you can throw
 *  usless stuff in. Only items that
 *  can be removed properly and are
 *  not livings will be destructed.
 *
 * Baldacin@Genesis, May 2004
 */

inherit "/std/container";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
                        ///////////////////////////////////////
int iRecycle_alarm,     // The alarm that triggers the recycle.
    iAlarm_flag;        // A flag thats true when recycle alarm
                        // is active.
 
void 
create_container()
{    
    set_name("bin");
    add_name("worshippers_bin_");
    set_adj("trash");
    set_long("It is a fair sized trash bin, you could probably "+
      "throw down just about anything that you wanted to rid of.\n");
 
    add_prop(CONT_I_WEIGHT,     2000);
    add_prop(CONT_I_MAX_WEIGHT, 7000);
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_MAX_VOLUME, 7000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "That is not possible.\n");
    set_no_show_composite(1);
}

void
do_recycle()
{
    mixed *inv = all_inventory(this_object()),
          *fails = ({}), *fails_str = ({});
    int i;
    
    for (i=0;i < sizeof(inv);i++)
    {
        if (!inv[i]->remove_object())
            fails += ({ inv[i] });
    }
    
    if (sizeof(fails))
    {
    	for (i=0;i < sizeof(fails);i++)
    	{
    	    fails[i]->move(environment(this_object()), 1);
    	    fails_str += ({ fails[i]->short() });
    	}
    	if (environment(this_object()))
        tell_room(environment(this_object()), "A loud coughing "+
          "sound is heard from the trash bin and the "+
          COMPOSITE_WORDS(fails_str)+" are thrown out of the "+
          "bin again.\n\n");
    }
    
    
    if (environment(this_object()))
    tell_room(environment(this_object()), "A bright flash of white "+
      "light emerges from the trash bin, forcing you to squint your "+
      "eyes briefly. When you open your eyes again and glance down "+
      "the trash bin you notice that it is empty again.\n");
    
    iAlarm_flag = 0;
}

int
prevent_enter(object ob)
{
    if (living(ob))
    {
        write("The "+ob->short()+" can not be put there.\n");
        return 1;
    }
    
    return 0;
}

void
enter_inv(object ob, object from)
{
    if (iAlarm_flag)
        return;
        
    iRecycle_alarm = set_alarm(4.0, 0.0, &do_recycle());
    iAlarm_flag = 1;
}
