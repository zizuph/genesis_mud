#pragma save_binary

inherit "/std/object.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

#define INS_SUBLOC "_instrument_subloc"
#define VOICE_SUBLOC "_voice_subloc"

#ifdef TEMP_SAY_VERB_HACK

#define VERBARRAY\
({  ({"admit","say","murmur","mutter","conceed","enunciate","convey",\
            "mention","imply","claim","utter","think"}),\
      ({"giggle","laugh","snicker","chuckle","snort","chatter","babble",\
            "jabber"}),\
      ({"declare","announce","proclaim","cry","exclaim","insists"}),\
      ({"say","convey","suggest","mention","admit","confess","conceed",\
            "suggest","delineate","answer","reply","aquiesce","agree",\
            "explain","hint","imply","chatter","claim","think","observe"}),\
      ({"sigh","murmur","mutter","mumble","confess","whine","sniff",\
            "wail","lament","moan","groan","sob","plead"}),\
      ({"snarl","growl","insinuate","imply","snort","snap","yell",\
            "exclaim","bark","bellow","roar","shriek"}),\
      ({"chant","intone","sing","trill","croon","carol","warble",\
            "howl","incant","ululate","burst into song"}),\
      ({"sneer","smirk","snort","retort","snicker","grin","snap","laugh",\
	    "chuckle","scoff"}),\
      ({"say","say"}),\
      ({"breath","coo","whisper","smile"}),\
      ({"whisper","breath","murmur","insinuate","hint","whisper"}),\
      ({"stutter","whine","moan","complain","sob","plead","snivel","pout"}),\
      ({"twitter","jabber","coo","sigh","mention","laugh"}),\
      ({"observe","note","explain","indicate","mention","remark"}),\
      ({"utter","blurt","snap","delineate","say","retort"}),\
      ({"decree","delineate","claim","remark","sneeer","announce"}) \
 })

#define ASKARRAY ({"ask", "query", "ponder", "wonder", "inquire"})
#define EXCLAIMARRAY ({"declare","announce","cry","exclaim","yell",\
      "bellow","roar","shriek","howl"})

#endif

#define MAXDAMAGE 10
#define TUNEDAMAGE      ({"is well tuned and in perfect repair",        \
      "seems slightly out of tune",                   \
      "sounds somewhat off-pitch",                    \
      "sounds out of tune",                           \
      "requires a thorough tuning",                   \
      "is painfully out of tune"})



/*
* CEDRIC:  I have started on these damage-arrays and some other
* things. As you can see, I've added or changed some instrument types
* as possible suggestions. Basically, you had a collection of
* predominantly string instruments and I have sugested offering
* more varied types. First, the mandolin is a fairly recently
* developed instrument, probably from the 16th or 17th century.
* However, the lute is basically the same but is much older and
* was the major instrument of the European Renaissance. Second,
* I would suggest recorder instead of flute (the modern flute was
* developed only in the 18th century and the recorder was a very
* popular medieval instrument). The dulcimer adds to diversity 
* because it is hammered instead of plucked. Harp also is an ancient
* instrument so I would keep it. The lyre is quite similar so I
* would suggest using another type.
*
* I suggest adding the following possible types. The viol, a bowed
* string instrument much like today's violin, except played with the
* base resting on one's leg. The shawm, a loud double-reed like the
* oboe, very popular in late medieval music. (You could also have
* the bombard, a low shawm, somewhat similar to the bassoon.)  You
* would probably also want some brass-type instruments:  a non-valved,
* straight trumpet;  the sackbut, or medieval trombone; cornetto, a
* high-pitched, conical brass instrument. I have tried to include
* some arrays for each of the basic types.
*/

void do_things();

int     damage_level = 0;
string  *damage_desc;

void
init()
{
   ::init();

   add_action("do_inspect", "inspect");
#ifdef TEMP_SAY_VERB_HACK
    add_action("do_communicate", "say");
    add_action("do_communicate", "'", 1);
#endif
}

