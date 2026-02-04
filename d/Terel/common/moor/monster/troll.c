/*
 Lilith Dec 2021: updated clone path for sack
*/

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <ss_types.h>

/*
* Define some attack and hitloc id's (only for our own benefit)
*/
#define A_BITE 0
#define A_R_CLAW 1
#define A_L_CLAW 2

#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
   object sack;
   
   set_name("troll"); 
   set_race_name("troll");
   set_short("troll");
   set_long("A horrible flesh-eating creature. It has thick skin\n"
      +"of putrid gray-green and mottled black. Its mouth lined\n"
      +"with cruel teeth, its hands with dagger like claws.\n"
      +"Dirty and smelling of rot, its body covered with hides\n"
      +"and tattered clothing, its head draped by thick strands\n"
      +"of gray bestial hair. Its eyes black with yellow slits.\n");
   
   /* str, con, dex, int, wis, dis
   */
   set_stats(({ 40, 30, 75, 12, 12, 45}));
   set_hp(9000);
   
   set_skill(SS_DEFENCE, 50);
   set_random_move(60);
   set_aggressive(1);
   set_alignment(-135);
   
   set_attack_unarmed(A_BITE,   25, 36, W_IMPALE, 35, "bite");
   set_attack_unarmed(A_R_CLAW, 45, 30, W_SLASH, 60, "right claw");
   set_attack_unarmed(A_L_CLAW, 40, 30, W_SLASH, 55, "left claw");
   
   seteuid(getuid(this_object()));
   sack=clone_object(MOOR_DIR +"obj/sack");
   sack->move(this_object());
   
   set_hitloc_unarmed(H_HEAD, ({ 40, 40, 25}), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 35, 40, 35}), 80, "body");
}


