/* SARR */
#include "defs.h"
inherit STD_MONSTER;
inherit "/d/Raumdor/lib/intro";

int sex;

string
random_female_name()
{
    return ({ "debbie", "nathime", "jennifer",  "elain", "jasmine", "sandra",
        "kristin", "amy", "laura", "sylvia", "sunshine", "effie", "stacey",
	"pamela", })[random(14)];
}

string
random_female_desc()
{
    return ({ "slim", "buxom", "lovely", "beautiful" })[random(4)];
}

void
create_monster()
{
   ::create_monster();

   set_gender(G_FEMALE);
   set_short(random_female_desc() + " woman");
   set_stats(STAT_ARRAY(60));
   set_name(({ random_female_name(), "woman" }));
   set_race_name("human");
   set_long("This is one of the many citizens of Drakmere. She seems "+
        "young and healthy, as she moves around with some vigor. "+
        "She notices you and smiles at you.\n");
   set_title("of Drakmere");
   set_alignment(DRAKMERE_ALIGN);

   set_skill(SS_WEP_KNIFE,60);
   set_skill(SS_DEFENSE, 40);
   set_skill(SS_UNARM_COMBAT, 20);

   add_act("emote fixes her hair.");
   add_act("emote checks on the fire.");
   add_act("emote says: Hello, stranger.");
   add_act("blush");

   equip(({
    DRAKMERE_ARM_DIR + "c_skirt",
    DRAKMERE_ARM_DIR + "c_shirt",
    DRAKMERE_ARM_DIR + "c_sandals",
    }));
}

do_die(object who)
{
    who->add_prop(IS_ENEMY_OF_DRAKMERE,who->query_prop(IS_ENEMY_OF_DRAKMERE)+1);
    ::do_die(who);
}
