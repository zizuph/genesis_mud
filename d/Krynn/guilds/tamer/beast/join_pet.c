#pragma save_binary

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>

#include "../defs.h"

public int do_tame(string str);

string  genus,
        tamer,
        vorare,
        biome;
object  taming;

/* Function name: set_tamer
 * Description:   Sets the name of the tamer to whom the mount belongs.
 */
public void
set_tamer(string str)
{
    tamer = str;
}

/* Function name: query_tamer
 * Description:   Returns the name of the tamer to whom the mount belongs.
 */
public string
query_tamer()
{
    return tamer;
}

/* Function name: set_genus
 * Description:   Sets the genus name of the mount.
 */
public void
set_genus(string str)
{
    genus = str;
}

/* Function name: query_genus
 * Description:   Returns the genus name of the mount.
 */
public string
query_genus()
{
    return genus;
}

/* Function name: set_biome
 * Description:   Sets the ecological origin of the
 *                mount, this is done upon cloning of
 *                a mount which can be tamed.
 */
public void
set_biome(string str)
{
    biome = str;
}

/* Function name: query_biome
 * Description:   Returns the ecological origin of the
 *                mount, this is done upon cloning of
 *                a mount which can be tamed.
 */
public string
query_biome()
{
    return biome;
}

public void
update_description(string new_genus)
{
    int    *list, s;
    mapping hitlocs;
    
    set_genus(new_genus);
    
    set_race_name(GENUS->query_cub(query_genus()));
    set_short(implode(query_adjs(), " ") + " " + query_race_name());
    set_long("This " + GENUS->query_cub(query_genus()) + " belongs to the " +
        GENUS->query_family(query_genus()) + " family, however as it is " +
        "quite a young specimen, it is difficult to verify any markers " +
        "identifying its gender or genus. Due to its young age, " +
        "it might be possible to 'tame' it.\n");
    
    hitlocs = GENUS->query_hitlocs(genus);
    list    = m_indexes(hitlocs);

    for (s = 0; s < sizeof(list); s++)
    {
        set_hitloc_unarmed(s, (10 * hitlocs[list[s]][0]) / 100,
                                    hitlocs[list[s]][1], list[s]);
    }
}

void
create_creature()
{
    set_name("pet");
    set_adj("young");
    set_gender(2);
    
    set_biome("ArcticTundra");
    update_description("ursidae");
    
    set_stats(({10, 10, 10, 10, 10, 10}));
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
}

int
special_attack(object enemy)
{
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(do_tame,         "tame");
}

public void
start_taming(object player)
{
    object ob;
    
    if (player->query_prop(CREATION_OBJECT))
        ob->remove_object();

    set_tamer(player->query_real_name());
    
    ob = clone_object(PET_MENU);
    player->add_prop(CREATION_OBJECT, ob);
    ob->start(this_object());
    
    return;
}

public int
input_tame(string str)
{
    object  sh;
    mixed   why;

    str = lower_case(str);
    
    if (IN_ARRAY(str, ({ "n", "no" }) ))
    {
        this_player()->catch_msg("The " + this_object()->query_short() +
        " looks at you curiously before running off into the distance.\n");
        tell_room(environment(this_object()), QCTNAME(this_object()) +
        " runs off into the distance.\n", this_player());
        remove_object();
        return 1;
    } else if (IN_ARRAY(str, ({ "y", "yes" }) ))
    {
        this_player()->catch_msg("You crouch down and extend your hand " +
        "in a gesture to allow " + QTNAME(this_object()) + " to catch " +
        "your scent.\n");
        tell_room(environment(this_object()), QCTNAME(this_player()) +
        " crouches down and reaches out towards " + QTNAME(this_object()) +
        ", in a gesture to allow it to catch " + this_player()->query_possessive() +
        " scent.\n", this_player());
        taming = this_player();
    } else
    {
        this_player()->catch_msg("You have entered an invalid " +
        "option, please enter [y]es to proceed or [n]o to stop.\n");
        input_to(input_tame, 1);
        return 1;
    }
    
    /*  Allow the player to change pets  */
    if (this_player()->query_guild_member(GUILD_NAME))
    {
        start_taming(this_player());
        return 1;
    }
    
    if (this_player()->query_skill(SS_ANI_HANDL) < 30)
    {
        this_player()->catch_msg("You attempt to tame the " + short() + ", but "
        + "your lack of skill in handling animals becomes apparent as your "
        + "sudden movements spook it.\nThe " + short() + " runs off into the "
        + "distance.\n");
        this_object()->remove_object();
        return 1;
    }
    
    sh = clone_object(GUILD_SHADOW);
    
    /* Try to add the shadow to the player */
    switch (sh->add_lay_shadow(this_player()))
    {
        case 1:
        /* Successfully joined the guild, time for taming */
        
        start_taming(this_player());
        
        if (!this_player()->query_prop(CREATION_OBJECT))
             this_player()->remove_lay_member();
        
        return 1;

        case -4:
        /* The player has a lay guild already, or one of his existing
         * guilds has blocked this one.
         */ 
        write("You are already occupied enough with your current " +
        "layman, you would be unable to find the time to raise a pet.\n");
            break;

        default:
        /* Some error in shadowing */
        write("An error has prevented you from joining.\n");
            break;
    }
    
    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
do_tame(string str)
{
    string  desc;
    object *pets;
    
    if (strlen(query_tamer()) > 0)
        return 0;

    if (!str)
    {
        notify_fail("Tame what? the " + short() + "?\n");
        return 0;
    }
    
    if (parse_command(str, ({ }), "[the] / [a] [young] %s", desc))
    {
        if (!IN_ARRAY(desc, ({query_race_name()}) + query_adjs()))
        {
            this_player()->catch_msg("Tame what?\n");
            return 1;
        }
    }
    
    if (stringp(tamer) && present(tamer, environment(this_object())))
    {
        notify_fail("The " + query_short() + " is paying no attention " +
        "to you.\n");
        return 0;
    }
    
    if (this_player()->query_guild_member(GUILD_NAME))
    {
        pets = filter(all_inventory(environment(this_player())),
               &operator(==)(,this_player()->query_real_name()) @
               &->query_tamer());
        
        if (sizeof(pets))
        {
            pets[0]->tell_watcher(QCTNAME(pets[0]) + " lashes out at " +
            QTNAME(this_object()) + " in rivalry.\n", this_object(),
            ({ pets[0], this_object() }));
            pets[0]->attack_object(this_object());
            return 1;
        }
        
        if (!MANAGER->query_pet_name(this_player()))
        {
            input_tame("yes");
            return 1;
        }
        this_player()->catch_msg("If you proceed with taming " +
        "this pet, your current pet will reject you and leave. " +
        "You will need to raise this pet from a pup, just as " + 
        "you have done with your previous pet.\nTo proceed " +
        "enter [y]es, to stop enter [n]o.\n");
        MANAGER->add_achievement(this_player(), TAME_NEW_PET);
        input_to(input_tame, 1);
        return 1;
    }
    
    this_player()->catch_msg("You have initiated the joining "+
    "process for a laymans guild.\nTo proceed enter [y]es, to "+
    "stop enter [n]o. ");
    input_to(input_tame, 1);
    return 1;
}