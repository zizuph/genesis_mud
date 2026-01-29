/* 
 * Warfare masterwork standard bow file for the various factions.
 *
 * Created by Theros Ironfeld in Solace.
 * Ingredients are:   100 steel coins (warfare reward item)
 *                    a silver bar (mine silver nuggets, sell nuggets,
 *                                  wait for another smith to finish and then
 *                                  buy a silver bar, bring it to Theros)
 *                    Eight iron bars 
 *                    Five leather scraps
 *
 *
 * Arman Kharas, November 2018
 */
 
inherit "/std/bow";
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

public void   setup_warfare_weapon(int level, int hand, string faction);
void          add_skill_bonus(object who, int skill);

int           gLevel, gHit, gPen, gHand, gWeight;

// Whether the gem cavity is filled (1) or empty (0)
int           crystal_one, crystal_two, crystal_three;
// Sets the possible crystal hit bonus
int           crystal_one_hit, crystal_two_hit, crystal_three_hit;
// Sets the possible crystal pen bonus
int           crystal_one_pen, crystal_two_pen, crystal_three_pen;
// Sets the possible crystal skill type
int           crystal_one_skill, crystal_two_skill, crystal_three_skill;
// Sets whether the crystal is skill activated
int           crystal_one_activated, crystal_two_activated, 
              crystal_three_activated;
// Set the shape of the gem cavities
string        crystal_shape_one, crystal_shape_two, crystal_shape_three;
// Set the id of the gems 
string        crystal_id_one, crystal_id_two, crystal_id_three;

string        gFaction; 

public int
query_krynn_warfare_weapon()
{
    return 1;
}

// Queries whether the crystal slot if used or not.
public int
query_crystal_slot_one()
{
    return crystal_one;
}

public int
query_crystal_slot_two()
{
    return crystal_two;
}

public int
query_crystal_slot_three()
{
    return crystal_three;
}

// Queries the shape of the crystal cavities
public string
query_crystal_shape_one()
{
    return crystal_shape_one;
}

public string
query_crystal_shape_two()
{
    return crystal_shape_two;
}

public string
query_crystal_shape_three()
{
    return crystal_shape_three;
}

// Sets the shape of the crystal cavities
public void
set_crystal_shape_one(string str)
{
    crystal_shape_one = str;
}

public void
set_crystal_shape_two(string str)
{
    crystal_shape_two = str;
}

public void
set_crystal_shape_three(string str)
{
    crystal_shape_three = str;
}

// Queries whether there are any free slots available
public int
query_free_gem_slot(string shape)
{
    if(!query_crystal_slot_one() && (query_crystal_shape_one() == shape))
        return 1;

    if(!query_crystal_slot_two() && (query_crystal_shape_two() == shape))
        return 2;

    if(!query_crystal_slot_three() && (query_crystal_shape_three() == shape))
        return 3;

    return 0;
}

