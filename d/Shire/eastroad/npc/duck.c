inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/domove";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define W_BITE 		0
#define W_FOOT 		1
#define W_L_WING 	2
#define W_R_WING	3

#define A_L_WING 	0
#define A_R_WING 	1
#define A_FOOT		2

void
create_creature()
{
	if(!IS_CLONE)
	return;
	set_name("duck");
	set_race_name("duck");
	set_adj("white");
	add_adj("spotted");
	set_gender(G_MALE);
	set_long(
		"This is a small white duck with black spots here and there.\n"+
		"He looks like he would fill your tummy right to the edge.\n");
	
   set_random_move(15);
   set_restrain_path("/d/Shire/eastroad");
	set_stats(({ 6, 8, 5, 10, 8, 7 })); /*Shouldnt be un-killable :)*/
	set_skill(SS_DEFENCE, 5);
	set_skill(SS_UNARM_COMBAT, 10);
   set_alignment(50 + random(43));
	
	set_hitloc_unarmed(A_BODY, 5, 5, "body");
	set_hitloc_unarmed(A_HEAD,0, 1, "head");		
	set_hitloc_unarmed(A_L_WING,2, 3, "left wing");
	set_hitloc_unarmed(A_R_WING,2, 3, "right wing");
	set_hitloc_unarmed(A_FOOT,3, 5, "feet");

	set_attack_unarmed(W_BITE, 5, 5, W_IMPALE, 25, "beak"); // It is supposed to be the
							        // thing the duck bites with
								// but dont remember its name
	set_attack_unarmed(W_L_WING, 2, 2, W_BLUDGEON, 25, "left wing");
	set_attack_unarmed(W_R_WING, 2, 2, W_BLUDGEON, 25, "right wing");
	set_attack_unarmed(W_FOOT, 4, 5, W_BLUDGEON, 25, "feet"); //same here, dont remember
																	//what name its feet has ;-)

	add_prop(CONT_I_WEIGHT, 2000);
	add_prop(CONT_I_VOLUME, 300);
	add_prop(NPC_I_NO_LOOKS, 1);

	set_act_time(5);
	add_act("emote flaps its wings absently.");
	add_act("emote goes 'quack quack'.");
	add_act(({"emote flies up in the air...suddenly some strange smelly piece\n"+
			"of something lands on your shoulder..... \nPhew..what a smell!", 
			  "emote lands again."}));
	set_cact_time(6);
	add_cact("emote flaps helplessly with its wings.");
	add_cact("emote quacks loudly, as if calling for help...");
}

	
	
