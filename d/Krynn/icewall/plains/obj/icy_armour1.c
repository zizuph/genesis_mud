/* Created by Macker 7/27/94 */
inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/icewall/local.h"

inherit MELT_BASE


int alarm = 0;

void
create_armour()
{
    set_name("armour");
    add_name("icy_armour1");
    set_ac(30);
    set_at(A_BODY);
    set_af(this_object());
    add_adj( ({"icy", "body"}) );
    set_short("icy body armour");
    set_long("This body armour is made of ice. You feel very cold " +
	     "wearing it, but also very comfortable knowing that many of your " +
	     "enemy's blows will slip right off the armour's icy surface.\n");
    add_prop(OBJ_I_VOLUME, 2900);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_BODY));
    /* Yes I know 30 != 25, but this armour's strength is in it's
       slippery surface, not it's mass. */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
    make_me_meltable();
}

void
do_freeze_player()
{
    object who;
    who = query_worn();
    if((who)&&(!(who->query_prop(MAGIC_I_RES_COLD))))
      {
	  who->catch_msg("You feel freezing pain from your icy " +
			 "armour.\n");
	  who->command("shiver");
	  who->heal_hp( -(random(20)+1));
	  set_alarm(300.0, 0.0, "do_freeze_player");
      }
    return;
}

int
wear()
{
    if(!alarm)
      alarm = set_alarm(300.0, 0.0,"do_freeze_player");
    return 0;
}

int
remove()
{
    return 0;
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}

