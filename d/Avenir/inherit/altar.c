// file name:   /d/Avenir/inherit/altar.c
// creator(s):  Lilith, March '97
// revision(s): 
//              Lilith, Aug 2014 added ability to offer drink to the gods
//              Lucius, Aug 2016: Reduced 'drinking' benefit, 4 hours is WAY
//                                too generous.
//              Lilith, Aug 2021: updated "offer", fixed some flavor text.             
//
// purpose:     Standard inheritable object for altars to Sybarite Gods
// note:        For working example, see /holm/obj/b_altar.c
//          Special offerings:
//              Modified the function do_offer() to check for the 
//              prop SPECIAL_OFFERING in offered objects. If true
//              the function altar_special(object altar) is called 
//              in the offered object.
// bug(s):           
// to-do: Tep has an idea re: offerings -- eventually have it so that 
// priests can (for a fee of course) bless or cleanse an item to make 
// it an acceptible offering.

inherit  "/std/object";

#include "/d/Avenir/include/deities.h"   /* Altar & diety-related defines */
#include "/d/Avenir/include/relation.h"  /* Sybarite status defines */
#include <composite.h>
#include <cmdparse.h> 
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#define  TP this_player()
#define  TO this_object()

/* Variables */
int    id_task,       /* The resolve_task result for id_altar_check */
       hour,          /* The number of the Hour */
       offer_max,     /* The maximum number of offerings at one time */
       offer_num;     /* The current number of offerings */

string altar,         /* The unique name of the altar */
       diety,         /* The name of the god of the altar */
       short_desc,    /* The base desc for the set_short */
       id_long,       /* The long desc for identified altar */
       unid_long;     /* The long desc for unidentified altar */

string *bless_cmds,   /* Commands to bless/sanctify the altar */
       *defile_cmds,  /* Commands used to defile the altar */
       *destroy_cmds, /* Commands used to destroy the altar */ 
       *disman_cmds,  /* Commands used to dismantle the altar */
       *pray_cmds,    /* Commands to pray or worship at altar */
       *offer_cmds,   /* Commands to make offerings at altar */
       *worship_cmds, /* Commands to worship at the altar */
       *offer_shorts, /* Short descs of offerings */
       *offer_bloody; /* Short descs of blood offerings */    

mixed  oprop;         /* The name(s) of acceptible offerings props */

/*
 * Function name: id_altar_check
 * Description:   Called to check if player identifies the altar.
 * Arguments:	  player - The player
 * Returns:       1 for identification, else 0.
 */
varargs int
id_altar_check(object player)
{
    if (!objectp(player))
        player = this_player();

    /* Sybarites have a slightly better chance of id-ing it */
    id_task = player->resolve_task(TASK_ROUTINE, ({TS_INT, SS_AWARENESS}));
    if (objectp(player) && ( (id_task > 25) || (IS_SYBARITE(player) && 
        id_task > 0) ))
        return 1;
    else
        return 0;
}

/*
 * Function name: set_id_long
 * Description:   Set the long description you see if you know
 *                what altar it is.
 * Arguments:     str - The description
 */
void
set_id_long(string str) { id_long = str; }

/*
 * Function name: query_id_long
 * Description:   The long description if you can id the altar
 * Returns:       The long description
 */
string
query_id_long() { return id_long; }

/*
 * Function name: set_unid_long
 * Description:   Set the long description you see if you cannot 
 *		      identify the altar.
 * Arguments:     str - The long description
 */
void
set_unid_long(string str) { unid_long = str; }

/*
 * Function name: query_unid_long
 * Description:   Query the long description you get if you cannot 
 *                identify the altar
 * Returns:       The unidentified long description
 */
string
query_unid_long() { return unid_long; }

/*
 * Function name: set_altar_short
 * Description:   Set the short desc of the altar
 * Arguments:     str - The description
 */
void
set_altar_short(string str) { short_desc = str; }

/*
 * Function name: query_altar_short
 * Description:   What is the short description?
 * Returns:       The short description
 */
