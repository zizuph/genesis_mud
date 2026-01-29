/*
/d/Shire/greyhavens/wep/sling.c

by Palmer, Dec 03, 2003

*/

inherit "/d/Shire/abandoned/greyhavens/wep/sling_base";
// inherit "/std/bow";
#include <formulas.h>


public void
create_bow()
{
    set_short("hobbit sling");
    set_name("sling");
    set_adj("leather");
    set_long("This all leather sling was made for hobbits, by hobbits.\n" +
	     "There is a small note attached to the pouch.\n");

    add_item("note", "On the back of the leather pouch, someone has written:\n\n" +
	     "aim target [in location]    - Aims sling at target, hit\n" +
	     "                              location is optional.\n\n" +
	     "fire                        - Slings rock at aimed target.\n\n" +
	     "shoot target [in location]  - Aims and fires at target.\n\n" +
	     "unload                      - Unloads the rock and stops you winding up.\n" +
	     "\n\n" +
	     "secondary [command]         - Specifies the command to\n" +
	     "                              perform if you should run\n" +
	     "                              out of rocks.\n\n" +
	     "repair sling                  - Puts a new pouch on a sling.\n\n" +
	     "                              a bow.\n\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 40));
    set_hit(40);
    set_pen(40);
}


