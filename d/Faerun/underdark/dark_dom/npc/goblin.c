
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";


#define RADJ ({ \
    "large black-eyed", "skinny hideous", "long-armed evil",\
    "grey-skinned pale", "large club-footed", "large fanged",\
    "grim pale", "grinning brutal", "dull-witted terrible",\
    "squat broad", "dark-skinned swarthy", "large wide mouthed",\
    "flat-nosed sallow skinned", "deadly flat-nosed",\
    "hideous warring", "squint-eyed flat-nosed", "large brutal",\
    "cruel pale", "repulsive squat", "red squint-eyed broad",\
    "hideous brutal", "terrible black-eyed", "savage black-skinned",\
    "large black", "leering squint-eyed"})

#define RLONG ({ \
    "has black eyes and is tall.",\
    "looks hideous and skinny, and reeks of death.",\
    "looks evil and has long arms.",\
    "looks pale and grey-skinned.",\
    "looks large and has club feet.",\
    "has large, dripping fangs and is tall.",\
    "has a grim look on his pale face.",\
    "looks dim-witted but terrible.",\
    "looks squat and broad.",\
    "has dark skin and has sharp fangs.",\
    "has dark skin and looks terrible with its dripping fangs.",\
    "has a wide mouth and is very tall.",\
    "has a flat nose and sallow skin.",\
    "looks deadly and has a flat nose.",\
    "looks hideous and ready to attack anything.",\
    "has squint eyes and a flat nose.",\
    "looks very tall and very brutal.",\
    "has pale skin and appears cruel.",\
    "looks repulsive and squat.",\
    "looks tall and has red, squinting eyes.",\
    "looks hideous and brutal.",\
    "has black eyes and looks terrible.",\
    "has black skin and looks savage",\
    "looks tall and has black skin.",\
    "looks leering with squint eyes.",\
})

int goblin_num = random(24);

void arm_me();

void create_monster()
{
    int i;

    seteuid(getuid(TO));
    npc_name = "goblin";

    set_living_name("goblin");
    set_name(({"goblin", "_goblin_soldier_"}));
    add_name(npc_name);
    set_pname(RADJ[goblin_num] + " goblins");
    add_adj(RADJ[goblin_num]);
    set_short(RADJ[goblin_num] + " goblin");
    set_race_name("goblin");
    set_long("This is a "+RADJ[goblin_num]+" goblin. It " + RLONG[goblin_num] +
    " This is one of the many goblins that inhabits the tunnels of Underdark. It looks vicious and ready to attack anything that crosses its path or wanders in the tunnels.\n");

   set_act_time(5);
   add_act("emote grins greedily.");
   add_act("emote picks something out of its teeth.");
   add_act("emote growls hideously.");
   add_act("emote mutters something in gutteral language.");
   add_act("emote sniffs the air.");

    set_cact_time(5);
    add_cact("emote eyes narrow and attacks you!");
    add_cact("emote begins to pant and slashes you!");
    add_cact("emote works itself into a battle rage.");
    add_cact("emote attacks you with renewed strength.");
    add_cact("emote howls with rage!");
    add_cact("emote charges you with renewed anger.");

    for (i = 0; i < 5; i++)
        set_base_stat(i, 90 + random(25));
    set_base_stat(5, 70);

    set_alignment(0);
    add_prop(LIVE_I_SEE_DARK,10);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);
//    set_restrain_path(TUN_DIR);
    set_pick_up_team(({"_goblin_soldier_"}));

    arm_me();

}

void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    arm = clone_object(ARM_DIR + "go_plate");
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "go_gaunt");
    arm -> move(TO);

    wep = clone_object(WEP_DIR + "go_sword");
    wep -> move(TO);
    wep = clone_object(WEP_DIR + "go_sword");
    wep -> move(TO);

    command("wear all");
    command("wield all");

}
void
init_living()
{
    ::init_living();
    init_team_pickup();
}
