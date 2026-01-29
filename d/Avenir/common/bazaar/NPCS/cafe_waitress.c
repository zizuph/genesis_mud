// file name:     ~Avenir/common/bazaar/NPCS/cafe_waitress.c
// creator(s):     Lilith, August 1998
// last update:   Lilith Nov 2021: added pen and paper give.
// purpose:     
// note:           
// bug(s):     
// to-do:                  

inherit "/std/monster";
inherit "/d/Avenir/inherit/intro";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/common/bazaar/museum/museum.h"
#define STUFF "/d/Avenir/common/bazaar/Obj/worn/"

int alarm_id;


void
equip_me()
{
    seteuid(getuid()); 
    equip(STUFF + "qbracel");
    equip(STUFF + "qbracer");
    equip(STUFF + "blouse");
    equip(STUFF + "qring1");
    equip(STUFF + "qskirt");
    equip(STUFF + "qring2");
    equip("/d/Avenir/common/clubs/dance/anklet");     
    equip("/d/Avenir/common/clubs/dance/veil");     
    command("wear all"); 
    command("bells on");
}                


void
create_monster() 
{
    string *randadj = ({ "demure", "smiling", "vivacious",
                         "graceful", "gracious", "doe-eyed",
                         "lovely", "perky", "gentle" });
    if (!IS_CLONE)
        return;

    set_name("mirmarin");
    set_living_name(query_name());
    add_name(({"dancer", "woman", "female", "waitress", "server"}));
    set_race_name("human");
    set_adj(randadj[random(sizeof(randadj))]);
    set_title("the Hostess of GoatFeathers and retired Dancer of Veils");
    set_long("She is a woman of middle years, still retaining "
        +"the lissome shape of her youth.\nHer eyes are dark "
        +"and very quick, never resting for long in one place.\n"
        +"She has black hair with a single white streak, and it "
        +"is fastened in a knot at her nape.\nShe looks like she "
        +"will be receptive to questions about the menu.\n"
        +"She looks like the image of perfection.\n");

    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS, 1);
	add_prop(CONT_I_WEIGHT, 40000);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_stats(({60, 75, 60, 50, 50, 40}));
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_CLUB, 40);
    set_alignment(0);

    set_act_time(5);   
    add_act("sit");
    add_act("stand up");
    add_act("emote quietly clears off a table.");
    add_act("do get all, fill bin");
       
    add_ask(({"city","forbidden city"}),
         "say The Forbidden City is the island where the Shadow Elves "+
         "live. It is a marvellous place. For those permitted to enter, "+
         "it is a great honour.",1);
    add_ask(({"menu", "menus"}), VBFC_ME("menu_check"));
	add_ask(({"pen", "paper", "tablet", "page", "pencil", "writing",
         "writing utensils", "writing supplies", "supplies", "vellum"}), 
         VBFC_ME("pen_check"));
    add_ask(({"kahve", "coffee"}), "say Our kahve, or coffee, as the "+
         "Outlanders say it, is made from the beans of kahve plants "+
         "that have grown under the blessed light of the Source. I "+
         "can guarantee that no Outlander coffee compares. We "+
         "offer it hot, with cream and sugar, and spiked with "+
         "cognac.", 1);
    add_ask(({"spiked kahve", "cognac", "alcohol"}), 
         "Over the years the Gods and the Hegmon have allowed sybarites "+
         "to consume alcohol outside of the temple and other sites of "+
         "divine rites. I am pleased to offer spiked kahve if you wish "+
         "to order it.", 1);
    add_ask(({"temple", "divine rites"}), "say Oh we don't talk about such "+
         "things in places like this.", 1);
    add_ask(({"sardine", "sardines", "grape leaves"}), 
         "say The sardines are imported from the far-away land of "+
         "Earthsea. They are prepared here, in a fashion developed "+
         "by Mishel himself. They are quite tasty.", 1);
    add_ask(({"loaf", "bread", "zuccarrot", "zuccarrot bread"}),
         "say A moist, sweet bread made with freshly harvested carrots "+
         "and zucchini. It is lovely as a snack or accompanying "+
         "your meal.", 1);
    add_ask(({"eggplant", "stuffed eggplant"}),
        "say A lovely, large egglant that is stuffed with sauteed "+
        "onions, rice, diced tomatoes, a bit of spicy ground meat, "+
        "and chopped parsley.", 1);
    add_ask(({"tabule", "tabuele"}),
        "say My favorite dish! It is a plate of rice flavoured "+
        "with a bit of olive oil and chopped clover.", 1);
    add_ask(({"jam", "jelly", "rose jelly"}),
        "say It is a delightful little dish of sweets made from "+
        "jellied rose petals. You really must try it.", 1);
    add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
        "say We of Sybarus are the Faithful. We live to serve and "+
        "uphold the Pact, that the Source will always cast its illum"+
        "ination upon us.",1);
    add_ask(({"infidel","infidels", "prisoner", "prisoners", 
        "criminals"}), "say A most unpleasant question. I hope "+
        "that you do not plan to pursue this topic?", 1);  
    equip_me();
}
/*
 * If player asks about menu, check for its presence and give one
 * if they don't have it already.
 */
