 /*
  * /d/Gondor/common/herbs/curugwath.c
  *
  * will temporarily increase your sneak and hide skill when eaten
  * following a suggestion by Karath
  *
  * Olorin, November 1993
  */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define ENHANCE        15   /* skill enhancement */
#define EFFECT         ({SS_SNEAK, SS_HIDE})
#define EFFECT_MSG     ({"sneak","hide yourself"})

void
create_herb()
{
    set_name("leaf");
    set_adj(({"silvery","long","slender"}));
    set_herb_name("curugwath");
    set_short("silvery leaf");
    set_pshort("silvery leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN(
    "A long, slender silvery leaf. When you shift it in the light, it seems to " +
    "change colour from grey to brown and green."));
    set_id_long(BSN(
    "This is a curugwath leaf. Curugwath is known to grow only in " +
    "dark and wet places. Eating the leaves is said to make a person more efficient " +
    "when trying to hide or to move stealthily."));

    /* with HERB_SPECIAL, define only one effect! */
    set_effect(HERB_SPECIAL,"",0);
    set_id_diff(60);
    set_find_diff(8);
    set_decay_time(2400);
    set_herb_value(975);
    set_dryable();
}

void
special_effect()
{
  object  shadow;
  int is;

  is = random(sizeof(EFFECT));
  shadow = clone_object(HERB_DIR + "skill_enhance");
  shadow->set_enhance_effect(EFFECT[is],EFFECT_MSG[is],ENHANCE);
  shadow->move(TP,1);
}
