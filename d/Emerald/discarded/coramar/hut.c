/*
 * HUT.c
 * This is Thanduin's hut. This hut is crucial to the entrance quest
 * for the Druids... Player's can roast game they've found in traps in
 * the forest.
 */


#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include "coramar.h"
#include "dirheader.h"

#define GAME_ID "_mist_forest_small_game_"

#define FIRE_ROASTING    1;
#define FIRE_DONEROAST   2;
#define FIRE_EMPTY       3;

inherit "/std/room";

int toast_game(string str);
int toast_game2(string str);
int get_rabbit(string str);

void do_roast(object bunny, object plr);
void complete_roast();
string stoke_fire;

int fire_status;
int roast_alarm;

void
create_room()
{
    set_short("A small, modest wooden hut");

    set_long("   This is a small, modest wooden hut. The walls are "+
	"made of a sturdy, but not particularly pretty dark wood. "+
	"The small, single-room dwelling seems fairly dry and able "+
	"to keep the weather outside. In the middle of the room there "+
	"is a heavy wooden table and an accompanying dark wood chair. "+
	"At the back of the room there are several crudely constructed "+
	"shelves, racks and pins for hanging cloaks. Cleverly "+
	"built into the north wall is a small fireplace. An iron "+
	"tray holds several burning logs beneath a roasting spit. An "+
	"iron funnel leads to a pipe that carries the smoke out "+
	"of the hut. The entire hut is bathed in the soft, flickering "+
	"light of the fireplace. The soft crackling and pleasant "+
	"smell of the burning fireplace creates a warm, safe feeling "+
	"here.\n"+
	"   @@display_fire_status@@\n\n");

    add_item(({"walls", "wood walls", "wooden walls", "wall",
	"wooden wall", "dark wood walls", "sturdy walls"}),
	"The walls of the hut are sturdy and dark, but less "+
	"appealing than a softer, lighter wood might be. It gives "+
	"the impression that the room is much smaller than it "+
	"truly is. The darkness of the wood doesn't seem to be "+
	"completely the fault of the wood. You notice several "+
	"glistening places on the wood from some kind of paste. It "+
	"could be some kind of treatment to prevent water damage "+
	"to the wood.\n");

    add_item( ({"table", "wooden table", "heavy table", 
	"heavy wooden table"}),
	"The heavy wooden table in the center of the hut is made "+
	"of the same planks of shaved wood as the rest of the "+
	"dwelling. It is very thick, sturdy-looking wood. On top "+
	"of the table there is a plate, a few pieces of cutlery "+
	"and a large mug half-filled with ale.\n");

        add_cmd_item(({"table", "wooden table", "heavy table"}),
		({"lift", "get", "take","push", "pull"}),
		"That table is far too heavy!\n");

       add_item("plate",
	   "The plate has some crumbs on it. It looks like someone "+
	   "has eaten on this plate recently.\n");
	  
          add_cmd_item("plate",
		({"get", "take", "steal", "borrow"}),
		"You wouldn't want to take someone else's plate, "+
		"would you? Its owner might get quite angry.\n");

       add_item(({"cutlery", "pieces of cutlery"}),
	   "The cutlery looks old, well-used and functional. Nothing "+
	   "fancy.\n");

	   add_cmd_item( ({"cutlery", "pieces of cutlery"}),
		({"get", "lift", "take", "steal", "borrow", "grab"}),
		"That belongs to someone else. How would he eat "+
		"without his cutlery?\n");

       add_item(({"mug", "large mug"}),
	   "The large mug is half-filled with ale. It looks like "+
	   "someone drank out of it recently.\n");       

           add_cmd_item( ({"mug", "large mug"}),
		({ "get", "lift", "take", "borrow", "steal", "grab"}),
		"That mug belongs to someone else. Don't you think "+
		"he would notice it missing?\n");

    add_item( ({"chair", "wood chair", "wooden chair",
	"dark wood chair", "dark chair"}),
	"The dark wooden chair is thick, sturdy and "+
	"comfortable-looking, even though it doesn't have any "+
	"cushioning.\n");

	   add_cmd_item( ({"chair", "wood chair", "wooden chair",
		"dark wood chair", "dark chair"}),
		({"get", "steal", "borrow", "lift", "push", "pull"}),
		"Even that is too heavy, and besides, this place "+
		"is occupied and its owner might notice it missing.\n");

    add_item("fireplace",
	"The fireplace is small and looks extremely well-used. Atop "+
	"the iron tray base rest a few burning logs. Above that "+
	"sits a roasting spit that looks as though it gets used "+
	"daily. Above the fireplace is a funnel which leads to "+
	"an exhaust pipe in the roof of the hut.\n");

    add_item("fire",
	"There are several logs in the fireplace burning.\n");

      add_cmd_item("fireplace",
		   "get",
	           "It is attached to the house, you simply can't "+
		   "get it.\n");

      add_cmd_item("fire",
		   "stoke",
		   "@@stoke_fire@@\n");

    add_item( ({"tray", "bottom tray", "base", "iron base",
	"iron tray"}),
	"The iron tray is being used as the base for the fireplace. "+
	"The edges are curved upward to prevent the hot coals from "+
	"starting a fire in the hut.\n");
       
       add_cmd_item( ({"tray", "bottom tray", "base", "iron base",
		"iron tray"}),
	 	({"get", "borrow", "steal", "grab", "take"}),
		"It is firmly attached to the floor, you can't "+
		"take it.\n");

    add_item( ({"exhaust pipe",  "iron pipe", "pipe", "funnel",
	"iron funnel", "exhaust"}),
	"The black funnel above the fireplace catches the smoke and "+
	"sends it out the roof of the hut through the narrow pipe. "+
	"The thick soot gathered around the edges of the funnel "+
	"indicates that the fireplace is probably burning all "+
	"day long.\n");

        add_cmd_item( ({"exhaust pipe", "iron pipe", "pipe" ,"funnel",
		"iron funnel", "exhaust"}),
		({"get", "take", "grab" ,"borrow", "steal", "move"}),
		"It is attached in various places. You might fill "+
		"the hut with smoke if you tampered with it.\n");

    add_item( ({"up", "roof"}),
	"The roof of the hut is slightly angled and has a black "+
	"iron pipe exiting through it, letting the smoke from "+
	"the fireplace leave.\n");


    add_item(({"spit","roasting spit"}),
	"@@display_spit_status@@\n");

    add_cmd_item( ({"spit", "roasting spit"}),
		({"get", "take", "borrow", "steal", "move", "push",
		"pull"}),
		"It is firmly attached to the fireplace. You can't "+
		"budge it out of position.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT, "You feel an overwhelming power "+
	"resisting your will.\n");

    reset_euid();
    clone_object(CORAMAR_OBJ+"hutdoor_in")->move(this_object(),1);
    clone_object(CORAMAR_NPC+"thanduin")->move(this_object(), 1);

}

