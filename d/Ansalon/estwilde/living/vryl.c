#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
#define DWARF_ENEMY "_dwarf_enemy"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("vryl");
    set_title("Bloodstone, Young Trailcutter of the Neidar Clan");
    set_introduce(1);
    set_race_name("dwarf");
    set_adj("young");
    add_adj("stubbled");
    set_short("young stubbled dwarf");
    set_long("This young dwarf is covered with trail dust, and " +
      "by the looks of his clothes has done alot of travelling. A horn hangs from his shoulder, " +
      "marking him as a scout for the Iron Delving clan.\n");

    set_stats(({55,30,70,40,40,50}));
    set_hp(10000);

    set_alignment(100);
    set_knight_prestige(-1);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_AXE, 40);

    set_act_time(15);
    add_act("say By Reorx I hate goblins!");

    set_default_answer("The young stubbled dwarf says: Sorry, " +
      "I don't 'ave time to chat. Gotta keep an eye out for " +
      "raiding parties on Iron Delving.\n");

    start_patrol();
    set_patrol_time(4);
    set_patrol_path(({"say Well! Off to patrol the plains. Axes high!",
	1,"emote rises from his chair.","w","s","nw","nw","nw","nw","sw",
	"w","sw","nw","w","nw","sw","sw","nw",
	600,"se","ne","ne","se","e","se","ne","e",
	"ne","se","se","se","se","n","e","say Ale barkeep!","emote sits himself down in a chair",
	120}));

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object("/d/Ansalon/kalaman/obj/weapon/notched_axe")->move(TO,1);
    clone_object(EOBJ + "vryl_horn")->move(TO,1);
    command("wield all");
}

void
attack_func(object enemy)
{
    if(enemy->query_race() == "giant")
    {
	command("shout Giants! Must warn the clan!");
	command("blow giant");
	return;
    }
    if(enemy->query_race() == "undead")
    {
	command("shout Lord Soth has sent his minions from the grave!");
	command("blow Lord Soth's undead force");
	return;
    }
    command("say Ogre raiding party! Heading to Iron Delving!");
    command("blow ogre");
    return;
}

void
run_off()
{
    command("spit");
    command("shout Yer mother ruts with gnolls!");
    command("emote runs off.");
    remove_object();
}

void
attacked_by(object ob)
{
    ob->add_prop(DWARF_ENEMY, 1);
    set_alarm(0.5, 0.0, "run_off");
    ::attacked_by(ob);
}

void
init_living()
{
    if(TP->query_race() =="ogre" || TP->query_race() == "giant" || TP->query_race() == "undead")
	set_alarm(0.5, 0.0, "attack_func", TP);
    ::init_living();
}
