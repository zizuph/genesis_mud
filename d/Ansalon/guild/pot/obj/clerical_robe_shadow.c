/* Stralle @ Genesis 020616
 */

#pragma strict_types

inherit "/std/shadow";

#include <composite.h>
#include <login.h>
#include <stdproperties.h>
#include "../guild.h"

#define ADJS ({ "velvet-robed", "hooded" })
#define HIDE ({ "eyes", "face", "hair", "mouth", "nose", "beard" })
#define M_UNHOODED  0
#define M_HOODED    1

#undef REVEALABLE
#define SKILL_DECREASE
#undef INTRO_REQ

int gHooded;
mapping gAttribmap = ([]), gAdjs = ([]);

/* Function name: create
 * Description:   The creator. Some of the below code is shamlessly
 *                stolen from the attribute session in the character
 *                creation process
 */
void
setup_pot_hood_shadow()
{
    mixed *categories;
    string *adjs;
    int i, x, tmp;
    
    categories = get_dir(PATH + "attributes/");
    find_player("stralle")->catch_tell("PATH: " + PATH + "\n");

    for (i = 0 ; i < sizeof(categories) ; i++)
    {
        if (member_array(categories[i], HIDE) < 0)
            continue;
            
        gAttribmap[categories[i]] = explode(read_file(PATH + "attributes/" +
            categories[i]), "\n");
    }

//    gAdjs[M_HOODED] = ADJS;
    gAdjs[M_UNHOODED] = gAdjs[M_HOODED] = ({ ADJS[0],
        query_shadow_who()->query_adjs()[0],
        query_shadow_who()->query_adjs()[1] });
    gAdjs[M_UNHOODED] = exclude_array(gAdjs[M_UNHOODED], 1, 1);
    
    for (i = 0, adjs = query_shadow_who()->query_adjs() ; i < 2 ; i++)
    {
        for (x = 0 ; x < sizeof(categories) ; x++)
        {
            if (member_array(adjs[i], gAttribmap[categories[x]]) >= 0)
            {
                tmp = member_array(adjs[i], gAdjs[M_HOODED]);
                
                gAdjs[M_HOODED] = exclude_array(gAdjs[M_HOODED], tmp, tmp);
            }
        }
    }

    if (sizeof(gAdjs[M_HOODED]) > 2)
        gAdjs[M_HOODED] = exclude_array(gAdjs[M_HOODED], 1, 1);
    else if (sizeof(gAdjs[M_HOODED]) == 1)
        gAdjs[M_HOODED] += ({ ADJS[1] });
}
    
void
set_pot_hooded()
{
    gHooded = 1;
}

void
unset_pot_hooded()
{
    gHooded = 0;
}

int
query_pot_hooded()
{
    return gHooded;
}

#ifdef INTRO_REQ
public int
query_met(mixed name)
{
    string str;
    mapping rem, smap;

    if (!query_pot_hooded())
        return query_shadow_who()->query_met(name);
    
    if (objectp(name))
        str = (string) name->query_real_name();
    else if (stringp(name))
    {
        str = name;
        name = find_living(name);
    }
    else
        return 0;
    
    if (name && name->query_prop(LIVE_I_NEVERKNOWN))
        return 0;
    
    find_player("stralle")->catch_tell("[] LIVE_I_ALWAYSKNOWN\n");
    if (name && name->query_prop(LIVE_I_ALWAYSKNOWN))
        return 1;
    
#ifdef 0
    if (query_shadow_who()->query_wiz_level())
        if (wiz_unmet == 0 || (wiz_unmet == 2 && name && !(name->query_npc())))
            return 1;
        else
            return 0;
#endif
 
    /* I always know myself */
    find_player("stralle")->catch_tell("[] 128\n");
    if (str == query_shadow_who()->query_real_name())
        return 1;

    /* If I have been introduced to person */
    find_player("stralle")->catch_tell("[] 133\n");
    if ((query_shadow_who()->query_introduced())[str])
        return 1;

    rem = query_shadow_who()->query_remember_name();

    /* If person is a member of my guild and I remember him
     */    
    find_player("stralle")->catch_tell("[] 141\n");
    if (query_shadow_who()->query_guild_name_occ() == GUILD_NAME &&
        (mappingp(rem) && rem[str]))
        return 1;

    find_player("stralle")->catch_tell("[] 146\n");
    return 0;
}
#endif

