#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include <ss_types.h>
#include <wa_types.h>
#include "../../default.h"
#include "../../khiraa.h"

#define MAX_KNIGHT_LEVEL 13

/* This is the shadow guild object for the Death Knighthood */
/* Sarr Apr.15.97      */
/* Modified by Sarr 10.Mar.98 for fixes */

/* strings that contain the alternative adjectives for this */
/* guild                                                    */
string adj1,adj2;


/*                *
 *  Guild titles  *
 *                */


#define TITLES ({ "Lesser Death Warrior of the Khiraa", \
                  "Death Warrior of the Khiraa", \
                  "Lesser Death Knight of the Khiraa", \
                  "Death Knight of the Khiraa", \
                  "Lesser Dark Paladin of the Khiraa", \
                  "Dark Paladin of the Khiraa", \
                  "Dark Paladin of the Thirteen Pillars", \
                  "Death Templar of the Khiraa", \
                  "Templar of the Nine Stones", \
                  "Unholy Blade of Shaadok Y'Sulgash", \
                  "Unholy Blade of the Namless Horror", \
                  "Lord Death Knight of the Khiraa", \
                  "Nightmare Death Knight of the Khiraa" })

#define FTITLES ({ "Lesser Death Warrior of the Khiraa", \
                   "Death Warrior of the Khiraa", \
                   "Lesser Death Knight of the Khiraa", \
                   "Death Knight of the Khiraa", \
                   "Lesser Dark Paladin of the Khiraa", \
                   "Dark Paladin of the Khiraa", \
                   "Dark Paladin of the Blood", \
                   "Death Templar of the Khiraa", \
                   "Templar of the Nine Stones", \
                   "Unholy Blade of Shaadok Y'Sulgash", \
                   "Unholy Blade of the Namless Horror", \
                   "Lady Death Knight of the Khiraa", \
                   "Nightmare Death Knight of the Khiraa" })
                  
#define AWARD_TITLES ({ "Blessed Hero of the Khiraa" , \
                        "Blessed Grand Hero of the Khiraa", \
                        "Blessed Savior of the Khiraa", \
                        "Blessed Grand Savior of the Khiraa", })
#define FAWARD_TITLES ({ "Blessed Heroine of the Khiraa", \
                         "Blessed Grand Heroine of the Khiraa", \
                         "Blessed Savior of the Khiraa", \
                         "Blessed Grand Savior of the Khiraa" })

#define CIRCLE_TITLE "Grand Master Death Knight of the Khiraa"
#define FCIRCLE_TITLE "Grand Mistress Death Knight of the Khiraa"
#define LIEU_TITLE "Master Death Knight of the Khiraa"

#define DISGRACED_TITLE "Disgraced Servent"

/* Made this person a member */

int
join_khiraa(object ob, string adjs, object inish)
{
    int res;
    object lay;
    setuid();
    seteuid(getuid());
    lay = clone_object(DK_LAY_SHADOW);
    res = lay->shadow_me(ob,DK_LAY_TYPE,DK_LAY_STYLE,DK_LAY_NAME);

    if(res != 1)
        return res;
    if(stringp(adjs))
        res = shadow_me(ob,DK_OCC_TYPE,DK_OCC_STYLE,DK_OCC_NAME,adjs);
    else
        res = shadow_me(ob,DK_OCC_TYPE,DK_OCC_STYLE,DK_OCC_NAME);

    KHIRAA_SERVER->add_member(shadow_who->query_real_name());

    write_file(JOIN_LOG,GTIME+": "+ob->query_real_name()+" entered "+
    "the Khiraa Knighthood through the hand of "+inish->query_real_name()+"\n");

    ob->clear_guild_stat(SS_OCCUP);
    ob->clear_guild_stat(SS_LAYMAN);
    
    return res;
}

/* This will set a new order level for the knight. Remember, only 
 * Knights can go from 1 to 13.
 */
void
set_guild_order(int i)
{
    if(i <= 0 || i > 13)
        return; // No go.
    KHIRAA_SERVER->set_guild_order(shadow_who->query_real_name(),i);
}

/* Return the Guild Order Level of the Player */
int
query_guild_order()
{
    int lvl = KHIRAA_SERVER->query_guild_order(shadow_who->query_real_name());
    if(lvl > MAX_KNIGHT_LEVEL)
    {
        lvl = MAX_KNIGHT_LEVEL;
        KHIRAA_SERVER->set_guild_order(shadow_who->query_real_name(),lvl);
    }
    return lvl;
}

