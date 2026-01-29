/* Remains of india-rubber man. ~solace/puzzle/objects/rubber_pile */

inherit "/std/object";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

int cheese_found, gloves_found;

void create_object()
{
    set_name("rubber");
    add_name("pile");
    set_adj("pile of");
    add_adj("singed");
    set_pshort("piles of singed rubber");
    set_long("Many different sized balls of rubber in a pile. They are "+
        "singed and burnt by different degrees and have a charred smell.\n");

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 7500);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_M_NO_GET, "The pile of singed rubber is too cumbersome to "+
	"lift.\n");
}

mixed do_search(object player, string str) 
{
    object obj;

    seteuid(getuid(TO));

    if(!cheese_found)
    {
        cheese_found = 1;
        obj = clone_object(OBJECTS + "cheese_slice");
    }
    else if(!gloves_found)
    {
        gloves_found = 1;
        obj = clone_object(ARMOUR + "leather_gloves");
    }
    else
        return 0;

    obj->move(E(TO));

    tell_room(E(TO), QCTNAME(player)+" finds "+LANG_ASHORT(obj)+"!\n", player);
    return "You find "+LANG_ASHORT(obj)+"!\n";
}
