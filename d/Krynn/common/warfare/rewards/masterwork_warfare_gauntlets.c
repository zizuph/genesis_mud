/* 
 * Warfare masterwork gauntlets standard file for the various factions.
 * Provides resistance to warfare npc special attacks.
 *
 * Created by Theros Ironfeld in Solace.
 * Ingredients are:   40 steel coins (warfare reward item)
 *                    a silver bar (mine silver nuggets, sell nuggets,
 *                                  wait for another smith to finish and then
 *                                  buy a silver bar, bring it to Theros)
 *                    Two iron bars 
 *
 *
 * Arman Kharas, November 2018
 */
 
inherit "/std/armour";
inherit "/lib/keep";
inherit "/d/Genesis/lib/commodity";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/clubs/warfare/defs.h"
#include "/d/Krynn/common/warfare/warfare.h"
#include <cmdparse.h>

#define PLATE_AC                     40
#define CHAIN_AC                     35
#define LEATHER_AC                   30

public void   setup_warfare_armour(int level, int location, string faction);
void          add_skill_bonus(object who, int skill);

int           gLevel, gAc, gAt, *gAm, gWeight;

// Whether the gem cavity is filled (1) or empty (0)
int           crystal_one;
// Sets the possible crystal ac bonus
int           crystal_one_ac;
// Sets the possible crystal skill type
int           crystal_one_skill;
// Sets whether the crystal is skill activated
int           crystal_one_activated;
// Set the shape of the gem cavities
string        crystal_shape_one;
// Set the id of the gems 
string        crystal_id_one;
// Set the resist of the gems 
string        crystal_resist_one;
// Sets the possible crystal resist bonus
int           crystal_one_rb;

public mapping      resistance_mapping = ([ ]);

string        gFaction; 

public int
query_krynn_warfare_armour()
{
    return 1;
}

// Queries the gem id.
public string
query_crystal_id_one()
{
    return crystal_id_one;
}

// Queries whether the crystal slot if used or not.
public int
query_crystal_slot_one()
{
    return crystal_one;
}

// Queries the shape of the crystal cavities
public string
query_crystal_shape_one()
{
    return crystal_shape_one;
}

// Sets the shape of the crystal cavities
public void
set_crystal_shape_one(string str)
{
    crystal_shape_one = str;
}

// Queries whether there are any free slots available
public int
query_free_gem_slot(string shape)
{
    if(!query_crystal_slot_one() && (query_crystal_shape_one() == shape))
        return 1;

    return 0;
}

// Sets the crystal bonuses to the armour
public void
set_crystal_slot(int slot, string gem_id, string gem_shape, mixed benefit_type, mixed benefit_bonus)
{
    if(slot == 1)
    {
        crystal_one = 1;
        crystal_id_one = gem_id;
        if(benefit_type == "ac")
            crystal_one_ac = benefit_bonus;
        if(benefit_type == "skill")
        {
            crystal_one_skill = benefit_bonus;

            if(objectp(query_worn()) && !crystal_one_activated)
            {
                add_skill_bonus(TP, crystal_one_skill);
                crystal_one_activated = 1;
            }
        }
        if(benefit_type == "weight")
        {
            if(!crystal_one_activated)
                gWeight += benefit_bonus;

            crystal_one_activated = 1;
        }
        if(benefit_type == "lesser_resist")
        {
            crystal_resist_one = benefit_bonus;
            crystal_one_rb = BASIC_RESIST_BONUS;

        }
        if(benefit_type == "greater_resist")
        {
            crystal_resist_one = benefit_bonus;
            crystal_one_rb = SUPERIOR_RESIST_BONUS;

        }
    }
}

public string
query_armour_faction()
{
    return gFaction;
}

public void
set_armour_faction(string str)
{
    gFaction = str;
}

varargs void
set_armour_level(int level = 0, int location = A_ARMS, string faction = "free")
{
    if ( !level )
        gLevel = 0;
    else
        gLevel = level;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 2)
        gLevel = 2;

    if ( !location )
        gAt = A_ARMS;
    else
        gAt = location;

    if ( !faction )
        gFaction = "free";
    else
        gFaction = faction;

    if (!gWeight)
        gWeight = 0;

    if (gWeight < 0)
        gLevel = 0;
    if (gWeight > 3)
        gWeight = 3;

    if (!crystal_one)
        crystal_one = 0;

    if (!crystal_one_ac)
        crystal_one_ac = 0;

    if (!crystal_one_skill)
        crystal_one_skill = 0;

    if (!crystal_one_activated)
        crystal_one_activated = 0;

    if (!crystal_shape_one)
        crystal_shape_one = "tear";

    if (crystal_one_ac > 5)
        crystal_one_ac = 5;

    if (crystal_one_ac < 0)
        crystal_one_ac = 0;
        
    setup_warfare_armour(gLevel, gAt, gFaction);
}

