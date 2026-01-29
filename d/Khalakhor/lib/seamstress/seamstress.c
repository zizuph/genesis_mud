/**********************************************************************
 * - seamstress.c                                                   - *
 * - This module is based heavily on the smithy code created by     - *
 * - Raven for me in SaV, with permission to use here.              - *
 * -                                                                - *
 * - npc_seamstress.c is an example on how to add this code to npc  - *
 * - to create a seamstress.                                        - *
 * - Created by Damaris@Genesis 08/2005                             - *
 **********************************************************************/
inherit "/lib/trade";
#include <exec.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "seamstress.h"

/**********************************************************************
 * - Function name : create_seamstress_repository                   - *
 * - Description   : A container to hold the produced items in      - *
 * - Arguments     : void    - no arguments                         - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
create_seamstress_repository()
{
	if (objectp(seamstress_repository) ||
	    objectp(seamstress_repository =
	    present("_seamstress_repository", ENV(TO))))
	    return;
	    setuid(); seteuid(getuid());
	    seamstress_repository = clone_object("/std/container");
	    seamstress_repository->set_name("_seamstress_repository");
	    seamstress_repository->set_no_show();
	    seamstress_repository->add_prop(OBJ_I_WEIGHT     , 0);
	    seamstress_repository->add_prop(OBJ_I_VOLUME     , 0);
	    seamstress_repository->add_prop(CONT_I_MAX_WEIGHT, 1000000);
	    seamstress_repository->add_prop(CONT_I_MAX_VOLUME, 1000000);
	    seamstress_repository->add_prop(OBJ_M_NO_GET     , 1);
	    seamstress_repository->move(ENV(TO), 1);
}

/**********************************************************************
 * - Function name : filter_seamstress_repository                   - *
 * - Description   : filters out objects that belong to the client  - *
 * - Arguments     : object  - the object                           - *
 * -                 string  - the client                           - *
 * - Returns       : int     - 1 if object belongs to client        - *
 * -                           0 if not                             - *
 **********************************************************************/

int
filter_seamstress_repository(object item, string client)
{
	/* oportunity to remove objects of logged out players */
	if (!objectp(find_player(item->query_prop(SEAMSTRESS_S_CLIENT))))
	{
		item->remove_object();
		return 0;
	}
	return (item->query_prop(SEAMSTRESS_S_CLIENT) == client);
}

/**********************************************************************
 * - Function name : format_seamstress_option                       - *
 * - Description   : formats an option list in rows                 - *
 * - Arguments     : string  - options header                       - *
 * -                 string* - a string list                        - *
 * -                 int     - field size                           - *
 * -                 int     - amount of rows                       - *
 * - Returns       : string  - string fomated in rows               - *
 **********************************************************************/

string
format_seamstress_option(string header, string *option, int fields, int rows)
{
	int     amount = sizeof(option), length, n = -1;
	string  output = "";
	
	fields -= (fields % rows);
	length  = (fields / rows);
	
	output += sprintf("%-*s\n", fields, "");
	output += sprintf("%|*s\n", fields, "- " + header + " -");
	
	while (++n < amount)
	{
		output += sprintf("%-*s", length, option[n]);
		if (!((n + 1) % rows)) output += "\n";
	}
	if (n % rows)
	output += sprintf("%-*s\n", (rows-(n % rows))*length, "");
	return (" | " + implode(explode(output, "\n"), " | \n | ") + " |\n");
}

/**********************************************************************
 * - Function name : add_seamstress_clothing                        - *
 * - Description   : sets options list for the clothing aspect,     - *
 * -                 player will be promted later to choose one of  - * 
 * -                 these options, the function should be called   - *
 * -                 several times with different aspects and       - *
 * -                 options for same clothing type                 - *
 * - Arguments     : string  - clothing type, like "cap"            - *
 * -                 string  - aspect name, like "fabric"           - *
 * -                 string* - option list, like                    - *
 * -                 ({"felt", "leather"})                          - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
add_seamstress_clothing(string clothing, string aspect, string *option)
{
    if (!strlen(clothing) || !strlen(aspect) || !sizeof(option))  return;

    if (!mappingp(seamstress_clothing[clothing])) seamstress_clothing[clothing] = ([]);

    seamstress_clothing[clothing][aspect] = option;
}

/**********************************************************************
 * - Function name : query_seamstress_clothing                      - *
 * - Description   : returns information stored in clothing mapping - *
 * - Arguments     : string  - clothing type, if 0 returns outer    - *
 * -                 mapindices                                     - *
 * -                 aspect  - aspect name, if 0 returns inner map  - *
 * -                 indices                                        - *
 * - Returns       : string* - array of outer/inner map indices or  - *
 * -                 options                                        - *
 **********************************************************************/

