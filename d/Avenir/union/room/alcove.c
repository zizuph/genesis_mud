/* One of the  training rooms for the      */
/*           Shadow Union                  */
/*           Cirion 031996                 */
/* Revisions:
 * 	Lilith, May 2004: Raised max skill for trainees
 * 	Lucius, Aug 2017: Re-Code.
 */
#pragma strict_types

#include "../defs.h"
#include "../lib/skills.h"

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>

inherit BASE;
inherit "/lib/skill_raise";

public object trainer, shelf;

public void set_up_skills(void);


public string
shelf_inv(void)
{
    if (!shelf) return "";
    return shelf->external_within();
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
	if (!objectp(query_prop(UCORPSE_PROP("arcadelt"))))
	    trainer = clone_here(NPC+"arcadelt");
    }

    if (trainer && !present(trainer))
	trainer->move_living("away", TO);
}

static void
update_vars(void)	{ shelf = present("_union_shelf"); }

public void
union_room(void)
{
    set_short("alcove");
    set_long("This is a small alcove just off a corridor "
      +"of reddish and smooth granite. The floor here is "
      +"of smooth, polished stone, covered by a thin "
      +"but strong rug.@@shelf_inv@@ The west wall is "
      +"open to the corridor.\n");

    add_item(({"rug","carpet"}),"The rug is made from a "
      +"strong grey cloth of very tight weave.\n");
    add_item(({"shelf","shelves"}),"It is a narrow stone shelf that "
      +"runs along the walls of the room.\nThere is nothing "
      +"on the shelf.\n");
    add_item(({"floor","ground"}),"It is covered by a thin grey rug.\n");
    add_item(({"hall","hallway","west","corridor"}),"A long and narrow "
      +"corridor lies west of here, from where a powerful "
      +"sense of heat presses in.\n");
    add_item(({"wall","walls","granite"}),"The walls are of smooth "
      +"reddish granite, and feel cold.\n");

    add_cmd_item(({"wall","walls","granite"}),({"touch","feel"}),
	"The granite walls are cold to the touch.\n");
    add_cmd_item(({"shelf","rug","carpet"}), "get",
	"That is impossible.\n");
    add_cmd_item(({"rug","carpet"}),({"lift","move","pull"}),
	"There is nothing beneath it.\n");

    add_exit("hall_n3", "west");

    create_skill_raise();
    set_up_skills();

    add_object(OBJ+"shelf");
    reset_room();
}

public void
init(void)
{
    ::init();
    init_skill_raise();
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
	trainer->command("say You are not permitted, "+
	    TP->query_race_name()+".");
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
	trainer->command("us I teach nothing to one who would let "+
	    "our flame go out.\n");
	trainer->command("scowl .");
	return 1;
    }

    if (IS_MEMBER(TP) && ENEMY(TP))
    {
	trainer->command("us After what you have done? I think not.");
	return 1;
    }

    return ::sk_improve(str);
}

public void
set_up_skills(void)
{
    sk_add_train(SS_LOC_SENSE,
	"discern location",
	0, 0, MAX_LOC_SENSE);

    sk_add_train(SS_BLIND_COMBAT,
	"fight in darkness",
	0, 0, MAX_BLINDFIGHT);

    sk_add_train(SS_AWARENESS,
	"be aware of surroundings",
	0, 0, MAX_AWARENESS);
}

public varargs int
sk_query_max(int sknum, int silent)
{
    int max;

    switch(sknum)
    {
    case SS_LOC_SENSE:    max = TP->query_stat(SS_INT);       break;
    case SS_BLIND_COMBAT: max = TP->query_stat(SS_WIS);       break;
    case SS_AWARENESS :   max = TP->query_stat(SS_INT);       break;
    default:              max = TP->query_stat(SS_OCCUP);     break;
    }

    /* Players that are trainees will not be able to train very high */
    if (TP->query_skill(OCC_LEVEL) < NORMAL)
	max = 50;

    return min(max, ::sk_query_max(sknum, silent));
}