// Sets the crystal bonuses to the weapon
public void
set_crystal_slot(int slot, string gem_id, string gem_shape, mixed benefit_type, mixed benefit_bonus)
{
    if(slot == 1)
    {
        crystal_one = 1;
        crystal_id_one = gem_id;

        if(benefit_type == "hit")
            crystal_one_hit = benefit_bonus;
        if(benefit_type == "pen")
            crystal_one_pen = benefit_bonus;
        if(benefit_type == "hit-pen")
        {
            crystal_one_hit = benefit_bonus;
            crystal_one_pen = benefit_bonus;
        }
        if(benefit_type == "skill")
        {
            crystal_one_skill = benefit_bonus;

            if(objectp(query_wielded()) && !crystal_one_activated)
            {
                add_skill_bonus(query_wielded(), crystal_one_skill);
                crystal_one_activated = 1;
            }
        }
        if(benefit_type == "weight")
        {
            if(!crystal_one_activated)
                gWeight += benefit_bonus;

            crystal_one_activated = 1;
        }

    }
    else if(slot == 2)
    {
        crystal_two = 1;
        crystal_id_two = gem_id;

        if(benefit_type == "hit")
            crystal_two_hit = benefit_bonus;
        if(benefit_type == "pen")
            crystal_two_pen = benefit_bonus;
        if(benefit_type == "hit-pen")
        {
            crystal_two_hit = benefit_bonus;
            crystal_two_pen = benefit_bonus;
        }
        if(benefit_type == "skill")
        {
            crystal_two_skill = benefit_bonus;

            if(objectp(query_wielded()) && !crystal_two_activated)
            {
                add_skill_bonus(query_wielded(), crystal_two_skill);
                crystal_two_activated = 1;
            }
        }
        if(benefit_type == "weight")
        {
            if(!crystal_two_activated)
               gWeight += benefit_bonus;

            crystal_two_activated = 1;
        }
    }
    else if(slot == 3)
    {
        crystal_three = 1;
        crystal_id_three = gem_id;

        if(benefit_type == "hit")
            crystal_three_hit = benefit_bonus;
        if(benefit_type == "pen")
            crystal_three_pen = benefit_bonus;
        if(benefit_type == "hit-pen")
        {
            crystal_three_hit = benefit_bonus;
            crystal_three_pen = benefit_bonus;
        }
        if(benefit_type == "skill")
        {
            crystal_three_skill = benefit_bonus;

            if(objectp(query_wielded()) && !crystal_three_activated)
            {
                add_skill_bonus(query_wielded(), crystal_three_skill);
                crystal_three_activated = 1;
            }
        }
        if(benefit_type == "weight")
        {
            if(!crystal_three_activated)
               gWeight += benefit_bonus;

            crystal_three_activated = 1;
        }
    }
}

public string
query_weapon_faction()
{
    return gFaction;
}

public void
set_weapon_faction(string str)
{
    gFaction = str;
}

varargs void
set_weapon_level(int level = 0, int hand = W_BOTH, string faction = "free")
{
    if ( !level )
        gLevel = 0;
    else
        gLevel = level;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 0)
        gLevel = 0;


    if ( !hand )
        gHand = W_BOTH;
    else
        gHand = hand;

    if ( !faction )
        gFaction = "free";
    else
        gFaction = faction;

    if (!gHit)
        if(gHand == W_ANYH)
            gHit = 35;
        else
            gHit = 40;

    if (!gPen)
        if(gHand == W_ANYH)
            gPen = 35;
        else
            gPen = 40;

    if (!gWeight)
        gWeight = 0;

    if (gWeight < 0)
        gLevel = 0;
    if (gWeight > 3)
        gWeight = 3;

    if (!crystal_one)
        crystal_one = 0;
    if (!crystal_two)
        crystal_two = 0;

    if (!crystal_one_skill)
        crystal_one_skill = 0;
    if (!crystal_two_skill)
        crystal_two_skill = 0;

    if (!crystal_one_activated)
        crystal_one_activated = 0;
    if (!crystal_two_activated)
        crystal_two_activated = 0;

    if (!crystal_three_activated)
        crystal_three_activated = 0;
    if (!crystal_three_activated)
        crystal_three_activated = 0;

    if (!crystal_shape_one)
        crystal_shape_one = "ellipse";
    if (!crystal_shape_two)
        crystal_shape_two = "ellipse";
    if (!crystal_shape_three)
        crystal_shape_three = "ellipse";
        
    setup_warfare_weapon(gLevel, gHand, gFaction);
}

public void
setup_warfare_weapon(int level, int hand, string faction)
{
    if(hand == W_ANYH)
    {
        gHit = 35 + crystal_one_hit + crystal_two_hit + crystal_three_hit;
        gPen = 35 + crystal_one_pen + crystal_two_pen + crystal_three_pen; 

        if(gHit > 50)
            gHit = 50;
        if(gPen > 50)
            gPen = 50;
    }
    else
    {
        gHit = 40 + crystal_one_hit + crystal_two_hit + crystal_three_hit; 
        gPen = 40 + crystal_one_pen + crystal_two_pen + crystal_three_pen; 

        if(gHit > 60)
            gHit = 60; 
        if(gPen > 60)
            gPen = 60; 
    }

    // WARFARE_DEBUG("Hit: " +gHit + ", Pen: " +gPen);

    if(!query_commodity_name())
        set_commodity_name("mw bow");

    set_commodity_value(F_VALUE_WEAPON(40, 40));
}

