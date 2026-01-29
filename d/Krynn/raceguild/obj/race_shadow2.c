/* The shadow of the Krynn race guild */
/* Version 0.01, ~Aridor 12/96        */

/* Navarre August 14th 2011, Adding code to remove any worn head piece before we give them the horns.
 * Previous it was possible to get the horns and keep wearing the helmet when you join.
 */

inherit "/std/guild/guild_race_sh";

#include "../guild.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <login.h>
#include "/std/combat/combat.h"

/* Uncomment this to set the query_race_name of half-elves to half-elf
 * Will also fix the hobbit to kender problem.
*/
#define HALFELF_ALLOWED 1

/* Uncomment this define if you want to mask query_race_name, or comment
 * it if you want to use set_race_name instead.
 */
/*#define USE_QUERY_RACE_NAME 1*/

string gTitle = DEFAULT_TITLE;
string gRegion = DEFAULT_REGION;
string gDracType = "unknown";

varargs public void
add_subloc(string sloc, mixed resp, mixed ids)
{
    if ((gRegion == "half-elf"  || gRegion == "half-human" ||
         gRegion == "kender"    || gRegion == "minotaur"   ||
         gRegion == "hobgoblin" || gRegion == "draconian") &&
         sloc == SUBLOC_MISCEXTRADESC)
      shadow_who->add_subloc(SUBLOC_MISCEXTRADESC, TO);
    else
      shadow_who->add_subloc(sloc, resp, ids);
}

void
setup_things()
{
    int head_ac = 0;

    if (gRegion != "kender")
      shadow_who->add_subloc(KRYNN_RACE_SUBLOC,TO);
    if (gRegion != "draconian")
      shadow_who->add_subloc(KRYNN_RACE_SUBLOC,TO);
  
    shadow_who->add_cmdsoul(KRYNN_RACE_SOUL);
    shadow_who->update_hooks();
    if (gRegion == "half-elf" || gRegion == "half-human" ||
          gRegion == "kender" || gRegion == "hobgoblin" ||
        gRegion == "minotaur")
    {
          shadow_who->remove_subloc(SUBLOC_MISCEXTRADESC);
          shadow_who->add_subloc(SUBLOC_MISCEXTRADESC, TO);
    }
    
    object player = query_shadow_who();

    /* IF THE PLAYER IS A MINOTAUR, ADD SOME NATURAL AC TO HIS HEAD LOCATION. */
    if (player->query_race_name() == "minotaur")
    {

    if (!present("_minotaur_ac_horns_", player))
	{
            object helm = player->query_armour(TS_HEAD);
            if (helm)
            {
                helm->remove_me();
            }
            
	    head_ac = player->query_stat(6) / 2;
	    if (head_ac > 40)
            {
	        head_ac = 40;
	    }
	    if (head_ac < 5)
	    {
	        head_ac = 5;
	    }
	  
	    setuid();
	    seteuid(getuid());
	    object horns = clone_object("/d/Krynn/raceguild/obj/minotaur_horns");
	    horns->set_ac(head_ac);
	    horns->move(player, 1);
	    player->wear_arm(horns);
	}
    }
}

/* Function name: autoload_shadow
 * Description:   Get the saved string from the autoload_shadow string.
 */
void
init_race_shadow(mixed arg)
{
    if (!arg || sscanf(arg,"%s#%s",gTitle,gRegion) != 2)
    {
        gTitle = DEFAULT_TITLE;  
		gRegion = DEFAULT_REGION;
    }

    /* Don't reduce the alarm time, or the miscextra subloc
     * will bug out and change back!!
     */
    set_alarm(1.0,0.0,"setup_things");
    //set_alarm(10.0,0.0,"setup_things");

    if (gRegion == "half-elf" || gRegion == "half-human" ||
        gRegion == "kender"   || gRegion == "hobgoblin"  ||
        gRegion == "minotaur" || gRegion == "draconian")
    {
#ifndef USE_QUERY_RACE_NAME
    shadow_who->set_race_name(gRegion == "half-human" ? "half-elf" : gRegion);
#endif /*USE_QUERY_RACE_NAME*/
    }
}


