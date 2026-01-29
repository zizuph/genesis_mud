/*
   Wayreth.

   mage_skills.c
   -------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 03/97
   By ...........: Karath
   Reason........: Full training of alchemy/herbaism regardless of level

*/

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>

inherit "/lib/skill_raise";
inherit TOWERROOM;

mapping order_limits = ([
                         INITIATE : ([
                                      SS_SPELLCRAFT      : 90,
                                      SS_HERBALISM       : 75,
                                      SS_ALCHEMY         : 35,
                                      SS_FORM_DIVINATION : 80,
                                      ]),
                         WHITE : ([ 
                                   SS_FORM_ABJURATION    : 90,
                                   SS_FORM_CONJURATION   : 50,
                                   SS_FORM_ENCHANTMENT   : 50, 
                                   SS_ELEMENT_FIRE       : 40,
                                   SS_ELEMENT_AIR        : 60,
                                   SS_ELEMENT_EARTH      : 90,
                                   ]),
                         RED   : ([
                                   SS_FORM_TRANSMUTATION  : 90,
                                   SS_FORM_CONJURATION   : 70,
                                   SS_FORM_ILLUSION      : 55,
                                   SS_ELEMENT_FIRE       : 70,
                                   SS_ELEMENT_AIR        : 45,
                                   SS_ELEMENT_EARTH      : 50,
                                   ]),
                         BLACK : ([ 
                                   SS_FORM_ENCHANTMENT   : 70,
                                   SS_FORM_CONJURATION   : 50,
                                   SS_FORM_ILLUSION      : 45,
                                   SS_ELEMENT_WATER      : 35,
                                   SS_ELEMENT_FIRE       : 50,
                                   SS_ELEMENT_AIR        : 40,
                                   SS_ELEMENT_DEATH      : 90 
                         ]),
                         ]);

/*
 * Global variables
 */
object gTrainer;

/*
 * Prototypes
 */
void set_up_skills();

void
reset_tower_room()
{
   if (!gTrainer)
    {
        gTrainer = clone_object(NPC + "aide.c");
        gTrainer->move(TO);
    }
   return;
}


void
create_tower_room()
{
   set_short("Training room for mage skills");
   AI(({"shelves","shelf"}),
	"Holding almost all of the books in this room, the shelves " +
	"are made of some black material, possibly a wood or maybe " +
	"a metal.\n");
   AI(({"books","texts","volumes","books of power","magical books"}),
	"There are so many volumes of books that you don't know where " +
	"to begin looking. For some reason, you can't read the bindings " +
	"that are shown and are too cautious to touch an unknown book " +
	"that might be magical.\n");
   set_long("Shelves line the walls of this room, each completely " +
	    "filled with hundreds " +
	    "of magical books of power and texts aiding in the learning " +
	    "of the arcane arts. There are so many volumes that you feel " +
	    "it would be unwise to try and search for knowledge on your " +
	    "own, and an aide has been given the duty to help you in your " +
	    "studies.\n");


   create_skill_raise();
   set_up_skills();
   add_prop(ROOM_I_NO_ATTACK, 1);
   add_exit("training", "north", 0);
   
   reset_tower_room();
}


void
init()
{
    init_skill_raise();
    ::init();
}

void
set_up_skills()
{
    /* This training room is a bit special.
     *  
     * All trainable skills here should be listed with the max set to
     * the max it can be trained in any order.
     *
     * The actual max it can be trained to will be depend upon the 
     * order of the wizard and his level in the guild.
     * See sk_query_max below.
     */

    /* General Skills */
    sk_add_train(SS_SPELLCRAFT,     "harness the lunar magics", 0, 0, 90);
    sk_add_train(SS_HERBALISM,         "know and use plants",   0, 0, 75);
    sk_add_train(SS_ALCHEMY,           "use alchemy",           0, 0, 50);

    /* Magic Forms */
    sk_add_train(SS_FORM_DIVINATION,   "use divination spells", 0, 0, 90);
    sk_add_train(SS_FORM_ABJURATION,   "use abjuration spells",  0, 0, 90);
    sk_add_train(SS_FORM_ENCHANTMENT,  "use enchantment spells", 0, 0, 90);
    sk_add_train(SS_FORM_TRANSMUTATION, "use transmutation spells", 0, 0, 90);
    sk_add_train(SS_FORM_CONJURATION, "use conjuration spells",  0, 0, 90);
    sk_add_train(SS_FORM_ILLUSION,     "use illusion spells",    0, 0, 90);

    /* Magic elements */
    sk_add_train(SS_ELEMENT_FIRE, "harness the element of fire", 0, 0, 90);
    sk_add_train(SS_ELEMENT_AIR,  "harness the element of air",  0, 0, 90);
    sk_add_train(SS_ELEMENT_EARTH, "harness the element of earth", 0, 0, 90);
    sk_add_train(SS_ELEMENT_WATER, "harness the element of water", 0, 0, 90);
    sk_add_train(SS_ELEMENT_DEATH, "harness the element of death", 0, 0, 90);
}

public varargs int
sk_query_max(int snum, int silent)
{
    mapping limits;
    string type;

    if (!this_player())
        return ::sk_query_max(snum, silent);
    
    type = ADMIN->query_member_type(this_player());
    
    limits = order_limits[INITIATE] + order_limits[type];

    return limits[snum];

    /* Insert cool wiz level limiting stuff here */
}

int
sk_hook_improved_max(string skill)
{
    NF("You cannot raise this skill any further here, you have to " +
        "seek knowledge elsewhere.\n");
    return 0;
}
