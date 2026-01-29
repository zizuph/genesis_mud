/*
 *  Based on /w/cedivar/fishing/obj/junk.c
 *  Created April 2018, Cedivar
 */

#include <stdproperties.h>

inherit "/std/object";

/*
 * Function name:        create_object
 * Description  :        the constructor
 */
void create_object()
{

    int junk_roll;

    junk_roll = random(6);
    switch (junk_roll)
    {
        case 1:
            set_name("seaweed");
            add_name("trash");
            set_adj("bit");
            set_short("bit of seaweed");
            set_pshort("bits of seaweed");
            set_long("A small bit of green and brown seaweed that "
                + "is quite slimy.\n");
            remove_prop(OBJ_I_VALUE);
            add_prop(OBJ_I_WEIGHT, 5);
            add_prop(OBJ_I_VOLUME, 5);
            break;
	
        case 2:
            set_name("boot");
            add_name("trash");
            set_adj("left");
            set_short("left boot");
            set_long("An old boot that has been rotted by the sea.\n");
            remove_prop(OBJ_I_VALUE);
            add_prop(OBJ_I_WEIGHT, 5);
            add_prop(OBJ_I_VOLUME, 5);
            break;
	
        case 3:
            set_name("boot");
            add_name("trash");
            set_adj("right");
            set_short("right boot");
            set_long("An old boot that has been rotted by the sea.\n");
            remove_prop(OBJ_I_VALUE);
            add_prop(OBJ_I_WEIGHT, 5);
            add_prop(OBJ_I_VOLUME, 5);
            break;
	
        case 4:
            set_name("driftwood");
            add_name("trash");
            set_adj("chunk");
            set_short("chunk of driftwood");
            set_pshort("chunks of driftwood");
            set_long("A broken piece of driftwood, off of what you "
                + "have no idea though.\n");
            remove_prop(OBJ_I_VALUE);
            add_prop(OBJ_I_WEIGHT, 5);
            add_prop(OBJ_I_VOLUME, 5);
            break;
	
        case 5:
            set_name("junk");
            add_name("trash");
            set_adj("handful");
            set_short("handful of junk");
            set_pshort("handfuls of junk");
            set_long("A handful of random pieces of junk ranging from "
                + "broken glass to corroded metal.\n");
            remove_prop(OBJ_I_VALUE);
            add_prop(OBJ_I_WEIGHT, 5);
            add_prop(OBJ_I_VOLUME, 5);
            break;

        default:
            set_name("gunk");
            add_name("trash");
            set_adj("piece");
            add_adj("brown");
            set_short("piece of brown gunk");
            set_pshort("pieces of brown gunk");
            set_long("You've no idea what this is exactly but it's brown "
                + "slimy and smells horrid.\n");
            remove_prop(OBJ_I_VALUE);
            add_prop(OBJ_I_WEIGHT, 5);
            add_prop(OBJ_I_VOLUME, 5);
    }
}