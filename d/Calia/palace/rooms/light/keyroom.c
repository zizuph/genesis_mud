
/* 
 * The keyroom of the Crystalline Palace of Caliana. 
 * Coded by Glykron. 
 * 
 * Access changed by Maniac, 1/10/97
 */ 


#pragma save_binary
#define MIN_REWARD_TO_ENTER 2 

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include "defs.h"
#include COUNCIL_HEADER
inherit CRPALACE_SPECIALS + "calian_utility";


object this;

void
reset_room()
{
}

string
pedestal()
{
    return
        "A brilliant white light eminates from the pedestal.  " +
        (present("crystalline_key") ?
            "A crystalline key is lying on the pedestal." :
            "There is an empty indentation on there with an inscription.") +
        "\n";
}


int
prevent_enter(object ob)
{
    if (!living(ob)) 
        return 0;

    if (ob->query_wiz_level() && 
        ((SECURITY->query_wiz_rank(ob->query_real_name()) >= WIZ_ARCH) ||
         is_calian_wiz(ob))) 
        return 0;

    if ((ob->query_skill(REWARD) >= MIN_REWARD_TO_ENTER) && 
        !ob->query_skill(PUNISHMENT))
        return 0;

    if (COUNCIL_CODE->is_council_member(ob->query_real_name())) 
        return 0;

    tell_object(ob, "You may not enter the keyroom!\n"); 
    return 1; 
}

void
create_room()
{
    set_short("Pedestal Room");
    set_long(
	"This is a large trapezoidal-shaped room whose east and west walls " +
	"slope away from you to the south.  " +
	"A brilliant light fills the room.  " +
        "There is a crystalline pedestal here.  " +
	"\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_guild"), "northwest", 0);
    add_exit(ROOM("light_entrance"), "down", 0);
    add_item("pedestal", "@@pedestal");
    this = THIS;
    OBJECT("crystalline_key")->move(this);
}

int
push(string str)
{
    if (str != "indentation")
        return 0;

    tell_room(this, "A crystalline key appears on the pedestal.\n");
    OBJECT("crystalline_key")->move(this);
    return 1;
}

int
read(string str)
{
    if (str != "inscription" && str != "inscription on indentation" &&
            str != "inscription on pedestal" ||
        present("crystalline_key"))
        return 0;

    write("The inscription says:\n" +
        "Push indentation to recall the key.  " +
        "\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("push", "push");
    add_action("read", "read");
}
