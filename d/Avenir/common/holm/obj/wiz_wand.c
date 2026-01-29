/* ruby in fuchsite wand /d/Avenir/common/holm/obj/wield/wiz_wand.c
 * creator(s):           Lilith, Dec 2021
 * purpose:              Magic enhancing obj.
 *                       set_magic_spellpower(42);
 * notes:                Cleared to implement by Arman Dec 31,2021
 *                       It is cloned by /d/Avenir/common/holm/mon/wizard.c
 *         Requirements: Spellcraft 40, Dis 80
 *              Effects: <flourish wand> Teleports to Bazaar Apothecary  
 *                       Needs 3 hours to recharge between uses. 
 *
 *     Associated files: 
 *
 * updates:    Lilith Jan 2022: fixed bug with the teleport.
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/lib/keep";

#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Avenir/common/holm/holm.h"
#include "/d/Avenir/include/relation.h"

#define APO             "/d/Avenir/common/bazaar/intr/apoth_below"
#define I_GOT_SKILLZ    "_av_i_gufdinin"
#define RECHARGING      "_av_gufdinin_recharging"
// Just about 3 hours
#define RECHARGE_DELAY  10000.0

int alarm_id, mana_reduce;
string read_symbols();

void create_object()
{
    set_name("wand");
	add_name("gufdinin");
    add_adj(({"ruby", "fuchsite", "in", "magic", "magick"}));
    set_short("ruby in fuchsite wand");
    set_long("This ruby in fuchsite wand is a gorgeous swirl of pastel "+
       "green, red, and blue colours. "+
	   "Roughly the length of your hand from the tip of your index finger "+
       "to your wrist and the thickness of your thumb, the stone has been "+
       "polished to silken smoothness. The green fuchsite "+
	   "is dotted with rose-red hexagonal ruby crystals the size of a " +
       "fingernail. Each hexagon is rimmed in blue kyanite, adding more " +
       "color to the mix. The soft fuchsite stone has been carved with " +
       "intricate symbols and imbued with magick. This wand " +
       "looks like it would be useful if held in the hand of a caster.\n");
       
    add_item(({ "symbol", "symbols", "magical symbols", "intricate symbols" }),
        "Magical symbols curl around the wand. They were carved into the "+
        "stone and filled in with a silvery-white metal, probably platinum. "+
        "You have a feeling that you might be able to make sense of the "+
        "symbols if you take a moment to <study> them.\n" );
    add_cmd_item(({ "symbol", "symbols", "magical symbols", "intricate symbols" }),
        ({"read", "study"}), read_symbols);	
		
    set_slots(W_ANYH);
    set_magic_spellpower(42);
    
    setuid();
    seteuid(getuid());
    if (IS_CLONE)
    {
        LISTENER_NOTIFY(this_object());
        set_item_expiration();
    }
	
    set_keep(1);
    
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 500); 
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 1500); /* Magical item */
	
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "  Such power stored in the ruby crystals\n", 10,
        "  Of the wand of Nemur Glim-Nodal the Great!\n", 15,
		"  Gufdinin will enhance the power of offensive\n"+
		"  Magicks during battle.\n", 25,
		"  Nemur also uses it as a shortcut to replenish his\n"+
        "  Stock of magical ingredients.\n", 40,
		"  Both the caster's mind and the wand need time "+
        "  To regain full strength after this use.\n", 45
		}));

    /* Let wizards know what this wand does */
    add_prop(OBJ_S_WIZINFO, "This wand is a magic enhancer with "+
        "spell power of 42 and a wand "+
        "of teleportation to apothecary in the Sybarus Bazaar.\nIt is "+
        "cloned by Nemur on the Holm in Avenir.\nIt needs 3 hours "+
		"to recharge between teleports and takes 1/5 of player's max "+
        "mana each time.\n");
}


