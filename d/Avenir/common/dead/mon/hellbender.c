// hellbender    /d/Avenir/common/dead/mon/hellbender.c
// Creator:      Lilith Aug 2021
// purpose:      Creepy critter for the Catacombs.
// note:         Hellbenders are RL salamanders
// updates:  Lilith Mar 2022: fixed runtime error due to
//               missing hitlocs  

inherit "/d/Avenir/inherit/creature";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/deities.h"

/* These define what it will attack with */
#define A_LFORE  TS_LHAND
#define A_RFORE  TS_RHAND
#define A_RHLEG  TS_RFOOT
#define A_LHLEG  TS_LFOOT
#define A_TAIL   TS_HEAD
#define A_LIP    TS_HEAD

/* These define what body parts will be hit in fights */
#define H_HEAD    TS_HEAD
#define H_ABDOM   TS_TORSO
#define H_RMID    TS_RARM  
#define H_LMID    TS_LARM
#define H_RHLEG   TS_RFOOT 
#define H_LHLEG   TS_LFOOT

void
create_creature()
{
    set_race_name("hellbender");
    set_name("hellbender");
	add_name(({"hellbender","_avenir_catacombs_salamander", "ghost salamander"}));
    set_adj(({"pale", "ghost", "ghostly", "white", "albino", "hellbender"}));
    set_short("ghost hellbender");
    set_long("This ghost hellbender is a long white salamander that lives "
	    +"entirely in the dark. It is about the length of your arm and as "
		+"thick around as your wrist. Its wrinkled skin is loose and "
		+"icy-cold to the touch, and its small eyes glow a very bright red. "
		+"It has five toes on each foot, short "
		+"legs, and a flattened body shape. Its head is flat and rounded, "
        +"with a wide mouth and rather sharp, pointed teeth. When it "
		+"moves in water, the flow of its skin around its body "
		+"can be both hypnotic and terrifying.\n"
		+"This creature thrives in the pools and misty dampness of the "
		+"catacombs.\n");
    set_alignment(0);
    UNIVERSAL_OFFERING;
//	MASCARVIN_OFFERING;
//  Sets the stats for us, its a simple critter
    default_config_creature(10 + random(10));
    remove_prop(OBJ_M_NO_GET);
    add_prop(CONT_I_VOLUME, 600);
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(LIVE_I_NEVERKNOWN, 1); 
	add_prop(NPC_I_NO_LOOKS, 1);
	add_prop(OBJ_I_RES_MAGIC, 10);
	add_prop(OBJ_I_RES_FIRE, 10);	
	add_prop(OBJ_I_RES_COLD, 10);
	
    if (random(3) > 1)
	  set_gender(G_FEMALE);
    else
	  set_gender(G_MALE);
  
     /*               'weapon', hit, pen, damage type, %use, desc  */
    set_attack_unarmed(A_LFORE, 80, 20, W_SLASH,    20, "claws on its left foreleg");
    set_attack_unarmed(A_RFORE, 80, 20, W_SLASH,    20, "claws on its right foreleg");
    set_attack_unarmed(A_RHLEG, 80, 20, W_BLUDGEON, 10, "right hind leg");
    set_attack_unarmed(A_LHLEG, 80, 20, W_BLUDGEON, 10, "left hind leg");  
    set_attack_unarmed(A_TAIL,  80, 20, W_BLUDGEON, 15, "thick tail");
    set_attack_unarmed(A_LIP,   80, 20, W_IMPALE,    25, "needle-like teeth");    

    /*                  where,     ac,  %hit,  desc  */
    set_hitloc_unarmed(H_HEAD,  ({ 15 }), 35, "flat head");
    set_hitloc_unarmed(H_ABDOM, ({ 5 }),   5, "soft underbelly");
    set_hitloc_unarmed(H_RMID,  ({ 20 }), 15, "right foreleg");
    set_hitloc_unarmed(H_LMID,  ({ 20 }), 15, "left foreleg");
    set_hitloc_unarmed(H_RHLEG, ({ 20 }), 15, "right hind leg");
    set_hitloc_unarmed(H_LHLEG, ({ 20 }), 15, "left hind leg");

}