#ifdef SKILL_DECREASE
public int
query_skill(int snum)
{
    /* If we are not hooded, return the original */
    if (!query_pot_hooded())
        return query_shadow_who()->query_skill(snum);
        
    /* Hide to show the original when the command skills is issued */
    if (snum == SS_AWARENESS &&
        (calling_program() == "cmd/live/state.c" ||
        query_verb() == "skills"))
        return query_shadow_who()->query_skill(snum);


    switch (snum)
    {
        case SS_AWARENESS:
            return (query_shadow_who()->query_skill(SS_AWARENESS) * 80) / 100;
        default:
            return query_shadow_who()->query_skill(snum);
    }
}                
#endif

#ifdef REVEALABLE
public varargs int
shadow_me(mixed to_shadow)
{
    int result = ::shadow_me(to_shadow);
    
    if (result)
    {
        query_shadow_who()->add_cmd_item(({"the face", "face"}), "reveal",
            "@@do_reveal");
        query_shadow_who()->update_actions();
    }
}

public void
remove_shadow()
{
    query_shadow_who()->remove_cmd_item("face");
    query_shadow_who()->update_actions();
    
    ::remove_shadow();
}

public int
reveal_access(object ob)
{
    return !(!living(ob) || (ob == TP));
}

public mixed
do_reveal()
{
    object *objs, pl;
    string rest = query_shadow_who()->query_item_rest_command();
    string who;
    float skill_tp;
    
    if (sscanf(rest, "of %s", who) != 1)
        return "Reveal the face of whom?\n";
    
    objs = CMDPARSE_ONE_ITEM(who, "reveal_access", "reveal_access");
    
    if (sizeof(objs) > 1)
        return "You would need to be an octopussy in order to reveal " +
            "the faces of many people at once.\n";

    if (!pointerp(objs) || !sizeof(objs))
        return "You cannot find any such person here.\n";
    
    pl = objs[0];
    
    if (!pl->query_pot_hooded())
        return "But " + pl->query_The_name(TP) + " is not hooded.\n";
    
    if ((pl->query_prop(CONT_I_HEIGHT) -
        TP->query_prop(CONT_I_HEIGHT)) >= 50)
        return "You are too short to do that.\n";
    
    skill_tp = (1.0 - (itof(TP->query_intoxicated()) /
        itof(TP->intoxicated_max()))) *
        itof(TP->query_skill(SS_DEX));
    
    TP->reveal_me(1);
    
    if (TP->resolve_task(TASK_ROUTINE, ({ ftoi(skill_tp) }), pl,
        ({ SS_AWARENESS })) <= 0)
    {
        TP->catch_msg(QCTNAME(pl) + " dudges away as you try to " +
            "remove " + HIS(pl) + " hood.\n");
        pl->catch_msg(QCTNAME(TP) + " tries to remove your hood, " +
            "but you manage to dudge away in time.\n");
        tell_room(E(TP), QCTNAME(TP) + " tries to remove " +
            LANG_POSS(QTNAME(pl)) + " hood, but " + HE(pl) +
            " dodges away.\n", ({ pl, TP }));
        
        return 1;
    }
    
    TP->catch_msg("You manage to remove the hood from " +
        LANG_POSS(QTNAME(pl)) + " face.\n");
    pl->catch_msg(QCTNAME(TP) + " successfully removes your hood, " +
        "revealing your face.\n");
    tell_room(environment(TP), QCTNAME(TP) + " successfully removes " +
        "the hood from " + LANG_POSS(QTNAME(pl)) + " face.\n", ({ pl, TP }));
    
    unset_pot_hooded();
    return 1;
}
#endif

void
destroy_pot_hood_shadow()
{
    remove_shadow();
}

/* Function name: query_list
 * Description:   Makes life easier in the beneath functions, to query
 *                the description of shadow_who in various ways.
 * Arguments:     string *list - The adjectives
 *                int arg      - If true return both adjectives, else
 *                               the first in the list.
 */
private mixed
query_list(string *list, int arg)
{
    if (!arg && sizeof(list))
        return list[0];
    else
        return list + ({ });
}

/* Masked functions
 */
varargs public mixed
query_adj(int arg)
{
    return query_list(gAdjs[query_pot_hooded()], arg);
}

public string *
query_adjs()
{
    return query_list(gAdjs[query_pot_hooded()], 1);
}

public int
adjective_id(string str)
{
    return (member_array(str, gAdjs[query_pot_hooded()]) >= 0);
}

public string *
parse_command_adjectiv_id_list()
{
    return gAdjs[query_pot_hooded()];
}