string
warfare_weapon_short()
{
    string short;

    short = "ironwood greatbow";
    add_name("bow");
    add_name("greatbow");
    add_adj("masterwork");
    set_crystal_shape_one("ellipse");
    set_crystal_shape_two("ellipse");
    set_crystal_shape_three("ellipse");

    return short;
}

string
query_crystal_slot_desc()
{
    string cav_desc, link_desc;

    if(!crystal_one && !crystal_two && !crystal_three)
    {
        return "Along the riser just below the grip of the bow you " +
            "notice three dark empty cavities, shaped to hold ellipse " +
            "shaped crystals, linked by runes inlayed with silver.";
    }

    if((!crystal_two && !crystal_three) || (!crystal_one && !crystal_three) ||
       (!crystal_one && !crystal_two))
    {
       string gem_desc1;

        if((!crystal_two && !crystal_three))
            gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_one][3];
        else if((!crystal_one && !crystal_three))
            gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_two][3];
        else
            gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_three][3];

        return "Along the riser just below the grip of the bow you notice " +
            "it is inset with " +LANG_ADDART(gem_desc1)+ ", linked by " +
            "silver-inlay runes to two dark empty cavities.";
    }

    if(!crystal_one || !crystal_two || !crystal_three)
    {
        if(!crystal_one)
        {
            string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_two][3];
            string gem_desc2 = MASTERWORK_GEM_PROPS[crystal_id_three][3];
            if(gem_desc1 == gem_desc2)
                link_desc = "two " +gem_desc1+ "s, ";
            else
                link_desc = LANG_ADDART(gem_desc1)+ " and " +
                LANG_ADDART(gem_desc2)+ ", ";
        }

        if(!crystal_two)
        {
            string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_one][3];
            string gem_desc2 = MASTERWORK_GEM_PROPS[crystal_id_three][3];
            if(gem_desc1 == gem_desc2)
                link_desc = "two " +gem_desc1+ "s, ";
            else
                link_desc = LANG_ADDART(gem_desc1)+ " and " +
                LANG_ADDART(gem_desc2)+ ", ";
        }

        if(!crystal_three)
        {
            string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_two][3];
            string gem_desc2 = MASTERWORK_GEM_PROPS[crystal_id_one][3];
            if(gem_desc1 == gem_desc2)
                link_desc = "two " +gem_desc1+ "s, ";
            else
                link_desc = LANG_ADDART(gem_desc1)+ " and " +
                LANG_ADDART(gem_desc2)+ ", ";
        }

        return "Along the riser just below the grip of the bow " +
            "you notice it is inset with " + link_desc +
            "linked by silver-inlay runes to an empty cavity.";

    }

    string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_one][3];
    string gem_desc2 = MASTERWORK_GEM_PROPS[crystal_id_two][3];
    string gem_desc3 = MASTERWORK_GEM_PROPS[crystal_id_three][3];

    if((gem_desc1 == gem_desc2) && (gem_desc1 == gem_desc3))
        link_desc = "three " +gem_desc1+ "s";
    else if(gem_desc1 == gem_desc2)
        link_desc = "two " +gem_desc1+ "s and " +LANG_ADDART(gem_desc3);
    else
        link_desc = LANG_ADDART(gem_desc1)+ ", " +LANG_ADDART(gem_desc2)+ 
        " and " +LANG_ADDART(gem_desc3);

    return "Along the riser just below the grip of the bow you " +
        "notice it is inset with " + link_desc + " linked together " +
        "by silver-inlay runes.";

}