/* Function name: query_guild_train
 * Description:   Give all the training objects
 */
mixed
query_guild_trainer_race()
{
    if (gRegion == "kender")
    {
        return "/d/Ansalon/guild/kender/room/train_room";
    }
/* 
    if (gRegion == "draconian")
    {
        return "/d/Ansalon/guild/draconian/room/train_room";
    }
*/
    return 0;
}

/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
int
query_guild_tax_race()
{
    if (gRegion == "kender")
    {
        return 2;
    }

    if (gRegion == "minotaur")
    {
        return 1;
    }

    if (gRegion == "draconian")
    {
        return 3;
    }
	
    if (gRegion == "elf" || gRegion == "half-elf" || gRegion == "half-human")
    {
	   return 1;
    }

    return 0;
}

/*
 * Function name: query_guild_style_race
 * Description:  Return the style of the guild
 */
string
query_guild_style_race()
{
    return "race";
}

/*----------------------------- ONLY FOR MINOTAURS ----------------------------*/

/*
 * Function name: wear_arm
 * Description:   wear an armour (This only works on Minotaurs.)
 * Arguments:     The armour to be worn
 * Returns:       string - error message (armour could not be worn)
 *                1 - success (armour was worn)
 */
mixed
wear_arm(object arm)
{
    if (query_shadow_who()->query_race_name() == "minotaur")
    {
      if (!arm->id("_mino_ac_horns") && arm->query_at() & A_HEAD)
      {
          return "The "+arm->short()+ " doesn't fit on your head.\n";
      }
    }
    return query_shadow_who()->wear_arm(arm);
}

/*---------------------------- ONLY FOR ELVES --------------------------------*/

/* Function name: do_glance
 * Description  : This is the routine describing rooms to livings. It will
 *                print the long or short description of the room, the
 *                possible exits, all visible non-living and living objects
 *                in the room (but not this_object() itself) and then it
 *                will print possible attacks going on. Note that this
 *                function performs a write(), so this_player() will get the
 *                descriptions printed to him/her.
 * Arguments    : int brief - if true, write the short-description,
 *                            else write the long-description.
 * Returns      : int 1 - always.
 */
public int
do_glance(int brief)
{
    object env, *livings;
    string one_living_desc, tmp_living_desc, *living_desc;
    int i;

    /* Don't work for non elves or half-elves */
    if (shadow_who->query_race_name() != "elf" &&
	shadow_who->query_race_name() != "half-elf" &&
	shadow_who->query_race_name() != "half-human")
	return shadow_who->do_glance(brief);

    /* Disable for vampires */
    if (shadow_who->query_prop(LIVE_I_UNDEAD))
        return shadow_who->do_glance(brief);

    /* Don't work if the elf can see in the room normally */
    if (CAN_SEE_IN_ROOM(shadow_who))
	return shadow_who->do_glance(brief);

    /* Don't work if the room is too dark */
    if (environment(shadow_who)->query_prop(ROOM_I_LIGHT) < -1)
	return shadow_who->do_glance(brief); 
  
    /* Don't work if the room has magical darkness in it */
    if (environment(shadow_who)->query_prop(OBJ_I_LIGHT) !=
	environment(shadow_who)->query_prop(ROOM_I_LIGHT))
    {
        shadow_who->catch_msg("Your elven vision cannot penetrate the "+
	    "darkness covering the area.\n");
	return shadow_who->do_glance(brief);
    }

    /* Wizard gets to see the filename of the room we enter and a flag if
     * there is WIZINFO in the room.
     */
    env = environment(shadow_who);
    if (shadow_who->query_wiz_level())
    {
        if (stringp(env->query_prop(OBJ_S_WIZINFO)))
        {
            write("Wizinfo ");
        }

        write(file_name(env) + "\n");
    }

    /* Describe the room and its contents. */
    if (shadow_who->query_race_name() == "half-elf")
    {
        if (stringp(env->query_prop(ROOM_S_DARK_LONG)))
	    write(env->query_prop(ROOM_S_DARK_LONG));
	   else
	    write("A dark room.\n");
    }
    else
    {
        write("Your elven vision reveals to you a limited view of the area.\n");
            write(capitalize(env->short()) + ".\n");
            write(env->exits_description());
    }

    livings = FILTER_LIVE(all_inventory(env));
    livings -= ({ shadow_who });

    if (sizeof(livings))
    {
        living_desc = ({ });

        for (i=0;i<sizeof(livings);i++)
	{
	    /* Don't see wizard level insibility or undeads that do not */
	    /* produce heat. Vampires do. :) */
            if ((livings[i]->query_prop(LIVE_I_UNDEAD) &&
 		livings[i]->query_guild_name_occ() != "Vampires of Emerald") ||
		livings[i]->query_prop(OBJ_I_INVIS) >= 100 ||
		livings[i]->query_no_show())
		break;

            switch (livings[i]->query_race_name())
            {
		case "elf":
		    	tmp_living_desc = "an elven figure";
		    	break;
		case "half-elf":
			tmp_living_desc = "a half-elven figure";
			break;
		case "dwarf":
			tmp_living_desc = "a dwarven figure";
			break;
		case "gnome":
			tmp_living_desc = "a gnomish figure";
			break;
		default:
			tmp_living_desc = "a "+livings[i]->query_race_name() +
				" figure";
			break;
	    }

            if (livings[i]->query_attack() == shadow_who)
		tmp_living_desc += " attacking you";
	    else if (livings[i]->query_attack())
		tmp_living_desc += " in combat";

 	    living_desc += ({ tmp_living_desc });
	}

    if (sizeof(living_desc))
    shadow_who->catch_msg("You recognize the heat cast by "+
	COMPOSITE_WORDS(living_desc)+".\n");
    }

    return 1;
}


