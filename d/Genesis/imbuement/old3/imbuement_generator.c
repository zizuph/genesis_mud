/*
 *
 */
#pragma strict_types
#include "imbuement.h"

#include <macros.h>
#include <files.h>
#include <wa_types.h>   //for W_BOTH

//#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Definitions */

/* Global Variables */
mapping             imbuements;
int                 max_id = 0;
public mapping      stone_results = ([
                        "heavenstone" : "bane_dragon",
                        "gallstone"   : "bane_dwarf",
                        "charstone"   : "bane_elf",
                        "gearstone"   : "bane_gnome",
                        "darkstone"   : "bane_goblin",
                        "piestone"    : "bane_hobbit",
                        "fellstone"   : "bane_human",
                        "hoofstone"   : "bane_minotaur",
                        "doomstone"   : "bane_ogre",
                        "firestone"   : "bane_troll",
                        "lifestone"   : "bane_undead",
                        "ruststone"   : "damage_acid",
                        "blowstone"   : "damage_air",
                        "snapstone"   : "damage_cold",
                        "blackstone"  : "damage_death",
                        "sinkstone"   : "damage_earth",
                        "ampstone"    : "damage_electricity",
                        "orangestone" : "damage_fire",
                        "bluestone"   : "damage_water", 
                        "nightstone"  : "effect_darkness",
                        "torchstone"  : "effect_darkvision",
                        "mercurystone": "effect_haste",
                        "balmstone"   : "effect_healing",
                        "morningstone": "effect_light",
                        "aspstone"    : "effect_poison",
                        "grogstone"   : "effect_slow",
                        "ironstone"   : "effect_unbreakable",
                        "wardstone"   : "extra_ac",
                        "guidestone"  : "extra_hit",
                        "stingstone"  : "extra_pen",
                        "salvestone"  : "resist_acid",
                        "tarpstone"   : "resist_air",
                        "woolstone"   : "resist_cold",
                        "larsstone"   : "resist_death",
                        "riverstone"  : "resist_earth",
                        "rubberstone" : "resist_electricity", 
                        "powderstone" : "resist_fire",
                        "mummystone"  : "resist_life",
                        "quietstone"  : "resist_magic",
                        "sweatstone"  : "resist_poison",
                        "duckstone"   : "resist_water", 
                        "twinstone"   : "skill_2handed",
                        "guststone"   : "skill_air",
                        "eyestone"    : "skill_awareness",
                        "cleavestone" : "skill_axe",
                        "molestone"   : "skill_blindcombat",
                        "crushstone"  : "skill_club",
                        "corpsestone" : "skill_death",
                        "shieldstone" : "skill_defence",
                        "soilstone"   : "skill_earth",
                        "emberstone"  : "skill_fire",
                        "needlestone" : "skill_knife",
                        "ankhstone"   : "skill_life",
                        "deftstone"   : "skill_parry",
                        "skewerstone" : "skill_polearm",
                        "rodentstone" : "skill_sneakhide",
                        "lodestone"   : "skill_spellcraft",
                        "edgestone"   : "skill_sword",
                        "palmstone"   : "skill_unarmed",
                        "surfstone"   : "skill_water",
                        "dwarfstone"  : "stat_con",
                        "hobbitstone" : "stat_dex",
                        "steelstone"  : "stat_dis",
                        "gnomestone"  : "stat_int",
                        "ogrestone"   : "stat_str",
                        "elfstone"    : "stat_wis",
                          ]);