varargs string*
query_seamstress_clothing(string clothing = 0, string aspect = 0)
{
	mapping data = seamstress_clothing;
	if (!clothing)
	return (m_sizeof(data) ? m_indices(data) : ({}));
	if (!aspect)
	return (data[clothing]  ? m_indices(data[clothing]) : ({}));
	return (data[clothing][aspect] ? data[clothing][aspect] : ({}));
}

/**********************************************************************
 * - Function name : add_seamstress_design                          - *
 * - Description   : adds information to the seamstress design      - *
 * -                 record                                         - *
 * - Arguments     : mixed   - client name or object                - *
 * -                 string  - aspect name                          - *
 * -                 string  - option                               - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

nomask void
add_seamstress_design(mixed client, string aspect, string option)
{
	client = objectp(client) ? client->query_real_name() : client;
	if (!client || !strlen(aspect) || !strlen(option)) 
	return;
	if (!mappingp(seamstress_design[client])) seamstress_design[client] = ([]);
	seamstress_design[client][aspect] = option;
}

/**********************************************************************
 * - Function name : remove_seamstress_design                       - *
 * - Description   : removes design or design aspect from the       - *
 * -                 records                                        - *
 * - Arguments     : mixed   - client name or object                - *
 * -                 string  - aspect, if 0 whole the design        - *
 * -                 removed                                        - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

nomask varargs void
remove_seamstress_design(mixed client, string aspect = 0)
{
	client = objectp(client) ? client->query_real_name() : client;
	if (!aspect)
	{
		seamstress_design = m_delete(seamstress_design, client);
		return;
	}
	if (seamstress_design[client])
	seamstress_design[client] = m_delete(seamstress_design[client], aspect);
}

/**********************************************************************
 * - Function name : query_seamstress_design                        - *
 * - Description   : returns information stored in the seamstress   - *
 * -                 design map                                     - *
 * - Arguments     : mixed   - client name or object, if 0 indices  - *
 * -                 returned                                       - *
 * -                 string  - requested aspect, if 0 subindices    - *
 *                   returned                                       - *
 * - Returns       : mixed   - information stored under the aspect  - *
 **********************************************************************/

nomask varargs mixed
query_seamstress_design(mixed client = 0, string aspect = 0)
{
	mapping data = seamstress_design;
	object  player;
	string *member = m_indices(seamstress_design);
	int     n      = sizeof(member);
	/* an oportunity to clean up the junk records */
	while (--n >= 0)
	{
		player = find_player(member[n]);
		if (!objectp(player) || (ENV(player) != ENV(TO)))
		remove_seamstress_design(member[n]);
	}
	client = objectp(client) ? client->query_real_name() : client;
	if (!client)
	return (m_sizeof(data) ? m_indices(data) : 0);
	if (!aspect)
	return (data[client]   ? m_indices(data[client]) : 0);
	return (data[client][aspect] ? data[client][aspect] : 0);
}

/**********************************************************************
 * - Function name : add_seamstress_repository                      - *
 * - Description   : adds produced object into the seamstress       - *
 * -                 repository                                     - *
 * - Arguments     : mixed   - client name/object                   - *
 * -                 object  - clothing                             - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

nomask void
add_seamstress_repository(mixed client, object item)
{
	client = objectp(client) ? client->query_real_name() : client;
	if (!objectp(seamstress_repository)) create_seamstress_repository();
	item->add_prop(SEAMSTRESS_S_CLIENT, client);
	item->move(seamstress_repository, 1);
}

/**********************************************************************
 * - Function name : query_seamstress_repository                    - *
 * - Description   : returns contents of ready production stock     - *
 * - Arguments     : mixed   - the client, if 0 whole the stock     - *
 * -                 returned                                       - *
 * - Returns       : object* - client products or all the products  - *
 **********************************************************************/

