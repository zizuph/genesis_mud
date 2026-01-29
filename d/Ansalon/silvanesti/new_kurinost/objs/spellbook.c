/*    Spellbook - provides spells for WoHS and SoHM
 */

inherit "/d/Genesis/specials/examples/std_magic_obj";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/guilds/wohs/defs.h"

void
start_tome_decay()
{
    set_alarm(900.0, 0.0, "do_i_dispel");
}

void
do_i_dispel()
{
    object room = TO;
    object person = TO;

    while(E(room))
      room = E(room);

    if(E(TO) != room)
      while(person && !(interactive(person)))
	person = E(person);

    person->catch_msg("The " +TO->short()+ " falls to pieces due to its " +
        "poor condition.\n");
    set_alarm(0.3, 0.0, "remove_tome_item");

    return;
}

void
remove_tome_item()
{
   remove_object();
}

public void
create_magic_obj()
{
    set_name("tome");
    add_name("_kurinost_spellbook");
    add_name("tome");
    add_adj("leather-bound");
    add_adj("battered");
    set_short("battered leather-bound tome");
    set_long("This is a leather-bound tome that looks like it barely " +
        "survived an explosion. Terribly battered, a lot of its contents " +
        "are damaged beyond comprehension. However you can still make " +
        "out some of the spells that could be scribed, or potentially cast " +
        "if you have the skill and components.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));

    add_prop(MAGIC_AM_ID_INFO, ({ "This is the spell tome of a bozak " +
        "draconian. While this " +
        "tome is damaged, it contains spells that may be scribed " +
        "in to a magician's spellbook or cast.\n", 20 }));

    add_prop(OBJ_S_WIZINFO, "This object holds the spells that can be " +
        "scribed by WoHS or SoHM. Players can also cast spells with it, " +
        "however it will self-destruct after around 15 minutes due to " +
        "the poor condition of the tome. It can be found as part of a spell " +
        "quest in Kurinost on the border of the Silvanesti forest.\n");

    set_keep(1);
    set_holdable(0);
    start_tome_decay();

    /* Turns it into a normal spellbook */
    set_magic_spellbook(1);

    set_magic_obj_soul(RSOBJS + "spellbook_soul.c"); 
    set_magic_obj_effect(({ "_kurinost_greater_magic_shield_object_" }));   
    
    add_cmd_item(({"tome","leather-bound tome","battered tome",
        "battered leather-bound tome"}),"read", "@@read_grimoire");
}

string
read_grimoire()
{
    return "You find one decipherable page that you can make out:\n"+
"\n"+
"         _______________________________________________   _____ \n"+
"     .-/|      ~~**~~      ~~**~~      ~~**~~           \\ /      / \n"+
"     ||||                                                :      |  \n"+
"     ||||          ~~*  LESSER SPELLS   *~~              :       | \n"+
"     ||||                                                :       | \n"+
"     ||||   SCOURING WIND         Conjure a damaging     :       | \n"+
"     ||||  'iniksuaco'            sandstorm.             :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spell element: Air, Superior Acolyte          :      |  \n"+
"     ||||  Spell form: Conjuration, Superior Acolyte     :      |  \n"+
"     ||||  Components: suaco potion (seaside grass,      :      |  \n"+
"     ||||                            alcohol)            :      |  \n"+
"     ||||                                                :      |  \n"+
"     ||||        ~~*  ADVANCED SPELLS  *~~               :       | \n"+
"     ||||                                                :       | \n"+
"     ||||   GREATER MAGIC SHIELD   A shield of magic     :       | \n"+
"     ||||  'jennufethos'           force that absorbs    :       | \n"+
"     ||||                          damage.               :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spell element: Air, Superior journeyman       :      |  \n"+
"     ||||  Spell form: Abjuration, Superior craftsman    :      |  \n"+
"     ||||  Components: Chokecherry and chantrelle herbs. :      |  \n"+
"     ||||                                                :       | \n"+
"     ||||                                                :      |  \n"+
"     ||||_______________________________________________ : _____|  \n"+
"     ||/================================================\\:/=====   \n"+
"     `-------------------------------------------------~___~----   \n"+
"\n\n";
}

string
scribe_spell(string str)
{
    if(!str)
    {
        write("Scribe what?\n");
        return "";
    }

    str = lower_case(str);

    if((str != "iniksuaco") && (str != "jennufethos"))
    {
        write("You do not find that spell in the tome to scribe.\n");
        return "";
    }  

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the " +
            "spells within the leather-bound tome.\n");
        return "";
    }

    if((str == "jennufethos"))
    {
        if(WOHS_MANAGER->query_scribed_spell(this_player(),"jennufethos"))
        {
           write("You already have jennufethos scribed in your " +
               "spellbook.\n");
           return "";
        }

        if(this_player()->query_advanced_spells_max() < 1)
        {
            write("This spell is too advanced for you to learn at this " +
            "time.\n");
            return "";
        } 
    }

    if((str == "iniksuaco"))
    {
        if(WOHS_MANAGER->query_scribed_spell(this_player(),"iniksuaco"))
        {
           write("You already have iniksuaco scribed in your " +
               "spellbook.\n");
           return "";
        }

        if(this_player()->query_lesser_spells_max() < 1)
        {
            write("This spell is too advanced for you to learn at this " +
            "time.\n");
            return "";
        }
    }

    write("You studiously copy the spell " +str+ " into your spellbook " +
        "from the leather-bound tome.\n");
    WOHS_MANAGER->scribe_spell_to_spellbook(this_player(), str);
    return "";

}

/*
 * Function name: init
 * Description:   initialise the commands
 * Arguments:
 */
void
init()
{
    ::init();
    add_action(scribe_spell, "scribe");
}

public string
query_recover()
{
    return MASTER;
}

