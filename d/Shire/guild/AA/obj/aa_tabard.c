/*
 * AA tabard
 *
 *
 *  Modification log:
 * 
 *     2008.06.17, Novo: If shield is gone, remove tabard
 *
 */
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "../guild.h"

inherit "/std/object";
inherit "/lib/commands";

#define SUBLOC_TABARD "_aa_tabard_subloc"

/*
 * Global constants
 */
static string *Rank = ({ "Servant",         
                  "Footman",         
                  "Standard Bearer", 
                  "Lance Corporal",        
                  "Corporal",   
	              "Sergeant",
                  "Master Sergeant",       
                  "Master Sergeant" });
static string *Sign = ({ "shape of boots carved in",                             
                  "'property of the Army' embroidered in wool thread",    
                  "a tiny flag embroidered in copper thread",             
                  "two stripes embroidered in silver thread",             
                  "a small star embroidered in silver thread",            
                  "two small stars emroidered in gold thread",            
                  "two small stars and a leaf embroidered in gold thread",
                  "three small stars and a leaf embroidered in platinum thread"
               });
static string *Fabric = ({ "thick hide",    
                    "rough wool",    
                    "fine wool",     
                    "soft cotton",   
                    "dark brocade",  
                    "rare brocatel", 
                    "shiny satin",   
                    "finest silk" });


/*
 * Global variables
 */
int Rnum;      /* number of rank 0-Servant, ... , 7-Captain */
int Shown;     /* is tabard draped over a shield?     */
object Shield; /* a shield that tabard is draped over */

// prototypes
int drape(string str);
int undrape(string str);
int dust(string str);
int adjust(string str);
int mend(string str);
int whack(string str);
int remind(string str);
int help(string str);


int tabard_is_shown()
{
    object on;
    if(!Shown) return 0;
    on = ENV(TO);
    if((Shield != on->query_armour(W_LEFT) &&
        Shield != on->query_armour(W_RIGHT))
        || !Shield)
    {
        on->remove_subloc(SUBLOC_TABARD);
        Shown = 0;
        set_no_show_composite(0);
        Shield = 0;
        on->remove_item(on->query_name()+" tabard");
    }
    return Shown;
}

void create_object()
{
    set_name(({"tabard"}));
	add_name("_aa_tabard_ob");
    set_adj("angmarian");
    set_long("@@my_long");
    
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_M_NO_SELL,"You will NOT sell your tabard.\n");
    add_prop(OBJ_M_NO_DROP,"You don't wan't to drop your tabard.\n");
}

string checkem(object ob)
{
    if(ob->query_stat(SS_WIS)>50 || IS_MEMBER(ob))
        return "recognize as a sign of rank of "+Rank[Rnum]+".";
    return "suspect is a kind of sign of rank.";
}

