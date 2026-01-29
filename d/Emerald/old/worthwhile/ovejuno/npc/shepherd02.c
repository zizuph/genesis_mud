/* Ckrik June 1998
 * Modified by Marisol (08/28/98) to be used in Ovejuno, Emerald
 */

inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/lib/intro.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include "../defs.h"

#define WEP (OVEJUNO_WEP_DIR + "staff")
#define SARM (OVEJUNO_ARM_DIR + "m_shirt")
#define SLEG (OVEJUNO_ARM_DIR + "pants")
#define FLUTE (OVEJUNO_OBJ_DIR + "panflute")

void
create_emerald_monster()
{
    ::create_emerald_monster();
    set_name("ribarto");
    set_adj("small");
    add_adj("dreamy");
    set_race_name("human");
    set_gender(G_MALE);
    set_appearance(65);
    set_short("small dreamy human");
    set_long("A small shepherd. It seems that he is not paying " +
        "much attention to his sheep. His eyes look dreamily to the " +
        "far lands of the south.\n");

    set_act_time(10);
  
    set_stats(({45, 55, 45, 55, 55, 45}));

    set_hp(query_max_hp());
  
    set_skill(SS_DEFENSE,70);
    set_skill(SS_PARRY,50);
    set_skill(SS_WEP_POLEARM, 65);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_BLIND_COMBAT,50);

    add_prop(OBJ_M_HAS_MONEY, 300);
    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_VOLUME, 100);
    add_equipment(({WEP, SARM, SLEG, FLUTE}));
  
    add_act("emote sighs witfully.");

    add_act("emote sings softly to himself: \n" +
        "\tCome live with me and be my love\n" +
        "\tAnd we will all the pleasures prove\n" +
        "\tThat hills and valleys, dales and fields,\n" +
        "\tAnd all the craggy mountains yields.\n");
  
    add_act("play sweetly his pan flute");

    set_alignment(400);

}


int
query_knight_prestige()
{
    return -500;
}
