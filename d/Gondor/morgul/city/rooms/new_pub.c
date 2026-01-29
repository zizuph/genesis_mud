/*
 * Dead Tark Pub, Minas Morgul
 * The old pub was creating bugs with ordering, 
 * so I updated it to use the /d/Gondor/lib/inn
 * inherit. I kept as much of Olorin's langage
 * from  July 1993 as possible.
 *
 * Raymundo, Summer 2021
 */

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/open/fireplace/fireplace.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

inherit "/d/Gondor/morgul/city/morgul.c";
//inherit MIRKWOOD_STD_DIR + "room";
inherit "/d/Gondor/lib/inn";
inherit "/d/Gondor/open/fireplace/fireplace";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#pragma save_binary
#pragma strict_types

#define PRICELIST_ID ({"menu","list","sign","pricelist","prices"})
#define RESET_WOOD 10
#define CHAIR_NAME "stool"
#define CHAIR_CAPACITY 30


public void reset_room();
public void init();
public void leave_inv(object ob, object dest);
public string   look_at(string arg);

static object innkeeper;
static object ranger;

void
create_morgul_room()
{
    set_extraline(
        "Here human and orc subjects of the Lord of Morgul gather to "
        + "celebrate victories and to laugh at their dead foes. Several "
        + "wooden tables and chairs are standing here. In front of the "
        + "east wall is a bar. Behind the bar, you can see several "
        + "bottles on a shelf and a menu hanging on the wall. "
        + "The exit out to the street is west.");
    set_road(9);
    set_short_desc("in the Dead Tark Pub in Minas Morgul");

    add_item( ({"stain", "circular stain", "stains", "circular stains"}), 
        "The stains are round and roughly the size of the bottom of a glass. "
        + "Clearly, the patrons don't use coasters.\n");
    add_item( ({"coaster", "coasters"}), "There are no coasters here. That's "
        + "why the bar is stained.\n");
    add_item( ({"gash", "gashes"}), "These gashes look like they were made "
        + "by patrons sticking their knives into the bar. Some of the gashes "
        + "a red mark in them.\n");
    add_item( ({"mark", "red mark", "marks", "red marks", "red gash", "red gashes"}),
        "The red marks appear to be blood!\n");
    add_item( ({"bottle", "bottles", "shelf"}), 
       "The shelf behind the counter of bottles of all sizes and " +
        "shapes. Most of them are close to empty, all are exceptionally " +
        "dirty. " );
      add_item(({"table","tables","chair","chairs"}), 
        "The tables and chairs all have seen better days. Some are " +
        "completely broken, none look as if you would be comfortable using them. " +
        "Certainly, there is not a single chair here on which you could " +
        "sit down without risking to break the chair and fall to the " +
        "ground. So you don't even try to sit down. There are, however, " +
        "some stools near the bar that look more promising.\n");
    add_item( ({"stool", "stools", "bar stool", "bar stools"}), 
        "The stools look "
        + "much sturdier than the chairs. You could probably sit on one of them.\n");
    add_item( ({"wall", "walls"}), "The walls look typical for Minas Morgul. There "
        + "is nothing remarkable about them.\n");
    add_item( ({"floor"}), "The floor is made of stone. It's dirty, as if many "
        + "customers have walked on it today.\n");
    add_item( ({"ceiling"}), "The ceiling keeps the rain off your head.\n");
    add_item( ({"rain"}), "There is no rain here. You're inside.\n");
    add_item("east wall", "You see a bar in front of the east wall. There are some "
        + "bottles on the shelf behind it.\n");
        
    add_cmd_item( ({"on chair", "chair"}), "sit", "You don't dare sit on the chair! " +
        "It'd break!\n");
  
    add_npc(MORGUL_DIR + "npc/drunk");

    add_chair(CHAIR_NAME,
        "[down] [in] [on] [the] [wooden] [bar] 'stool'",
         30, "in", 1, 1);
  
    add_prop(ROOM_I_INSIDE,1);
    
    add_exit(MORGUL_DIR + "city/darkstr2", "west");

    setuid(); 
    seteuid(getuid());

    add_menu_item(MORGUL_DIR + "obj/pub_beer", "drink");
    add_menu_item(MORGUL_DIR + "obj/pub_wine", "drink");
    add_menu_item(MORGUL_DIR + "obj/pub_booze", "drink");
    add_menu_item(MORGUL_DIR + "obj/pub_ghash", "drink");

    set_menu_group_title("drink", "Drinks");

    object bar = clone_object("/d/Gondor/std/inn_bar");
    bar->move(this_object());
    bar->set_short("solid wooden bar");
    bar->set_long("This bar is made of wood and feels quite solid. "
        + "There are circular stains on it from where people have placed "
        + "their drinks. You also notice some gashes on it. \n");
    set_bar(bar);    

    config_default_trade(); 
    configure_inn();

    reset_room();
}


void
remove_object()
{ 
    remove_inn_object();
    ::remove_object();
}


void 
init()
{
    ::init();

    add_action("do_read","read");
    init_inn();

    init_room_chairs();
}

int
do_read(string str)
{
    if(!str)
    {
        notify_fail("Read what?\n");
        return 0;
    }
    
    if(member_array(str, PRICELIST_ID) == -1)
    { 
        notify_fail("Read what?\n");
        return 0;
    }
    write(query_menu_description());
    SAYBB(" reads the sign.");
    return 1;
}

void
reset_room()
{
    if (!objectp(innkeeper)) 
    {
        innkeeper = clone_object(MORGUL_DIR + "npc/ahyando");
        set_innkeeper(innkeeper);
    }

    if (environment(innkeeper) != this_object())
    {
        innkeeper->move_living("inside", this_object());
    }

  
}




public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} 

public string
look_at(string arg)
{
    switch ( arg )
    {
    case CHAIR_NAME:
    return "The wooden bar stool looks like a good place to sit down, and have a drink. \n" +
        sitting_on_chair(CHAIR_NAME, this_player(), 0);
    
    }
}