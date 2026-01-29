/* Guild symbol for the gnomish racial guild.
 * Format inspired by Nick's Solamnian medal.
 * Modified by Percy
 * Completed by Dajala
 *
 * Most of the data for the modules is stored in modules.h but,
 * because of their length, the descriptions are found in 
 * guild/module_desc.o.
 *
 * Latest update: 02.04.95
 */

#pragma save_binary

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../guild.h"
#include "../modules.h"

static string modules;       /* Each module adds features to the item. */   
string *module_desc;  
static int number_of_modules, level;
static int *flags, *break_chance;      /* module flags */
static int water;                      /* water in the dispenser */
static int fire, steam, wood, burn_id; /* for module steamengine */
static int flour;		       /* for MasterBakerFritter */

/* Prototypes */

void update_flags(string flagnames);


void
create_object()
{
    if (!IS_CLONE)
	return;
    flags = ({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    break_chance = ({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    set_name("gizmo");
    add_name("k_gizmo");
    set_short("gnomish gizmo");
    set_long(   "This is the symbol of your proud heritage as a "+
      "Krynnish gnome.  It is a bewildering collection of gears "+
      "and springs that only a true gnome could love.  There is "+
      "room for additional pieces to be clipped on.  For a list "+
      "of the modules on your gizmo, type 'modules'. For general " +
      "information about the Inventors use 'help gnomes menu'.\n");

    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP, "You don't dare to drop your precious gizmo!\n");
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE, "You could never give your gizmo away!\n");

    add_item(({"room", "room for additional modules", "spaces", "space"}),
      "@@module_number");

    seteuid(getuid());

    restore_object("/d/Krynn/gnome/guild/module_desc");
}


string
module_number()
{
    return "There is space for 15 modules in total to be clipped onto the "
    + "gizmo.\nCurrently, you're using " + number_of_modules 
    + " spaces.\n";
}

string
query_auto_load()
{ 
    return MASTER + ":" + modules + "," + water + ","
    + wood + "," + flour;
}

void
init_arg(string arg)
{
    string *arr;
    int i;

    if(sscanf(arg, "%s,%d,%d,%d", modules, water, wood, flour) != 4)
	if(sscanf(arg, "%s,%d,%d", modules, water, wood) == 3)
	    flour = 0;

    level = 1;
    arr = explode(modules, "!");

    /*  arr[0] is the player's name, to prevent transfer of the item. */
    set_alarm(1.0, -1.0, "test_owner", arr[0]);

    update_flags(modules);

    /* The modules string contains all modules this player has installed. */
    /* Sample:  "Dajala! 4steamengine 3waterdispenser" */
    /*       Playername! break-% modulename /*
    /* Appropriate flags are set in the following loops.  Add references */
    /* to modules here, and flag routines at the end of this file. */
    /* Be sure to declare flags at top of file. */
    /* The actual routines are in the soul file. */
}

void
test_owner(string name)
{
    if(name !=  (E(TO)->query_real_name()))
	set_alarm(10.0, -1.0, "junk");
}

void
update_flags(string flagnames)
{
    string *list;
    int i, j;
    list = explode(flagnames, " ");
    for(i=0;i<sizeof(TYPES);i++)
	remove_item(TYPES[i]);

    for (i=0;i<sizeof(list);i++)
    {
	for(j=0;j<sizeof(TYPES);j++)
	{
	    if ((list[i][1..]) == (C(TYPES[j])))
	    {
		flags[j] = 1;
		break_chance[j] = atoi(list[i][0..0]);
		add_item(TYPES[j], module_desc[j]);
	    }
	}
    }
    number_of_modules = sizeof(list)-1;
}

void
init()
{
    if (!interactive(TP))
	return;
    if ((!GMEMBER(TP)) && !TP->query_wiz_level())
	set_alarm(3.0, -1.0, "junk");
    ADA("modules");
    set_alarm(3.0, -1.0, "soul", E(TO));
    set_alarm(3.0, -1.0, "set_tax");
}

void
junk()
{
    object junk;
    E(TO)->catch_msg("The gizmo makes a strange"
      + " whirring noise.... Suddenly a cog wheel comes loose"
      + " and clatters to the ground. The whole gizmo shudders"
      + ", shivers, shakes... before disintegrating into a pile"
      + " of useless junk.\n");
    E(TO)->command("confused");
    seteuid(getuid(TO));
    junk = clone_object(GOBJ + "junk.c");
    junk->move(E(E(TO)));
    TO->remove_object();
}

int
add_module(string str)
{
    modules = modules + str + " ";
    update_flags(modules);
    return 1;
}

void
set_modules(int *mods)
{
    flags = mods;
}

int *
query_modules()
{
    return flags;
}

int
modules()
{
    int i, flag;

    NF("You have no modules attached.\n");
    for (i=0;i<sizeof(flags);i++)
	if (flags[i]==1)
	    flag=1;
    if (!flag)
	return 0;

    write("You have the following modules attached to your gizmo:\n");

    for (i=0;i<sizeof(TYPES);i++)
	if (flags[i])
	    write("The " + C(TYPES[i]) + ".\n");

    write("\nTry 'examine <module>' for a closer look at a single module.\n");
    return 1;
}

void
soul(object ob)
{
    ob->add_cmdsoul(GNOME_SOUL);
    ob->update_hooks();
}

int
update_level(int stat)
{
    int level;

    level = 1;
    if (stat >= L2) level = 2;
    if (stat >= L3) level = 3;
    if (stat >= L4) level = 4;
    if (stat >= L5) level = 5;
    if (stat >= L6) level = 6;
    if (stat >= L7) level = 7;
    if (stat >= L8) level = 8;
    if (stat >= L9) level = 9;
    if (stat >= L10)
    {
	level = (stat/5)+2;
    }
    return level;
}

void
set_tax(int i)
{
    object ob;

    ob = E(TO);
    ob->set_guild_pref(SS_RACE, GNOME_TAX);
}

int
query_gnome_level()
{
    return update_level(E(TO)->query_stat(6));
}


/* Called from the joinroom to fix the owner */

void
config()
{
    modules = (E(TO)->query_real_name()) + "! ";
}


/* Modules are breakable */
void
do_break(int number)
{
    int i;
    object obj;

    E(TO)->catch_msg("Ohh no! The " + C(TYPES[number]) + "-module "
      + "breaks!\n");
    flags[number] = 0;
    config();
    for(i=0;i<sizeof(TYPES);i++)
	if(flags[i])
	    modules = modules + break_chance[i] + C(TYPES[i]) + " ";
    update_flags(modules);
    if(number == 2)
	water = 0;
    if(number == 3)
    {
	steam = 0;
	fire = 0;
	wood = 0;
    }
    if(number == 7)
	if(obj = P("_reusable_parts_module_", E(E(TO))))
	    obj->remove_object();
    if(number == 9)
    {
	E(TO)->remove_prop("_gnome_i_gmaker_ent_");
	E(TO)->remove_prop("_gnome_i_gmaker_on_");
    }
}

int
query_number_of_modules()
{
    return number_of_modules;
}

/**************************************************************************
 *              module-functions called from the soul                     *
 **************************************************************************/

void
break_chance(int number)
{
    if(random(100) < break_chance[number])
	do_break(number);
}


int
query_flag(int number)  
{ 
    return flags[number]; 
}

int
check_water()   
{
    return water;
}

void
reduce_water()
{
    water--;
    if((water < 1) && fire)
    {
	E(TO)->catch_msg("OhNo!ThereIsNoMoreWaterLeftToCreateSteam!\n");
	E(TO)->catch_msg("An alarming bell rings and the Steamengine"
	  + "EmergencyShutDownSequence is initiated.\n");
	set_alarm(10.0, -1.0, "ext_fire");
    }
}

void
refill_water(int new_water)     {water = new_water;}

int
check_flour()			{return flour;}

void
reduce_flour()			{flour--;}

void
refill_flour(int new_flour)	{flour = new_flour;}

int
check_wood()    	{return wood;}

void
set_wood(int new_wood)  {wood = new_wood;}

int
check_steam()   	{return steam;}

int
check_fire()    	{return fire;}

void
burn_wood()             /* module 4 and 12 */
{
    if(wood < 1)
    {
	if(fire && random(2))
	    E(TO)->catch_msg("OhNo!TheFireInTheSteamEngineJust"
	      + "WentOut!\n");
	steam = 0;
	fire = 0;
	return;
    }
    if (fire > 0 && steam == 0)
    {
	tell_room(E(TO), "A bell rings.\n");
	if(water < 1)
	{
	    E(TO)->catch_msg("If there had been water in the "
	      + "CavityContainingHotWater of your "
	      + "gizmo, it would have been hot enough "
	      + "for operation by now. You might want to "
	      + "switch the steamengine off "
	      + "to end this waste of energy.\n");
	}
	else
	{
	    steam = 1;
	    E(TO)->catch_msg("The water in the SteamEngine is now "
	      + "hot enough for usage.\n");
	}
    }
    wood--;
    fire++;
    burn_id = set_alarm(800.0, -1.0, "burn_wood");
    seteuid(getuid());
    find_object(GNOME_SOUL)->set_alarm(50.0, -1.0, "distill_contents", E(TO));
}

void
ext_fire()
{
    remove_alarm(burn_id);
    fire = 0;
    steam = 0;
    E(TO)->catch_msg("Your steamengine exhales a final cloud of steam and "
      + "ceases working.\n");
    /* GNOME_SOUL->ext_everything(E(TO)); */
}

void
no_steam()
{
    steam = 0;
}
