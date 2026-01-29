/*      the Calian warrior guild in the crystalline palace

    coder(s):   Glykron

    history:    22. 9.94    created                         Glykron

*/

inherit "/std/room";

#define OLD_START_LOC "/d/Calia/tmp/glykron/palace/guild"
#define NEW_START_LOC "/d/Calia/glykron/palace/rooms/light/guild"

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->query_default_start_location() == OLD_START_LOC)
	ob->set_default_start_location(NEW_START_LOC);
    ob->move(NEW_START_LOC);
}
 
void
create_room()
{ 
}
