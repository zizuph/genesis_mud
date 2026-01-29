#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit AUTO_TEAM 

int hound_here = 0;

#define KOBJ "/d/Ansalon/guild/OLD/dknights/obj/"
#define WEP "/d/Ansalon/dargaard/obj/weapon/black_mace"
#define ARM1 KOBJ + "armour/dplatemail"
#define ARM2 KOBJ + "armour/dgreaves"
#define ARM3 KOBJ + "armour/dgauntlets"
#define ARM4 KOBJ + "armour/dbracers"
#define ARM5 KOBJ + "armour/dcloak"
#define ARM6 KOBJ + "armour/dhelm"

int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"skeleton", "hound"}));
    set_max_team_size_auto_join(11);

    set_name("knight");
    set_race_name("undead");
    set_adj("undead");
    set_short("undead knight");
    set_gender("G_MALE");
    set_long("Before you stands a demonic creature, mockingly dressed in " +
      "the full battle array of a Knight of Solamnia. Once a noble knight of " +
      "the Order of the Rose back in the days before the Cataclysm, now a "+
      "skeletal minion of the Abyss, it is a deadly combination of knightly " +
      "skills and unholy powers from beyond the grave... certainly not a " +
      "creature to be taken lightly.\n");

    set_stats(({170,170,180, 100, 100, 119}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);

    set_alignment(-1200);
    set_knight_prestige(1000);
    set_all_hitloc_unarmed(20);

    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 97900);
    add_prop(CONT_I_WEIGHT, 78400);
    add_prop(LIVE_I_NO_BODY, 1);
    set_aggressive(VBFC_ME("check_aggressive"));

    set_act_time(12);
    add_act("emote says in an unholy voice: By my vows that bind me to " +
      "the Queen of Darkness, may none stand in my way!");
    add_act("emote stares at you, his skeletal eye sockets filled with " +
      "malevolent fires from beyond the grave.");
    add_act("emote says in a voice from the grave: Undeath before dishonour!");

    set_cact_time(2);
    add_cact("emote salutes you mockingly, as if he did not view you as a " +
      "worthy foe.");
    add_cact("emote rasps: For Dargaard Keep, and the Queen of Darkness!");
    add_cact("shout My undead minion! To me! Let us slay these mortals and "+
      "feed their souls to the demons of the Abyss!");
    add_cact("emote narrows his flaming eyes threateningly.");
    add_cact("say You won't escape fool! Your soul is mine!");

    add_ask(({"quest","task","help"}),"say The Queen of Darkness may have use " +
      "for your soul... allow me to send you to her!",1);

    start_patrol();
    set_patrol_time(20);
    set_patrol_path(({"nw","n","n","n","n","e","e","e","se","s","s","s","s",
	"se","se","se","se","s","s","s","s","se","s","s","s","se",
	"e","e","se","e","e","e","se","se","ne",
	"ne","se","e","se","ne",5,"kill clan_guard","shout Die mortal!",
	700,"shout Time to die, dwarfkin!","e","e","se",
	"say Your town shall fall to my undead forces!","kill guard",400,"se","se",
	"se","se","kill guard",700}));
    disable_patrol_loop();


}


void
attacked_by(object ob)
{
    object g1,g2;
    ::attacked_by(ob);
    
    command("shout Hounds of the Abyss! To me!");

    if(hound_here == 0)
    {
        g1 = clone_object(DNPC + "hound");
        g2 = clone_object(DNPC + "hound");
        
	g1->move(E(TO),1);
	tell_room(E(TO),"From the depths of the shadows, a hound from "+
	  "the pits of hell comes to the death knights call!\n");
	g2->arm_me();
	g2->move(E(TO),1);
	tell_room(E(TO),"From the depths of the shadows, a hound from "+
	  "the pits of hell comes to the death knights call!\n");
	hound_here = 1;
    }
    g1->command("emote howls chillingly into the air!");
    g1->command("kill " +ob->query_real_name());
    g2->command("emote snarls malevolently!");
    g2->command("kill " +ob->query_real_name());

}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    command("wield all");

    clone_object(ARM1)->move(this_object(),1);
    clone_object(ARM2)->move(this_object(),1);
    clone_object(ARM3)->move(this_object(),1);
    clone_object(ARM4)->move(this_object(),1);
    clone_object(ARM5)->move(this_object(),1);
    clone_object(ARM6)->move(TO,1);
    command("wear all");
}

public void
do_die(object killer)
{
    command("emote wails in fury as his undead soul is sent back to the Abyss!");
    ::do_die(killer);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