void
create_object()
{
   
   if (IS_CLONE) 
       set_alarm(4.0, 0.0, do_things);
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

public string
show_instrument_subloc(object carrier, object for_obj)
{
    return "";
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    string *indexes;
    int i;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

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
	    return show_instrument_subloc(carrier, for_obj);
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
   
   add_name("minstrel_instrument");

   if (living(holder))
   {
       holder->add_cmdsoul(GUILDSOUL);
       holder->update_hooks();
       holder->add_subloc(INS_SUBLOC, TO());
       holder->add_subloc(VOICE_SUBLOC, TO());
       if (sizeof(get_dir(BANISHDIR+holder->query_real_name()+"_banished")))
       {
	   holder->banish_me();
       }

   }

   ("/d/Terel/cedric/guild/tower_roof")->do_arrive(environment(TO()));
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
            + "set her blessing. Guard it well, for upon the condition "
            + "of your instrument the success of your songs depends. "
            + "Should the "+query_name()+" be damaged, or lose its perfect tone, "
            + "you may attempt to tune or repair it. If this prove beyond "
            + "your skill, take the "+query_name()+" to the workshop in the guild; "
            + "for a cost any instrument may be repaired by the skilled "
            + "craftsmen therein.\n")+check_call("@@query_damage_desc@@\n"));
      say(QCTNAME(TP())+" carefully inspects "+TP()->query_possessive()+" "
	  + query_name()+" for damage.\n");
      return 1;
   }
   notify_fail("Inspect what?\n");
   return 0;
}

#ifdef TEMP_SAY_VERB_HACK

public string
public_sound(string str, object target)
{
   string *arr;
   
   if (!interactive(target))
      return "says";
   
   arr=explode(str, "");
   if (arr[sizeof(arr)-1]=="s")
      {
      str=str+"es";
      return str;
   }
   switch (str)
   {
      case "reply":return "replies";
      case "query":return "queries";
      case "imply":return "implies";
      case "cry":return "cries";
      case "breath":return "breathes";
      case "burst into song":return "bursts into song";
   }
   str=str+"s";
   return str;
}

int
do_communicate(string str) /* Must have it here for special with ' */
{
   string  verb, *the_array;
   object  *plist;
   int    index, i;
   
   verb = query_verb();
   if (str == 0)
      str = "";
   if (strlen(verb) && verb[0] == "'"[0])
      if (strlen(str))
      str = extract(verb, 1) + " " + str;
   else
      str = extract(verb, 1);
   
   switch (extract(str, strlen(str)-1))
   {
      case "?":
      the_array = ASKARRAY;
      break;
      case "!":
      the_array = EXCLAIMARRAY;
      break;
      default: 
      if (this_player()->query_mood()==RANDOM)
         the_array = VERBARRAY[random(sizeof(VERBARRAY))];
      else
         the_array = VERBARRAY[this_player()->query_mood()-1];
   }
   plist = all_inventory(environment(TP())) + ({environment(TP())});
   index = random(sizeof(the_array));
   say(QCTNAME(environment(TO()))+" "
   +public_sound(the_array[index], plist[i])
   +": "+str+"\n",TP());
   
   if (this_player()->query_get_echo())
      write("You "+the_array[index]+": " + str + "\n");
   else
      write("Ok.\n");
   
   return 1;
}
#endif

public string
query_instrument_auto_load()
{
    return "";
}

string
query_auto_load()
{
    return MASTER + ":" + damage_level + "##" + query_instrument_auto_load();
}

public void
instrument_init_arg(string arg)
{
}

void
init_arg(string arg)
{   
   string inst_init = "";

   /* Get rid of the obsolete m_shadow */
   this_player()->remove_autoshadow("/d/Terel/cedric/guild/obj/m_shadow");

   sscanf(arg, "%d##%s", damage_level, inst_init);

   set_damage(damage_level);

   instrument_init_arg(inst_init);
}
