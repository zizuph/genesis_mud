/* The training chamber of the Inventors
 * taken from Vingaard Keep coded by Percy, 
 * modified for the gnomes guild by Dajala
 */

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Krynn/std/room";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include <std.h>
#include <ss_types.h>
#define  BUILD_MAX  100   /* Even numbers only */
#define  TRADE_MAX  50   /* Even numbers only */

#define PARENT  "/d/Krynn/"
#define TDIR    PARENT + "gnome/"
#define MON	    TDIR + "monster/"

int levlim;
object trainer;
object meditate;

/*
 * Prototypes
 */
void set_up_skills();

void
reset_room()
{
    if (trainer)
	return;
    trainer = clone_object(MON + "armavir");
    trainer->move_living("xxx",TO);
}

void
create_room()
{
    INSIDE;
    LIGHT;
    set_short("Training room");
    set_long(BSN(
	"You are in the training room of the Inventor Guild. Here, "
	+ "Armavir, the master inventor can help you to improve "
	+ "skills of different types. You can either 'learn' "
	+ "a new skill or 'improve' a skill you already know "
	+ "something about. The central guild hall is south of "
	+ "here."));

    add_exit(ROOMS + "joinroom", "south", 0);

    create_skill_raise();
    set_up_skills();

    set_alarm(1.0, -1.0, "reset_room");
}


void
init()
{
    init_skill_raise();
    init_guild_support();
    ::init();
}

/* always define the name of the skill when introducing further skills
 * since sk_add_train() has been masked.
 */
void
set_up_skills()
{
    sk_add_train(SS_WEP_CLUB,   "use a hammer","hammer", 0, 30 ); /*  0 */
    sk_add_train(SS_PICK_POCKET,"pick pockets","pick pocket", 0, 20 ); /*  0 */
    sk_add_train(SS_HIDE,       "hide from others","hide", 0, 20 ); /*  0 */
    sk_add_train(SS_AWARENESS,"be aware of things","awareness", 0, 50 ); /*  0 */
    sk_add_train(SS_APPR_OBJ,"appraise objects","appraise object",0,30); /* 0 */
    sk_add_train(SS_APPR_VAL,"appraise values","appraise value",0,30); /* 0 */
    sk_add_train(SS_TRADING,    "trade",    "trading", 0, TRADE_MAX, 0); /* 20 */

    sk_add_train(SS_BUILD, "build and analyze machines", "build", 30, BUILD_MAX, 0);
    /* Special skill
* sum skills: 270, sum above numbers in 'man skills': 20 => 1% tax
* special skills: build  -  max_skill = 100              => 1% tax 
*/
}

int
gs_meditate(string str) 
{
    return ::gs_meditate(str);
}

int
sk_improve(string sk)
{
    if (sk)
    { 
	if (!GMEMBER(TP))
	{
	    NF("Only real Inventors can raise their skills here.\n");
	    return 0;
	}
	if (!trainer || (E(trainer) != TO))
	{
	    NF("Armavir is not here at the moment, I'm afraid.\nYou "
	      + "will have to wait for him to return.\n");
	    return 0;
	}
    }
    NF("You can't do this.\n");
    return ::sk_improve(sk);
}


int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have to\n" +
      "seek knowledge elsewhere.\n");
    if (levlim)
	notify_fail("Sorry, but your rank in our guild doesn't allow you to\n"
	  + "train to that level in this skill.\n");
    return 0;
}

int
sk_query_max(int snum, int silent)
{
    int glev, mxtrain, *skills_available_here;
    mixed skval;

    /* Added to adapt to the skill_decay function.            */
    /* If a skill isn't available here, this function should  */
    /* return 0.               Jeremiah, 95/07/09             */

    skills_available_here = sk_query_train();

    if(member_array(snum, skills_available_here) == -1)
	return 0;


    glev = TP->query_gnome_level();
    if(glev > 10)
	glev = 10;
    mxtrain = MAX_TRAIN[glev];

    if (!mappingp(sk_default))
	return 0;

    skval = sk_trains[snum];

    if (skval[2] < mxtrain)
    {
	mxtrain = skval[2];
	levlim = 0;
    }
    else levlim = 1;
    if (sizeof(skval)>2)
	return mxtrain;
    else
	return 0;
}

/* masked from /lib/skill_raise to get the skill-description
 * 'hammer' instead of 'club'
 */
varargs void
sk_add_train(mixed snum, mixed desc, string name, int costf, 
  int maxskill, int stat, int weight)
{
    int il;
    mixed skval;

    if (!sk_trains)
	create_skill_raise();

    if (!mappingp(sk_default))
	return 0;

    if (pointerp(snum))
    {
	for (il = 0; il < sizeof(snum); il++)
	    sk_add_train(snum[il], desc, name, costf, maxskill);
	return;
    }

    if (!intp(snum))
	return;

    if (weight == 0)
    {
	stat = -1;
	weight = 100;
    }
    skval = sk_default[snum];

#ifdef STAT_LIMITED_SKILLS
    if (pointerp(skval))
	/* The modification is here! --- name instead of skval[0]*/
	sk_trains[snum] = ({ name, skval[1], maxskill, 
	  skval[2], skval[3] });
    else
	sk_trains[snum] = ({ name, costf, maxskill, stat, weight });
#else
    if (pointerp(skval))
	sk_trains[snum] = ({ skval[0], skval[1], maxskill });
    else
	sk_trains[snum] = ({ name, costf, maxskill});
#endif

    if (pointerp(desc))
    {
	if (sizeof(desc) > 1)
	    sk_tdesc[snum] = desc;
	else
	    sk_tdesc[snum] = ({ desc[0], desc[0] });
    } 
    else
	sk_tdesc[snum] = ({ desc, desc });

}