string
warfare_weapon_long()
{
    string long;
    string faction = gFaction;

    if(faction == "pot")
    {
        string short = query_short();

        long = "This is a greatbow masterfully crafted from the wood " +
            "of the black locust tree found in the mountains north of " +
            "Sanction, laminated together with horn and sinew to " +
            "provide incredible energy and power. Larger and " +
            "more powerful than a longbow, this greatbow has been " +
            "carved with disturbing images of the Dark Temptress. " +
            query_crystal_slot_desc()+ "\n";
        set_short("black locust greatbow");
        remove_adj("ironwood");
        add_adj("black");
        add_adj("locust");

            
    }
    else if(faction == "blue" || faction == "red" || faction == "white" ||
        faction == "black" || faction == "green")
    {
        string short = query_short();

        long = "This is a greatbow masterfully crafted from the wood " +
            "of the black locust tree found in the mountains north of " +
            "Sanction, laminated together with horn and sinew to " +
            "provide incredible energy and power. Larger and " +
            "more powerful than a longbow, this greatbow has carvings " +
            "of " +faction+ " dragons entwined around the limbs of " +
            "the bow. " +
            query_crystal_slot_desc()+ "\n";
        set_short("black locust greatbow");
        remove_adj("ironwood");
        add_adj("black");
        add_adj("locust");

            
    }
    else if(faction == "knights")
    {
        string short = query_short();

        long = "This is a greatbow masterfully crafted " +
            "from wood of the Ergothian red cedar, laminated together " +
            "with horn and sinew to provide incredible energy and power. " +
            "Expensive and difficult to make, these bows are found " +
            "only in the hands of the best Solamnian marksmen " +
            "or richest knights and nobles. " +
            query_crystal_slot_desc()+ "\n";
        set_short("red cedar greatbow");
        remove_adj("ironwood");
        add_adj("red");
        add_adj("cedar");            

    }
    else if(faction == "neidar")
    {
        string short = query_short();

        long = "This is a greatbow masterfully crafted " +
            "from wood of the Kharolis red cedar, laminated together " +
            "with horn and sinew to provide incredible energy and power. " +
            "These bows are greatly prized by horse barbarians and archers " +
            "from across Krynn for their sturdiness and effectiveness. " +
            query_crystal_slot_desc()+ "\n";
        set_short("red cedar greatbow");
        remove_adj("ironwood");
        add_adj("red");
        add_adj("cedar");
            
    }
    else if(faction == "qualinesti")
    {
        string short = query_short();

        long = "This is a greatbow masterfully crafted " +
            "from wood of Qualinesti ash, laminated together " +
            "with horn and sinew to provide incredible energy and power. " +
            "Expensive and difficult to make, these bows are rarely " +
            "found in the hands of any other than elven archers or " +
            "hunters. " +
            query_crystal_slot_desc()+ "\n";
        set_short("elven ash greatbow");
        remove_adj("ironwood");
        add_adj("elven");
        add_adj("ash");            

    }
    else if(faction == "free")
    {

        string short = query_short();

        long = "This is a greatbow masterfully crafted " +
            "from wood of the Kharolis red cedar, laminated together " +
            "with horn and sinew to provide incredible energy and power. " +
            "These bows are greatly prized by horse barbarians and archers " +
            "from across Krynn for their sturdiness and effectiveness. " +
            query_crystal_slot_desc()+ "\n";
        set_short("red cedar greatbow");
        remove_adj("ironwood");
        add_adj("red");
        add_adj("cedar");
            
    }
    else
    {
        string short = query_short();

        long = "This is a greatbow masterfully crafted " +
            "from wood of the Kharolis red cedar, laminated together " +
            "with horn and sinew to provide incredible energy and power. " +
            "These bows are greatly prized by horse barbarians and archers " +
            "from across Krynn for their sturdiness and effectiveness. " +
            query_crystal_slot_desc()+ "\n";
        set_short("greatbow");          

    }

    return long;
}

public void
create_warfare_weapon()
{

    if ( !strlen(gFaction) )
        set_weapon_level();

}

