/*
*  /d/Sparkle/area/jade/rooms/jade_attic.c
*  The upper floor of the house in the Jade orchard - an austere dormitory with
*  arrow holes from which an NPC stationed here can engage anyone who attacks
*  another family.c.
*  Created 2017-02-03 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>
#include <composite.h> //For viewing other rooms

/* Global variables */
object  archer,  //The family member on duty here
        native_archer; //The unique family member first spawned here on reset

/* Prototypes */
int     prevent_exit();
object  query_archer();

/*
 * Function name: create_room
 * Description  : Constructor for the attic
 */
void
create_room()
{
    set_short("An austere attic");
    set_long("A bed and small dresser nestle under the sloping ceiling in "
        + "each corner of the "
        + "attic, except for the southwestern one, where bare wooden stairs "
        + "lead down to the ground floor. Small openings have been cut in the "
        + "centres of each ceiling "
        + "and wall, providing views to the north, south, east and west. "
        + "Though this appears to be the livingspace of four people, "
        + "no furniture or possessions obstruct the approach to any of the "
        + "openings, and the floor by and between the openings is markedly "
        + "more worn than around the beds. The only belongings by each bed "
        + "consist of a few changes of clothes and piles of thin sticks and "
        + "feathers.\n");

    add_item( ({"attic", "living space", "livingspace", "space", "room"}),
        "This is the second and highest floor of the house, as indicated by "
        + "the absence of any doors, stairs leading down, and a sloping "
        + "ceiling so steep that it could pass for walls.\n");
    add_item( ({"belongings", "possessions", "things", "stuff"}),
        "Not counting the beds and dressers, the only belongings out in the "
        + "open are clothes, sticks and feathers.\n");
    add_item( ({"bed", "beds"}), "The beds are narrow and covered with furs - "
        + "some but not all of them with a healthy tinge of green.\n");
    add_item( ({"dresser", "dressers", "small dresser", "small dressers"}),
        "The dressers are each made of varnished brown wood with three "
        + "narrow drawers.\n");
    add_item( ({"drawer", "drawers", "dresser drawers", "narrow drawers"}),
        "The drawers are narrow and made of the same unvarnished brown wood as "
        + "the dressers. All are closed");
    add_item( ({"clothes", "clothing", "changes", "change"}),
        "The clothes are handwoven mixtures of earth brown and tree green "
        + "(essentially, anything between yellow and blue). They are arranged "
        + "in neat bundles\n");
    add_item( ({"pile", "piles"}),
        "There is a pile of sticks and a pile of feathear by each bed.\n");
    add_item( ({"sticks", "thin sticks", "pile of sticks", "piles of sticks",
        "piles of thin sticks"}), "There are dozens of sticks in each pile, "
        + "all straight and stripped of leaves and twigs. You see a few that "
        + "have been sharpened into points at one end, and split in two at the "
        + "other.\n");
    add_item( ({"feathers", "pile of feathers", "piles of feathers"}),
        "There are a variety of feathers in each pile, the largest twice the "
        + "length of the smallest. Most are uniform in colour (a faint shade of "
        + "mint the most common), but a few have grey and emerald stripes or jade "
        + "dots on brown.\n");

    add_item( ({"floor", "ground", "worn floor", "lines", "paths"}),
        "The floor is all wooden planks, worn smooth along the six "
        + "paths between the openings in the walls and ceilings.\n");
    add_item( ({"axis", "ceiling", "ceilings", "wooden ceiling", "roof", "up"}),
        "The wooden ceiling above your head has the same slope as the roof of "
        + "the house, and is made of the same colourful wood. Its axis runs "
        + "east-west, and the two halves to either side slope steeply "
        + "downwards to the north and south, reaching the floor at a nearly "
        + "right angle. There are openings in the centres of both ceilings.\n");
    add_item( ({"wall", "walls", "east wall", "west wall"}),
        "Roughly triangular walls at the east and "
        + "west ends of the attic hold up the ceiling. Each is featureless "
        + "apart from an opening in its centre.\n");

    add_item( ({"opening", "hole", "window", "slit", "arrowslit",
        "arrow slit"}),
        "There are four openings you can examine - north, south, east and "
        + "west.\n");
    add_item( ({"openings", "holes", "windows", "slits", "arrowslits",
        "arrow slits"}),
        "There are cross-shaped openings in the west and east walls, and in "
        + "the steeply sloping ceilings to the north and south. They look "
        + "rather like arrowslits.\n");

    add_item( ({"north", "north opening", "north hole", "north window",
        "north slit", "north arrowslit", "north arrow slit"}),
        "@@view_room|north");
    add_item( ({"south", "south opening", "south hole", "south window",
        "south slit", "south arrowslit", "south arrow slit"}),
        "@@view_room|south");
    add_item( ({"east", "east opening", "east hole", "east window", "east slit",
            "east arrowslit", "east arrow slit"}), "@@view_room|east");
    add_item( ({"west", "west opening", "west hole", "west window", "west slit",
            "west arrowslit", "west arrow slit"}), "@@view_room|west");

    //Add views of three rooms plus a generic view of forest to south.
    //Describe feathers and sticks, add NPC activity - sharpening thereof.

    add_exit(ROOM_DIR + "jade_house", "down", "@@prevent_exit");

    set_no_exit_msg( ({ "north", "south", "east", "west" }), "The opening "
        + "is too small to climb through.\n");

    add_prop(OBJ_S_SEARCH_FUN, "stop_search");
    add_prop(OBJ_I_SEARCH_TIME, 1);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(PATH_HOME_PROP, "down");

    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Ensure that room's NPC exists, and ensure that there is an
 *      archer on duty (not necessarily the same NPC)
 */
void
reset_room()
{
    if (!objectp(native_archer)) //This room's native NPC does not exist
    {
        native_archer = query_archer();
        archer = native_archer;
        archer->set_family_index(5); //The native NPC can hold a quest role
    }
    if (!present(archer)) //Original NPC exists but is elsewhere
    {
        archer = query_archer();
    }
}


/*
 * Function name: init
 * Description  : Add actions when player arrives
 */
void
init()
{
    ::init();
    //add_action("search", "stop_search");
}

/*
 * Function name: filter_family
 * Description  : Filter function for identifying family members
 */
int
filter_family(object test_me)
{
    return wildmatch(NPC_DIR + "family*", file_name(test_me));
}


/*
 * Function name: request_arrow
 * Description  : Family members in the attic watch over the farm, shooting
 *          anyone who misbehaves. This function activates a combat bowshot,
 *          and is appropriate for delay and realism.
 * Arguments    : (object) The target
 *                (string) What the a family member outside is shouting
 */
varargs void
request_arrow(object target, string message = "")
{
    if(message != "")
    {
        tell_room(this_object(), "Outside, someone shouts: " + message);
    }

    object archer = query_archer();
    if (strlen(query_living_name(target)))
    {
        archer->command("shoot " + query_living_name(target) + " body");
    }
    else
    {
        archer->command("shoot " + lower_case(target->query_name()) + " body");
    }
}


/*
 * Function name: send_arrow
 * Description  : Family members in the attic act as overwatch for the farm,
 *          shooting anyone who misbehaves. This was the original fake shooting
 *          function, now replaced by a regular bow-shooting command.
 * Arguments    : (object) The room from which other family can provide backup
 *                (int) If someone requested the arrow, as opposed to the
 *          archer acting on own initiative.
 */
varargs void
send_arrow(object target, int requested = 0, int warning = 0)
{
    //Need to make sure archer has not wandered off or died.
    object archer = query_archer();

    int target_hp = target->query_hp();
    if (target_hp < 25 && !warning) //Don't auto-harm low-health player
    {
        if (requested)
        {
            string refuse_message;
            switch (random(5))
            {
                case 0:
                    refuse_message = "You can finish that one off yourself!";
                    break;
                case 1:
                    refuse_message = "You're doing fine on your own!";
                    break;
                case 2:
                    refuse_message = "A bit tired up here!";
                    break;
                case 3:
                    refuse_message = "Sorry, have to conserve arrows!";
                    break;
                default:
                    refuse_message = "My shift's up, not firing unless you're in "
                        + "trouble!";
            }
            archer->command("shout " + refuse_message);
            tell_room(environment(target), "A voice from the house shouts: "
                + refuse_message);
        }
        return;

    }

    archer->command("emote hurries over to an opening while nocking an arrow "
        + "with practiced ease.");
    archer->command("emote sights, pulls back the bowstring and fires in a "
        + "single movement.");

    object target_room = environment(target);
    string room;
    if (target_room->query_prop(ROOM_I_INSIDE) ||
        !sscanf(file_name(target_room), ROOM_DIR + "jade%s", room))
    {
        return; //Cannot hit the target, even if archer is clearly trying
    }

    object arrow = clone_object(WEP_DIR + "jade_arrow");
    arrow->set_broken(1); //Otherwise a source of infinite projectiles
    arrow->set_heap_size(1);

    if (warning) //Move arrow near player, notify
    {
        arrow->move(target_room);

        string target_message;
        switch (random(3))
        {
            case 0:
                target->catch_msg("An arrow thuds into the ground near you "
                    + "and snaps.\n");
                break;
            case 1:
                target->catch_msg("Something brushes across your skin. There "
                    + "is a broken arrow on the ground.\n");
                break;
            default:
                target->catch_msg("You hear a twang. An arrow whistles by your "
                    + "head.\n");
        }

        return;
    }

    //Tell player and others
    string target_message;
    switch (random(4))
    {
        case 1:
            target_message = "You feel a sharp pain. You are carrying one more "
                + "arrow than you remember.";
            break;
        case 2:
            target_message = "An arrow arcs out of the sky and hits you!";
            break;
        case 3:
            target_message = "You hear a 'twang' from the house and see a "
                + "broken arrow on the ground. The pain begins a moment later.";
            break;
        default:
            target_message = "Where did that arrow come from?";
    }
    target->catch_msg(target_message + "\n");
    tell_room(target_room, "An arrow flies through the air and hits "
        + QTNAME(target) + ".", ({target}));

    arrow->move(target); //Move arrow to player and harm

    if (target_hp < 500)
    {
        target->heal_hp(-min(25, target_hp/15));
        return;
    }

    if (target_hp < 5000)
    {
        target->heal_hp(-min(400, target_hp/10));
        return;
    }

    target->heal_hp(-min(1000, target_hp/8));
}


/*
 * Function name: prevent_exit
 * Description  : Checked when exiting. Prevents last family member (archer) in
 *          the room from leaving the post unattended.
 * Returns      : (int) 0 if exit allowed, 1 if forbidden.
 */
int
prevent_exit()
{
    if (!filter_family( this_player() )) {
        return 0;
    }

    return (sizeof(filter(all_inventory(), filter_family)) < 2);
}


/*
 * Function name: query_archer
 * Description  : Returns the family member currently acting as the attic
 *      archer; ensures that one is present and properly equipped.
 * Returns      : (object) The family member currently on duty.
 */
object
query_archer()
{
    object archer;
    object *archers = filter(all_inventory(), filter_family);
    if(sizeof(archers))
    {
        archer = archers[0];
    }
    else
    {
        //Generate new archer.
        archer = clone_object(NPC_DIR + "family.c");
        archer->move(this_object());
        tell_room(this_object(), QCTNAME(archer) + " arrives from below.\n");
    }

    //Equip if needed
    if(!present("bow", archer))
    {
        clone_object(WEP_DIR + "greenwood_bow.c")->move(archer);
        clone_object(WEP_DIR + "jade_bowstring.c")->move(archer);
        archer->command("string bow");
        archer->command("wield bow");
    }

    if(!present("arrow", archer))
    {
        object arrows = clone_object(WEP_DIR + "jade_arrow.c");
        arrows->set_heap_size(12);
        arrows->move(archer);
    }

    return archer;
}

/*
 * Function name: query_range_targets
 * Description  : Returns rooms into which one can fire a launch_weapon from here
 * Returns      : (object) The family member currently on duty.
 */
object
*query_range_targets(object archer)
{
    string near_source = "the upper floor of the two-storey house";
    string far_source = "somewhere around the two-storey house";
    return ({ find_object(ROOM_DIR + "jade_forest_e"), "",
        "in the forest to the east", " somewhere to the west",
        find_object(ROOM_DIR + "jade_forest_w"), "",
        "in the forest to the west", near_source,
        find_object(ROOM_DIR + "jade_forest_s"), "",
        "in the forest to the south", near_source,
        find_object(ROOM_DIR + "jade_yard"), "",
        "in the yard", near_source,
        find_object(ROOM_DIR + "jade_stand"), "",
        "by the fruit stand", near_source,
        find_object(ROOM_DIR + "jade_orchard_sw"), "",
        "in the southwestern part of the orchard", near_source,
        find_object(ROOM_DIR + "jade_forest_se"), "",
        "in the southeastern part of the orchard", near_source,
        find_object(ROOM_DIR + "jade_orchard_e"), "",
        "in the eastern part of the orchard", near_source,
        find_object(ROOM_DIR + "jade_orchard_mid"), "",
        "in the middle of the orchard", near_source,
        find_object(ROOM_DIR + "jade_orchard_n"), "",
        "north of the orchard", near_source,
        find_object(ROOM_DIR + "jade_orchard_w"), "",
        "in the western part of the orchard", near_source });
}

/*
 * Function name: view_room
 * Description	: Return the view out an opening, with NPC's in the
 *      corresponding rooms.
 * Arguments	: (string) Direction to the room - north, south, east, west
 * Returns		: (string) Overhead description with NPC's
 */
void view_room(string direction)
{
    string description = "Through the opening to the " + direction
        + ", you see ";
    object *room_contents;
    switch (direction) {
        case "north":
            room_contents =
                all_inventory(find_object(ROOM_DIR + "jade_orchard_w"))
                + all_inventory(find_object(ROOM_DIR + "jade_orchard_mid"))
                + all_inventory(find_object(ROOM_DIR + "jade_orchard_n"));
            description += "an orchard full of fruit trees. Near the house "
                + "lies a pile of gathered fruits. Beyond the trees to the "
                + "north runs a fence, surrounded by a cleared area "
                + "and the trees of the Jade Forest. ";
            break;
        case "south":
            room_contents = all_inventory(find_object(ROOM_DIR
                + "jade_forest_s"));
            description += "burnt and newly planted "
                + "fruit trees below, and past them, the sturdy wooden fence. "
                + "Between the fence and the trees of the Jade Forest is a "
                + "wide strip of scorched earth. ";
            break;
        case "east":
            room_contents =
                all_inventory(find_object(ROOM_DIR + "jade_orchard_sw"))
                + all_inventory(find_object(ROOM_DIR + "jade_orchard_se"))
                + all_inventory(find_object(ROOM_DIR + "jade_orchard_e"));
            description += "an orchard full of fruit trees and an outhouse "
                + "beyond them. Farther to the south is a tall fence, which "
                + "extends from the furthest that you can see to the right, "
                + "turns north past the outhouse, and continues that way as "
                + "far as you can see to the left. Beyond it are a cleared "
                + "area and the Jade Forest. ";
            break;
        case "west":
        default:
            room_contents =
                all_inventory(find_object(ROOM_DIR + "jade_yard"))
                + all_inventory(find_object(ROOM_DIR + "jade_stand"))
                + all_inventory(find_object(ROOM_DIR + "jade_forest_w"));
            description += "a yard surrounded by an imposing wooden fence. "
                + "In the northern part of the yard is a large pile of fruits "
                + "by a stand. A path leads west, through the fence and the "
                + "empty area around it and into the forest. ";
            break;
    }
    if (sizeof(room_contents))
    {
        string living_list = COMPOSITE_LIVE(room_contents);
        if(living_list != "someone")
        {
            description += "You see movement in the area:\n" + living_list;
        }
    }

    return description + "\n";
}

/*
 * Function name: stop_search
 * Description	: Archer on duty prevents player from searching private
 *      possessions
 */
string
stop_search()
{
    object searcher = this_player();
    object archer = query_archer();
    searcher->catch_msg(archer->query_The_name(searcher) + " stares at you while "
        + "reaching for an arrow. You abandon your search prematurely.\n");
    tell_room(this_object(), QCTNAME(archer) + " stares at " +  QTNAME(searcher)
        + " while reaching for an arrow. " +  QTNAME(searcher)
        + " stops searching.\n", ({ searcher }) );
    return 0;
}
