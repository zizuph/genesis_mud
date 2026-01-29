
 /*  Elemental Worshippers of Calia Shadow    */
 /*  Coded by Jaacar & Maniac 1996    */


#pragma save_binary

inherit "/std/guild/guild_lay_sh";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include "defs.h"
#include WORSHIP_HEADER
#include COUNCIL_HEADER

#define MODIFIER 20

static int prot;
static string *titles; 

string query_guild_style_lay() { return GUILD_STYLE; }
string query_guild_name_lay() { return GUILD_NAME; }

int
is_worship()
{
    return 1;
}

int 
query_guild_tax_lay() 
{ 
    return 12; 
}


public void
do_die(object killer)
{
    object *members;
    string diety;
    diety = "Lord Pyros";

    if ((shadow_who->query_hp() > 0) || shadow_who->query_wiz_level() ||
        shadow_who->query_ghost())
    {
        return;
    }

    members = filter(users(), &->is_worship());
    if (!sizeof(members))
    {
        shadow_who->do_die(killer);
        return;
    }
    if (shadow_who->query_skill(SS_PATRON_ELEMENTAL) == FIRE_FLAG)
        diety = "Lord Pyros";
    if (shadow_who->query_skill(SS_PATRON_ELEMENTAL) == AIR_FLAG)
        diety = "Lady Aeria";
    if (shadow_who->query_skill(SS_PATRON_ELEMENTAL) == WATER_FLAG)
        diety = "Lord Diabrecho";
    if (shadow_who->query_skill(SS_PATRON_ELEMENTAL) == EARTH_FLAG)
        diety = "Lady Gu";
    map(members, &->catch_msg("The voice of "+diety+" echoes through "+
        "your mind announcing that "+capitalize(shadow_who->query_real_name())+
        " has just perished.\n"));
    shadow_who->do_die(killer);
}

void
council_check()
{
    object *members;
    string diety;
    diety = "Lord Pyros";

    seteuid(getuid());
    COUNCIL_CODE->carry_out_punishments(shadow_who);
    if ((shadow_who->query_skill(SS_CARVED) &AIR_FLAG) ||
        (shadow_who->query_skill(SS_CARVED) &WATER_FLAG) ||
        (shadow_who->query_skill(SS_CARVED) &FIRE_FLAG) ||
        (shadow_who->query_skill(SS_CARVED) &EARTH_FLAG))
    {
        shadow_who->catch_msg("Greetings, Dedicated Member of the Circle.\n");
    }
    members = filter(users(), &->is_worship());
    if (!sizeof(members))
        return;
    if (shadow_who->query_ghost())
        return;
    if (shadow_who->query_skill(SS_PATRON_ELEMENTAL) == FIRE_FLAG)
        diety = "Lord Pyros";
    if (shadow_who->query_skill(SS_PATRON_ELEMENTAL) == AIR_FLAG)
        diety = "Lady Aeria";
    if (shadow_who->query_skill(SS_PATRON_ELEMENTAL) == WATER_FLAG)
        diety = "Lord Diabrecho";
    if (shadow_who->query_skill(SS_PATRON_ELEMENTAL) == EARTH_FLAG)
        diety = "Lady Gu";
    map(members, &->catch_msg("The voice of "+diety+" echoes through your mind announcing "+
        "that "+capitalize(shadow_who->query_real_name())+" has entered "+
        "the realms.\n"));
}


void
init_worshipper_titles()
{
    int spe = shadow_who->query_skill(SS_PATRON_ELEMENTAL); 

    seteuid(getuid()); 
    if (COUNCIL_CODE->is_leader(shadow_who->query_real_name())) { 
        titles = LEADER_TITLES; 
        return;
    } 

    if (COUNCIL_CODE->is_council_member(shadow_who->query_real_name())) 
    {
        if (shadow_who->query_skill(SS_CARVED) != ALL_FLAGS)
            shadow_who->set_skill(SS_CARVED,ALL_FLAGS); 
        switch (spe) 
        { 
            case FIRE_FLAG : titles = COUNCIL_PYROS_TITLES;  
                             break;
            case EARTH_FLAG : titles = COUNCIL_GU_TITLES;  
                              break;
            case AIR_FLAG : titles = COUNCIL_AERIA_TITLES; 
                            break;
            case WATER_FLAG : titles = COUNCIL_DIABRECHO_TITLES;  
                              break;
            default : titles = COUNCIL_DEFAULT_TITLES;  
                      break;
        } 
        return;
    } 

    switch (spe) { 
       case FIRE_FLAG : titles = PYROS_TITLES;  
                        break;
       case EARTH_FLAG : titles = GU_TITLES;  
                         break;
       case AIR_FLAG : titles = AERIA_TITLES; 
                       break;
       case WATER_FLAG : titles = DIABRECHO_TITLES;  
                       break;
       default : titles = DEFAULT_TITLES;  
                 break;
    } 
}



void
init_lay_shadow(string str)
{
    ::init_lay_shadow();

    init_worshipper_titles(); 
    set_alarm(2.0, 0.0, council_check);
}


int
query_guild_keep_player(object ob)
{
    return 1;
}


int
query_calia_worshipper_level()
{
    return (shadow_who->query_stat(SS_LAYMAN) / 10); 
}