string              *mods_both   = ({ "bane_dragon",
                                      "bane_dwarf",
                                      "bane_elf",
                                      "bane_gnome",
                                      "bane_goblin",
                                      "bane_hobbit",
                                      "bane_human",
                                      "bane_minotaur",
                                      "bane_ogre",
                                      "bane_troll",
                                      "bane_undead", 
                                      "effect_darkness",
                                      "effect_darkvision",
                                      "effect_haste",
                                      "effect_healing",
                                      "effect_light",
                                      "effect_slow",
                                      "effect_unbreakable",
                                      "skill_2handed",
                                      "skill_air",
                                      "skill_awareness",
                                      "skill_axe",
                                      "skill_blindcombat",
                                      "skill_club",
                                      "skill_death",
                                      "skill_defence",
                                      "skill_earth",
                                      "skill_fire",
                                      "skill_knife",
                                      "skill_life",
                                      "skill_parry",
                                      "skill_polearm",
                                      "skill_sneakhide",
                                      "skill_spellcraft",
                                      "skill_sword",
                                      "skill_water",
                                      "stat_con",
                                      "stat_dex",
                                      "stat_dis",
                                      "stat_int",
                                      "stat_str",
                                      "stat_wis",
                                   });

string              *mods_weapon = mods_both +
                                   ({ "damage_acid",
                                      "damage_air",
                                      "damage_cold",
                                      "damage_death",
                                      "damage_earth",
                                      "damage_electricity",
                                      "damage_fire",
                                      "damage_water",
                                      "effect_poison",
                                      "extra_hit",
                                      "extra_pen",
                                   });
string              *mods_armour = mods_both +
                                   ({ "extra_ac",
                                      "resist_acid",
                                      "resist_air",
                                      "resist_cold",
                                      "resist_death",
                                      "resist_earth",
                                      "resist_electricity", 
                                      "resist_fire",
                                      "resist_life",
                                      "resist_magic",
                                      "resist_poison",
                                      "resist_water", 
                                      "skill_unarmed",
                                   });

/* Prototypes */
public void             create();
public varargs int   imbue(object obj, string imb1, int lev1, string imb2,
                            int lev2, string imb3, int lev3, int id);
public string           add_imbuement(object ob, string mod, int lvl, int num,
                            int id);
public void             destructed(int id, string caller);
public void             set_recover(int id, string recover);
public string           get_recover(int id);
public void             reimbue(object obj, int id);
public static string    rand_imbuement(object ob, string mod1 = 0,
                            string mod2 = 0);
public int              imbue_random(object obj);

public string          *query_mods_weapon()   { return mods_weapon;   }
public string          *query_mods_armour()   { return mods_armour;   }
public mapping          query_stone_results() { return stone_results; }

/*
 * Function name:        create
 * Description  :        set up
 */
public void
create()
{
    setuid();
    seteuid(getuid());
    imbuements = IMBUE_MASTER->get_imbuements();
} /* create */

/*
 * Function name:        imbue
 * Description  :        imbue an object
 */
public varargs int
imbue(object obj,
    string imb1, int lev1, string imb2, int lev2, string imb3, int lev3,
    int id)
{
    int count, i;
    mixed *magic_arr;
    if (!obj)
        return 0;
    if (obj->query_imbue_info())
        return 0;
    send_debug_message("Imbuement", file_name(obj) + " imbuing.");

    /* Since the mods are all magic, we set the MAGIC_AM_MAGIC info.
     * As we are modding an unknown item that might already have
     * magical properties, we first check to see if that is the case,
     * and if so add that to the equation.
     */
    i = 0;
    magic_arr = obj->query_prop(MAGIC_AM_MAGIC);

    if (magic_arr)
    {
        i = magic_arr[0];
    }

    i += (lev1 + lev2 + lev3) * 10;

    obj->add_prop(MAGIC_AM_MAGIC, ({ MIN(i, 100), "enchantment" }) );

    /* Now, we'll do the same thing for our MAGIC_AM_ID_INFO. At the
     * same time, we'll go ahead and add the actual effect shadows. */
    magic_arr = obj->query_prop(MAGIC_AM_ID_INFO);

    if (!sizeof(magic_arr))
    {
        magic_arr = ({});
    }

    magic_arr += ({ IMBUE_M_ID, 10 });

    if (!id)
        id = IMBUE_MASTER->get_id();
    if (imb1 == "r")
        //imb1 = one_of_list(obj->check_weapon() ? mods_weapon : mods_armour);
        imb1 = rand_imbuement(obj);
    if (imb1)
    {
        add_imbuement(obj, imb1, lev1, 1, id);
        magic_arr += ({ obj->query_imbue_info() + "\n", 50 });
    }
    if (imb2 == "r")
        imb2 = rand_imbuement(obj, imb1);
    if (imb2)
    {
        add_imbuement(obj, imb2, lev2, 2, id);
        magic_arr += ({ obj->query_imbue_info() + "\n", 50 });
    }
    if (imb3 == "r")
        imb3 = rand_imbuement(obj, imb1, imb2);
    if (imb3)
    {
        add_imbuement(obj, imb3, lev3, 3, id);
        magic_arr += ({ obj->query_imbue_info() + "\n", 50 });
    }

    imbuements[id] = ({ obj, imb1, lev1, imb2, lev2, imb3, lev3, 1, 0 });
    IMBUE_MASTER->set_updated();
    for (int i = 1; i <= 3; i++)
    {
        if (obj->get_shadow(i))
            count++;
    }
    obj->add_prop(MAGIC_AM_ID_INFO, magic_arr);
    obj->add_prop(IMBUE_SHORT, POWER_SHORT[count]);
    obj->add_adj(POWER_SHORT[count]);

    return id;
}


