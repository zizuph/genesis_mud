/*
 * The Black Claw training hall, modified by Turgon from Elessars 
 * training hall of Rangers, Sun 13 October 1996
 *
 * Modification log:
 *
 */

#pragma save_binary

inherit "/lib/guild_support";
inherit "/d/Shire/room";
inherit "/lib/skill_raise";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/bits.h"
#include "/d/Shire/skills.h"
#include "/d/Shire/guild/claws/claw_defs.h"

#define NUM sizeof(query_money_types())

void set_up_skills();

object meditate;

void
create_trainhall()
{
    set_short("Black Claw training hall");
    set_long("This is the vast hall where the Orkish warriors which belong "+
        "to the Black Claw Clan gain new knowledge in many different skills. "+
        "Some can be seen fighting with swords, while other practice how "+
        "to improve their defence with shields. You can either <learn> new "+
        "skills here, or you might even try to <improve> them here. It is "+
        "also possible to seek guidance from The Mightiest of all, the One "+
        "by trying to <meditate>. By doing so Melkor can tell you something "+
        "about your mental/physical abilities and how they are improving. "+
        "Just south of here is a huge door which lead into the dining room.\n");

    add_exit("throne", "east");
    add_exit("meeting", "northwest");
}

nomask void
create_room()
{
    create_trainhall();

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    
    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_item(({"poster", "skill list", "skill-list", "list"}),
        "@@read_poster");

	//JOINROOM->load_me();
}

string
exa_poster()
{
    int i, snum, smax;
    int *guild_sk = sk_query_train();
    string list = "These are the skills you can learn here as a Black Claw: \n\n";

    guild_sk = sort_array(guild_sk);
    for (i = 0; i < sizeof(guild_sk); i++)
    {
        snum = guild_sk[i];
        smax = ::sk_query_max(snum, 0);
        if (smax)
            list += sprintf(" %-25s %-25s", sk_trains[snum][0], sk_rank(smax));
    }

    return list + "\n";
}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (!str || 
    (str != "poster" && 
     str != "skill list" &&
     str != "skill-list" &&
     str != "list"))
    return 0;

    write(exa_poster());
    return 1;
}


int
skill_loc(int sk)
{
	int a;
	a = member_array(sk, SKILLS);
	if (a < 0)
		return -1;
	return a;
}

int
cmax(int sk)
{
    int     a,
            max_rs,
            rank_no;

    a = skill_loc(sk);

    if ((a == -1) && TP->query_wiz_level())
    {
        TP->catch_msg("BLACK CLAWS: The training room is trying to set up "
          + "a skill not listed in claws_defs.h!\n");
        return 0;
    }
    else
        return 0;

    rank_no = 0;
    while (rank_no < sizeof(RANK_SKILLS))
    {
        if (RANK_SKILLS[rank_no][a] > max_rs)
            max_rs = RANK_SKILLS[rank_no][a];
        rank_no++;
    }
    return max_rs;
}

int
rank_max(int sknum, int rank_no)
{
    int     a;

    a = skill_loc(sknum);
    rank_no -= 1;
    if (a == -1)
        return 0;
    else if ((rank_no < (SLAVE - 1)) || (rank_no > (CAPTAIN - 1)))
        return 0;
    else
        return RANK_SKILLS[rank_no][a];
}


void
set_up_skills()
{
    string me;
//    me = "fight with spears";
//    sk_add_train(SS_WEP_SPEAR,({ me, me }), 0, 0, cmax(SS_WEP_SPEAR));
//           me = "use scimitars and shortswords effectively";
//    sk_add_train(SS_WEP_SHORTSWORD,({ me, me }), 0, 0, cmax(SS_WEP_SHORTSWORD));
    me = "use clubs effectively";
    sk_add_train(SS_WEP_CLUB, ({ me, me }), 0, 0, cmax(SS_WEP_CLUB));
    me = "defend in combat";
    sk_add_train(SS_DEFENCE,({ me, me }), 0, 0, cmax(SS_DEFENCE));
    me = "parry blows with a weapon";
    sk_add_train(SS_PARRY,({ me, me }), 0, 0, cmax(SS_PARRY));
    me = "sneak and move stealthily about";
    sk_add_train(SS_SNEAK, ({ me, me }), 0, 0, cmax(SS_SNEAK));
    me = "hide and conceal";
    sk_add_train(SS_HIDE, ({ me, me }), 0, 0, cmax(SS_HIDE));
    me = "be aware of your surroundings";
    sk_add_train(SS_AWARENESS,({ me, me }), 0, 0, cmax(SS_AWARENESS));
    /* Special Black claw skills */
    //me = "use your claws as weapon";
    //sk_add_train(SS_CLAW, ({ me, me }), "clawing",50, cmax(SS_CLAW));
    //me = "block hits with a shield";
    //sk_add_train(SS_SHIELD, ({ me, me }), "shield", 50, cmax(SS_SHIELD));
    me = "fight unarmed";
    sk_add_train(SS_UNARM_COMBAT,({ me, me }), 0, 0, cmax(SS_UNARM_COMBAT));
    me = "climb";
    sk_add_train(SS_CLIMB,({ me, me }), 0, 0, cmax(SS_CLIMB));

}

