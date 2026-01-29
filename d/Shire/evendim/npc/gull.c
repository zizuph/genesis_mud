/*
 * This is a common sea gull
 * Can be cloned by ~Shire/common/evendim/ev16
 */
 inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
#include <ss_types.h>
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
 object target;
string name;

void
create_creature()
{
    set_name("bird");
   add_name(({"seagull","gull"}));
   set_short("silver grey seagull");
   add_adj(({"silver","grey"}));
   set_race_name("seagull");
   set_gender(G_NEUTER);
    set_long("This seagull seems to be a long way from "+
   "the sea.  Perhaps it has found another source of "+
   "fresh fish?\n");
     add_prop(LIVE_I_NEVERKNOWN, 1);
    set_stats(({ 5, 10, 2, 15, 15, 25 }));
    set_attack_unarmed(0,  8, 8,W_IMPALE, 100, "beak");
   set_hitloc_unarmed(0, ({ 8, 8, 8, 8 }), 100, "body");
    set_act_time(3);
   add_act("hiccup");
    add_prop(CONT_I_WEIGHT, 50);   /* 0.05 Kg  */
   add_prop(CONT_I_VOLUME, 100);   /* 0.10 Ltr */
  }
  /* For the solamnian Knights */
 query_knight_prestige() { return(10); } /* Nobody likes a gull */
