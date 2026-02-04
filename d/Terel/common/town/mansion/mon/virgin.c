/*

    September 1992


   This is a Virgin.  She is the subject of the Sacrifice Quest
   See ~Terel/open/BITS, group 0 bit 12 for more info.

   Coded by Vader
   Modified by Deagol, 2004, set_living_name() has been removed 
*/
inherit "/std/monster";
inherit "/std/act/trigaction";
#include "/sys/ss_types.h"
#include "/sys/macros.h"

/* Global variables for quest specific code */
/* as well as the following code            */


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;

   set_name("virgin");
   add_name("girl");
/*   set_living_name("eve"); */
   set_race_name("human");
   set_short("beautiful wide-eyed girl");
   set_adj("beautiful");
   add_adj("wide-eyed");
   set_long(break_string(
    "A young girl, barely sixteen years of age.  She has been " +
    "chained to the wall here.  Her clothing is torn and drenched " +
    "with dirt and sweat.  Her hair is tangled, but still falls " +
    "across her shoulders in an attractive way.  She looks like " +
    "she could use some help.\n", 70));

   set_gender(1);


 /*  Lets set her stats to a realistic level for a gal with enough 
     strength to save herself for the right man                   */
   default_config_npc(35);


    set_all_hitloc_unarmed(15);

   set_chat_time(1);
   add_chat("Help me!");
   add_chat("I'm too young to die, please get me out of here...");
   add_chat("When that evil priest returns with the key, I'm dead!\n");
}
