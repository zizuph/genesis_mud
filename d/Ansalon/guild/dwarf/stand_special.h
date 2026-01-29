#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "guild.h"

static private int stand_alarm = 0;


void
reset_stand()
{
    object who = query_shadow_who();
    who->catch_msg("You feel a surge of adrenalin, " +
      "and once again feel ready to rage like a true " +
      "dwarven warrior!\n");
    stand_alarm = 0;
}


void
stand(string str)
{
    object who = query_shadow_who();
    int shield_ac, bonus_ac, dwarf_skill, dwarf_con;
    object stand_firm, stand_strong;

    stand_alarm = 1;

    if(member_array(A_SHIELD, who->query_armour(-1)->query_at()) < 0)
    {
	shield_ac = 0;
    }
    else
    if(who->query_armour(W_RIGHT)->query_at() == A_SHIELD)
    {
	shield_ac = who->query_armour(W_RIGHT)->query_ac();
    }
    else if(who->query_armour(W_LEFT)->query_at() == A_SHIELD)
    {
	shield_ac = who->query_armour(W_LEFT)->query_ac();
    }

    dwarf_skill = who->query_skill(SLAM_SPECIAL_SKILL);
    dwarf_con = who->query_stat(SS_CON);

    if(str == "fiercely")
    {
	bonus_ac = (dwarf_con + dwarf_skill) /40 + shield_ac /10;

	stand_firm = clone_object(GUILD_DIR + "stand_firm");
	stand_firm->set_ac(bonus_ac);
	stand_firm->set_duration(30);
	stand_firm->move(who);
        who->add_fatigue(-(who->query_stat(SS_CON) / 10));

    }
    if(str == "stubbornly")
    {
	bonus_ac = dwarf_skill /5 + shield_ac /2;

	stand_strong = clone_object(GUILD_DIR + "stand_strong");
	stand_strong->set_ac(bonus_ac);
	stand_strong->move(who);
        who->add_fatigue(-(who->query_stat(SS_CON) / 8));
    }
    if(str == "aggressively")
    {
	clone_object(GUILD_DIR + "stand_aggro")->move(who);
        who->add_fatigue(-(who->query_stat(SS_CON) / 16));
    }

    set_alarm(40.0, 0.0, "reset_stand");
}


int
query_stand()
{
    return !!stand_alarm;
}

