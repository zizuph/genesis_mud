/* 
 * Warfare masterwork standard weapon file for the various factions.
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
 
inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/lib/commodity";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/clubs/warfare/defs.h"
#include "/d/Krynn/common/warfare/warfare.h"
#include <cmdparse.h>

public void   setup_warfare_weapon(int level, int type, int hand, string faction);
void          add_skill_bonus(object who, int skill);

int           gLevel, gType, gHit, gPen, gHand, gWeight, gSpellpower;

// Whether the gem cavity is filled (1) or empty (0)
int           crystal_one, crystal_two;
// Sets the possible crystal hit bonus
int           crystal_one_hit, crystal_two_hit;
// Sets the possible crystal pen bonus
int           crystal_one_pen, crystal_two_pen;
// Sets the possible crystal skill type
int           crystal_one_skill, crystal_two_skill;
// Sets whether the crystal is skill activated
int           crystal_one_activated, crystal_two_activated;
// Set the shape of the gem cavities
string        crystal_shape_one, crystal_shape_two;
// Set the id of the gems 
string        crystal_id_one, crystal_id_two;

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

// Queries whether there are any free slots available
public int
query_free_gem_slot(string shape)
{
    if(!query_crystal_slot_one() && (query_crystal_shape_one() == shape))
        return 1;

    if(!query_crystal_slot_two() && (query_crystal_shape_two() == shape))
        return 2;

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
set_weapon_level(int level = 0, int type = W_SWORD, int hand = W_ANYH, string faction = "free")
{
    if ( !level )
        gLevel = 0;
    else
        gLevel = level;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 2)
        gLevel = 2;

    if ( !type )
        gType = W_SWORD;
    else
        gType = type;

    if ( !hand )
        gHand = W_ANYH;
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

    if (type == W_KNIFE)
    {
        gHand = W_ANYH;
        gHit = 20;
        gPen = 20;
    }

    // Staves get a base spellpower
    if ( (type == W_POLEARM) && (level == 1) )
    {
        gSpellpower = 38;
    }

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

    if (!crystal_shape_one)
        crystal_shape_one = "ellipse";
    if (!crystal_shape_two)
        crystal_shape_two = "ellipse";
        
    setup_warfare_weapon(gLevel, gType, gHand, gFaction);
}

public void
setup_warfare_weapon(int level, int type, int hand, string faction)
{
    if(hand == W_ANYH)
    {
        gHit = 35 + crystal_one_hit + crystal_two_hit;
        gPen = 35 + crystal_one_pen + crystal_two_pen; 

        if(gHit > 50)
            gHit = 50;
        if(gPen > 50)
            gPen = 50;
    }
    else
    {
        gHit = 40 + crystal_one_hit + crystal_two_hit; 
        gPen = 40 + crystal_one_pen + crystal_two_pen; 

        if(gHit > 60)
            gHit = 60; 
        if(gPen > 60)
            gPen = 60; 
    }

    if(type == W_KNIFE)
    {
        gHit = 20 + crystal_one_hit + crystal_two_hit;
        gPen = 20 + crystal_one_pen + crystal_two_pen; 
        gSpellpower = min(40, (20 + crystal_one_pen + 
            crystal_two_pen + crystal_one_hit + crystal_two_hit));

        if(gHit > 40)
            gHit = 40;
        if(gPen > 40)
            gPen = 40;
    }

    if( (type == W_POLEARM) && (level == 1) )
    {
        gSpellpower = min(58, (38 + crystal_one_pen + 
            crystal_two_pen + crystal_one_hit + crystal_two_hit));
    }

    // WARFARE_DEBUG("Hit: " +gHit + ", Pen: " +gPen);

    if(!query_commodity_name())
        set_commodity_name("mw sword");

    set_commodity_value(F_VALUE_WEAPON(40, 40));
}

string
warfare_weapon_short()
{
    string short;

    switch(gType)
    {
        case W_SWORD:
            switch(gHand)
            {
                case W_ANYH:
                    short = "steel longsword";
                    add_name("sword");
                    add_name("longsword");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_IMPALE | W_SLASH);
                break; 
                default:
                    short = "steel greatsword";
                    add_name("sword");
                    add_name("greatsword");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_IMPALE | W_SLASH);
                break;
            }
            break;
        case W_POLEARM:
            if(gLevel == 1) // setting for staff
            {
                short = "ironwood staff";
                add_name("staff");
                add_adj("ironwood");
                add_adj("masterwork");
                set_crystal_shape_one("ellipse");
                set_crystal_shape_two("ellipse");
                set_dt(W_BLUDGEON);
                break;
            }
            if(gLevel == 2) // setting for hoopak
            {
                short = "ironwood hoopak";
                add_name("hoopak");
                add_adj("ironwood");
                add_adj("masterwork");
                set_crystal_shape_one("ellipse");
                set_crystal_shape_two("ellipse");
                set_dt(W_BLUDGEON);
                break;
            }
            else
            {
                switch(gHand)
                {
                    case W_ANYH:
                        short = "one-handed spear";
                        add_name("spear");
                        add_adj("steel");
                        add_adj("metal");
                        add_adj("masterwork");
                        set_crystal_shape_one("ellipse");
                        set_crystal_shape_two("ellipse");
                        set_dt(W_IMPALE);
                    break; 
                    default:
                        short = "steel skylance";
                        add_name("skylance");
                        add_name("lance");
                        add_adj("steel");
                        add_adj("metal");
                        add_adj("masterwork");
                        set_crystal_shape_one("ellipse");
                        set_crystal_shape_two("ellipse");
                        set_dt(W_IMPALE);
                    break;
                }
            }
            break;
        case W_AXE:
            switch(gHand)
            {
                case W_ANYH:
                    short = "steel battleaxe";
                    add_name("battleaxe");
                    add_name("axe");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_SLASH);
                break; 
                default:
                    short = "steel greataxe";
                    add_name("greataxe");
                    add_name("axe");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_SLASH);
                break;
            }
            break;
        case W_KNIFE:
            switch(gHand)
            {
                case W_ANYH:
                    short = "steel dagger";
                    add_name("dagger");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_IMPALE | W_SLASH);
                break; 
                default:
                    short = "steel dagger";
                    add_name("dagger");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_IMPALE | W_SLASH);
                break;
            }
            break;
        case W_CLUB:
            switch(gHand)
            {
                case W_ANYH:
                    short = "steel mace";
                    add_name("mace");
                    add_name("club");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_BLUDGEON);
                break; 
                default:
                    short = "steel warhammer";
                    add_name("warhammer");
                    add_name("club");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_BLUDGEON);
                break;
            }
            break;
        default:
            switch(gHand)
            {
                case W_ANYH:
                    short = "steel longsword";
                    add_name("sword");
                    add_name("longsword");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_IMPALE | W_SLASH);
                break; 
                default:
                    short = "steel greatsword";
                    add_name("sword");
                    add_name("greatsword");
                    add_adj("steel");
                    add_adj("metal");
                    add_adj("masterwork");
                    set_crystal_shape_one("ellipse");
                    set_crystal_shape_two("ellipse");
                    set_dt(W_IMPALE | W_SLASH);
                break;
            }
            break;
     }

    return short;
}

string
query_crystal_slot_desc()
{
    string cav_desc, link_desc;

    if(!crystal_one && !crystal_two)
    {
        if(gType == W_SWORD) // sword
            return "On both ends of the cross-guard you notice two " +
            "empty cavities shaped like ellipses.";
        else if(gType == W_POLEARM) // polearm
        {
            if(gLevel == 1) // staff
                return "Atop the staff you notice two empty clawlike " +
                    "cavities, designed to hold ellipse " +
                    "shaped crystals.";
            else if(gLevel == 2) // hoopak
                return "Where the hoopak forks you notice two empty " +
                    "cavities, designed to hold ellipse " +
                    "shaped crystals.";
            else
                return "Along the haft you notice two " +
                    "empty cavities shaped like ellipses.";
        }
        else if(gType == W_AXE) // axe
            return "Along the haft you notice two " +
                    "empty cavities shaped like ellipses.";
        else if(gType == W_KNIFE) // knife
            return "On either side of the pommel of the " +short()+
                " you notice two empty cavities shaped like ellipses.";
        else if(gType == W_CLUB) // club
            return "Along the handle you notice two " +
                    "empty cavities shaped like ellipses.";
        else
            return "On both ends of the cross-guard you notice two " +
            "empty cavities shaped like ellipses.";
    }

    if(!crystal_one || !crystal_two)
    {
        if(!crystal_one)
        {
            string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_two][3];
            link_desc = LANG_ADDART(gem_desc1);

        }
        if(!crystal_two)
        {
            string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_one][3];
            link_desc = LANG_ADDART(gem_desc1);
        }

        if(gType == W_SWORD)
            return "On one end of the cross-guard you notice it is " +
                "inset with " + link_desc + ", while on the other end " +
                "of the cross-guard is an empty cavity.";
        else if(gType == W_POLEARM) // polearm
        {
            if(gLevel == 1) // staff
                return "Atop the staff you notice " +link_desc+ " beside " +
                    "an empty clawlike cavity.";
            else if(gLevel == 2) // hoopak
                return "Where the hoopak forks you notice " +link_desc+ " " +
                    "beside an empty cavity.";
            else
                return "Along the haft you notice " +link_desc+ " and " +
                    "an empty cavity shaped like an ellipse.";
        }
        else if(gType == W_AXE) // axe
            return "Along the haft you notice " +link_desc+ " and " +
                "an empty cavity shaped like an ellipse.";
        else if(gType == W_KNIFE) // knife
            return "On one side of the pommel of the " +short()+
                " you notice " +link_desc+ ", while on the other " +
                "side an empty cavity shaped like an ellipse.";
        else if(gType == W_CLUB) // club
            return "Along the handle you notice " +link_desc+ " and " +
                "an empty cavity shaped like an ellipse.";
        else
            return "On one end of the cross-guard you notice it is " +
                "inset with " + link_desc + ", while on the other end " +
                "of the cross-guard is an empty cavity.";
    }

    string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_one][3];
    string gem_desc2 = MASTERWORK_GEM_PROPS[crystal_id_two][3];

    link_desc = LANG_ADDART(gem_desc1)+ " and " +LANG_ADDART(gem_desc2);

    if(gType == W_SWORD)
        return "On the ends of the cross-guard you notice it is " +
            "inset with " + link_desc + ", circled by " +
            "silver-inlay runes.";
    else if(gType == W_POLEARM) // polearm
    {
        if(gLevel == 1) // staff
            return "Atop the staff you notice it is " +
                "inset with " + link_desc + ", circled by " +
                "silver-inlay runes.";
        else if(gLevel == 2) // hoopak
            return "Where the hoopak forks you notice it is " +
                "inset with " + link_desc + ", circled by " +
                "silver-inlay runes.";
        else
            return "Along the haft you notice it is " +
                "inset with " + link_desc + ", circled by " +
                "silver-inlay runes.";
    }
    else if(gType == W_AXE) // axe
        return "Along the haft you notice it is " +
            "inset with " + link_desc + ", circled by " +
            "silver-inlay runes.";
    else if(gType == W_KNIFE) // knife
        return "On either side of the pommel of the " +short()+
            " you notice it is inset with " + link_desc + 
            ", circled by silver-inlay runes.";
    else if(gType == W_CLUB) // club
            return "Along the handle you notice it is " +
            "inset with " + link_desc + ", circled by " +
            "silver-inlay runes.";
    else
        return "On the ends of the cross-guard you notice it is " +
            "inset with " + link_desc + ", circled by " +
            "silver-inlay runes.";
}

string
warfare_weapon_long()
{
    string long;
    string faction = gFaction;

    if(faction == "pot")
    {
        string short = query_short();

            switch(gType)
            {
                case W_SWORD: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a longsword of dark steel, with " +
                              "a great onyx hilt featuring a leather " +
                              "chappe branded with the mark of a " +
                              "five-headed dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                       default:
                          long = "This is a greatsword of dark steel, with " +
                              "a prominent onyx hilt featuring a leather " +
                              "chappe branded with the mark of a five-headed " +
                              "dragon. " + query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                     }
                     break;
                case W_POLEARM: 
                    if(gLevel == 1)
                    {
                          long = "This is a staff made from the rare " +
                              "ironwood, however is dark and malformed " +
                              "as if cut from a tortured sapling. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("malformed " + short);
                          add_adj("malformed");
                          break;
                    }
                    else if(gLevel == 2)
                    {
                          long = "This is a curious staff made from the rare " +
                              "ironwood, with one end a sharp point and the " +
                              "other a forked top with a leather sling attached " +
                              "to the top - a hoopak, masterfully crafted in " +
                              "the traditional fashion of the kender! " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed spear with a " +
                              "nasty looking tip of dark steel. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                       default:
                          long = "This is a dark steel skylance. Meant " +
                              "for use from the back of an aerial mount, " +
                              "this exceptionally long lance would be " +
                              "difficult to wield if not for its " +
                              "masterful craftsmanship. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                     }
                     break;
                case W_AXE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a battleaxe of dark steel, with " +
                              "a haft branded with the mark of a " +
                              "five-headed dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                       default:
                          long = "This is a greataxe of dark steel, with " +
                              "a haft branded with the mark of a five-headed " +
                              "dragon. " + query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                     }
                     break;
                case W_KNIFE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a cruel dagger of dark steel, with " +
                              "an elaborate hilt in the fashion of a " +
                              "five-headed dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                       default:
                          long = "This is a cruel dagger of dark steel, with " +
                              "an elaborate hilt in the fashion of a " +
                              "five-headed dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                     }
                     break;
                case W_CLUB: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a mace of dark steel, with " +
                              "an ironwood handle and a head shaped " +
                              "elaborately to look like an entwined " +
                              "five-headed dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dragon-headed " + short);
                          add_adj("dragon-headed");
                          add_adj("dragon");
                          add_adj("headed");
                          break;
                       default:
                          long = "This is a warhammer of dark steel, with " +
                              "a handle branded with the mark of a five-" +
                              "headed dragon. " + query_crystal_slot_desc()+ 
                              "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                     }
                     break;
                default: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a longsword of dark steel, with " +
                              "a great onyx hilt featuring a leather " +
                              "chappe branded with the mark of a " +
                              "five-headed dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                       default:
                          long = "This is a greatsword of dark steel, with " +
                              "a prominent onyx hilt featuring a leather " +
                              "chappe branded with the mark of a five-headed " +
                              "dragon. " + query_crystal_slot_desc()+ "\n";
                          set_short("dark " + short);
                          add_adj("dark");
                          break;
                     }
                     break;
            }
    }
    else if(faction == "blue" || faction == "red" || faction == "white" ||
        faction == "black" || faction == "green")
    {
        string short = query_short();

            switch(gType)
            {
                case W_SWORD: 
                    switch(gHand)
                    { 
                        case W_ANYH:
                          long = "This is a longsword of dark steel, " +
                                "with a great onyx hilt featuring a " +
                                "leather chappe branded with " +
                                "the mark of a " +faction+ " dragon. " + 
                                query_crystal_slot_desc()+ "\n";
                          set_short("dragon-marked " + short);
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                       default:
                          long = "This is a greatsword of dark steel, with " +
                              "a prominent onyx hilt featuring a leather " +
                              "chappe branded with the mark of a " +faction+
                              "dragon. " + query_crystal_slot_desc()+ "\n";
                          set_short("dragon-marked " + short);
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                     }
                     break;
                case W_POLEARM: 
                    if(gLevel == 1)
                    {
                          long = "This is a staff made from the rare " +
                              "ironwood, however is dark and twisted " +
                              "as if cut from a tortured sapling. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("twisted " + short);
                          add_adj("twisted");
                          break;
                    }
                    else if(gLevel == 2)
                    {
                          long = "This is a curious staff made from the rare " +
                              "ironwood, with one end a sharp point and the " +
                              "other a forked top with a leather sling attached " +
                              "to the top - a hoopak, masterfully crafted in " +
                              "the traditional fashion of the kender! " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed spear with a " +
                              faction+ " dragon brand running down " +
                              "the length of its ironwood haft, and a " +
                              "nasty looking tip of dark steel. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dragon-marked " + short);
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                       default:
                          long = "This is a skylance, marked with a " +
                              faction+ " dragon brand running down " +
                              "the length of its ironwood haft. Meant " +
                              "for use from the back of an aerial mount, " +
                              "this exceptionally long lance would be " +
                              "difficult to wield if not for its " +
                              "masterful craftsmanship. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dragon-marked steel skylance");
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                     }
                     break;
                case W_AXE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a battleaxe of dark steel, with " +
                              "a haft branded with the mark of a " +
                              faction+ " dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dragon-marked " + short);
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                       default:
                          long = "This is a greataxe of dark steel, with " +
                              "a haft branded with the mark of a " +
                              faction+ " dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dragon-marked " + short);
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                     }
                     break;
                case W_KNIFE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a cruel dagger of dark steel, with " +
                              "an elaborate hilt in the fashion of a " +
                              faction+ " dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("cruel " + short);
                          add_adj("cruel");
                          break;
                       default:
                          long = "This is a cruel dagger of dark steel, with " +
                              "an elaborate hilt in the fashion of a " +
                              faction+ " dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("cruel " + short);
                          add_adj("cruel");
                          break;
                     }
                     break;
                case W_CLUB: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a ball-and-chain flail with " +
                              "an ironwood handle and a chain-linked ball " +
                              "of dark steel shaped elaborately to look " +
                              "like the head of a " +faction+ " dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          add_name("flail");
                          set_short("dragon-headed flail");
                          add_adj("dragon-headed");
                          add_adj("dragon");
                          add_adj("headed");
                          break;
                       default:
                          long = "This is a warhammer of dark steel, with " +
                              "a handle branded with the mark of a " +faction+
                              "headed dragon. " + query_crystal_slot_desc()+ 
                              "\n";
                          set_short("dragon-marked " + short);
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                     }
                     break;
                default: 
                switch(gHand)
                { 
                        case W_ANYH:
                          long = "This is a longsword of dark steel, " +
                                "with a great onyx hilt featuring a " +
                                "leather chappe branded with " +
                                "the mark of a " +faction+ " dragon. " + 
                                query_crystal_slot_desc()+ "\n";
                          set_short("dragon-marked " + short);
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                       case W_BOTH:
                          long = "This is a greatsword of dark steel, with " +
                              "a prominent onyx hilt featuring a leather " +
                              "chappe branded with the mark of a " +faction+
                              "dragon. " + query_crystal_slot_desc()+ "\n";
                          set_short("dragon-marked " + short);
                          add_adj(faction);
                          add_adj("dragon-marked");
                          add_adj("marked");
                          add_adj("dragon");
                          break;
                 }
            }
    }
    else if(faction == "knights")
    {
        string short = query_short();

            switch(gType)
            {
                case W_SWORD: 
                    switch(gHand)
                    { 
                        case W_ANYH:
                          long = "This is a longsword of fine steel, with an " +
                              "ornate hilt and heavy pommel designed in the " +
                              "fashion popular with the Knights of Solamnia. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");
                          break;
                       default:
                          long = "This is a greatsword of fine steel, with an " +
                              "impressive ornate hilt and heavy pommel designed " +
                              "in the fashion popular with the Knights of " +
                              "Solamnia. " +query_crystal_slot_desc()+ "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");
                          break;
                     }
                     break;
                case W_POLEARM: 
                    if(gLevel == 1)
                    {
                          long = "This is a staff made from the rare " +
                              "ironwood, polished to a beautiful red hue. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("polished " + short);
                          add_adj("polished");
                          break;
                    }
                    else if(gLevel == 2)
                    {
                          long = "This is a curious staff made from the rare " +
                              "ironwood, with one end a sharp point and the " +
                              "other a forked top with a leather sling attached " +
                              "to the top - a hoopak, masterfully crafted in " +
                              "the traditional fashion of the kender! " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed spear approximately two " +
                              "metres in length with a shaft made from ash and " +
                              "a sharp steel head. A heavy crossbar sits just " +
                              "beneath the blade, preventing the spear from " +
                              "penetrating too deeply into its target, allowing " +
                              "for repeated stabbing with little risk of the " +
                              "weapon getting stuck in an opponent. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");
                          break;
                       default:
                          long = "This is a beautiful skylance, marked with " +
                              "Solamnic sigils that run down the length of " +
                              "its ironwood haft and inlaid with rare " +
                              "dragonsilver. Meant for use from the back of " +
                              "an aerial mount, this exceptionally long lance " +
                              "would be difficult to wield if not for its " +
                              "masterful craftsmanship. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");
                          break;
                     }
                     break;
                case W_AXE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle axe with a " +
                              "double bladed trumpet-shaped steel blade " +
                              "mounted on the end of a stout four foot pole " +  
                              "in Solamnic fashion. " +
                              query_crystal_slot_desc()+ "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");
                          break;
                       default:
                          long = "This is a greataxe of steel, with a five " +
                              "foot ironwood haft with a long cleaver-type " +
                              "blade attached to it. " +
                              query_crystal_slot_desc()+ "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");
                          break;
                     }
                     break;
                case W_KNIFE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a long dagger of Solamnic steel, with " +
                              "an elaborate hilt in the fashion of a " +
                              faction+ " dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("long solamnic " + short);
                          add_adj("long");
                          add_adj("solamnic");
                          break;
                       default:
                          long = "This is a long dagger of Solamnic steel, with " +
                              "an elaborate hilt in the fashion of a " +
                              faction+ " dragon. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("long solamnic " + short);
                          add_adj("long");
                          add_adj("solamnic");
                          break;
                     }
                     break;
                case W_CLUB: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a ball-and-chain flail with " +
                              "an ironwood handle and a chain-linked ball " +
                              "of the finest steel shaped like the head of " +
                              "a rose. " + 
                              query_crystal_slot_desc()+ "\n";
                          add_name("flail");
                          add_name("ball-and-chain");
                          add_name("ball");
                          add_name("chain");
                          set_short("solamnic ball-and-chain flail");
                          add_adj("solamnic");
                          break;
                       default:
                          long = "This is a warhammer with a large steel " +
                              "head attached to it that would easily drop a " +
                              "horse. It is beautifully tooled with the " +
                              "symbols of the Knights of Solamnia. " + 
                              query_crystal_slot_desc()+  "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");

                          break;
                     }
                     break;
                default: 
                switch(gHand)
                { 
                        case W_ANYH:
                          long = "This is a longsword of fine steel, with an " +
                              "ornate hilt and heavy pommel designed in the " +
                              "fashion popular with the Knights of Solamnia. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");
                          break;
                        case W_BOTH:
                          long = "This is a greatsword of fine steel, with an " +
                              "impressive ornate hilt and heavy pommel designed " +
                              "in the fashion popular with the Knights of " +
                              "Solamnia. " +query_crystal_slot_desc()+ "\n";
                          set_short("solamnic " + short);
                          add_adj("solamnic");
                          break;
                 }
            }

    }
    else if(faction == "neidar")
    {
        string short = query_short();

            switch(gType)
            {
                case W_SWORD: 
                    switch(gHand)
                    { 
                        case W_ANYH:
                          long = "This is a longsword of fine steel, with an " +
                              "ornate hilt and heavy pommel designed in the " +
                              "fashion popular with the hill dwarves of Krynn. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");
                          break;
                       default:
                          long = "This is a greatsword of fine steel, with an " +
                              "impressive ornate hilt and heavy pommel designed " +
                              "in the fashion popular with the hill dwarves of " +
                              "Krynn. " +query_crystal_slot_desc()+ "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");
                          break;
                     }
                     break;
                case W_POLEARM: 
                    if(gLevel == 1)
                    {
                          long = "This is a staff made from the rare " +
                              "ironwood, polished to a beautiful red hue. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("polished " + short);
                          add_adj("polished");
                          break;
                    }
                    else if(gLevel == 2)
                    {
                          long = "This is a curious staff made from the rare " +
                              "ironwood, with one end a sharp point and the " +
                              "other a forked top with a leather sling attached " +
                              "to the top - a hoopak, masterfully crafted in " +
                              "the traditional fashion of the kender! " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed spear approximately two " +
                              "metres in length with a shaft made from ash and " +
                              "a sharp steel head. A heavy crossbar sits just " +
                              "beneath the blade, preventing the spear from " +
                              "penetrating too deeply into its target, allowing " +
                              "for repeated stabbing with little risk of the " +
                              "weapon getting stuck in an opponent. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");
                          break;
                       default:
                          long = "This is a two-handed long-spear capped with " +
                              "a sharp steel blade intricately carved with " +
                              "dwarven sigils of war. " + 
                              query_crystal_slot_desc()+ "\n";
                          add_name("spear");
                          add_name("long-spear");
                          set_short("dwarven long-spear");
                          add_adj("dwarven");
                          add_adj("long");
                          break;
                     }
                     break;
                case W_AXE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle axe with a " +
                              "double bladed trumpet-shaped steel blade " +
                              "mounted on the end of a stout four foot pole " +  
                              "in dwarven fashion. " +
                              query_crystal_slot_desc()+ "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");
                          break;
                       default:
                          long = "This is a greataxe of steel, with a long " +
                              "cleaver-type blade attached to a five " +
                              "foot ironwood haft inscribed with dwarven " +
                              "sigils of war. " +
                              query_crystal_slot_desc()+ "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");
                          break;
                     }
                     break;
                case W_KNIFE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a jagged dagger of fine steel, with " +
                              "an elaborate hilt designed in dwarven fashion. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("jagged " + short);
                          add_adj("jagged");
                          break;
                       default:
                          long = "This is a jagged dagger of fine steel, with " +
                              "an elaborate hilt designed in dwarven fashion. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("jagged " + short);
                          add_adj("jagged");
                          break;
                     }
                     break;
                case W_CLUB: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle mace with a " +
                              "broad steel head mounted on the end of a " +
                              "stout four foot handle, and engraved with " +
                              "dwarven war symbols. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dwarven battle mace");
                          add_adj("dwarven");
                          add_adj("battle");
                          break;
                       default:
                          long = "This is a warhammer with a large steel " +
                              "head attached to it that would easily drop a " +
                              "horse. It is beautifully tooled with " +
                              "war sigils of the hill dwarves of Krynn. " + 
                              query_crystal_slot_desc()+  "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");

                          break;
                     }
                     break;
                default:
                switch(gHand) 
                { 
                        case W_ANYH:
                          long = "This is a longsword of fine steel, with an " +
                              "ornate hilt and heavy pommel designed in the " +
                              "fashion popular with the hill dwarves of Krynn. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");
                          break;
                        case W_BOTH:
                          long = "This is a greatsword of fine steel, with an " +
                              "impressive ornate hilt and heavy pommel designed " +
                              "in the fashion popular with the hill dwarves of " +
                              "Krynn. " +query_crystal_slot_desc()+ "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");
                          break;
                 }
            }
    }
    else if(faction == "qualinesti")
    {
        string short = query_short();

            switch(gType)
            {
                case W_SWORD: 
                    switch(gHand)
                    { 
                        case W_ANYH:
                          long = "This is an elegant longsword of fine " +
                              "steel, its blade engraved with graceful " +
                              "elven carvings. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                       default:
                          long = "This is a greatsword of fine steel, " +
                              "long yet gracefully designed in the " +
                              "fashion of the elven nations of Krynn. " +
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                     }
                     break;
                case W_POLEARM: 
                    if(gLevel == 1)
                    {
                          long = "This is an elven staff made from the rare " +
                              "ironwood, polished to a beautiful red hue. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                    }
                    else if(gLevel == 2)
                    {
                          long = "This is a curious staff made from the rare " +
                              "ironwood, with one end a sharp point and the " +
                              "other a forked top with a leather sling attached " +
                              "to the top - a hoopak, masterfully crafted in " +
                              "the traditional fashion of the kender! " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed spear approximately two " +
                              "metres in length with a shaft made from ash and " +
                              "a sharp steel head. Light and graceful, it is " +
                              "a beautifully crafted weapon in the style of the " +
                              "elven nations of Krynn. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                       default:
                          long = "This is a two-handed long-spear capped with " +
                              "a sharp steel blade intricately carved with " +
                              "elven runes. " + 
                              query_crystal_slot_desc()+ "\n";
                          add_name("spear");
                          add_name("long-spear");
                          set_short("elven long-spear");
                          add_adj("elven");
                          add_adj("long");
                          break;
                     }
                     break;
                case W_AXE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle axe with a " +
                              "slender double-bladed steel blade " +
                              "mounted on the end of a sturdy four foot pole " +  
                              "in elven fashion. " +
                              query_crystal_slot_desc()+ "\n";
                          set_short("dwarven " + short);
                          add_adj("dwarven");
                          break;
                       default:
                          long = "This is a greataxe of steel, with a long " +
                              "cleaver-type blade attached to a five " +
                              "foot ironwood haft inscribed with elven " +
                              "runes. " +
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                     }
                     break;
                case W_KNIFE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a elven dagger of fine steel and " +
                              "an elaborate hilt. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                       default:
                          long = "This is a elven dagger of fine steel and " +
                              "an elaborate hilt. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                     }
                     break;
                case W_CLUB: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle mace with a " +
                              "broad steel head mounted on the end of a " +
                              "stout four foot handle, and engraved with " +
                              "elven war runes. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                       default:
                          long = "This is a warhammer with a large steel " +
                              "head attached to it that would easily drop a " +
                              "horse. It is beautifully tooled with " +
                              "elven runes. " + 
                              query_crystal_slot_desc()+  "\n";
                          set_short("elven " + short);
                          add_adj("elven");

                          break;
                     }
                     break;
                default: 
                switch(gHand)
                { 
                        case W_ANYH:
                          long = "This is an elegant longsword of fine " +
                              "steel, its blade engraved with graceful " +
                              "elven carvings. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                        case W_BOTH:
                          long = "This is a greatsword of fine steel, " +
                              "long yet gracefully designed in the " +
                              "fashion of the elven nations of Krynn. " +
                              query_crystal_slot_desc()+ "\n";
                          set_short("elven " + short);
                          add_adj("elven");
                          break;
                 }
            }

    }
    else if(faction == "free")
    {

        string short = query_short();

            switch(gType)
            {
                case W_SWORD: 
                    switch(gHand)
                    { 
                        case W_ANYH:
                           long = "This is a longsword of fine steel, " +
                               "with an ornate hilt and heavy pommel. " + 
                               query_crystal_slot_desc()+ "\n";
                          break;
                       default:
                           long = "This is a greatsword of fine steel, " +
                               "with an ornate hilt and heavy pommel. " + 
                               query_crystal_slot_desc()+ "\n";
                          break;
                     }
                     break;
                case W_POLEARM: 
                    if(gLevel == 1)
                    {
                          long = "This is a staff made from the rare " +
                              "ironwood, polished to a beautiful red hue. " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else if(gLevel == 2)
                    {
                          long = "This is a curious staff made from the rare " +
                              "ironwood, with one end a sharp point and the " +
                              "other a forked top with a leather sling attached " +
                              "to the top - a hoopak, masterfully crafted in " +
                              "the traditional fashion of the kender! " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed spear approximately two " +
                              "metres in length with a shaft made from ash and " +
                              "a sharp steel head. " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                       default:
                          long = "This is a two-handed long-spear capped with " +
                              "a sharp steel blade intricately carved with " +
                              "elven runes. " + 
                              query_crystal_slot_desc()+ "\n";
                          add_name("spear");
                          add_name("long-spear");
                          set_short("steel long-spear");
                          add_adj("long");
                          break;
                     }
                     break;
                case W_AXE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle axe with a " +
                              "slender double-bladed steel blade " +
                              "mounted on the end of a sturdy four foot pole. " +
                              query_crystal_slot_desc()+ "\n";
                          break;
                       default:
                          long = "This is a greataxe of steel, with a long " +
                              "cleaver-type blade attached to a five " +
                              "foot ironwood haft. " +
                              query_crystal_slot_desc()+ "\n";
                          break;
                     }
                     break;
                case W_KNIFE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is dagger of fine steel and " +
                              "an elaborate hilt. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("fine " + short);
                          add_adj("fine");
                          break;
                       default:
                          long = "This is dagger of fine steel and " +
                              "an elaborate hilt. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("fine " + short);
                          add_adj("fine");
                          break;
                     }
                     break;
                case W_CLUB: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle mace with a " +
                              "broad steel head mounted on the end of a " +
                              "stout four foot handle. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("steel battle mace");
                          add_adj("battle");
                          break;
                       default:
                          long = "This is a warhammer with a large steel " +
                              "head attached to it that would easily drop a " +
                              "horse. It is beautifully tooled with " +
                              "sigils of battle. " + 
                              query_crystal_slot_desc()+  "\n";
                          break;
                     }
                     break;
                default: 
                switch(gHand)
                { 
                        case W_ANYH:
                           long = "This is a longsword of fine steel, " +
                               "with an ornate hilt and heavy pommel. " +  
                              query_crystal_slot_desc()+ "\n";
                          break;
                       default:
                           long = "This is a longsword of fine steel, " +
                               "with an ornate hilt and heavy pommel. " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                 }
            }

    }
    else
    {
        string short = query_short();

            switch(gType)
            {
                case W_SWORD: 
                    switch(gHand)
                    { 
                        case W_ANYH:
                           long = "This is a longsword of fine steel, " +
                               "with an ornate hilt and heavy pommel. " + 
                               query_crystal_slot_desc()+ "\n";
                          break;
                       default:
                           long = "This is a greatsword of fine steel, " +
                               "with an ornate hilt and heavy pommel. " + 
                               query_crystal_slot_desc()+ "\n";
                          break;
                     }
                     break;
                case W_POLEARM: 
                    if(gLevel == 1)
                    {
                          long = "This is a staff made from the rare " +
                              "ironwood, polished to a beautiful red hue. " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else if(gLevel == 2)
                    {
                          long = "This is a curious staff made from the rare " +
                              "ironwood, with one end a sharp point and the " +
                              "other a forked top with a leather sling attached " +
                              "to the top - a hoopak, masterfully crafted in " +
                              "the traditional fashion of the kender! " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                    }
                    else switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed spear approximately two " +
                              "metres in length with a shaft made from ash and " +
                              "a sharp steel head. " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                       default:
                          long = "This is a two-handed long-spear capped with " +
                              "a sharp steel blade, beautifully crafted by a " +
                              "master weaponsmith. " + 
                              query_crystal_slot_desc()+ "\n";
                          add_name("spear");
                          add_name("long-spear");
                          set_short("steel long-spear");
                          add_adj("long");
                          break;
                     }
                     break;
                case W_AXE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle axe with a " +
                              "slender double-bladed steel blade " +
                              "mounted on the end of a sturdy four foot pole. " +
                              query_crystal_slot_desc()+ "\n";
                          break;
                       default:
                          long = "This is a greataxe of steel, with a long " +
                              "cleaver-type blade attached to a five " +
                              "foot ironwood haft. " +
                              query_crystal_slot_desc()+ "\n";
                          break;
                     }
                     break;
                case W_KNIFE: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is dagger of fine steel and " +
                              "an elaborate hilt. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("fine " + short);
                          add_adj("fine");
                          break;
                       default:
                          long = "This is dagger of fine steel and " +
                              "an elaborate hilt. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("fine " + short);
                          add_adj("fine");
                          break;
                     }
                     break;
                case W_CLUB: 
                    switch(gHand)
                    { 
                       case W_ANYH:
                          long = "This is a one-handed battle mace with a " +
                              "broad steel head mounted on the end of a " +
                              "stout four foot handle. " + 
                              query_crystal_slot_desc()+ "\n";
                          set_short("steel battle mace");
                          add_adj("battle");
                          break;
                       default:
                          long = "This is a warhammer with a large steel " +
                              "head attached to it that would easily drop a " +
                              "horse. It is beautifully tooled with " +
                              "sigils of battle. " + 
                              query_crystal_slot_desc()+  "\n";
                          break;
                     }
                     break;
                default: 
                switch(gHand)
                { 
                        case W_ANYH:
                           long = "This is a longsword of fine steel, " +
                               "with an ornate hilt and heavy pommel. " +  
                              query_crystal_slot_desc()+ "\n";
                          break;
                       default:
                           long = "This is a longsword of fine steel, " +
                               "with an ornate hilt and heavy pommel. " + 
                              query_crystal_slot_desc()+ "\n";
                          break;
                 }
            }
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

    add_prop(MAGIC_AM_ID_INFO, ({ "This " +short()+ " is a beautifully " +
        "crafted weapon, designed to be able to insert magical " +
        "augmentation stones in to it and enhancing it with magic. " +
        magic_info_string, 25 }));

    add_prop(MAGIC_AM_MAGIC, ({ magic_value, "abjuration" }));

    add_prop(OBJ_S_WIZINFO, "This weapon has been enchanted by having " +
        "up to two warfare reward gems inserted in to it. Gem " +
        "code can be found at /d/Krynn/common/warfare/rewards/\n");
}

string
cavity_weapon_desc()
{
    string cavity_string, gem_type_string, cav_type1, cav_type2;
    string s1 = query_crystal_shape_one();
    string s2 = query_crystal_shape_two();

    if((s1 == s2))
        gem_type_string = s1;
    else
        gem_type_string = s1 +" and "+ s2;

    cav_type1 = "cavity";
    cav_type2 = "cavities";   

    if (!strlen(crystal_id_one) && !strlen(crystal_id_two))
        cavity_string =  "These " +cav_type2+ " have been deliberately " +
            "designed by a master smith to allow the insertion of " +
            "augmentation crystals of similar shape - in this " +
            "case " +gem_type_string+ " - providing a " +
            "magical effect to the weapon when affixed.";
    else if(!strlen(crystal_id_two))
        cavity_string =  "This " +cav_type1+ " has been deliberately " +
            "designed by a master smith to allow the insertion of " +
            "an augmentation crystal of a specific shape - in this " +
            "case " +s2+ " - providing a magical effect to the weapon " +
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

    set_name("weapon");
    set_short(warfare_weapon_short());
    set_long(warfare_weapon_long());

    // need to set for commodity hooks to work with plural_short()
    set_pshort(short() + "s");

    string s1 = query_crystal_shape_one();
    string s2 = query_crystal_shape_two();

    add_item(({ s1 +"-shaped cavities", s1+ "drop shaped cavities", 
        "cavities", s1+ "drop cavities", "cavity", s1+ "drop-shaped " +
        "cavity", s2 +"-shaped cavities", s2+ "drop shaped cavities", 
        s2+ "drop cavities", s2+ "drop-shaped cavity", "runes", 
        "silver-inlay runes", "dark empty cavities", "empty cavities" }),
        cavity_weapon_desc());
      
    set_hit(gHit);
    set_pen(gPen);
    set_magic_spellpower(gSpellpower);
    set_wt(gType);
    // set_dt(W_SLASH);
    set_hands(gHand);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(gHit, gPen) + random(20) - 10);

    int weight_mod = 4 - min(3, gWeight);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(gPen, gType) *
        weight_mod / 4 );

    if(crystal_one || crystal_two)
        add_masterwork_magic_props();

    if (objectp(query_wielded()))
        query_wielded()->update_weapon(this_object());
}

void
create_weapon()
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

    TP->remove_magic_effect(TO);
    return 0;
} /* remove */