void
add_masterwork_magic_props()
{
    int magic_value = 25; 
    string magic_info_string = "";
    int inserted_gems = crystal_one + crystal_two;

    magic_info_string += "Inserted into the " +short()+ " is ";

    if(crystal_one)
    {
        string gem_desc = MASTERWORK_GEM_PROPS[crystal_id_one][3];  
        gem_desc = LANG_ADDART(gem_desc); 
        magic_info_string += gem_desc;

        string gem_benefit = MASTERWORK_GEM_PROPS[crystal_id_one][1];

        if(gem_benefit == "hit" || gem_benefit == "pen" ||
            gem_benefit == "hit-pen")
            magic_info_string += ", magically enhancing the weapon";
        else if(gem_benefit == "lesser_resist" || gem_benefit == "greater_resist")
        {
            string gem_resist_benefit = MASTERWORK_GEM_PROPS[crystal_id_one][2];
            magic_info_string += ", providing magical resistance to " +
                gem_resist_benefit;
        }
        else if(gem_benefit == "skill")
            magic_info_string += ", magically enhancing the wielder's skills";
        else if(gem_benefit == "special")
            magic_info_string += ", providing the wielder with magical " +
                "enhancement when the gemstone is pressed";
        else if(gem_benefit == "weight")
            magic_info_string += ", magically reducing the weight of the " +
                "weapon";

        if(inserted_gems < 2)
            magic_info_string += ".\n";
        else if(inserted_gems < 3)
            magic_info_string += " and ";
        else
            magic_info_string += ", ";

       inserted_gems -= 1;
    }

    if(crystal_two)
    {
        string gem_desc = MASTERWORK_GEM_PROPS[crystal_id_two][3];  
        gem_desc = LANG_ADDART(gem_desc); 
        magic_info_string += gem_desc;

        string gem_benefit = MASTERWORK_GEM_PROPS[crystal_id_two][1];

        if(gem_benefit == "hit" || gem_benefit == "pen" ||
            gem_benefit == "hit-pen")
            magic_info_string += ", magically enhancing the weapon";
        else if(gem_benefit == "lesser_resist" || gem_benefit == "greater_resist")
        {
            string gem_resist_benefit = MASTERWORK_GEM_PROPS[crystal_id_two][2];
            magic_info_string += ", providing magical resistance to " +
                gem_resist_benefit;
        }
        else if(gem_benefit == "skill")
            magic_info_string += ", magically enhancing the wielder's skills";
        else if(gem_benefit == "special")
            magic_info_string += ", providing the wielder with magical " +
                "enhancement when the gemstone is pressed";
        else if(gem_benefit == "weight")
            magic_info_string += ", magically reducing the weight of the " +
                "weapon";

        if(inserted_gems < 2)
            magic_info_string += ".\n";
        else if(inserted_gems < 3)
            magic_info_string += " and ";

       inserted_gems -= 1;
    }

    if(crystal_three)
    {
        string gem_desc = MASTERWORK_GEM_PROPS[crystal_id_three][3];  
        gem_desc = LANG_ADDART(gem_desc); 
        magic_info_string += gem_desc;

        string gem_benefit = MASTERWORK_GEM_PROPS[crystal_id_three][1];

        if(gem_benefit == "hit" || gem_benefit == "pen" ||
            gem_benefit == "hit-pen")
            magic_info_string += ", magically enhancing the weapon";
        else if(gem_benefit == "lesser_resist" || gem_benefit == "greater_resist")
        {
            string gem_resist_benefit = MASTERWORK_GEM_PROPS[crystal_id_three][2];
            magic_info_string += ", providing magical resistance to " +
                gem_resist_benefit;
        }
        else if(gem_benefit == "skill")
            magic_info_string += ", magically enhancing the wearer's skills";
        else if(gem_benefit == "special")
            magic_info_string += ", providing the wearer with magical " +
                "enhancement when the gemstone is pressed";
        else if(gem_benefit == "weight")
            magic_info_string += ", magically reducing the weight of the " +
                "weapon";

        magic_info_string += ".\n";
    }

    add_prop(MAGIC_AM_ID_INFO, ({ "This " +short()+ " is a beautifully " +
        "crafted greatbow, designed to be able to insert magical " +
        "augmentation stones in to it and enhancing it with magic. " +
        magic_info_string, 25 }));

    add_prop(MAGIC_AM_MAGIC, ({ magic_value, "abjuration" }));

    add_prop(OBJ_S_WIZINFO, "This weapon has been enchanted by having " +
        "up to three warfare reward gems inserted in to it. Gem " +
        "code can be found at /d/Krynn/common/warfare/rewards/\n");
}

