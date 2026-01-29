// Mascarvin
// creator(s): Lilith
// last update: Created May 2021
// purpose:   Mascarvin, Goddess of Death, Collector of Souls.
// note:      She visits those questors who have completed the 
//            Mascarvin's Maze Quest and gives them the Diadem
//            of Life and Death.
//
// bug(s):
// to-do:    1) Considering making it so that if someone attacks her
//              they just die and are added to the infidel list.
//              I mean, what idiot tries to kill the Goddess of Death???


inherit "/d/Avenir/inherit/monster";
#include "defs.h"
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

void
create_monster()
{
    ::create_monster();

    set_name("mascarvin");
    set_adj(({"tenebrous", "ethereal"}));
    set_title("the Goddess of Death and Rebirth, Little Mother of All");
    set_race_name("goddess");
    set_gender(G_FEMALE);

    set_long("Shadows play about this towering, cloaked figure. "
	    +"It is She who collects the souls of dying "
		+"Sybarites and nurtures them back to the "
		+"point where they are ready to be reborn "
		+"and serve the Gods of Sybarus once more. "
		+"You feel nourished and revived in her "
		+"presence.\n");

    set_stats(({200,200,200,200,200,200}));

    add_prop(CONT_I_HEIGHT, 500);
    add_prop(CONT_I_WEIGHT, 56000);

    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_alignment(0);
}

/*
void
arm_me()
{
    seteuid(geteuid(this_object()));

    command("wear all");
    command("wield all");
}
*/

string
race_sound()
{
   return "speaks";
}