string
display_fire_status()
{
    if (fire_status == FIRE_EMPTY)
      return "The spit over the fire is currently empty save "+
	"for a few leftover bits from the last time a rabbit "+
	"was roasted.";
    else if (fire_status == FIRE_ROASTING)
      return "There is a delicious-looking rabbit roasting over "+
	"the fire on a spit.";
    else
      return "There is a delicious-looking rabbit on the spit "+
	"over the calm fire. It looks ready to eat.";
}

string
display_spit_status()
{
    if (fire_status == FIRE_EMPTY)
	return "The spit is empty.";
    else if (fire_status == FIRE_ROASTING)
	return "There is a juicy, delicious-looking rabbit "+
	"roasting on it.";
    else
	return "There is a fully-cooked, delicious looking "+
	"rabbit on it.";
}

void
init()
{
    ::init();
    
    add_action(toast_game, "put");
    add_action(toast_game2, "roast");
    add_action(toast_game2, "cook");
    add_action(get_rabbit, "get");
    add_action(get_rabbit, "take");
}

int
toast_game(string str)
{
    object rabbit;

    if (str != "rabbit on spit")
    {
        notify_fail("Put what where?\n");
        return 0;
    }

    if (!(rabbit=present(GAME_ID, this_player())))
    {
        write("You have no rabbit to put on the spit.\n");
        return 1;
    }

    do_roast(rabbit, this_player());
    return 1;
}

int
toast_game2(string str)
{
    if (str != "rabbit")
    {
        write("What did you want to cook?\n");
        return 1;
    }

    if (!(rabbit=present(GAME_ID, this_player())))
    {
       write("You have no rabbit to cook.\n");
       return 1;
    }

    do_roast(rabbit, this_player());
    return 1;
}

void
do_roast(object bunny, object plr)
{
    if (fire_status == FIRE_ROASTING)
    {
         plr->catch_msg("There is already something roasting "+
		"on the spit!\n");
         return;
    }
    if (fire_status == FIRE_DONEROAST)
    {
         plr->catch_msg("There is a fully cooked rabbit already "+
		"on the spit.\n");
         return;
    }

    plr->catch_msg("You spear the small animal with the spit "+
	"and hang it back up over the fire. The spit begins "+
	"to slowly turn on its own.\n");
    tell_room(this_object(), QCTNAME(this_player())+" spears a "+
	"small animal with the spit and hangs it back up over "+
	"the fire, where the spit begins to turn on its own.\n",
	plr);
    bunny->remove_object();
    fire_status = FIRE_ROASTING;
    roast_alarm = set_alarm(300.0, 0.0, complete_roast);
    return 1;
}

void
complete_roast()
{
    fire_status = FIRE_DONEROAST;
    tell_room(this_object(),
	"The spit stops turning and the fire calms down as the "+
	"rabbit hanging above the coals appears to be "+
	"fully cooked.\n");
}

int
get_rabbit(string str)
{
    object cooked_rabbit;

    if (str != "rabbit")
	return 0;

    if (fire_status == FIRE_ROASTING)
    {
        write("The rabbit is still being roasted.\n");
        return 1;
    }
    if (fire_status == FIRE_EMPTY)
    {
        write("There is nothing on the spit to take.\n");
        return 1;
    }


    write("You take the freshly roasted rabbit from the spit.\n");
    say(QCTNAME(this_player()+" takes the freshly roasted "+
	"rabbit from the spit.\n");
    fire_status = FIRE_EMPTY;
    reset_euid();
    cooked_rabbit = clone_object(CORAMAR_OBJ+"roastrabbit");
    cooked_rabbit->move(this_player());
}

int
query_prevent_snoop()
{
    return 1;
}

string
stoke_fire()
{
    say(QCTNAME(this_player())+" stokes the fire.\n");
    return "You stoke the fire.";
}