string
cavity_weapon_desc()
{
    string cavity_string, gem_type_string, cav_type1, cav_type2;
    string s1 = query_crystal_shape_one();
    string s2 = query_crystal_shape_two();
    string s3 = query_crystal_shape_three();

    if((s1 == s2) && (s2 == s3))
        gem_type_string = s1;
    else if((s1 == s2) && (s2 != s3))
        gem_type_string = s1 +" and "+ s3;
    else
        gem_type_string = s1 +", " +s2+ ", and "+ s3;

    cav_type1 = "cavity";
    cav_type2 = "cavities";   

    if (!strlen(crystal_id_one) && !strlen(crystal_id_two) &&
        !strlen(crystal_id_three))
        cavity_string =  "These " +cav_type2+ " have been deliberately " +
            "designed by a master smith to allow the insertion of " +
            "augmentation crystals of similar shape - in this " +
            "case " +gem_type_string+ " - providing a " +
            "magical effect to the bow when affixed.";
    else if(!strlen(crystal_id_two) && !strlen(crystal_id_three))
        cavity_string =  "These " +cav_type2+ " have been deliberately " +
            "designed by a master smith to allow the insertion of " +
            "augmentation crystals of similar shape - in this " +
            "case " +((s2 == s3) ? s2 : s2 +" and "+ s3)+ 
            " - providing a magical effect to the bow when affixed.";
    else if(!strlen(crystal_id_two))
        cavity_string =  "This " +cav_type1+ " has been deliberately " +
            "designed by a master smith to allow the insertion of " +
            "an augmentation crystal of a specific shape - in this " +
            "case " +s3+ " - providing a magical effect to the bow " +
            "when affixed.";
    else
        cavity_string = "";

    return query_crystal_slot_desc() + " " + cavity_string + "\n";
}

public void
update_warfare_weapon()
{
    if(strlen(crystal_id_one) > 1)
    {
        string gem_shape = MASTERWORK_GEM_PROPS[crystal_id_one][0];
        string benefit_type = MASTERWORK_GEM_PROPS[crystal_id_one][1];
        int benefit_bonus = MASTERWORK_GEM_PROPS[crystal_id_one][2];

        set_crystal_slot(1, crystal_id_one, gem_shape, benefit_type,
           benefit_bonus);
    }

    if(strlen(crystal_id_two) > 1)
    {
        string gem_shape = MASTERWORK_GEM_PROPS[crystal_id_two][0];
        string benefit_type = MASTERWORK_GEM_PROPS[crystal_id_two][1];
        int benefit_bonus = MASTERWORK_GEM_PROPS[crystal_id_two][2];

        set_crystal_slot(2, crystal_id_two, gem_shape, benefit_type,
           benefit_bonus);
    }

    if(strlen(crystal_id_three) > 1)
    {
        string gem_shape = MASTERWORK_GEM_PROPS[crystal_id_three][0];
        string benefit_type = MASTERWORK_GEM_PROPS[crystal_id_three][1];
        int benefit_bonus = MASTERWORK_GEM_PROPS[crystal_id_three][2];

        set_crystal_slot(3, crystal_id_three, gem_shape, benefit_type,
           benefit_bonus);
    }

    set_name("bow");
    set_short(warfare_weapon_short());
    set_long(warfare_weapon_long());

    // need to set for commodity hooks to work with plural_short()
    set_pshort(short() + "s");

    string s1 = query_crystal_shape_one();
    string s2 = query_crystal_shape_two();
    string s3 = query_crystal_shape_three();

    add_item(({ s1 +"-shaped cavities", "cavities", "cavity", 
        s2 +"-shaped cavities", s3 +"-shaped cavities",        
        "runes", "silver-inlay runes", "dark empty cavities", 
        "empty cavities" }),
        cavity_weapon_desc());
      
    set_hit(gHit);
    set_pen(gPen);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(gHit, gPen) + random(20) - 10);

    int weight_mod = 4 - min(3, gWeight);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(gPen, W_MISSILE) *
        weight_mod / 4 );

    if(crystal_one || crystal_two || crystal_three)
        add_masterwork_magic_props();

    if (objectp(query_wielded()))
        query_wielded()->update_weapon(this_object());
}

