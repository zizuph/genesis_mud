#pragma save_binary

inherit "/std/object.c";
#include <macros.h>
#include <language.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "../guild_defs.h"

#define INS_SUBLOC "_instrument_subloc"
#define VOICE_SUBLOC "_voice_subloc"

#define MAXDAMAGE 10
#define TUNEDAMAGE      ({"is well tuned and in perfect repair",        \
      "seems slightly out of tune",                   \
      "sounds somewhat off-pitch",                    \
      "sounds out of tune",                           \
      "requires a thorough tuning",                   \
      "is painfully out of tune"})

#define LUTE_DAMAGE TUNEDAMAGE +\
({"has a broken string",                        \
      "has lost a tuning-peg",                        \
      "has a warped fret-board",                      \
      "has a fractured bridge",                       \
      "has a large crack in its sounding-case"})
#define LUTE_FIX ({"lute_string",\
      "lute_tuning_peg",\
      "lute_fret_board",\
      "lute_bridge",\
      "lute_big"})

#define RECORDER_DAMAGE TUNEDAMAGE +\
({"is moldy and needs a good cleaning",         \
      "has a cracked mouth-piece",                    \
      "is badly warped by the humidity",              \
      "is missing its bottom section",                \
      "has a large crack between finger-holes"})
#define RECORDER_FIX ({"recorder_mouldy",\
      "recorder_mouth_piece",\
      "recorder_warped",\
      "recorder_broken",\
      "recorder_big"})

#define DULCIMER_DAMAGE TUNEDAMAGE +\
({"has a broken string",                        \
      "is without one of its hammers",                \
      "has lost several tuning-pegs",                 \
      "has a warped bridge",                          \
      "is broken completely in half"})
#define DULCIMER_FIX ({"dulcimer_string",\
      "dulcimer_hammer",\
      "dulcimer_tuning_peg",\
      "dulcimer_bridge",\
      "dulcimer_big"})

#define HARP_DAMAGE TUNEDAMAGE +\
({"has a handful of missing strings",           \
      "has a cracked forepillar",                     \
      "has a severely warped neck",                   \
      "has a crushed resonator",                      \
      "is broken completely in half"})
#define HARP_FIX ({"harp_strings",\
      "harp_forepillar",\
      "harp_neck",\
      "harp_resonator",\
      "harp_big"})

#define SHAWM_DAMAGE TUNEDAMAGE +\
({"has a dried-out and cracked reed",           \
      "has no mouthpiece",                            \
      "has some rusty and immobile keys",              \
      "has sustained heavy water damage",              \
      "has a shattered bell"})
#define SHAWM_FIX ({"shawm_reed",\
      "shawm_mouthpiece",\
      "shawm_keys",\
      "shawm_water_damage",\
      "shawm_big"})

#define VIOL_DAMAGE TUNEDAMAGE +\
({"is missing an A-string",                     \
      "has a loose and warped bow",                   \
      "has a splintered and collapsed bridge",        \
      "has lost all its tuning-pegs",                 \
      "has its fingerboard completely cracked off"})
#define VIOL_FIX ({"viol_string",\
      "viol_bow", \
      "viol_bridge",\
      "viol_tuning_pegs",\
      "viol_big"})

#define TRUMPET_DAMAGE TUNEDAMAGE +\
({"is blocked up and needs to be cleaned",      \
      "is badly rusted",                              \
      "needs a mouthpiece",                           \
      "has been severely dented",                     \
      "has been pounded almost completely flat"})
#define TRUMPET_FIX ({"trumpet_blocked",\
      "trumpet_rusty",\
      "trumpet_mouthpiece",\
      "trumpet_dented",\
      "trumpet_big"})

void do_things();

int     damage_level = 0;
string  *damage_desc;

void
init()
{
   ::init();
   add_action("do_inspect", "inspect");
}

void
create_object()
{
   
   if (IS_CLONE) 
       set_alarm(4.0, 0.0, do_things);
}

public int
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
   // DEBUG("Instrument damage pre increase by " +i+ ": " +damage_level);
   damage_level +=i;
   if (damage_level>MAXDAMAGE)
      damage_level = MAXDAMAGE;
   if (damage_level<0)
      damage_level = 0;

   // DEBUG("Instrument damage post: " +damage_level+ ", " + damage_desc[query_damage()]);
}

