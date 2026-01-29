
/* smaller fish for coral requiem */
/* Karath 01/97 */

inherit "/d/Emerald/std/emerald_creature";

#include "/d/Emerald/eclipsia/edefs.h"
#include <wa_types.h>

#define	HURTPLAYER	((this_player()->query_hp() / this_player()->query_max_hp()) * 10 < 9)

object myEnemy;


void
create_emerald_creature()
{
   string *adjs, *species;

   int h, i;

   add_prop(LIVE_I_NEVERKNOWN, 1);

   add_prop(MAGIC_I_BREATH_WATER, 1);

   set_gender(2);

   add_adj("dangerous");
   set_race_name("mako");
   add_name("shark");

   set_long("	This "+short()+" is one of the most dangerous "+
	"beings in the waters. It's sleek body is almost eight "+
	"feet long, and ends with a mouth full of razor-sharp "+
	"teeth. The mako shark has been known to swim as fast "+
	"as a cheetah can run on land. It feeds on many different "+
	"sizes of fish, but will usually only attack swimmers that "+
	"are already wounded and bleeding.\n");

   add_prop("_coral_requiem_npc_", 1);
   add_prop(MAGIC_I_BREATH_WATER, 1);

   set_skill(SS_DEFENCE, 65 + random(10));
   set_skill(SS_SWIM, 100);
   set_skill(SS_BLIND_COMBAT, 70);
   set_skill(SS_AWARENESS, 70 + random(15));
   set_skill(SS_UNARM_COMBAT, 70);

   set_stats( ({ 100, 160, 150, 15, 15, 150 }) );
   
   set_hitloc_unarmed(1, 50, 75, "tough-skinned body");
   set_hitloc_unarmed(1, 50, 25, "tough-skinned head");

   set_attack_unarmed(1, 55, 55, W_IMPALE|W_SLASH, 100, "horrible bite");

   set_random_move(5);

   set_act_time(6);

   add_act("emote slowly swims around looking for smaller prey.");
   add_act("emote brushes against you, then swims away, apparantly "+
	"deciding you were too big to kill.");
   add_act("kill _eclipsia_small_fish_");
   add_act("kill _eclipsia_large_fish_");

   set_cact_time(3);  

   add_cact("emote swims furiously around, trying to get an opening.");
   add_cact("emote opens it's jaws wide and charges in again.");

   trig_new("%w 'leaves' / 'sneaks' %s", "follow_attacker");
}

public void
init_attack()
{   
    if (HURTPLAYER && !(this_player()->query_npc()) && !this_object()->query_enemy())
    {
        set_alarm(2.0, 0.0, &command("kill "+this_player()->query_real_name()));
    	myEnemy = this_player();
    }
        return;
}   


public void
do_follow(string where)
{   
    if (where != "enter")
        command(where);
}   

public int
follow_attacker(string who, string where)
{   
    mixed arr;
    int i;

    sscanf(where, "%s.", where);

    if (myEnemy && (myEnemy->query_real_name() == lower_case(who)))
    set_alarm(0.2, 0.0, "do_follow", where);

    return 1;
}

