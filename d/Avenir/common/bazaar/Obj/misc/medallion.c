// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/misc/button (v1.2)
// creator(s):	  Gracie->Lilith&Tep	Jan 1996
// last update:	  Zielia Feb '09 - changed from armour to clothing
//                Lilith, May 2022: added more button options and
//                 added item_expiration
// purpose:       Button/medllion with funny one-liners
// note:  
// bug(s):
// to-do:
#pragma strict_types

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/std/object";
inherit "/lib/wearable_item";

static int buttnum;
public string gButt_desc;

void set_buttnum(int i)  {  buttnum = i;  }
int query_buttnum()   {  return buttnum;  } 

public void
set_button_desc(int i)
{
    switch (i)
    {
      case 0:  gButt_desc="Celebrate the Source";	break;
      case 1:  gButt_desc="Noble Warrior";	break;
      case 2:  gButt_desc="Suicide is the ultimate sacrificial offering";	break;
      case 3:  gButt_desc="Old age and treachery will triumph over youth and honesty";	break;
      case 4:  gButt_desc="He who dies with the most wives wins";	break;
      case 5:  gButt_desc="Belly dancer: Push button to start";	break;
      case 6:  gButt_desc="Darkness is a god's way of telling the Faithful to burn more Infidels";	break;
      case 7:  gButt_desc="I do not believe in Hobbits";	break;
      case 8:  gButt_desc="The Path of Excess leads to the Palace of Wisdom"; 	break;
      case 9:  gButt_desc="The way to a man's heart is through his ribs";	break;
      case 10: gButt_desc="Old warriors never die--Their armour just smells like they did"; break;
      case 11: gButt_desc="Old warriors never die--They just take longer to re-incarnate";	break;
      case 12: gButt_desc="Will fight for food";	break;
      case 13: gButt_desc="Sybarites are Superior";	break;
      case 14: gButt_desc="He who dies with the most platinum wins";	break;
      case 15: gButt_desc="You live and learn--or you don't live long";	break;
      case 16: gButt_desc="Evil men bend the rules. Stupid men break them"; 	break;
      case 17: gButt_desc="Spellcasters are people, too";	break;
      case 18: gButt_desc="He who dies with the most combat experience loses";	break;
      case 19: gButt_desc="Have you hugged a wizard today?";	break;
      case 20: gButt_desc="I fart in your general direction. I eat my feces, too";	break;
      case 21: gButt_desc="Dwarves do it deeper"; break;
      case 22: gButt_desc="Gnomes do it for fun and profit";	break;
      case 23: gButt_desc="Humans just do it";	break; 
      case 24: gButt_desc="Goblins do it in the dark"; break;   
      case 25: gButt_desc="Elves do it better";  break;
      case 26: gButt_desc="Hide your sheep--the Angmarians are coming";	break;
      case 27: gButt_desc="Rabble I am. Rabble I remain";	break;
      case 28: gButt_desc="Angmars had a smashin' good time";   break;
      case 29: gButt_desc="Ima glad he ate her";	break;
      case 30: gButt_desc="Brutal-looking, but brainy";	break;
      case 31: gButt_desc="Old Minstrels don't die--They just have harp failure";	break;
      case 32: gButt_desc="Bard sanctuary: No hunting";	break;
      case 33: gButt_desc="Everything will perish save love and music";	break;
      case 34: gButt_desc="Vamp tramp";	break;
      case 35: gButt_desc="Monks hit below the belt";	break;
      case 36: gButt_desc="Monks don't get nun";  break;
      case 37: gButt_desc="Calians move behind women and children first";	break;
      case 38: gButt_desc="I dance like a butterfly and swarm like a bee";	break;
      case 39: gButt_desc="An old gladiator is an oxymoron";	break;
      case 40: gButt_desc="oh grr, oh grr, oh grr!";	break;
      case 41: gButt_desc="My Honour is my Life";   break;
      case 42: gButt_desc="Death before Dishonour";	break;
      case 43: gButt_desc="Knights of Solamnia take a licking--but keep on kicking";	break;
      case 44: gButt_desc="Heralds lend class to what would otherwise be a drunken brawl";	break;
      case 45: gButt_desc="Banish the bearing of bad tidings--Hang a Herald";	break;
      case 46: gButt_desc="Nazgul are sissies";	break;
      case 47: gButt_desc="Morgul Mages don't die--They're already undead";	break;
      case 48: gButt_desc="Sauron is my master, poison is my servant"; 	break;
      case 49: gButt_desc="The road to Morgul is stained with Rangers";	break;
      case 50: gButt_desc="Rangers are disarming";	break;
      case 51: gButt_desc="Lone Ranger";	break;
      case 52: gButt_desc="One man's belly-laugh is another man's Mystic";	break;
      case 53: gButt_desc="I seek the Ancients";	break;
      case 54: gButt_desc="Lloth gets tangled in her own web";    break;
      case 55: gButt_desc="Hey Thieves: Pick this";  break;
      case 56: gButt_desc="To create a little flower is the labour of a Trickster"; break;
      case 57: gButt_desc="I've survived AA. Now, get me a drink"; break;
      case 58: gButt_desc="I still raid the Keep"; break;
      case 59: gButt_desc="Fang you very much"; break;
      case 60: gButt_desc="Mirth'n hairy"; break;
      case 61: gButt_desc="Kinder care"; break;
      case 62: gButt_desc="Uncle Crapflinger"; break;
      case 63: gButt_desc="POThead"; break;
      case 64: gButt_desc="KnOThead"; break;
      case 65: gButt_desc="I follow Tacky Sis"; break;
      case 66: gButt_desc="Blue Dragonballs Are Me"; break;
      case 67: gButt_desc="Red Dragonballs Are Me"; break;
      case 68: gButt_desc="Shallot Onion"; break;
      case 69: gButt_desc="I'm not swaying because I'm drunk"; break;
      case 70: gButt_desc="I romance death"; break;
      case 71: gButt_desc="I love the smell of corpse in the morning"; break;
      case 72: gButt_desc="Vamp hireling"; break;
      case 73: gButt_desc="Ella Mental"; break;
      case 74: gButt_desc="It's ok man"; break;
      case 75: gButt_desc="Spear it Sir Kull"; break;
      case 76: gButt_desc="I WIN"; break;
      case 77: gButt_desc="Never Mind The Dog, Beware Of Owner"; break;
	  case 78: gButt_desc="Who FKing cares about the FKers?"; break;
	  case 79: gButt_desc="Fire knives are circus performers"; break;
	  case 80: gButt_desc="Horny Minotaur"; break;
	  case 81: gButt_desc="Lizards are people too?"; break;
	  case 82: gButt_desc="Irate Pirate"; break;
	  case 83: gButt_desc="Are Wart Lox edible?"; break;
      case 84: gButt_desc="Those who can't, cast"; break;
      case 85: gButt_desc="Wizzers of High Scorchery"; break;
      case 86: gButt_desc="Smiths know how to pound"; break;
      case 87: gButt_desc="I follow Dragon Orders"; break;
	  case 88: gButt_desc="The earth trembles under my feet"; break;
      default: gButt_desc="Buy it at the Bazaar"; 
        break;
    }
}

