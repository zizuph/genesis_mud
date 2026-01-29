/*
   Wayreth.

   mage_skills.c
   -------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 01/97
   By ...........: Kentari

*/

#include "../local.h"
#include "../guild/local.h"
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>

inherit "/lib/skill_raise";
inherit TOWERROOM;
int gLocal = 0;

/*
 * Global variables
 */
#define NPC "/d/Krynn/wayreth/npc/"
object gTrainer;

mapping gBlack_sk_trains, gRed_sk_trains, gWhite_sk_trains, gGen_sk_trains;

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

   gTrainer->move(TO);
   reset_tower_room();
   create_skill_raise();
   set_up_skills();
   add_prop(ROOM_I_NO_ATTACK, 1);
   add_exit(WTOWER + "training", "north", 0);
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

/*  Trained in the room 2 n (/d/Krynn/wayreth/tower/norm_skills.c)
 *	NORM_SKILLS_:
 *  sk_add_train(SS_WEP_POLEARM,     "use a polearm",          0, 0, 30 );
 *  sk_add_train(SS_DEFENCE,         "use defence skills",     0, 0, 20 );
 *  sk_add_train(SS_LANGUAGE,        "understand languages",   0, 0, 50 );
 *  sk_add_train(SS_APPR_OBJ,        "appraise objects",       0, 0, 50 );
 *  sk_add_train(SS_APPR_VAL,        "appraise values",        0, 0, 30 );
 *  sk_add_train(SS_APPR_MON,        "appraise creatures",     0, 0, 50 );
 *  sk_add_train(SS_AWARENESS,       "notice fine details",    0, 0, 50 );
 *
 *  Not anymore. Teth, Feb 5 1997.
 */
 
    sk_add_train(SS_SPELLCRAFT,     "harness the lunar magics", 0, 0, 90);
    sk_add_train(SS_HERBALISM,         "know and use plants",   0, 0, 75);
    sk_add_train(SS_ALCHEMY,           "use alchemy",           0, 0, 50);
    sk_add_train(SS_FORM_DIVINATION,   "use divination spells", 0, 0, 80);
    gGen_sk_trains = sk_trains;
    sk_trains = ([]);
 
    sk_add_train(SS_FORM_ABJURATION,   "use abjuration spells",  0, 0, 90);
    sk_add_train(SS_FORM_CONJURATION,  "use conjuration spells", 0, 0, 55);
    sk_add_train(SS_FORM_ENCHANTMENT,  "use enchantment spells", 0, 0, 55);
    sk_add_train(SS_ELEMENT_FIRE, "harness the element of fire", 0, 0, 55);
    sk_add_train(SS_ELEMENT_AIR,  "harness the element of air",  0, 0, 60);
    sk_add_train(SS_ELEMENT_EARTH, "harness the element of earth", 0, 0, 90);
    gWhite_sk_trains = sk_trains;
    sk_trains = ([]);

    sk_add_train(SS_FORM_TRANSMUTATION, "use transmutation spells", 0, 0, 90);
    sk_add_train(SS_FORM_CONJURATION, "use conjuration spells",  0, 0, 70);
    sk_add_train(SS_FORM_ILLUSION,     "use illusion spells",    0, 0, 55);
    sk_add_train(SS_ELEMENT_FIRE, "harness the element of fire", 0, 0, 80);
    sk_add_train(SS_ELEMENT_AIR,  "harness the element of air",  0, 0, 55);
    sk_add_train(SS_ELEMENT_EARTH, "harness the element of earth", 0, 0, 55);
    gRed_sk_trains = sk_trains;
    sk_trains = ([]);

    sk_add_train(SS_FORM_ENCHANTMENT,  "use enchantment spells",   0, 0, 80);
    sk_add_train(SS_FORM_CONJURATION,  "use conjuration spells",   0, 0, 55);
    sk_add_train(SS_FORM_ILLUSION,     "use illusion spells",      0, 0, 45);
    sk_add_train(SS_ELEMENT_WATER, "harness the element of water", 0, 0, 35);
    sk_add_train(SS_ELEMENT_FIRE,  "harness the element of fire",  0, 0, 60);
    sk_add_train(SS_ELEMENT_AIR,   "harness the element of air",   0, 0, 40);
    sk_add_train(SS_ELEMENT_DEATH, "harness the element of death", 0, 0, 90);
    
    gBlack_sk_trains = sk_trains;
    sk_trains = ([]);
}

public mapping
query_train_skills(object player)
{
    mapping tmp = ([]);

    tmp += gGen_sk_trains;
    switch(ADMIN->query_member_order(RNAME(player)))
    {
        case TYPE_BLACK:
            tmp += gBlack_sk_trains;
            break;
        case TYPE_RED:
            tmp += gRed_sk_trains;
            break;
        case TYPE_WHITE:
            tmp += gWhite_sk_trains;
            break;
    }

    return tmp;
}

public int
sk_improve(string sk)
{
    object master;
    int result;

/*    if (!(master = present("_wohs_mage_trainer", TO)))
    {
        return NF("There is no one here to teach you.\n");
    }

    if (!IS_MEMBER(TP))
    {
        master->msg_not_member(TP);
        return 1;
    }
*/
    sk_trains = query_train_skills(TP);

    gLocal = 1;
    result = ::sk_improve(sk);
    gLocal = 0;

    return result;
}

public varargs int
sk_query_max(int snum, int silent)
{
    int *skills_available_here;
    int result, level, tmp;
    
    /* Added to adapt to the skill_decay function.            */
    /* If a skill isn't available here, this function should  */
    /* return 0.               Jeremiah, 95/07/09             */

    if (!gLocal)
        sk_trains = query_train_skills(TP);

    skills_available_here = sk_query_train();

    if (member_array(snum, skills_available_here) == -1)
        return 0;

    result = ::sk_query_max(snum, silent);
find_player("rastlin")->catch_msg(sprintf("%O %O %O %O %O\n", RNAME(TP), result, gLocal, snum, 0));

    if (result && gLocal)
    {
	  int t = TP->query_wohs_level() + 1;

        level = ADMIN->query_number_levels();
        result = ftoi(((itof(result) / itof(level)) * itof((t >= level ? level : t))));
    }
find_player("rastlin")->catch_msg(sprintf("%O\n", tmp));

    return result;
}

/*
 * Function name: sk_list
 * Description:   Someone wants a list of skills
 * Arguments:     steps - How many steps the player wants to raise
 * Returns:       1
 */
int
sk_list(int steps)
{
    int tmp;

    gLocal = 0;
    tmp = ::sk_list(steps);
    gLocal = 1;

    return tmp;    
}

int
sk_hook_improved_max(string skill)
{
    if (gLocal)
    {
        NF("You have to gain another level to be able to attain further " +
	   "knowledge about this skill.\n");
    }
    else
        NF("You cannot raise this skill any further here, you have to " +
           "seek knowledge elsewhere.\n");

    return 0;
}






