
/* 	
    This the hairdresser in the town Gelan. 
    One can get one's hair cut which installs a special hair shadow. 
    One can also get magic eye drops to give one eyes of a certain colour
    and type, installing a special eye shadow. The eyes ideas and 
    descriptions are from Prokop.   

    coder(s):   Glykron & Maniac

    history:     
                8/11/97   fixed check for existing eyes shadow Maniac
                 1/8/96   typos corrected                      Maniac 
             14-17/6/96   added eyes feature                   Maniac
                 2/5/96   call_out -> set_alarm                Maniac
                 5/1/96   tell wizards what to do              Maniac
                11/7/95   emote info added                     Maniac
                19/5/95   exit east added                      Maniac
                13.9.94   hair mappings separated to include file,
                          as need to go in hair shadow too.    Maniac
                13.9.94     length & colour options added      Maniac
                12.9.94     autoshadowing for hairstyle added  Maniac
                11. 8.94    bugs removed, mobile added         Maniac
                16. 4.93    updated                         Glykron
                16. 2.93    path/guard system               Merlin
		12.02.93    modified                        Glykron
                12.01.93    created                         Glykron
		 6.11.92    installed help system           Merlin

    purpose:    cut hair here to improve ones look
    exits:      west to square

    objects:    none
    npcs:       none

    quests:     none
    special:    hair shadow

    to do:      none
    bug:        none known
*/

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include GUARD_INCLUDE
#include HAIR_INCLUDE
#include "/d/Calia/gelan/specials/eyes.h"

inherit GELAN_BASE_ROOM;
inherit "/lib/trade";

#define NUM 4
#define HAIRSTYLE_SHADOW GELAN_SPECIALS + "hair_shadow"
#define HAIRSTYLE_SUBLOC "hairstyle"
#define HAIRSTYLE_PRICE 100

#define EAST_EXIT GELAN_ROOMS + "t_par"

mapping eye_colours = EYE_COLOURS; 
mapping eye_types = EYE_TYPES; 
mapping colours = HAIR_COLOURS; 
mapping styles = HAIR_STYLES; 
mapping lengths = HAIR_LENGTHS; 

string *eye_types_ind = m_indexes(eye_types); 
string *eye_colours_ind = m_indexes(eye_colours); 
string *colours_ind = m_indexes(colours); 
string *styles_ind = m_indexes(styles); 
string *lengths_ind = m_indexes(lengths); 

object keeper;



/* 
 * The following query functions are provided so that we only
 * need to have one copy of the hair and eye mappings in the 
 * game. 
 */ 

string
query_hair_length(string ind)
{
    return lengths[ind]; 
}

string
query_hair_colour(string ind)
{
    return colours[ind]; 
}

string
query_hair_style(string ind)
{
    return styles[ind]; 
}


string
query_eye_colour(string ind)
{
    return eye_colours[ind]; 
}


string
query_eye_type(string ind)
{
    return eye_types[ind]; 
}


void
fix_keeper()
{
     keeper = clone_object(GELAN_MONSTERS + "bigoudi");
     keeper->move_living("into the hairdresser", this_object());
}


void
reset_room()
{
    if (!objectp(keeper)) 
         fix_keeper();
}



/*
 * Function name:   picture_descriptions
 * Description:     returns a string with pictures descriptions from the
 *		    mapping hairstyles
 * Arguments:       none
 * Returns:         the descriptions string
 */
string
picture_descriptions()
{
    string desc; 

    desc = ("The pictures showcase various hairstyles. " +
        "Try examining 'hairstyles', 'hair lengths' and 'hair colours'.\n" + 
        "They also show various eyes. " + 
        "Try examining 'eye colours' and 'eye types'.\n"); 

    return desc;
}


/* map_desc, used when putting together descriptions of 
   options for hair cuts or eyes. */ 
string
map_desc(string *ind, mapping m)
{
    int i;
    string md = ""; 

    for (i = 0; i < sizeof(ind); i += 2)  { 
        md += sprintf("%39-s", ind[i] + " - " + m[ind[i]]);  
        if ((i+1) < sizeof(ind)) 
            md += sprintf("%39-s\n", ind[i+1] + " - " + m[ind[i+1]]);  
        else 
            md += "\n"; 
    }

    return md;
}