//--------------------------------------------------------------------


/*
 * Function name: query_guild_name_race
 * Description:  Query the name of the guild
 */
string
query_guild_name_race()
{
    return GUILD_NAME;
}

/*
 * Function name: check_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *                Throws the player out of the guild if not wanted!
 * Arguments:     ob - the player.
 */
void
check_keep_player(object ob)
{
    string dummy;

    /* Check here if the player still has his old race.
     * If not, kick him/her out
     *
     * First, check the half-elves/half-humans
     */
    if (ob->query_race() == "elf" && gRegion == "half-human")
      return;
    if (ob->query_race() == "human" && gRegion == "half-elf")
      return;
    if (ob->query_race() == "hobbit" && gRegion == "kender")
    {
      if (ob->query_alignment() > 0)
        return;
      else
      {
        ob->catch_msg("\n\n\nA Dragonlance Kender is by nature good aligned, " +
            "since you are not, you have been removed.\nFeel free to rejoin " +
            "if you wish to roleplay a kender in the future.\n\n\n\n");
        setuid();
        seteuid(getuid());
        (JOINROOM)->do_leave(ob,1);
        return;
      }
    }
    if (ob->query_race() == "draconian")
      return;
    if (ob->query_race() == "goblin" && gRegion == "hobgoblin")
      return;
    if (ob->query_race() == "goblin" && gRegion == "minotaur")
      return;
    if (ob->query_race() == "human" && gRegion == "minotaur")
      return;
    if(ob->query_race() == "dwarf" && gRegion == "minotaur")
      return;

    if (gRegion != "half-elf" && gRegion != "half-human")
      /* Then, check the rest */
      if (sscanf(L(gRegion),"%s" + ob->query_race() + "%s",dummy,dummy) == 2)
    return;

    /* Doesn't match, kick him/her out of the guild! */
    ob->catch_msg("It seems you have changed race and are not allowed " +
          "in the Krynn race guild with this region any more. " +
          "Please rejoin the guild appropriately if possible.\n");
    setuid();
    seteuid(getuid());
    (JOINROOM)->do_leave(ob,1);
    return 0;
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    if (MASTER_OB(ob) != "/d/Genesis/login/ghost_player")
      set_alarm(2.0,0.0,"check_keep_player",ob);
    return 1;
}