int
insert_gem(string str)
{
    string gem, weapon;
    mixed  *oblist,
           *weapons;
    object * item;
    object player = this_player();
    string cavity_desc;

    cavity_desc = "cavity"; 

    if (!str)
    {
        notify_fail("Insert what?\n");
        return 0;
    }


    if (!parse_command(str, ({}), "[the] %s 'into' [the] %s", gem, weapon))
    {
        notify_fail("Insert <what> into <what>?\n");
        return 0;
    }

    if (!sizeof(oblist = FIND_STR_IN_ARR(gem, all_inventory(player))))
    {
        notify_fail("You possess no " + gem + ".\n");
        return 0;
    }

    if (!sizeof(weapons = FIND_STR_IN_ARR(weapon, all_inventory(player))))
    {
        notify_fail("You possess no " + weapon + ".\n");
        return 0;
    }

    if (!IN_ARRAY(this_object(), weapons))
    {
        // WARFARE_DEBUG("weapon doesn't equal this object");
        return 0; 
    }

    if(crystal_one && crystal_two)
    {
        notify_fail("There are already two augmentation stones inserted " +
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
    insert_type = "on the cross-guard of";

    set_crystal_slot(gem_slot, gem_id, gem_shape, benefit_type, benefit_bonus);

    player->catch_tell("You insert " +oblist[0]->short()+ " into "+
        "the " +gem_shape+ "-shaped " +cavity_desc+ " " +insert_type+
        " your " +short()+ ". The silvery runes around the " +
        oblist[0]->query_short()+ " glow as it locks in to place and " +
        ward_type+ " are activated.\n");

    tell_room(environment(player), QCTNAME(player)+ " inserts " + 
        oblist[0]->short()+ " into " +HIS(player)+ " " +query_short()+ ".\n", 
        ({ player }), player);

    setup_warfare_weapon(gLevel, gType, gHand, gFaction);
    update_warfare_weapon();
    oblist[0]->reduce_heap_size();
    
    return 1;
}

void 
appraise_object(int num)
{
    ::appraise_object(num);

    if(gSpellpower)
        write(item_spellpower_desc());
}
string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
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
    gType = atoi(a[2]);
    gHand = atoi(a[3]);
    gFaction = (a[4]);
    crystal_id_one = (a[5]);
    crystal_id_two = (a[6]);
    gHit = atoi(a[7]);
    gPen = atoi(a[8]);
    gSpellpower = atoi(a[9]);
    init_wep_recover(a[0]);
    update_warfare_weapon();
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" + gLevel + "&&" + 
        gType + "&&" + gHand + "&&" + gFaction + "&&" + crystal_id_one  + 
        "&&" + crystal_id_two + "&&" + gHit + "&&" + gPen + "&&" + gSpellpower;
}