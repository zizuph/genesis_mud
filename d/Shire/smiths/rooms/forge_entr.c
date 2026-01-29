/*
     The entrance to the forges
*/

#pragma save_binary;

inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

#include <composite.h>
#include <filter_funs.h>

#define FORGE_NE          SMITHSDIR_ROOMS + "forge_ne"
#define FORGE_E           SMITHSDIR_ROOMS + "forge_e"
#define FORGE_SE          SMITHSDIR_ROOMS + "forge_se"
#define FORGE_S           SMITHSDIR_ROOMS + "forge_s"

string do_check();

void
create_room() {
   set_short("Forge entrance");
   set_long("This is the entrance to the forges. It is a large " +
        "room with several entrances leading to private forges " +
        "for Blacksmiths to use.\n");

   add_exit(SMITHSDIR_ROOMS+"discus","west",0);
   add_exit(SMITHSDIR_ROOMS+"forge_ne","northeast",0);
   add_exit(SMITHSDIR_ROOMS+"forge_e","east",0);
   add_exit(SMITHSDIR_ROOMS+"forge_se","southeast",0);
   add_exit(SMITHSDIR_ROOMS+"forge_s","south",0);

   if (!objectp("guild_assistant")) 
        room_add_object(SMITHSDIR_NPC+"berim", 1, QCTNAME(TO)+" arrives.\n");

    add_cmd_item("forges", "check", "@@forge_check@@");

   add_prop(ROOM_I_INSIDE,1);
// safe rooms
/*
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
*/
}

public void
init()
{
   ::init();
    add_action(do_check,   "smcheck");
}


/*
 * Routine to check who is in forges
 */

string
do_check()
{
    object other_room;
    mixed opeople;
 
    write("                                Forge Occupants\n");
    write("======================================================"+
            "========================\n\n");
 
 // check forge_ne
    if (!LOAD_ERR(FORGE_NE))
        other_room = find_object(FORGE_NE);
    else
        write("\tNortheast Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\tNortheast Forge: Deserted and quiet.\n");
    else
        write("\tNortheast Forge: "+COMPOSITE_LIVE(opeople)+"\n");

 
 // check forge_e
    if (!LOAD_ERR(FORGE_E))
        other_room = find_object(FORGE_E);
    else
        write("\t     East Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\t     East Forge: Deserted and quiet.\n");
    else
        write("\t     East Forge: "+COMPOSITE_LIVE(opeople)+"\n");
 
 // check forge_se
    if (!LOAD_ERR(FORGE_SE))
        other_room = find_object(FORGE_SE);
    else
        write("\tSoutheast Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\tSoutheast Forge: Deserted and quiet.\n");
    else
        write("\tSoutheast Forge: "+COMPOSITE_LIVE(opeople)+"\n");
 
 // check forge_s
    if (!LOAD_ERR(FORGE_S))
        other_room = find_object(FORGE_S);
    else
        write("\t    South Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\t    South Forge: Deserted and quiet.\n");
    else
        write("\t    South Forge: "+COMPOSITE_LIVE(opeople)+"\n");

    write("\n======================================================"+
            "========================\n\n");

return "";
}
