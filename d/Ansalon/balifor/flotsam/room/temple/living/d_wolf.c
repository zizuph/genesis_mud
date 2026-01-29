/*
Pax Tharkas

Borrowed from : A minor rat. Used in human starting location.
Styles, 920317.

-----

Copied an altered : 95/03/25
By ...............: Jeremiah

Copied an altered : 96/03/15
By ...............: Arman


*/

#include "/d/Ansalon/common/defs.h"
inherit AC_FILE
inherit "/std/combat/unarmed";
inherit "/std/act/attack";       /* Allows rat to act  */
inherit "/std/act/domove";       /* Allows rat to move */
inherit "/std/act/chat";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

void
create_creature() 
{
   
   if (!IS_CLONE)
      return;
   set_name("dreadwolf");
   add_name("wolf");
   set_short("dreadwolf");
   set_pshort("dreadwolves");
   set_race_name("undead");
   
   set_long(" This undead monstrosity is a dreadwolf, often summoned by evil necromancers " +
      "as messengers, spies or guardians. The unmistakable odor " +
      "of this pale, hairless beast is one of rot and decay. " +
      "Its pupiless eyes stare balefully up at you.\n");
   
   set_aggressive(1);
   
   
   set_gender(G_NEUTER);
   set_stats(({20,30,20,5,5,65}));
   add_prop(LIVE_I_UNDEAD, 25);
   set_alignment(-350);
   set_knight_prestige(200);
   
   set_skill(SS_SWIM, 95);
   
   add_prop(CONT_I_WEIGHT, 4000);
   add_prop(CONT_I_VOLUME, 3700);
   
   
   /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
   set_attack_unarmed(A_BITE, 20,29,W_IMPALE,80,"jaws");
   set_attack_unarmed(A_LCLAW, 22,15,W_SLASH,10,"left paw");
   set_attack_unarmed(A_RCLAW, 22,15,W_SLASH,10,"right paw");
   
   /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
   set_hitloc_unarmed(H_HEAD, ({ 18,22,15,15}),20,"head");
   set_hitloc_unarmed(H_BODY,({ 14,17,20,0}),80,"body");
}