string
read_symbols()
{
	if (!this_player()->query_prop(I_GOT_SKILLZ))
	{
        write("Perhaps if you held it properly, you might be able "+
            "to make sense of them.\n");
        return "";
	}
	
    if(this_player()->query_skill(SS_LANGUAGE) < 40)
    {
        write("Much to your disappointment, you realize that "+
            "you lack the language skills to decipher the symbols "+
            "on the wand.\n");
        return "";
    }
	
	if (this_player()->query_skill(SS_SPELLCRAFT) <40)
    {
        write("Much to your disappointment, you realize that "+
            "you lack the knowledge of spellcraft needed to decipher "+
            "the symbols on the wand.\n");		
        return "";
    }
	
    return "The symbols seem to indicate that the wand is named "+
        "Gufdinin and that if you 'flourish gufdinin' " +
        "you will summon winds to move you somewhere else.\n";
}

/*
 * Function name: hold
 * Description  : Called when the person wants to hold an item. This function
 *                may allow or disallow the object to be held, and it may
 *                print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be held, print default messages.
 *                 1 - The item can be held, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be held. Print default messages.
 *                string - The item cannot be held. The string contains the
 *                         fail message.
 */
public mixed
hold()
{
    if (holder->query_skill(SS_SPELLCRAFT) >= 40 &&
        holder->query_stat(SS_DIS) >= 80)
    {
        write("A wave of peculiar energy rolls over you as you take hold "+
           "of it.\n");
		holder->add_prop(I_GOT_SKILLZ, 1);
    }
    return 0;
}

/*
 * Function name: release
 * Description  : Called when the person wants to release the item. This
 *                function may allow or disallow the object to be released,
 *                and it may print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be relased, print default messages.
 *                 1 - The item can be relased, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be released. Print default messages.
 *                string - The item cannot be relased. The string contains the
 *                         fail message.
 */
public mixed
release()
{
	if (holder->query_prop(I_GOT_SKILLZ))
        holder->remove_prop(I_GOT_SKILLZ);
    return 0;
}

void leave_env(object from, object to)
{
    ::leave_env(from, to);
	if (holder->query_prop(I_GOT_SKILLZ))
        holder->remove_prop(I_GOT_SKILLZ);
    holdable_item_leave_env(from, to);
 }
/*
 * This function is called RECHARGE_DELAY after the 
 * teleportation effect is used.
 */
void restore_flourish()
{
	tell_room(ENV(TO), "A flash of light emits from "+ short() + ".\n");
    remove_prop(RECHARGING);
}

/* This gives a sequence of messages and then moves the player */
void
spell_seq(object ob, int count)
{
    string str;

    /* Sanity checks */
    if (!ob)
    {		
        remove_alarm(alarm_id);	
		return;
	}
    
	/* Was it dropped or put into a container? */
    if (environment(this_object()) != ob)
    {
        ob->catch_tell("The flourish spell fails because you no longer have "+
            "the wand.\n");
        remove_alarm(alarm_id);				
	    return;
    }

    /* Check to make sure it is held through the whole process */
    if (!this_object()->query_held())
    {
        ob->catch_tell("The flourish spell fails because you aren't holding "+
            "the wand.\n");
        remove_alarm(alarm_id);	
        return;
    }
	
    /* The sequence is done, do the move, take the mana */		
    if (count > 3)
    {
		// reduce mana by 1/5th of max.
		ob->add_mana(-mana_reduce);
	    ob->catch_tell("Your flesh knits together again and your eyes can "+
            "see you're in a new place!\n\n");	
	    say(capitalize(ob->query_the_name()) +" disappears in a swirl of motes.\n");
	    ob->move_living("M", APO, 1, 0);
	    say(QCTNAME(ob) +" materializes from a swirl of flesh-toned "+
            "motes.\n");
		this_object()->add_prop(RECHARGING, 1);
		set_alarm(RECHARGE_DELAY, 0.0, "restore_flourish");
	    return;
    }

    switch (count)
    {
        case 0: str = "You feel the magic symbols sinking into your skin...\n";
	      break;
        case 1: str = "Your skin starts to glow and become translucent!\n";
	      break;
        case 2: str = "You feel yourself dissolving into motes!\n";
		  break;
        case 3: str = "Your essence scatters into the wind!\n";
		  break;		  
    }

    /* Spacing for emphasis */
    if (query_interactive(ob))
	ob->catch_tell(str + "\n\n");

    alarm_id = set_alarm(1.0, 0.0, &spell_seq(ob, ++count));
	
}

