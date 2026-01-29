/*
 *  Stables of Imladris
 *  Finwe, January 1998
 *
 * ChangeLog:
 * Palmer 03/22/2004 - Removed "black and white" as color opton.
 *                   - Added "Use <idea> to suggest horse names" to plaque.
 *
 * Palmer 03/23/2004 - Removed unused MAX_HORSES, object *horses
 *                   - No fighting here. Stable master has code to remove
 *                     horses when players leave guild
 *                   - Added this room to /d/Shire/domain_link.c in case player
 *                     is removed from Noldor immediately after reboot.
 *
 */

inherit "/d/Shire/std/room.c";

#include "local.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>


public void
create_shire_room()
{
    object stable_master;

    set_short("Stables of Imladris");
    set_long("The stables of Imladris. The stables are large, " +
        "housing many fine steeds of the elves. Many stalls " +
        "fill one end of the building, some with horses and " +
        "others empty. Straw covers the floor, with bales of hay " +
        "stacked up against one wall. There is a door " +
        "that leads to a tack shop and outside to the house. " +
        "Hanging on the wall is a large poster and a plaque.\n");

    add_item(({"hay", "bales of hay", "alfalfa"}),
        "It is freshly cut and stacked up against the walls. " +
        "It is excellent food for the horses.\n");
    add_item(({"horses", "steeds"}),
        "The horses in the stalls are tall magnificent " +
        "creatures, They are muscular and by far the best you " +
        "have ever seen. The steeds are different colors, with " +
        "white being the common color.\n");
    add_item("ceiling",
        "Large carved beams hold up the roof high above you.\n");
    add_item(({"down", "straw", "floor", "ground"}),
        "Fresh straw cover the ground. It is golden colored " +
        "and smells clean like it was freshly cut.\n");
    add_item(({"stalls", "stall"}),
        "The stalls are a good size, sturdy and made of solid " +
        "wood, and able to house a large " +
        "horse comfortably. Within each stall you see troughs " +
        "for food and water. Some stalls are empty " +
        "while others are occupied.\n");
    add_item(({"troughs", "trough"}),
        "you see troughs in the stalls for food and water.\n");
    add_item(({"water trough", "water troughs", "metal water troughs",
            "metal water trough"}),
        "The troughs are made of metal and hold water for the " +
        "thirsty horses.\n");
    add_item(({"food trough", "food troughs", "wooden food troughs",
            "wooden food trough"}),
        "The food troughs are made of wood and have some hay, alfalfa" +
        "and grain in them for the hungry horses.\n");
    add_item(({"grain", "oats", "sweet molasses", "molasses",
            "corn", "feed"}),
        "You see a mixture of oats, corn, sweet molasses, and " +
        "other good foods in the food troughs.\n");
    add_item(({"walls", "wall"}),
        "The walls are strong and durable, made of planed wood. " +
        "Some shelves and racks are on the walls.\n");
    add_item("racks",
        "The racks stretch across a long wall. On them, are " +
        "various saddles, bridles, halters, and other implements " +
        "of horsmanship.\n");
    add_item("shelves",
        "You see some combs, brushes, bells, blankets, and " +
        "other items stacked on the shelves.\n");
    add_item(({"comb", "combs"}),
        "The combs are made of metal and have teeth to remove " +
        "tangles and debris from the animal's hair.\n");
    add_item(({"brushes", "brush"}),
        "The brush is made of soft, smooth bristles of pure dark " +
        "horsehair blend and is the best finishing brush you've seen. " +
        "The brushes are small and fit in your hand comfortably.\n");
    add_item(({"bells", "silver bells"}),
        "All kinds and shapes of bells are on the shelves. They " +
        "are silver and are used to decorate the saddles of the " +
        "horses.\n");
    add_item(({"blankets", "horses blankets"}),
        "The blankets are wool and in many bright colors. They " +
        "are used to cover the horses and for riding.\n");
    add_item(({"saddles", "saddle"}),
        "The saddles are strongly built to withstand and " +
        "protect the rider from extended travel. The saddles " +
        "have a flatter seat allowing greater freedom while " +
        "riding. Silver bells decorate some saddles.\n");
    add_item(({"bridle", "bridles"}),
        "These harnesses fit over the horses head and are used " +
        "to guide or restrain the animal. They consist of a " +
        "'U'-shaped metal piece which fits in the mouth and " +
        "leather straps to secure it to the horse.\n");
    add_item(({"halters", "halter"}),
        "These devices are made of leather straps and fit over " +
        "the horses head and neck.\n");

    add_prop(ROOM_M_NO_TELEPORT_TO,
        "A great Elven-power prevents you from teleporting there.\n");

    // No fighting here. Stable master has code to remove horses when players leave guild
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    
    stable_master = clone_object("/d/Shire/rivendell/steeds/stable_master");
    stable_master->move(this_object());
    
    room_add_object("/d/Shire/rivendell/obj/stable_book");

    reset_shire_room();

    add_cmd_item(({"poster", "parchment", "white parchment", "large poster"}), 
            "read", "@@read_poster@@");
    add_cmd_item(({"plaque", "piece of steel", "piece of polished steel", 
            "polished steel", "steel"}), "read", "@@read_plaque@@");
    add_item(({"poster", "large poster", "parchment", "white parchment"}), 
        "The poster is made of white parchment. Instructions are written in " +
        "fine elvish letters across its surface.\n");
    add_item(({"elvish letters", "letters", "fine elvish letters"}),
        "The letters were written by a skilled elf. The writing is " +
        "exquisite and flows freely, as is the case of fine Sindarin " +
        "characters.\n");
    add_item(({"plaque", "piece of steel", "piece of polished steel", 
            "polished steel", "steel"}),
        "The plaque is made from a polished piece of steel. Inscribed " +
        "on the surface is some information written in fine elvish letters.\n");   
    

    add_exit(VALLEY_DIR + "n_path01", "east");
    add_exit(VALLEY_DIR + "tack_shop","west");


}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());
}


