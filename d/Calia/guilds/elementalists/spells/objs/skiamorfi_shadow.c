/*
 *   Skiamorfi Shadow based off of Igneous' Disguise Shadow   
 *
 *   This shadow is used to disguise a players met/nonmet description
 *
 *   Copyright (C) Chad Richardson July 1996
 *
 *   Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Modifications by Bishop, April 2004.
 *
 * Navarre December 2006:
 *   - Changed the evade code to no longer
 *     evade special attacks and spells.
 *     Also changed to take number of enemies into
 *     account, so when you are fighting one enemy and evade
 *     X % of the incoming hits, you should only evade
 *     X/2 % of the incoming hits when you are fighting two 
 *     enemies, otherwise you get double the combat aid.
 *
 * Jaacar February 2017:
 *   - Changed to new standard spell system.
 * 
 * Zizuph July 2022:
 *   - Show limited sublocs through (teleport status)
 */

#pragma save_binary
#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "shadow_base_sh";

#include <macros.h>
#include <living_desc.h>
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#define SW   shadow_who
#define ALLOWED_SUBLOCS    ({ "teleport_timer" })

//    Prototypes
private mixed query_list(mixed list, int arg);

//   Global Vars
private string *Intro_list = ({});
int Block_prop = 0;
int skiamorfi_level = 1;
string Adj1 = "large", Adj2 = "ghostly";
string primary_element = "life";
string elem_form = "presence";
string elem_sound = "whispers in an eerie voice";
string elem_descrip = "shadows and mist";

string me_desc = "You are cloaked in shifting shadows. Your identity is "+
                 "concealed to all onlookers unless you choose to introduce "+
                 "yourself to them again. All of your possessions are "+
                 "concealed from sight by the shadowy " + elem_form +
                 " you have become.";

string other_desc1 = "This strange " + elem_form + " is cloaked in shifting "+
                     "shadows. The shadows contract and expand eerily as "+
                     "the being moves, but in spite of its forbidding "+
                     "exterior, you do not feel threatened by it. Its "+
                     "shape is only vaguely humanoid, but you get a sense " +
                     "that it is ";

string other_desc2 = "Your breath catches as you take in the haunting beauty" +
		             " of this radiant " + elem_form + ". It moves languidly "+
		             "and with purpose, and though clearly not of this "+
		             "world, it does not strike you as ominous or menacing. "+
		             "Instead, you find it comforting to look at and be "+
		             "near. Its shape is only vaguely humanoid, but you get "+
		             "a sense that it is ";           

string other_desc3 = "This mesmerizing " + elem_form + " has been touched "+
                     "by the divine. It appears forged  from light and "+
                     "shadow equally, casting a glow upon its surroundings "+
                     "that makes them seem greater and more alive. From the "+
		             "serene manner of its movements, to the sheer majesty "+
		             "of its presence, everything about this being suggests "+
		             "that it possesses the wisdom of the ages. Its shape is "+
		             "only vaguely humanoid, but you get a sense that it is ";

/*
 * Function name :  remove_disguise_shadow
 * Description   :  remove this shadow from a player.
 */
void remove_disguise_shadow()
{
	remove_shadow();
}

/*
 * Function name :  remove_shadow
 * Description   :  Removes all the props we added to the player
 *                  and removes the shadow
 */
void
remove_shadow()
{
    destruct();
}

/*
 * Function name :  set_disguise
 * Arguments     :  *string vars,  an array of vars we need to have to make
 *                  this disguise.
 * Description   :  Does what is says... sets up the disguise.
 */