string my_long()
{
    if(TP == ENV(TO))
    {
        if(tabard_is_shown())
		{ 
			if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1)
			{
				return "This is the Captain of the Army of Angmar's tabard. It looks rather used, " +
					"and it's is made of fine silk. You have just had it washed " +
					"by a Servant, to make sure the colours are bright and " +
					"clear. It is draped over your " + Shield->short() + ", showing " +
					"to the world that you are a Mighty Angmarim Captain. It " +
					"bears the symbol of a black shield with a nasty-looking " +
					"mace crossing it. It also has three small stars and a leaf "
					+"embroidered in platinum thread, showing that " +
					"your official rank is Captain. You also notice a small " +
					"embroidered <help AA tabard> on it.\n";
			}

			if (AA_COUNCIL_OBJ->is_lieutenant(this_player()->query_name()) == 1)
			{
				return "This is the Lieutenant of the Army of Angmar's tabard. It looks rather used, " +
					"and it's is made of fine silk. You have just had it washed " +
					"by a Servant, to make sure the colours are bright and " +
					"clear. It is draped over your " + Shield->short() + ", showing " +
					"to the world that you are an Angmarim Lieutenant. It " +
					"bears the symbol of a black shield with a nasty-looking " +
					"mace crossing it. It also has two small stars and a leaf "
					+ "embroidered in gold thread, showing that " +
					"your official rank is Lieutenant. You also notice a small " +
					"embroidered <help AA tabard> on it.\n";
			}

			return "This is the " + Rank[Rnum] + "s tabard. It looks rather used, " +
				"and it's made of " + Fabric[Rnum] + ". You have just had it washed " +
				"by a Servant, to make sure the colours are bright and " +
				"clear. It is draped over your " + Shield->short() + ", showing " +
				"to the world that you are a proud Angmarim soldier. It " +
				"bears the symbol of a black shield with a nasty-looking " +
				"mace crossing it. It also has " + Sign[Rnum] + ", showing that " +
				"your official rank is " + Rank[Rnum] + ". You also notice a small " +
				"embroidered <help AA tabard> on it.\n";
		}


		if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1)
		{
			return "This is the Captain of the Army of Angmar's tabard. It looks rather used, and " +
				"it's made of fine silk. You have just had it washed by a " +
				"Servant, to make sure the colours are bright and clear. It " +
				"bears the symbol of a black shield with a nasty-looking mace " +
				"crossing it. It also has three small stars and a leaf "+ 
				"embroidered in platinum thread, showing that your " +
				"official rank is Captain. You also notice a small " +
				"embroidered <help AA tabard> on it.\n";
		}

		if (AA_COUNCIL_OBJ->is_lieutenant(this_player()->query_name()) == 1)
		{
			return "This is the Lieutenant of the Army of Angmar's tabard. It looks rather used, and " +
				"it's made of fine silk. You have just had it washed by a " +
				"Servant, to make sure the colours are bright and clear. It " +
				"bears the symbol of a black shield with a nasty-looking mace " +
				"crossing it. It also has two small stars and a leaf " +
				"embroidered in gold thread, showing that your " +
				"official rank is Lieutenant. You also notice a small " +
				"embroidered <help AA tabard> on it.\n";
		}
            

        return "This is the "+Rank[Rnum]+"s tabard. It looks rather used, and "+
            "it's made of "+Fabric[Rnum]+". You have just had it washed by a "+
            "Servant, to make sure the colours are bright and clear. It "+
            "bears the symbol of a black shield with a nasty-looking mace "+
            "crossing it. It also has "+Sign[Rnum]+", showing that your "+
            "official rank is "+Rank[Rnum]+". You also notice a small "+
            "embroidered <help AA tabard> on it.\n";
    }

	if (tabard_is_shown())
	{
		if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1)
		{
			return "It is draped over " + HIS(ENV(TO)) + " " + Shield->short() +
				", showing you that " + HE(ENV(TO)) + " is the Captain of the " +
				"Army of Angmar. It bears the symbol of a black shield crossed " +
				"with a nasty-looking mace. It also has three small stars " +
				"and a leaf embroidered in platinum thread. It seems to " +
				"be made of fine silk. It also seems to be rather well used.\n";
		}


		if (AA_COUNCIL_OBJ->is_lieutenant(this_player()->query_name()) == 1)
		{
			return "It is draped over " + HIS(ENV(TO)) + " " + Shield->short() +
				", showing you that " + HE(ENV(TO)) + " is a Lieutenant of the " +
				"Army of Angmar. It bears the symbol of a black shield crossed " +
				"with a nasty-looking mace. It also has two small stars " +
				"and a leaf embroidered in gold thread. It seems to " +
				"be made of fine silk. It also seems to be rather well used.\n";
		}

		return "It is draped over " + HIS(ENV(TO)) + " " + Shield->short() +
			", showing you that " + HE(ENV(TO)) + " is a soldier in the " +
			"Army of Angmar. It bears the symbol of a black shield crossed " +
			"with a nasty-looking mace. It also has " + Sign[Rnum] +
			" which you " + checkem(TP) + " It seems to be made of " +
			Fabric[Rnum] + ". It also seems to be rather well used.\n";
	}

    return "";
}

void init()
{
    ::init();
    Rnum = AA_RANKS_OBJ->rank_no(ENV(TO)) + 1;
    add_action(drape,"drape");
    add_action(undrape,"undrape");
    add_action(dust,"dust");
    add_action(adjust,"adjust");
    add_action(mend,"mend");
    //add_action(whack,"whack");
    //add_action(remind,"remind");
    add_action(help,"help");
}