public void
setup_warfare_armour(int level, int location, string faction)
{
    if(gLevel == 0)
        gAc = PLATE_AC + crystal_one_ac;
    else if(gLevel == 1)
        gAc = CHAIN_AC + crystal_one_ac;
    else
        gAc = LEATHER_AC + crystal_one_ac;

    gAm = ({-2, 3, -1});

    if(!query_commodity_name())
        set_commodity_name("mw pgauntlet");

    set_commodity_value(F_VALUE_ARMOUR(gAc), 0);
}

string
warfare_armour_short()
{
    string short;

    switch(gLevel)
    { 
        case 0:
            short = "plate gauntlets";
            add_name("gauntlets");
            add_adj("steel");
            add_adj("plate");
            add_adj("metal");
            add_adj("masterwork");
            set_crystal_shape_one("tear");
        break; 
        case 1:
            short = "chain gloves";
            add_name("gloves");
            add_adj("steel");
            add_adj("chain");
            add_adj("metal");
            add_adj("masterwork");
            remove_adj("plate");
            remove_name("gauntlets");
            set_crystal_shape_one("tear");
        break;
        case 2:
            short = "leather gloves";
            add_name("gloves");
            add_name("armour");
            add_adj("leather");
            add_adj("masterwork");
            remove_adj("steel");
            remove_adj("metal");
            remove_adj("plate");
            remove_name("gauntlets");
            set_crystal_shape_one("oval");
        break;
        default:
            short = "plate gauntlets";
            add_name("gauntlets");
            add_adj("steel");
            add_adj("plate");
            add_adj("metal");
            add_adj("masterwork");
            set_crystal_shape_one("tear");
        break;
     }

    return short;
}

string
query_crystal_slot_desc()
{
    string cav_desc, link_desc;

    if(!crystal_one)
    {
        if(gLevel == 0) //plate
            return "Embedded in the dorsum of the gauntlet, circled by " +
            "runes inlayed by silver, is a dark empty cavity shaped like " +
            "a teardrop.";
        else if(gLevel == 1) // chain
            return "Attached to the the dorsum of the glove, circled by " +
            "runes inlayed by silver, is an empty clasp shaped to hold " +
            "something teardrop-shaped.";
        else // leather
            return "Attached to the the dorsum of the glove, circled by " +
            "embroidered runes of silver, is an empty clasp shaped to hold " +
            "something oval-shaped.";
    }
    else
    {
        string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_one][3];  
        link_desc = LANG_ADDART(gem_desc1);         

        if(gLevel == 0)
            return "Embedded in the dorsum of the gauntlet, circled by " +
            "runes inlayed by silver, is " +link_desc+ ".";
        else if(gLevel == 1)
            return "Attached to the the dorsum of the glove, circled by " +
            "runes inlayed by silver, is " +link_desc+ ".";
        else
            return "Attached to the the dorsum of the glove, circled by " +
            "embroidered runes of silver, is " +link_desc+ ".";
    }

    return "Hmm... bugged out.";
}

