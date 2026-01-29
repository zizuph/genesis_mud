/*
    lp_shadow.c

    This is the shadow guild object for the Lich Priesthood

    Sarr Apr.15.97
    recoded by Fysix, Feb 1998
 */

#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_occ_sh";

#include <ss_types.h>
#include <wa_types.h>
#include "/d/Kalad/sys/ss_types.h"
#include "../../default.h"
#include "../../khiraa.h"

#define LP_MAX_LEVEL 26

// Guild titles
#define KHIRAA_TITLES ({ "Beginning Disciple of the Khiraa", \
                         "Novice Disciple of the Khiraa", \
                         "Secure Disciple of the Khiraa", \
                         "Fortified Disciple of the Khiraa", \
                         "Learned Disciple of the Khiraa", \
                         "Minor Servant of the Khiraa", \
                         "Proud Servant of the Khiraa", \
                         "Trusted Servant of the Khiraa", \
                         "Wise Servant of the Khiraa", \
                         "Unholy Servant of the Khiraa", \
                         "Apprentice Necromancer of the Khiraa", \
                         "Necromancer of the Khiraa", \
                         "Greater Necromancer of the Khiraa", \
                         "High Necromancer of the Khiraa", \
                         "Battle Necromancer of the Khiraa", \
                         "Death Priest of the Khiraa", \
                         "High Death Priest of the Khiraa", \
                         "Greater Lich of the Khiraa", \
                         "Master Lich of the Khiraa", \
                         "Nightmare Lich of the Khiraa", \
                         "Gholash Warlock of the Khiraa", \
                         "High Gholash Warlock of the Khiraa", \
                         "Spirit Master of the Khiraa", \
                         "Grave Master of the Khiraa", \
                         "Soul Taker of the Khiraa", \
                         "Chosen One of the Nameless Horror" })

#define FKHIRAA_TITLES ({  "Beginning Disciple of the Khiraa", \
                          "Novice Disciple of the Khiraa", \
                          "Secure Disciple of the Khiraa", \
                          "Fortified Disciple of the Khiraa", \
                          "Learned Disciple of the Khiraa", \
                          "Minor Servant of the Khiraa", \
                          "Proud Servant of the Khiraa", \
                          "Trusted Servant of the Khiraa", \
                          "Wise Servant of the Khiraa", \
                          "Unholy Servant of the Khiraa", \
                          "Apprentice Necromancer of the Khiraa", \
                          "Necromancer of the Khiraa", \
                          "Greater Necromancer of the Khiraa", \
                          "High Necromancer of the Khiraa", \
                          "Battle Necromancer of the Khiraa", \
                          "Death Priestess of the Khiraa", \
                          "High Death Priestess of the Khiraa", \
                          "Greater Lich of the Khiraa", \
                          "Mistress Lich of the Khiraa", \
                          "Nightmare Lich of the Khiraa", \
                          "Gholash Witch of the Khiraa", \
                          "High Gholash Witch of the Khiraa", \
                          "Spirit Mistress of the Khiraa", \
                          "Grave Mistress of the Khiraa", \
                          "Soul Taker of the Khiraa", \
                          "Chosen One of the Nameless Horror" })

#define CIRCLE_TITLE            "Unholy Apostle of the Khiraa"
#define CIRCLE_MASTER_TITLE     "Unholy Prophet of the Khiraa"
#define DISGRACED_TITLE         "Disgraced Servant of the Khiraa"

/* strings containing the alternative adjectives */
string adj1, adj2;

