/*
   Wayreth.

   norm_skills.c
   -------------

   Coded ........: 01/97
   By ...........: Kentari

   Latest update : 07/97
   By ...........: Kentari

*/

#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>

inherit "/lib/skill_raise";
inherit TOWERROOM;

/*
 * Global variables
 */
#define NPC "/d/Krynn/wayreth/npc/"
object gTrainer;


/*
 * Prototypes
 */
public void
set_up_skills();


public void
reset_tower_room()
{
   if (!gTrainer)
    {
        gTrainer = clone_object(NPC + "staffmaster.c");
	gTrainer->move(TO);
    }
   return;
}


void
create_tower_room()
{
   set_short("Training room");
   AI(({"east","east wall","rack","staffs","padded staffs"}),
	"The rack along this wall holds padded practice staffs of " +
	"differing lengths and weights. Hopefully the trainer will " +
	"teach a Wizard how to use them without too many bruises.\n");
   AI(({"west","west wall","mirror"}),
	"This mirror aids in improving combat skills by showing the " +
	"practitioner where their form and movements are in error.\n");
   AI(({"floor","mattress","soft mattress","thin mattress"}),
	"Helping to cushion the fall of someone being trained, the " +
	"mattress guards against serious injury, yet does surprisingly " +
	"little for the aches and pains of most training sessions.\n");
   set_long("This is the training room for non-magical skills in the " +
            "Tower of High Sorcery. Here can be learned the mundane arts, " +
            "those which you may depend on to augment your combative " + 
	    "skills as a whole, or to use should it ever become hazardous " +
	    "to proclaim yourself Magi. Along the east wall is a rack " +
	    "containing what looks like ordinary staffs, with the " +
	    "exception that these are padded, the west wall is covered " +
	    "in a mirror to help in practicing, and the floor, to the " +
	    "delight of all but the trainer, is covered with a thin, " +
	    "but soft, mattress.\n");

   gTrainer->move(TO);
   reset_tower_room();
   create_skill_raise();
   set_up_skills();

   add_exit(WTOWER + "training", "south", 0);
}


void
init()
{
    init_skill_raise();
    ::init();
}


int
member(object who)
{
   if((who->test_bit("Krynn", 3, 6)) || (who->test_bit("Krynn", 3, 7)))
      return 1;

   return 0;
}


void
set_up_skills()
{
    sk_add_train(SS_WEP_POLEARM,     "use a polearm",          0, 0, 30 );
    sk_add_train(SS_DEFENCE,         "use defence skills",     0, 0, 20 );
    sk_add_train(SS_LANGUAGE,        "understand languages",   0, 0, 50 );
    sk_add_train(SS_APPR_OBJ,        "appraise objects",       0, 0, 50 );
    sk_add_train(SS_APPR_VAL,        "appraise values",        0, 0, 30 );
    sk_add_train(SS_APPR_MON,        "appraise creatures",     0, 0, 50 );
    sk_add_train(SS_AWARENESS,       "notice fine details",    0, 0, 50 );
}  


int
sk_improve(string sk)
{
    return ::sk_improve(sk);
}


int
sk_query_max(int snum)
{
    int *skills_available_here;
    mixed skval;
    
    /* Added to adapt to the skill_decay function.            */
    /* If a skill isn't available here, this function should  */
    /* return 0.               Jeremiah, 95/07/09             */

    skills_available_here = sk_query_train();

    if(member_array(snum, skills_available_here) == -1)
        return 0;


    if (!mappingp(sk_default))
      return 0;


    skval = sk_trains[snum];

    if (sizeof(skval)>2)
      return skval[2];
    else
      return 0;
}


int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have to\n" +
                "seek knowledge elsewhere.\n");

    return 0;
}

