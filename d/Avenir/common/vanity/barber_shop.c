// /d/Avenir/common/vanity/barber_shop
// connects to /d/Avenir/common/outpost/tower_middle2.c 
//
// Stylist for Beards and Mustaches
//   heavily based on Maniac's and Glykron's hairdresser
//   in Gelan for consistency of experience for mortals.
// 
// For thematic reasons the barber is prohibited from 
//  working on hobbits as well as thieves,  
//  kenders, and other shady types of characters.
//  Males and females can have mustaches and beards.

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/common/vanity/vanity.h"
#include "/d/Avenir/common/vanity/facial_hair.h"
#include "/d/Avenir/common/outpost/outpost.h"

inherit "/d/Avenir/common/outpost/fort_base";
inherit "/lib/trade";

#define BEARD_SHADOW     VANITY +"beard_shadow" 
#define BEARD_SOUL       VANITY +"beard_cmdsoul"
#define BEARD_SUBLOC     "vanity_beard"

#define MUSTACHE_SHADOW    VANITY +"mustache_shadow"
#define MUSTACHE_SOUL      VANITY +"mustache_cmdsoul"
#define MUSTACHE_SUBLOC    "vanity_mustache"

// Beard 1pc & Mustache 6gc
#define COST_BEARD   1728
#define COST_STACHE  864

/* Number of coin types */
#define NUM          4

mapping colours = F_HAIR_COLOURS; 
mapping lengths = F_HAIR_LENGTHS; 
mapping b_styles = BEARD_STYLES; 
mapping s_styles = STACHE_STYLES;

string *s_styles_ind = m_indexes(s_styles); 
string *b_styles_ind = m_indexes(b_styles); 
string *lengths_ind = m_indexes(lengths); 
string *colours_ind = m_indexes(colours); 

object keeper;

/* 
 * The following query functions are provided so that we only
 * need to have one copy of the mappings in the game. 
 */ 

string
query_f_hair_length(string ind)
{
    return lengths[ind]; 
}

string
query_f_hair_colour(string ind)
{
    return colours[ind]; 
}

string
query_beard_style(string ind)
{
    return b_styles[ind]; 
}

string
query_mustache_style(string ind)
{
    return s_styles[ind]; 
}

void
fix_keeper()
{
     keeper = clone_object(VANITY + "barber");
     keeper->move_living("struts into the room", this_object());
}

void
reset_domain_room()
{
    if (!objectp(keeper)) 
         fix_keeper();
}


string
picture_descriptions()
{
    string desc; 

    desc = ("The pictures showcase various ways the barber knows "+
            "how to style facial hair.\n"+
            "Try examining 'beard styles' and 'mustache styles' as "+
		    "well as 'hair lengths|hair growth' and 'hair colours'.\n"); 

    return desc;
}


string
map_desc(string *ind, mapping m)
{
    int i;
    string md = ""; 

    for (i = 0; i < sizeof(ind); i += 2)  { 
        md += sprintf("%s\n", ind[i] + " - " + m[ind[i]]);  
        if ((i+1) < sizeof(ind)) 
            md += sprintf("%s", ind[i+1] + " - " + m[ind[i+1]]);  
            md += "\n"; 
    }

    return md;
}


/* Hair length descs. */ 
string
lengths_desc()
{
    string desc;   

    desc = "These are the possible growth|lengths of facial hair you can choose:\n"; 

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

    desc = "These are the possible facial hair colours you can choose:\n"; 

    desc += map_desc(colours_ind, colours); 

    desc += "\n"; 

    this_player()->more(desc); 

    return "";
}



/* Beard styles desc */ 
string
b_styles_desc()
{
    string desc;

    desc = "These are the possible beard styles you can choose:\n";

    desc += map_desc(b_styles_ind, b_styles); 

    desc += "\n"; 

    this_player()->more(desc); 

    return "";
}