int
join_khiraa(object ob, string adjs, object inish)
{
    int res;
    object lay;

    setuid();
    seteuid(getuid());

    lay = clone_object(LP_LAY_SHADOW);
    res = lay->shadow_me(ob,LP_LAY_TYPE,LP_LAY_STYLE,LP_LAY_NAME);

    if(res != 1)
        return res;
    if(stringp(adjs))
        res = shadow_me(ob,LP_OCC_TYPE,LP_OCC_STYLE,LP_OCC_NAME,adjs);
    else
        res = shadow_me(ob,LP_OCC_TYPE,LP_OCC_STYLE,LP_OCC_NAME);

    KHIRAA_SERVER->add_member(shadow_who->query_real_name());

    write_file(JOIN_LOG,GTIME+": "+ob->query_real_name()+" entered "+
    "the Khiraa Priesthood through the hand of "+inish->query_real_name()+"\n");

    ob->clear_guild_stat(SS_OCCUP);
    ob->clear_guild_stat(SS_LAYMAN);

    return res;
}

/* Returns if they are a circle member or master, or not */
int
query_circle()
{
    return KHIRAA_SERVER->query_circle_member(shadow_who->query_real_name());
}

/* This is called in the player to add them to the council(circle) */
/* With 1 being a normal member, and 2 being the master            */
void
add_circle_member(int i)
{
    KHIRAA_SERVER->add_circle_member(shadow_who->query_real_name(), i);
}

/* Set this player guild order, and save it to a file. Arg i is */
/* is passed as the level...must be from 1 - 5 */
void
set_guild_order(int i)
{
    if(i <= 0 || i > LP_MAX_LEVEL)
        return; // no go
    KHIRAA_SERVER->set_guild_order(shadow_who->query_real_name(), i);
}

/* return the current order. This is not the 'true' order, as the */
/* the true one is a combo of guild stat and council sanctioned */
/* order, and can be found in 'query_lp_order' */
int
query_guild_order()
{
    return KHIRAA_SERVER->query_guild_order(shadow_who->query_real_name());
}

/* This is called to add a new special Lich title name. It will */
/* Update the master list and save it to a file                 */
void
set_lich_name(string str)
{
    KHIRAA_SERVER->set_lich_name(shadow_who->query_real_name(), str);
}

/* Returns the special lich title name */
string
query_lich_name()
{
    return KHIRAA_SERVER->query_lich_name(shadow_who->query_real_name());
}

/* extra adverbs for this guild */
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

/* This will set the new special adjective */

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

/* Returns the special adjectives */

mixed
query_adj(int i)
{
    if(!adj1 && !adj2)
        return shadow_who->query_adj(i);
    if(i)
        return ({adj1,adj2});
    return adj1;
}

string *
parse_command_adjectiv_id_list()
{
    string *str;

    str = shadow_who->parse_command_adjectiv_id_list();
    str += ({adj1, adj2, "undead"});
    return str;
}


/* Initialize the shadow, read our lich name
   and add any special adjectives */
public void
init_occ_shadow(string arg)
{
    if(stringp(arg))
        sscanf(arg, "%s,%s", adj1, adj2);
}

/* Our post office */
string
query_def_post()
{
    return KHIRAA + "temple/rooms/po";
}

