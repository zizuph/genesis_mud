//-*-C++-*-
// file name:    /d/Avenir/common/potions/special/nausea.c
// creator(s):   Lilith 04/07/97
// revised:     
// purpose:      The 'poison' from the anarex potion 
// note:         
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Avenir/include/defs.h"

int    time;       /* How long it will be in effect */

void set_time(int i) { time = i; }
void stop_nausea();

void
create_object()
{
    set_long("This thing makes you unable to eat or drink.\n");
    set_short("nausea object");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();

    time = 10;
}

int
no_eat(string str)
{
    write("Gorge rises in your throat at the very idea!\n");
    switch(random(4))
    {
        case 0: TP->command("$gag");          break;
        case 1: TP->command("$puke");         break;
        case 2: TP->command("groan pain");    break;
        case 3: TP->command("frown");         break;
    }
    return 1;
}

void
stop_nausea()
{
    object ob;

    if ((ob = environment(this_object())) && interactive(ob))
	  tell_object(ob, "Your stomach seems to have settled. You "+
            "feel much better now!\n");
    remove_object();
}


void
init()
{
   ::init();

   add_action(no_eat, "drink");
   add_action(no_eat, "quaff");
   add_action(no_eat, "eat");   
}

/*
 * Function name: enter_env
 * Description:   Called each time this object enters another environment
 * Arguments:     to   - The object this object enters
 *		  from - The object this object leaves
 */
void
enter_env(object to, object from)
{
    if (time)
	set_alarm(itof(time), 0.0, stop_nausea);

    if (interactive(to))
    {
        to->add_prop(TEMP_STDFOOD_CHECKED, 1);
        to->add_prop(TEMP_STDDRINK_CHECKED, 1);
        to->add_prop(TEMP_STDPOTION_CHECKED,1);
    }

    ::enter_env(to, from);
}
/*
 * Function name: leave_env
 * Description:   Called when this object is moved from another object
 * Arguments:     from - The object this object is moved from
 *		  to   - The object to which this object is being moved
 */
void
leave_env(object from, object to)
{
    if (interactive(from))
    {
        from->remove_prop(TEMP_STDFOOD_CHECKED);
        from->remove_prop(TEMP_STDDRINK_CHECKED);
        from->remove_prop(TEMP_STDPOTION_CHECKED);
    }
    ::leave_env(from, to);
}
