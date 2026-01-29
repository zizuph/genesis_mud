/* 
 * /d/Emerald/std/ogre.c
 * 
 * The standard Emerald orc npc.
 *
 * Created (date unknown) by Shiva?
 *
 * Modification log: 6-28-2006 (Gorboth):
 *                     Altered to fit with the Army of Darkness concepts
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Emerald/std/emerald_monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/* prototypes */
public void        config_ogre(int level);
public void        create_ogre();
public void        create_emerald_monster();


/*
 * Function name:        config_ogre
 * Description  :        set up the standard specs for the ogre race
 */
public void
config_ogre(int level)
{
    set_stats(({ level * 15 / 10 + random(10),
                 level * 9 / 10 + random(10),
                 level * 15 / 10 + random(10),
                 level * 3 / 10 + random(10),
                 level * 3 / 10 + random(10),
                 level * 10 / 10 + random(10)}));

    set_all_attack_unarmed(min(40, query_stat(SS_DEX) / 3),
                           min(80, query_stat(SS_STR) / 3));

    set_skill(SS_WEP_CLUB, level * 7 / 10 + random(10));
    set_skill(SS_WEP_SWORD, level * 7 /10 + random(10));
    set_skill(SS_WEP_POLEARM, level * 7 / 10 + random(10));
    set_skill(SS_WEP_KNIFE, level * 7 / 10 + random(10));
    set_skill(SS_WEP_AXE, level * 7 / 10 +  random(10));
    set_skill(SS_UNARM_COMBAT, level + random(10));
    set_skill(SS_DEFENSE, level * 7 / 10 + random(10));
    set_skill(SS_AWARENESS, level * 3 /10 + 20 + random(10));
    set_skill(SS_BLIND_COMBAT, max(40, level * 6 / 10 + random(10)));

    add_prop(CONT_I_HEIGHT, 300 + random(100));
    add_prop(CONT_I_WEIGHT, 400000 + random(300000));
    add_prop(CONT_I_VOLUME, 420000 + random(300000));
  
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 5);

    /* thick skin is advantageous */ 
    set_all_hitloc_unarmed(MIN( (level / 5), 40) );
} /* config_ogre */


/*
 * Function name:        create_ogre
 * Description  :        dummy function to be used in inheriting files
 */
public void
create_ogre()
{
    config_ogre(80);
} /* create_ogre */


/*
 * Function name:        create_emerald_monster
 * Description  :        set up the npc with domain and other presets
 */
nomask void
create_emerald_monster()
{
    set_name("ogre");
    set_race_name("ogre");
    set_adj(({ "ogre", "ogreish", "ogrish" }));
    set_appearance(50 + random(50));
    set_appearance_offset(-30);
    
    create_ogre();
} /* create_ogre */
