/* 
 * The ghost of the orcchief */
inherit "/std/monster";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define NF(xx)          notify_fail(xx)
#define TP              this_player()
#define TO              this_object()
#define ALIGN           -300

static object orc_killer;
static string orc_killer_name;

void
init_living()
{
    ::init_living();
}

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("orcghost");
    add_name("ghost");
    set_long(BSN(
	"He is a ghost of the orcchief.  He is even more fearsome in his "+
	"undead form."
        ));
    set_race_name("ghost");
    set_gender(0);

    set_stats(({190, 180, 200, 70, 70, 120}));
    set_hp(6000);
    set_alignment(ALIGN);
    set_all_hitloc_unarmed(60);
    set_all_attack_unarmed(35, 40);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 100);
    
    add_prop(LIVE_I_SEE_DARK, 99);
    add_prop(CONT_I_WEIGHT, 230000);
    add_prop(CONT_I_VOLUME, 230000);
    add_prop(CONT_I_MAX_WEIGHT, 330000);
    add_prop(CONT_I_MAX_VOLUME, 330000);
    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_aggressive(1);
    
    trig_new("%s 'moves behind' %s", "attack_killer");
    trig_new("%s 'rescues' %s", "attack_killer");    
}

void
arise()
{
     command("emote arises from the dead body of the orchief");
     command("say " + orc_killer_name + "!  You killed me!");
     command("say prepare to die!  I have come back in undead form " +
	     "to massacre you!");
}

void
set_killer(object k)
{
     orc_killer = k;
     orc_killer_name = k->query_name();
     set_random_move(1);
     set_follow(orc_killer_name);
     set_random_move(1);     
}

void
attack_killer(string s1, string s2)
{
     aggressive_attack(orc_killer);
}
void attack()
{
     aggressive_attack(orc_killer);
}