/*
 * Function name: query_guild_not_allow_join_race
 * Description:  Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *  intended guild.
 * Returns:  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_race(object player, string type, string style,
                   string name)
{
    NF("You are already a member of another race guild!\n");
    if (::query_guild_not_allow_join_race(player, type, style, name))
      return 1;

    return 0;
}

/* Function name: query_region_title
 * Description:   give the guild title
 * Arguments:     none
 * Returns:       the guild title
 */
string
query_region_title()
{
    return gRegion;
}

/* Function name: query_family_title
 * Description:   give the guild title
 * Arguments:     none
 * Returns:       the guild title
 */
string
query_family_title()
{
    return gTitle;
}



#ifdef USE_QUERY_RACE_NAME
/* For Half-Elves we need to redefine the following
 * four functions.
 */
#ifdef HALFELF_ALLOWED
string
query_race_name()
{
    /* Safeguard if we die, so that we don't change race all the time */
    if (MASTER_OB(shadow_who) == "/d/Genesis/login/ghost_player")
      return shadow_who->query_race_name();
    if (gRegion == "kender")
      return "kender";
    if (gRegion == "hobgoblin")
      return "hobgoblin";
    if (gRegion == "minotaur")
      return "minotaur";
    if (gRegion == "draconian")
      return "draconian";
    if (gRegion == "half-elf" || gRegion == "half-human")
      return "half-elf";
    return shadow_who->query_race_name();
}
#endif

string *
query_names()
{
    if (gRegion == "half-elf" || gRegion == "half-human")
      return shadow_who->query_names() + ({"half-elf"});
    if (gRegion == "kender")
      return shadow_who->query_names() + ({"kender"});
    if (gRegion == "hobgoblin")
      return shadow_who->query_names() + ({"hobgoblin"});
    if (gRegion == "minotaur")
      return shadow_who->query_names() + ({"minotaur"});
    if (gRegion == "draconian")
      return shadow_who->query_names() + ({"draconian"});
    return shadow_who->query_names();
}

int
id(string str)
{
    if ((gRegion == "half-elf" || gRegion == "half-human") &&
    str == "half-elf")
      return 1;
    if (gRegion == "kender" && str == "kender")
      return 1;
    if (gRegion == "hobgoblin" && str == "hobgoblin")
      return 1;
    if (gRegion == "minotaur" && str == "minotaur")
      return 1;
    if (gRegion == "draconian" && str == "draconian")
      return 1;
    return shadow_who->id(str);
}

string *
parse_command_id_list()
{
    if (gRegion == "half-elf" || gRegion == "half-human")
      return (string*)(shadow_who->parse_command_id_list())
#ifdef HALFELF_ALLOWED
    - ({"elf","human"})
#endif /*HALFELF_ALLOWED*/
      + ({"half-elf"});

    if (gRegion == "hobgoblin")
      return (string*)(shadow_who->parse_command_id_list())
#ifdef HALFELF_ALLOWED
    - ({"goblin"})
#endif /*HALFELF_ALLOWED*/
      + ({"hobgoblin"});

    if (gRegion == "minotaur")
      return (string*)(shadow_who->parse_command_id_list())
#ifdef HALFELF_ALLOWED
    - ({"human"})
#endif /*HALFELF_ALLOWED*/

    if (gRegion == "draconian")
      return (string*)(shadow_who->parse_command_id_list())
#ifdef HALFELF_ALLOWED
    - ({"human"})
#endif /*HALFELF_ALLOWED*/

    if (gRegion == "kender")
      return (string*)(shadow_who->parse_command_id_list())
#ifdef HALFELF_ALLOWED
    - ({"hobbit"})
#endif /*HALFELF_ALLOWED*/
      + ({"kender","halfling"});
    return shadow_who->parse_command_id_list();
}
#endif /*USE_QUERY_RACE_NAME*/



/* Function name: query_guild_title_race
 * Description:   give the guild title
 * Arguments:     none
 * Returns:       the guild title
 */
string
query_guild_title_race()
{
    return query_family_title();
}

/* Function name: query_guild_family_name
 * Description:   returns whether the guild gives a family name or a normal title
 * Returns:       0/1
 */
int
query_guild_family_name()
{
    return 1;
}