nomask varargs object*
query_seamstress_repository(mixed client = 0)
{
	object *item;
	if (!objectp(seamstress_repository)) create_seamstress_repository();
	item = INV(seamstress_repository);
	if (client)
	{
		client = objectp(client) ? client->query_real_name() : client;
		item = filter(item, &filter_seamstress_repository(, client));
	}
	return item;
}

/**********************************************************************
 * - Function name : set_seamstress_crafts                          - *
 * - Description   : sets seamstress busy flag making him busy or   - *
 * -                 unbusy                                         - *
 * - Arguments     : int     - 1 means busy, 0 means not busy       - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
set_seamstress_crafts(int number)
{
	seamstress_crafts = number;
}

/**********************************************************************
 * - Function name : query_seamstress_crafts                        - *
 * - Description   : checks if the seamstress is busy making an     - *
 * -                 order                                          - *
 * - Arguments     : none    - no arguments                         - *
 * - Returns       : int     - 1 means busy, 0 means not busy       - *
 **********************************************************************/

int
query_seamstress_crafts()
{
	return seamstress_crafts;
}

/**********************************************************************
 * - Function name : query_seamstress_config                        - *
 * - Description   : returns seamstress default clothing, cloth     - *
 * -                 config the settings are configured under       - *
 * -                 SEAMSTRESS_CLOTHING and SEAMSTRESS_FABRICS     - *
 * - Arguments     : string  - the type clothing, or fabric         - *
 * -                 string  - the clothing/fabric name             - *
 * - Returns       : mixed   - array of default settings for the    - *
 * -                 name                                           - *
 **********************************************************************/

mixed
query_seamstress_config(string type, string name)
{
	if (type == "clothing")
	return SEAMSTRESS_CLOTHING[name];
	if (type ==   "fabric")
	return SEAMSTRESS_FABRICS[name];
	return ({});
}

