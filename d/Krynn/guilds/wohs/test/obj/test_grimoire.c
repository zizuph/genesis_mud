/*    Spell book - cannot leave the WoHS test environment
 */

inherit "/d/Genesis/specials/examples/std_magic_obj";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"

#define MEMORISED_INVIS   "_wohs_test_did_not_know_invis"
#define MEMORISED_SCRY    "_wohs_test_did_not_know_scry"

void
check_if_in_test()
{
    set_alarm(180.0, 0.0, "do_i_dispel");
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

    if(room && file_name(room))
      if(file_name(room)[0..30] != "/d/Krynn/guilds/wohs/test/room/")
      {
         person->catch_msg("The " +TO->short()+ " dissipates! It was " +
           "nothing but an illusion!\n");
         set_alarm(0.3, 0.0, "remove_illusionary_item");
      }
      else
	set_alarm(180.0, 0.0, "do_i_dispel");

    return;
}

void
remove_illusionary_item()
{
   remove_object();
}

public void
create_magic_obj()
{
    set_name("grimoire");
    add_name("_wohs_test_grimoire");
    add_name("grimoire");
    add_adj("leather-bound");
    set_long("This is a thin leather-bound grimoire, commonly used by " +
        "aspiring apprentice spellcasters learning the basics of " +
        "magic. You could probably scribe some of the spells within " +
        "the spellbook, or cast directly from it if you have the " +
        "components.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));

    add_prop(MAGIC_AM_ID_INFO, ({ "This is an apprentice's grimoire. " +
        "It provides the holder a handful of basic spells.\n", 20 }));

    add_prop(OBJ_S_WIZINFO, "This object holds the spells that will " +
        "assist with the entry quest for the WoHS.\n");

    check_if_in_test();
    set_keep(1);
    set_holdable(0);

    /* Turns it into a normal spellbook */
    set_magic_spellbook(1);

    set_magic_obj_soul("/d/Krynn/guilds/wohs/test/obj/test_spell_soul.c"); 
    set_magic_obj_effect(({ "invisibility spell object", 
        "mirror portal object" }));   
    
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
"     ||||                                                :      |  \n"+
"     ||||            ~~*  CANTRIPS  *~~                  :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  MIRROR PORTAL         A command of activation :       | \n"+
"     ||||  'dotonobsule'         for magical mirror      :       | \n"+
"     ||||                        teleportation.          :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spell element: Water, Superior amateur        :      |  \n"+
"     ||||  Spell form: Divination, Superior amateur      :      |  \n"+
"     ||||  Components:  None                             :      |  \n"+
"     ||||                                                :       | \n"+
"     ||||                                                :      |  \n"+
"     ||||          ~~*  LESSER SPELLS  *~~               :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  DIVINE LOCATION       Scry someone's          :       | \n"+
"     ||||  'ehtahxiekiv'         location.               :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spell element: Water, Superior acolyte        :      |  \n"+
"     ||||  Spell form: Divination, Superior journeyman   :      |  \n"+
"     ||||  Components: Sargassum, bull kelp              :      |  \n"+
"     ||||                                                :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  SHADOW WALK           Cloak yourself in       :       | \n"+
"     ||||  'zhinpersvek'         shadows, becoming       :       | \n"+
"     ||||                        invisible.              :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spell element: Air, Superior journeyman       :      |  \n"+
"     ||||  Spell form: Illusion, Superior journeyman     :      |  \n"+
"     ||||  Components: Snake skin, blung                 :      |  \n"+
"     ||||                                                :      |  \n"+
"     ||||                                                :      |  \n"+
"     ||||        ~~*  ADVANCED SPELLS  *~~               :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  METEOR STORM          Exploding spheres       :       | \n"+
"     ||||  'tonashkepesk'        of stone.               :       | \n"+
"     ||||                                                :       | \n"+
"     ||||  Spell element: Earth, Superior journeyman     :      |  \n"+
"     ||||  Spell form: Conjuration, Superior craftsman   :      |  \n"+
"     ||||  Components: Gem shard, tonash potion.         :      |  \n"+
"     ||||                                                :       | \n"+
"     ||||                                                :      |  \n"+
"     ||||    PROPERTY OF THE DALTIGOTH TOWER OF HIGH     :      |  \n"+
"     ||||   SORCERY. NOT FOR REMOVAL FROM THE LIBRARY.   :      |  \n"+
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

    if((str != "tonashkepesk") && (str != "zhinpersvek") && 
       (str != "ehtahxiekiv") && (str != "dotonobsule"))
    {
        write("You do not find that spell in the grimoire to scribe.\n");
        return "";
    }  

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the " +
            "spells within the thin leather-bound grimoire.\n");
        return "";
    }

    if((str == "tonashkepesk"))
    {
        write("Advanced spells are beyond your ability to learn at " +
            "the moment.\n");
        return "";
    }

    if((str == "zhinpersvek"))
    {
        if(WOHS_MANAGER->query_scribed_spell(this_player(),"zhinpersvek"))
        {
           write("You already have zhinpersvek scribed in your " +
               "spellbook.\n");
           return "";
        }

        this_player()->add_prop(MEMORISED_INVIS, 1);
        WOHS_MANAGER->add_wohs_test_props(this_player(), MEMORISED_INVIS, 1);
    }

    if((str == "ehtahxiekiv"))
    {
        if(WOHS_MANAGER->query_scribed_spell(this_player(),"ehtahxiekiv"))
        {
           write("You already have ehtahxiekiv scribed in your " +
               "spellbook.\n");
           return "";
        }

        this_player()->add_prop(MEMORISED_SCRY, 1);
        WOHS_MANAGER->add_wohs_test_props(this_player(), MEMORISED_SCRY, 1);
    }

    if((str == "dotonobsule") && 
        WOHS_MANAGER->query_scribed_spell(this_player(),"dotonobsule"))
    {
        write("You already have that spell scribed in your spellbook.\n");
        return "";
    }

    write("You studiously copy the spell " +str+ " into your spellbook " +
        "from the thin leather-bound grimoire.\n");
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

