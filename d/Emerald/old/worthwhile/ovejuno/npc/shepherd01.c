/* Ckrik June 1998
 * Modified by Marisol (08/24/98) to be used in Ovejuno, Emerald.
*/

#pragma strict_types
inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/lib/intro.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include "../defs.h"

#define WEP OVEJUNO_WEP_DIR + "staff.c"
#define SARM OVEJUNO_ARM_DIR + "m_shirt.c"
#define SLEG OVEJUNO_ARM_DIR + "pants.c"

string
sing()
{
tell_room(environment(),QCTNAME(this_object()) + " sings softly:\n" +
    "\tOh Danny boy, the pipes, the pipes are calling\n" +
    "\tFrom glen to glen, and down the mountain side\n" +
    "\tThe summer's gone, and all the flowers are dying\n" +
    "\t'tis you, 'tis you must go and I must bide.\n", this_object());
return "";
}

string
sing1()
{
tell_room(environment(),QCTNAME(this_object()) + " sings softly:\n" +
    "\tBut come you back when summer's in the meadow\n" +
    "\tOr when the valley's hushed and white with snow\n" +
    "\t'tis I'll be there in sunshine or in shadow\n" +
    "\tOh Danny boy, oh Danny boy, I love you so.\n", this_object());
return "";
}

string
sing2()
{
tell_room(environment(),QCTNAME(this_object()) + " sings softly:\n" +
    "\tAnd if you come, when all the flowers are dying\n" +
    "\tAnd I am dead, as dead I well may be\n" +
    "\tYou'll come and find the place where I am lying\n" +
    "\tAnd kneel and say and 'Ave' there for me.\n", this_object());
return "";
}

string
sing3()
{
tell_room(environment(),QCTNAME(this_object()) + " sings softly:\n" +
    "\tAnd I shall hear, tho' soft you tread above me\n" +
    "\tAnd all my dreams will warm and sweeter be\n" +
    "\tIf you'll not fail to tell me that you love me\n" +
    "\tI simply sleep in peace until you come to me.\n", this_object());
return "";
}

void
create_emerald_monster()
{
    ::create_emerald_monster();
    set_name("Amos");
    set_adj("young");
    add_adj("shepherd");
    set_race_name("human");
    set_gender(G_MALE);
    set_appearance(75);
    set_short("young shepherd human");
    set_long("A young shepherd. He stands tall in the pastures "+
        "watching the sheep grazes placidly in the green grass. "+
        "Sometimes he sings softly to himself, some shepherd song "+
        "to abate his boredom.\n");

    set_title("the Shepherd");
    add_prop(CONT_I_HEIGHT, 240);
    add_prop(CONT_I_VOLUME, 5000);
    add_prop(OBJ_M_HAS_MONEY, 500);
    add_equipment(({WEP, SARM, SLEG}));
    set_stats(({60, 55, 60, 45, 45, 55}));

    set_hp(query_max_hp());
    set_all_hitloc_unarmed(50);
  
    set_skill(SS_DEFENSE,70);
    set_skill(SS_PARRY,50);
    set_skill(SS_WEP_POLEARM, 65);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_BLIND_COMBAT,50);
  

    set_alignment(55);

{
    set_act_time(10);
    add_act("@@sing@@");
    add_act("@@sing1@@");
    add_act("@@sing2@@");
    add_act("@@sing3@@");
}

}

int
query_knight_prestige()
{
    return -30;
}