/**********************************************************************
 * - Function name : seamstress_answer_dark_room                    - *
 * - Description   : refuse to deal with player when the room is    - *
 * -                 dark                                           - *
 * - Arguments     : void    - no arguments                         - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_answer_dark_room()
{
	command("say Who turned out the lights?");
	command("say It's a bit too dark for me to do business.");
	return 1;
}

/**********************************************************************
 * - Function name :  seamstress_answer_invisible                   - *
 * - Description   : refuse to deal with player when cant see him   - *
 * - Arguments     : void    - no arguments                         - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_answer_invisible()
{
	command("say Ok enough of this, where are you hiding? "+
	"I can't see you!");
	command("peer suspiciously");
	return 1;
}

/**********************************************************************
 * - Function name : seamstress_check_faulty_syntax                 - *
 * - Description   : called when check syntax is wrong              - *
 * - Arguments     : string  - argument writen by the player        - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_check_faulty_syntax(string letter)
{
	if (!letter)
	{
		notify_fail(CAP(query_verb()) + " what?\n");
		return 0;
	}
	command("say What would you like to check? Clothing or orders?");
	command("confused");
	return 1;
}

/**********************************************************************
 * - Function name : seamstress_check_clothing_check                - *
 * - Description   : shows a list of clothings or specific clothing - *
 * -                 attributes                                     - *
 * - Arguments     : string  - argument written by the player       - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_check_clothing_check(string clothing)
{
	int     n = -1,  amount;
	string  output, *aspect, *option;
	if ((clothing == "clothings") || (clothing == "clothing"))
	{
		command("say Yes, yes you come to the right place. I "+
		"am an expert seamstress.");
		command("say I can make any of these clothes for you:");
		command("say " + CAP(COMPOSITE_WORDS(query_seamstress_clothing())) +".");
		command("say You can check each one of these clothes "+
		"and I will gladly tell you more.");
		command("smile .");
		return 1;
	}
	command("nod " + OB_NAME(TP));
	command("emote reaches inside her apron pocket and takes "+
	"out a notebook.");
	command("emote starts to list the notebook.");
	command("say Ahh here it is! My " + clothing + " notebook!");
	TP->catch_msg(QCTNAME(TO) +" shows the notebook to you.\n");
	say(QCTNAME(TO)+" shows the notebook to "+QTNAME(TP)+".\n");
	aspect = query_seamstress_clothing(clothing);
	amount = sizeof(aspect);
	output = sprintf(" o%'-'|62so\n", "oooO  "+CAP(clothing)+
             " Ordering  Oooo");
             while (++n < amount)
             {
		     option  = query_seamstress_clothing(clothing, aspect[n]);
		     output += format_seamstress_option(aspect[n], option, 60, 3);
	     }
	     output += sprintf(" o%'-'|62so\n", "oooOOooo");
	     TP->more(output);
	     return 1;
}

/**********************************************************************
 * - Function name : seamstress_check_repository_check              - *
 * - Description   : shows the ready for collection clothing        - *
 * - Arguments     : string  - argument writen by the player        - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_check_repository_check(string letter)
{
	int     size;
	object *item = query_seamstress_repository(TP);
	command("say " + CAP(letter) + "? Ahh your orders!");
	command("emote checks over the racks.");
	if (size = sizeof(item))
	{
		command("say " + CAP(COMPOSITE_DEAD(item)) + (size==1 ? " is" : 
               " are") + " awaiting for your coppers!");
               command("grin merrily");
               command("say You can always 'pay' and take your items.");
               return 1;
         }
         command("say Hmm... Nothing I see in the racks is yours.");
            return 1;
}

/**********************************************************************
 * - Function name : seamstress_select_faulty_syntax                - *
 * - Description   : called when select syntax is wrong             - *
 * - Arguments     : string  - argument writen by the player        - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_select_faulty_syntax(string letter)
{
	notify_fail(CAP(query_verb()) + " what?\n");
	return 0;
}

/**********************************************************************
 * - Function name : seamstress_select_notify_busy                  - *
 * - Description   : called when seamstress is busy with a          - *
 * -                 selection                                      - *
 * - Arguments     : void    - no arguments                         - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_select_notify_busy()
{
	command("say I am currently busy with an order. Just wait a "+
	"moment please.");
	command("smile " + OB_NAME(TP));
	return 1;
}

/**********************************************************************
 * - Function name : seamstress_select_notify_header                - *
 * - Description   : writes a header for clothing selection         - *
 * - Arguments     : string  - argument writen by the player        - *
 * -                 clothing                                       - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
seamstress_select_notify_header(string letter)
{
	command("say Excellent! You may 'cancel order' at any time.");
}

/**********************************************************************
 * - Function name : seamstress_select_notify_prompt                - *
 * - Description   : writes a prompt with aspect and options to     - *
 * -                 choose                                         - *
 * - Arguments     : string  - aspect name                          - *
 * -                 string* - option list                          - *  
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
seamstress_select_notify_prompt(string aspect, string *option)
{
	command("say What kind of " + aspect + " would you like?");
	command("say I have the following "+LANG_PWORD(aspect)+" available:");
	command("say " + CAP(COMPOSITE_WORDS(option)) + ".");
}

/**********************************************************************
 * - Function name : seamstress_select_faulty_option                - *
 * - Description   : called when player selects unproper option     - *
 * - Arguments     : string  - the unproper option                  - *
 * -                 string  - aspect name                          - *
 * -                 string* - option list                          - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
seamstress_select_faulty_option(string letter, string aspect,
    string *option)
{
	command("say Hmm I dont have " + aspect + " named " + letter + ".");
	command("say Or mayhaps you wanted to 'cancel order'?");
	command("confused");
}

/**********************************************************************
 * - Function name : seamstress_select_notify_cancel                - *
 * - Description   : called when player cancels the selection       - *
 * - Arguments     : void    - no arguments                         - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
seamstress_select_notify_cancel()
{
	write("You decide to cancel your order.\n");
	say(QCTNAME(TP) + " cancels " + TP->query_possessive() + " order.\n");
	command("say Next, please!");
}

/**********************************************************************
 * - Function name : seamstress_select_create_clothing              - *
 * - Description   : called to create and configure seamstress made - *
 * -                 clothing                                       - *
 * - Arguments     : mapping - the design mapping                   - *
 * - Returns       : object  - clothing object                      - *
 **********************************************************************/

