#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <macros.h>
#include <ss_types.h>

inherit MITHAS_IN;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";


/*
*    prototypes.
*/
void set_up_skills();


void
reset_mithas_room()
{
    return;
}

void
create_mithas_room()
{
    set_short("Training room");
    set_long("This is the training room in Nethosak. It "+
             "is were people from all over Ansalon come "+
             "to train and learn skills from some of the "+
             "best fighters around, for a small fee of "+
             "course. It's also possible to meditate here "+
             "to estimate how physically and mentally far "+
             "you are from advancing. There's an exit to "+
             "the south leading to the main road.\n");   

    add_exit(MROOM + "road48","west","@@remove_medi_props");

    create_skill_raise();
    set_up_skills();

    reset_mithas_room();
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
    write("You start to concentrate solely upon your own mind and you " +
      "block off all your senses. A feeling of great ease and self " +
      "control falls upon you as you slowly sink into a deep " +
      "trance.\n");

    say(QCTNAME(TP) + " enters into a trance and slowly kneels " +
      "down. " + C(PRONOUN(TP)) + " sinks into a deep trance and " +
      "seems lost to the world around " + OBJECTIVE(TP) + ".\n"); 
}


int
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface " +
      "of your consciousness. You exhale and feel very relaxed as " +
      "you get up and prepare yourself for whatever may lie ahead. " +
      " \n");

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
	sk_add_train(SS_PARRY,"parry attacks",0,0,90);
    sk_add_train(SS_WEP_POLEARM,"use a polearm",0,0,90);
    sk_add_train(SS_WEP_SWORD,"use a sword",0,0,90);
    sk_add_train(SS_WEP_AXE,"use a knife",0,0,90);
    sk_add_train(SS_SWIM,"swim",0,0,90);
    sk_add_train(SS_DEFENCE,"avoid getting hit",0,0,90);
    sk_add_train(SS_APPR_MON,"consider enemies",0,0,90);
    sk_add_train(SS_HUNTING,"hunt",0,0,25); 
    sk_add_train(SS_2H_COMBAT,"fight with two weapons",0,0,0,30);   
    sk_add_train(SS_AWARENESS,"be more wary",0,0,30);
}

int
sk_improve(string sk)
{
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
sk_hood_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further " +
      "here, you have to \n" + "seek knowledge elsewhere. \n");
    return 0;
}

