/* 
 * Garden Shed Shelf for the Elementalist Guilds of Calia
 *
 * There are a few shelves in the shed in the garden that contain the
 * gardening tools necessary to tend the gardens. Each shelf will
 * hold a unique item.
 *  
 * Created by Petros, May 2011
 */

#include <stdproperties.h>
#include "defs.h"

inherit "/std/container";

// Prototypes
public void         fill_shelf();

// Global Variables
public string       shelf_type;

public void
create_container()
{
    set_name("shelf");
    add_name("_garden_shed_shelf");
    add_adj( ({ "gardening", "tools" }) );
    set_short("gardening tools shelf");
    set_long("@@describe_long");
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME, 5000);
    add_prop(CONT_I_RIGID, 1);    
    add_prop(OBJ_M_NO_GET, "The " + short() + " is attached to the "
        + "shed and cannot be taken.\n");    
    add_prop(CONT_I_ATTACH, 1); // allows things to be put "on" the shelf insteads
    
    set_no_show_composite(1);
}

public void
set_shelf_type(string type)
{
    shelf_type = type;
    all_inventory(this_object())->remove_object();
    fill_shelf();
}

public string
get_shelf_type()
{
    return shelf_type;
}

public string
describe_long()
{
    string description = "This " + short() + " is perfect for holding specific "
        + "gardening tools. ";
    
    switch (get_shelf_type())
    {
    case "hoe":
        description += "It looks like this particular shelf has the hooks "
            + "to hold gardening hoes. Hoes would be quite useful in "
            + "breaking up the tough dirt in the garden if you wanted "
            + "to <tend> the garden.";
        break;
    
    case "secateur":
        description += "It looks like this particular shelf has the "
            + "configuration to hold secateurs, otherwise known as "
            + "pruning shears. The secateurs ought to be useful in "
            + "cutting through any branches.";
        break;
    
    case "watering can":
        description += "It looks like this particular shelf has some "
            + "indentations in the shape of watering cans. If you "
            + "were to <tend> the garden, you may need watering cans "
            + "to provide moisure to the earth.";
        break;
    
    case "basket":
        description += "This particular shelf can hold hand-woven baskets "
            + "for use in gathering things in the garden. Baskets should "
            + "be useful for gathering branches after you <tend> the "
            + "garden.";
        break;
    }
    
    return description + "\n\n";
}

public void
clone_multiple_objects(int num_objs, string filename)
{
    setuid();
    seteuid(getuid());
    for (int index = 0; index < num_objs; ++index)
    {
        clone_object(filename)->move(this_object());
    }
}

public void
fill_shelf()
{
    switch (get_shelf_type())
    {
    case "hoe":
        clone_multiple_objects(10, GARDENING_HOE);
        break;
    
    case "secateur":
        clone_multiple_objects(10, GARDENING_SECATEUR);
        break;
    
    case "watering can":
        clone_multiple_objects(10, GARDENING_WATERINGCAN);
        break;
    
    case "basket":
        clone_multiple_objects(10, GARDENING_BASKET);
        break;
    }
}
