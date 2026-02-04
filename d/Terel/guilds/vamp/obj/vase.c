/* A vase for the vampyres to fill with flowers.
 * An empty vase displeases the Eldest.
 *
 * Creator: Lilith, Sept 24 2008
 */
inherit "/std/container";
#include "/d/Terel/include/Terel.h";
#include <composite.h>

public nomask void create_container()
{

    set_name("vase");
    add_name("flower vase");
    set_adj(({"bloodstone", "fluted", "opaque", "flower"}));
    set_short(VBFC_ME("empty_str") + "bloodstone vase");
    set_long("This tall vase appears to be carved from an enormous piece of "+
        "the semi-precious gem known as bloodstone. It is nearly the height of "+
        "a dwarf, with a long, fluted neck and a wide-rimmed mouth. It has been "+
        "placed on the floor before the dais, within easy reach of the chair and "+
        "its motionless occupant.\n");

    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 600);
    add_prop(OBJ_M_NO_GET, "You'd sooner bait a troll in his den than move "+
        "that vase from its place.\n");
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 20000);

}

public string
empty_str()
{
    if(!sizeof(all_inventory(TO)))
        return "empty ";
    else
        return "flower-filled ";
}

/*
 * Function name: test_vase
 * Description  : Test for presence of flowers.
 * Returns      : 1-Flowers are present.
 *                0-Empty.	 
 */
public int
test_vase()
{
    if (sizeof(all_inventory(this_object())) < 1)
        return 0;
    else 
        return 1;
}

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
int
prevent_enter(object entering)
{
    if (entering->id("flower"))
        return 0;
    if (entering->id("flowers"))
        return 0;
    if (entering->id("flower arrangement"))
        return 0;
    if (entering->id("bouquet"))
        return 0;
    else
        write("The " + entering->short()+ " does not belong in "+
            "the "+ short() +".\n");
        return 1;
}

