
/* 
   The Calian Council study 

   Coded by Maniac. 
*/ 


#include <macros.h>
#include <stdproperties.h>
#include <std.h>

#include "defs.h"
#include COUNCIL_HEADER
 
#pragma save_binary

inherit "/std/room";

int
query_prevent_snoop()
{
    return 1;
}

void 
create_room()
{
    set_short("The study of the Calian Council");
    set_long("The study of the Calian Council. This is a smallish " +
	"room where the Council can read its guidelines as " +
	"set by Caliana, but it's also somewhere to come for a " +
	"bit of peace and quiet from the busy world of Genesis. " +
	"A small oak reading table and a comfortable chair " +
	"are the only furniture in the room, which is lit by the " +    
	"gentle light of candles.\n");
   
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    
    add_item( ({ "candle", "candles" }),
	"These small candles with silver sticks perch on the " +
	"reading desk so you won't have to strain your eyes.\n"); 
    add_item( ({ "table" }),
	"A small reading table made of oak, slanted slightly so that " +
	"you don't have to bend your back to read what's on it.\n");
    add_item( ({ "chair" }),
	"A comfortable looking chair sat next to the reading table.\n");

    add_exit(ROOM("light_councilroom1"), "north", 0);
 
    clone_object(OBJECT("council_guide_book"))->move(THIS);
}

/*
 * Function:     prevent_enter
 * Description:  Returns 1 if the object is a player who
 *               can enter the council chambers, or a non-
 *               living. Returns 0 otherwise. 
 */ 
int
prevent_enter(object ob)
{
    string nm; 

    if (!living(ob))
        return 0; 

    nm = ob->query_real_name(); 

    if (!(COUNCIL_CODE->is_council_member(capitalize(nm)) ||
          COUNCIL_CODE->is_calian_wiz(ob) || 
          (SECURITY->query_wiz_rank(nm) >= WIZ_ARCH))) 
    {
        tell_object(ob, 
            "You're not coming into the Calian Council " +
            "headquarters without special permission!\n"); 
        return 1; 
    }

    return 0; 
}