string
query_altar_short() { return short_desc; }

/*
 * Function name:  set_god
 * Description:    Set the name of the god to whom the altar is erected
 * Arguments:      str - The god's name
 */   
void   
set_god(string str) { diety = str;}

/*
 * Function name:  query_god
 * Description:    What is the name of the god of this altar
 * Returns:	   diety - The god's name
 */   
string 
query_god() { return diety; }

/*
 * Function name:  set_altar_hour
 * Description:    Set the Hour the God/Altar belongs to, if any.
 * Arguments:      i - The Hour
 */   
void
set_altar_hour(int i) { hour = i; }

/*
 * Function name:  query_altar_hour
 * Description:    What is the Hour of the god of this altar
 * Returns:        The Hour
 */   
int 
query_altar_hour() { return hour; }

/*
 * Function name:  set_offer_max
 * Description:    Set the maximum number of offerings on the altar
 * Arguments:      i - The max number
 */   
void
set_offer_max(int i) { offer_max = i; }

/*
 * Function name:  query_offer_max
 * Description:    What is the maximum number if offerings permitted
 * Returns:        The max number
 */   
int 
query_offer_max() { return offer_max; }

/*
 * Function name:  add_offer_short
 * Description:    Set the short(s) for offerings on the altar
 * Arguments:      shorts - The short(s) for the offerings
 */   
void
add_offer_short(mixed shorts)
{
    if (!query_prop(ALTAR_IS_OFFERING))
        add_prop(ALTAR_IS_OFFERING,  1);

    if (pointerp(shorts))
        offer_shorts += shorts;
    else
        offer_shorts += ({ shorts });
}

/*
 * Function name:  query_offer_short()
 * Description:    Get the short(s) for offerings on the altar
 * Returns:        The short(s)
 */   
string *
query_offer_short() { return offer_shorts; }

/*
 * Function name:  add_offer_bloody
 * Description:    Set the short(s) for blood-offerings on the altar
 * Arguments:      shorts - The short(s) for the blood-offerings
 */   
void
add_offer_bloody(mixed shorts)
{
    if (pointerp(shorts))
        offer_bloody += shorts;
    else
        offer_bloody += ({ shorts });
}

/*
 * Function name:  query_offer_bloody()
 * Description:    Get the short(s) for offerings on the altar
 * Returns:        The short(s)
 */   
string *
query_offer_bloody() { return offer_bloody; }

/*
 * Function name:  set_altar_name
 * Description:    Set the true name of the altar
 * Arguments:      str - The altar name
 */   
void
set_altar_name(string str) { altar = str; }   

/*
 * Function name:  query_altar_name
 * Description:    Get the true name of the altar
 * Returns:        The altar name
 */   
string
query_altar_name() { return altar; }

/*
 * Function name:  set_offering_prop
 * Description:    Set the 'acceptable offerings' prop.
 *                 (prop defines will be in the deities.h file)
 * Arguments:      str - The property
 */   
mixed
set_offering_prop(mixed prop) 
{ 
    if (pointerp(prop))
        oprop = prop;
    else
        oprop = ({ prop });
}

/*
 * Function name:  query_offering_prop()
 * Description:    Get the 'acceptable offerings' prop
 * Returns:        The property
 */   
mixed
query_offering_prop() { return oprop; }

/*
 * Function name:  set_bless_command
 * Description:    Set the command(s) to bless the altar
 * Arguments:      command - The command(s)
 */   
void
set_bless_command(mixed command)
{
    if (pointerp(command))
        bless_cmds = command;
    else
        bless_cmds = ({ command });
}

/*
 * Function name:  query_bless_command()
 * Description:    Get the command(s) to bless the altar
 * Returns:        The command(s)
 */   
string *
query_bless_command() { return bless_cmds; }

/*
 * Function name:  set_defile_command
 * Description:    Set the command(s) to defile the altar
 * Arguments:      command - The command(s)
 */   
void
set_defile_command(mixed command)
{
    if (pointerp(command))
        defile_cmds = command;
    else
        defile_cmds = ({ command });
}

