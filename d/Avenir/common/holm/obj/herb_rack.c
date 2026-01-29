// herbal drying rack /d/Avenir/common/holm/obj/herb_rack.c
// creator(s):  Lilith  1/28/97
// last update: 
// purpose:     This rack will force_dry() herbs that are put in it.
// note:        The herb selection is randomized.
// bug(s):
// to-do:


inherit "/std/receptacle";

#include "../holm.h"
string *herbs = HERB_MASTER->query_herbs( ({"jungle","stream","desert","pine"}) );

/* Function name: reset_placed_functions
 * Description:   This function is called from the placer module to 
 *                reset the object. Can be used to fill the object with 
 *                contents. 
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
    object herb;

    if (sizeof(all_inventory(this_object())) < 2 )
    {

        herb = clone_object(GET_ONE(herbs));
        herb->move(TO, 1);
        herb = clone_object(GET_ONE(herbs));
        herb->move(TO, 1);
        herb = clone_object(GET_ONE(herbs));
        herb->move(TO, 1);
        herb = clone_object(GET_ONE(herbs));
        herb->move(TO, 1);
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
 
    return "This rack is pungent with the scent of herbs. "+ 
        "Its sides are covered in a fine steel mesh "+
        "which allows the free-flow of air through it. The mesh is "+
        "so fine that it is impossible to see through it to what is "+
        "inside. Herbs are placed inside to dry under controlled "+
        "conditions, protected from dampness and secure from prying "+
        "fingers. There is a small steel lock on the rack. " + str;
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

    set_name("Chumlock's box");
    set_adj(({"herbal", "drying", "mesh"}));
    add_name(({"box", "rack"}));
    set_short("herbal drying rack"); 
    set_long("@@long_desc");

    set_key(HERB_KEY);
    set_pick(random(20) + 10);
    add_item(({"lock", "steel lock"}), "@@lock_desc");
    add_item(({"mesh", "steel mesh", "fine mesh"}),
        "It is of excellent quality and strength.\n");
    add_item(({"rod", "rods", "wooden rods"}),
        "There are several wooden rods inside the box from which "+
        "herbs can be hung for drying.\n");

    add_prop(CONT_I_LOCK,1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_WEIGHT, 150000);     // 150 kilos
    add_prop(CONT_I_VOLUME, 40000);      // 40 litres
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 250000); // 250 kilos
    add_prop(CONT_I_RIGID, 1);

    seteuid(getuid());
    reset_placed_functions();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);


    if (!ob || living(ob)) 
        return;

    if (ob->query_name() == "herb");
    {
        ob->force_dry();
    }
}