object
seamstress_select_create_clothing(mapping design)
{
	string  atype   = design["type"] ,   consr  = design["pattern"],
	        fabric  = design["fabric"],  color  = design["color"],
	        linin   = design["lining"],  ornam  = design["ornament"];
	mixed   config  = query_seamstress_config("clothing", consr),
	        fabrics = query_seamstress_config("fabric" , fabric);
	string  prep    = "is";
	object  item;
	setuid(); seteuid(getuid());
	item = clone_object(CLOTHING_PATH);
	item->set_at(config[0]);
	item->set_ac(ftoi(fabrics[0] * itof(config[1])));
	item->set_am(config[2]);
	item->set_likely_cond(ftoi(fabrics[1] * 2.0));
	item->add_prop(OBJ_I_WEIGHT, ftoi(fabrics[2] * itof(
          F_WEIGHT_DEFAULT_ARMOUR(item->query_ac(), item->query_at()))));
        item->add_prop(OBJ_I_VOLUME, config[3]);
        item->add_prop(OBJ_I_VALUE , ftoi(fabrics[3] * itof(
          F_VALUE_ARMOUR(item->query_ac()))));
        item->set_name(({consr, atype}));
        item->set_adj(({ ornam ? ornam : color, ornam ? color : fabric }));
        item->set_short(implode(item->query_adjs()[0..1], " ") + " " + 
        item->query_name());
        if (member_array(item->query_at(),({A_ARMS, A_HANDS, A_LEGS,
        A_FEET})) >= 1)
        {
		prep = "are";
		item->set_pshort("pairs of " + item->query_short());
		item->set_short("pair of " + item->query_short());
	}
	item->set_long(CAP(LANG_ADDART(item->query_short())) + ".\n");
	return item;
}

/**********************************************************************
 * - Function name : seamstress_select_notify_create                - *
 * - Description   : called when player finishes selecting, this    - *
 * -                 hook is self calling, which is made to allow   - *
 * -                 item creating emotions; inspite the theory     - *
 * -                 item  is not completed at the end of           - *
 * -                 seamstress creating emotions, but before;      - *
 * -                 so this hook accepts already made clothing     - *
 * - Arguments     : object  - the object of player who ordered     - *
 * -                 object  - the already comfigured clothing      - *
 * -                 mapping - the player design (messaging)        - *
 * -                 int     - the counter, first time its 0        - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
seamstress_select_notify_create(object client, object item, 
    mapping design, int counter)
{
	string fabric = design["fabric"], 
	name  = design["pattern"];
	switch (counter)
	{
		case 0: command("say Excellent! I will start sewing "+
		"this at once.");
		command("emote takes a large piece of " + fabric + " "+
		"from a large round rack.");
                break;
                case 1: command("emote puts a piece of " + fabric + " "+
                "onto a large counter top, using a special pair of "+
                "shears begins to cut out a pattern in the "+
                "" + fabric +".");
                break;
                case 2: command("emote removes the pieces of "+
                "" + fabric + " from the table then neatly pins them "+
                "in place on a dress form made from cotton and wool.");
                break;
                case 3: command("emote takes a spool of thread and a "+
                "needle then begins to work on the pieces of fabric "+
                "creating a somewhat coarse shape of a " +name+".");
                break;
                case 4: command("emote rotates the dress form back "+
                "and forth as "+this_player()->query_pronoun()+" lets "+
                ""+this_player()->query_objective() +" fingers "+
                "caress the " + fabric + " taking a good study of it "+
                "before "+this_player()->query_pronoun()+" proceeds.");
                break;
                case 5: command("emote does some finishing work and "+
                "stitches a small tag on the " + fabric + " "+
                "" + name + ".");
                break;
                case 6: command("emote finishes creating "+LANG_THESHORT(item)+".");
                command("emote puts "+LANG_THESHORT(item)+" in the rack.");
                break;
    }

    if (counter < 6)
    {
	    /* we call this hook again with a greater counter */
	    set_alarm(4.0, 0.0,  &seamstress_select_notify_create(client, item, design, ++counter));
	    return;
    }

    if (ENV(client) == ENV(TO))
    {
	    command("say Wonderful that you are here!");
	    command("say Your " + item->short() + " is now finished.");
	    command("say You can 'pay for "+item->query_name()+"' to "+
	    "get it.");
    }
    else
    {
	    tell_object(client, "A short-haired little girl arrives.\n");
	    tell_object(client, "The short-haired little girl says to "+
	    "you: Your " + item->query_short() + " is now finished.\n");
	    tell_object(client, "The short-haired little girl skips "+
	    "away.\n");
    }
    /* the following function must be called at the end of the process */
    TO->finish_seamstress_select(client, item); 
}


