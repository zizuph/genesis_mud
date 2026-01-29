/*
 * pTeleport
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h> 
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>

mapping gLocs = ([]);
static int gListIsActive;

#define PP_DEBUG(x)	find_player("stralle")->catch_tell("#pot_teleport# " + (x) + "\n")
 
/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 13;
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, mixed *targets, int *resist, int result)
{
    int x, size;
    mapping locs;
    string *a_locs;
    object tp, abyss;

    PP_DEBUG("resolving");

    if (result <= 0 || (objectp(targets[0]) &&
        targets[0]->query_prop(ROOM_I_IS) &&
        environment(caster) != targets[0]))
    {
        caster->catch_tell("Your spell fizzles.\n");
        return;
    }
    tp = this_player();
    set_this_player(find_player("stralle"));
    dump_array(targets);
    set_this_player(tp);


    if (objectp(targets[0]) && targets[0] == caster)
    {
        PP_DEBUG("resolving list");

//        set_spell_ingredients(0);

        if (!m_sizeof(GUILD_ADMIN->query_planeswalk_locations(caster->query_real_name())))
            caster->catch_tell("You cannot recall having previously set " +
                "any locations.\n");
        else
        {
            caster->catch_tell("You remember having previously set the " +
                "following locations:\n");
            for (x = 0, locs = GUILD_ADMIN->query_planeswalk_locations(caster->query_real_name()),
                 size = m_sizeof(locs), a_locs = m_indices(locs) ; x < size ; x++)
            {
                caster->catch_tell(sprintf("  %15s - %s\n",
                    capitalize(a_locs[x]), locs[a_locs[x]][1]));
            }
            x = GUILD_ADMIN->query_planeswalk_slots(caster->query_real_name());
            caster->catch_tell("You believe you can" + (!(x - size) ?
                "not keep any" : " keep " + LANG_WNUM(x - size)) +
                " more location" + ((x - size) > 1 ? "s" : "") + " in " +
                "memory.\n");
        }

        tp = this_player();
        set_this_player(caster);
        all_msgbb(QCTNAME(caster) + "'s eyes turns white as " + HE(caster) +
            " looks inward for a while.\n", caster, 0);
        set_this_player(tp);
    }
    else if (stringp(targets[0]) && file_size(targets[0] + ".c") >= 0)
#ifdef 0
        GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
        targets[0]))
#endif
    {
        PP_DEBUG("resolving move");
//        set_spell_ingredients(({"elidross", "amanita"}));


        /* Delay the teleport by moving to a temporary room, walking in
         * the abyss mindlessly..
         */
        caster->catch_tell("You trace a doorway before you, mumble a " +
            "prayer and step through the imaginary doorway. Suddenly " +
            "you find yourself in a strange place.\n");
        tell_room(environment(caster), QCTNAME(caster) + " traces a " +
            "shape before " + HIM(caster) + " resembling a doorway, " +
            "mumbles a prayer and steps through the imaginary doorway.\n",
            caster);

        setuid();
        seteuid(getuid());
        abyss = clone_object("/d/Ansalon/guild/pot/spells/obj/abyss");
        abyss->set_planeswalk_loc(caster->query_real_name(), targets[0]);
#ifdef 0
            GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
                targets[0]));