/* Stache styles desc */ 
string
s_styles_desc()
{
    string desc;   

    desc = "These are the possible mustache styles you can choose:\n";

    desc += map_desc(s_styles_ind, s_styles); 

    desc += "\n"; 

    this_player()->more(desc); 

    return "";
}


void
do_sorts2()
{
     colours_ind = sort_array(colours_ind); 	 
     lengths_ind = sort_array(lengths_ind); 
}

void
do_sorts1()
{
     s_styles_ind = sort_array(s_styles_ind);
     b_styles_ind = sort_array(b_styles_ind);	
	 
     set_alarm(1.0, 0.0, do_sorts2); 
}

/* Create the barber shop  */
public void
create_fort_room()
{
    /* descriptions */
    set_short("the barber shop");
    set_long("This is the barber shop on the third floor of the largest tower "+
      "in Fort Sybarus. "+
      "The room is mostly just a landing for the stairs that wind "+
      "their way up and down along the stone walls. "+
      "The window north of here provides great light for cutting hair. "+
	  "Pictures of beard and mustache styles are hanging everywhere, "+
      "with a colour chart being the most prominently placed.\n" +
	  "There is a sign overhead providing instructions to "+
      "prospective clients." +
      "\n");
	  
    room_add_object(OUTPOST +"obj/seats/stool");
	add_exit(OUTPOST +"tower_middle2", "north", 0);
    add_exit(OUTPOST +"tower_office",  "up",    0, 0, 1);
    add_exit(OUTPOST +"tower_middle3", "down",  0, 0, 1);
	
    add_fort_room();
    add_exit_views();

    add_item(({"sign", "instructions"}), 
	"It is a large sign with a lot of information on it.\n");
    add_item("pictures",      "@@picture_descriptions");

    add_item("beard styles",      "@@b_styles_desc");
    add_item("beard style",       "@@b_styles_desc");
    add_item("beards",            "@@b_styles_desc");
	
    add_item("stache styles",     "@@s_styles_desc");
    add_item("mustache styles",   "@@s_styles_desc");
    add_item("mustache style",    "@@s_styles_desc");
    add_item("mustaches",         "@@s_styles_desc");
	
    add_item("lengths",           "@@lengths_desc");	
    add_item("length",            "@@lengths_desc");	
    add_item("hair lengths",      "@@lengths_desc");
    add_item("beard lengths",     "@@lengths_desc");
    add_item("mustache lengths",  "@@lengths_desc");
    add_item("stache lengths",    "@@lengths_desc");

    add_item("growth",            "@@lengths_desc");	
    add_item("hair growth",       "@@lengths_desc");
    add_item("beard growth",      "@@lengths_desc");
    add_item("mustache growth",   "@@lengths_desc");
    add_item("stache growth",     "@@lengths_desc");

    add_item("colours",           "@@colours_desc");
    add_item("colour",            "@@colours_desc");
    add_item("colors",            "@@colours_desc");
    add_item("color",             "@@colours_desc");
    add_item("hair colours",      "@@colours_desc");
    add_item("beard colours",     "@@colours_desc");
    add_item("mustache colours",  "@@colours_desc");
    add_item("stache colours",    "@@colours_desc");
    add_item("hair colors",       "@@colours_desc");
    add_item("beard colors",      "@@colours_desc");
    add_item("mustache colors",   "@@colours_desc");
    add_item("stache colors",     "@@colours_desc");
    add_item("colour chart",      "@@colours_desc");
    add_item("color chart",       "@@colours_desc");
    add_item("chart",             "@@colours_desc");
	
    add_item(({"window", "large window", "view"}),
    "You'll need to go a bit further north to get a good view "+
    "from the window.\n");
	
    config_default_trade();

    seteuid(getuid());
    reset_domain_room();
    set_alarm(1.0, 0.0, do_sorts1); 
} 


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
    notify_fail("Read what?\n");
    if (str != "sign" && str != "instructions")
	return 0;

    this_player()->more(
        "The price for styling beards is 1 platinum coin.\n "+
        "Here are some example beard styling commands:\n" +
        "   beard <shave> to remove a beard from your description.\n" + 
		"   beard <growth|length> <colour> <style>\n"+
	    "   Examples: 'beard g12 c26 b13' results in:\n" +
		"              a knee-length green forked beard\n"+
        "             'beard g18 c39 b10' results in:\n"+
        "              a bushy black pair of mutton-chops\n"+
        "\n\n"+ 
        "The price for styling mustaches is 6 gold coins.\n "+ 
        "Here are some example mustache styling commands:\n" +
        "   mustache <shave> to remove a mustache from your description.\n" + 
        "   mustache <growth|length> <colour> <style>\n" +
     	"   Examples: 'mustache g11 c53 m07' results in:\n" +
     	"              a very long rainbow-coloured walrus mustache\n" +
     	"             'stache g10 c48 m10' results in:\n"+
        "              a long silvery fu manchu mustache\n"+ 		
		"\n\n"+
		"   <exa beard growth|colours|styles> and\n"+
		"  <exa stache growth|colours|styles> for details.\n\n"+
	    "      We reserve the right to refuse service to anyone.\n\n");
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
 * Function name:   buy_it_beard
 * Description:     Try to let the player buy the item array
 * Returns:         1 on success
 * Arguments:       ob - the object array
 *                  str2 - string describing how the money should be paid
 *                  str3 - what coin types to get change back in
 */