void
set_disguise(string *vars)
{
    //  Can't fool ourselves
    Intro_list = ({SW->query_real_name()});

    Adj1 = vars[0];
    Adj2 = vars[1];
    primary_element = GUILD_MANAGER->query_primary_element(SW);
    switch (primary_element)
    {
    	case "fire":
    		elem_form = "efreet";
    		elem_sound = "bellows in a loud voice";
	        elem_descrip = "flames and smoke";    		
    		me_desc = "You are cloaked in flames. Your identity is concealed "+
    		    "to "+
		        "all onlookers unless you choose to introduce yourself to "+
		        "them again. All of your possessions are concealed from "+
		        "sight by the fiery " + elem_form + " you have become.";
		    other_desc1 = "This "+Adj1+" "+elem_form+" is enveloped in "+
		        Adj1 + " embers of flame. Eerily the glow of the flames "+
		        "seem to illuminate the surroundings yet not at the same "+
		        "time as if the flickering " + elem_form + " is both here "+
		        "and not. With every graceful move the flames flicker. Its "+
       		    Adj1 + " exterior is"+
       		    " only vaguely humanoid, but you get a sense that it is ";
            other_desc2 = "Here stands a " + Adj1 + " " + elem_form + 
                " covered in flickers of flame. The " + elem_form + 
                " stands firm as the strands of fire expand and contract "+
                "illuminating the surroundings with flames that cast no "+
                "apparent light. Blanketed in fire the " + Adj1 + " " +
                elem_form+" is only vaguely humanoid, but you get a " +
	            "sense that it is ";
	        other_desc3 = "Before you stands a " + Adj1 + " " +
	            elem_form + " fully ablaze by flame eternal. The " +
	            Adj1 + " " + elem_form + " is wholly encompassed "+
	            "by flames yet the cast of light does not illuminate "+
	            "the surroundings, as if the flames are of an "+
	            "otherworldly nature. From eyes like smouldering embers of "+
	            "wrath to a form radiating furiating heat this being is "+
	            "elemental flame incarnate. The " + Adj1 + " " + 
	            elem_form + " is vaguely humanoid, but you get a sense "+
	            "that it is ";
    		break;
    	case "air":
    		elem_form = "wisp";
    		elem_sound = "whispers in a quiet voice";
	        elem_descrip = "air and fog";    		
    		me_desc = "You are cloaked in clouds. Your identity is concealed "+
    		    "to all onlookers unless you choose to introduce yourself to "+
		        "them again. All of your possessions are concealed from "+
		        "sight by the cloudy " + elem_form + " you have become.";
		    other_desc1 = "This " + Adj1 + " " + elem_form + " seems to be "+
		        "in a shifting state of solidity and wind with cloudy "+
		        "sprouts of gaseous strands twirling about in a constant "+
		        "traverse across its form. Its shape is only "+
		        "vaguely humanoid, but you get a sense that it is ";
            other_desc2 = "This " + Adj1 + " " + elem_form + " is covered "+
                "in misty trails of wind and with every move it forms "+
                "bursts of winds that radiate a solemmn cold to its "+
                "whereabouts. It is composed of the moving winds of "+
                "creation that you are not always certain, but you "+
                "realize its " + Adj1 + " shape is vaguely humanoid and "+
                "you surmise it to be ";
	        other_desc3 = "Chaotic and howling winds envelop this " + Adj1 +
	            " " + elem_form + " before you. Its every move and pose "+
	            "causes freezing winds to exert themselves on the "+
	            "surroundings. With magnificent poise and stalwart resolve "+
	            "this being of pure elemental wind stands at a constant "+
	            "ready. A voice like the gales and a gaze of storms "+
	            "this " + Adj1 + " " + elem_form + " is only vaguely "+
	            "humanoid and you speculate it to be ";
    		break;
    	case "water":
    		elem_form = "tempest";
    		elem_sound = "reverberates in an echoey voice";
	        elem_descrip = "water and mist";    		
    		me_desc = "You are cloaked in water. Your identity is concealed "+
    		    "to all onlookers unless you choose to introduce yourself to "+
		        "them again. All of your possessions are concealed from "+
		        "sight by the watery " + elem_form + " you have become.";
		    other_desc1 = "Here you see a watery " + Adj1 + " " + elem_form +
		        ". This is an entity embodied wholly by evermoving water and "+
		        "its bluish and translucent hues shift with its fluid and "+
		        "graceful movements. Studying the humanoid-like form you "+
		        "speculate it is a ";
            other_desc2 = "A watery " + Adj1 + " " + elem_form + " stands "+
                "before you. This " + elem_form + " is pure water and you "+
                "see bluish and white shimmers all about as small waves "+
                "constantly traverse its surface, reflecting a scintilating "+
                "pattern of the surrounding ambience. Its every move is "+
                "composed equally of smooth grace and surging menace. Its "+
                Adj1 + " shape is only vaguely humanoid, but you get a "+
                "sense that it is ";
	        other_desc3 = "This watery " + Adj1 + " " + elem_form + " moves "+
	            "about with a sinuous fluid grace that suggests a nature "+
	            "beyond this world. Firm and insolid at the same time, this "+
	            "being is composed of water alone and it radiates a solemn "+
	            "resolve and a patience of the fathoms deep. You sense "+
	            "rushing storms and tidal waves that shook the first dawn "+
	            "when looking at this creature. Its " + Adj1 + " shape is "+
	            "only vaguely humanoid, but you get the sense that it is ";
    		break;
    	case "earth":
    		elem_form = "golem";
    		elem_sound = "booms in a piercing voice";
	        elem_descrip = "stone and dust";    		
    		me_desc = "You are cloaked in rocks. Your identity is concealed "+
    		    "to all onlookers unless you choose to introduce yourself to "+
		        "them again. All of your possessions are concealed from "+
		        "sight by the rocky " + elem_form + " you have become.";
		    other_desc1 = "This strange " + Adj1 + " " + elem_form + " is "+
		        "covered in rocks of various sizes, from the tiniest of "+
		        "pebbles to boulders half a metre across. The rocks shift "+
		        "around the surface as the being moves, almost " +
                "hypnotically. Its shape is vaguely humanoid, but you get "+
                "a sense that it is ";
            other_desc2 = "An earthen " + Adj1 + " " + elem_form + " stands "+
                "here like an adamant living bulwark of the ground. Its "+
                "rocky surface reminds you that this being is both from "+
                "this world and the world below us. There is a vague sound "+
                "as of flinty cracks and the rumble of moving soil when "+
                "the being shifts and moves. Its " + Adj1 + " shape is "+
                "only vaguely humanoid, but you get a sense that it is ";
	        other_desc3 = "Firmament embodied this earthen " + Adj1 + " "+
	            elem_form + " standing before you, a pillar of the very "+
	            "foundations. This is the elemental earth personified and "+
	            "in so permeates a deep resolve and calm grace that stem "+
	            "from the first impassive mountain to the latest crevices "+
	            "and caches of wisdom. Its " + Adj1 + " shape is only "+
	            "vaguely humanoid, but you get a sense that it is ";
    		break;
    	default:
    		elem_form = "presence";	            
	        elem_sound = "whispers in an eerie voice";
	        elem_descrip = "shadows and mist";    		
    		me_desc = "You are cloaked in shifting shadows. Your identity "+
    		    "is concealed to all onlookers unless you choose to "+
    		    "introduce yourself to them again. All of your possessions "+
    		    "are concealed from sight by the shadowy " + elem_form +
    		    " you have become.";
		    string other_desc1 = "This strange " + Adj1 + " " + elem_form +
		        " is cloaked in shifting shadows.The shadows contract and "+
		        "expand eerily as the being moves, but in spite of its "+
		        "forbidding exterior, you do not feel threatened by it. "+
		        "Its shape is only vaguely humanoid, but you get a sense "+
		        "that it is ";
			string other_desc2 = "You catch your breath as you take in the "+
			    "haunting beauty of this radiant " + Adj1 + " " + elem_form +
			    ". It moves languidly and with purpose, and though clearly "+
			    "not of this world, it does not strike you as ominous or "+
			    "menacing. Instead, you find it comforting to look at and "+
			    "be near. Its " + Adj1 + " shape is only vaguely humanoid, "+
			    "but you get a sense that it is ";           
			string other_desc3 = "This mesmerizing " + Adj1 + " " + 
			    elem_form + " has been touched by the divine. It appears "+
			    "forged from light and shadow equally, casting a glow upon "+
			    "its surroundings that makes them seem greater and more "+
			    "alive. From the serene manner of its movements, to the "+
			    "sheer majesty of its presence, everything about this being "+
			    "suggests that it possesses the wisdom of the ages. Its "+
			    Adj1 + " shape is only vaguely humanoid, but you get a "+
			    "sense that it is ";
    		break;
    }
}