#endif
        caster->move_living("X", abyss, 1, 0);
    }
    else if (stringp(targets[0]) &&
        GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
        lower_case(targets[0])))
    {
        PP_DEBUG("resolving remove");
        caster->catch_tell("You mumble a prayer and decide to uncommit " +
            "the place you knew as " + targets[0] + " from memory.\n");
        GUILD_ADMIN->remove_planeswalk_loc(caster->query_real_name(),
            targets[0]);
    }        
    else
    {
        PP_DEBUG("resolving set");

//        set_spell_ingredients(({"elidross", "amanita"}));

        caster->catch_tell("You trace an X-like figure on the " +
            (targets[0]->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
            ", mumble a prayer and commit this place to memory " +
            "as " + capitalize(gLocs[caster->query_real_name()]) + ".\n");
        tp = this_player();
        set_this_player(caster);
        all_msgbb(QCTNAME(caster) + " traces an X-like figure on the " +
            (targets[0]->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
            " and mumbles a prayer.\n", caster, 0);
        set_this_player(tp);

        GUILD_ADMIN->set_planeswalk_loc(caster->query_real_name(),
            file_name(targets[0]), gLocs[caster->query_real_name()]);
    }
}

/*
 * cast pplaneswalk to 'location'
 * cast pplaneswalk set 'location'
 * cast pplaneswalk list [locations]
 * cast pplaneswalk remove 'location' // To be implemented
 */
public mixed *
pplaneswalk_target(object caster, string str)
{
    string fail, arg, room;
    object env = environment(caster);

    if (!stringp(str))
    {
        caster->catch_tell("Target the spell on what mark?\n");
        return ({ });
    }
    PP_DEBUG("str: \"" + str + "\"");
    gListIsActive = 0;

    /* if setting, check this
     */
    if (parse_command(str, environment(caster), "[to] 'set' %s", arg))
    {
        PP_DEBUG("cast to set");

//        set_spell_ingredients(({"elidross", "amanita"}));

        if (stringp(env->query_prop(ROOM_M_NO_TELEPORT)))
            fail = env->query_prop(ROOM_M_NO_TELEPORT);
        else if (stringp(env->query_prop(ROOM_M_NO_TELEPORT_TO)))
            fail = env->query_prop(ROOM_M_NO_TELEPORT_TO);
        else if (env->query_prop(ROOM_M_NO_TELEPORT) ||
            env->query_prop(ROOM_M_NO_TELEPORT_TO))
            fail = "There is no way to open a portal to another plane " +
                "from here.\n";
        
#ifdef 0
        if (strlen(fail) || (env->query_domain() != "Ansalon" &&
            env->query_domain() != "Krynn"))
        {
            if (!strlen(fail))
                fail = "The fabric of space seems different here, you " +
                    "don't think you are able to open a portal to " +
                    "another plane from here.\n";

            write(fail);
            return ({ });
        }
#endif
        
        if (GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
            lower_case(arg)))
        {
            write("You already have that location memorised.\n");
            return ({ });
        }

        if (m_sizeof(GUILD_ADMIN->query_planeswalk_locations(caster->query_real_name())) >=
            GUILD_ADMIN->query_planeswalk_slots(caster->query_real_name()))
        {
            write("You cannot remember any more locations.\n");
            return ({ });
        }
        
        if (!file_size(file_name(env) + ".c"))
        {
            fail = "The fabric of space seems different here, you " +
                "don't think you are able to open a portal to " +
                "another plane from here.\n";
            write(fail);
        }    

        if (strlen(arg) > 15 || sizeof(explode(arg, " ")) > 1)
        {
            write("Please refrain from any longer names and use single " +
                "words.\n");
            return ({ });
        }

        gLocs[caster->query_real_name()] = lower_case(arg);

        return ({ env });
    }
    else if (parse_command(str, environment(caster), "[to] 'remove' %s", arg))
    {
        PP_DEBUG("cast to remove");
        
        gListIsActive = 1;
        
        if (!GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
            lower_case(arg)))
        {
            write("You cannot recall having previously named such a location.\n");
            return ({ });
        }
        
        return ({ arg });
    }
    else if (parse_command(str, env, "'list'"))
    {
        PP_DEBUG("cast to list");

        gListIsActive = 1;
//        set_spell_ingredients(0);

        return ({ caster });
    } 
    else if (parse_command(str, env, "[to] %s", arg))
    {
        PP_DEBUG("cast to move");

//        set_spell_ingredients(({"elidross", "amanita"}));

        room = GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
            lower_case(arg));
        if (room && !catch(room->teleledningsanka()))
        {
            return ({ room });
        }
        else if (!room)
        {
            write("You don't remember having named a location that.\n");
            return ({ });
        }
        else
        {
            write("You sense that location have ceased to exist.\n");
            return ({ });
        }
    }

    write("You need a valid target.\n");
    return ({ });
}

/* Function name: pplaneswalk_ingr
 * Description:   This is apparently the only way to have one outcome of
 *                the spell to not sacrifice ingredients while another
 *                do cost ingredients. If I knew this beforehand I wouldn't
 *                have to do trial and error for an hour.. *sigh*
 *                This approach has a bug though. If two cast the spell
 *                simultaniously there will be a race for setting the
 *                state of gListIsActive and someone will either be surprised
 *                to have her ingredients sacrificed anyway or the other
 *                will gladly note no ingredients were lost.. Oh well.
 *                A rainy day there will be a similar solution as with ptell
 */
object *
pplaneswalk_ingr(object caster)
{
   object *list, *herbs, *ingr = allocate(2);
   object tp;

   PP_DEBUG("Inside pplaneswalk_ingr");

   if (gListIsActive)
      return ({ });

   PP_DEBUG("Using ingredients");
#ifdef 0
   tp = this_player();
   set_this_player(find_player("stralle"));
   dump_array(possible);
   dump_array(found);
   set_this_player(tp);

   if (!found)
      found = ({ });

   list = possible - found;
#endif
   list = get_item_search_list(caster);
   herbs = filter(list, &operator(==)("elidross") @ &->query_herb_name());
   if (sizeof(herbs))
      ingr[0] = herbs[0];
   herbs = filter(list, &operator(==)("amanita") @ &->query_herb_name());
   if (sizeof(herbs))
      ingr[1] = herbs[0];

  tp = this_player();
  set_this_player(find_player("stralle"));
  dump_array(ingr);
  PP_DEBUG("gListIsActive: " + gListIsActive);
  set_this_player(tp); 

   if (!objectp(ingr[0]) && !objectp(ingr[1]))
      return 0;

   return ingr;
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("pplaneswalk");
    set_spell_desc("Step into another plane to speed up travel");

    set_spell_element(SS_ELEMENT_LIFE, 45);
    set_spell_form(SS_FORM_DIVINATION, 30);

    set_spell_time(10);
    set_spell_mana(222);

    set_spell_task(TASK_ROUTINE);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(pplaneswalk_ingr);
//    set_spell_ingredients(({"elidross", "amanita"}));
#endif

    set_spell_target(pplaneswalk_target);
    set_spell_resist(0);

    set_spell_vocal(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_visual(0);

    return 0;
}