string
warfare_armour_long()
{
    string long;
    string faction = gFaction;

    if(faction == "pot")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0:
                  long = "This is a pair of plate gauntlets of dark steel. " +
                      query_crystal_slot_desc()+ "\n";
                  set_short("pair of dark " + short);
                  set_pshort("pairs of dark " + short);
                  add_adj("dark");
                  break;
               case 1:
                  long = "This is a pair of gloves of dark steel chains. " +
                      query_crystal_slot_desc()+ "\n";
                  set_short("pair of dark " + short);
                  set_pshort("pairs of dark " + short);
                  add_adj("dark");
                  break;
               case 2:
                  long = "This is a pair of dark leather gloves. " +
                      query_crystal_slot_desc()+ "\n";
                  set_short("pair of dark " + short);
                  set_pshort("pairs of dark " + short);
                  add_adj("dark");
                  break;
               default:
                  long = "This is a pair of plate gauntlets of dark steel. " +
                      query_crystal_slot_desc()+ "\n";
                  set_short("pair of dark " + short);
                  set_pshort("pairs of dark " + short);
                  add_adj("dark");
                  break;
            }
    }
    else if(faction == "blue" || faction == "red" || faction == "white" ||
        faction == "black" || faction == "green")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0:
                  long = "This is a pair of steel gauntlets, stained " +
                      faction+ " to distinguish the wearer as a supporter " +
                      "of the " +capitalize(faction)+ " Dragonarmy. " +
                      query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + faction + " " + short);
                  set_pshort("pairs of " + faction + " " + short);
                  add_adj(faction);
                  break;
               case 1:
                  long = "This is a pair of chain gloves, stained " +
                      faction+ " to distinguish the wearer as a supporter " +
                      "of the " +capitalize(faction)+ " Dragonarmy. " +
                      query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + faction + " " + short);
                  set_pshort("pairs of " + faction + " " + short);
                  break;
               case 2:
                  long = "This is a pair of leather gloves, stained " +
                      faction+ " to distinguish the wearer as a supporter " +
                      "of the " +capitalize(faction)+ " Dragonarmy. " +
                      query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + faction + " " + short);
                  set_pshort("pairs of " + faction + " " + short);
                  break;
               default:
                  long = "This is a pair of steel gauntlets, stained " +
                      faction+ " to distinguish the wearer as a supporter " +
                      "of the " +capitalize(faction)+ " Dragonarmy. " +
                      query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + faction + " " + short);
                  set_pshort("pairs of " + faction + " " + short);
                  add_adj(faction);
                  break;
            }
    }
    else if(faction == "knights")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "in Solamnic fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of solamnic plate gauntlets");
                  set_pshort("pairs of solamnic plate gauntlets");
                  add_adj("solamnic");
                  break;
               case 1:
                  long = "This is a pair of chain gloves, designed " +
                      "in Solamnic fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of solamnic chain gloves");
                  set_pshort("pairs of solamnic chain gloves");
                  add_adj("solamnic");
                  break;
               case 2:
                  long = "This is a pair of leather gloves, designed " +
                      "in Solamnic fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of solamnic leather gloves");
                  set_pshort("pairs of solamnic leather gloves");
                  add_adj("solamnic");
                  break;
               default:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "in Solamnic fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of solamnic plate gauntlets");
                  set_pshort("pairs of solamnic plate gauntlets");
                  add_adj("solamnic");
                  break;
            }
    }
    else if(faction == "neidar")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "in dwarven fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of dwarven plate gauntlets");
                  set_pshort("pairs of dwarven plate gauntlets");
                  add_adj("dwarven");
                  break;
               case 1:
                  long = "This is a pair of chain gloves, designed " +
                      "in dwarven fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of dwarven chain gloves");
                  set_pshort("pairs of dwarven chain gloves");
                  add_adj("dwarven");
                  break;
               case 2:
                  long = "This is a pair of leather gloves, designed " +
                      "in dwarven fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of dwarven leather gloves");
                  set_pshort("pairs of dwarven leather gloves");
                  add_adj("dwarven");
                  break;
               default:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "in dwarven fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of dwarven plate gauntlets");
                  set_pshort("pairs of dwarven plate gauntlets");
                  add_adj("dwarven");
                  break;
            }
    }
    else if(faction == "qualinesti")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "in elven fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of elven plate gauntlets");
                  set_pshort("pairs of elven plate gauntlets");
                  add_adj("elven");
                  break;
               case 1:
                  long = "This is a pair of chain gloves, designed " +
                      "in elven fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of elven chain gloves");
                  set_pshort("pairs of elven chain gloves");
                  add_adj("elven");
                  break;
               case 2:
                  long = "This is a pair of leather gloves, designed " +
                      "in elven fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of elven leather gloves");
                  set_pshort("pairs of elven leather gloves");
                  add_adj("elven");
                  break;
               default:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "in elven fashion. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of elven plate gauntlets");
                  set_pshort("pairs of elven plate gauntlets");
                  add_adj("elven");
                  break;
            }
    }

    else if(faction == "free")
    {
        string short = query_short();

            switch(gLevel)
            {  
               case 0:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "by a master smith. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + short);
                  set_pshort("pairs of " + short);
                  break;
               case 1:
                  long = "This is a pair of chain gloves, designed " +
                      "by a master smith. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + short);
                  set_pshort("pairs of " + short);
                  break;
               case 2:
                  long = "This is a pair of leather gloves, designed " +
                      "by a master smith. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + short);
                  set_pshort("pairs of " + short);
                  break;
               default:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "by a master smith. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + short);
                  set_pshort("pairs of " + short);
                  break;
            }
    }

    else
    {
        string short = query_short();

            switch(gLevel)
            {  

               case 0:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "by a master smith. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + short);
                  set_pshort("pairs of " + short);
                  break;
               case 1:
                  long = "This is a pair of chain gloves, designed " +
                      "by a master smith. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + short);
                  set_pshort("pairs of " + short);
                  break;
               case 2:
                  long = "This is a pair of leather gloves, designed " +
                      "by a master smith. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + short);
                  set_pshort("pairs of " + short);
                  break;
               default:
                  long = "This is a pair of steel plate gauntlets, designed " +
                      "by a master smith. " +query_crystal_slot_desc()+ "\n";
                  set_short("pair of " + short);
                  set_pshort("pairs of " + short);
                  break;
            }
    }

    return long;
}