/*
 * Function name:  query_defile_command()
 * Description:    Get the command(s) to bless the altar
 * Returns:        The command(s)
 */   
string *
query_defile_command() { return defile_cmds; }

/*
 * Function name:  set_destroy_command
 * Description:    Set the command(s) to destroy the altar
 * Arguments:      command - The command(s)
 */   
void
set_destroy_command(mixed command)
{
    if (pointerp(command))
        destroy_cmds = command;
    else
        destroy_cmds = ({ command });
}

/*
 * Function name:  query_destroy_command()
 * Description:    Get the command(s) to destroy the altar
 * Returns:        The command(s)
 */   
string *
query_destroy_command() { return destroy_cmds; }

/*
 * Function name:  set_dismantle_command
 * Description:    Set the command(s) to dismantle the altar
 * Arguments:      command - The command(s)
 */   
void
set_dismantle_command(mixed command)
{
    if (pointerp(command))
        disman_cmds = command;
    else
        disman_cmds = ({ command });
}

/*
 * Function name:  query_dismantle_command()
 * Description:    Get the command(s) to dismantle the altar
 * Returns:        The command(s)
 */   
string *
query_dismantle_command() { return disman_cmds; }

/*
 * Function name:  set_offer_command
 * Description:    Set the command(s) to make offerings at the altar
 * Arguments:      command - The command(s)
 */   
void
set_offer_command(mixed command)
{
    if (pointerp(command))
        offer_cmds = command;
    else
        offer_cmds = ({ command });
}

/*
 * Function name:  query_offer_command()
 * Description:    Get the command(s) to make offerings at the altar
 * Returns:        The command(s)
 */   
string *
query_offer_command() { return offer_cmds; }

/*
 * Function name:  set_pray_command
 * Description:    Set the command(s) to pray at the altar
 * Arguments:      command - The command(s)
 */   
void
set_pray_command(mixed command)
{
    if (pointerp(command))
        pray_cmds = command;
    else
        pray_cmds = ({ command });
}

/*
 * Function name:  query_pray_command()
 * Description:    Get the command(s) to pray at the altar
 * Returns:        The command(s)
 */   
string *
query_pray_command() { return pray_cmds; }

/*
 * Function name:  set_worship_command
 * Description:    Set the command(s) to worship at the altar
 * Arguments:      command - The command(s)
 */   
void
set_worship_command(mixed command)
{
    if (pointerp(command))
        worship_cmds = command;
    else
        worship_cmds = ({ command });
}

/*
 * Function name:  query_worship_command()
 * Description:    Get the command(s) to worship at the altar
 * Returns:        The command(s)
 */   
string *
query_worship_command() { return worship_cmds; }

/*
 * Function name:  reset_altar()
 * Description:    Reset the offerings so more can be made at intervals
 */   
void
reset_altar() { this_object()->remove_prop(ALTAR_IS_OCCUPIED); }

void
reset_object() { this_object()->reset_altar(); }

/*
 * Function name: my_long
 * Description:   This VBFC tests if the player examining it can
 *                identify it.
 *                Make sure to set_id_long(str) and set_unid_long(str)
 *                from the create_altar() function.
 */
string
my_long()
{
    string str1, str2;

    str1 = "";
    if (query_prop(ALTAR_IS_BLOODY))
        str1 += " It has the corpse of a "+ 
                COMPOSITE_WORDS(query_offer_bloody()) +" on it.";

    str2 = "";
    if (query_prop(ALTAR_IS_OFFERING))
        str2 += " Someone has made the offering of "+ 
                COMPOSITE_WORDS(query_offer_short()) +" on the altar.";

    if (id_altar_check(this_player()))
        return id_long + str2 + str1 +"\n";

    return unid_long + str2 + str1 +"\n";
}

/*
 * Function name: my_short
 * Description:   Tests for certain props before setting the short.
 */