void
set_damage_desc(string *the_arr)
{
   damage_desc = the_arr;
}

string
query_damage_desc()
{
   return "The " + query_name() + " " + damage_desc[query_damage()] + ".";
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    string *indexes;
    int i;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    string reputation = PERFORM_MANAGER->query_reputation_level_desc(carrier);

    switch(subloc)
    {
	case VOICE_SUBLOC:
	if (for_obj == carrier)
	{
	    return "Your "+carrier->query_race_adj()+" voice is "
		+ (carrier->query_prop(MINSTREL_I_VOICE_TRAINING)
		   ? "trained to a " :"a natural ")
		+ carrier->query_voice_adj() + ".\n";
	}
	else
	{
	    return capitalize(carrier->query_possessive()) + " Minstrel's "
		+ "voice is a "
		+ (carrier->query_prop(MINSTREL_I_VOICE_TRAINING)
		   ? "highly trained " :"natural ")
		+ carrier->query_voice_adj()+".\n";
	}
	break;
	case INS_SUBLOC:
	if (for_obj == carrier)
	{
	    switch(query_name())
	    {
		case "lute":
		str = "Your Minstrel's lute is alive with music and "
		    + "dedicated to "+ TP()->query_muse_name() + ".\n";
		break;
		case "shawm":
		str = "Your Minstrel's shawm is alive with music and "
		    + "dedicated to "+ TP()->query_muse_name() + ".\n";
		break;
		case "viol":
		str = "Your Minstrel's viol is alive with music and "
		     + "dedicated to "+ TP()->query_muse_name() + ".\n";
		break;
		case "trumpet":
		str = "Your Minstrel's trumpet is alive with music and "
		    + "dedicated to " + TP()->query_muse_name() + ".\n";
		break;
		case "recorder":
		str = "Your Minstrel's recorder is alive with music and "
		    + "dedicated to " + TP()->query_muse_name() + ".\n";
		break;
		case "harp":
		str = "Your Minstrel's harp is alive with music and dedicated "
		    + "to " + TP()->query_muse_name() + ".\n";
		break;
		case "dulcimer":
		str = "Your Minstrel's dulcimer is alive with music and "
		    + "dedicated to " + TP()->query_muse_name() + ".\n";
		break;	    
	    }

            str += "You are " + LANG_ART(reputation) + " " + reputation + 
                " performer of the realms.\n";
	}
	else
	{
	    switch(query_name())
	    {
		case "lute":
		str = capitalize(carrier->query_pronoun()) + " proudly carries"
		    + " a Minstrel's lute.\n";
		break;
		case "shawm":
		str = capitalize(carrier->query_pronoun()) + " proudly carries"
		    + " a Minstrel's shawm.\n";
		break;
		case "viol":
		str = capitalize(carrier->query_pronoun()) + " proudly carries"
		    + " a Minstrel's viol.\n";
		break;
		case "trumpet":
		str = capitalize(carrier->query_pronoun()) + " proudly carries"
		    + " a Minstrel's trumpet.\n";
		break;
		case "recorder":
		str = capitalize(carrier->query_pronoun()) + " proudly carries"
		    + " a Minstrel's recorder.\n";
		break;
		case "harp":
		str = capitalize(carrier->query_pronoun()) + " proudly carries"
		    + " a Minstrel's harp.\n";
		break;
		case "dulcimer":
		str = capitalize(carrier->query_pronoun()) + " proudly carries"
		    + " a Minstrel's dulcimer.\n";
		break;
	    }

            str += capitalize(carrier->query_pronoun()) + " is " + 
                LANG_ART(reputation) + " " + reputation + " performer of " +
                "the realms.\n";
	}

	return str;
	break;
	
	default:
	return TP()->show_subloc(subloc, carrier, for_obj);
    }
    return str;
}