/* Can the player flourish the wand and start the teleport process? */
string
flourish_me(string str)
{
	mixed msg;

    if (!str)
    {
		write("Flourish what? The wand?");
        return "";
    }

    if (str != "wand" && str != "gufdinin")
    {
		write("Flourish what? The wand?");		
        return "";
    }
		
	/* Am I holding the wand? */
    if (!this_object()->query_held())
    {
        write("You have to be holding the ruby in fuchsite wand "+
        "to use it.\n");
        return "";
    }
	
	/* Do I have the desired skill levels? */
	if (!holder->query_prop(I_GOT_SKILLZ))
    {
        write("You lack the requisite proficiencies to "+
           "flourish the wand effectively.\n");
        return "";		   
    } 	
	
    /* Are we already casting a spell? */
    if (this_player()->query_prop(LIVE_O_CONCENTRATE))
    {
        write("You are already casting a spell.\n");
        return "";
    }

    /* Cant use to escape combat, sorry. */	
	if (!this_player()->query_relaxed_from_combat())
    {
        write("You were too recently in combat to focus on flourishing "+
            "the wand properly.\n");
        return"";
    }
    
    if (IS_INFIDEL(this_player()))
    {
        write("The Idrys do not provide for those judged by Plalgus.\n");
        return "";
    }
    
    if (present("nasty_sickness", this_player())) 
    {
        write("The Idrys do not provide for those that bring sickness.\n");
        return "";
    }

    /* Is the wand still recharging? */
    if (this_object()->query_prop(RECHARGING))
    {
        write("It was flourished too recently. It needs more time to "+
            "recharge.\n");
        return "";
    }
	
    /* One-fifth of max mana will be taken */
    mana_reduce = this_player()->query_max_mana() / 5;
    if (this_player()->query_mana() < mana_reduce)
    {
        write("You lack the mental strength to attempt this now.\n");
        return "";
    }

	/* Does the room prevent teleportation? */
    msg = environment(this_player())->query_prop(ROOM_M_NO_TELEPORT);
    if (msg)
    {
        if (stringp(msg))
            this_player()->catch_msg(msg);
        else
            write("You cannot teleport from this place.\n");
        return"";
    }
	
    msg = environment(this_player())->query_prop(ROOM_M_NO_TELEPORT_FROM);
    if (msg)
    {
        if (stringp(msg))
            this_player()->catch_msg(msg);
        else
            write("You cannot teleport from this place.\n");
        return"";
    }

    msg = environment(this_player())->query_prop(ROOM_M_NO_MAGIC);
    if (msg)
    {
        if (stringp(msg))
            this_player()->catch_msg(msg);
        else
            write("You cannot cast magick here.\n");
        return"";
    }	
	
	/* Does the destination load? */
    if (LOAD_ERR(APO))
	{
        write("You flourish the ruby in fuchsite wand but get the feeling "+
            "that your destination is unavailable.\n");       
        return "";
    }
	
	write("You flourish the ruby in fuchsite wand and as you do, the metal "+
        "symbols etched into it lift from the surface and bind themselves "+
        "to your hand.\n");
		          //  Wind  move  my  flesh 
	write("The words: V'nda s'da tis ipk'nna! reverberate in your mind.\n\n");
    say(capitalize(this_player()->query_the_name()) +" flourishes a wand.\n");
    set_alarm(1.0, 0.0, &spell_seq(this_player(), 0));
    return "";	
}

void
init()
{
    ::init();
    add_action(flourish_me, "flourish");
}

void appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
	write(item_spellpower_desc());
}

string query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}

void init_recover(string arg)
{
    init_item_expiration_recover(arg);
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
