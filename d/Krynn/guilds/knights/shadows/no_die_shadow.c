/* prevent the player/npc from dying if shadowed with this. */

#include <stdproperties.h>
#include <std.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../guild.h"
#define MERCYFUL "_knight_mercyful"

inherit "/std/shadow";

object *knights = ({ });
int all = 0;
int alrm;
object *my_killer_list = ({ });

void
set_all_knight_generous(int how)
{
    /*all = !!how;    don't make all generous!!!*/
    if (!alrm)
      alrm = set_alarm(3000.0,0.0,"remove_shadow",MASTER);
}

void
remove_generous_knight(object who)
{
    knights -= ({ who });
}

void
add_generous_knight(object who)
{
    knights += ({ who });
}

object
query_generous_knight(int which)
{
    return knights[which];
}

object *
query_generous_knights()
{
    return knights;
}

void
stop_the_fight()
{
    object *ene = shadow_who->query_enemy(-1);
    ene->stop_fight(shadow_who);
    shadow_who->stop_fight(ene);
}

void
do_die(object killer)
{
    int il;
    object *tm, medal;

    /* Bad wiz forgot to set the killer */
    if (!objectp(killer))
      killer = previous_object();

    if (!objectp(killer))
    {
	shadow_who->do_die(killer);
	return;
    }

    medal = P("pal_med",killer);

    /* check if this function is the correct one to call or not
     */
    if (all)
    {
	if (!MEMBER(TP) && !LAYMAN(TP))
	{
	    shadow_who->do_die(killer);
	    return;
	}
    }
    else if (!medal || (!medal->query_generous() &&
			shadow_who->query_prop(MERCYFUL) != killer))
      /*if (member_array(killer, knights) == -1)*/
    {
	shadow_who->do_die(killer);
	return;
    }
    
    /* Did I die ?
     */
    if (TO->query_hp() > 0 || TO->query_wiz_level() || TO->query_ghost())
      return;
    
    /* Stupid wiz didn't give the objectp to the killer.
     */
    if (!objectp(killer))
      killer = previous_object();
    /* Bad wiz, calling do_die in someone.
     */
    if ((MASTER_OB(killer) == WIZ_CMD_NORMAL) ||
        (MASTER_OB(killer) == TRACER_TOOL_SOUL))
      killer = this_interactive();
    
    stop_the_fight();
    my_killer_list += ({ killer });
    if (shadow_who->query_prop(MERCYFUL) == killer)
      killer->catch_msg("You have shown mercy to " + QTNAME(shadow_who) + " before, now you can't change your mind!\n");
    killer->catch_msg("You have knocked " + QTNAME(shadow_who) + " out cold.\n");
    shadow_who->catch_msg(QCTNAME(killer) + " has knocked you out cold!\n");
    tell_room(E(shadow_who), QCTNAME(killer) + " has knocked " +
	      QTNAME(shadow_who) + " out cold.\n", ({killer, shadow_who}));
    shadow_who->command("$drop all");
    shadow_who->add_prop(LIVE_S_EXTRA_SHORT," is unconscious");
    shadow_who->add_stun();
    shadow_who->add_prop("_see_invis_backup",
			 shadow_who->query_prop(LIVE_I_SEE_INVIS));
    shadow_who->add_prop(LIVE_I_SEE_INVIS, -100);
    shadow_who->add_prop("_see_dark_backup",
			 shadow_who->query_prop(LIVE_I_SEE_DARK));
    shadow_who->add_prop(LIVE_I_SEE_DARK, -100);
    killer->notify_you_killed_me(shadow_who);
    killer->add_panic(-20);
    tm = (object*)killer->query_team_others();
    for (il = 0; il < sizeof(tm); il++)
      if (E(killer) == E(tm[il])) 
	tm[il]->add_panic(-12);
    
    tm = (object*)shadow_who->query_team_others();
    for (il = 0; il < sizeof(tm); il++)
      if (E(shadow_who) == E(tm[il])) 
	tm[il]->add_panic(20);
    
    //shadow_who->second_life();   
    //what should i do with this? dracs fix a corpse here!!! so i guess i can't call it.
}


void
wake_up_again()
{
    set_alarm(3.0,0.0,"get_ready");
}

void
get_ready()
{
    int i = shadow_who->query_prop("_see_invis_backup");
    if (i)
      shadow_who->add_prop(LIVE_I_SEE_INVIS, i);
    else
      shadow_who->remove_prop(LIVE_I_SEE_INVIS);
    shadow_who->remove_prop("_see_invis_backup");
    i = shadow_who->query_prop("_see_dark_backup");
    if (i)
      shadow_who->add_prop(LIVE_I_SEE_DARK, i);
    else
      shadow_who->remove_prop(LIVE_I_SEE_DARK);
    shadow_who->remove_prop("_see_dark_backup");
    shadow_who->remove_prop(LIVE_S_EXTRA_SHORT);
    shadow_who->catch_msg("You slowly regain consciousness.\n");
    tell_room(E(shadow_who), QCTNAME(shadow_who) + " seems to regain " +
	      "consciousness.\n", shadow_who);
    shadow_who->remove_stun();
    shadow_who->command("$get all");
    shadow_who->command("$wear all");
    shadow_who->command("$wield all");
}

void
attack_object(object ob)
{
    if (member_array(ob, my_killer_list) >= 0)
      return;
    shadow_who->attack_object(ob);
}
