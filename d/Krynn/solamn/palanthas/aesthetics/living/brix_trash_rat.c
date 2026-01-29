/*
 * One of many rats foraging through the trash around
 * Jems court in the aesthetics quarter of Palanthas.
 * The rats here are vicious and intelligent.
 *
 * Mortis 06.2006
 *
 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#define A_BITE		0
#define A_LCLAW		1
#define A_RCLAW		2

#define H_HEAD		0
#define H_BODY		1

inherit C_FILE
inherit "/std/act/attack";
inherit "/std/act/action";

void
create_creature() 
{
	set_name("rat");
	set_adj("black-whiskered");
	add_adj(({"hairy", "black", "whiskered", "brown"}));
    set_short("black-whiskered brown rat");
    set_long("With bristly, black whiskers and slick, dark brown fur, this "
	+ "sleek muscled rat darts its head about, its black eyes searching "
	+ "voraciously for something with a vicious intelligence.  Its hairless "
	+ "tail is long and whips and curls around with an agile control "
	+ "uncommon in these vermin.\n");
 	set_race_name("rat"); 
   
    set_aggressive(1);

    default_config_mobile(15);

    set_gender(G_NEUTER);
    set_stats((({ 20, 35, 15, 50, 75, 65})), 5);

    //				  Wep_type, to_hit, pen, Dam_type, %usage, attack_desc
    set_attack_unarmed(A_BITE,      15,  13, W_IMPALE,   80,   "needle-sharp "
	+ "teeth");
    set_attack_unarmed(A_LCLAW,     11,   7, W_SLASH,    10,   "clawed left "
	+ "paw");
    set_attack_unarmed(A_RCLAW,     11,   7, W_SLASH,    10,   "clawed right "
	+ "paw");

    //				  Hit_loc, AC (im, sl, bl, ma), %hit, hit_desc
    set_hitloc_unarmed(H_HEAD, ({  12, 12,  5,  5 }), 25, "darting head");
    set_hitloc_unarmed(H_BODY, ({  18, 20, 15,  5 }), 75, "sleek body");

	set_alignment(0);
	set_knight_prestige(1);
	
	set_act_time(40);
	add_act("emote darts its black-eyed head about voraciously.");
	add_act("emote darts through the trash in swift spurts, its long "
	+ "hairless tail curling around with an oddly agile whipping motion.");
	add_act("emote finds a " + one_of_list(({"worm", "beetle", "winged bug",
	"tiny mouse", "centipede", "small lizard"})) + " in the trash and "
	+ "shreds it with its needle-sharp teeth before swallowing it "
	+ "voraciously.");

	set_cact_time(30);
	add_cact("emote clicks its needle-sharp teeth while growling from "
	+ "a low rumble to a loud squeak.");
	add_cact("emote whirrs growlingly as it clicks its need-sharp teeth "
	+ "together repeatedly.");
	add_cact("emote hisses spittingly as it spreads wide its black whiskers "
	+ "and bares its needle-sharp teeth aggressively.");

	add_prop(OBJ_I_NO_INS, 1);
}
