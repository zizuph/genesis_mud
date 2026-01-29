/*
 *
 */
#pragma strict_types
#include "imbuement.h"

#include <macros.h>
#include <files.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Definitions */

/* Global Variables */
mapping             imbuements;
int                 max_id = 0;
string              *mods_weapon = ({ "bane_dragon", "bane_dwarf", "bane_elf", "bane_gnome", "bane_goblin", "bane_hobbit", "bane_human", "bane_minotaur", "bane_ogre", "bane_troll", "bane_undead", "damage_acid", "damage_air", "damage_cold", "damage_death", "damage_earth", "damage_electricity", "damage_fire", "damage_water", "effect_darkness", "effect_darkvision", "effect_haste", "effect_healing", "effect_light", "effect_poison", "effect_slow", "effect_unbreakable", "extra_hit", "extra_pen", "skill_2handed", "skill_air", "skill_awareness", "skill_axe", "skill_blindcombat", "skill_club", "skill_death", "skill_defence", "skill_earth", "skill_fire", "skill_knife", "skill_life", "skill_parry", "skill_polearm", "skill_sneakhide", "skill_spellcraft", "skill_sword", "skill_water", "stat_con", "stat_dex", "stat_dis", "stat_int", "stat_str", "stat_wis",
});
string              *mods_armour = ({ "bane_dragon", "bane_dwarf", "bane_elf", "bane_gnome", "bane_goblin", "bane_hobbit", "bane_human", "bane_minotaur", "bane_ogre", "bane_troll", "bane_undead", "effect_darkness", "effect_darkvision", "effect_haste", "effect_healing", "effect_light", "effect_unbreakable", "extra_ac", "resist_acid", "resist_air", "resist_cold", "resist_death", "resist_earth", "resist_electricity", "resist_fire", "resist_life", "resist_magic", "resist_poison", "resist_water", "skill_2handed", "skill_air", "skill_awareness", "skill_axe", "skill_blindcombat", "skill_club", "skill_death", "skill_defence", "skill_earth", "skill_fire", "skill_knife", "skill_life", "skill_parry", "skill_polearm", "skill_sneakhide", "skill_spellcraft", "skill_sword", "skill_unarmed", "skill_water", "stat_con", "stat_dex", "stat_dis", "stat_int", "stat_str", "stat_wis",
});

/* Prototypes */
public void             create();
public varargs string   imbue(object obj, string imb1, int lev1, string imb2,
                            int lev2, string imb3, int lev3, int id);
public string           add_imbuement(object ob, string mod, int lvl, int num,
                            int id);
public void             destructed(int id, string caller);
public void             set_recover(int id, string recover);
public string           get_recover(int id);
public void             reimbue(object obj, int id);


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
public varargs string
imbue(object obj,
    string imb1, int lev1, string imb2, int lev2, string imb3, int lev3,
    int id)
{
    int count;
    if (!obj)
        return 0;
    if (obj->query_imbue_info())
        return 0;
    send_debug_message("Imbuement", file_name(obj) + " imbuing.");
    if (!id)
        id = IMBUE_MASTER->get_id();
    if (imb1 == "r")
        imb1 = one_of_list(obj->check_weapon() ? mods_weapon : mods_armour);
    if (imb1)
        add_imbuement(obj, imb1, lev1, 1, id);
    if (imb2 == "r")
        imb2 = one_of_list(obj->check_weapon() ? mods_weapon : mods_armour);
    if (imb2)
        add_imbuement(obj, imb2, lev2, 2, id);
    if (imb3 == "r")
        imb3 = one_of_list(obj->check_weapon() ? mods_weapon : mods_armour);
    if (imb3)
        add_imbuement(obj, imb3, lev3, 3, id);

    imbuements[id] = ({ obj, imb1, lev1, imb2, lev2, imb3, lev3, 1, 0 });
    IMBUE_MASTER->set_updated();
    for (int i = 1; i <= 3; i++)
    {
        if (obj->get_shadow(i))
            count++;
    }
    obj->add_prop(IMBUE_SHORT, POWER_SHORT[count]);
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
