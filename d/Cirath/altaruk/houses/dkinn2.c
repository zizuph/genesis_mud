/*
 * /d/Cirath/altaruk/houses/dead_kank_inn.c
 *
 * The backroom of the inn in Altaruk.
 * It uses the room_chair code from Gondor.
 *
 * Azazel
 */
#pragma strict_types

#include "../defs.h"
inherit "/d/Cirath/std/room.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "/d/Cirath/common/mobber.h"

#define TABLE_NAME	"large table"

/* prototypes */
public void	create_room();
public void	init();
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);	/* VBFC for chairs */

void
reset_room()
{
   bring_room_mob("bard",ALT_NPC+"bard.c",1,1);
   bring_room_mob("dancer",ALT_NPC+"dancer.c",1,1);
}

void
create_room()
{
    set_short("the Dead Kank Inn backroom.");
    set_long("This is the back room of the Dead Kank inn." +
        " A smoke filled room with tables and a stage at" +
        " the far end. Dubious characters are gambling or" +
        " arguing over some far fetched subject. The room" +
        " went completely silent as you walked in and for a" +
        " second all eyes where on you, but soon became just" +
        " as noisy as it where. A female dancer is performing" +
        " on the stage.\n");

    add_chair(TABLE_NAME, "[down] [at] [the] [large] 'table'",
        8, "at", 0);

    add_item("stage", "The stage is just a step higher that the" +
        " rest of the floor. A half-naked woman is dancing all" +
        " over it. A bard plays on some strange stringed instrument" +
        " in the corner of the stage.\n");

    add_item(({"wall", "walls"}), "The walls are sandstone" +
        " with dents and carvings You can also see the odd" +
        " bloodstain.\n");

    add_item(({"chair", "chairs"}), "There are chairs scattered" +
        " all around the room.\n");

    add_item( ({ "large table", "table" }), &look_at(TABLE_NAME) );

    add_item( ({ "tables", "large tables" }),
        &look_at("tables"));
       
    add_prop(ROOM_I_INSIDE,1);
    add_exit("dead_kank_inn.c","north", check_sitting, 1);

    reset_room();

}

public void
init()
{
    ::init();
    init_room_chairs();	/* add chair verbs */
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

    if (arg == TABLE_NAME)
    {
    	return "The large wooden table is all" +
        " scratched from the brawls that sometimes break out" +
        " in here.\n" + 
	    sitting_on_chair(TABLE_NAME, this_player(), 0, 1);
    }

    return "The wooden tables are all" +
        " scratched from the brawls that sometimes break out" +
        " in here.\n" +
	sitting_on_chair(TABLE_NAME, this_player(), 0, 0);
}

public void
do_sit_msgs(object pl, string prep, string name)
{
   if ( name == TABLE_NAME )
   {
        write("You pull up a chair and sit down at the large" +
            " wooden table.\n");
        say(QCTNAME(pl)+" sits pulls up a chair and down at" +
            " the large wooden table.\n");
   }
   else
   {
	::do_sit_msgs(pl, prep, name);
   }
}

public void
do_stand_msgs(object pl, string name)
{
   if ( name == TABLE_NAME )
   {
        write("You get up from the large wooden table.\n");
        say(QCTNAME(pl)+
	   " gets up from the large wooden table.\n");
   }
   else
   {
	::do_stand_msgs(pl, name);
   }
}