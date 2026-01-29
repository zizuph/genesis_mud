/* 
 * Warfare masterwork standard wand file for the various factions.
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

inherit "/std/object";
inherit "/lib/holdable_item";
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

public void   setup_warfare_wand(int level, string faction);
void          add_skill_bonus(object who, int skill);

int           gLevel, gType, gHit, gPen, gHand, gWeight, gSpellpower;

// Whether the gem cavity is filled (1) or empty (0)
int           crystal_one;
// Sets the possible crystal skill type
int           crystal_one_skill;

// Sets the possible crystal hit bonus for spell power calculations
int           crystal_one_hit;
// Sets the possible crystal pen bonus for spell power calculations
int           crystal_one_pen;

// Sets whether the crystal is skill activated
int           crystal_one_activated;
// Set the shape of the gem cavities
string        crystal_shape_one;
// Set the id of the gems 
string        crystal_id_one;

string        gFaction;

public int
query_krynn_warfare_wand()
{
    return 1;
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

// Sets the crystal bonuses to the wand
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

            if(objectp(query_holder()) && !crystal_one_activated)
            {
                add_skill_bonus(query_holder(), crystal_one_skill);
                crystal_one_activated = 1;
            }
        }
    }
}

public string
query_wand_faction()
{
    return gFaction;
}

public void
set_wand_faction(string str)
{
    gFaction = str;
}

varargs void
set_wand_level(int level = 0, string faction = "free")
{
    if ( !level )
        gLevel = 0;
    else
        gLevel = level;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 0)
        gLevel = 0;

    if ( !faction )
        gFaction = "free";
    else
        gFaction = faction;

    if (!crystal_one)
        crystal_one = 0;

    if (!crystal_one_skill)
        crystal_one_skill = 0;

    if (!crystal_one_activated)
        crystal_one_activated = 0;

    if (!crystal_shape_one)
        crystal_shape_one = "ellipse";

    gSpellpower = 35;
        
    setup_warfare_wand(gLevel, gFaction);
}

public void
setup_warfare_wand(int level, string faction)
{

    gSpellpower = min(45, (35 + crystal_one_pen + crystal_one_hit));

    if(!query_commodity_name())
        set_commodity_name("mw wand");

    set_commodity_value(400);
}

string
warfare_wand_short()
{
    string short;

    short = "wand";
    add_name("wand");
    add_adj("masterwork");
    set_crystal_shape_one("ellipse");

    return short;
}

string
query_crystal_slot_desc()
{
    string cav_desc, link_desc;

    if(!crystal_one)
    {
        return "Atop of the " +short()+ " is a silver clawlike clasp, " +
            "resembling the claw of an eagle. It is currently empty, " + 
            "however looks like it could hold an ellipse-shaped crystal.";
    }
    else
    {
        string gem_desc1 = MASTERWORK_GEM_PROPS[crystal_id_one][3];  
        link_desc = LANG_ADDART(gem_desc1);         

        return "Atop of the " +short()+ " is a silver clawlike clasp, " +
            "resembling the claw of an eagle, holding " +link_desc+ ".";
    }

    return "Hmm... bugged out.";
}

public string
query_warfare_short(string faction)
{
    if(faction == "pot")
    {
        return "dark steel rod";
    }
    else if(faction == "blue" || faction == "red" || faction == "white" ||
        faction == "black" || faction == "green")
    {
        return faction + "-tinted rod";
    }
    else if(faction == "knights")
    {
        return "engraved steel rod";
    }
    else if(faction == "neidar")
    {
        return "engraved steel rod";
    }
    else if(faction == "qualinesti")
    {
        return "engraved ash wand";
    }
    else if(faction == "free")
    {
        return "engraved ironwood wand";
    }
    else
    {
        return "engraved ironwood wand";
    }
}

string
warfare_wand_long()
{
    string long;
    string faction = gFaction;

    if(faction == "pot")
    {
        string short = query_short();
        long = "This is a rod of dark steel, carved with runes " +
            "of homage to the Queen of Darkness. " + 
            query_crystal_slot_desc()+ "\n";
        set_name("rod");
        set_short("dark steel rod");
        add_adj("dark");
        add_adj("steel");

    }
    else if(faction == "blue" || faction == "red" || faction == "white" ||
        faction == "black" || faction == "green")
    {
        string short = query_short();
        long = "This is a rod of steel tinted " +faction+ ", with " +
            "silver inlaid carvings of dragons entwined around it. " +
            query_crystal_slot_desc()+ "\n";
        set_name("rod");
        set_short(faction + "-tinted rod");
        add_adj(faction);
        add_adj(faction+ "-tinted");
        add_adj("tinted");

    }
    else if(faction == "knights")
    {
        string short = query_short();

        long = "This is an engraved steel rod, made from the finest " +
            "steel forged at the quarries of Garnet. " +
            query_crystal_slot_desc()+ "\n";
        set_name("rod");
        set_short("engraved steel rod");
        add_adj("engraved");
        add_adj("steel");

    }
    else if(faction == "neidar")
    {
        string short = query_short();

        long = "This is an engraved steel rod, made from the finest " +
            "steel forged at the quarries of Iron Delving. " +
            query_crystal_slot_desc()+ "\n";
        set_name("rod");
        set_short("engraved steel rod");
        add_adj("engraved");
        add_adj("steel");

    }
    else if(faction == "qualinesti")
    {
        string short = query_short();

        long = "This is an engraved wand of ash, carved with " +
            "beautiful elven sigils inlaid with silver. " +
            query_crystal_slot_desc()+ "\n";
        set_short("engraved ash wand");
        add_adj("engraved");
        add_adj("ash");

    }
    else if(faction == "free")
    {
        string short = query_short();

        long = "This is an engraved wand made from rare " +
            "ironwood, and carved with mystical sigils " +
            "inlaid with silver. " +
            query_crystal_slot_desc()+ "\n";
        set_short("engraved ironwood wand");
        add_adj("engraved");
        add_adj("ironwood");

    }
    else
    {
        string short = query_short();

        long = "This is an engraved wand made from rare " +
            "ironwood, and carved with mystical sigils " +
            "inlaid with silver. " +
            query_crystal_slot_desc()+ "\n";
        set_short("engraved ironwood wand");
        add_adj("engraved");
        add_adj("ironwood");

    }

    return long;
}

public void
create_warfare_wand()
{

    if ( !strlen(gFaction) )
        set_wand_level();

}

void
add_masterwork_magic_props()
{
    int gem_total = 40;
    int magic_value = gem_total; 
    string magic_info_string = "";

    if(crystal_one)
    {
        magic_info_string += "Inserted into the " +short()+ " is ";

        string gem_desc = MASTERWORK_GEM_PROPS[crystal_id_one][3];  
        gem_desc = LANG_ADDART(gem_desc); 
        magic_info_string += gem_desc;

        string gem_benefit = MASTERWORK_GEM_PROPS[crystal_id_one][1];

        if(gem_benefit == "hit" || gem_benefit == "pen" ||
            gem_benefit == "hit-pen")
            magic_info_string += ", inert and ineffective.";
        else if(gem_benefit == "lesser_resist" || gem_benefit == "greater_resist")
        {
            string gem_resist_benefit = MASTERWORK_GEM_PROPS[crystal_id_one][2];
            magic_info_string += ", providing magical resistance to " +
                gem_resist_benefit;
        }
        else if(gem_benefit == "skill")
            magic_info_string += ", magically enhancing the holder's skills.";
        else if(gem_benefit == "special")
            magic_info_string += ", providing the holder with magical " +
                "enhancement when the gemstone is pressed.";
        else if(gem_benefit == "weight")
            magic_info_string += ", magically reducing the weight of the " +
                "wand.";
    }        

    add_prop(MAGIC_AM_ID_INFO, ({ "This " +short()+ " is a beautifully " +
        "crafted wand, designed to be able to insert magical " +
        "augmentation stones in to it and enhancing it with magic. " +
        magic_info_string + "\n", 25 }));

    add_prop(MAGIC_AM_MAGIC, ({ magic_value, "abjuration" }));

    add_prop(OBJ_S_WIZINFO, "This wand has been enchanted by having " +
        "one warfare reward gem inserted in to it. Gem " +
        "code can be found at /d/Krynn/common/warfare/rewards/\n");
}

string
cavity_wand_desc()
{
    string cavity_string, gem_type_string, cav_type1;
    string s1 = query_crystal_shape_one();

    if(gLevel > 0)
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
            "magical effect to the wand when affixed.";
    else
        cavity_string = "";

    return query_crystal_slot_desc() + " " + cavity_string + "\n";
}

public void
update_warfare_wand()
{
    if(strlen(crystal_id_one) > 1)
    {
        string gem_shape = MASTERWORK_GEM_PROPS[crystal_id_one][0];
        string benefit_type = MASTERWORK_GEM_PROPS[crystal_id_one][1];
        int benefit_bonus = MASTERWORK_GEM_PROPS[crystal_id_one][2];

        set_crystal_slot(1, crystal_id_one, gem_shape, benefit_type,
           benefit_bonus);
    }

    set_name("wand");
    set_short(warfare_wand_short());
    set_long(warfare_wand_long());

    // need to set for commodity hooks to work with plural_short()
    set_pshort(short() + "s");

    string s1 = query_crystal_shape_one();

    add_item(({ s1 +"-shaped clasp", s1+ " shaped clasp", 
        "clasp", s1+ "drop clasp", "clasp", s1+ "drop-shaped clasp",
        "runes", "silver-inlay runes", "dark empty clasp", "empty clasp" }),
            cavity_wand_desc());

    add_prop(OBJ_I_VALUE, 4000);
    add_prop(OBJ_I_VOLUME,200);

    int weight_mod = 4 - min(3, gWeight);
    add_prop(OBJ_I_WEIGHT, 3000 * weight_mod / 4 );

    set_slots(W_ANYH);
    set_keep(1);
    set_magic_spellpower(gSpellpower);

    if(crystal_one)
        add_masterwork_magic_props();

/*  To do - Add skill boost if held
    if (objectp(query_holder()))
        query_holder()->update_weapon(this_object());
*/
}