/* Hair length descs. */ 
string
lengths_desc()
{
    string desc;   

    desc = "These are the possible lengths of hair you can choose:\n"; 

    desc += map_desc(lengths_ind, lengths);  

    desc += "\n"; 

    this_player()->more(desc); 

    return "";
}



/* Hair colours desc */ 
string
colours_desc()
{
    string desc;   

    desc = "These are the possible hair colours you can choose:\n"; 

    desc += map_desc(colours_ind, colours); 

    desc += "\n"; 

    this_player()->more(desc); 

    return "";
}



/* Hair styles desc */ 
string
styles_desc()
{
    string desc;

    desc = "These are the possible styles of hair you can choose:\n";

    desc += map_desc(styles_ind, styles); 

    desc += "\n"; 

    this_player()->more(desc); 

    return "";
}



/* Eye colours desc */ 
string
eye_colours_desc()
{
    string desc;   

    desc = "These are the possible eye colours you can choose:\n";

    desc += map_desc(eye_colours_ind, eye_colours); 

    desc += "\n"; 

    this_player()->more(desc); 

    return "";
}


/* Eye colours desc */ 
string
eye_types_desc()
{
    string desc;   

    desc = "These are the possible eye types you can choose:\n";

    desc += map_desc(eye_types_ind, eye_types); 

    desc += "\n"; 

    this_player()->more(desc); 

    return "";
}


void
do_sorts2()
{
     colours_ind = sort_array(colours_ind); 
     styles_ind = sort_array(styles_ind); 
     lengths_ind = sort_array(lengths_ind); 
}

void
do_sorts1()
{
     eye_types_ind = sort_array(eye_types_ind); 
     eye_colours_ind = sort_array(eye_colours_ind); 
     set_alarm(1.0, 0.0, do_sorts2); 
}



/*
 * Function name:   create_gelan_room
 * Description:     Initialize this room
 * Returns:
 */
public void
create_gelan_room()
{
    /* descriptions */

    set_short("Hair Salon");
    set_long(
	"This room looks like it is in the shape of the inside of a large " +
	"bottle.  " +
	"On the shelves are hundreds of bottles containing colored liquids, " +
	"as well as many sorts of brushes, combs, and scissors.  " +
        "There are pictures on the wall showing you various hairstyles and " +
        "eye types.  " +
        "You also notice a box in the corner and a sign for you to read. " +
        "To the east you see a tattoo parlour.\n");

    /* properties */

    add_prop(ROOM_I_INSIDE, 1);			/* this room is inside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_eastend_s", "west", 0);
    add_exit(EAST_EXIT, "east");
    /* items in the room */

    add_item( ({ "bottles", "liquids" }), 
      "There are many different bottles here with many colors of liquid.\n");
    add_item("combs", "There are combs here in every color.\n");
    add_item("brushes",
      "There are brushes in many colors and with many styles of bristles.\n");
    add_item("scissors", "These are both new and older pairs of scissors " +
	"here.\n");
    add_item("pictures", "@@picture_descriptions");
    add_item("hair lengths", "@@lengths_desc");
    add_item("hairstyles", "@@styles_desc");
    add_item("hair colours", "@@colours_desc");
    add_item("eye colours", "@@eye_colours_desc"); 
    add_item("eye types", "@@eye_types_desc"); 
    add_item("box", "This box has a slit in the top and the word \"idea\" " +
	"written on it.\n");

    config_default_trade();

    seteuid(getuid());
    reset_room();
    set_alarm(1.0, 0.0, do_sorts1); 
} /* create_room */


/*
 * Function name:   do_read
 * Description:     If a player wants to know what instructions can be
 *                  used
 * Arguments:       str - string, hopefully "sign"
 * Returns:         1/0
 */
int
do_read(string str)
{
    NF("Read what?\n");
    if (str != "sign")
	return 0;

    this_player()->more(
         "The price for all hairstyles is " + HAIRSTYLE_PRICE + 
         " copper coins.\nHere are some example haircut commands:\n" +
        "   hair normal (to remove any hairstyle from your description)\n" + 
	"   hair med lbr wavy\n" +
	"   hair med lbr wavy for gold\n" +
	"   hair med lbr wavy for gold and get copper\n\n" +
        "Remember, for a haircut, you give hair length, hair colour then " +
        "hair style.\n\n"  + 
        "The price to have your eyes washed is " + EYES_PRICE + 
        " copper coins.\nHere are some example eye commands:\n" +
        "   eyes normal (to remove any eye details from your description)\n" + 
    "   Adding 'one' on the end will allow you to have just one eye.\n"+
	"   eyes dem icbl\n" +
	"   eyes dem icbl one\n" +
	"   eyes dem icbl for gold\n" +
	"   eyes dem icbl for gold and get copper\n\n" +
        "Remember, for an eye wash, you give eye type then eye colour.\n\n");
    return 1;
}