string
my_short()
{
    if (query_prop(ALTAR_IS_BROKEN))
        return "damaged " + short_desc;
    if (query_prop(ALTAR_IS_DEFILED))
        return "defiled " + short_desc;
    if (query_prop(ALTAR_IS_BLOODY))
        return short_desc + " covered in blood";
    return short_desc;
}

/*
 * Function name: create_altar
 * Description:   create the altar object, set default names, etc.
 *                Use this when inheriting this file to create an altar.
 */
public void
create_altar()
{
    ::create_object();

    set_name("altar");

    set_altar_name("unknown");
    set_altar_hour(0);  
    set_god("unknown"); 
    set_altar_short("unknown altar");
   
    /* NOTE: Don't use \n here. It is done in my_long() */
    set_id_long("This is the long description for those who can "+
        "identify this altar.");
    set_unid_long("This is the long description for those who cannot "+
        "identify this altar.");


/*  NOTE: Below, the set_* refers to add_actions. If you want these  
    actions added, you have to set them in your altar file. These      
    are the 'default' commands, and you should review the functions    
    to see if they are suitable. They can be easily redefined for      
    customization of your altar.                                      

    set_bless_command(({"bless", "sanctify"}));
    set_defile_command(({"desecrate", "defile"}));
    set_destroy_command(({"destroy", "break"}));
    set_dismantle_command("dismantle");
    set_offer_command(({"offer", "sacrifice"}));
    set_offering_prop(UNIVERSAL_OFFERING); 
    set_pray_command("pray");
    set_worship_command("worship");
 */     

    add_prop(OBJ_M_NO_GET, "The altar is far too heavy to be gotten.\n");
    

    /* Weight is used in the do_destroy calculations */
    add_prop(OBJ_I_WEIGHT, 110000);
    add_prop(OBJ_I_VOLUME, 70000);

}

/*
 * Function name: create_object
 * Description:   Initialize object.
 */
void
create_object()
{
    bless_cmds = ({ });
    defile_cmds = ({ });
    destroy_cmds = ({ });
    disman_cmds = ({ });
    offer_cmds = ({ });
    pray_cmds = ({ });
    worship_cmds = ({ });
    offer_shorts = ({ });
    offer_bloody = ({ });

    set_name("altar");
  
    create_altar();

    set_short("@@my_short");
    set_long("@@my_long");   

    /* default maximum offerings */
    set_offer_max(20);
}

/*
 * Function name:  do_item_filter
 * Description:    Filter player inventory for wielded weapons.
 * Returns:        0 - if no wielded weapons, 1 - if there are.
 */   
int
do_item_filter(object ob)
{
    if ( (ob->query_wt() != W_KNIFE) && (ob->query_wt() != W_SWORD))
        return 0;
    return objectp(ob->query_wielded());
}

/*
 * Function name:  check_oprop
 * Description:    Check offered object for 'acceptable' property.
 * Returns:        0 - if no prop, 1 - if there is.
 */   
int
check_oprop(object ob)
{   
    return sizeof(filter(oprop, ob->query_prop));
}

/*
 * Function name:  altar_result_pos
 * Description:    Here the message is written when the player
 *                 does something Positive to the altar.
 *                 You may redefine it if you wish, to add things 
 *                 like align adjustments, etc.
 * Arguments:      qvb  - The verb used 
 */
void
altar_result_pos(object pl, string qvb)
{
    pl->catch_msg("A feeling of ecstasy uplifts you, as though you can feel "+ 
        capitalize(query_god()) +"'s pleasure in your actions.\n");
    say(QCTNAME(this_player()) +" appears to be momentarily over"+
        "come with ecstacy.\n");
}

/*
 * Function name:  altar_result_neg
 * Description:    Here the message is written when the player
 *                 does something Negative to the altar.
 *                 You may redefine it if you wish, to add things 
 *                 like align adjustments, etc.
 * Arguments:      qvb  - The verb used 
 */
