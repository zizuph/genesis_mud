// kitchen chest
// creator(s):    Lilith  1/28/97
// last update: 
// purpose:     
// bug(s):
// to-do:

inherit "/std/receptacle";

#include "../holm.h"

/* Function name: reset_placed_functions
 * Description:   This function is called from the placer module to 
 *                reset the object. Can be used to fill the object with 
 *                contents. 
 *
 *    For when it is called see:
 *    /d/Avenir/smis/std/placer_mod.c
 *
 *    If it returns 1, the placer will do nothing, but if it returns 0,
 *    the placer will clone a new object.
 *
 */
int
reset_placed_functions()
{

    if (sizeof(all_inventory(this_object())) < 2 )
    {
	clone_object(DARK + "obj/knife")->move(this_object(),1);
	clone_object(DARK + "obj/knife")->move(this_object(),1);
	clone_object(DARK + "obj/knife")->move(this_object(),1);
    }
    return 1;
}

string
long_desc()
{
    string str;

    if (TO->query_prop(CONT_I_LOCK))
        str = "It is locked. ";
    else
    {
        str = "It is not locked. ";
    }
 
    return "A fairly large chest made of wood, with iron bands for "+
        "support. The wood is highly polished and surprisingly clean."+
        " There is a big iron lock on the chest. " + str;
}

string
lock_desc()
{
    string str;
    if (TO->query_prop(CONT_I_LOCK))
        str = "It is locked. ";
    else
    {
        str = "It is unlocked. ";
    }
    return str;
}
    
void
create_receptacle()
{

    set_name("kitchen chest");
    set_adj(({"iron-banded", "wooden", "utensil"}));
    add_name(({"box", "chest"}));
    set_short("iron-banded wooden chest"); 
    set_long("@@long_desc");

    set_key(KITCH_KEY);
    set_pick(random(20) + 20);

    add_item(({"bands", "iron bands"}),
        "They have been meticulously oiled to prevent rust.\n");
    add_item(({"lock", "iron lock"}), "@@lock_desc");

    add_prop(CONT_I_LOCK, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_WEIGHT, 150000);     // 150 kilos
    add_prop(CONT_I_VOLUME, 40000);      // 40 litres
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 250000); // 250 kilos
    add_prop(CONT_I_RIGID, 1);

    seteuid(getuid(TO));
    reset_placed_functions();
}

