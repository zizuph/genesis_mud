inherit "/std/object.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

#define MAXDAMAGE	10
#define TUNEDAMAGE      ({"is well tuned and in perfect repair",        \
                        "seems slightly out of tune",                   \
                        "sounds somewhat off-pitch",                    \
                        "sounds out of tune",                           \
                        "requires a thorough tuning",                   \
                        "is painfully out of tune"})

#define LUTE_DAMAGE TUNEDAMAGE +					\
                        ({"has a broken string",                        \
                        "has lost a tuning-peg",                        \
                        "has a warped fret-board",                      \
                        "has a fractured bridge",                       \
                        "has a large crack in its sounding-case"})
#define LUTE_FIX	({"lute_string",				\
			"lute_tuning_peg",				\
			"lute_fret_board",				\
			"lute_bridge",					\
			"lute_big"})

#define RECORDER_DAMAGE TUNEDAMAGE +					\
                        ({"is moldy and needs a good cleaning",         \
                        "has a cracked mouth-piece",                    \
                        "is badly warped by the humidity",              \
                        "is missing its bottom section",                \
                        "has a large crack between finger-holes"})
#define RECORDER_FIX	({"recorder_mouldy",				\
			"recorder_mouth_piece",				\
			"recorder_warped",				\
			"recorder_broken",				\
			"recorder_big"})
	
#define DULCIMER_DAMAGE TUNEDAMAGE +					\
                        ({"has a broken string",                        \
                        "is without one of its hammers",                \
                        "has lost several tuning-pegs",                 \
                        "has a warped bridge",                          \
                        "is broken completely in half"})
#define DULCIMER_FIX	({"dulcimer_string",				\
			"dulcimer_hammer",				\
			"dulcimer_tuning_peg",				\
			"dulcimer_bridge",				\
			"dulcimer_big"})

#define HARP_DAMAGE TUNEDAMAGE +					\
                        ({"has a handful of missing strings",           \
                        "has a cracked forepillar",                     \
                        "has a severely warped neck",                   \
                        "has a crushed resonator",                      \
                        "is broken completely in half"})
#define HARP_FIX	({"harp_strings",				\
			"harp_forepillar",				\
			"harp_neck",					\
			"harp_resonator",				\
			"harp_big"})

#define SHAWM_DAMAGE TUNEDAMAGE +					\
                        ({"has a dried-out and cracked reed",           \
                        "has no mouthpiece",                            \
                        "has some rusty and immobile keys",              \
                        "has sustained heavy water damage",              \
                        "has a shattered bell"})
#define SHAWM_FIX	({"shawm_reed",					\
			"shawm_mouthpiece",				\
			"shawm_keys",					\
			"shawm_water_damage",				\
			"shawm_big"})

#define VIOL_DAMAGE TUNEDAMAGE +					\
                        ({"is missing an A-string",                     \
                        "has a loose and warped bow",                   \
                        "has a splintered and collapsed bridge",        \
                        "has lost all its tuning-pegs",                 \
                        "has its fingerboard completely cracked off"})
#define VIOL_FIX	({"viol_string",				\
			"viol_bow", 					\
			"viol_bridge",					\
			"viol_tuning_pegs",				\
			"viol_big"})

#define TRUMPET_DAMAGE TUNEDAMAGE +					\
                        ({"is blocked up and needs to be cleaned",      \
                        "is badly rusted",                              \
                        "needs a mouthpiece",                           \
                        "has been severely dented",                     \
                        "has been pounded almost completely flat"})
#define TRUMPET_FIX	({"trumpet_blocked",				\
			"trumpet_rusty",				\
			"trumpet_mouthpiece",				\
			"trumpet_dented",				\
			"trumpet_big"})

/*
 * CEDRIC:  I have started on these damage-arrays and some other
 * things.  As you can see, I've added or changed some instrument types
 * as possible suggestions.  Basically, you had a collection of
 * predominantly string instruments and I have sugested offering
 * more varied types.  First, the mandolin is a fairly recently
 * developed instrument, probably from the 16th or 17th century.
 * However, the lute is basically the same but is much older and
 * was the major instrument of the European Renaissance.  Second,
 * I would suggest recorder instead of flute (the modern flute was
 * developed only in the 18th century and the recorder was a very
 * popular medieval instrument).  The dulcimer adds to diversity 
 * because it is hammered instead of plucked.  Harp also is an ancient
 * instrument so I would keep it.  The lyre is quite similar so I
 * would suggest using another type.
 *
 * I suggest adding the following possible types.  The viol, a bowed
 * string instrument much like today's violin, except played with the
 * base resting on one's leg.  The shawm, a loud double-reed like the
 * oboe, very popular in late medieval music.  (You could also have
 * the bombard, a low shawm, somewhat similar to the bassoon.)  You
 * would probably also want some brass-type instruments:  a non-valved,
 * straight trumpet;  the sackbut, or medieval trombone; cornetto, a
 * high-pitched, conical brass instrument.  I have tried to include
 * some arrays for each of the basic types.
 */