void
altar_result_neg(object pl, string qvb)
{
    pl->catch_msg("You have the sense of something malignant preying upon "+
        "your mind, as though you have offended the being to whom "+
        "this altar was erected and it is intent upon vengeance.\n");
    say(QCTNAME(this_player()) +" suddenly looks frightened by "+
        this_player()->query_possessive() +" actions, as if "+
        this_player()->query_pronoun() +" fears the consequences.\n");
    WRATHOBJ->load_me();         
    WRATHOBJ->mark_enemy(pl);
}

/*
 * Function name:  pray_text
 * Description:    Here the prayer/worship message is written. 
 *                 You may redefine it if you wish.
 * Arguments:      qvb  - The verb used (pray or worship)
 */
void
pray_text(object pl, string qvb)
{
    string pra;

    if (qvb == "pray")
        pra = "prayer";
    else
        pra = "worship";

    pl->catch_msg("You kneel before the "+ QSHORT(TO) +", pressing your forehead "+
        "against the ground and stretching your arms out toward it.\n");
    say(QCTNAME(this_player()) +" kneels before the "+ QSHORT(TO) +" in "+
        pra +".\n");
}

/*
 * Function name:  do_bless
 * Description:    Default bless/sanctify add_action.
 *                 You may redefine this function if you wish.
 * Arguments:      str - the words after the verb
 */   
int
do_bless(string str)
{
    string qvb;

    qvb = query_verb();    
    (capitalize(qvb) + " what? the altar?\n");
    if (!str || !strlen(str))    
        return 0;
    if (!parse_command(str, ({ }), "[the] 'altar'"))
        return 0;    

    notify_fail("The "+ QSHORT(TO) +" has been damaged. You cannot "+ qvb +
        " it in this condition!\n");
    if (query_prop(ALTAR_IS_BROKEN))
        return 0;

    notify_fail("The altar has been defiled! Only a priest of "+ 
        capitalize(query_god()) +" can "+ qvb +" it in this "+
        "condition.\n");
    if (query_prop(ALTAR_IS_DEFILED))
        return 0;

    write("You are not a priest of "+ capitalize(query_god()) +". "+
        "Your attempt to "+ qvb +" this altar has failed.\n");
    say(QCTNAME(TP) +" attempts to "+ qvb +" the altar, but fails.\n");
    return 1;
}

/*
 * Function name:  do_defile
 * Description:    Default defile add_action.
 *                 You may redefine this function if you wish.
 * Arguments:      str - the words after the verb
 */   
int
do_defile(string str)
{
    string qvb, def;
    object pl = TP;

    qvb = query_verb();    
    notify_fail(capitalize(qvb) + " what? the altar?\n");
    if (!str || !strlen(str))    
        return 0;
    if (!parse_command(str, ({ }), "[the] 'altar'"))
        return 0;    

    notify_fail("The altar is already defiled!\n");
    if (query_prop(ALTAR_IS_DEFILED))
        return 0;

    write("You commit an act of blasphemy by your defilement of the "+ 
        QSHORT(TO) +".\n");
    say(QCTNAME(TP) +" "+ qvb +"s the "+ QSHORT(TO) +".\n");
    add_prop(ALTAR_IS_DEFILED, 1);
    set_id_long(id_long +" It has been defiled.");
    set_unid_long(unid_long +" It has been defiled.");

    /* This func would be a good place to put align adjustments, etc
     * that may result from the player's actions.
     */
    altar_result_neg(pl, qvb);         

    return 1;   
}

/*
 * Function name:  do_destroy
 * Description:    Default destroy add_action
 *                 You may redefine this function if you wish.
 * Arguments:      str - the words after the verb
 */   