public void
create_warfare_armour()
{

    if ( !strlen(gFaction) )
        set_armour_level();

}

void
add_masterwork_magic_props()
{
    int gem_total = (crystal_one_ac);
    int magic_value = gem_total * 3; 
    string magic_info_string = "";

    if(crystal_one)
    {
        magic_info_string += "Inserted into the " +short()+ " is ";

        string gem_desc = MASTERWORK_GEM_PROPS[crystal_id_one][3];  
        gem_desc = LANG_ADDART(gem_desc); 
        magic_info_string += gem_desc;

        string gem_benefit = MASTERWORK_GEM_PROPS[crystal_id_one][1];

        if(gem_benefit == "ac")
            magic_info_string += ", magically warding the armour from breaches.";
        else if(gem_benefit == "lesser_resist" || gem_benefit == "greater_resist")
        {
            string gem_resist_benefit = MASTERWORK_GEM_PROPS[crystal_id_one][2];
            magic_info_string += ", providing magical resistance to " +
                gem_resist_benefit+ ".";
        }
        else if(gem_benefit == "skill")
            magic_info_string += ", magically enhancing the wearer's skills.";
        else if(gem_benefit == "special")
            magic_info_string += ", providing the wearer with magical " +
                "enhancement when the gemstone is pressed.";
        else if(gem_benefit == "weight")
            magic_info_string += ", magically reducing the weight of the " +
                "armour.";
    }        

    add_prop(MAGIC_AM_ID_INFO, ({ "This " +short()+ " is a beautifully " +
        "crafted piece of armour, designed to be able to insert magical " +
        "augmentation stones in to it and enhancing it with magic. " +
        magic_info_string + "\n", 25 }));

    add_prop(MAGIC_AM_MAGIC, ({ magic_value, "abjuration" }));

    add_prop(OBJ_S_WIZINFO, "This armour has been enchanted by having " +
        "up to three warfare reward gems inserted in to it. Gem " +
        "code can be found at /d/Krynn/common/warfare/rewards/\n");
}

string
cavity_armour_desc()
{
    string cavity_string, gem_type_string, cav_type1;
    string s1 = query_crystal_shape_one();

    if(gLevel < 1)
    {
        cav_type1 = "cavity";
    }
    else
    {
        cav_type1 = "clasp";
    }    

    if (!strlen(crystal_id_one))
        cavity_string =  "This " +cav_type1+ " has been deliberately " +
            "designed by a master smith to allow the insertion of " +
            "augmentation crystals of similar shape - in this " +
            "case " +s1+ " - providing a " +
            "magical effect to the armour when affixed.";
    else
        cavity_string = "";

    return query_crystal_slot_desc() + " " + cavity_string + "\n";
}

public void
update_warfare_armour()
{
    if(strlen(crystal_id_one) > 1)
    {
        string gem_shape = MASTERWORK_GEM_PROPS[crystal_id_one][0];
        string benefit_type = MASTERWORK_GEM_PROPS[crystal_id_one][1];
        int benefit_bonus = MASTERWORK_GEM_PROPS[crystal_id_one][2];

        set_crystal_slot(1, crystal_id_one, gem_shape, benefit_type,
           benefit_bonus);
    }

    set_name("armour");
    set_short(warfare_armour_short());
    set_long(warfare_armour_long());

    // need to set for commodity hooks to work with plural_short()
    // set_pshort(short() + "s");

    string s1 = query_crystal_shape_one();

    if(gLevel < 1)
        add_item(({ s1 +"-shaped cavities", s1+ "drop shaped cavities", 
            "cavities", s1+ "drop cavities", "cavity", s1+ "drop-shaped cavity",
            "runes", "silver-inlay runes", "dark empty cavities", "empty cavities" }),
            cavity_armour_desc());
    else
        add_item(({ s1 +"-shaped clasps", s1+ "drop shaped clasps", 
            "clasps", s1+ "drop clasp", "clasp", s1+ "drop-shaped clasp",
            "runes", "silver-inlay runes", "dark empty cavities", "empty cavities" }),
            cavity_armour_desc());
      
    set_ac(gAc);
    set_at(A_HANDS | gAt);
    set_am(gAm);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(gAc) + random(20) - 10);

    int weight_mod = 4 - min(3, gWeight);
    // WARFARE_DEBUG("Weight mod: " +weight_mod);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(gAc, gAt) *
        weight_mod / 4 );

    if(crystal_one)
        add_masterwork_magic_props();

    if (objectp(query_worn()))
        query_worn()->update_armour(this_object());
}

