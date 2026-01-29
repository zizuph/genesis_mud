/*    This is an example object that allows spells to be linked to it.
 *    Created by Arman September 2017.
 */

inherit "/d/Genesis/specials/examples/std_magic_obj";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

public void
create_magic_obj()
{
    set_name("grimoire");
    add_adj("leather-bound");
    add_name("_tutorial_magic_tome");
    add_name("_tutorial_item");
    set_long("This is a thin leather-bound grimoire, commonly used by aspiring " +
         "apprentice spellcasters of Greenhollow learning the basics of magic. " +
         "To see a list of spells now at your disposal while in possession of " +
         "the grimoire, use the <spells> command. You can also check what spell " +
         "effects are currently active through the <spelleffects> command. " +
         "You can also <read grimoire> to learn more about the spells it holds.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));

    add_prop(MAGIC_AM_ID_INFO,
      ({ "This is the grimoire of an apprentice of Greenhollow. It provides " +
         "the holder a handful of basic spells.\n", 20 }));

    add_prop(OBJ_S_WIZINFO, "This object holds the Genesis tutorial spells.\n");

    set_keep(1);

    set_holdable(0);
    /* Turns it into a normal spellbook */
    set_magic_spellbook(1);

    set_magic_obj_soul("/d/Genesis/specials/examples/tutorial_grimoire_spell_soul.c"); 

    set_magic_obj_effect(({ "_tutorial_light_object_", "_demonfethos_object_" }));   
    
    add_cmd_item(({"grimoire","leather-bound grimoire"}),"read",
                   "@@read_grimoire");
}

string
read_grimoire()
{
    return "\n"+
"\n"+
"         _______________________________________________   _____ \n"+
"     .-/|      ~~**~~      ~~**~~      ~~**~~           \\ /      / \n"+
"     ||||   'cast <spellname>' to cast a spell.          :      |  \n"+
"     ||||      ~~**~~      ~~**~~      ~~**~~            :      |  \n"+
"     ||||                                                :      |  \n"+
"     ||||  'illuminatus'         A spell of light.       :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spellcraft required:  Confident student       :      |  \n"+
"     ||||  Components:           None                    :      |  \n"+
"     ||||                                                :       | \n"+
"     ||||                                                :      |  \n"+
"     ||||  'aquablast'           A magical attack of     :       | \n"+
"     ||||                        scalding water.         :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spellcraft required:  Superior student        :      |  \n"+
"     ||||  Components:           broad silver leaf       :      |  \n"+
"     ||||                        (sterling leaf)         :       | \n"+
"     ||||                                                :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  'demonfethos'         A magical shield        :       | \n"+
"     ||||                        protecting the caster   :       | \n"+
"     ||||                        from demons.            :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spellcraft required:  Confident amateur       :      |  \n"+
"     ||||  Components:           gleaming silver berry   :      |  \n"+
"     ||||                        (stiltberry)            :       | \n"+
"     ||||                                                :      |  \n"+
"     ||||_______________________________________________ : _____|  \n"+
"     ||/================================================\\:/=====   \n"+
"     `-------------------------------------------------~___~----   \n"+
"\n\n";
}

public string
query_recover()
{
  return MASTER;
}