int
do_destroy(string str)
{
    int iwt;
    string qvb, des;
    object pl = TP;

    qvb = query_verb();    
    notify_fail(capitalize(qvb) + " what? the altar?\n");
    if (!str || !strlen(str))    
        return 0;
    if (!parse_command(str, ({ }), "[the] 'altar'"))
        return 0;    
    
    notify_fail("The altar is already broken. You cannot "+ qvb +
        " it any more than it already is!\n");
    if (query_prop(ALTAR_IS_BROKEN))
        return 0;

    /* Use a combination of STR and weight to determine of they have 
     * what it takes to break the altar 
     */
    iwt = ((TP->weight() * TP->query_stat(SS_STR)) / 75);
    if (TO->query_prop(OBJ_I_WEIGHT) < iwt)
    {
        write("You visciously "+ qvb +" the altar, deriving great "+
            "pleasure from it.\n");
        say(QCTNAME(TP) +" seems to derive great pleasure from destroy"+
            "ing the altar.\n");
        add_prop(ALTAR_IS_BROKEN, 1);
        set_id_long(id_long +" It has been damaged.");
        set_unid_long(unid_long +" It has been damaged.");

        /* This func would be a good place to put align adjustments, etc
         * that may result from the player's actions.
         */
        altar_result_neg(pl, qvb);         
        return 1;
    }
    write("You do not have the strength to do any serious damage to "+
        "the altar.\n");
    say(QCTNAME(TP) +" doesn't seem to have the strength to damage the "+
        "altar.\n");
    return 1;
}

/*
 * Function name:  do_dismantle
 * Description:    Default dismantle add_action
 *                 You may redefine this function if you wish, 
 *                 making it possible to dismantle the altar 
 *                 into smaller pieces that could be re-assembled.
 * Arguments:      str - the words after the verb
 */   
int
do_dismantle(string str)
{
    write("You cannot dismantle the altar at this time.\n");
    return 0;
}

/*
 * Function name:  do_offer
 * Description:    Default offer/sacrifice add_action
 *                 You may redefine this function if you wish.
 * Arguments:      str - the words after the verb
 */   
