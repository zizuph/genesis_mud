// -*-C++-*-
// file name: 	  mummer_emotes
// creator(s):	  Lilith Oct-Nov 1996
// update:	  Lilith Aug 1996
// history:       
// purpose:       
// note:
// bug(s):
// to-do: 

#pragma save_binary

#include <wa_types.h>
#include <composite.h>
#include <cmdparse.h>

#define SOULDESC(x)	(this_player()->add_prop(LIVE_S_SOULEXTRA, x))

/* Some filter functions */
private int male (object ob) { return ob->query_gender() == G_MALE; }
private int female (object ob) { return ob->query_gender() == G_FEMALE; }

/*
 *      mcap
 */
int
mcap(string str)
{
    object *cap;

    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        
        
    NF("Mcap "+ str +" can't be done.\n");
    if (strlen(str))
        return 0;

    if (!sizeof(cap = filter(all_inventory(TP), "cap_check", TO)))
    {
        NF("You can't do that if you're not wearing your mummer's cap!\n");
        return 0;
    }
    write("You whirl your head about, setting the prongs of your cap "+
        "into serpentine motion and the bells to jingling.\n");
    allbb(" whirls "+ POSSESS(TP) +" head about, sending the prongs "+
        "of "+ POSSESS(TP) +" multi-coloured cap into serpentine "+
        "motion and making the bells at the tips jingle.");
    ADD_A_LEVEL(TP);
    return 1;
}

/*
 * 	mcoin
 */
int 
mcoin(string str)
{
    object *oblist;
    string pstr;

    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        

    notify_fail("You don't have a gold coin to do <mcoin> with.\n");
    if (!present("gold coin", TP))
        return 0;

    if (!strlen(str))
    {
        write("You practice making the gold coin appear and disappear.\n"+
            "It would probably be more fun if you tried the trick "+
            "on a person though.\n");
        allbb(" flourishes "+ POSSESS(TP) +" left hand, and a coin appears in "+
            POSSESS(TP) +" right one.");
        ADD_A_LEVEL(this_player());
        return 1;
    }
    
    oblist = parse_this(str, "[from] [the] [ear] [of] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        notify_fail("Mcoin who?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("You can only perform <mcoin> on one "+
            "person at a time.\n");
        return 0;
    }

    actor("You walk up to", oblist," and reach toward "+ POSSESS(oblist[0]) +
        " ear. Pretending astonishment, you produce a gold coin "+
        "in your hand, then grab "+ OBJECTIVE(oblist[0]) +
        " by the head and peer excitedly into "+ POSSESS(oblist[0]) +
        " ear.");
    target(" walks up to you and reaches a hand toward your "+
        "ear.", oblist); 
    target(" gasps in astonishment when "+ PRONOUN(TP) +" "+
        "produces a gold coin, then grabs your head and peers "+
        "excitedly into your ear!", oblist);
    all2actbb(" reaches a hand toward", oblist, "'s ear and gasps "+
        "in astonishment when "+ PRONOUN(TP) +" produces a gold coin.\n"+
        capitalize(PRONOUN(TP)) +" suddenly grabs "+ OBJECTIVE(oblist[0]) +
        " by the head and peers excitedly into "+ POSSESS(oblist[0]) +
        " ear!");
    ADD_A_LEVEL(this_player());
    return 1;
}

/*
 *  mfire_taste 
 */
int mfire_taste(string str)
{
    object *fire;

    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        

    if (!strlen(str))
    {
        notify_fail("What fire do you want to taste?\n");
        return 0;
    }

    fire = FIND_STR_IN_OBJECT(str, TP);
    if (sizeof(fire) == 0)
        fire = FIND_STR_IN_OBJECT(str, environment(TP));
    if (!sizeof(fire))
    {
	notify_fail("Can't locate "+ str +". Sorry.\n");
	return 0;
    }
    fire = filter(fire, "torch_check", this_object());
    if (!sizeof(fire))
    {
        notify_fail("But it is not lighted!\n");
        return 0;
    }
    if (sizeof(fire) > 1)
    {
        notify_fail("You can taste the fire of one thing at a time.\n");
        return 0;
    }
    if (objectp(TP->query_attack()))
    {
        notify_fail("It is not wise to perform with fire during "+
            "combat. You could injure yourself.\n");
        return 0;
    }

    write("You stick your tongue out and carefully skim its surface "+ 
        "with your "+ fire[0]->short() +", leaving behind a foul-"+
        "tasting smear that burns brightly, but briefly.\n");
    say(QCTNAME(TP) +" touches "+ POSSESS(TP) +" tongue with "+
        POSSESS(TP) +" "+ fire[0]->short() +" and it catches fire!\n");
    ADD_A_LEVEL(this_player());
    return 1;
}
/*
 * 	mflip  
 */