public void
set_button(int i)
{
    set_button_desc(i);
    set_buttnum(i);
	
    set_long("This medallion is worn around the neck. It is very big "+
        "and is made of some kind of faux-gold metal. It can be "+
        "worn and displayed. Printed on it, in big block letters, "+
        "are the following words:\n"+ gButt_desc +".\n");

    set_short("medallion that reads:   "+ gButt_desc);
    set_pshort("medallions that read:   "+ gButt_desc);  
}  
  
public void
create_object(void)
{    
    if (buttnum)
        set_button(buttnum);
	else
        set_button(random(89));  
    config_wearable_item(A_NECK, 1, 15, this_object());
    set_name(({"button", "medallion"}));
    set_adj("big");
    add_adj(({"faux-gold", "faux", "gold"}));    
    add_prop("_aod_wear_prop", 1);  // A vanity item ogres can wear.    
    add_prop(HEAP_S_UNIQUE_ID, "button_"+ (random(100)) + "_");
    add_prop(OBJ_I_VOLUME, 200);   
    add_prop(OBJ_I_WEIGHT, 300);   

   if (IS_CLONE)
      set_item_expiration();  	
}

public int
do_flash(string arg)
{
    notify_fail("Flash or display what?\n");
    if (!arg) return 0;

    if (arg == "button" || arg == "medallion")
    {
	write("You briefly display the '"+ gButt_desc 
	+"' medallion so others can see it.\n");
	say(QCTNAME(this_player()) +" flashes "+ 
	this_player()->query_possessive() + " '"+ gButt_desc +
	"' medallion.\n");
	return 1;
    }    
}

public void
init(void)
{
   ::init();
      add_action(do_flash, "flash");
      add_action(do_flash, "display");
      add_action(do_flash, "show");
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public string
query_recover()
{
    return MASTER + ":#num#" + buttnum +"#"+ query_item_expiration_recover();  
}


/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    string dummy1, dummy2;

    sscanf(arg, "%s#num#%d#", dummy1, buttnum, dummy2);
    init_item_expiration_recover(arg);
    set_buttnum(buttnum);
	set_button(buttnum);
}