int
do_offer(string str)
{
    string qvb, oshort;
    object *obs, *wep, ob;
    object pl = TP;

    qvb = query_verb();    
    notify_fail(capitalize(qvb) + " what?\n");
    if (!str || !strlen(str))    
        return 0;

    notify_fail("The altar has been defiled! You cannot "+ qvb +
        " anything on it in this condition!\n");
    if (query_prop(ALTAR_IS_DEFILED))
        return 0;

    notify_fail("The altar is damaged. You cannot "+ qvb +
        " anything on it in this condition!\n");
    if (query_prop(ALTAR_IS_BROKEN))
        return 0;
    
    notify_fail("No further offerings can be made at the altar.\n");
    if (query_prop(ALTAR_IS_OCCUPIED) >= offer_max)
        return 0;

    notify_fail("The correct syntax is: '"+ qvb +" <item> on the altar', "+
        "or, '"+ qvb +" <item> to <god>'\n");
    if (!parse_command(str, ({ }), 
        "[the] %s 'at' / 'on' [the] 'altar'", str))
    if (!parse_command(str, ({ }), "[the] %s 'to' [the] '"+ query_god() 
        +"'", str))
        return 0;    

    obs = FIND_STR_IN_OBJECT(str, TP);    
    if (!sizeof(obs))
        return 0;

    if (sizeof(obs) > 1)
    {
        write("You cannot "+ qvb +" more than one thing at a time.\n");
        return 1;
    }
    
    notify_fail("You are not certain as to the nature of this altar, "+
        "so you decide not to "+ qvb +" anything after all.\n");
    if (!id_altar_check(this_player()))
        return 0;
       
    ob = obs[0];
	oshort = ob->short();
	
    /* Offer the Gods a drink, get intoxicated */	
	if (ob->query_alco_amount())
	{
		int a, c;
		
		// The Gods don't like sybarites to be drunk unless its at a Revel
		//  So sybarites can't get more than 25% max intox 
		if (IS_SYBARITE(TP))
	   	    c = this_player()->intoxicated_max() / 4;
		else 
	   	    c = this_player()->intoxicated_max();
      
		// Let's do this thing
		a = this_player()->query_intoxicated() + ob->query_alco_amount();

        if (a > c)
		    this_player()->set_intoxicated(c);
		else 
			this_player()->set_intoxicated(a);

		write("Making an offering to "+ capitalize(query_god()) +
			", you pour the drink over the surface of the altar.\n"+
			"You enjoy a heady burst of camaraderie from "+
	    capitalize(query_god()) +" that leaves you tingling with "+
			"intoxication.\nSharing a drink with the gods "+
			"is an amazing feeling.\n");
		say(QCTNAME(TP) +" makes an offering at the altar.\n");       
			 			 
		// Increase offering count in player by one
		TP->add_prop(I_MADE_OFFERING, TP->query_prop(I_MADE_OFFERING) + 1);
			 
		// Increase drinking time, allows 30 - 60 minutes.
		TP->add_prop(I_DRANK_WITH_SYBARUN_GOD, time() + 1800 + random(1801));
			 
		// Increase the number of offerings in the altar by one 
		add_prop(ALTAR_IS_OCCUPIED, query_prop(ALTAR_IS_OCCUPIED) + 1);
				
		// This handles heaps like leftovers
		if (ob->query_prop(HEAP_I_IS))
		{
			ob->reduce_heap_size(1);
		}
		else
			ob->remove_object();
		return 1;	
			
    }
    notify_fail(capitalize(LANG_THESHORT(ob)) +" is not an acceptable "+
        "offering.\n");
    if (!check_oprop(ob))
        return 0;

    if (ob->query_worn())
    {
        notify_fail("You're wearing it!\n");
        return 0;
    }
    if (ob->query_wielded())
    {
        notify_fail("You're wielding it!\n");
        return 0;
    }

    /* Just to make sure players don't sacrifice each other */
    notify_fail("You cannot offer "+ capitalize(oshort) +"!\n");
    if (interactive(ob))
        return 0;

    /* If an object has this prop defined, it does something special
     * when offered. Since the effect depends upon the offering, the
     * function altar_special(object altar) -must- be defined in the 
     * offered object or an error will result.
     */       
    if (ob->query_prop(SPECIAL_OFFERING))
    {
        ob->altar_special(this_object(), this_player());
        return 1;
    }

    if (living(ob))
    {
        wep = filter(all_inventory(this_player()), do_item_filter);
        if (!sizeof(wep))
        {
            write("You need to be wielding a blade in order to "+ qvb +
                " the "+ oshort +" properly.\n");
            return 1;
        }
        else
        {
            write("Making an offering to "+ capitalize(query_god()) +
                ", you slit the "+ oshort +" open on the altar.\n"+
                "The "+ oshort +" writhes and twitches spasmodically "+
                "under your hands, splashing blood everywhere.\n");
            say(QCTNAME(TP) +" offers the "+ oshort +" as a blood "+
                "sacrifice upon the altar.\n"+ QCTNAME(TP) +" slits "+
                "the "+ oshort +" open and watches as it writhes "+
                "and twitches spasmodically, splashing blood every"+
                "where.\n");

            /* Add the bloody sacrifice to the altar long */
            add_offer_bloody(oshort);

            /* Increase blood-offering count in player by one */
            TP->add_prop(I_MADE_BLOOD_OFFERING, 
                TP->query_prop(I_MADE_BLOOD_OFFERING) + 1);

            /* Increase the number of offerings in the altar by one */
            add_prop(ALTAR_IS_OCCUPIED, query_prop(ALTAR_IS_OCCUPIED) + 1);

            /* Blood-sacrifices are messy. */
            add_prop(ALTAR_IS_BLOODY, 1);

            /* altar_result_pos() is a good function to put adjustments
             * to player alignment etc as a result of his/her actions
             */
            altar_result_pos(pl, qvb);
            ob->remove_object();
            return 1;
        }
    }

    /* Normal offering style */
    write("You offer "+ oshort +" at the altar of "+
        capitalize(query_god()) +".\n"+"Your offering is accepted.\n");
    say(QCTNAME(TP) +" offers "+ oshort +" at the altar.\n");       

    /* Add the sacrifice to the altar long */
    add_offer_short(oshort);

    /* Increase offering count in player by one */
    TP->add_prop(I_MADE_OFFERING, TP->query_prop(I_MADE_OFFERING) + 1);

    /* Increase the number of offerings in the altar by one */
    add_prop(ALTAR_IS_OCCUPIED, query_prop(ALTAR_IS_OCCUPIED) + 1);

    /* altar_result_pos() is a good function to put adjustments
     * to player alignemnt etc as a result of his/her actions
     */
    altar_result_pos(pl, qvb);

    /* This handles heaps like leftovers */
    if (ob->query_prop(HEAP_I_IS))
    {
		ob->reduce_heap_size(1);
    }
    else
        ob->remove_object();
    return 1;
}