/* This will add a special shadow to the living that this player  */
/* kills. THe shadow makes a normal corpse, but adds a special    */
/* property to it that will contain the living's desc, and add it */
/* to the corpse. This way, when the spell 'raise dead' is used,  */
/* the zombie raised can have the old living's former long description */
/* in it.                                                         */
void
find_corpse(string str1, string str2)
{
    int i;
    object *poss;

    poss = all_inventory(ENV(shadow_who));
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


/* Special effect for the death of a lich */
void
do_die(object killer)
{
    if(shadow_who->query_hp() > 0)
        return; // so we won't go packing when called in a bogus routine

    shadow_who->add_prop(LIVE_I_NO_CORPSE,1);

    tell_room(ENV(shadow_who),QCTNAME(shadow_who)+" explodes into "+
    "a blinding shower of white sparks!\n",shadow_who);
    tell_object(shadow_who,"You explode into a blinding shower of "+
    "white sparks!\n");

    clone_object(KHIRAA + "temple/obj/death_flag2")->move(shadow_who);
    shadow_who->do_die(killer);
}

public mixed
query_guild_trainer_occ()
{
   return ({KHIRAA + "temple/rooms/temple_dk_train",
            KHIRAA + "temple/rooms/temple_lp_train"});
}

/* This will add the command soul, send a message to guild members */
/* on notifying them of the player's log in, and add the props     */
/* to them and load up all the title, council and order data       */
public void
get_souls(object ob)
{
    int i;
    object *membs;

    seteuid(getuid());

    ob->add_cmdsoul(LP_SOUL);
    ob->update_hooks();

    membs = users();
    for(i=0;i<sizeof(membs);i++)
    {
        if(IS_DK(membs[i]) || IS_LP(membs[i]))
        {
            tell_object(membs[i],"Screams from the Netherworld "+
            "echo in your head, all chanting that the "+query_lich_name()+
            " has risen from the grave.\n");
        }
    }

    clone_object(LP_DIR + "obj/lp_med")->move(ob);

    if(ob->query_alignment() > 900)
    {
        tell_object(ob,"You have done too many good deads, and "+
        "not enough evil! You will be disgraced now!\n");
        KHIRAA_SERVER->set_guild_order(shadow_who->query_real_name(), -1);
    }

    if(query_circle())
        clone_object(LP_DIR + "obj/master_key")->move(ob);

    shadow_who->add_prop(LIVE_I_UNDEAD,"@@query_g_stat@@");
    shadow_who->add_prop(LIVE_I_NO_GENDER_DESC,1);

/* I like to be able to see in the dark ;-) */
    if(shadow_who->query_wiz_level())
    {
        shadow_who->add_prop(LIVE_I_SEE_DARK,100);
        if(shadow_who->query_real_name() == "sarr")
            clone_object(DK_DIR + "obj/dk_medallion")->move(ob);
	}
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
                tell_object(membs[j],"The "+query_lich_name()+
                " travels to the Netherworld to meditate.\n");
             if(i == 0)
                tell_object(membs[j],"The "+query_lich_name()+
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
            tell_object(obs[i],"The "+query_lich_name()+" has returned "+
            "to "+HIS(shadow_who)+" coffin.\n");
        }
     }
    shadow_who->remove_object();
}

public int
query_guild_keep_player(object ob)
{
    set_alarm(2.0, 0.0, &get_souls(ob)); /* set an alarm, or else bad things
                                          will happen for some reason */
    return 1;
}

/* returns guild stat for LIVE_I_UNDEAD prop */
int
query_g_stat()
{
    return MIN(100,shadow_who->query_base_stat(SS_OCCUP));
}

public int
query_guild_tax_occ()
{
    return LP_OCC_TAX; /* TAX THEM ALL THE SAME */
}


/* Get the proper title */
public string
query_guild_title_occ()
{
    string  str, lich_name;
    int     guild_order, circle;

    lich_name = query_lich_name();

    if (lich_name && !stringp(shadow_who->query_guild_title_race()))
        str = lich_name + ", ";
    else
        str = "";

    circle = query_circle();
    if (circle == 2)
    {
        str += CIRCLE_MASTER_TITLE;
        return str;
    }
    if (circle == 1)
    {
        str += CIRCLE_TITLE;
        return str;
    }
    guild_order = query_guild_order();

    if(guild_order < -1 || guild_order > LP_MAX_LEVEL)
        return "the Bugged";

    if(query_guild_order() == -1)
        return str + DISGRACED_TITLE;

    if(shadow_who->query_gender() == 1)
        str += FKHIRAA_TITLES[guild_order - 1];
    else
        str += KHIRAA_TITLES[guild_order - 1];
    return str;
}

public string
query_guild_style_occ()
{
   return LP_OCC_STYLE;
}

public string
query_guild_name_occ()
{
   return LP_OCC_NAME;
}

/* Not sure if we need this...hmmm */
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

/* add something neat to the presentation title of the player */
public string
query_gender_string()
{
    return "undead";
}

/* special skills description */
public mixed
query_guild_skill_name(int type)
{
    if(type == SS_GOUGE)
        return "gouge";
}