/**********************************************************************
 * - Function name : seamstress_obtain_faulty_syntax                - *
 * - Description   : called when player tries to obtain a wrong     - *
 * -                 item                                           - *
 * - Arguments     : string  - argument writen by the player        - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_obtain_faulty_syntax(string letter)
{
	notify_fail(CAP(query_verb()) + " for what?\n");
	return 0;
}

/**********************************************************************
 * - Function name : seamstress_obtain_cannot_afford                - *
 * - Description   : called when player cannot afford the order     - *
 * - Arguments     : object* - items player tried to obtain         - *
 * -                 int     - total price of the items             - *
 * - Returns       : int     - 0 for notify_fail or 1 for anything  - *
 * -                 else                                           - *
 **********************************************************************/

int
seamstress_obtain_cannot_afford(object *item, int cost)
{
	command("say So you want " + COMPOSITE_DEAD(item) + "?");
	command("smile .");
	command("say Then you better bring money first!");
	command("say No money - no deal!");
	return 1;
}

/**********************************************************************
 * - Function name : seamstress_obtain_notify_obtain                - *
 * - Description   : called if player succesfully obtained items,   - *
 * -                 note that this hook must actually deliver the  - *
 * -                 items to the player                            - *
 * - Arguments     : object* - items player obtained                - *
 * -                 int*    - array of coins payed by the player   - *
 * -                 int*    - array of coins player got back       - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
seamstress_obtain_notify_obtain(object *item, int *charge, int* change)
{
	int     n = sizeof(item);
	TP->catch_msg("You pay " + QTNAME(TO) + " " + text(charge) + ".\n");
	if (strlen(text(change))) write("You get "+text(change)+" back.\n");
	item->move(TO, 1);
	while (--n >= 0)
	{
		command("give " + OB_NAME(item[n]) + " to " + OB_NAME(TP));
		if (ENV(item[n]) == TO)
		{
			command("say You dont seem to be able to "+
			"carry the "+ item[n]->short()+".");
			command("drop " + OB_NAME(item[n]));
			while (--n >= 0) command("drop " + OB_NAME(item[n]));
		}
	}
}

/**********************************************************************
 * - Function name : action_seamstress_check                        - *
 * - Description   : handles browsing of the selection options and  - *
 * -                 repository                                     - *
 * - Arguments     : string  - argument written by the player       - *
 * - Returns       : int     - 1 for success or 0 for failure       - *
 **********************************************************************/

int
action_seamstress_check(string text)
{
	string *clothing = query_seamstress_clothing(), 
	*repository = ({"orders", "order"}), stxt;
	if (!text) return seamstress_check_faulty_syntax(text);
	say(QCTNAME(TP)+" inquires "+QTNAME(TO)+" for "+LANG_ADDART(text)+
        ".\n");
        TP->catch_msg("You inquire "+QTNAME(TO)+" for "+LANG_ADDART(text)+
        ".\n");
        if (!CAN_SEE_IN_ROOM(TO))
        return seamstress_answer_dark_room();
        if (!CAN_SEE(TO, TP))
        return seamstress_answer_invisible();
        if (query_seamstress_design(TP)) remove_seamstress_design(TP);
        if (query_seamstress_design() || query_seamstress_crafts())
        return seamstress_select_notify_busy();
        if (sizeof(clothing)) clothing += ({"clothings", "clothing"});
        stxt = LANG_SWORD(text);
        if (member_array(text, clothing) >= 0)
        return seamstress_check_clothing_check(text);
        if (member_array(stxt, clothing) >= 0)
        return seamstress_check_clothing_check(stxt);
        if (member_array(text, repository) >= 0)
        return seamstress_check_repository_check(text);
        return seamstress_check_faulty_syntax(text);
}