int help(string str)
{
    if(!str || (str != "AA tabard")) return 0;
    
    write("The standard provides the following emotes:\n"+
        "   'drape shield'     Put tabard over the shield.\n"+
        "   'undrape shield'   Remove tabard from shield and hide it.\n"+
        "   'dust tabard'      Clean tabard from dirt.\n"+
        "   'adjust tabard'    Make sure it is well on the shield.\n"+
        "   'mend tabard'      Repair the holes on tabard.\n"+
        //"   'remind [target]'  Remind [target] about your feelings.\n"+
        //"   'whack [target]'   whack someone over the head.\n"+
        "\nSuggestions on more emotes are welcome!\n");
    return 1;
}

int undrape(string str)
{
    if((!str) || (str != "shield")) return 0;
    if(!tabard_is_shown())
    {
        NF(""); write("Your tabard is not draped on a shield!\n");
        return 0;
    }
    write("You remove your tabard from the "+Shield->short()+", "+
        "carefully fold it and hide it from sight of others.\n");
    allbb(" removes "+HIS(TP)+" tabard of Angmar's Army from "+
        HIS(TP)+" "+Shield->short()+", folds it "+
        "and hides it from your sight.\n");
    TP->remove_subloc(SUBLOC_TABARD);
    TP->remove_item(TP->query_name()+" tabard");
    Shown = 0;
    set_no_show_composite(0);
    return 1;
}

int drape(string str)
{
    object sh;
    string name, cname;
    
    if((!str) || (str != "shield")) 
    {
        NF("Drape what?\n");
        return 0;
    }
    if(tabard_is_shown())
    {
        NF("You have allready draped your tabard over your "+Shield->short()+".\n");
        return 0;
    }
    
    if (((sh = TP->query_armour(W_LEFT)) && (sh->query_at() == A_SHIELD)) ||
        ((sh = TP->query_armour(W_RIGHT)) && (sh->query_at() == A_SHIELD)))
    {
        Shield = sh;

		if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()) == 1)
		{
			write("You proudly drape your " + Shield->short() + " with the Captain" + 
				"s tabard of Angmar's Army.\n");

			allbb(" proudly drapes " + HIS(TP) + " " + Shield->short() + " with the " +
				"Captains tabard of Angmar's Army.");

			TP->add_subloc(SUBLOC_TABARD, TO);
			name = TP->query_real_name();
			cname = TP->query_name();
			TP->add_item(({ name + " tabard", cname + " tabard",
				name + "s tabard", cname + "s tabard",
				name + "'s tabard", cname + "'s tabard" }),
				VBFC_ME("item_tabard"));
			Shown = 1;
			set_no_show_composite(1);
			return 1;
		}


		if (AA_COUNCIL_OBJ->is_lieutenant(this_player()->query_name()) == 1)
		{
			write("You proudly drape your " + Shield->short() + " with the Lieutenant"+
				"s tabard of Angmar's Army.\n");

			allbb(" proudly drapes " + HIS(TP) + " " + Shield->short() + " with the " +
				"Lieutenants tabard of Angmar's Army.");

			TP->add_subloc(SUBLOC_TABARD, TO);
			name = TP->query_real_name();
			cname = TP->query_name();
			TP->add_item(({ name + " tabard", cname + " tabard",
				name + "s tabard", cname + "s tabard",
				name + "'s tabard", cname + "'s tabard" }),
				VBFC_ME("item_tabard"));
			Shown = 1;
			set_no_show_composite(1);
			return 1;
		}


        write("You proudly drape your "+Shield->short()+" with the "+Rank[Rnum]+
            "s tabard of Angmar's Army.\n");

        allbb(" proudly drapes "+HIS(TP)+" "+Shield->short()+" with the "+
            "tabard of Angmar's Army."); 

        TP->add_subloc(SUBLOC_TABARD, TO);
        name = TP->query_real_name();
        cname = TP->query_name();
        TP->add_item(({name+" tabard", cname+" tabard",
            name+"s tabard", cname+"s tabard",
            name+"'s tabard", cname+"'s tabard"}), 
            VBFC_ME("item_tabard"));
        Shown = 1;
        set_no_show_composite(1);
        return 1;
    }
    NF("But you are not wearing a shield to drape....\n");
    return 0;
}