void
init()
{
	init_skill_raise();
    ::init();
	add_action("do_read", "read");
}


void
gs_hook_already_meditate()
{
	write(BSN("You are already in contact with Melkor. If you wish to loose "+
		"your contact with him, and leave this state, just type 'rise'. "));
}

gs_hook_start_meditate()
{
	write(BSN("You touch the crystal sphere and all of a sudden you feel "+
		"an great evil sensation. An powerful eye stares at you, and a "+
		"twisted voice tells you: \n\n"+
		"  If thou wilst, I can <estimate> thy different preferences,\n"+
		"  or I can <set> them as you desire.\n\n"+
		"Thy can leave this high mental state by typing <rise> when thou "+
		"is finished. "));
}

void
gs_hook_rise()
{
	write(BSN("As you move your hands away from the sphere, the blurred picture of "+
		"the great, stirring eye vanishes, and the voice can be heard no more. "));
}

/*
 * Function name: sk_hook_write_header
 * Description:   Write the header to the improve or learn list
 * Arguments:     Steps - How many steps are we talking about
 */
void
sk_hook_write_header(int steps)
{
	if (!steps)
	  steps = 1;
	write("These are the skills you are able to " + query_verb() +
	" " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") +
	" here.\n");
    write("  Skill:                  Cost:    "+
		  "Next level:              Max level:\n"+
		  "--------------------------------------"+
		  "--------------------------------------\n");
}

/*
 * Function name: sk_hook_skillisting
 * Description:   Someone is listing the skills
 */
void
sk_hook_skillisting()
{
	write("Here follows the skills we teach, and your next level in "+
	  "those skills:\n");
	write("   Skills:                Cost:    "+
	      "Next level:           Max level:\n"+
		  "--------------------------------------"+
	      "--------------------------------------\n");
}

/*
 * Function name: sk_list
 * Description:   Someone wants a list of skills
 * Arguments:     steps - How many steps the player wants to raise
 * Returns:       1
 */
int
sk_list(int steps)
{
	int i, *guild_sk, learn;

	guild_sk = sort_array(sk_query_train());
	if (!steps)
	  steps = 1;

	if (steps < 0)
	{
	  sk_hook_skillisting();
	  steps = 1;
	}
	else if (query_verb() == "learn")
	{
	  guild_sk = filter(guild_sk, "sk_filter_learn", this_object(), steps);
	  if (!sizeof(guild_sk))
		return sk_hook_no_list_learn();
		sk_hook_write_header(steps);
	}
	else
	{
	  guild_sk = filter(guild_sk, "sk_filter_improve", this_object(), steps);
	  if (!sizeof(guild_sk))
		return sk_hook_no_list_improve();
		sk_hook_write_header(steps);
	}

	for (i = 0; i < sizeof(guild_sk); i++)
	write(sk_fix_cost(guild_sk[i], steps));

	return 1;
}

/*
 * Function name: sk_fix_cost
 * Description:   Fix each line in the improve/learn list
 * Arguments:     snum - The skill to check
 *                steps - How many steps the player wants to raise
 * Returns:       A formated string
 */
varargs string
sk_fix_cost(int snum, int steps)
{
    int this_level, next_level, max;
    string next_rank, max_rank, cost;

    this_level = this_player()->query_base_skill(snum);
    next_level = steps ? this_level + steps : this_level + 1;

    if (next_level > (max = sk_query_max(snum,0)))
        cost = "---";
    else
        cost = sk_cost(snum, this_level, next_level) + " cc";

    if(!max)
        return "";

    if (this_level >= 100)
        next_rank = "maxed";
    else
        next_rank = sk_rank(next_level);

    max_rank = sk_rank(max);

    return sprintf("  %-21s %9s  %-21s %-20s\n", sk_trains[snum][0],
                cost, next_rank, max_rank);
}

varargs int
sk_query_max(int sknum, int silent)
{
    int     pl_rank,
            r_max;
    object  pl;

    seteuid(getuid());
    if (!objectp(previous_object()))
        pl = calling_object();
    else
        pl = previous_object();
    if (!this_player() || ((this_player() != previous_object()) &&
        previous_object() != this_object()))
        pl = previous_object();
    else
        pl = this_player();
    if (silent)
    {
        if (objectp(pl))
            return rank_max(sknum, pl->query_claw_rank());
        else
            return cmax(sknum);
    }
    pl_rank = pl->query_claw_rank();
    r_max = rank_max(sknum, pl_rank);
    return r_max;
}

int
sk_improve(string str)
{
    object tp = TP;
    int     rank_no = tp->query_claw_rank();

    if (rank_no < SLAVE)
    {
        write("You are not an Orc of the Black Claw! Go away or you "
          + "will be killed!\n");
        return 1;
    }
    return ::sk_improve(str);
}