/*
 * Function name:        add_imbuement
 * Description  :        add a specific imbuement to a given object.
 * Arguments    :        object ob - the object receiving the imbuements
 *                       string mod - the name of the imbuement
 *                       int lvl - The power rating of the imbuement (1-3)
 *                       int num - The order number of the imbuement (1-3)
 * Returns      :        a string containing the info this specific imbuement
 *                       should show for a magic id spell.
 */
public string
add_imbuement(object ob, string mod, int lvl, int num, int id)
{
    object  shadow;

    send_debug_message("Imbuement", sprintf("%O %i:%s lev %i  ID %i", ob, num,
        mod, lvl, id));
    shadow = clone_object(SHADOW_DIR + mod + "_shadow");
    if (shadow->has_imbue_shadow())
        send_debug_message("Imbuement", "OK");
    else
        send_debug_message("Imbuement", "Failed!");

    shadow->set_id(id);
    shadow->set_num(num);
    shadow->shadow_me(ob);
    ob->init_imbue_shadow(lvl);

    return shadow->query_imbue_info() + "\n";
} /* add_imbuement */


/*
 * Function name:        destructed
 * Description  :        called by a shadow when destructed
 * Arguments    :        int id - ID of object
 *                       string caller - calling function
 */
public void
destructed(int id, string caller)
{
    if (!imbuements[id])
        return;
    if (caller == "quit")
    {
        imbuements[id][COL_STA] = 2;
    }
    else
    {
        imbuements[id][COL_STA] = -1;
    }
    IMBUE_MASTER->set_updated();
} /* destructed */


/*
 * Function name:        set_recover
 * Description  :        called by a shadow when destructed
 * Arguments    :        object obj - object to reimbue
 *                       int id - ID of object
 */
public void
set_recover(int id, string recover)
{
    if (!imbuements[id])
        return;
    imbuements[id][COL_REC] = recover;
    IMBUE_MASTER->set_updated();
} /* set_recover */


/*
 * Function name:        get_recover
 * Description  :        Get recovery info for object
 * Arguments    :        int id - ID of object
 * Returns      :        string - recovery string
 */
public string
get_recover(int id)
{
    if (!imbuements[id])
        return 0;
    return imbuements[id][COL_REC];
} /* get_recover */


/*
 * Function name:        reimbue
 * Description  :        Recover imbuements for object
 * Arguments    :        int id - ID of object
 * Returns      :        string - recovery string
 */