int
mflip(string str)
{
    object *oblist;

    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        
 
    if (!str)
    {
        write("You launch yourself into a series of cartwheels "+
           "and back-flips, making a big circle around the area.\n");
	allbb(" launches into a spectacular series of cartwheels "+
           "and back-flips, making a big circle around the area.");
        SOULDESC("turning cartwheels and back-flips");
        ADD_A_LEVEL(this_player());
	return 1;
    }
  
    oblist = parse_this(str, "[to] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Mflip to who?");
        return 0;
    }
    if (sizeof(oblist) > 1)
    {
        NF("Mflip to who?");
        return 0;
    }    
    targetbb(" launches into a series of back-flips and cartwheels "+
        "which end with "+ OBJECTIVE(TP) +" standing before you."
        , oblist);
    actor("You launch yourself into a series of back-flips and "+
        "cartwheels that end with you standing before", oblist, 
        ".");
    all2actbb(" launches into a series of cartwheels and back-flips "+
        "which end with "+ OBJECTIVE(TP) +" standing before", oblist,
        ".");
    SOULDESC("turning cartwheels and back-flips");
    ADD_A_LEVEL(this_player());
    return 1;
}

/*
 * 	mime functions
 */
string
mime_fail()
{    
    string str1, str2;
    string *anima = ({ "horse", "dogcow", "troloby", "draconian", 
                       "balrog","dragon", "mother", "pig", "demon", 
                       "dog", "goat", "bug", "god", "goddess", 
                       "orc", "mouse", "kender", "gypsy" });
    string *plant = ({ "tree", "flower", "bush", "sapling", "blossom", 
                       "root", "mushroom", "twig", "berry", "fruit", 
                       "seed", "vine","leaf", "thorn", "pickle" });
    string *verb  = ({ "beat", "bite", "cuddle", "eat", "hug", "kill",
                       "kick", "pick", "ride", "snuggle", "sneak"});
    string *hverb = ({ "dancing", "farting", "frolicking", "grunting",
                       "gyrating", "hopping", "jumping", "nodding",
                       "ranting", "running", "sleeping", "standing", 
                       "singing", "tickling"});
    string *how   = ({ "above", "around", "behind", "beneath", "on", 
                       "under", "with" });

    switch (random(3))
    {
        case 0:
           str2 = "be "+ ONEOF(hverb) +" "+ ONEOF(how) +" a "+
                   ONEOF(anima) +" so "+ PRONOUN(TP) +" can "+
                   ONEOF(verb) +" a "+ ONEOF(plant);
            break;
        case 1:
            str2 = ONEOF(verb) +" a "+ ONEOF(plant);
            break;
        case 2:
            str2 = ONEOF(verb) +" a "+ ONEOF(plant) +" while "+
                   ONEOF(hverb) +" "+ ONEOF(how) +" a "+ ONEOF(anima);
            break;
        case 3:
            str2 = "be a "+ ONEOF(hverb) +" "+ ONEOF(anima);
            break;
    }
    switch(random(3))
    {
        case 0:
            str1 = "nearly ties "+ OBJECTIVE(TP) +"self into a pretzl "+
                   "pantomiming something that indicates "+ PRONOUN(TP)+
                   " would like to";
            break;
        case 1:
            str1 = "goes into a strange series of contortions and "+
                   "grimaces that make "+ OBJECTIVE(TP) +" look "+
                   "absolutely ridiculous. You aren't sure, but you "+
                   "think "+ PRONOUN(TP)+"'s trying to tell you "+
                   PRONOUN(TP) +" wants to";
            break;
        case 2:
            str1 = "uses elaborately exaggerated body-language that "+
                   "you interpret to mean that "+ PRONOUN(TP)+" wants "+
                   "to";
            break;
    }
    return str1 +" "+ str2;
}

void
my_mime(object tp, object who, string str)
{
    int    i, skill;
    string mf = mime_fail();

    if (!present(who, environment(tp)))
        return;

    /* If you don't practice mummery, you don't do well. */
    if (tp->query_skill(MUMMER_SKILL) < 25)
    {
        tell_object(who, tp->query_The_name(who) +" gesticulates "+
            "absurdly and incomprehensibly. You feel certain "+
            "that "+ PRONOUN(tp) +" is trying to communicate "+
            "something to you.\n");
        write("You need to practice pantomiming more before you "+
            "are skilled enough to communicate effectively.\n");
        return;
    }

    /* Wizards, players of the same guild, and players w/ good 
     * language will understand the pantomime.
     */                  
    skill = (who->query_skill(SS_LANGUAGE) + 
             TP->query_skill(SS_LANGUAGE) +
             TP->query_skill(MUMMER_SKILL));

    if (IS_MEMBER(who) || who->query_wiz_level())
    {
        tell_object(who, tp->query_The_name(who) +
            " pantomimes: "+ str + "\n");
        return;
    }
    if (skill > 125)
    {
        tell_object(who, tp->query_The_name(who) +
            " pantomimes: "+ str + "\n");
        return;
    }
    /* Others will see something humorous and unintended */
    tell_object(who, tp->query_The_name(who) +" "+ mf +".\n");
    return;
}