/*
 * Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *                the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:       0 if no skill of mine, else the string. "" if skill not shown.
 */
mixed
query_guild_skill_name(int type)
{
    return 0;
}

/*
 * Function name: set_race_title
 * Description:   When a player joins the guild, this command is called to
 *                initialize and set the chosen region and family name.
 * Arguments:     title  - the family name
 *                region - the region the person comes from
 */
void
set_race_title(string title, string region)
{
	string dracTitle;
	string dracType;
	
    if (file_name(previous_object()) != JOINROOM &&
        file_name(previous_object()) != JOINROOM2)
      return;
	
	if (region == "draconian")  
	{
		sscanf(title,"%s %s",dracType, dracTitle);
		gDracType = dracType;
		gTitle = dracTitle;
	}
	else
		gTitle = title;
	
    gRegion = region;

    if (gRegion == "half-elf" || gRegion == "half-human" ||
        gRegion == "kender"   || gRegion == "hobgoblin"  ||
        gRegion == "minotaur" || gRegion == "draconian")
    {
#ifndef USE_QUERY_RACE_NAME
    shadow_who->set_race_name(gRegion == "half-human" ? "half-elf" : gRegion);
#endif /*USE_QUERY_RACE_NAME*/
    }

    set_alarm(1.0,0.0,"setup_things");
}

/*
 * Function name: show_subloc
 * Description:   Override the default subloc for human/elf to show
 *                the half-elf description instead
 * Arguments:     on, for_obj
 * Returns:       the string for the subloc
 */
public string
show_subloc_size(object on, object for_obj)
{
    string race, res;
    int val, rval, *proc;

    race = on->query_race();
    /* This will give problems when the new race is of a different
     * size/shape than the original race. If both are about similar,
     * everything works perfectly. Otherwise, you might want to change
     * the above line to use some race which fits better with the size
     * of the used (half-elf,kender,hobgoblin) race.
     * Alternatively, you can use different values for RACEATTR below.
     */

    if (member_array(race, RACES) >= 0)
    {
        val = on->query_prop(CONT_I_HEIGHT);
        rval = RACEATTR[race][0];
        val = 100 * val / (rval ? rval : val);
        proc = SPREAD_PROC;

        for (rval = 0; rval < sizeof(proc); rval++)
            if (val <= proc[rval])
                break;
        rval = (rval < sizeof(proc) ? rval : sizeof(proc) -1 );

        res = " " + HEIGHTDESC[rval] + " and ";

        val = on->query_prop(CONT_I_WEIGHT) / on->query_prop(CONT_I_HEIGHT);
        rval = RACEATTR[race][5];
        val = 100 * val / (rval ? rval : val);
        proc = SPREAD_PROC;

        for (rval = 0; rval < sizeof(proc); rval++)
            if (val <= proc[rval])
                break;
        rval = (rval < sizeof(proc) ? rval : sizeof(proc) -1 );

    res += WIDTHDESC[rval] + " for ";
    if (gRegion == "kender")
      res += LANG_ADDART("kender");
    else if (gRegion == "hobgoblin")
      res += LANG_ADDART("hobgoblin");
          else if (gRegion == "minotaur")
        res += LANG_ADDART("minotaur");
      else
        res += LANG_ADDART("half-elf");
    res += ".\n";
    }
    else
        res = "";

    return res;
}

public string
show_subloc_misc(object on, object for_obj)
{
    string res, cap_pronoun, cap_pronoun_verb, tmp;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";

    if (for_obj == on)
    {
    res = "You are";
    cap_pronoun_verb = res;
    cap_pronoun = "You are ";
    }
    else
    {
    res = capitalize(on->query_pronoun()) + " is";
    cap_pronoun_verb = res;
    cap_pronoun = capitalize(on->query_pronoun()) + " seems to be ";
    }

    if (strlen(tmp = show_subloc_size(on, for_obj)))
      res += tmp;
    else
      res = "";

    res += MISC_SUBLOC->show_subloc_looks(on, for_obj);

    if (on->query_attack())
      res += cap_pronoun_verb + MISC_SUBLOC->show_subloc_fights(on, for_obj);

    res += cap_pronoun + MISC_SUBLOC->show_subloc_health(on, for_obj) + ".\n";

    return res;
}

