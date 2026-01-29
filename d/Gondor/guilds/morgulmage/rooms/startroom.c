/*
 *  The Tower of the Society of the Morgul Mages
 *  floor 3 (startroom.c)
 *
 *  Special atributes: Members of the Soicety may choose to have their
 *                     logon location moved here.
 *
 *  By Randor and Soermo. Last change 28.08.93.
 *  Modification log:
 *  - Olorin, 10-jan-1994: morgul/tower/tower master
 *  - Gorboth, 21-apr-1997: added ROOM_I_NO_CLEANUP prop
 *                          for droproom purposes
 *  - Eowul, 28-feb-2009: Moved to the new guild directory
 *  - Raymundo 3/24/2020: Added \n to add_item("rune", *) and add_item("light", *)
 */
 
#pragma save_binary

inherit "/d/Gondor/morgul/tower/tower";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

object  orb;
int     query_my_light_level();

void create_morgul_tower_room()
{
    object rack, chest;

    set_level(4);
    set_room_type("dark gloomy room");
    set_extra_long(" The walls are of smooth, black stone, the only distinctive " +
        "marks being a rune radiating a blue light inscribed on the wall. A mailed " +
        "glove is extending from a granite pedestal set in the southwest corner of the " +
        "room. The doorway leads back into darkness and a big equipment rack is taking " +
        "up the entire north wall.");

    add_item("rune",
        "As you study the rune, it seems to begin to move "+
        "first slowly, and then faster and faster. You cannot pull your "+
        "gaze from it, and soon all you see is blue light. Then a text "+
        "printed in black letters on the blue light appears saying: "+
        "'By touching me you choose this place as the location "+
        "you use when entering this world.'\n");
    add_item("light",
        "There isn't much of it, and the little little there " +
        "is in a very cold shade of blue. It also seems to just be there "+
        "and you cannot find out what's really radiating it.\n");
 
    FLOOR
    WALLS
    ROOF

    add_exit(MORGUL_ROOM_DIR + "tower_4c", "south", 0, 0);

    add_prop(ROOM_I_LIGHT, query_my_light_level);
    add_prop(ROOM_I_NO_CLEANUP, 1); // For droproom purposes

    rack = clone_object(MORGUL_OBJ_DIR + "rack");
    rack->move(this_object());
    rack->set_rack_type(0);

    orb = clone_object(MORGUL_OBJ_DIR + "glowing_orb");
    orb->move(this_object());

    chest = clone_object(MORGUL_OBJ_DIR + "great_chest");
    chest->move(this_object());
}

int query_my_light_level()
{
    if(!orb->query_is_lit())
        return 1;

    return 1 - query_internal_light();
}

void init()
{
    ::init();
    add_action("touch_rune","touch");
}
 
int touch_rune(string str)
{
    if (str != "rune")
    {
        NF("Touch what?\n");
        return 0;
    }
    if (TP->query_wiz_level())
    {
        NF("You are a wizard, you do not need this!\n");
        return 0;
    }

    seteuid(getuid());
    if (TP->query_guild_name_occ() == GUILD_NAME)
    {
        TP->set_default_start_location(file_name(TO));
        write("Feeling malice and dark energy flowing through "+
	      "you, this is where you will awaken "+
	      "when you enter into His realm!\n");
        return 1;
    }
    else
    {
        NF("A jolt of electricity forces you to pull your hand away.\n"+
           "A voice in your mind says: Only members of the Society may touch me!\n");
        return 0;
    }
}
 
void update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);
    orb->light_changed(l);
}