/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 * Lilith Oct 2014: Buffed size and added some fire agates for loot.
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

public void
create_creature(void)
{
	
	setuid();
    seteuid(getuid());
	
    set_name("lizard");
    set_race_name("lizard");
    set_short("shadowy lizard");
    set_adj("shadowy");
    set_long("A shadow beast, in the form of a black reptile. It " +
	"seems to be a creature spawned of demons. Though it seems " +
	"of such nature, it is real enough. It has sharp fangs and " +
	"looks horribly vicious and malevolent.\n");

    set_gender(G_NEUTER);
    set_alignment(0);
	add_prop(NPC_I_NO_LOOKS,1);
    /*
     * str, con, dex, int, wis, dis
     */
    set_stats(({ 100, 136, 154, 5, 5, 30 }));
    set_skill(SS_ACROBAT,      50); 
    set_skill(SS_DEFENCE,      75);
	set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_UNARM_COMBAT, 75);

    set_attack_unarmed(A_BITE, 50, 40, W_IMPALE, 100, "fangs");

    set_hitloc_unarmed(H_HEAD, 25, 20, "head");
    set_hitloc_unarmed(H_BODY, 60, 60, "abdomen");
    set_hitloc_unarmed(H_TAIL, 30, 20, "tail");
	
	clone_object("/d/Genesis/gems/obj/agate_fire")->move(this_object());
	clone_object("/d/Genesis/gems/obj/agate_fire")->move(this_object());
}
