/* One of the  training rooms for the      *
 *           Shadow Union                  *
 *           Cirion 031996                 *
 *
 * Revisions:
 *   Lilith, May 2004: Raised max skill for trainees
 *
 */
#pragma strict_types

#include "../defs.h"
#include "../lib/skills.h"

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>

inherit BASE;
inherit "/lib/skill_raise";

#define SEE_WEST	({ "/d/Shire/smiths/rooms/shadow_forge" })

public object trainer;

public void set_up_skills(void);

public int
go_up(void)
{
    if (trainer->query_questor())
    {
	trainer->command("emote moves into the shadows near the forge.");
	trainer->check_room();
    }

    write("You ascend the stairs.\nThey rise to the "+
	"north, where you come out on a landing.\n");
    return 0;
}

public string
west_view(void)
{
    object *live = get_view(SEE_WEST);

    if (!sizeof(live))
	return "";

    return " In the western side of the cavern you can see "+
	COMPOSITE_LIVE(live) + ".";
}

public void
reset_room(void)
{
    /* If the NPC has been slain, then the "union_o_corpse_of_<npc>" */
    /* prop will be set in this room (from the make_corpse())        */
    /* function in NPC + "npc.c". Until the corpse is destroyed,     */
    /* the Union member will not reset.                              */
    if (!trainer)
    {
	if (!objectp(query_prop(UCORPSE_PROP("hephamenios"))))
	    trainer = clone_here(NPC+"hephamenios");
    }

    if (trainer && !present(trainer))
	trainer->move_living("away", TO);
}

public void
union_room(void)
{
    set_short("hephamenios' forge");
    set_long("Steam rises up everywhere, making the heat "+
      "almost unbearable. You are in a circular cavern, "+
      "rough-hewn and irregular. A broad staircase rises up "+
      "into the northern wall, dividing this cavernous space "+
      "into two areas, of which you are currently in the "+
      "eastern half.@@west_view@@ "+
      "A large, square chute has been cut into "+
      "the south wall, the base of which glows bright red, "+
      "as if the rock there were superheated to the point "+
      "of melting. On the east side of the room is a large "+
      "basin of water and a heavy iron anvil. There is also "+
      "a large rack containing various tools and unfinished "+
      "blades.\n");

    add_item("anvil","It is massive, made completely of iron, "+
      "and is covered in innumerable scratch marks.\n");
    add_item(({"stair","staircase"}),"The stairs are broad, "+
      "made from thick granite and rising to the west, "+
      "where it disappears around a bend to the north.\n");
    add_item(({"cave","cavern","room","chamber","forge",
	"wall","walls"}),"The walls of the cavern are rough "+
      "and irregular, almost making them seem naturally "+
      "formed. The southern wall glows with a hot, red light.\n");
    add_item(({"glow","light","south wall","southern wall"}),
      "The south wall glows molten red, as if there were "+
      "a mass of lava just behind or below it. The heat "+
      "from the wall makes the entire cavern stifling "+
      "and unbearably hot.\n");
    add_item(({"rack","tools","tool","hammer","tongs","tong",
	"blades"}), "The rack contains a heavy hammer, numerous "+
      "unfinished knife blades, and some smaller tools like tongs.\n");

    add_cmd_item(({"wall","rock","stone","molten rock"}),
      ({"touch","feel"}), "The rock is burning hot, almost "+
      "to the point of melting.\n");
    add_cmd_item(({"rack","tools","tool","hammer","tongs",
	"tong","blades"}), ({"get","take","steal"}),
      "Hephamenios would break your fingers if you took his "+
      "tools. If you want to try your hand at forging, "+
      "use the forge west of here.\n");
    add_cmd_item(({"anvil", "forge" }), ({"get","take"}),
      "It is far too heavy.\n");

    add_exit("f_landing", "up", "@@go_up@@", 2);
    add_exit("/d/Shire/smiths/rooms/shadow_forge", "west");

    set_noshow_obvious(1);

    create_skill_raise();
    set_up_skills();

    /* Wiz info for stat_object */
    add_prop(OBJ_S_WIZINFO, "This is one of the training halls "
      +"for the Union of the Warriors of Shadow. If a problem "
      +"occurs and you find it necessary to shut down the "
      +"guild, do 'Call /d/Avenir/union/list close_guild' (NOT "
      +"Call here close_guild). Note that this will shut down "
      +"ALL of the training rooms in the guild, and it will "
      +"remain so until someone calls open_guild (ie, it will "
      +"last through reboots). In other words, make sure you "
      +"have a good reason for doing it!\n");

    add_object(OBJ+"basin");
    add_object(OBJ+"chute");
    reset_room();
}

public void
init(void)
{
    ::init();
    init_skill_raise();
}

/* Skill functions and hooks */
public void
set_up_skills(void)
{
    sk_add_train(SS_APPR_OBJ,
      "appraise various objects",
      0, 3,
      MAX_APP_OBJ,
      SS_INT, 90);
}

/*
 * Function name: sk_hook_unknown_skill
 * Description:   Player tries to improve or learn an unknown skill
 */
public int
sk_hook_unknown_skill(string skill, string verb)
{
    if (!present(trainer))
	return 0;

    trainer->command("us I cannot teach you that.");
    trainer->command("us Perhaps there is somewhere else "+
	"you could learn it...");

    return 1;
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 */
public int
sk_hook_cant_train(string skill, int to_lev)
{
    if (!present(trainer))
	return 0;

    trainer->command("us You would need to be a bit "+
	"smarter to learn that any further.");

    return 1;
}

/*
 * Function name: sk_hook_cant_pay
 * Description:   Player can't pay for session (kill him?)
 */
public int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    trainer->command("us I'm afraid I need to charge you "+
	"for the cost of training, and you "+
	"can't afford my price right now.");

    return 1;
}

/*
 * Function name: sk_hook_no_list_learn
 * Description:   No more unknown skills for the player in this guild
 */
public int
sk_hook_no_list_learn(void)
{
    if (!present(trainer))
	return 0;

    trainer->command("us You have begun to learn all the "+
	"skill I can teach you, "+ TP->query_name() +".");
    trainer->command("us You can work on improving those "+
	"skills you know.");

    return 1;
}

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:	  str - The rest of the command player made
 * Returns:	  1/0
 */
public int
sk_improve(string str)
{
    if (GUILD_CLOSED)
    {
	write("The Union has been shut down due to problems, so "+
	    "training is impossible.\nTry back later.\n");

	return 1;
    }

    if (!present(trainer))
	return 0;

    if (!IS_MEMBER(TP))
    {
	trainer->command("say You are not a member of the Union.");
	return 1;
    }

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOTRAIN))
    {
	trainer->command("us I have been told that you "+
	    "are to be denied instruction.");
	trainer->command("shrug .");
	return 1;
    }

    if (!STATE)
    {
	trainer->command("us You have let the flame go out. I "+
	    "will teach you nothing.\n");
	return 1;
    }

    if (IS_MEMBER(TP) && ENEMY(TP))
    {
	trainer->command("us Traitor and fool! Do you honestly "+
	    "think I will teach you after your actions?");
	trainer->command("shout Begone before I slay you!");
	return 1;
    }

    return ::sk_improve(str);
}

public varargs int
sk_query_max(int sknum, int silent)
{
    int max;

    /* Players that are trainees will not be able to train very high */
    if (TP->query_skill(OCC_LEVEL) < NORMAL)
	max = 50;
    else
	max = MAX_APP_OBJ;

    return min(max, ::sk_query_max(sknum, silent));
}