string item_tabard()
{
    object ob = ENV(TO);

    if(TP == ob) return my_long();

    if(!tabard_is_shown()) return "Examine what?\n";
    
    ob->catch_msg(QCTNAME(TP)+" examines your tabard of Angmar's Army.\n");

    TP->catch_msg("You examine "+QTNAME(ob)+"'s tabard of Angmar's Army.\n");

    tell_room(ENV(ob), QCTNAME(TP)+" examines "+QTNAME(ob)+
        "'s tabard of Angmar's Army.\n", ({ TP,ob }) );


	if (AA_COUNCIL_OBJ->is_captain(ob->query_name()) == 1)
	{
		return "It is draped over " + HIS(ENV(TO)) + " " + Shield->short() +
			", showing you that " + HE(ENV(TO)) + " is the Captain of the " +
			"Army of Angmar. It bears the symbol of a black shield crossed " +
			"with a nasty-looking mace. It also has three small stars " +
			"and a leaf embroidered in platinum thread. It seems to " +
			"be made of fine silk. It also seems to be rather well used.\n";
	}


	if (AA_COUNCIL_OBJ->is_lieutenant(ob->query_name()) == 1)
	{
		return "It is draped over " + HIS(ENV(TO)) + " " + Shield->short() +
			", showing you that " + HE(ENV(TO)) + " is a Lieutenant of the " +
			"Army of Angmar. It bears the symbol of a black shield crossed " +
			"with a nasty-looking mace. It also has two small stars " +
			"and a leaf embroidered in gold thread. It seems to " +
			"be made of fine silk. It also seems to be rather well used.\n";
	}


    return my_long();
}

int dust(string str)
{
    if((!str) || (str != "tabard")) return 0;
    if(!tabard_is_shown())
    {
        NF("");
        write("You should drape a shield with it first!\n");
        return 0;
    }
    write("You carefully dust your tabard, removing all dirt so that" +
        " all can see the sign of Angmar's Army.\n");

    allbb(" carefully dusts "+HIS(TP)+" tabard, removing all dirt, thus revealing"+
        " a picture of a shield crossed by a nasty-looking mace.");
    return 1;
}

int adjust(string str)
{
    if((!str) || (str != "tabard")) return 0;
    if(!tabard_is_shown())
    {
        NF("");
        write("You must drape the tabard on a shield first!\n");
        return 0;
    }
    write("You adjust the tabard on your "+Shield->short()+", making sure "+
        "it will stay on it in the battles to come.\n");
    allbb(" adjusts the tabard of Angmar's Army, making sure it will "+
        "stay on "+HIS(TP)+" "+Shield->short()+" in the battles to come.");
    return 1;
}

int remind(string str)
{
    int i;
    object *higher=({});
    object *oblist;
    
    if(!tabard_is_shown())
    {
        NF("");
        write("You must drape a shield with your tabard first!\n");
        return 0;
    }
    if (!str)
    {
        NF("You remind yourself that you need to specify who you want to "+
            "remind to successfully remind them.\n");
        return 0;
    }
    
    oblist = PARSE_THIS(str, "[the] %l");
    
    if (!sizeof(oblist))
    {
        NF("Remind who?\n");
        return 0;
    }
    
    for(i=0; i<sizeof(oblist); i++)
        if(IS_HIGHER(oblist[i]))
            higher += ({ oblist[i] });
    oblist -= higher;
    
    if(sizeof(higher))
    {
        targetbb(" points to "+HIS(TP)+" tabard, reminding you that "+HE(TP)+
            " is merely a flea to live and die at your whim.", higher);

        actor("You point to your tabard, reminding ", higher, 
            " that you are but a flea who lives and dies at "+
            (sizeof(higher)>1 ? "their" : HIS(higher[0]))+" whim.");

        all2actbb("  points to "+HIS(TP)+" tabard. It seem's that "+HE(TP)+
            " wants to remind ", higher," of "+HIS(TP)+
            " insignificance compared to "+HIS(TP)+" superiors.");
    }
    
    if(sizeof(oblist))
    {
        targetbb(" points to "+HIS(TP)+" tabard, reminding you that "+HE(TP)+
            " is a "+Rank[Rnum]+" of the Army of Angmar, and will take no "+
            "crap from you!", oblist);

        actor("You point to your tabard, reminding",oblist,
            " that you are a "+Rank[Rnum]+" of the Army of Angmar, and "+
            "that you will take no crap from "+
            (sizeof(oblist)>1 ? "them" : HIM(oblist[0]) )+"!");

        all2actbb(" points to "+HIS(TP)+" tabard. It seem's that "+HE(TP)+
            " wants to make",oblist," realise that "+
            (sizeof(oblist) >1 ? "they" : HE(oblist[0]))+
            " should respect a "+Rank[Rnum]+" of the Army of Angmar.");
    }
    return 1;
}