void
create_armour()
{
    create_warfare_armour();
    update_warfare_armour();
    set_af(this_object());
}


varargs mixed
query_magic_protection(string prop, object protectee = previous_object()) 
{
    if ( protectee == query_worn() )
    {
       int resist_elem = crystal_one_rb; // The resist bonus  
       int res_water, res_fire, res_death, res_life, res_air, 
           res_earth, res_poison, res_cold;     

        if(strlen(crystal_resist_one))
        {
            switch (crystal_resist_one)
            {
                case "water":
                    res_water += crystal_one_rb;
                break;
                case "fire":
                    res_fire += crystal_one_rb;
                break;
                case "death":
                    res_death += crystal_one_rb;
                break;
                case "life":
                    res_life += crystal_one_rb;
                break;
                case "air":
                    res_air += crystal_one_rb;
                break;
                case "earth":
                    res_earth += crystal_one_rb;
                break;
                case "poison":
                    res_poison += crystal_one_rb;
                break;
                case "cold":
                    res_cold += crystal_one_rb;
                break;
            }
        }

        if(res_water)
            resistance_mapping += ([ MAGIC_I_RES_WATER : res_water ]);
        if(res_fire)
            resistance_mapping += ([ MAGIC_I_RES_FIRE : res_fire ]);
        if(res_death)
            resistance_mapping += ([ MAGIC_I_RES_DEATH : res_death ]);
        if(res_life)
            resistance_mapping += ([ MAGIC_I_RES_LIFE : res_life ]);
        if(res_air)
            resistance_mapping += ([ MAGIC_I_RES_AIR : res_air ]);
        if(res_earth)
            resistance_mapping += ([ MAGIC_I_RES_EARTH : res_earth ]);
        if(res_poison)
            resistance_mapping += ([ MAGIC_I_RES_POISON : res_poison ]);
        if(res_cold)
            resistance_mapping += ([ MAGIC_I_RES_COLD : res_cold ]);

        if (resistance_mapping[prop])
        {
            return ({ resistance_mapping[prop], 1 });
        }

        return ::query_magic_protection(prop, protectee);

    }
    else
    {
        return ::query_magic_protection(prop, protectee); 
    }
}



public int 
warfare_mitigation() 
{ 
    return 5; 
}

void
add_skill_bonus(object who, int skill)
{
   who->set_skill_extra(skill, who->query_skill_extra(skill) +
       MASTERWORK_SKILL_BONUS);
   return;
}

void
remove_skill_bonus(object who, int skill)
{

   who->set_skill_extra(skill, who->query_skill_extra(skill) - 
       MASTERWORK_SKILL_BONUS);
   return;
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    int resistance = warfare_mitigation();

    if(crystal_one && (query_crystal_shape_one() == "oval"))
    {
        // while zero is technically a skill number, it will
        // cause errors if we allow it
        if(!crystal_one_activated && crystal_one_skill)
        {
            add_skill_bonus(TP, crystal_one_skill);
            crystal_one_activated = 1;
        }
    }

    TP->add_prop(WARFARE_ARMOUR_PROP, resistance);
    TP->add_magic_effect(TO);

    return 0;
} /* wear */

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
mixed
remove(object obj)
{
    int resistance = warfare_mitigation();

    if(crystal_one && (query_crystal_shape_one() == "oval"))
    {
        if(crystal_one_activated && crystal_one_skill)
        {
            remove_skill_bonus(TP, crystal_one_skill);
            crystal_one_activated = 0;
        }
    }

    if(TP->query_prop(WARFARE_ARMOUR_PROP) <= resistance)
        TP->remove_prop(WARFARE_ARMOUR_PROP);
    else
        TP->add_prop(WARFARE_ARMOUR_PROP, 
            TP->query_prop(WARFARE_ARMOUR_PROP) - resistance);

    TP->remove_magic_effect(TO);
    return 0;
} /* remove */