void do_things()
{
   object holder;
   
   add_prop(OBJ_M_NO_DROP, "Drop your sacred "
      +TO()->query_name()+"? You must be joking!\n");
   
   holder = environment(TO());
   seteuid(getuid(TO()));
   if (!MEMBER(holder))
      {
      holder->catch_msg(BS("The "+short()+" slips from your grasp. "
            + "As you stand and watch, dumbfounded, it becomes translucent and "
            + "gradually vanishes altogether.\n"));
      remove_object();
   }
   
   /*
   * About the long_desc for the instruments:  it might be nice to
   * include more description of the instrument itself when the player
   * examines it. Medieval/Renaissance instruments were often as
   * elaborate and exotic as their strange names, sometimes covered
   * with intricate engravings, mosaics and inscriptions. For example,
   * the head part of the lute, above the tuning-pegs, was sometimes
   * carved into the shape of a person's head--in this case, perhaps
   * the player's likeness, or that of his muse or something. Each
   * description could be personalized without a great deal of trouble.
   * The information which you have presently in the long_desc could
   * perhaps be provided to the player under a separate command par-
   * ticular to the object, "inspect" for example. This would give
   * him the history of the instrument, perhaps in a small inscription,
   * that it was received in a special blessing from whichever muse;
   * the state of its tuning and damage level; etc. If you are interest
   * in doing this, I will draw up some descriptions of each type.
   *
   * Hope this is helpful. /Azireon
   */
   
   switch(query_name())
   {
      case "lute":
      set_damage_desc(LUTE_DAMAGE);
      set_short("handsome Minstrel's lute");
      set_long(BS(
            "The pear-shaped body of this beautiful lute has " +
            "been crafted from striped ribs of yew wood. " +
            "From the balsam wood bridge up the fretted neck " +
            "six strings have been tightly stretched, the lower " +
            "five in double courses. On each tuning-peg holding " +
            "the strings, a tiny marble cameo has been carved, " +
            "depicting " +holder->query_muse_name()+
            ", the muse to whom this instrument was dedicated. " +
            "A circular hole in the lute's body, beneath the " +
            "strings, allows the instrument to resonate " +
            "strongly. You may inspect your lute to assess its " +
            "state of tuning and general repair.\n"));
      break;
      
      case "recorder":
      set_damage_desc(RECORDER_DAMAGE);
      set_short("beautiful Minstrel's recorder");
      set_long(BS(
            "Fashioned from a deep red cherry wood, this recorder " +
            "is actually three sections fitted together: a flat, " +
            "lateral mouthpiece; a long middle piece with eight " +
            "fingerholes; and a small bell-shaped piece on the " +
            "end. A twirling vine of ivy has been carved into the " +
            "wood, running up and down the instrument's length, " +
            "curling at last around a florid inscription: the name " +
            "of your muse, " +holder->query_muse_name()+ ". " +
            "You may inspect your recorder to assess its state of " +
            "tuning and general repair.\n"));
      break;
      
      case "dulcimer":
      set_damage_desc(DULCIMER_DAMAGE);
      set_short("carefully crafted Minstrel's dulcimer");
      set_long(BS(
            "This beautiful dulcimer has been crafted from a " +
            "large, trapezoidally shaped piece of white ash wood. " +
            "Two octaves of silvery strings, in double courses, " +
            "are suspended across the width of " +
            "the instrument. These strings weave intricately over " +
            "two central bridges at different lengths to produce " +
            "different pitches. Between the two central bridges " +
            "a silhouette has been painted, an image of " +
            holder->query_muse_name()+ ", the Muse to whom this " +
            "dulcimer was dedicated. Two hammers are kept in a " +
            "small compartment on the dulcimer's back. You may " +
            "inspect your " +
            "dulcimer to assess its state of tuning and general " +
            "repair.\n"));
      break;
      
      case "harp":
      set_damage_desc(HARP_DAMAGE);
      set_short("exquisite Minstrel's harp");
      set_long(BS(
            "This harp, made of a dark brown and fragrant spruce " +
            "wood, measures two and a half feet and is meant to be " +
            "pressed against the chest or rested in the lap. A " +
            "broad resonator supports a sounding board from which " +
            "29 strings, tuned diatonically, stretch up to the " +
            "neck, gently curving like a swan's. A narrow " +
            "forepillar reaches from the resonator's base to the " +
            "neck, forming a basic triangle. Above the point at " +
            "which the neck and forepillar meet, a carved and " +
            "painted head, depicting " +holder->query_muse_name()+
            ", your muse, has been placed. You may inspect your " +
            "harp to determine its state of tuning and general " +
            "repair.\n"));
      break;
      
      case "shawm":
      set_damage_desc(SHAWM_DAMAGE);
      set_short("beautiful Minstrel's shawm");
      set_long(BS(
            "This shawm is a long conical bore that flares out " +
            "into a two-inch bell. Made of stained walnut wood, it "+
            "may be disassembled into three basic parts: a small " +
            "mouthpiece with double-reed and pirouette, a long " +
            "section with drilled fingerholes, and the bell. " +
            "Three of the lower fingerholes are covered with pads; "+
            "keys maneuver the pads, making the shawm easier to " +
            "play. This is an alto shawm and its range is low, " +
            "rich, and melancholy. Around the circumference of " +
            "the bell, intertwined with a lily flower, is " +
            "the floridly engraved name of your muse, " +
            holder->query_muse_name()+ ". You may inspect your " +
            "shawm to assess its state of tuning and general " +
            "repair.\n"));
      break;
      
      case "viol":
      set_damage_desc(VIOL_DAMAGE);
      set_short("fine Minstrel's viol");
      set_long(BS(
            "This dark spruce-wood instrument is roughly two " +
            "feet in length. The sounding-box has a flat back " +
            "and rounded shoulders which curve inward and then " +
            "out again to round off at the bottom. Six strings, " +
            "tuned in fourths and thirds, stretch over the bridge, "+
            "up a fretted fingerboard, and are held by tuning-pegs "+
            "at the top of the neck. A bow, held with palm " +
            "upward, is drawn across the strings to produce sound." +
            "  While playing the viol, the instrument may be rested "+
            "on the knee or pressed against the arm and shoulder." +
            "  Twin fresco-like paintings, depicting " +
            holder->query_muse_name()+ ", your Muse, adorn the " +
            "sounding-box, beneath resonating C-shaped holes. " +
            "You may inspect your viol to assess its state of " +
            "tuning and general repair.\n"));
      break;
      
      case "trumpet":
      set_damage_desc(TRUMPET_DAMAGE);
      set_short("shiny Minstrel's trumpet");
      set_long(BS(
            "This long and slender trumpet has been fashioned " +
            "out of brass that shines with golden lustre. A silver "+
            "alloy mouthpiece may be detached from the smaller " +
            "end. From the mouthpiece, the bore of the trumpet " +
            "gradually increases in diameter, bending back around " +
            "itself only once and then flaring out into a bell. " +
            "Although the trumpet has no valves or keys, the " +
            "various pitches of the harmonic series may be " +
            "produced by manipulating the shape of the ombouchure " +
            "and pressure of air blown through the mouthpiece. " +
            "This trumpet has been tuned to the fundamental pitch " +
            "of D. The name of your Muse, " +holder->query_muse_name()+
            ", has been inscribed in elaborate silver runes along " +
            "the final section of the instrument. You may inspect " +
            "your trumpet to assess its state of tuning and " +
            "general repair.\n"));
      break;
      
      default:
      holder->catch_msg("Yikes! Weird instrument type: "+query_name()+"\n");
      set_short("Minstrel's instrument");
      break;
   }
   add_name("minstrel_instrument");


   if (living(holder))
   {
       holder->add_subloc(INS_SUBLOC, TO());
       holder->add_subloc(VOICE_SUBLOC, TO());
   }

   ("/d/Terel/cedric/guild/tower_roof")->do_arrive(environment(TO()));
}

