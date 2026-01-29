/*
 * Sign/crossroads outside Bree
 * adapted from old Bree by Finwe, April 2002
 *
 * 07 Sept 2003 Palmer - Fixed lean action , added map back to sign
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit "/d/Shire/bree/base_common";
inherit "/d/Shire/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#define SIGN_LEAN   "i_am_leaning"
#define SIGN_SIT    "on top of the sign"

public string	look_at(string arg);	/* VBFC for chairs */

object sign;


void
create_shire_room()
{
   set_short("Crossroads");
   set_long("You are standing on a great crossroad west of the " +
        "town Bree. The Greenway, the Old North Road and the Great " +
        "East Road meet here. A huge sign has been posted here " +
        "for all to read.\n");

   sign = clone_object(STAND_OBJ + "sign");
   sign -> set_name("sign");
   sign -> set_adj("huge");
   sign -> set_short("huge sign");
   sign -> set_long(
      "\n\n"+
      "      __________________________________________________________\n"+
      "     |                                                          |\n"+
      "     |                    The Old North Road                    |\n"+
      "     |                            to                            |\n"+
      "     |                 Deadman's Dike (Fornost)                 |\n"+
      "     |                            /\\                            |\n"+
      "     |                            ||                            |\n"+
      "     |                            ||                            |\n"+
      "     |       The Shire    The Great Eastroad      Bree-hill     |\n"+
      "     |           and    <=====================>       and       |\n"+
      "     |      Greyhavens.           ||           Misty Mountains. |\n"+
      "     |                            ||                            |\n"+
      "     |                            \\/                            |\n"+
      "     |                       The Greenway                       |\n"+
      "     |                            to                            |\n"+
      "     |                          Gondor                          |\n"+
      "     |                                                          |\n"+
      "     |__________________________________________________________|\n"+
      "                                 |    |\n"+
      "                                 |    |\n"+
      "                                 |    |\n"+
      "                                 |    |\n"+
      "   ______________________________|____|______________________________\n");

   sign -> move(TO);
   add_item(({"bree","hill","wall"}),
      "To the east, you see Bree-Hill and the town of Bree beneath. "+
      "A large wall can be seen surrounding the town, and the only "+
      "entrance is through the West-Gate.\n");
   add_item(({"gate","west-gate"}),
      "The gate is not here, you'll have to go east first.\n");
   add_item(({"road","roads"}),
      "Which road do you mean?\n");
   add_item(({"eastroad","east road","west road", "great east road"}),
      "The Great East Road looks well trodden.\n");
   add_item(({"greenway","south road","south way"}),
      "The Greenway looks not so well trodden, in fact grass grow "+
      "on the road, hence the name...\n");
    add_item(({"north road","old north road"}),
        "It seems not to have been used so much.\n");
    set_add_sky();
    room_add_object("/d/Shire/bree/rooms/road/behind_sign");

   add_exit(ER_DIR + "er29","west","@@tree_west@@",1);
   add_exit(ROAD_DIR + "road01", "east","@@tree_east@@") ;
   add_exit(GWAY_DIR  + "gw1", "south", "@@tree_south@@");
   add_exit(ROAD_DIR + "nroad01", "north", "@@tree_north@@");
}

void tree_north()
{
//    tell_room(ROAD_DIR + "treetop.c", QCTNAME(TP) + " went north under the tree.\n");
    tell_tree("went north onto the old highway.");
}

void tree_south()
{
//    tell_room(ROAD_DIR + "treetop.c", QCTNAME(TP) + " went south leaving the Crossroads.\n");
    tell_tree("went south down the Greenway.");
}

void tree_east()
{
//    tell_room(ROAD_DIR + "treetop.c", QCTNAME(TP) + " went east leaving the Crossroads.\n");
    tell_tree("went east leaving the Crossroads.");
}

void tree_west()
{
//    tell_room(ROAD_DIR + "treetop.c", QCTNAME(TP) + " went west leaving the Crossroads.\n");
    tell_tree("went west leaving the Crossroads.");
}

void
init()
{
    ::init();
    add_action("do_lean","lean");
    add_action("do_stand","stand");
    add_action("do_nothing","north");
    add_action("do_nothing","south");
    add_action("do_nothing","east");
    add_action("do_nothing","west");
    add_action("do_nothing","northeast");
    add_action("do_nothing","northwest");
    add_action("do_nothing","southwest");
    add_action("do_nothing","southeast");
    add_action("do_nothing","jump");
    add_action("do_nothing","tackle");
    add_action("do_nothing","dance");
    add_action("do_nothing","bow");
    add_action("do_nothing","curtsey");
    add_action("do_nothing","wiggle");
    add_action("do_nothing","strut");
    add_action("do_nothing","kill");

}

int
do_lean(string str)
{
    if(str!="against sign" && str!="against huge sign" &&
        str!="up against sign" && str!="up against huge sign")
    {
	    write("Lean against what, the sign?\n");
	    return 1;
    }

    TP->add_prop(LIVE_S_EXTRA_SHORT, " leaning against the sign");
    TP->add_prop(SIGN_LEAN,1);
    write("You lean against the sign. You may 'stand up' when rested.\n");
    say(QCTNAME(TP)+ " leans against the sign.\n");
    return 1;

}

int
do_stand()
{
    if(!TP->query_prop(SIGN_LEAN))
    {
	write("But you're not leaning against the sign!\n");
	say(QCTNAME(TP)+ " kicks a rock in the road absentmindedly.\n");
	return 1;
    }

    TP->remove_prop(SIGN_LEAN);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You push up away from the sign with a spring in your step.\n");
    say(QCTNAME(TP)+ " pushes up away from the sign with a spring in " +
        HIS_HER(TP) + " step.\n");
    return 1;

}

int
do_nothing()
{
    if(TP->query_prop(SIGN_LEAN))
    {
	write("You can't do that while leaning against the sign!\n");
	say(QCTNAME(TP)+ " looks around the crossroads.\n");
	return 1;
    }
}



/*
 * Function name:	look_at
 * Description	:	VBFC to describe chair/sofa + occupants
 * Arguments	:	string arg -- what's being looked at
 *				      null str -> it's the room
 * Returns	:	string -- the description
 */

public string
look_at(string arg)
{
      switch ( arg )
    {
        case SIGN_SIT:
	        return "The sign is large and rectangular. It has been pounded into the ground. On it are directions pointing to different locations in Middle-earth.\n"+
	        sitting_on_chair(SIGN_SIT, this_player(), 0);
            break;

    }
} 