int 
mime(string str)
{
    object *oblist;
    int i;

    if (!stringp(str))
    {
        notify_fail("What did you want to pantomime?\n");
        return 0;
    }

    oblist = FILTER_OTHER_LIVE(all_inventory(environment(TP)));
    if (!sizeof(oblist))
    {
        write("You practice pantomiming: "+ str +"\n");
        ADD_A_LEVEL(TP);
        return 1;
    }
 
    for(i=0; i<sizeof(oblist); i++)
        my_mime(TP, oblist[i], str);

    if (TP->query_option(OPT_ECHO))
        write("You pantomime: " + str + "\n");
    else
        write("Ok.\n");
    ADD_A_LEVEL(TP);
    return 1;
}

/* 
 *    fake mime
 */ 
int
fake_mime(string str)
{
    object *oblist;
    string mf = mime_fail();

    if (strlen(str))
    {
         NF("Fakemime " +str+ " can't be done.\n");
         return 0;
    }

    oblist = FILTER_OTHER_LIVE(all_inventory(environment(TP)));
    if (!sizeof(oblist))
    {
        write("You perform an improvisational pantomime. Your "+
            "audience would see:\n"+ 
            capitalize(TP->query_name()) +" "+ mf +".\n");
        ADD_A_LEVEL(TP);
        return 1;
    }

    write("You perform an improvisational pantomime. Your "+
         "audience sees:\n"+ capitalize(TP->query_name()) +" "+
         mf +".\n");
    allbb(" "+ mf +".");
    ADD_A_LEVEL(TP);
    return 1;
}
/*
 *   Mpull
 */
int
mpull(string str)
{
    object *items, item;

    if (!strlen(str))   
    {
        notify_fail("What do you want to pull out of your cap?\n");
        return 0;
    }
    items = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(items))
    {
	notify_fail("Can't locate "+ str +". Sorry.\n");
	return 0;
    }
    if (sizeof(items) > 1)
    {
        notify_fail("You can only pull one thing at a time from your cap.\n");
        return 0;
    }
    item = items[0];
    if (!living(item))
    {
        notify_fail("You must have something -alive- in your inventory "+
            "inorder to do this.\n");
        return 0;
    }
    write("You wave your hand over the cap, embellishing every movement.\n");    
    write("You reach into the cap, and feign a look of surprise as you "+
        "pull "+ LANG_ASHORT(item) +" from your cap.\n");
    allbb(" waves "+ POSSESS(TP) +" hand over the dark center of the cap, "+
        "reaches inside, and looks pleasantly surprised as "+ PRONOUN(TP) +" pulls "+
        LANG_ASHORT(item) +" out of "+ POSSESS(TP) +" cap.");
    ADD_A_LEVEL(this_player());
    return 1;
}

/*
 *  Mshow
 */
int
mshow(string str)
{
    object *cap;

    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        

    if (str == "hat" || str == "cap" || str == "mummers cap")
    {
        if (sizeof(cap = filter(all_inventory(TP), "cap_check", TO)))
            command("remove cap");

        write("With studied grace and a flourish of your hands, you "+
            "show your audience that you have nothing at all inside "+
            "your mummer's cap.\n");
        say("With studied grace and a flourish of "+ POSSESS(TP) +
            " hands, "+ QTNAME(TP) +" demonstrates that "+ PRONOUN(TP) +
            " has nothing at all inside "+ POSSESS(TP) +" mummer's cap.\n");
        ADD_A_LEVEL(this_player());
        return 1;       
    }
    write("With great flair and deliberate grace, you show your "+
        "audience that you have nothing at all up your sleeves.\n");
    allbb(" extends "+ POSSESS(TP) +" arms and, with great flair "+
        "and deliberate grace, shows you that "+ PRONOUN(TP) +
        " has nothing at all up "+ POSSESS(TP) +" sleeves.");
    ADD_A_LEVEL(this_player());
    return 1;
}



/*
 *     msleeve 
 */
