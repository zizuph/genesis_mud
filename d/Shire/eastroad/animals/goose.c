inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/domove";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define W_BITE 0
#define W_FOOT 1
#define W_L_WING 2
#define W_R_WING 3


#define A_L_WING 0
#define A_R_WING 1


void
create_creature()
{
   if(!IS_CLONE)
      return;
   set_name("goose");
   set_race_name("goose");
   set_pname("geese");
   set_pshort("black geese");
   set_short("black goose");
   set_adj("black");
   set_long(
      "This is a rather large bird. It is black as the deepest hole, and "+
      "looks quite fat.\n");
   
   set_stats(({9,20,8,10,8,7 }));
   set_skill(SS_DEFENCE, 5);
   set_alignment(25 + random(100));
   
   set_random_move(15);
   set_restrain_path("/d/Shire/eastroad");
   set_hitloc_unarmed(A_BODY, 5, 5, "body");
   set_hitloc_unarmed(A_HEAD,0, 1,"head");
   set_hitloc_unarmed(A_L_WING,2, 3,"left wing");
   set_hitloc_unarmed(A_R_WING,2,3,"right wing");
   
   set_attack_unarmed(W_BITE,   5,5, W_IMPALE,25, "beak"); /*It is supposed to be the
   *thing the duck bites with
   *but dont remember its name.
   */
   set_attack_unarmed(W_L_WING, 2, 2, W_BLUDGEON, 25, "left wing");
   set_attack_unarmed(W_R_WING, 2, 2, W_BLUDGEON, 25, "right wing");
   set_attack_unarmed(W_FOOT, 4, 5, W_BLUDGEON, 25, "feet");//same here, dont remember
   //what name its feet has ;-)

	add_prop(CONT_I_WEIGHT, 10000); //11 Kg's
	add_prop(CONT_I_VOLUME, 700);   //7 Ltr's
	add_prop(NPC_I_NO_LOOKS, 1);

	set_act_time(5);
	add_act("emote flaps its wings absently.");
	add_act("emote honks loudly.");
	add_act("emote unfolds its wings, showing itself in all its pride.");
}