string
menu_check()
{
    object obj;
    if (present("_museum_cafe_menu", TP))
    {
        command("say I gave you a menu already, yes?");
        command("say You may ask me about specific items on "+
            "the menu, if you wish.");
        return "";
    }
    else
    {
        obj = clone_object(MUS_OBJ +"menu");
        obj->move(TO);
        command("give menu to "+ TP->query_real_name());
        return "";
    }
}

/* Player asks for pen or paper.
 * Clones these objects if the player doesn't have them.
 */
string
pen_check()
{
	seteuid(getuid());
    object obj1, obj2;
    if (!present("_museum_tablet", TP))
    {
        obj1 = clone_object("/d/Avenir/common/bazaar/museum/obj/pad")->move(TO);
        command("say I have a tablet for you right here.");
		command("give tablet to "+ TP->query_real_name());
    }

    if (!present("_Avenir_poets_pen", TP))
    {
        obj2 = clone_object("/d/Avenir/common/bazaar/Obj/misc/poet_pen");
		obj2->randomize();
		obj2->move(TO);
        command("say ...And a pen. Pen. Ah! Here it is!");		
		command("give pen to "+ TP->query_real_name());
    }
    
	command("say I think you have what you need to write now, yes?");
	command("say I look forward to reading it on the bulletin board.");
	command("smile encour");
    return "";
}

/* Remove item from inventory */
void 
dest_it(object bye)
{
   bye->remove_object();
}
    
void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
    if (!from)
        return;
 
    if (ob->id("menu"))
    {
        set_alarm(2.0,0.0, &dest_it(ob));
        return;
    }
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i = random(10);

    if (!present(tp, environment(TO)))
        return;

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 2)
            command("cutsey deep "+ tp->query_real_name());
        if (i == 4)
            command("say to "+ tp->query_real_name() +" I am "+
                "honoured by your presence!");
        return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
        if (i > 4)
            command("say to "+ tp->query_real_name() +
                " Sister dancers are always welcome here.");
        return;
    }       
    else
    {
        if (i == 5)
            command("say to "+ tp->query_real_name() + " "+
               "Welcome to the GoatFeathers Cafe, Outlander.");
        if (i == 7)
            command("say to "+ tp->query_real_name() + " "+
               "Buy a bowl of kahve and sit awhile.");
        if (i == 9)
            command("say to "+ tp->query_real_name() + " "+
               "All are welcome who respect the peace.");
            return;
    }
}

/*
 *  Give player a menu if they don't have one.
 */
void
test_menu(object tp)
{
    object obj;
    if (obj = present("_museum_cafe_menu", tp))
        return;
    else
    {
        obj = clone_object(MUS_OBJ +"menu");
        obj->move(TO);
        command("give menu to "+ tp->query_real_name());
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        set_alarm(1.5, 0.0, &test_menu(TP));
        if (alarm_id)
            return;
        else
            alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
    }
}  


/*
 * Function name: return_hug
 * Description  : When the NPC is hugged, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_hug(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    command("smile slight "+ OB_NAME(actor));
    command("say Demonstrations of affection are quite nice, but they"+
        " don't pay my bills.");
}
/*
 * Function name: return_hit
 * Description  : When the NPC is groped, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_hit(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    command("frown "+ OB_NAME(actor));
    command("say If you want food and beverages, that is what I am here for.");
    command("say If being rough with women is your pleasure, visit the "+
        "Ziggurat in the Forbidden City...");
    command("say They take all kinds there...even yours.");
    command("spit");
}

/*
 * Function name: return_grope
 * Description  : When the NPC is groped, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_grope(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    command("smile ");
    command("say to "+ OB_NAME(actor) +" I appreciate your affection. "+
	    "However, if you are feeling passionate perhaps you should visit "+
		"the Ziggurat for a more appropriate venue...");
}

/*
 * Function name: return_poke
 * Description  : When the NPC is poked, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_poke(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    command("poke " + OB_NAME(actor));
    command("say You must be a friend of Tricky's.");
    command("say Any friend of Tricky's is welcome, he used to spend a " +
	"lot of gold watching me dance.");
}

/*
 * Function name: emote_hook
 * Description  : This hook is called whenever an emotion is performed on this
 *                NPC. If it is an emotion that we hook on, call a little
 *                alarm and then call the return function.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 */
void
emote_hook(string emote, object actor, string adverb, object *oblist,     int
    cmd_attr, int target)
{
    /* See if we want to trigger on the emote. If so, call a little alarm
     * for the reaction function.
     */
    if (target <= 0) {
        return;
    }
    switch(emote)
    {
        case "caress":
        case "grope":
        case "fondle":
        case "lick":
            set_alarm(3.0, 0.0, &return_grope(actor, adverb) );
            return;

        case "poke":
	    set_alarm(3.0, 0.0, &return_poke(actor, adverb) );
	    return;
        case "hug":
        case "kiss":
        case "cuddle":
        case "snuggle":
		case "nuzzle":
            set_alarm(3.0, 0.0, &return_hug(actor, adverb));
            return;
        case "slap":
        case "kick":
            set_alarm(3.0, 0.0, &return_hit(actor, adverb));
            return;
    }
}