int
msleeve(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        

    if (strlen(str))
    {
         NF("Msleeve " +str+ " can't be done.\n");
         return 0;
    }

    write("With great flair and deliberate grace, you show your "+
        "audience that you have nothing at all up your sleeves.\n");
    allbb(" extends "+ POSSESS(TP) +" arms and, with great flair "+
        "and deliberate grace, shows you that "+ PRONOUN(TP) +
        " has nothing at all up "+ POSSESS(TP) +" sleeves.");
    return 1;
}

/*
 * 	mstand
 */
int
mstand(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        

    if (strlen(str))
    {
         NF("Mstand " +str+ " can't be done.\n");
         return 0;
    }

     write("You stand on your hands with practiced ease.\n");
     allbb(" stands on "+ POSSESS(TP) +" hands with practiced ease.");
     SOULDESC("standing on both hands");
     ADD_A_LEVEL(this_player());
     return 1;
}


/*
 * 	mtip
 */
int
mtip(string str)
{
    object *oblist;

    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        
 
    if (!str)
    {
        write("With a flourish, you tip your cap upside-down and "+
           "present it to onlookers, soliciting coins for your "+
           "performance.\n");
	allbb(" flourishes "+ POSSESS(TP) +" mummer's cap and tips "+
           "it upside-down, soliciting coins for "+ POSSESS(TP) +
           " performance.");
	return 1;
    }
  
    oblist = parse_this(str, "[to] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Mtip to who?");
        return 0;
    }
    targetbb(" flourishes "+ POSSESS(TP) +" mummer's cap, tips "+
        "it upside-down, and presents it to you, soliciting "+
        "coins for "+ POSSESS(TP) +" performance.", oblist);
    actor("With a flourish, you tip your cap upside-down and "+
        "present it to", oblist, ", soliciting coins for your "+
        "performance.");
    all2actbb(" flourishes "+ POSSESS(TP) +" mummer's cap, tips "+
        "it upside-down, and presents it to", oblist, ", "+
        "soliciting coins for "+ POSSESS(TP) +" performance.");
    return 1;
}

/*
 * 	mtoe
 */
int
mtoe(string str)
{
    object *boots;
    object *obs, *ob_ar = ({ });
    string race;

    if (!IS_MEMBER(TP))
    {
        NF("You're not a Mummer of Sybarus!\n");
        return 0;
    }        
    
    NF("Juggle what with your toes?\n");
    if (!strlen(str))
        return 0;

    obs = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(obs))
	return 0;

    NF("You can't juggle with your toes if you're wearing shoes!\n");
    if (sizeof(boots = filter(all_inventory(TP), "boot_check", TO)))
        return 0;

    race = QRACE(TP);
    if (race == "drow")
    {
        if (sizeof(obs) > 10) 
            ob_ar = ({ obs[0], obs[1], obs[2], obs[3], obs[4],
                       obs[5], obs[6], obs[7], obs[8], obs[9] });
        else
            ob_ar = obs;
    }              
    if (race == "elf")
    {
        if (sizeof(obs) > 10) 
            ob_ar = ({ obs[0], obs[1], obs[2], obs[3], obs[4],
                       obs[5], obs[6], obs[7], obs[8], obs[9] });
        else
            ob_ar = obs;
    }              
    if (race == "half-elf")
    {
        if (sizeof(obs) > 10) 
            ob_ar = ({ obs[0], obs[1], obs[2], obs[3], obs[4],
                       obs[5], obs[6], obs[7], obs[8], obs[9] });
        else
            ob_ar = obs;
    }
    if (race == "human")
    {
        if (sizeof(obs) > 8) 
            ob_ar = ({ obs[0], obs[1], obs[2], obs[3], obs[4],
                       obs[5], obs[6], obs[7] });
        else
            ob_ar = obs;
    }
    if (race == "gnome")
    {
        if (sizeof(obs) > 7) 
            ob_ar = ({ obs[0], obs[1], obs[2], obs[3], obs[4],
                       obs[5], obs[6] });
        else
            ob_ar = obs;
    }              
    if (race == "kender")
    {
        if (sizeof(obs) > 7) 
            ob_ar = ({ obs[0], obs[1], obs[2], obs[3], obs[4],
                       obs[5], obs[6] });
        else
            ob_ar = obs;
    }              
    else
    {
        if (sizeof(obs) > 5) 
            ob_ar = ({ obs[0], obs[1], obs[2] });
        else
            ob_ar = obs;
    }              
                   
    write("You stand on your hands and begin juggling "+ 
        COMPOSITE_DEAD(ob_ar) +" with your toes.\n");
    allbb(" stands on "+ POSSESS(TP) +" hands and begins juggling "+
        COMPOSITE_DEAD(ob_ar) +" with "+ POSSESS(TP) +" toes.");
    ADD_A_LEVEL(this_player());
    return 1;
}