int whack(string str)
{
    int i;
    object *higher=({});
    object *oblist;
    
    if(!tabard_is_shown())
    {
        NF("");
        write("You must drape a shield with your tabard first!\n");
        return 0;
    }
    if (!str)
    {
        NF("Whack what ? The sky ? \n");
        return 0;
    }
    
    oblist = PARSE_THIS(str, "[the] %l");
    
    if (!sizeof(oblist))
    {
        NF("Whack who?\n");
        return 0;
    }
    
    for(i=0; i<sizeof(oblist); i++)
        if(IS_HIGHER(oblist[i]))
            higher += ({ oblist[i] });
    oblist -= higher;
    
    if(sizeof(higher))
    {
        targetbb(" gives you "+HIS(TP)+
            " shield. You take it and whack "+HIM(TP)+
            " over the head  with it. The shield goes BOOOIIIING!", higher);
        actor("You give your "+Shield->short()+" to", higher, " allowing "+
            (sizeof(higher)>1 ? "them" : HIM(higher[0]))+
            " to whack you over the head with it. The shield goes BOOOIIIING!");
        all2actbb(" gives "+HIS(TP)+" "+Shield->short()+" to", higher,
            " who whacks "+HIM(TP)+ " over the head with it. "+
            "The shield goes BOOOIIIING!");
    }
    
    if(sizeof(oblist))
    {
        targetbb(" whacks you over the head with "+HIS(TP)+" "+Shield->short()+
            ". You feel rather humiliated. The shield goes BOOOIIIING!", 
            oblist);
        actor("You whack",oblist," over the head with your "+Shield->short()+
            ". "+(sizeof(oblist) >1 ? "They look":CAP(HE(oblist[0])+" looks"))+
            " rather humiliated. The shield goes BOOOIIIING!");
        all2actbb(" whacks",oblist," over the head with "+HIS(TP)+" "+Shield->short()+
            ", making "+(sizeof(oblist) >1 ? "them" : HIM(oblist[0]))+
            " look rather humiliated. The shield goes BOOOIIIING!.");
    }
    return 1;
}

int mend(string str)
{
    if((!str) || (str != "tabard"))
    {
        NF("Mend what?\n");
        return 0;
    }
    if(!tabard_is_shown())
    {
        NF("");
        write("You must drape a shield with your tabard first!\n");
        return 0;
    }
    
    write("With horror you see that there is a tiny hole in your tabard. "+
        "You immediately mend it, sowing it together with a piece of "+
        "hair from your latest kill.\n");

    allbb(" notices a hole in "+HIS(TP)+" tabard of Angmar's Army, "+
        "and immediately mends it with something that looks like a bloody "+
        "piece of hair.");
    return 1;
}

/*
 * Function name: show_subloc
 * Description:   Shows the specific sublocation description for a living
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if(!tabard_is_shown()) return "";
    if(subloc != SUBLOC_TABARD) return "";
    if (for_obj == on)
        return "Your "+Shield->short()+
            " is draped with your tabard of Angmar's Army.\n";
    else
        return CAP(HIS(on))+" "+Shield->short()+
            " is draped with "+HIS(on)+" tabard of Angmar's Army.\n";
}

