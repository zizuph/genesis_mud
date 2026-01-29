/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Extra functionality for npcs
 *
 */

#include "/d/Terel/include/Terel.h"

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone.
 */
public string*
query_object_list()
{
    return ({ });
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    int i;
    string *list;
    
    FIX_EUID;

    list = TO->query_object_list();
    for (i = 0; i < sizeof(list); i++)
        clone_object(list[i])->move(this_object(), 1);
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield all");
    TO->command("wear all");
}

/*
 * Function name: berate_wankers
 * Description: Berate the spnking Solamnian Knights
 */
public string
berate_wankers()
{
    object *oblist;
    int i;
    int wankers_here = 0;

    oblist = all_inventory(ETO);
    for (i = 0; i < sizeof(oblist); i++) {
        if ((oblist[i]->query_guild_name_occ() == "Solamnian Knights") ||
            (oblist[i]->query_guild_name_lay() == "Solamnian Knights")) {
            wankers_here = 1;
            break;
        }
    }

    if (wankers_here)
        return "You spanking knights can take your Oath and your Measure " +
            "and shove 'em right up yer ass, where the sun ain't shining!";
    else
        return "I destroy those pitiful worshippers of Paladine!";
}

/*
 * Function name: query_knight_prestige
 * Description:   Prestige is used by Solamnian knights in Krynn.  We use the
 *                formula suggested by Aridor.
 * Returns:       the prestige value.
 */
public int
query_knight_prestige()
{
    int stat_ave;

    if (TO->query_alignment() < -10) {
        stat_ave = TO->query_average_stat();
        return (stat_ave * stat_ave) / 10;
    }

    return 0;
}

void
set_spell_prop(object ob)
{
    if (!TO->query_prop(LIVE_O_SPELL_ATTACK))
        TO->add_prop(LIVE_O_SPELL_ATTACK, ob);
}

/*
 * query_my_enemies(): written by Mortricia
 */

public varargs object *
query_my_enemies(int how_to_sort = 0)
{
    int i, j, swap = 0;
    object foo, *all, *enemies = ({ });

    all = all_inventory(environment(TO)) - ({ TO });

    for (i=0; i<sizeof(all); i++) {
        if (living(all[i]) && member_array(TO, all[i]->query_enemy(-1)) >= 0)
            enemies += ({ all[i] });
    }
    if (how_to_sort == 0) return enemies;
    
    for (i=0; i<sizeof(enemies)-1; i++) {
        for (j=i+1; j<sizeof(enemies); j++) {
            switch (how_to_sort) {
                case -1:     /* Sort in decreasing stat order */
                    if (enemies[i]->query_average_stat() <
                        enemies[j]->query_average_stat()) swap = 1;
                    break;
                case 1:      /* Sort in increasing stat order */
                    if (enemies[i]->query_average_stat() >
                        enemies[j]->query_average_stat()) swap = 1;
                    break;
                default:
                    return enemies;
            }
            if (swap) {
                foo = enemies[i];
                enemies[i] = enemies[j];
                enemies[j] = foo;
                swap = 0;
            }
        }
    }
    return enemies;
}

public object
query_smallest_enemy()
{
    object *enemies;

    if (sizeof(enemies = TO->query_my_enemies(1)) == 0) return 0;

    return enemies[0];
}

public object
query_biggest_enemy()
{
    object *enemies;

    if (sizeof(enemies = TO->query_my_enemies(-1)) == 0) return 0;

    return enemies[0];
}
