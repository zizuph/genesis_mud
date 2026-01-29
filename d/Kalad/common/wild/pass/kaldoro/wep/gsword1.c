/* 
 * /d/Kalad/common/wild/pass/kaldoro/wep/gsword1.c
 * Purpose    : A standard sword for use by Kaldoro guards.
 * Located    : ../npc/kguard1.c and ../npc/kguard2.c
 * Created By : Rico 13.Dec.94
 * Modified By: 
 */ 

inherit "/d/Kalad/std/weapon.c";

#include "/d/Kalad/defs.h"

create_weapon()
{
   ::create_weapon();
   
   set_name("sword");
   set_adj("rough");
   
   set_short("rough sword");
   set_long("This sword looks to have been through many "+
      "battles.  It is stained with blood and has many "+
      "knicks and deep scratches in it.  Even so, it "+
      "looks like a formidable weapon.\n");
   
   set_default_weapon(28, 25, W_SWORD, W_SLASH | W_IMPALE, W_ANYH, 0);
   
   add_prop(OBJ_I_WEIGHT, 600);
   add_prop(OBJ_I_VOLUME, 1000);
}
