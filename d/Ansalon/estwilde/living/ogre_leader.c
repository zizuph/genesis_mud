#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit AUTO_TEAM

#define WEP1 WEP + "ogre_axe"
#define ARM "/d/Ansalon/balifor/flotsam/obj/armour/chain"

string *gAdj1 = ({"warty","ugly","grey-skinned",
  "huge","giant","fat","bony"});
string *gAdj2 = ({"cruel","evil","brutal","depraved",
  "harsh","rugged","hungry"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"ogre","goblin"}));
    set_max_team_size_auto_join(20);

    set_name("ogre");
    add_name("ogre_leader");
    set_adj("towering");
    add_adj(ONE_OF(gAdj2));
    set_race_name("ogre");
    set_long("This huge ogre towers over eleven feet tall, " +
      "and looks almost twice as wide in the shoulders as any " +
      "other ogre you have seen. Malevolent intelligence " +
      "gleams in his eyes, pointing him out to be a dangerous " +
      "adversary.\n");

    set_stats(({210, 90, 200, 60, 60, 100}));
    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(-450);
    set_knight_prestige(50);

    set_skill(SS_WEP_AXE, 80);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 30);
    set_skill(SS_AWARENESS, 10);

    set_act_time(10);
    add_act("emote stares across the plains hungrily.");
    add_act("emote growls: Ooomans taste nice, uhnlike " +
      "dem dwarfies! Der too tough on da chops!");
    add_act("scream");
    add_act("emote smells his smelly furs.");
    add_act("kill dwarf");
    add_act("assist");

    set_cact_time(0);
    add_cact("assist");
    add_cact("say Eat axe!");


    start_patrol();
    set_patrol_time(10);
    set_patrol_path(({"n","w","w","n","n","w","s","w",
	"n","n","e","n","w","n","s","e","s",
	"w","s","s","e","n","e",
	"s","s","e","e","s",
	"e","e","e","se","se","ne",
	"ne","se","e","se","ne","kill guard","shout Squish da dwarfies!",
	700,"say Pillage time!","e","e","se",
	"say Iron Delving! Over da brudge!","kill guard",400,"se","se",
	"se","se","kill guard",700}));
    disable_patrol_loop();
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP1)->move(TO,1);
    command("wield all");
    clone_object(ARM)->move(TO,1);
    command("wear all");

}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