/*
 * Function name: show_subloc
 * Description:   Shows the specific sublocation description for a living
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != KRYNN_RACE_SUBLOC)
    {
    if (subloc == SUBLOC_MISCEXTRADESC)
      return show_subloc_misc(on, for_obj);
    else
      return shadow_who->show_subloc(subloc, on, for_obj);
    }

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return shadow_who->show_subloc(subloc, on, for_obj);

    /* This is handled by the kender guild now
    if (gRegion == "kender")
    {
    if (for_obj == on)
      return "You are a kender.\n";
    return C(PRONOUN(on)) + " is a kender from Krynn.\n";
    }*/

    if (gRegion == "hobgoblin")
    {
       if (for_obj == on)
          return "You are a hobgoblin of Krynn.\n";
       return C(PRONOUN(on)) + " looks like a goblin but is too large for " +
           "one and you realize that " + PRONOUN(on) + " is a hobgoblin.\n";
    }

    if (gRegion == "minotaur")
    {
       if (for_obj == on)
          return "You have the long characteristic horns of a proud minotaur "+
                 "from Krynn.\n";
       return C(PRONOUN(on)) + " has the long characteristic horns of a proud "+
               "minotaur from Krynn.\n";
    }

    if (gRegion == "draconian")
    {
       switch (gDracType)
       {
	      case "Kapak":
             if (for_obj == on)
                return "You have the scaled copper coloured skin of a kapak draconian from Krynn.\n";
             return C(PRONOUN(on)) + " has the scaled copper coloured skin of a kapak draconian from Krynn.\n";
			 break;
	      case "Aurak":
             if (for_obj == on)
	            return "You have the scaled gold coloured skin of an aurak draconian from Krynn.\n";
             return C(PRONOUN(on)) + " has the scaled gold coloured skin of an aurak draconian from Krynn.\n";
			 break;
	      case "Bozak":
             if (for_obj == on)
                return "You have the scaled bronze coloured skin of a bozak draconian from Krynn.\n";
             return C(PRONOUN(on)) + " has the scaled bronze coloured skin of a bozak draconian from Krynn.\n";
			 break;
	      case "Sivak":
             if (for_obj == on)
                return "You have the scaled silver coloured skin of a sivak draconian from Krynn.\n";
             return C(PRONOUN(on)) + " has the scaled silver coloured skin of a sivak draconian from Krynn.\n";
			 break;
	   }
    }
	
    if (gRegion == "half-elf" || gRegion == "half-human")
    {
    if (for_obj == on)
      return "You have the delicate features and pointed ears common "+
        "to half-elves.\n";

    if (for_obj->query_race_name() == "elf")
      return "You notice that "+POSSESSIVE(on)+" features are more "+
        "crude than those of the elves and realize that "+
          PRONOUN(on)+" is a half-elf.\n";

    if (for_obj->query_race_name() == "human")
      return "You notice "+PRONOUN(on)+" has slightly pointed "+
        "ears and delicate features, which hint at elven blood.\n";

    return "You realize, judging from "+POSSESSIVE(on)+" mixed "+
      "features, that "+PRONOUN(on)+" is a half-elf.\n";
    }

    /* Obviously, we need a special description for each region/race here!
    if (on->query_race() == "dwarf")
    {
    if (for_obj == on)
      return "You wear your long braided beard proudly, indicating your " +
        "heritage as " + LANG_ADDART(C(gRegion)) + " from Krynn.\n";

    return C(PRONOUN(on)) + " has a long braided beard, indicating " + HIS(on) +
      " heritage as " + LANG_ADDART(C(gRegion)) + " from Krynn.\n";
      }*/

    /* These were the specialized descriptions, all the rest will get the
     * generic text */
    if (for_obj == on)
      return "You are " +  LANG_ADDART(C(gRegion)) + " from Krynn.\n";

    return C(PRONOUN(on)) + " seems to be " + LANG_ADDART(C(gRegion)) +
      " from Krynn.\n";
}