void
set_skiamorfi_level(int i)
{
    skiamorfi_level = i;
}

/* 
 *  All functions that this shadow masks should be placed 
 *  below this comment header, -Igneous-  
 */


/*
 * Function name :  parse_command_adjectiv_id_list
 * Description   :  Adds the disguised adverbs to the adjective list
 */
string *
parse_command_adjectiv_id_list()
{
    return ({Adj1}) + ({Adj2});
}

string *
parse_command_id_list()
{
    string *ids =  ({SW->query_real_name(), OB_NAME(SW), elem_form});
    
    if (SW->notmet_me(TP))
    {
        ids -= ({ SW->query_real_name() });
    }
 
    return ids;
}

private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
	return 0;
    if (!arg && sizeof(list))
	return list[0];
    else
	return list + ({});
}

varargs public mixed
query_adj(int arg)
{
    return query_list(({Adj1,Adj2}), arg);
}

public string *
query_adjs() 
{ 
    return query_list(({Adj1, Adj2}), 1);
}

public int
adjectiv_id(string str)
{
    return (member_array(str, ({Adj1, Adj2})) >= 0);
}

string
query_race_name()
{
    return elem_form;
}

public varargs string
long(mixed for_obj)
{
    string sex, other_desc;

    if (shadow_who->query_gender() == G_MALE)
    {
        sex = "male.";
    }
    else if (shadow_who->query_gender() == G_FEMALE)
    {
        sex = "female.";
    }
    else
    {
        sex = "neuter.";
    }

    if (!objectp(for_obj))
    {
        for_obj = TP;
    }
    
    if (skiamorfi_level == 1)
    {
        other_desc = other_desc1 + sex; 
    }
    else
    if (skiamorfi_level == 2)
    {
        other_desc = other_desc2 + sex;
    }
    else
    {
        other_desc = other_desc3 + sex;
    }      

    string visible_sublocs = shadow_who->show_sublocs(
      for_obj, ALLOWED_SUBLOCS);
      
    string result = (SW == for_obj ? me_desc : other_desc) + "\n";
    
    if (stringp(visible_sublocs) && strlen(visible_sublocs))
    {
        result += visible_sublocs;
    }
    
    return result;
} 

public string
race_sound()
{
    return elem_sound;
}

public void
shadow_me_transform(object target)
{
    shadow_me(target);
}