string
query_guild_title_lay()
{
    int title_level, s;
    string full_title;

    title_level = query_calia_worshipper_level();

    s = sizeof(titles); 

    if (title_level < 0) 
        title_level = 0;
    else if (title_level >= s) 
        title_level = (s - 1); 

    full_title = titles[title_level];
    if (shadow_who->query_skill(SS_CARVED) == ALL_FLAGS)
        full_title += ", Dedicated Worshipper of the Elements";

    return full_title;
}


string
query_guild_skill_name(int skill)
{
    if ((skill == SS_CARVED) ||
        (skill == SS_PUNISHMENT) ||
        (skill == SS_PATRON_ELEMENTAL))
       return ""; 
    return 0;
}


string
query_def_post()
{
    return (WOR_TEMPLE+"post");
}

        

string
*query_guild_trainer_lay()
{
    return ({WOR_TEMPLE+"board",WOR_TEMPLE+"medroom"});
}


public void
worship_stop_fight(object me, object target, string caller)
{
    int i;
    string pn;

    i = random(4);
    pn = PUNISHER[i]; 

    seteuid(getuid());
    me->stop_fight(target);
    target->stop_fight(me);
    if (file_name(me) == caller)
    {
        if (me->query_prop(BEEN_BAD_BOY))
        {
            tell_room(environment(me), pn +" suddenly "+
                "appears, looking very angry.\n");
            tell_object(me, pn+" points at you and screams "+
                "out in anger: You have been warned, but have not "+
                "listened!  Action must be taken!\nSuddenly, you feel "+
                "mentally and physically weakened.\n" + pn +
                " smiles wickedly, and disappears.\n");
            tell_room(environment(me),pn+" points at "+
                QTNAME(me) +" and screams out in anger:  You have " +
                "been warned, but have not "+
                "listened!  Action must be taken!\n"+
                pn +" smiles wickedly, and disappears.\n"+
                QTNAME(me)+" looks visibly drained.\n",me);
            me->set_mana(0);
            me->heal_hp(-(me->query_max_hp()/2));
                (WOR_OBJECTS+"council_log_book")->update_log_book(COUNCIL_CODE->my_time() +
                    capitalize(me->query_real_name())+" has been "+
                    "punished by "+ pn +" for attacking "+
                    capitalize(target->query_real_name())+".\n");
            if (me->query_hp() <= 0)
            {
                DEATH_OBJECT->load_me();
                me->do_die(find_object(DEATH_OBJECT));
            }
        }
        else 
        {
            tell_room(environment(me), pn + " suddenly "+
                "appears, looking slightly annoyed.\n");
            tell_object(me, pn + " whispers to you: Do not "+
                "attack another in our family again, or you shall "+
                "feel the wrath of the Elementals.  I hope I make "+
                "myself clear.\n");
            tell_room(environment(me), pn + " whispers to "+
                QTNAME(me)+".\n",me);
            tell_room(environment(me), pn + " disappears.\n");
            me->add_prop(BEEN_BAD_BOY,1);
        }
    }
    else
    {
        tell_room(environment(me), pn + " suddenly appears, "+
            "looking very angry.\n" + pn + " shouts: I don't "+
            "know which of you did it, but you had best behave!  "+
            "You aren't going to like it if I have to come back!\n"+
            pn + " disappears.\n");
    }
}


public void
attack_object(object target)
{
    if (target->is_worship())
    {
        int i;
        object temp;

        for (i = 0; i < 20; i++)
        {
            if (calling_object(-i))
                temp = calling_object(-i);
            else
                break;
        }
        set_alarm(1.0, 0.0,
              &worship_stop_fight(shadow_who, target, file_name(temp)));
    }
    shadow_who->attack_object(target);
}

/* -----CARVING ROUTINES------*/

/*
 * function name: carve_count
 * description  : Returns the number of times a player has
 *                carved based on the SS_CARVED skill, or the
 *                number he's eligible to carve, if the 
 *                'eligible' var is true.
 * arguments    : int eligible - optional arg. Set true if
 *                looking for the number of times the player
 *                can carve, rather than the number of times he
 *                has carved.
 * returns      : 0, 1, 2, 3, or 4. (number of elemental tools
 *                that have been carved).
 */
public varargs int
carve_count(int eligible=0)
{
  /* Get the player's SS_CARVED skill */
    int skill = shadow_who->query_skill(SS_CARVED);

  /* If 'eligible' var is set, return number of times  */
  /* the player is eligible to carve */
    if (eligible)
        return shadow_who->query_base_stat(SS_LAYMAN) / MODIFIER;

  /* Decipher how many of the possible four carving */
  /* bits are mapped into the SS_CARVED skill, and */
  /* return that value. */
    return ((skill & FIRE_FLAG) / FIRE_FLAG +
        (skill & EARTH_FLAG) / EARTH_FLAG +
        (skill & WATER_FLAG) / WATER_FLAG +
        (skill & AIR_FLAG) / AIR_FLAG);
}

int
query_guild_leader_lay()
{
    string pn;

    pn = shadow_who->query_real_name();
    seteuid(getuid());
    return (COUNCIL_CODE->is_council_member(pn));
}