public void
create_object()
{
    create_warfare_wand();
    update_warfare_wand();
}

/*
 * Function name:        leave_env
 * Description  :        This function needs to be overridden
 *                       so the wand works properly
 * Arguments    :        object env, object to
 *                       
 */
void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

/*
 * Function name:        appraise_object
 * Description  :        This function needs to be overridden
 *                       for the wand to works properly
 * Arguments    :        int num
 *                       
 */
void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();

    if(gSpellpower)
        write(item_spellpower_desc());
}
string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
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
 * Function name:        hold
 * Description  :        Handles the holding of the wand
 * Returns      :        0
 *                       
 */
public mixed
hold()
{
    if(crystal_one && (query_crystal_shape_one() == "ellipse"))
    {
        // while zero is technically a skill number, it will
        // cause errors if we allow it
        if(!crystal_one_activated && crystal_one_skill)
        {
            add_skill_bonus(holder, crystal_one_skill);
            crystal_one_activated = 1;
        }
    }
    
    return 0;
}
/*
 * Function name:        release
 * Description  :        Handles the releasing of the wand
 * Returns      :        0
 *                       
 */
public mixed
release()
{
    if(crystal_one && (query_crystal_shape_one() == "ellipse"))
    {
        if(crystal_one_activated && crystal_one_skill)
        {
            remove_skill_bonus(holder, crystal_one_skill);
            crystal_one_activated = 0;
        }
    }
     
    return 0;
}

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
        notify_fail("There is already an augmentation crystal inserted " +
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

        if(query_free_gem_slot("ellipse"))
            spare_slot1 = "ellipse";

        player->catch_tell("The " +oblist[0]->query_short()+ " is the " +
            "wrong shape to insert into your " +short()+ ". You need " +
            LANG_ADDART(spare_slot1) + " shaped crystal to insert " +
            "in to your wand.\n");
        return 1;
    }

    int gem_slot = query_free_gem_slot(gem_shape);
    string ward_type, chest_type;

    if(query_free_gem_slot("tear"))
        ward_type = "wards of protection";
    else
        ward_type = "enhancement magics";

    chest_type = "clawlike clasp atop";

    set_crystal_slot(gem_slot, gem_id, gem_shape, benefit_type, benefit_bonus);

    player->catch_tell("You insert " +oblist[0]->short()+ " into "+
        "the " +chest_type+ " your " +short()+ ". The silvery runes " +
        "along the " +short()+ " glow as it locks in to place and " +
        ward_type+ " are activated.\n");

    tell_room(environment(player), QCTNAME(player)+ " inserts " + 
        oblist[0]->short()+ " into " +HIS(player)+ " " +query_short()+ ".\n", 
        ({ player }), player);

    setup_warfare_wand(gLevel, gFaction);
    update_warfare_wand();
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
    gLevel = atoi(a[0]);
    gFaction = (a[1]);
    crystal_id_one = (a[2]);
    gSpellpower = atoi(a[3]);
    update_warfare_wand();
}

string
query_recover()
{
    return MASTER + ":"  + gLevel + "&&" + 
        gFaction + "&&" + crystal_id_one + "&&" + gSpellpower;
}