/* Returns if we are the grand master or not */
int
query_circle()
{
    return KHIRAA_SERVER->query_circle_member(shadow_who->query_real_name());
}

/* For Death Knights, its either 0 or 3 */
/* 0 Will remove from the circle */

void
add_circle_member(int i)
{
    if(i != 0 && i != 3)
        return;
    KHIRAA_SERVER->add_circle_member(shadow_who->query_real_name(),i);
}


/* Extra speical adverbs for this guild */
string 
full_adverb(string str)
{
    if ((strlen(str) > 2) && wildmatch(str + "*", "eerily"))
    {
        return "eerily";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "darkly"))
    {
        return "darkly";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "spookily"))
    {
        return "spookily";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "weirdly"))
    {
        return "weirdly";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "unwholesomely"))
    {
        return "unwholesomely";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "vilely"))
    {
        return "vilely";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "mystifyingly"))
    {
        return "mystifyingly";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "blackly"))
    {
        return "blackly";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "cryptically"))
    {
        return "cryptically";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "enigmatically"))
    {
        return "enigmatically";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "gruesomely"))
    {
        return "gruesomely";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "horridly"))
    {
        return "horridly";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "hideously"))
    {
        return "hideously";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "horribly"))
    {
        return "horribly";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "luridly"))
    {
        return "luridly";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "terrifyingly"))
    {
        return "terrifyingly";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "gloomily"))
    {
        return "gloomily";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "murkily"))
    {
        return "murkily";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "repulsively"))
    {
        return "repulsively";
    }

    if ((strlen(str) > 2) && wildmatch(str + "*", "somberly"))
    {
        return "somberly";
    }

    return query_shadow_who()->full_adverb(str);
}



/* Setting up the adjectives of the player */

void
set_khiraa_adj1(string adj)
{
    adj1 = adj;
}

void
set_khiraa_adj2(string adj)
{
    adj2 = adj;
}
string
query_khiraa_adj1()
{
    return adj1;
}

string
query_khiraa_adj2()
{
    return adj2;
}

/* Get the alternative adjectives */

mixed
query_adj(int i)
{
    if(!adj1 && !adj2)
        return shadow_who->query_adj(i);
    if(i)
        return ({adj1,adj2});
    return adj1;
}

/* Initialize shadow and set the alternative adjectives, if there */
/* are any  */

string *
parse_command_adjectiv_id_list()
{
    string *str;
    str = shadow_who->parse_command_adjectiv_id_list();
    str += ({adj1,adj2,"undead"});
    return str;
}

public void
init_occ_shadow(string arg)
{
    if(stringp(arg))
       sscanf(arg,"%s,%s",adj1,adj2);
}


/* This will add a special shadow to the victim of the killer, */
/* that will make a corpse like normal, but also it will add */
/* a special prop to it that contains long description, for the */
/* spell 'raise dead'. This way, the zombie raised can also look */
/* like its former self */

void
find_corpse(string str1,string str2)
{
    int i;
    object *poss;
    poss = all_inventory(E(shadow_who));
    for(i=0;i<sizeof(poss);i++)
    {
        if(sizeof(poss[i]->query_prop(CORPSE_AS_KILLER)) &&
           poss[i]->query_prop(CORPSE_AS_KILLER)[0] ==
           shadow_who->query_real_name())
        {
           poss[i]->add_prop(DK_AS_CORPSE,({str1,str2}));
        }
    }
}
 
void
notify_you_killed_me(object ob)
{
    if(ob->query_npc())
        set_alarm(0.25,0.0,&find_corpse(ob->long(),ob->query_adj(1)));
}


public mixed 
query_guild_trainer_occ()
{
   return ({"/d/Kalad/common/guilds/khiraa/temple/rooms/temple_dk_train",
          "/d/Kalad/common/guilds/khiraa/temple/rooms/temple_lp_train"});
}


/* special effect for when we die */
void
do_die(object killer)
{
    if(shadow_who->query_hp() > 0)
        return;
    shadow_who->add_prop(LIVE_I_NO_CORPSE,1);
    tell_room(E(shadow_who),QCTNAME(shadow_who)+" explodes into "+
    "a blinding shower of white sparks!\n",shadow_who);
    tell_object(shadow_who,"You explode into a blinding shower of "+
    "white sparks!\n");

    // return to temple
    clone_object(KHIRAA+"temple/obj/death_flag2")->move(shadow_who);
    shadow_who->do_die(killer);
}

