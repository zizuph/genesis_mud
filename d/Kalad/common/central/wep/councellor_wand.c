/*
 * /d/Kalad/common/central/wep/councellor_wand.c
 * A wand for the mage at Urian, it will give 10 increased
 * skill in the elemental skill that the user is most skilled in,
 * aswell as 5 spellcraft.
 *
 * Created Nov 2017, by Andreas Bergstrom ( Zignur )
 *
 * Added set_keep, Arman Sep 2018
 *
 * Added item expiration functionality, Arman April 2020
 *
 * Added as a magic enhancer as part of the updated magic 
 * system, Arman December 2021
 */
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include "/d/Kalad/defs.h"

/* Global Variables */
static mapping      skill_list = ([]);
static int         *element_list = ({   SS_ELEMENT_FIRE, SS_ELEMENT_WATER,
                                        SS_ELEMENT_LIFE, SS_ELEMENT_DEATH,
                                        SS_ELEMENT_EARTH, SS_ELEMENT_AIR });
                                        
/* Prototypes */
public void         create_wand();
nomask void         create_object();
void                leave_env(object env, object to);
void                appraise_object(int num);
public int          get_highest_elemental_skill(object player);
public void         limited_extra_skill(object player, int skill, int value);
public mixed        hold();
public mixed        release();


/*
 * Function name:        create_wand
 * Description  :        Function used if we want to customize
 *                       the wand
 */
public void
create_wand()
{
    // Mask this function to customize the wand.
}


/*
 * Function name:        create_object
 * Description  :        Function used to create the wand
 *                   
 */
nomask void
create_object()
{
    string *adjs = ({ "twisted", "thin", "black" });
    set_name("wand");
    set_adj(adjs[0]);
    add_adj(adjs[1]);
    add_adj(adjs[2]);
    set_long("This "+ adjs[0] + " "+ adjs[1] + " "+ adjs[2] +" wand it" +
       " is marked with strange ancient runes. The wand itself is carved" +
       " out from a piece of twisted wood, it is almost as if the wand" +
       " itself is twisting in torment.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 25, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"This wand seems to be enchanted " +
       " with some ancient very powerful magic. You get the feeling " +
       " that this wand will grant its user increased magical " +
       " abilities and enhance their spells.\n", 10 }));  
    
    add_prop(OBJ_S_WIZINFO, "This is the wand used by Urians mage. " +
       "/d/Kalad/common/central/npc/lord_councelor. The wand will offer " +
       " 10 increased skill in the Elemental damage type that the user is" +
       "most skilled in, aswell as 5 in spellcraft. It also provides " +
       "a spellpower rating of 45.\n");
      
    add_prop(OBJ_I_VALUE,1728);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,250);

    set_magic_spellpower(45); 
    set_slots(W_ANYH);
    set_keep(1);

    //Enable default item expiration
    set_item_expiration();

    /* Call the create_wand function for customization purposes */
    create_wand();
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
    write(item_spellpower_desc());
}

/*
 * Function name:        get_highest_elemental_skill
 * Description  :        Checks which is the highest elemental
 *                       skill of the player.
 * Arguments    :        object player
 * Returns      :        e_skill the nr of the elemental skill
 *                       
 */
public int
get_highest_elemental_skill(object player)
{
    int e_skill;
    
    foreach(int skill: element_list)
    {
        if (player->query_skill(skill) > 99)
            continue;
        
        if (!e_skill || player->query_base_skill(e_skill) <
            player->query_base_skill(skill))
            e_skill = skill;
    }
    
    return e_skill;
}


/*
 * Function name:        limited_extra_skill
 * Description  :        add the extra skill to the player
 * Arguments    :        object player, int skill, int value
 *                       
 */
public void
limited_extra_skill(object player, int skill, int value)
{
    if ((player->query_skill(skill) + value) > 100)
        value = 100 - player->query_skill(skill);
    
    player->set_skill_extra(skill, player->query_skill_extra(skill) + value);
    skill_list[skill] = value;
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
    int element_skill = get_highest_elemental_skill(holder);
    
    limited_extra_skill(holder, SS_SPELLCRAFT, 5);
    limited_extra_skill(holder, element_skill, 10);
    holder->catch_msg("You feel more confident in your magical arts, as" +
          " you wrap your fingers around your " +short()+ ".\n");
    
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
    foreach(int skill, int value: skill_list)
    {
        limited_extra_skill(holder, skill, -value);
        skill_list[skill] = 0;
        
    }
    holder->catch_msg("You feel less confident in your magical" +
        " arts, as you release your " + short() +".\n");
     
    return 0;
}

string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}

void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    ::init_keep_recover(arg);
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}