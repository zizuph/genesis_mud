/*
   Wayreth.

   equiproom.c
   ------------

   Coded ........: 97/09/11
   By ...........: Karath

*/

#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include "/d/Krynn/common/defs.h"

inherit TOWERROOM;

#define TRACK      "/d/Krynn/wayreth/tower/rack/"

object cabinet, cupboard, armour, weapon, wand, staff, misc, aide;

public object
query_rack_object()
{
    return weapon;
}

void
reset_tower_room()
{

    if(!objectp(misc))
    {
	misc = clone_object(TOBJ + "misc_rack");
	misc->move(TO);
    }
    if(!objectp(cabinet))
    {
	cabinet = clone_object(TRACK + "cabinet");
        // cabinet->set_rack_log_file(WLOG + "racks/wohs_rack_log");
	cabinet->move(TO);
    }
    if(!objectp(cupboard))
    {
	cupboard = clone_object(TRACK + "herb_cupboard");
        // cupboard->set_rack_log_file(WLOG + "racks/wohs_rack_log");
	cupboard->move(TO);
    }
    if(!objectp(armour))
    {
	armour = clone_object(TRACK + "armour_chest");
        armour->set_rack_log_file(WLOG + "racks/wohs_rack_log");
	armour->move(TO);
    }
    if(!objectp(weapon))
    {
	weapon = clone_object(TRACK + "weapon_rack");
        weapon->set_rack_log_file(WLOG + "racks/wohs_rack_log");
	weapon->move(TO);
    }
    if(!objectp(wand))
    {
	wand = clone_object(TRACK + "wand_shelf");
        wand->set_rack_log_file(WLOG + "racks/wohs_rack_log");
	wand->move(TO);
    }
    if(!objectp(staff))
    {
	staff = clone_object(TRACK + "staff_rack");
        staff->set_rack_log_file(WLOG + "racks/wohs_rack_log");
	staff->move(TO);
    }
    if (!objectp(aide))
    {
        aide = clone_object(TRACK + "rack_attendant");
        aide->move(this_object());
    }

    return;
}

void
create_tower_room()
{
   set_short("The equipment storage room");
   set_long("This room is very spartan, the floor a shiny hardwood. "+
	"This is the place where common equipment is stored for "+
	"mages and apprentices alike to store and share their "+
	"needed items for travel in the dangerous realms.\n");

   add_item("floor", "The floor is hardwood, polished and waxed causing "+
		"light to reflect, illuminating the place.\n");

    set_wall_type(2);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(WTOWER + "meditation", "north", 0);
    reset_tower_room();
}

public mixed
prevent_teleport()
{
    if(!this_player())
	return 0;

    if(WOHS_MANAGER->query_renegade_wohs(TP))
        return "Something prevents you from teleporting there.";

    if(WOHS_MANAGER->query_wohs_train_rack_ban(TP))
        return "Something prevents you from teleporting there.";

    if(this_player()->query_guild_name_occ() == "Wizards of High Sorcery")
	return 0;

    return "Something prevents you from teleporting there.";
}

public void
leave_inv(object ob, object to)
{
    object *books;
    
    if (sizeof(books = filter(deep_inventory(ob), &->query_rack_log())))
    {
        if (objectp(aide))
        {
            ob->catch_msg(QCTNAME(aide) + " gestures towards you as you "
            + "are about to leave, magically retrieving the " 
            + books[0]->short() + " from your possession.\n");
            aide->tell_watcher(QCTNAME(aide) + " gestures towards "
            + QTNAME(ob) + " as " +HE(ob)+ " leaves, magically retrieving "
            + LANG_ADDART(books[0]->short()) + ".\n", ({ ob }));
        }
        
        books->remove_object();
    }
    
    ::leave_inv(ob, to);
}