int
buy_it_beard(string str1, string str2, string str3, string l, string c, string s)
{
    int price, i, j, k, *arr, error, bought;
    string aut = (BEARD_SHADOW + ":" + l + "," + c + "," + s);
    object shadow;

    if (sizeof(arr = pay(COST_BEARD, TP, str2, 0, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    /* Detect if there was a move error. */
    if (error = arr[sizeof(arr) - 1])
    {
	if (error < -1)
	{
	    /* Couldn't take the money from player, the coins were stuck */
        keeper->command("say Magic money? No thanks!");
	    notify_fail("");
	    return 0;
	}
    }
    
	keeper->command("say I trust that is the right choice for you. Now "+
        "if you will just hold still for a moment...");
		
    shadow = TP->query_subloc_obj(BEARD_SUBLOC);
    if (!shadow)
    {
	    shadow = clone_object(BEARD_SHADOW);
	    if (!shadow->shadow_me(TP))
	    {
            shadow->destruct_beard_shadow();
            keeper->command("say This is odd, ae can't style a beard for you!");
	        notify_fail("Failed to add beard shadow.\n");
	        return 0;
        }

	    TP->catch_msg(QCTNAME(keeper) + " gets to work on changing your beard.\n");
        say(QCTNAME(keeper) + " gets to work on " + QTNAME(TP) + "'s beard.\n"); 
        TP->add_autoshadow(aut);
	    TP->add_subloc(BEARD_SUBLOC, shadow);

    }

    if (str1 == "shave")
    {
		keeper->command("emote produces a straight-razor and some cream and "+
		    "and gets to work.");
        shadow->destruct_beard_shadow();
        TP->remove_autoshadow(BEARD_SHADOW);
	    TP->remove_subloc(BEARD_SUBLOC);
        if (TP->query_wiz_level()) 
        {
            TP->catch_msg("You will have to remove the autoshadow " + 
               "and cmdsoul yourself if they are present.\n"); 
        }
    }
	
    else 
    {
		keeper->command("emote dips into some pots of hair dye and starts "+
		    "snipping near your face with tiny scissors.");
        shadow->set_beardstyle(str1);
        shadow->set_beard_length(lengths[l]);
        shadow->set_beard_colour(colours[c]);
		shadow->set_beard_style(b_styles[s]);
        shadow->add_beard_commands();
        TP->remove_autoshadow(BEARD_SHADOW);		
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

    if (TP->query_wiz_level() && (str1 != "shave")) 
	{ 
        TP->catch_msg("Since you are a wizard, you will have to do " +
          "the following if you want to keep your hair shadow " +
          "and have hair emote commands.\n" + 
          "First: Call @" + TP->query_real_name() + " add_autoshadow " + 
          aut + "\nSecond: Call @" + TP->query_real_name() + " add_cmdsoul " +
          BEARD_SOUL +".\n"); 
        TP->catch_msg("Finally: 'Call me update_hooks' or just do 'newhooks'.\n");
    }

    if (str1 != "shave")
	{
		keeper->command("emote smiles triumphantly.");
		TP->catch_msg("The barber gives your beard a final pat.\n");
        TP->catch_msg("\n\nType 'help beard' for beard-related emotes.\n");
    }
    return 1;
}


/*
 * Function name:   do_buy_beard
 * Description:     Try to let the player buy a beard
 * Returns:         1 on success
 * Arguments:       str - describing how to pay and get change
 */
int
do_buy_beard(string str)
{
    object *item, store;
    string str1, str2, str3, *descr_str;

    if(!str || str == "")
    {
	notify_fail("Beard what? Try [beard <growth> <colour> <style>].\n");
	return 0;
    }

    if (!check_keeper())
    {
       notify_fail("The barber is not here to style your beard.\n");
       return 0;
    }
	
	/* These are the races and guilds that services are denied to */
	/*if (TP->query_race() == "elf")
    {
        keeper->command("bow politely");
        keeper->command("say It would be my privilege to style "+
        "a beard for you, but alas, I cannot help elves grow "+
        "facial hair. That requires magical skills I do not have.");
        return 0;
    }
	*/
    if (member_array(TP->query_race(), FH_DENY_RACES) != -1)
    { 
    	keeper->command("say It is forbidden for me to provide any "+
        "services to people of your species.\n");
	    return 0;
    }
	
    if (member_array(TP->query_guild_style_occ(), DENY_G_STYLE) != -1)
    { 
    	keeper->command("say You look too shady to me, Outlander. "+
        "No amount of coin is worth the risk of being dragged "+
        "before the Inquisitors because you used my services "+
        "to change your look.\n");
	    return 0;
    }
	
    if (member_array(TP->query_guild_style_lay(), DENY_G_STYLE) != -1)
    { 
    	keeper->command("say You look too shady to me, Outlander. "+
        "No amount of coin is worth the risk of being dragged "+
        "before the Inquisitors because you used my services "+
        "to change your look.\n");
	    return 0;
    }

    if (member_array(TP->query_guild_style_race(), DENY_G_STYLE) != -1)
    { 
    	keeper->command("say You look too shady to me, Outlander. "+
        "No amount of coin is worth the risk of being dragged "+
        "before the Inquisitors because you used my services "+
        "to change your look.\n");
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

    if (!(str1 == "shave")) 
	{
        descr_str = explode(str1, " ");
        if (sizeof(descr_str) != 3) 
    	{
            notify_fail("");
            keeper->command("say I don't understand you, " + 
            TP->query_nonmet_name() + ", please read the sign.");
            return 0; 
        }

        if (!lengths[descr_str[0]])
        {
            notify_fail("");
            keeper->command("say I don't know a beard length called " + descr_str[0]
                + ", sorry.");
            return 0;
        }

        if (!colours[descr_str[1]])
        {
            notify_fail("");
            keeper->command("say I do not know of a beard colour called " + descr_str[1]
                + ", so sorry.");
            return 0;
        }

        if (!b_styles[descr_str[2]])
        {
            notify_fail("");
            keeper->command("say I don't know of a style of beard called " + descr_str[2]
                + ", so very sorry.");
            return 0;
        }

        str1 = lengths[descr_str[0]] + " " + colours[descr_str[1]] + " " +
           b_styles[descr_str[2]];

    } /* End if */

    if (str1 == "shave") 
	{
	    say(QCTNAME(keeper) + " shaves " + QCTNAME(TP) + "'s beard off.\n");
    	TP->catch_msg(QCTNAME(keeper) + " shaves off your beard.\n");
        descr_str = ({ "", "", "" });
    }		
	
    if (buy_it_beard(str1, str2, str3, descr_str[0], descr_str[1], descr_str[2]))
    {
    	TP->catch_msg(QCTNAME(keeper) + " appears to be pleased with his efforts.\n");
	    return 1;
    }

    return 0; /* Player tried to sell a non sellable object. */
}



/*
 * Function name:   buy_it_stache
 * Description:     Try to let the player a mustache
 * Returns:         1 on success
 * Arguments:       ob - the object array
 *                  str2 - string describing how the money should be paid
 *                  str3 - what coin types to get change back in
 */
int
buy_it_stache(string str1, string str2, string str3, string l, string c, string s)
{

    int price, i, j, k, *arr, error, bought;
    string aut = (MUSTACHE_SHADOW + ":" + l + "," + c + "," + s);
    object shadow;

    if (sizeof(arr = pay(COST_STACHE, TP, str2, 0, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */

    /* Detect if there was a move error. */
    if (error = arr[sizeof(arr) - 1])
    {
	if (error < -1)
	{
	    /* Couldn't take the money from player, the coins were stuck */
        keeper->command("say Magic money? No thanks!");
	    notify_fail("");
	    return 0;
	}
    }

    keeper->command("say That should be a good look on you. Now, if you would "+
        "hold still for me, please... this is meticulous work.");
		
    shadow = TP->query_subloc_obj(MUSTACHE_SUBLOC);
    if (!shadow)
    {
	    shadow = clone_object(MUSTACHE_SHADOW);
	    if (!shadow->shadow_me(TP))
	    {
            shadow->destruct_mustache_shadow();
            keeper->command("say This is odd, ae can't style a mustache for you!");
	        notify_fail("Do a bug report. Failed to add mustache shadow.\n");
	        return 0;
        }

	    TP->catch_msg(QCTNAME(keeper) + " gets to work on changing your mustache.\n");
        say(QCTNAME(keeper) + " gets to work on " + QTNAME(TP) + "'s mustache.\n"); 
        TP->add_autoshadow(aut);
	    TP->add_subloc(MUSTACHE_SUBLOC, shadow);

    }

    if (str1 == "shave")
    {
		keeper->command("emote produces a straight-razor and some cream and "+
		    "and gets to work.");
        shadow->destruct_mustache_shadow();
        TP->remove_autoshadow(MUSTACHE_SHADOW);
	    TP->remove_subloc(MUSTACHE_SUBLOC);
        if (TP->query_wiz_level()) 
        {
            TP->catch_msg("You will have to remove the autoshadow " + 
               "and cmdsoul yourself if they are present.\n"); 
        }
    }
	
    else 
    {
		keeper->command("emote dips into some pots of hair dye and starts "+
		    "snipping near your upper lip with tiny scissors.");
        shadow->set_mustachestyle(str1);
        shadow->set_mustache_length(lengths[l]);
        shadow->set_mustache_colour(colours[c]);
		shadow->set_mustache_style(s_styles[s]);
        shadow->add_mustache_commands();
        TP->remove_autoshadow(MUSTACHE_SHADOW);		
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

    if (TP->query_wiz_level() && (str1 != "shave")) 
	{ 
        TP->catch_msg("Since you are a wizard, you will have to do " +
          "the following if you want to keep your hair shadow " +
          "and have hair emote commands.\n" + 
          "First: Call @" + TP->query_real_name() + " add_autoshadow " + 
          aut + "\nSecond: Call @" + TP->query_real_name() + " add_cmdsoul " +
          MUSTACHE_SOUL +".\n"); 
        TP->catch_msg("Finally: 'Call me update_hooks' or just do 'newhooks'.\n");
    }

    if (str1 != "shave")
	{
		keeper->command("emote smiles triumphantly.");
		TP->catch_msg("The barber gives your mustache a final pat.\n");
        TP->catch_msg("\n\nType 'help mustache' for mustache-related emotes.\n");
    }
    return 1;
}


/*
 * Function name:   do_buy_stache
 * Description:     Try to let the player buy a mustache
 * Returns:         1 on success
 * Arguments:       str - describing how to pay and get change
 */
int
do_buy_stache(string str)
{

    object *item, store;
    string str1, str2, str3, *descr_str;

    if(!str || str == "")
    {
	notify_fail("Mustache what? Try mustache <growth> <colour> <style>.\n");
	return 0;
    }

    if (!check_keeper())
    {
       notify_fail("The barber is not here to style your mustache.\n");
       return 0;
    }
	
	/* These are the races and guilds that services are denied to */
	if (TP->query_race() == "elf")
    {
        keeper->command("bow politely");
        keeper->command("say It would be my privilege to style "+
        "a mustache for you, but alas, elves cannot grow facial hair.");
        return 0;
    }
	
    if (member_array(TP->query_race(), FH_DENY_RACES) != -1)
    { 
    	keeper->command("say It is forbidden for me to provide any "+
        "services to people of your species.\n");
	    return 0;
    }
	
    if (member_array(TP->query_guild_style_occ(), DENY_G_STYLE) != -1)
    { 
    	keeper->command("say You look too shady to me, Outlander. "+
        "No amount of coin is worth the risk of being dragged "+
        "before the Inquisitors because you used my services "+
        "to change your look.\n");
	    return 0;
    }
	
    if (member_array(TP->query_guild_style_lay(), DENY_G_STYLE) != -1)
    { 
    	keeper->command("say You look too shady to me, Outlander. "+
        "No amount of coin is worth the risk of being dragged "+
        "before the Inquisitors because you used my services "+
        "to change your look.\n");
	    return 0;
    }

    if (member_array(TP->query_guild_style_race(), DENY_G_STYLE) != -1)
    { 
    	keeper->command("say You look too shady to me, Outlander. "+
        "No amount of coin is worth the risk of being dragged "+
        "before the Inquisitors because you used my services "+
        "to change your look.\n");
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

    if (!(str1 == "shave")) {

    descr_str = explode(str1, " ");
    if (sizeof(descr_str) != 3) {
        notify_fail("");
        keeper->command("say I don't understand you, " + 
               TP->query_nonmet_name() + ", please read the sign.");
        return 0; 
    }


    if (!lengths[descr_str[0]])
    {
       notify_fail("");
       keeper->command("say I don't know a mustache growth called " + descr_str[0]
                     + ", sorry.");
       return 0;
    }


    if (!colours[descr_str[1]])
    {
       notify_fail("");
       keeper->command("say I do not know of a mustache colour called " + descr_str[1]
                     + ", so sorry.");
       return 0;
    }

    if (!s_styles[descr_str[2]])
    {
       notify_fail("");
       keeper->command("say I don't know of a style of mustache called " + descr_str[2]
                     + ", so very sorry.");
       return 0;
    }

    str1 = lengths[descr_str[0]] + " " + colours[descr_str[1]] + " " +
           s_styles[descr_str[2]];

    } /* End if */

    if (str1 == "shave") 
	{
	    say(QCTNAME(keeper) + " shaves " + QCTNAME(TP) + "'s mustache off.\n");
    	TP->catch_msg(QCTNAME(keeper) + " shaves off your mustache.\n");
        descr_str = ({ "", "", "" });
    }		
    if (buy_it_stache(str1, str2, str3, descr_str[0], descr_str[1], descr_str[2]))
    {
        keeper->command("emote steps back to admire the overall effect of his efforts.");
	    return 1;
    }

    return 0; /* Player tried to sell a non sellable object. */
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
    add_action(do_buy_beard,  "beard");
    add_action(do_buy_stache, "mustache");
    add_action(do_buy_stache, "stache");	
    add_action(do_read, "read");
}