public void
reimbue(object obj, int id)
{
    mixed *rec = imbuements[id];
    if (!rec)
        return;
    imbue(obj, rec[COL_TY1], rec[COL_LV1], rec[COL_TY2], rec[COL_LV2],
        rec[COL_TY3], rec[COL_LV3], id);
//    if (rec[COL_TY1])
//        add_imbuement(obj, rec[COL_TY1], rec[COL_LV1], 1, id);
//    if (rec[COL_TY2])
//        add_imbuement(obj, rec[COL_TY2], rec[COL_LV2], 2, id);
//    if (rec[COL_TY3])
//        add_imbuement(obj, rec[COL_TY3], rec[COL_LV3], 3, id);
//    rec[COL_STA] = 1;
} /* reimbue */


/*
 * Function name:        rand_imbuement
 * Description  :        Find a random imbuement suitable for an object
 * Arguments    :        object - object to get an imbuement for
 * Returns      :        string - imbuement name
 */
public string
rand_imbuement(object ob, string mod1 = 0, string mod2 = 0)
{
    //mods_weapon = ({ "skill_sword", "skill_club" });
    string imb, mod, race, *races;
    int weapskill;
    object env = environment(ob);
    while (!imb)
    {
        imb = one_of_list(ob->check_weapon() ? mods_weapon : mods_armour);
        mod = SHADOW_DIR + imb + "_shadow";
        races = mod->query_races();
        if (races)
        {
            race = env->query_race_name();
            if (member_array(race, races) >= 0)
            {
                send_debug_message("Imbuement", "Race " + race +
                    " subject to bane in " + imb + ".");
                imb = 0;
            }
        }
        weapskill = mod->query_weapon_skill();
        if (weapskill)
        {
            if (ob->query_wt() != weapskill - 1)
            {
                send_debug_message("Imbuement", "Wrong weapon type for " +
                    imb + ".");
                imb = 0;
            }
        }
        if ((imb == "skill_2handed") && (ob->query_hands() == W_BOTH))
        {
            send_debug_message("Imbuement", "2handed on both-hands weapon.");
            imb = 0;
        }
        if (imb && ((imb == mod1) || (imb == mod2)))
        {
            send_debug_message("Imbuement", "Already have " + imb + ".");
            imb = 0;
        }
    }
    return imb;
} /* rand_imbuement */

/*
 * Function name:        imbue_random
 * Description  :        Generate random imbuement
 * Arguments    :        object obj - Object to imbue
 * Returns      :        int - ID of imbuement
 */
public int
imbue_random(object obj)
{
    int pow1, pow2, pow3, id;
    // One
    pow1 = 1;
    if (random(99) < 10)
    {
        pow1 = 2;
        if (random(99) < 20)
            pow1 = 3;
    }
    if (random(99) < 10)
    {
        // Two
        pow2 = 1;
        if (random(99) < 10)
        {
            pow2 = 2;
            if (random(99) < 10)
                pow2 = 3;
        }
        if (random(99) < 10)
        {
            // Three
            pow3 = 1;
            if (random(99) < 10)
            {
                pow3 = 2;
                if (random(99) < 20)
                    pow3 = 3;
            }
            send_debug_message("Imbuement", file_name(obj) +
                " three imbuements.");
            id = imbue(obj, "r", pow1, "r", pow2, "r", pow3);
            return id;
        }
        send_debug_message("Imbuement", file_name(obj) +
            " two imbuements.");
        id = imbue(obj, "r", pow1, "r", pow2);
        return id;
    }
    send_debug_message("Imbuement", file_name(obj) +
        " one imbuement.");
    id = imbue(obj, "r", pow1);
    return id;
} /* imbue_random */


/*
 * Function name:        imbue_log
 * Description  :        Allow something from outside of the Genesis dir
 *                       to log something using this function call to the
 *                       imbuement log directory.
 * Arguments    :        string log - the log file
 *                       string txt - the log entry
 */
public void
imbue_log(string log, string txt)
{
    write_file(IMBUE_LOG_DIR + log, txt);
} /* imbue_log */