/*
 * /d/Gondor/common/guild/obj/blind_ob.c
 *
 * This is an object that is cloned into a player to blind him for some time.
 * It is used with the "brawl" command of the Gondorian Rangers.
 *
 * Originally coded by Lord Elessar Telcontar
 *
 * Revision history:
 *
 * /Mercade, 17 November 1993, recoded and enhanced, solved the killing prob
 */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#define BLIND_SUBLOC "ranger_blind_subloc"

/*
 * Global variables
 */
int    time, old_prop;
object brawler;
object victim;

void
create_object()
{
    set_name("Ranger_Blind_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_time(int i)
{
    time = time + i;
}

void
set_brawler(object ob)
{
    brawler = ob;
}

void
do_blind()
{
    int old_prop = (int)victim->query_prop(LIVE_I_SEE_INVIS);

    victim->add_prop(LIVE_I_SEE_INVIS, -1);

    call_out("can_see_again", time);
    time = 0;
}

void
can_see_again()
{
  if (time < 1)
  {
  /* Ok, this means my eyes are cleared and I can see */
  victim->add_prop(LIVE_I_SEE_INVIS, old_prop);

    if ((!objectp(victim)) || (victim->query_ghost()) || (!living(victim)))
    {
        return;
    }

    victim->catch_msg(BSN("You finally manage to clear your eyes of sand, " +
        "and are able to see again!"));
    TELL_ROOM(ENV(victim), victim, " rubs " + POSSESSIVE(victim) +
        " eyes, and seems to have cleared them of sand!", victim);

    if ((objectp(brawler)) && (environment(brawler) == environment(victim)))
    {
        brawler->CATCH_MSG(" glares at you with hatred in " +
            POSSESSIVE(victim) + " sore eyes.", victim);
        if(!victim->query_attack()) {

        /* I think we need an euid to force someone. */
        seteuid(getuid(TO));
        victim->add_prop(LIVE_O_LAST_KILL, brawler);
        victim->command("kill " + brawler->query_real_name());
        }
    }

    call_out("remove_object", 1);
  }
  /* Oops, somebody has thrown more sand in my eyes! */
  else {
    call_out("can_see_again",time);
  time = 0;
  }
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to))
    {
        call_out("remove_object", 1);
        return;
    }

    if (!living(to))
    {
        call_out("remove_object", 1);
        return;
    }

    victim = to;
    victim->add_subloc(BLIND_SUBLOC,TO);
    do_blind();
}

void
leave_env(object from, object to)
{
    from->remove_subloc(BLIND_SUBLOC);
    ::leave_env(from, to);

    if (find_call_out("can_see_again") != -1)
    {
        can_see_again();
    }
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
  string str;
  if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    return "";
  if (for_obj == carrier)
    str = "You have trouble looking, since your eyes are filled with sand!\n";
  else str = CAP(carrier->query_pronoun()) +
    " is desperately trying to get sand out of "+
    carrier->query_possessive()+" eyes!\n";
  return str;
}