int
insert_gem(string str)
{
    string gem, armour;
    mixed  *oblist,
           *armours;
    object * item;
    object player = this_player();
    string cavity_desc;

    if(gLevel > 0)
        cavity_desc = "clasp";
    else
        cavity_desc = "cavity"; 

    if (!str)
    {
        notify_fail("Insert what?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[the] %s 'into' [the] %s", gem, armour))
    {
        notify_fail("Insert <what> into <what>?\n");
        return 0;
    }

    if (!sizeof(oblist = FIND_STR_IN_ARR(gem, all_inventory(player))))
    {
        notify_fail("You possess no " + gem + ".\n");
        return 0;
    }

    if (!sizeof(armours = FIND_STR_IN_ARR(armour, all_inventory(player))))
    {
        notify_fail("You possess no " + armour + ".\n");
        return 0;
    }

    if (!IN_ARRAY(this_object(), armours))
    {
        // WARFARE_DEBUG("armour doesn't equal this object");
        return 0; 
    }

    if(crystal_one)
    {
        notify_fail("There is already an augmentation stone inserted " +
            "in to your " +short()+ ". You cannot put any more in!\n");
        return 0;
    }

    string *gem_array = filter(m_indexes(MASTERWORK_GEM_PROPS), 
        &call_other(oblist[0], "id",));

    if(!sizeof(gem_array))
    {
        notify_fail("The " +oblist[0]->query_short()+ " is the wrong " +
            "shape to insert into your " +short()+ ".\n");
        return 0;
    }

    string gem_id = gem_array[0];
    string gem_shape = MASTERWORK_GEM_PROPS[gem_id][0];
    string benefit_type = MASTERWORK_GEM_PROPS[gem_id][1];
    int benefit_bonus = MASTERWORK_GEM_PROPS[gem_id][2];   

    // WARFARE_DEBUG("Id: "+gem_id+ ", shape: " +gem_shape+
    //    ", free slot?: " +query_free_gem_slot(gem_shape));

    if (!query_free_gem_slot(gem_shape))
    {
        string spare_slot1;

        if(query_free_gem_slot("tear"))
            spare_slot1 = "tear";
        if(query_free_gem_slot("oval"))
            spare_slot1 = "oval";

        player->catch_tell("The " +oblist[0]->query_short()+ " is the " +
            "wrong shape to insert into your " +short()+ ". You need " +
            LANG_ADDART(spare_slot1) + " shaped crystal to insert " +
            "in to your armour.\n");
        return 1;
    }

    int gem_slot = query_free_gem_slot(gem_shape);
    string ward_type, chest_type;

    if(query_free_gem_slot("tear"))
        ward_type = "wards of protection";
    else
        ward_type = "enhancement magics";

    chest_type = "on the dorsum of";

    set_crystal_slot(gem_slot, gem_id, gem_shape, benefit_type, benefit_bonus);

    player->catch_tell("You insert " +oblist[0]->short()+ " into "+
        "the " +gem_shape+ "-shaped " +cavity_desc+ " " +chest_type+
        " your " +short()+ ". The silvery runes around the " +
        oblist[0]->query_short()+ " glow as it locks in to place and " +
        ward_type+ " are activated.\n");

    tell_room(environment(player), QCTNAME(player)+ " inserts " + 
        oblist[0]->short()+ " into " +HIS(player)+ " " +query_short()+ ".\n", 
        ({ player }), player);

    setup_warfare_armour(gLevel, gAt, gFaction);
    update_warfare_armour();
    oblist[0]->reduce_heap_size();
    
    return 1;
}

void
init()
{
    ::init();
    add_action(insert_gem, "insert");
    add_action(insert_gem, "affix");
}

void 
init_recover(string arg)
{
    // WARFARE_DEBUG("Recover string: " +arg);

    string *a = explode(arg,"&&");
    gLevel = atoi(a[1]);
    gAc = atoi(a[2]);
    gAt = atoi(a[3]);
    gFaction = (a[4]);
    crystal_id_one = (a[5]);
    init_arm_recover(a[0]);
    update_warfare_armour();
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + gLevel + "&&" + 
        gAc + "&&" + gAt + "&&" + gFaction + "&&" + crystal_id_one;
}