void
create_bow()
{
    create_warfare_weapon();
    update_warfare_weapon();
    set_wf(this_object());
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

public mixed
wield(object obj)
{

    if(crystal_one && (query_crystal_shape_one() == "ellipse"))
    {
        // while zero is technically a skill number, it will
        // cause errors if we allow it
        if(!crystal_one_activated && crystal_one_skill)
        {
            add_skill_bonus(TP, crystal_one_skill);
            crystal_one_activated = 1;
        }
    }

    if(crystal_two && (query_crystal_shape_two() == "ellipse"))
    {
        if(!crystal_two_activated && crystal_two_skill)
        {
            add_skill_bonus(TP, crystal_two_skill);
            crystal_two_activated = 1;
        }
    }

    if(crystal_three && (query_crystal_shape_three() == "ellipse"))
    {
        if(!crystal_three_activated && crystal_three_skill)
        {
            add_skill_bonus(TP, crystal_three_skill);
            crystal_three_activated = 1;
        }
    }

    TP->add_magic_effect(TO);

    return 0;
} 

mixed
unwield(object obj)
{

    if(crystal_one && (query_crystal_shape_one() == "ellipse"))
    {
        if(crystal_one_activated && crystal_one_skill)
        {
            remove_skill_bonus(TP, crystal_one_skill);
            crystal_one_activated = 0;
        }
    }

    if(crystal_two && (query_crystal_shape_two() == "ellipse"))
    {
        if(crystal_two_activated && crystal_two_skill)
        {
            remove_skill_bonus(TP, crystal_two_skill);
            crystal_two_activated = 0;
        }
    }

    if(crystal_three && (query_crystal_shape_three() == "ellipse"))
    {
        if(crystal_three_activated && crystal_three_skill)
        {
            remove_skill_bonus(TP, crystal_three_skill);
            crystal_three_activated = 0;
        }
    }

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

    if(crystal_one && crystal_two && crystal_three)
    {
        notify_fail("There are already three augmentation stones inserted " +
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
        string spare_slot1 = "ellipse";

        player->catch_tell("The " +oblist[0]->query_short()+ " is the " +
            "wrong shape to insert into your " +short()+ ". You need " +
            LANG_ADDART(spare_slot1) + " shaped crystal to insert " +
            "in to your weapon.\n");
        return 1;
    }

    int gem_slot = query_free_gem_slot(gem_shape);
    string ward_type, insert_type;

    ward_type = "enhancement magics";
    insert_type = "just below the grip on the riser of";

    set_crystal_slot(gem_slot, gem_id, gem_shape, benefit_type, benefit_bonus);

    player->catch_tell("You insert " +oblist[0]->short()+ " into "+
        "the " +gem_shape+ "-shaped " +cavity_desc+ " " +insert_type+
        " your " +short()+ ". The silvery runes around the " +
        oblist[0]->query_short()+ " glow as it locks in to place and " +
        ward_type+ " are activated.\n");

    tell_room(environment(player), QCTNAME(player)+ " inserts " + 
        oblist[0]->short()+ " into " +HIS(player)+ " " +query_short()+ ".\n", 
        ({ player }), player);

    setup_warfare_weapon(gLevel, gHand, gFaction);
    update_warfare_weapon();
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
    gHand = atoi(a[2]);
    gFaction = (a[3]);
    crystal_id_one = (a[4]);
    crystal_id_two = (a[5]);
    crystal_id_three = (a[6]);
    gHit = atoi(a[7]);
    gPen = atoi(a[8]);
    init_wep_recover(a[0]);
    update_warfare_weapon();
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" + gLevel + "&&" + 
        gHand + "&&" + gFaction + "&&" + crystal_id_one  + 
        "&&" + crystal_id_two + "&&" + crystal_id_three + "&&" + 
        gHit + "&&" + gPen;
}