/**********************************************************************
 * - Function name : finish_seamstress_select                       - *
 * - Description   : makes the final arrangements for ordered       - *
 * -                 object                                         - *
 * - Arguments     : object  - the client                           - *
 * -                 object  - the object                           - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
finish_seamstress_select(object client, object item)
{
	set_seamstress_crafts(0);
	if (!objectp(client))
	{
		item->remove_object();
		return;
	}
	add_seamstress_repository(client, item);
}

/**********************************************************************
 * - Function name : prompt_seamstress_select                       - *
 * - Description   : loops the input of player                      - *
 * - Arguments     : int     - module clothing                      - *
 * -                 string  - clothing/ type                       - *
 * -                 int     - order counter                        - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
prompt_seamstress_select(int module, string type, int spot)
{
	object  item;
	string  aspect, *option = ({});
	mapping design = ([]);
	if (!sizeof(query_seamstress_design(TP))) return;
	switch (module)
	{
		case MODULE_CLOTHING: design = seamstress_clothing[type]; break;
	}
	if (spot >= sizeof(m_indices(design)))
	{
		if (!objectp(TP) || (ENV(TP) != ENV(TO)))
		return remove_seamstress_design(TP);
		design = ([]) + seamstress_design[TP->query_real_name()];
		setuid(); seteuid(getuid());
		if (module == MODULE_CLOTHING) 
		item = seamstress_select_create_clothing(design);
		remove_seamstress_design(TP);
		set_seamstress_crafts(1);
		return seamstress_select_notify_create(TP, item, design, 0);
	}
	aspect = sort_array(m_indices(design))[spot];
	option = design[aspect];
	seamstress_select_notify_prompt(aspect, option);
	write(":");
	input_to(&TO->record_seamstress_select(, module, type, spot));
}

/**********************************************************************
 * - Function name : record_seamstress_select                       - *
 * - Description   : prompts the player to selection of clothing    - *
 * -                 attributes                                     - *
 * - Arguments     : string  - argument writen by the player        - *
 * -                 int     - module clothing                      - *    
 * -                 string  - clothing type                        - *
 * -                 int     - order counter                        - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
record_seamstress_select(string letter, int module, string type, int spot)
{
	string  aspect, *option = ({});
	mapping design = ([]);
	if ((ENV(TP) != ENV(TO)) || wildmatch("cancel*", letter))
	{
		/* selection was canceled from some reason */
		if (ENV(TP) == ENV(TO)) seamstress_select_notify_cancel();
		return remove_seamstress_design(TP);
	}
	switch (module)
	{
		case MODULE_CLOTHING: design = seamstress_clothing[type]; break;
	}
	if (!strlen(letter))
	{
		write(":");
		input_to(&record_seamstress_select(, module, type, spot));
		return;
	}
	TP->catch_msg("You say to " + QTNAME(TO) + ": " + letter + ".\n");
	say(QCTNAME(TP)+" says to " + QTNAME(TO) + ": " + letter + ".\n");
	aspect = sort_array(m_indices(design))[spot];
	option = design[aspect];
	if (member_array(letter, option) < 0)
	{
		seamstress_select_faulty_option(letter, aspect, option);
		write(":");
		input_to(&record_seamstress_select(, module, type, spot));
		return;
	}
	add_seamstress_design(TP, aspect, letter);
	prompt_seamstress_select(module, type, ++spot);
}

/**********************************************************************
 * - Function name : action_seamstress_select                       - *
 * - Description   : handles clothing ordering                      - *
 * - Arguments     : string  - argument written by the player       - *
 * - Returns       : int     - 1 for success or 0 for failure       - *
 **********************************************************************/