int
check_keeper()
{
  if (keeper && present(keeper,this_object()))
    return 1;
  else
    return 0;
}


/*
 * Function name:   buy_it_hair
 * Description:     Try to let the player buy the item array
 * Returns:         1 on success
 * Arguments:       ob - the object array
 *                  str2 - string describing how the money should be paid
 *                  str3 - what coin types to get change back in
 */
int
buy_it_hair(string str1, string str2, string str3, string l, string c, string s)
{
    int price, i, j, k, *arr, error, bought;
    string aut = HAIRSTYLE_SHADOW + ":" + l + "," + c + "," + s;
    object shadow;

    if (sizeof(arr = pay(HAIRSTYLE_PRICE, TP, str2, 0, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    /* Detect if there was a move error. */
    if (error = arr[sizeof(arr) - 1])
    {
	if (error < -1)
	{
	    /* Couldn't take the money from player, the coins were stuck */
            keeper->command("say Magic money? No thanks!");
	    NF("");
	    return 0;
	}
    }

    shadow = TP->query_subloc_obj(HAIRSTYLE_SUBLOC);
    if (!shadow)
    {
	shadow = clone_object(HAIRSTYLE_SHADOW);
	if (!shadow->shadow_me(TP))
	{
            shadow->destruct_hair_shadow();
            keeper->command("say How strange, I can't give you a hairdo!");
	    NF("");
	    return 0;
	}

	TP->catch_msg(QCTNAME(keeper) + " changes your hairstyle.\n");
        say(QCTNAME(keeper) + " changes " + QTNAME(TP) + "'s hairstyle.\n"); 
        TP->add_autoshadow(aut);
	TP->add_subloc(HAIRSTYLE_SUBLOC, shadow);
    }

    if (str1 == "normal")
    {
        shadow->destruct_hair_shadow();
        TP->remove_autoshadow(HAIRSTYLE_SHADOW);
	TP->remove_subloc(HAIRSTYLE_SUBLOC);
        if (TP->query_wiz_level()) {
            TP->catch_msg("You will have to remove the autoshadow " + 
                           "and cmdsoul yourself if they are present.\n"); 
        }
    }
    else {
	    shadow->set_hairstyle(str1);
        shadow->set_hair_length(lengths[l]);
        shadow->set_hair_style(styles[s]);
        shadow->set_hair_colour(colours[c]);
        shadow->add_hair_commands();
        TP->remove_autoshadow(HAIRSTYLE_SHADOW);
        TP->add_autoshadow(aut);
    }

    str2 = text(arr[NUM .. 2 * NUM - 1]);
    if (!str2) str2 = "nothing";
    TP->catch_msg("You pay " + QTNAME(keeper) + " " + 
                  text(arr[0 .. NUM - 1]) + 
                  ", getting back " + str2 + " in change.\n");
    say(QCTNAME(TP) + " pays " + QTNAME(keeper) + " " +
                  text(arr[0 .. NUM - 1]) +
                  ", getting back " + str2 + " in change.\n");

    if (TP->query_wiz_level() && (str1 != "normal")) { 
        TP->catch_msg("Since you are a wizard, you will have to do " +
          "the following if you want to keep your hair shadow " +
          "and have hair emote commands.\n" + 
          "First: Call @" + TP->query_real_name() + " add_autoshadow " + 
          aut + "\nSecond: Call @" + TP->query_real_name() + " add_cmdsoul " +
          GELAN_SPECIALS + "hair_cmdsoul" + "\n"); 
    TP->catch_msg("Finally: Call me update_hooks\n");
     }

    if (str1 != "normal")
        TP->catch_msg("\n\nType `help hair' for hair emote details.\n");

    return 1;
}


/*
 * Function name:   do_buy_hair
 * Description:     Try to let the player buy a hairstyle
 * Returns:         1 on success
 * Arguments:       str - describing how to pay and get change
 */
int
do_buy_hair(string str)
{
    object *item, store;
    string str1, str2, str3, *descr_str;

    if(!str || str == "")
    {
	NF("Hair what?\n");
	return 0;
    }

    if (!check_keeper())
    {
       NF("The hairdresser is not here!\n");
       return 0;
    }

    /*  Did the player specify payment and change? */
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done at least? */
	str3 = "";
	if (sscanf(str, "%s for %s", str1, str2) != 2)
	{
	    str2 = "";
	    str1 = str;
	}
    }

    if (!(str1 == "normal")) {

    descr_str = explode(str1, " ");
    if (sizeof(descr_str) != 3) {
        NF("");
        keeper->command("say I don't understand you, " + 
               TP->query_nonmet_name() + ", please read the sign.");
        return 0; 
    }


    if (!lengths[descr_str[0]])
    {
       NF("");
       keeper->command("say I don't know a length called " + descr_str[0]
                     + ", ducky.");
       return 0;
    }


    if (!colours[descr_str[1]])
    {
       NF("");
       keeper->command("say I have no dye colour called " + descr_str[1]
                     + ", ducky.");
       return 0;
    }

    if (!styles[descr_str[2]])
    {
       NF("");
       keeper->command("say I don't know a style called " + descr_str[2]
                     + ", ducky.");
       return 0;
    }

    str1 = lengths[descr_str[0]] + ", " + colours[descr_str[1]] + " and " +
           styles[descr_str[2]];

    } /* End if */

    if (str1 == "normal") 
      descr_str = ({ "", "", "" });
    
    if (buy_it_hair(str1, str2, str3, descr_str[0], descr_str[1], descr_str[2]))
    {
	say(QCTNAME(keeper) + " fixes " + QCTNAME(TP) + "'s hair so that " +
                   "it is " + str1 + ".\n");
	TP->catch_msg(QCTNAME(keeper) + " fixes your hair so that it is " 
                      + str1 + ".\n");
	return 1;
    }

    return 0; /* Player tried to sell a non sellable object. */
}


/*
 * Function name:   buy_it_eyes
 * Description:     Try to let the player buy eyes
 * Returns:         1 on success
 * Arguments:       str1 - the description of the eyes  
 *                  str2 - string describing how the money should be paid
 *                  str3 - what coin types to get chainge back in
 *                  t - the eye type index
 *                  c - the eye colour index
 *                  num - the number of eyes 
 */
int
buy_it_eyes(string str1, string str2, string str3, string t, string c, int num)
{
    int price, i, j, k, *arr, error, bought;
    string aut = (EYES_SHADOW + ":" + t + "," + c + "," + num);
    object shadow;
    string eye_or_eyes; 

    if (sizeof(arr = pay(EYES_PRICE, TP, str2, 0, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    /* Detect if there was a move error. */
    if (error = arr[sizeof(arr) - 1])
    {
	if (error < -1)
	{
	    /* Couldn't take the money from player, the coins were stuck */
            keeper->command("say Magic money? No thanks!");
	    NF("");
	    return 0;
	}
    }

    if (i == 1) 
        eye_or_eyes = "eye"; 
    else
        eye_or_eyes = "eyes"; 

    shadow = TP->query_gelan_eyes_shadow();
    if (!objectp(shadow))
    {
	shadow = clone_object(EYES_SHADOW);
	if (!shadow->shadow_me(TP))
	{
            shadow->destruct_eyes_shadow();
            keeper->command("say How strange, I can't wash your " + 
                            eye_or_eyes + "!");
	    NF("");
	    return 0;
	}

	TP->catch_msg(QCTNAME(keeper) + " looks into your " + eye_or_eyes +
                      ".\n");
        say(QCTNAME(keeper) + " looks into " + QTNAME(TP) + "'s " + 
            eye_or_eyes + ".\n"); 
    }

    if (str1 == "normal")
    {
        shadow->destruct_eyes_shadow();
        TP->remove_autoshadow(EYES_SHADOW);
        if (TP->query_wiz_level()) {
            TP->catch_msg("You will have to remove the autoshadow " + 
                           "and cmdsoul yourself if they are present.\n"); 
        }
    }
    else {
	shadow->set_eyes(str1);
        shadow->set_eyes_type(eye_types[t]);
        shadow->set_eyes_colour(eye_colours[c]);
        shadow->set_eyes_number(num); 
        shadow->add_eyes_commands();
        TP->remove_autoshadow(EYES_SHADOW);
        TP->add_autoshadow(aut);
    }

    str2 = text(arr[NUM .. 2 * NUM - 1]);
    if (!str2) str2 = "nothing";
    TP->catch_msg("You pay " + QTNAME(keeper) + " " + 
                  text(arr[0 .. NUM - 1]) + 
                  ", getting back " + str2 + " in change.\n");
    say(QCTNAME(TP) + " pays " + QTNAME(keeper) + " " +
                  text(arr[0 .. NUM - 1]) +
                  ", getting back " + str2 + " in change.\n");

    if (TP->query_wiz_level() && (str1 != "normal")) { 
        write("Since you are a wizard, you will have to do " +
          "the following if you want to keep your eye shadow " +
          "and have eye emote commands.\n" + 
          "First: Call @" + TP->query_real_name() + " add_autoshadow " + 
          aut + "\nSecond: cmdsoul " + EYES_CMDSOUL + "\n"); 
        write("Finally:  Call me update_hooks\n");
    }

    if (str1 != "normal")
        write("\n\nType `help eyes' for eye emote details.\n");

    return 1;
}


/*
 * Function name:   do_buy_eyes
 * Description:     Try to let the player buy an eye wash
 * Returns:         1 on success
 * Arguments:       str - describing how to pay and get change
 */
int
do_buy_eyes(string str)
{
    int i; 
    object *item, store;
    string str1, str2, str3, *descr_str;

    if (!str || str == "")
    {
	NF("Eyes what?\n");
	return 0;
    }

    if (!check_keeper())
    {
       NF("The hairdresser is not here!\n");
       return 0;
    }

    /*  Did the player specify payment and change? */
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done at least? */
	str3 = "";
	if (sscanf(str, "%s for %s", str1, str2) != 2)
	{
	    str2 = "";
	    str1 = str;
	}
    }

    i = 2; 

    if (!(str1 == "normal")) {
        descr_str = explode(str1, " ");
        i = sizeof(descr_str); 
        if (i == 3 && (descr_str[2] == "one")) {  
            descr_str = exclude_array(descr_str, 2, 2);  
            i = 1;  
        } 
        else 
            i = 2; 

        if (sizeof(descr_str) != 2) {
            NF("");
            keeper->command("say I don't understand you, " + 
                   TP->query_nonmet_name() + ", please read the sign.");
            return 0; 
        }

        if (!eye_types[descr_str[0]])
        {
            NF("");
            keeper->command("say I don't know an eye type called " + 
                            descr_str[0] + ".");
            return 0;
        }


        if (!eye_colours[descr_str[1]])
        {
            NF("");
            keeper->command("say I don't know any eye colour called " + 
                            descr_str[1] + ".");
            return 0;
        }

        str1 = eye_types[descr_str[0]] + " " + eye_colours[descr_str[1]];

    } /* End if */

    if (str1 == "normal") 
        descr_str = ({ "", "", "" });

    if (buy_it_eyes(str1, str2, str3, descr_str[0], descr_str[1], i))
    {
	say(QCTNAME(keeper) + " squirts cleaning fluid into " + 
                 QCTNAME(TP) + "'s " + (i == 1 ? "eye" : "eyes") + 
                 ". After a moment, " + 
                 (i == 1 ? "it becomes " : "they become ") + str1 + ".\n");
	TP->catch_msg(QCTNAME(keeper) + " squirts cleaning fluid into your " + 
              (i == 1 ? "eye" : "eyes") + 
              ". After a moment " + (i == 1 ? "it becomes " : "they become ")+ 
              str1 + ".\n");
	return 1;
    }

    return 0; /* Player tried to sell a non sellable object. */
}



/*
 * Function name:   do_idea
 * Description:     let the player put an idea in the idea box
 * Returns:         1 on success
 * Arguments:       str - the idea
 */
int
do_idea(string str)
{
    write("You place an idea in the box.\n");
    say(QCTNAME(this_player()) + " places an idea in the box.\n"); 
    return 0;
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();  
    add_action(do_buy_hair, "hair");
    add_action(do_buy_eyes, "eyes"); 
    add_action(do_read, "read");
    add_action(do_idea, "idea");
}

