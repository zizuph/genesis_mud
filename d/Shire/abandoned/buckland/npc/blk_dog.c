/* 
 *  Farmer Maggot had 3 dogs, and I can only
 *  remember the name of one of em, so I'll
 *  make him :) His name is Fang.
 */

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

object target;
string name;

create_creature()
{
    if (!IS_CLONE)
        return;
    seteuid(getuid(this_object()));
    set_name("fang");
    set_pname("dogs");
    set_living_name("_fang_");
    set_race_name("dog");
    set_gender(G_MALE);
    set_long("This is one of Farmer Maggot's dogs, he looks mean. \n");


    set_stats(({30,40,30,10,10,50}));

    set_attack_unarmed(
                   W_KNIFE,   /* weapon type (claws and teeth) */
                        15,   /* hit */
                        15,   /* pen */
        W_SLASH | W_IMPALE,   /* damage type */
          33, "right claw",   /* right claw 33% use */
          33,  "left claw",   /* left claw 33% use */
          34,      "teeth"    /* teeth 34% use */);

    set_hitloc_unarmed(
         0,                    /* armour type ?? */
        10,                    /* armour class */
        100, "body"            /* body hit all the time */);

  }
        