int     damage_level = 0;
string  *damage_desc;

void
init()
{
    ::init();
    add_action("do_fix", "tune");
    add_action("do_fix", "repair");
}

void
create_object()
{
    
    if (IS_CLONE) 
        call_out("do_things", 4);
}

void
set_damage_desc(string *the_arr)
{
    damage_desc = the_arr;
}

void
do_things()
{
    object holder;
    
    add_prop(OBJ_M_NO_DROP, "Drop your sacred "+TO()->query_name()+"? You must be joking!\n");
    holder = environment(TO());
    seteuid(getuid(TO()));
    if (!MEMBER(holder))
    {
        holder->catch_msg(BS("The "+short()+" slips from your grasp. "
        + "As you stand and watch, dumbfounded, it becomes translucent and "
        + "gradually vanishes altogether.\n"));
        remove_object();
    }
    if (living(holder))
    {
        holder->add_cmdsoul(GUILD+"minstrel_soul");
        holder->update_hooks();
    }
   
/*
 * About the long_desc for the instruments:  it might be nice to
 * include more description of the instrument itself when the player
 * examines it.  Medieval/Renaissance instruments were often as
 * elaborate and exotic as their strange names, sometimes covered
 * with intricate engravings, mosaics and inscriptions.  For example,
 * the head part of the lute, above the tuning-pegs, was sometimes
 * carved into the shape of a person's head--in this case, perhaps
 * the player's likeness, or that of his muse or something.  Each
 * description could be personalized without a great deal of trouble.
 * The information which you have presently in the long_desc could
 * perhaps be provided to the player under a separate command par-
 * ticular to the object, "inspect" for example.  This would give
 * him the history of the instrument, perhaps in a small inscription,
 * that it was received in a special blessing from whichever muse;
 * the state of its tuning and damage level; etc.  If you are interest
 * in doing this, I will draw up some descriptions of each type.
 *
 * Hope this is helpful.  /Azireon
 */

    set_long(BS("This beautifully made "+query_name()+" is your chosen "
    + "instrument, and upon it "+holder->query_muse_name()+ " has "
    + "set her blessing. Guard it well, for upon the condition "
    + "of your instrument the success of your songs depends. "
    + "Should the "+query_name()+" be damaged, or lose its perfect tone, "
    + "you may attempt to tune or repair it. If this prove beyond "
    + "your skill, take the "+query_name()+" to the workshop in the guild; "
    + "for a cost any instrument may be repaired by the skilled "
    + "craftsmen therein.\n") +"@@query_damage_desc@@\n");
    switch(query_name())
    {
        case "lute":     /* I would suggest lute. */
            set_damage_desc(LUTE_DAMAGE);
            set_short("handsome Minstrel's lute");
            break;
        case "recorder":     /* I would suggest recorder. */
            set_damage_desc(RECORDER_DAMAGE);
            set_short("beautiful Minstrel's recorder");
            break;
        case "dulcimer":
            set_damage_desc(DULCIMER_DAMAGE);
            set_short("carefully crafted Minstrel's dulcimer");
            break;
        case "harp":
            set_damage_desc(HARP_DAMAGE);
            set_short("exquisite Minstrel's harp");
            break;
	case "shawm":    /* I would suggest shawm. */
	    set_damage_desc(SHAWM_DAMAGE);
            set_short("exquisitely crafted Minstrel's shawm");
            break;
	case "viol":
	    set_damage_desc(VIOL_DAMAGE);
	    set_short("beautiful Minstrel's viol");
	    break;
	case "trumpet":
	    set_damage_desc(TRUMPET_DAMAGE);
	    set_short("handsome Minstrel's trumpet");
	    break;


     /* I would suggest adding other types:  sackbut, cornetto,
      * viol, trumpet,etc.
      */

        default:
            write("Yikes! Weird instrument type: "+query_name()+"\n");
            set_short("Minstrel's instrument");
    }
    
    ("/d/Terel/cedric/guild/tower_roof")->do_arrive(environment(TO()));
}

int
query_damage()
{
    return damage_level;
}

void
set_damage(int i)
{
    damage_level = i;
}

void
add_damage(int i)
{
    damage_level +=i;
    if (damage_level>MAXDAMAGE)
        damage_level = MAXDAMAGE;
    if (damage_level<0)
        damage_level = 0;
}

string
query_auto_load()
{
    return MASTER_OB(TO())+":"+damage_level+"**"+query_name();
}

void
init_arg(string arg)
{   
    string trash,name;
    sscanf(arg, "%s:%d**%s", trash, damage_level, name);
    set_name(name);
    set_damage(damage_level);
    write_file(GUILD+"obj_errors"," name="+query_name()+"; damage_level="+query_damage()+";\n"); 
    write_file(GUILD+"obj_errors","arg="+arg+"; time="+time()+"\n");
}