string
query_auto_load()
{
   return MASTER_OB(TO())+":"+damage_level+"**"+query_name();
}

void
init_arg(string arg)
{   
   string name;

   /* Get rid of the obsolete m_shadow */
   TP()->remove_autoshadow("/d/Terel/cedric/guild/obj/m_shadow");
   setuid();seteuid(getuid());
   sscanf(arg, "%d**%s", damage_level, name);
   set_name(name);
   set_damage(damage_level);
}

int
do_inspect(string str)
{
   object ob;
   
   if (!str) return 0;
   if (parse_command(str, TP(), "%o", ob) && ob == TO())
      {
      TP()->catch_msg(BS("This beautifully made "+query_name()+" is your chosen "
            + "instrument, and upon it "+TP()->query_muse_name()+ " has "
            + "set her blessing. "
            + "Should the "+query_name()+" be damaged, or lose its perfect tone, "
            + "you may attempt to tune or repair it. If this prove beyond "
            + "your skill, take the "+query_name()+" to the workshop in the guild "
            + ".\n")+check_call("@@query_damage_desc@@\n"));
      say(QCTNAME(TP())+" carefully inspects "+TP()->query_possessive()+" "
	  + query_name()+" for damage.\n");
      return 1;
   }
   notify_fail("Inspect what?\n");
   return 0;
}
