/*
Kendermore Adventurer's Guild
Gwyneth, June 1999
*/

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/kendermore/local.h"
#include <macros.h>
#include <ss_types.h>

inherit KENDERMORE_OUT;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

object vincint_ogre;

/*
*    prototypes.
*/
void 
set_up_skills();


void
reset_kendermore_room()
{
    if (!vincint_ogre)
    {
        vincint_ogre = clone_object(KNPC + "vincint.c");
        vincint_ogre->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("A wide open courtyard");
    set_long("@@long_descr");

    add_item(({"rack", "clubs"}), "The clubs hang neatly out of the way " + 
        "in the large wooden rack.\n");
    add_item(({"wooden table", "table"}), "A few pieces of parchment, some " + 
        "quills, and ink pots have been placed on the table.\n");
    add_item("courtyard", "You stand in an open courtyard used for " + 
        "training.\n");
    add_item(({"pots", "ink pots"}), "They are filled with black ink.\n");
    add_item("parchment", "It is clear and ready to be written on.\n");
    add_item("quills", "They are long thin feathers. Dipped in ink, they " + 
        "can be used to write with.\n");
    add_item(({"bench", "wooden bench"}), "It has been pulled up to the " + 
        "table, and looks quite comfortable for a wooden bench.\n"); 
    add_item(({"wall", "east wall"}), "It is rough, and looks like it can " + 
        "be used to train a person to climb.\n");

    add_exit(KROOM + "street54", "northeast", "@@remove_medi_props");
    add_exit(KROOM + "street55", "southeast", "@@remove_medi_props");
    add_exit(KROOM + "w_tower", "northwest", "@@remove_medi_props");

    add_cmd_item("wall", "climb", "@@climb_wall");
    create_skill_raise();
    set_up_skills();

    reset_kendermore_room();
}

string
long_descr()
{
    return(tod_descr() + season_descr() + "You've come across a large " + 
        "open courtyard. Some well used clubs have been carefully placed " + 
        "in a rack next to a wooden table and bench. A large wall has been " + 
        "built on the east side. There is plenty of " + 
        "open space, but the passers-by seem to avoid it. Perhaps because " +
        "there is often martial training going on when the trainer is " + 
        "present.\n");
}

string
climb_wall()
{
    if (TP->query_skill(SS_CLIMB) < 30)
    {
        write("You start to climb the wall, but fall down. Perhaps you " + 
            "could get some training here?\n");
        say(QCTNAME(TP) + " attempts to climb the wall, but falls down.\n");
        return "";
    }

    write("You quickly climb up and down the wall, displaying your skill.\n");
    say(QCTNAME(TP) + " quickly climbs up and down the wall, " +
        "displaying " + HIS(TP) + " skill.\n");
    return "";
}

int
remove_medi_props()
{
    TP->remove_prop(LIVE_I_MEDITATES);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
}


void
init()
{
    init_guild_support();
    add_action("gs_meditate","meditate");
    init_skill_raise();
    ::init();
}


void
gs_hook_start_meditate()
{
    write("With great concentration, you block off the noisy chatter " +
      "of your surroundings. You turn your mind inward, focusing on " + 
      "your inner being. A feeling of peace and tranquility comes over " + 
      "you as you sink into a deep trance. You feel you could <estimate> " + 
      "your abilities. As well, you can exert enough control over your " + 
      "body to <set> which abilities you want to concentrate on. To return " + 
      "from your trance, you must <rise>.\n");

    say(QCTNAME(TP) + " finds a relaxing position and closes " + HIS(TP) + 
        " eyes. A peaceful look comes over his face as " + HE(TP) + 
        " enters a deep trance.\n");
}


int
gs_hook_rise()
{
    write("You gradually bring your consciousness back from the deep " +
        "trance. You breathe in the fresh air and slowly open your eyes, " + 
        "feeling refreshed and relaxed.\n");

    say(QCTNAME(TP) + " takes a deep breath and slowly opens his eyes, " + 
        "returning from " + HIS(TP) + " deep trance. " + HE(TO) + " then " + 
        "rises, refreshed and relaxed.\n");
}


void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}


void
set_up_skills()
{
    sk_add_train(SS_WEP_CLUB,"use a club",0,0,30);
    sk_add_train(SS_LANGUAGE,"speak other languages",0,0,30);
    sk_add_train(SS_AWARENESS,"be more wary",0,0,30);
    sk_add_train(SS_CLIMB,"climb",0,0,30);
    sk_add_train(SS_APPR_OBJ,"find out properties of an object",0,0,30);
}

int
sk_improve(string sk)
{
    if (!(present("vincint", TO)))
    {
        write("Without a trainer, your efforts to improve go awry.\n");
        return 1;
    }
    return ::sk_improve(sk);
}

int
sk_query_max(int snum)
{
    int *skills_available_here;
    mixed skval;

    skills_available_here = sk_query_train();

    if(member_array(snum, skills_available_here) == -1)
	return 0;

    if (!mappingp(sk_default))
	return 0;
    skval = sk_trains[snum];
    if (sizeof(skval)>2)
	return skval[2];
    else return 0;
}


int
sk_hook_improved_max(string skill)
{
    notify_fail("That level of expertise is beyond Vincint's " +
      "knowledge.\nSeek knowledge elsewhere. \n");
    return 0;
}

