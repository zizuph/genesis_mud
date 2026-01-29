#include "/d/Krynn/common/defs.h"

inherit M_FILE
#include <macros.h>
#include <ss_types.h>

#define OBJ    "/d/Krynn/pax/s_road/obj/"

void
create_krynn_monster()
{
    int i;

    set_name("dwarf warrior");
    set_living_name("hill dwarf warrior");
    set_long("This is a dwarven clansman who has been hired by the miners " +
             "for protection. He is a broad-shouldered, stocky fellow, " +
             "and you deem it to be unwise to underestimate his prowess.\n");
    set_race_name("dwarf");
    set_adj("strong");

    add_act("say what i wouldn't do for a cup of fine mead... ");
    add_act("emote lovingly inspects his axe for any signs of wear. ");
    add_act("emote grumbles something about the boredom of guard duty. "); 
    add_act("say They don't pay me enough for this!");
    set_act_time(8);
    set_gender(0); /* male = 0, female = 1, other = 2 */
    add_prop(NPC_I_NO_LOOKS,1);

    set_alignment(50);
    set_knight_prestige(-200);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 55 + random(20));

    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_AWARENESS, 25);
    set_skill(SS_DEFENCE, 50 );
    set_all_hitloc_unarmed(({ 6, 7, 5 }));
    
    set_alarm(0.0, 0.0, "arm_me");
}

int
arm_me()
{
    clone_object(OBJ + "dscal.c")->move(TO);
    clone_object(OBJ + "dwhelm.c")->move(TO);
    clone_object(OBJ + "dleg.c")->move(TO);
    clone_object(OBJ + "battleax.c")->move(TO);
    command("wear all");
    command("wield all");
}