/* Load up the soul and add it to the player. Notify members of */
/* person's arrival, and load up the orders and circle levels */

public void
get_souls(object ob)
{
    int i;
    object *membs;

    seteuid(getuid());

    ob->add_cmdsoul(DK_SOUL);
    ob->update_hooks();

    membs = users();
    for(i=0;i<sizeof(membs);i++)
    {            
        if(IS_DK(membs[i]) || IS_LP(membs[i])) 
        {
            tell_object(membs[i],"Screams from the Netherworld "+
            "echo in your head, all chanting that "+ob->query_name()+
            " has risen from the grave.\n");
        }
    }

    clone_object(DK_DIR+"obj/dk_medallion")->move(ob);
    clone_object(DK_DIR+"obj/knight_scabbard")->move(ob);
    present("_dk_scab_",ob)->set_owner(ob->query_name());

    shadow_who->add_prop(LIVE_I_UNDEAD,"@@query_g_stat@@");
    shadow_who->add_prop(LIVE_I_NO_GENDER_DESC,1);
    shadow_who->add_prop(LIVE_I_NO_CORPSE,1);

    if(query_circle())
        clone_object(LP_DIR+"obj/master_key")->move(shadow_who);
    
    /* Check to see if we are right alignment, if not disgrace them */
    if(ob->query_alignment() > 900)
    {
        tell_object(ob,"You have done too many good deeds, and "+
        "not enough evil! You will be disgraced now!\n");
        set_guild_order(-1);
    }

    /* I like to be able to see in the dark ;-) */
    if(IS_GUILD_MASTER(shadow_who))
        shadow_who->add_prop(LIVE_I_SEE_DARK,100);
}

void
linkdeath_hook(int i)
{
    int j;
    object *membs = users();    
    for(j = 0; j < sizeof(membs);j++)
    {
        if(IS_DK(membs[j]) || IS_LP(membs[j]))
        {
            if(i == 1)
                tell_object(membs[j],shadow_who->query_name()+
                " travels to the Netherworld to meditate.\n");
             if(i == 0)
                tell_object(membs[j],shadow_who->query_name()+
                " has returned from the Netherworld.\n");
        }
    }
    shadow_who->linkdeath_hook(i);
}

void
remove_object()
{
    int i;
    object *obs = users();
    if(calling_function(-1) == "quit")
    {
        for(i = 0; i < sizeof(obs); i++)
         {
        if(IS_DK(obs[i]) || IS_LP(obs[i]))
            tell_object(obs[i],shadow_who->query_name()+" has returned "+
            "to "+HIS(shadow_who)+" coffin.\n");
        }
     }
    shadow_who->remove_object();
}


public int
query_guild_keep_player(object ob)
{
    set_alarm(2.0,0.0,&get_souls(ob)); /* set an alarm */
    return 1;
}

/* return the guild stat, for the LIVE_I_UNDEAD prop */
int
query_g_stat()
{
    return MIN(100,shadow_who->query_base_stat(SS_OCCUP));
}

public int
query_guild_tax_occ()
{
    return DK_OCC_TAX; 
}

/* Get the right title */
public string 
query_guild_title_occ()
{
    string str = "";
    if(query_guild_order() == -1)
        return DISGRACED_TITLE;
    if(shadow_who->query_gender() == 1)
        str = FTITLES[query_guild_order() - 1];
    else
        str = TITLES[query_guild_order() - 1];
    if(query_circle())
    {
        if(shadow_who->query_gender() == 1)
            str = FCIRCLE_TITLE;
        else
            str = CIRCLE_TITLE;
    }
    return str;
}

public string
query_guild_style_occ()
{
   return DK_OCC_STYLE;
}

public string
query_guild_name_occ()
{
   return DK_OCC_NAME;
}

public int
list()
{
   string str;  
   str = TP->list_major_guilds();
   if (str)
      write("You are member of following guilds.\n" + str);
   else
      write("You are not member of any guilds.\n");
   
   return 1;
}

/* Add something special for the titlel presentation */
public string
query_gender_string()
{
    return "undead";
}

/* Removed sunlight code */

public mixed
query_guild_skill_name(int type)
{
    if(type == SS_WHIRLWIND)
        return "whirlwind";
    if(type == SS_BASHSTUN)
        return "stunbash";
}