/*
 * Function name:  do_pray
 * Description:    It is possible to pray at the altar.
 *                 You may redefine this function if you wish.
 * Arguments:      str - the words after the verb
 */   
int
do_pray(string str)
{
    string qvb;
    object pl = TP;

    notify_fail("The "+ QSHORT(TO) +" is defiled! You cannot "+ qvb +" here.\n");
    if (query_prop(ALTAR_IS_DEFILED))
        return 0;
    
    notify_fail("You take a moment to pray silently.\n");
    if (!str || !strlen(str))    
        return 0;
    
    qvb = query_verb();
    notify_fail(capitalize(qvb) +" how?\n");
    if (!parse_command(str, ({ }), "[at] / [to] [the] 'altar' / '"+ 
        query_god() +"' / '"+ query_altar_name() +"'"))
        return 0;    

    if (id_altar_check(this_player()))
    {      
        write("You assume the proper posture for praying to "+ 
            capitalize(query_god()) +".\n");
        pray_text(pl, qvb);        
        altar_result_pos(pl, qvb);
        return 1;
    }
    write("You take a moment to "+ qvb +" silently.\n");
    return 1;
}

/*
 * Function name:  do_worship
 * Description:    Default worship add_action (same as pray for now)
 *                 You may redefine this function if you wish.
 * Arguments:      str - the words after the verb
 */   
int
do_worship(string str)
{
    string qvb;
    object pl = TP;

    notify_fail("The "+ QSHORT(TO) +" is defiled! You cannot "+ qvb +" here.\n");
    if (query_prop(ALTAR_IS_DEFILED))
        return 0;
    
    notify_fail(capitalize(qvb) +" whom?\n");
    if (!str || !strlen(str))    
        return 0;
    
    qvb = query_verb();
    notify_fail(capitalize(qvb) +" how?\n");
    if (!parse_command(str, ({ }), "[at] / [to] [the] 'altar' / '"+ 
        query_god() +"' / '"+ query_altar_name() +"'"))
        return 0;    

    if (id_altar_check(this_player()))
    {      
        write("You assume the proper posture for worship of "+ 
            capitalize(query_god()) +".\n");
        pray_text(pl, qvb);        
        altar_result_pos(pl, qvb);
        return 1;
    }
    write("You take a moment to "+ qvb +" silently.\n");
    return 1;

}

void 
init()
{
    int i;

    ::init();
    
    for (i = 0; i < sizeof(bless_cmds) ; i++)
        add_action(do_bless, check_call(bless_cmds[i]));
	
    for (i = 0; i < sizeof(offer_cmds) ; i++)
        add_action(do_offer, check_call(offer_cmds[i]));

    for (i = 0; i < sizeof(pray_cmds) ; i++)
        add_action(do_pray, check_call(pray_cmds[i]));
	
    for (i = 0; i < sizeof(worship_cmds) ; i++)
        add_action(do_worship, check_call(worship_cmds[i]));

	/*  No sybarite priests around to undo these effects right now	 
	 for (i = 0; i < sizeof(defile_cmds) ; i++)
	 add_action(do_defile, check_call(defile_cmds[i]));
	 
	 for (i = 0; i < sizeof(destroy_cmds) ; i++)
	 add_action(do_destroy, check_call(destroy_cmds[i]));
	 
	 for (i = 0; i < sizeof(disman_cmds) ; i++)
	 add_action(do_dismantle, check_call(disman_cmds[i]));
	 */
	
}