string
read_poster()
{
    return "\n"+
    "\t --------------------------------------------------------------- \n" +
    "\t| o                                                           o |\n" +
    "\t|            T H E   I M L A D R I S  S T A B L E S             |\n" +
    "\t|     -----------------------------------------------------     |\n" +
    "\t|                                                               |\n" +
    "\t|  To choose your horse, I need to have two adjectives,         |\n" +
    "\t|  the gender, and the name you wish to call your horse.        |\n" +
    "\t|                                                               |\n" +
    "\t|  Male and female horses are available.                        |\n" +
    "\t|                                                               |\n" +
    "\t|  For a list of adjectives and names, please ask me.           |\n" +
    "\t|                                                               |\n" +
    "\t|  When you have decided:                                       |\n" +
    "\t|                                                               |\n" +
    "\t|  choose <adj1> <adj2> <gender> horse named <name>             |\n" +
    "\t|                                                               |\n" +
    "\t|  Example:                                                     |\n" +
    "\t|  choose glimmering silvery female horse named Bingil          |\n" +
    "\t|                                                               |\n" +
    "\t|                                                               |\n" +
    "\t|  Be sure to read the plaque for a list of adjectives and      |\n" +
    "\t|  horse names, and read the book for full details about        |\n" +
    "\t|  how to use them.                                             |\n" +
    "\t|                                                               |\n" +
    "\t|                                    Ridlin, Stable Master      |\n" +
    "\t| o                                                           o |\n" +
    "\t --------------------------------------------------------------- \n";


}

string
read_plaque()
{
    return "\n"+
    "\t ___                                                            ___\n" +
    "\t[___]__________________________________________________________[___]\n" +  
    "\t|   |                                                          |   |\n" +
    "\t|   |   Listed below are the adjectives and colors you may use |   |\n" +
    "\t|   |   when getting your horse. You must choose one item from |   |\n" +
    "\t|   |   each category in order for him to trust you with one   |   |\n" +
    "\t|   |   of his horses.                                         |   |\n" +
    "\t|   |                                                          |   |\n" +
    "\t|   |   If your horse is not to your liking, you may trade it  |   |\n" +
    "\t|   |   in when you <pay fee>. However, Ridlin will charge you |   |\n" +
    "\t|   |   100 platinum coins to clean it, stable it, and get the |   |\n" +
    "\t|   |   horse ready for its next rider. Therefore, be sure     |   |\n" +
    "\t|   |   your horse is to your liking before you finalize your  |   |\n" +
    "\t|   |   choice with the stablemaster.                          |   |\n" +
    "\t|   |                                                          |   |\n" +
    "\t|   |   Adjective 1 (style)                                    |   |\n" +
    "\t|   |   -----------------------------------------------------  |   |\n" +
    "\t|   |   Confident          High-Spirited        Rogue          |   |\n" +
    "\t|   |   Muscular           Stately              Wild           |   |\n" +
    "\t|   |   Athletic           Painted              Regal          |   |\n" +
    "\t|   |   Shimmering         Glimmering           Majestic       |   |\n" +
    "\t|   |   Proud              Sleek                Swift          |   |\n" +
    "\t|   |   Spotted            Speckled                            |   |\n" +
    "\t|   |                                                          |   |\n" +
    "\t|   |   Adjective 2 (color)                                    |   |\n" +
    "\t|   |   ----------------------------------------------------   |   |\n" +
    "\t|   |   Silvery            Cream                Chestnut       |   |\n" +
    "\t|   |   White              Dun                  Champagne      |   |\n" +
    "\t|   |   Grey               Bay                  Palomino       |   |\n" +
    "\t|   |                                                          |   |\n" +
    "\t|   |   Horse Names                                            |   |\n" +
    "\t|   |   ----------------------------------------------------   |   |\n" +
    "\t|   |   You may list available names, and their meanings,      |   |\n" +
    "\t|   |   when you <ask ridlin names>.                           |   |\n" +
    "\t|   |                                                          |   |\n" +  
    "\t|   |   If you have a suggestion for a horse name, use <idea>. |   |\n" +  
    "\t|___|__________________________________________________________|___|\n" +
    "\t[___]                                                          [___]\n";
    
}
