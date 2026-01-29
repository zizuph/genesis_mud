/* An creature horse. created by Gus and modified by Hamurabbi*/

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "/sys/macros.h"
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LHOOF 1
#define A_RHOOF 2
#define A_KICK  3

#define H_HEAD    0
#define H_BODY    1
#define H_F_L_LEG 2
#define H_F_R_LEG 3
#define H_B_L_LEG 4
#define H_B_R_LEG 5

create_creature()
{
 if (!IS_CLONE) 
        return;

    set_living_name("mearas");
    set_name(({"rechelaid","wildhorse","wild horse","horse","mearas"})); 
    set_race_name("horse");
    set_short("mearas");
    set_pshort("mearas");
    set_adj("wild");
    set_long("This is one of the wild horses of Rohan. The horse is also\n"
           + "called Mearas. This one is very wild, therefore unmountable.\n"
           + "\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 40, 40, 35, 34, 7, 45 }));

    set_hp(5000);
    set_alignment(300 + random(100));
    set_gender(1);

    set_skill(SS_DEFENCE, 70);
    set_skill(SS_ACROBAT, 32);
    set_skill(SS_PARRY, 65);

    set_attack_unarmed(A_BITE,  10, 20, W_IMPALE|W_BLUDGEON, 30, "muzzle");
    set_attack_unarmed(A_LHOOF, 10, 15, W_BLUDGEON,  15, "left hoof");
    set_attack_unarmed(A_RHOOF, 10, 15, W_BLUDGEON,  15, "right hoof");
    set_attack_unarmed(A_KICK, 10, 20, W_BLUDGEON,  40, "hindquarters");
   
    set_hitloc_unarmed(H_HEAD, ({ 8, 8, 8, 8 }), 15, "head");
    set_hitloc_unarmed(H_BODY, ({ 19, 19, 19, 19 }), 45, "body");
    set_hitloc_unarmed(H_F_L_LEG, ({ 15, 15, 15, 15 }), 10, "left front leg");
    set_hitloc_unarmed(H_F_R_LEG, ({ 15, 15, 15, 15 }), 10, "right front leg");
    set_hitloc_unarmed(H_B_L_LEG, ({ 15, 15, 15, 15 }), 10, "left back leg");
    set_hitloc_unarmed(H_B_R_LEG, ({ 15, 15, 15, 15 }), 10, "right back leg");


}

init_living()
{
  ::init_living();
  add_action("try_mount","mount");
}

try_mount(string str)
{
  if(!str)
  {
    NF("Mount what?\n");
    return 0;
  }

  if(str == "horse" || str == "mearas")
  {
    write("You try to mount the wild mearas.\n");
  say(QCTNAME(this_player()) + " tries to mount the wild mearas.\n");
    write("But the mearas jumps and throws you on the ground.\n");
  say("But the mearas shies and throws " + QTNAME(this_player()) + " on the ground.\n");
    this_player()->heal_hp(-20);
    write("Ouch, that hurt!\n");
    return 1;
  }
  NF("Mount what?\n");
  return 0;
}

/* solemnian prestige */
query_knight_prestige() {return (-8);}