public int
action_seamstress_select(string text)
{
	int     module;
	string *clothing=query_seamstress_clothing();
	if (!text)
	return seamstress_select_faulty_syntax(text);
	else if (member_array(text, clothing) >= 0) module = MODULE_CLOTHING;
	else
	return seamstress_select_faulty_syntax(text);
	say(QCTNAME(TP)+" asks "+QTNAME(TO)+" for "+LANG_ADDART(text)+ ".\n");
	TP->catch_msg("You ask "+QTNAME(TO)+" for "+LANG_ADDART(text)+ ".\n");
	if (!CAN_SEE_IN_ROOM(TO))
	return seamstress_answer_dark_room();
	if (!CAN_SEE(TO, TP))
	return seamstress_answer_invisible();
/**********************************************************************
 * - This is a security feature , for example player linkdied in    - *
 * - the middle of selection process and seamstress_design still    - *
 * - contains his record, in such a case we remove the record       - *
 **********************************************************************/
        if (query_seamstress_design(TP)) remove_seamstress_design(TP);

/**********************************************************************    
 * - Checking if someone already ordering, query_seamstress_design()- *
 * - will clean up the junk records and return true only if someone - *
 * - really orders something at the moment                          - *
 **********************************************************************/

       if (query_seamstress_design() || query_seamstress_crafts())    
       return seamstress_select_notify_busy();
       add_seamstress_design(TP, "type", text);
       seamstress_select_notify_header(text);
       prompt_seamstress_select(module, text, 0);
       return 1;
}
/**********************************************************************
 * - Function name : action_seamstress_obtain                       - *
 * - Description   : handles attempts to pay for ready clothing     - *
 * - Arguments     : string  - argument written by the player       - *
 * - Returns       : int     - 1 for success or 0 for failure       - *
 **********************************************************************/

public int
action_seamstress_obtain(string text)
{
	int     cost = 0, *coin, n, *charge, *change;
	string  what;
	object *item;
	if (!text || !parse_command(text, ({}), "'for' [the] %s", what) ||        !(n=sizeof(item=FIND_STR_IN_ARR(what,query_seamstress_repository(TP)))))
	return seamstress_obtain_faulty_syntax(text);
	say(QCTNAME(TP) + " asks " + QTNAME(TO) + " to give " + 
        TP->query_possessive() + " " + COMPOSITE_DEAD(item) + ".\n");
        TP->catch_msg("You ask " + QTNAME(TO) + " to give you " +
        COMPOSITE_DEAD(item) + ".\n");
        if (!CAN_SEE_IN_ROOM(TO))
        return seamstress_answer_dark_room();
        if (!CAN_SEE(TO, TP))
        return seamstress_answer_invisible();
        if (query_seamstress_design(TP)) remove_seamstress_design(TP);
        if (query_seamstress_design() || query_seamstress_crafts())
        return seamstress_select_notify_busy();
        while (--n >= 0)  cost += OBTAIN_COST(item[n]);
        if (sizeof(coin = pay(cost, TP, 0, 0, 0, 0, 1)) == 1)
        return seamstress_obtain_cannot_afford(item, cost);
        charge = coin[0..(SIZEOF_MONEY_TYPES - 1)];
        change = coin[SIZEOF_MONEY_TYPES..(2*SIZEOF_MONEY_TYPES - 1)];
        item->remove_prop(SEAMSTRESS_S_CLIENT);
        seamstress_obtain_notify_obtain(item, charge, change);
        return 1;
}

/**********************************************************************
 * - Function name : init_seamstress                                - *
 * - Description   : adds seamstress actions to the environment     - *
 * - Arguments     : void    - no arguments                         - *
 * - Returns       : void    - nothing is returned                  - *
 **********************************************************************/

void
init_seamstress()
{
	/* the following commands available only if seamstress has stock */
	if (sizeof(query_seamstress_clothing()))
	{
		add_action(action_seamstress_check,   "check");
		add_action(action_seamstress_select,  "order");
		add_action(action_seamstress_obtain,    "pay");
	}
}
