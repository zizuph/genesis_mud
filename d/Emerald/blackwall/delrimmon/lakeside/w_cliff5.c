/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_cliff5.c
 *
 *  A room containing an orc encampment beneath the cliffs of
 *  the Blackwall Mountains.
 *
 *  Copyright May 1997, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define NPC_FILE        "/d/Emerald/blackwall/delrimmon/npc/outdoor_orc"

/* prototypes */
public void    create_cliff_room();
public int     check_exit();
public void    reset_room();
public void    init();

// Global Variables
object *Npcs = allocate(4 + random(3));

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("west");

    set_extraline("Rubbish and filth are scattered along the ground here,"
      + " strewn carelessly among what appear to be large footprints. A"
      + " cave mouth is visible in the cliff face to the west.");

    add_item(({"cliffs","sheer cliffs","cliff","sheer cliff"}), BSN(
        "Along the brink of this western rim of the bowl surrounding the"
      + " lake of Del Rimmon stretches a wide tumbled flat of scored and"
      + " weathered rock, cut every now and again by deep notches in the"
      + " cliff face that slope steeply up to trench-like gullies high"
      + " above. The dark opening of a cave entrance is visible at the"
      + " base of the cliff here, heading in to the west."));

    add_item(({"rock","rock face","cleft","clefts","cliff face","face"}),
      BSN("The rock of these cliffs is rent and cracked by numerous"
      + " clefts and fissures. At the base of the rocky slope, a cave"
      + " entrance opens to the west."));
    add_item( ({"ashes"}), BSN(
        "The ashes in the campfire look to have been stomped upon"
      + " by many feet."));
    add_item( ({"bones", "bone", "flesh", "animal flesh"}), BSN(
        "The bones in the rubbish are testimony to the meals which"
      + " must have been eaten here recently."));
    add_item(({"ground"}), BSN(
        "The green covering which carpets the forested hillside"
      + " stops just yards short of the looming cliff face."
      + " Rubbish and filth litter the ground, and many deep"
      + " and twisted footprints score the earth."));
    add_item(({"refuse","rubbish","debris"}), BSN(
        "This area has the unmistakable appearance of having been"
      + " recently been used as a campsite for orcs. Bits of"
      + " charred wood and partially devoured animals litter"
      + " the ground here, and a clumsily fashioned ring of"
      + " stones marks what was most likely a campfire."));
    add_item(({"wood","bits of charred wood","charred wood",
              "bits of wood"}), BSN(
        "Charred wood is strewn all about the area, its soot"
      + " blackening the otherwise green grasses. It appears"
      + " as if a campfire might have been built, and then"
      + " kicked and stomped out by many feet."));
    add_item(({"filth","feces","bowel movements"}), BSN(
        "A closer inspection of the filth on the ground reveals"
      + " it to be, among other hideous things, the bowel"
      + " movements of orcs!"));
    add_item(({"animals","partially devoured animals"}), BSN(
        "While a few of the animal corpses appear to be birds,"
      + " the vast majority are recognizable as the black"
      + " squirrels which flourish in these parts."));
    add_item( ({"campfire"}), BSN(
        "A thin trail of smoke rises from charred pieces of wood"
      + " which look to have once been a burning campfire. A"
      + " clumsy circle of stones surrounds the ashes."));
    add_item( ({"circle", "stones", "circle of stones", "stone"}), BSN(
        "The stones surround a smoking pile of charred wood. They"
      + " are blackened and sooty from the ashes of the former fire."));
    add_item( ({"smoke", "trail", "thin trail",
                "thin trail of smoke"}), BSN(
        "A thin trail of smoke rises from an extinguished campfire"
      + " here and winds its way above the treetops."));
    add_item(({"cave","cave opening","opening","cave mouth","mouth",
               "cave entrance","entrance"}),
        BSN("The opening in the western cliff face is quite"
      + " narrow, and little to no light seems to make its"
      + " way in to illuminate what might be beyond."));
    add_item(({"grass","grasses","soot"}), BSN(
        "Soot from the charred pieces of wood has stained"
      + " the otherwise green grass in this place."));
    add_item(({"footprints","footprint","print","prints",
               "large print","large prints","large footprints",
               "large footprint"}), BSN(
        "Though ground and smeared beyond recognition in most"
      + " cases, these prints bear testimony to the activities"
      + " of orcs."));

    add_cmd_item( ({"ground"}), 
                  ({"search", "dig"}), BSN(
        "The ground here is scored by the marks of many deep"
      + " footprints. They are confusing for tracking purposes,"
      + " running this way and that and trampling one another"
      + " amidst the filth and refuse upon the ground."));

    add_cmd_item( ({"filth", "feces", "bowel movements"}),
                  ({"search", "dig"}), BSN(
        "It becomes very quickly apparent that this filth is"
      + " little more than the excretion from orcish bowels,"
      + " and you care to search no further!"));
    add_cmd_item( ({"rubbish", "debris", "refuse", "bits", "wood",
                    "bits of charred wood", "bits of wood",
                    "charred wood"}),
                  ({"search", "dig"}), BSN(
        "Searching through the debris in the area you find"
      + " many bones and pieces of animal flesh. There is little"
      + " else to speak of, save for the abominable filth which"
      + " abounds here."));
    add_cmd_item( ({"stones", "circle of stones", "campfire"}),
                  ({"search", "dig"}), BSN(
        "There is nothing in the campfire save for ashes."));

    add_exit(DELRIMMON_DIR + "lakeside/w_wood5b","east",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff1","northeast");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4b","southeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff4","south");
    add_exit(DELRIMMON_DIR + "lakeside/caves/entrance",
             "west", check_exit, 0, 1);

    set_no_exit_msg( ({ "southwest", "northwest", "north" }),
        "The cliffs rise to stop you in that direction.\n");

    reset_room();
} /* create_cliff_room */

/*
 * Function name:    check_exit
 * Description  :    if the orcs are in the room, they will not let
 *                   players they can see into the cave
 * Returns      :    0 -- the player gets through
 *                   1 -- the player is blocked
 */
public int
check_exit()
{
    object  block = present("_blackwall_orc", this_object());
    string  npc = block->query_nonmet_name();

    if (!objectp(block))
    {
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(block) || !CAN_SEE(block, TP))
    {
        return 0;
    }

    TP->catch_msg(BSN("The " +npc+ " steps in front of you,"
      + " saying: Where do you think you are going, "
      + TP->query_race_name() + "?"));
    say(QCTNAME(block) + " stops " + QCTNAME(TP) + " from going"
      + " northeast.\n", ({TP, block}));
    return 1;
} /* check_exit */

/*
 * Function name: reset_room
 * Description  : clones the npcs into the room at resets
 */
public void
reset_room()
{
    clone_npcs(Npcs, NPC_FILE, 0.0);
} /* reset_room */

/*
 * Function name: init
 * Description  : Add actions to the player.
 */
public void
init()
{
    ::init();

    add_action(em_climbing_hook, "climb");
} /* init */
