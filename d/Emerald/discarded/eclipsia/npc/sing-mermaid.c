/* A singing mermaid for Coral Requiem */


inherit "/d/Emerald/std/emerald_monster.c";
inherit "/d/Emerald/std/aid_npc.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Emerald/eclipsia/edefs.h"

mixed equip_me();

mixed
equip_me()
{
    int j;

    j = random(3);

    setuid();
    seteuid(getuid());

    switch (j)
    {
	case 0:
		return ({ ECLIPSIA_OBJ + "pendant", ECLIPSIA_OBJ + "bodice" });
		break;
	case 1:
		return ({ ECLIPSIA_OBJ + "tiara", ECLIPSIA_OBJ + "bodice" });
		break;
	case 2:
		return ({ ECLIPSIA_OBJ + "necklace", ECLIPSIA_OBJ + "bodice" });
		break;
    }
    
}

create_emerald_monster()
{
    string *my_adj_arr;
    string my_adj;
    int i;

    my_adj_arr = ({"beautiful", "charming", "dazzling", "young",
                   "cute", "shy"});

    i = random(sizeof(my_adj_arr));
    my_adj = my_adj_arr[i];

    set_short( my_adj +" mermaid");
    add_adj(my_adj);
    set_name("mermaid");
    set_race_name("merfolk");
    set_long("The mermaid sits in the corner of the cavern "+
		"and sings a haunting, yet beautiful melody. "+
        	"Her striking blond hair flows around the back "+
		"of her head as the currents flow around her.\n");

    add_prop(LIVE_I_NEVERKNOWN,1);
    set_alignment(200);
    set_gender(1);
    set_act_time(4);
    add_act("twinkle");
    add_act("emote sings softly. Her voice rises and falls like a "+
		"softly roaring surf.");
    add_act("emote tosses her hair back, takes a breath, and "+
		"resumes singing.");
    add_act("emote looks into your eyes and smiles during a pause "+
		"in her song.");
    add_cact("scream");
    add_cact("emote shrieks a horrible, deafening sound.");
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_WEIGHT, 75000);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_SWIM, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS, 50);

    set_stats(({(random(60)+40),(random(80)+40),(random(60)+40),
        70,70,(random(40)+20)}));
    add_equipment(equip_me());
}

attacked_by(object enemy)
{
  ::attacked_by(enemy);
  get_assistance(enemy);
}
