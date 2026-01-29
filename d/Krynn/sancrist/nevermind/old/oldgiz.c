/* Guild symbol for the gnomish racial guild. */
/* Format inspired by Nick's Solamnian medal.  */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

string modules; /* Each module adds features to the item. */
int number_of_modules = 0;
int emoter_flag = 0; /* List of module flags. */
int lighter_flag = 0;
int smoker_flag = 0;

void
create_object()
{
    if (!IS_CLONE)
	return;

  modules = "";
  set_name("gizmo");
  set_short("a gnomish gizmo");
  set_long(BS("This is the symbol of your proud heritage as a "+
    "Krynnish gnome.  It is a bewildering collection of gears "+
    "and springs that only a true gnome could love.  There is "+
    "room for additional pieces to be clipped on.  For a list "+
    "of the modules on your gizmo, type 'modules'."),70);

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

string
query_auto_load() { 
return MASTER_OB(this_object()) + ":" + modules;

void
init_arg(string str){
  string *list;
  int i = 1;
  strcpy(modules, str);
  strcat(str, " end");
  list = explode(str, " ");

/* modules[0] is the player's name, to prevent transfer of the item. */
/* The modules string contains all modules this player has installed. */
/* Appropriate flags are set in the following loops.  Add references */
/* to modules here, and flag routines at the end of this file. */
/* Be sure to declare flags at top of file. */
/* The actual routines are in the soul file. */

  while (list[i] != "end"){
    if (list[i] == "emoter") emoter_flag = 1;
    if (list[i] == "lighter") lighter_flag = 1;
    if (list[i] == "smoker") smoker_flag = 1;
    i++;
  }
  number_of_modules = i;
}

void
init()
{
    if ((!MEMBER(TP) && !LAYMAN(TP)) && (environment(TO) == TP))
    {
	write("You are not a member of the Solamnian Knights. The medal\n" +
	    "will self destruct.\n");
	remove_object();
    }
    if (!MEMBER(TP) && !LAYMAN(TP))
	return;

    seteuid(getuid(TO));
    if (IN_B_LIST(TP->query_real_name(), 1))
	return;

    IN_P_LIST(TP->query_real_name(), 1);

    call_out("soul", 5, TP);
    call_out("set_tax", 1, 0);
}

soul(object ob)
{
    int i;
    string *souls;

    seteuid(getuid(TO));
    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
	ob->remove_cmdsoul(souls[i]);
    ob->add_cmdsoul(KNIGHT_SOUL);
    for (i = 0; i < sizeof(souls); i++)
	if (souls[i] != KNIGHT_SOUL)
	    ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}

void set_knight_level(int level) { knight_level = level; }

int query_knight_level() { return knight_level; }

void
set_tax(int i)
{
    int stat, old_tax;
    object ob;

    ob = E(TO);
    if (!knight_level)
    {
	ob->set_skill(SS_PRESTIGE_ST, ob->exp_to_stat(
		ob->query_skill(SS_PRESTIGE_ACC)));
	stat = ob->query_skill(SS_PRESTIGE_ST);
	if (stat < 20)
	{
	    ob->set_skill(SS_PRESTIGE_ST, 20);
	    ob->set_skill(SS_PRESTIGE_ACC, 20 * 20 * 20 + 100);
	    stat = 20;
	}

	if (stat <= SS_DBROSE)
	    knight_level = L_BROSE;
	else if (stat <= SS_UCROWN)
	    knight_level = L_SQUIRE;
	else if (stat <= SS_USHIELD)
	    knight_level = L_CROWN;
	else if (stat <= SS_UROSE)
	    knight_level = L_SHIELD;
	else
	    knight_level = L_ROSE;
    }
    if (knight_level && !ob->query_skill(SS_PRESTIGE_ACC))
    {
	ob->set_skill(SS_PRESTIGE_ACC, ob->query_acc_exp(SS_OCCUP));
	ob->set_skill(SS_PRESTIGE_ST, ob->exp_to_stats(ob->
		query_skill(SS_PRESTIGE_ACC)));
    }
    old_tax = ob->query_learn_pref(SS_OCCUP);
    if (TAX[knight_level] < old_tax)
	ob->set_guild_pref(SS_OCCUP, old_tax - i);
    else
	ob->set_guild_pref(SS_OCCUP, TAX[knight_level]);
}


