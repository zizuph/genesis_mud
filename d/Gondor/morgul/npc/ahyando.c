/* This file is /d/Gondor/morgul/npc/ayhando.c         */
/*                                                     */
/* Olorin, July 1993                                   */

inherit "/d/Gondor/morgul/npc/ithil_man.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "dagger",WEP_DIR + "knife"})
#define ARM_ARRAY1 ({ARM_DIR + "ltrousers"})
#define ARM_ARRAY2 ({ARM_DIR + "fjacket"})

#define SEQ_PICK "_mon_pick"

public void
create_ithil_man()
{
    set_long(BSN("A tall swarthy man from Harad or Khand in the south, "
      + "with a face like a skull and burning eyes. He has probably "
      + "seen many a fight in his day, but now he is rather aged and "
      + "working here as barkeeper. From his place behind the counter "
      + "he is watching his customers intently, but he seems to look "
      + "at you more than at all others."));
    set_living_name("ahyando");
    set_name("ahyando");
    add_name("bar keeper");
    add_name("barkeeper");
    add_name("keeper");
    
    set_base_stat(SS_STR, 35+random(15));
    set_base_stat(SS_DIS, 25+random(5));
    remove_prop(LIVE_I_NEVERKNOWN);

    set_chat_time(15+random(15));

    set_cchat_time(5+random(10));

    set_pick_up(0);
}

static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;

    seq_delete(SEQ_PICK);
}

