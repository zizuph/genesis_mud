/*
 * /d/Shire/bree/obj/medallion.c
 * Badge of the Society for the Preservation of Treehouses
 * -- Finwe, October 2005
 *
 *   Modification log:
 *
 *        2006.09.05, Toby: Change command throw to clthrow as
 *                          it intervened with other objects throw.
 *                          just changing [away] to 'away' did not work.
 *
 *        2008.10.18, ?: Last modified
 *        2011.07.22, Lavellan: Added slot, so doesn't vanish when worn.
 *                      Fixed some typos
 *        2015.05.18, Gorboth: Changed "clhelp" to "clcommands" to avoid
 *                             conflict with Khalakhor guild commands.
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

throw_it();

query_auto_load()
{
  return MASTER;
}

create_object()
{
  set_name("medallion");
  set_adj("small");
  add_name("_shire_medallion");
  set_short("small brass medallion");
    set_long("This is a round medallion made of brass. On the front of " +
        "the badge, set in the center is an image of a treehouse. In a " +
        "circle, surrounding the image are the words 'Society for the " +
        "Preservation of Treehouses'. On the back of the badge " +
        "are the words, 'Protect Treehouses!' It looks like 'clcommands' " +
        "will tell you more about the club.\n");
  set_slots(TS_CHEST);
  set_looseness(10);

  add_prop(OBJ_I_NO_DROP,"This is too valuable of an object to lose.\n");
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
  {
    return "";
  }

  if (for_obj == on)
    data = "You are ";
  else
    data = capitalize(environment(this_object())->query_pronoun()) + " is ";

  data+="a member of the Society for the Preservation of Treehouses.\n";

  return data;
}

enter_env(object dest,object old)
{
  remove_name("_shire_medallion");
  if(present("_shire_medallion",E(TO)))
    {
      tell_room(E(TO),"You throw the duplicate medallion away.\n");
      remove_object();
      return;
    }

  add_name("_shire_medallion");
  if(living(E(TO)))
    dest->add_subloc("_shire_medallion", this_object());
}

public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("_shire_medallion");
}

init()
{
    ::init();
    add_action("badge", "clthrow");
    add_action("help", "clcommands");
    add_action("treehouse", "clhouse");
    add_action("polish", "clpolish");
    add_action("trees", "cltrees");
    add_action("toss", "cltoss");
//    add_action("wack", "clwack");
    add_action("wack", "clwhack");
//    add_action("skip", "clskip");
}
 
badge(string s)
{
    /* Check in future if query_cmdlist gives another throw in the player and if so
     * return that NF if possible. for now changed command to clthrow. Toby
     */
    NF("Throw away what? The medallion?\n");
    if(!strlen(s) || !parse_command(s,TO," 'away' [the] [small] [brass] 'medallion' "))
        return 0;
    else
    {
        TP->catch_msg("You throw away the " +short()+ ". It bounces on the ground then rolls away.\n");
        say(QCTNAME(TP)+ " throws the " +short()+ ". It bounces on the ground then rolls away.\n"); 
        set_alarm(4.5, 0.0, &throw_it());
        return 1;
    }
}

int
throw_it()
{
    TO->remove_object();
    return 1;
}


/*******************************************************************************
 * Emotes
 ******************************************************************************/

int
help()
{
    write("As a member of the club, you are granted some extra emotes. " +
        "Below are what they are:\n" +
//        "\tclhouse, clpolish, cltoss, cltrees, clwack\n\n" +
        "\tclhouse, clpolish, cltoss, cltrees, clwhack\n\n" +
        "If you want to leave the club, you may either return to the " +
        "treehouse or 'clthrow away medallion' at anytime.\n");
    return 1;
}


int
polish()
{
    write("You blow some hot air onto the medallion, and polish it.\n");
    say(QCTNAME(TP) + " blows some hot air onto "+HIS_HER(TP)+
//        " medallion and polishes it.\n");
        " " + short() + " and polishes it.\n");
    return 1;
}

int
toss()
{
    write("You toss the " + short() + " into the air. It flips several times in the air, and then falls flat into your hand.\n");
//    say(QCTNAME(TP) + " tosses "+HIS_HER(TP)+ " " + short() + "into the air. It flips several times then falls flat into " + HIS_HER(TP) + " hand.\n");
    say(QCTNAME(TP) + " tosses "+HIS_HER(TP)+ " " + short() + " into the " +
        "air. It flips several times then falls flat into " + HIS_HER(TP) +
        " hand.\n");
    return 1;
}

int
treehouse()
{
    write("You tell everyone about the wonderful treehouse you found.\n");
    say(QCTNAME(TP) + " tells you about the wonderful treehouse " + 
        HE_SHE(TP) + " found.\n");
    return 1;
}

int
trees()
{
    write("You expertly expound on the virtues of healthy trees.\n");
//    say(QCTNAME(TP) + " expertly exponds on the virtues of healthy trees.\n");
    say(QCTNAME(TP) + " expertly expounds on the virtues of healthy trees.\n");
    return 1;
}

int
wack()
{
    write("You whack everyone upside the head, trying to get their attention.\n");
    say(QCTNAME(TP) + " whacks you upside the head, trying to get your attention.\n");
    return 1;
}

// skipping routines

void
start_skip(object player)
{
    object shadow;

    setuid(); seteuid(getuid());

    if(player->query_prop(LIMP_PROP))
    {
        write("This may conflict with your Old Fogey movement. Please " +
            "turn that off first.\n");
        return;
    }

//    check_movements(player);
    shadow = clone_object("/d/Shire/guild/clubs/treehouse/skip_shadow");
    if (!shadow->shadow_me(player))
	shadow->remove_object();
}

void
stop_skip(object player)
{
    player->remove_prop(SKIP_PROP);
    player->remove_treehouse_skip_shadow();
}

int
skip(string str)
{
    if (TP->query_treehouse_skip_shadow() && str != "stop")
    {
	    write("You're already skipping along.  Use 'clskip stop' to stop.\n");
	    return 1;
    }

    if(!str)
    {
	    write("Your eyes twinkle and smile broadly. Suddenly, you get an urge to start skipping everywhere you go.\n");
	    say(QCTNAME(TP) + " eyes twinkle and smiles broadly. " + CAP(HE_SHE(TP)) + " suddenly shuffles " + HIS_HER(TP) + " feet slightly.");
	    start_skip(TP);
	return 1;
    }

    if(str != "stop")
    {
    TP->remove_prop(LIMP_PROP);
	write("clskip stop, maybe?\n");
	return 1;
    }
    write("You stop skipping.\n");
    say(QCTNAME(TP) + " suddenly stops skipping.");
    stop_skip(TP);
    return 1;

}


