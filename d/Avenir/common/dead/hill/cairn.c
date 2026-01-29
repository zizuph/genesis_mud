// file name: cairn
// creator(s): Ilyian (28 August, 1995)
// last update: Lilith Dec 2007   for watch questor
//              Lilith July 2021  added interactions with Banshee and the Guardians.
//                                player can get dropped into the Catacombs this way.
//              Lilith Oct 2021  Updated statserv logging, typo fix
// purpose:     Top of the hill/cairn.  
// note:
// bug(s):
// to-do:    

inherit "/d/Avenir/common/dead/dead";
inherit "/d/Avenir/inherit/avenir_time";
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"
#include "../dead.h"

object ban;

string *objects = (({ "cube", "column", 
                      "edifice", "monolith",
                      "stone", "structure", 
                      "spire", "pillar",
                      "obelisk", "standing-stone", 
                      "rock", "willow" }));

string *writings = 
        (({ "Where you pass in safety, you dwell in peace" ,
            "You will dance with joy, governing your choices" ,
            "My fear clutches at your heart and tears it out" ,
            "My judgement is final, my words the law" ,
            "In knowledge you will find either wisdom or confusion" ,
            "What a shame, that which cannot be bought was not worth buying" ,
            "Nothing you see is real, yet you would kill another for it" ,
            "The enchantments of the world are great mysteries" ,
            "My wrath will destroy you, body and soul" ,
            "I provide sustenance for your flesh, that you may Serve" ,
            "We are essential, yet our gifts in great quantity are poison" ,
            "Intertwined, we are the pinnacle of passion and grace" }));

int *difficulty = (({ random(15)+ 20, random(15)+ 15, random(15)+ 10,
                      random(15)+ 10, random(15)+ 10, random(15)+ 10,
                      random(15)+ 10, random(15)+ 20, random(15)+ 25,
                      random(15)+ 20, random(15)+ 20, random(15)+ 15 }));

void reset_room();
int read(string what);
void report(object ob, object amulet);

/*
 * We are masking this function from the avenir_time.c
 * It notifies us of the change of hours once every hour.
 */
public void
avenir_time_callout(int av_year,int av_week_of_year,int av_dow,int av_hour)
{
   /* this will tell the time every hour */  
   tell_room(this_object(),
        "There is a bright flash overhead, and one massive object dims "+
        "while another begins to glow.\n");
}

void
create_room()
{
  set_long("You are standing atop the very apex of the "
          +"hill. To the north, a steep cliff drops "
          +"straight down to the mist veiled swamps below. Back "
          +"to the south, there appears to be some sort of "
          +"archway, and to the east and west the hill descends. "
          +"Spaced evenly around you stand twelve massive "
          +"objects like eerie guardians.\n");
  set_short("cairn");

  AI(({"cliff","dropoff"}),"The hill ends abruptly to the "
         +"north, dropping straight down to the swampy "
         +"ground below.\n");
  AI(({"arch","archway","south"}),"To the south lies a "
         +"lone archway, enshrouded in clinging fog.\n");
  AI(({"mist","fog"}),"The mist is not so thick up here "
         +"as it is down below, but it still makes a light "
         +"covering over everything.\n");

  AI(({"objects", "massive objects", "twelve objects",
       "twelve massive objects", 
	   "guardians", "massive guardians", "twelve guardians",
	   "twelve massive guardians", 
       "figures", "massive figures", "twelve figures",
	   "twelve massive figures", 
	   "sentinels", "massive sentinels", "twelve sentinels",
	   "twelve massive sentinels"}),  
	      "There are twelve evenly-spaced objects encircling the outside "
	     +"edge of the cairn. To the north stands a slender willow, and "
	     +"to the right of it is a granite cube, followed by "
         +"an enormous column, a menacing edifice, "
         +"an imposing monolith, a white stone, a gold structure, "
         +"an ornate spire, an obsidian pillar, a black "
         +"obelisk, a grey standing-stone, and a bluish rock.\n");

    add_item(({"cube", "granite cube", "first guardian", 
	    "first sentinel", "first object", "first figure"}),     
         "@@check_one@@");     // 1, Salilus

    add_item(({"column", "enormous column", "second guardian", 
	    "second sentinel", "second object", "second figure"}),    
        "@@check_two@@");      // 2, Tabris

    add_item(({"edifice", "menacing edifice", "reddish edifice",
        "third guardian", "third sentinel", "third object", "third figure"}),                
        "@@check_three@@");     // 3, Hahabi

    add_item(({"monolith", "imposing monolith", "black monolith",
        "fourth guardian", "fourth sentinel", "fourth object", "fourth figure"}),                                
        "@@check_four@@");      // 4, Plalgus

    add_item(({"stone", "white stone", "limestone", "fifth sentinel",
        "fifth guardian", "fifth object", "fifth figure"}),                                    
        "@@check_five@@");      // 5, Nantur

    add_item(({"structure", "gold structure", "golden structure",
        "sixth guardian", "sixth sentinel", "sixth object", "sixth figure"}),                               
        "@@check_six@@");       // 6, Nitikas

    add_item(({"spire", "ornate spire", "greenish-grey spire",
        "seventh guardian", "seventh sentinel", "seventh object",
		"seventh figure"}),                         
        "@@check_seven@@");      // 7, Cahor

    add_item(({"pillar", "obsidian pillar", "black pillar", "eighth object",
        "eighth guardian", "eighth sentinel", "eighth figure"}),                              
        "@@check_eight@@");     // 8, Tacritan

    add_item(({"obelisk", "black obelisk", "metal obelisk",
        "ninth guardian", "ninth sentinel", "ninth object", "ninth figure"}),                                 
        "@@check_nine@@");      // 9, Zaren

    add_item(({"standing-stone", "grey standing-stone",
        "tenth guardian", "tenth sentinel", "tenth figure", "tenth object"}),                                    
        "@@check_ten@@");       // 10, Sabrus

    add_item(({"rock", "bluish rock", "blue rock", "pale rock",
        "eleventh guardian", "eleventh sentinel", "eleventh object", 
		"eleventh figure"}),                           
        "@@check_eleven@@");     // 11, Hizarbin

    add_item(({"willow", "slender willow", "twelfth guardian",
	    "twelfth sentinel", "twelfth object", "twelfth figure"}),
        "@@check_twelve@@");      // 12, Jazur

  ahdown(HILL+"hill6","west");
  ahdown(HILL+"hill9","east");

  AE(PATH+"entry","south",0,1);

  start_avtime();
  reset_room();
}

void reset_room()
{

}

string check_one()
{
    string s1, s2;

    if (1 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
        s2 = "This is a perfect cube, as large as a horse, "
            +"made from solid granite. It stands between "
            +"the enormous column and the slender willow, and "
            +"carved on the top face is an inscription. The "
            +"cube faces to the northeast.";
    return s2 + s1;
}

string check_two()
{
    string s1, s2;

    start_avtime();
    if (2 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";

        s2 = "This huge column is made from some dull "
            +"metal, possibly lead. It is perfectly round "
            +"and smooth, and tapers to a rounded end at "
            +"the top. Etched all around the middle is "
            +"some thin writing. The column faces northeast, "
            +"and stands between the granite cube and the "
            +"menacing edifice.";
    return s2 + s1;
}

string check_three()
{
    string s1, s2;

    if (3 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
           s2 = "The tremendous edifice towers above you, the "
            +"height of three tall men. It seems to emanate "
            +"heat from its reddish-black surface, and "
            +"in barely visible etchings along its surface "
            +"are some letters. It faces due east, standing "
            +"between the enormous column and the imposing "
            +"monolith.";
    return s2 + s1;
}

string check_four()
{
    string s1, s2;

    if (4 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "Rising to the height of at least three "
            +"tall humans, this monolith seems to inspire "
            +"awe. It is made from a shiny black stone "
            +"that is interspersed with veins of red "
            +"minerals. The structure faces southeast, and "
            +"carved vertically along it are some spidery "
            +"letters. It stands between the white stone "
            +"and the menacing edifice.";
    return s2 + s1;
}

string check_five()
{
    string s1, s2;

    if (5 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "This enormous piece of limestone is a dull "
            +"white, and what little light there is "
            +"seems to be captured by its face, making "
            +"it shimmer softly. The rock faces to the "
            +"southeast, and it stands between the "
            +"imposing monolith and the gold structure. "
            +"Inscribed in the base of the stone are some "
            +"strange runes.";
    return s2 + s1;
}

string check_six()
{
    string s1, s2;

    if (6 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "This enormous gold structure is a thin "
            +"rectangle, as tall as two men. Across "
            +"the middle is an inscription that "
            +"has been melted into the soft metal and "
            +"filled in with silver. The structure faces "
            +"due south, and stands between the white stone "
            +"and the ornate spire.";
    return s2 + s1;
}

string check_seven()
{
    string s1, s2;

    if (7 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "This ornate spire rises up from the "
            +"ground to the height of a tall human. It "
            +"is made from a soft greenish-grey metal that "
            +"is imbedded with semi-precious stones and "
            +"bizarre swirling designs. It lies between "
            +"the obsidian pillar and the gold structure, "
            +"facing southwest. Along the base of the spire "
            +"are some words painted in a delicate and "
            +"flowing script.";
    return s2 + s1;
}

string check_eight()
{
    string s1, s2;

    if (8 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "This deep black pillar has eight perfect "
            +"facets along it that end in a flat top. It "
            +"rises up to the height of two men, and faces "
            +"towards the southwest. Some deeply inscribed "
            +"runes run along the inner facet. The pillar "
            +"rests between the ornate spire and the "
            +"black obelisk.";
    return s2 + s1;
}

string check_nine()
{
    string s1, s2;

    if (9 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "This dark obelisk towers above you, the height "
            +"of three men. It is made of a jet black metal "
            +"that seems to suck all the light into its "
            +"surface. Lightly etched along the base is an "
            +"inscription in strange letters. It stands "
            +"between the obsidian pillar and the grey "
            +"standing stone, facing due west.";
    return s2 + s1;
}

string check_ten()
{
    string s1, s2;

    if (10 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "This is a simple standing stone, about as high "
            +"as a gnome and facing towards the northwest. Upon "
            +"its uneven top are painted a few words in dark "
            +"blue. The stone rests between the black "
            +"obelisk and the bluish rock.";
    return s2 + s1;
}

string check_eleven()
{
    string s1, s2;

    if (11 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "This large rock is made from some pale blue "
            +"stone that seems to glimmer with an unearthly "
            +"glow. It stands between the slender willow and "
            +"the grey standing stone, and carved around the "
            +"base are some spidery letters. The stone faces "
            +"northwest.";
    return s2 + s1;
}

string check_twelve()
{
    string s1, s2;

    if (12 != (get_avenir_hour()))
        s1 ="\n";
    else
        s1 =" It seems to be glowing with a pale light.\n";
    
            s2 = "This thin and delicate tree rises inexplicably "
            +"from the stoney dead ground. Its branches reach "
            +"out overhead, swaying gently in an invisible "
            +"wind. Carved into the wood of the base is "
            +"an inscription. The willow faces due north, "
            +"and rests between the bluish rock and the "
            +"granite cube.";
    return s2 + s1;
}


int 
read(string what)
{
   string str;
   int mem;

   NF("Read what?\n");

   if(!what || what == "") return 0;

   if(!parse_command(what, ENV(TP), "[the] 'inscription' / 'writing' / 'letters' / "+
                "'script' / 'words' / 'runes' / 'rune' "+
                "%s", str))
            return 0;

   NF("Try to read the writing on <object description>.\n");
   if(!parse_command(what, ENV(TP), "[the] 'inscription' / 'writing' / 'letters' / "+
                "'script' / 'words' / 'runes' / 'rune' 'on' [the] "+
                "[massive] / [large] / [tall] / [menacing] / [black] / "+
                "[white] / [gold] / [enormous] / [imposing] / [obsidian] "+
                "[granite] / [slender] / [ornate] / [grey] / [bluish] %s", str))
            return 0;

   mem = member_array(str, objects);

   if (mem == -1)  return 0;

   if(TP->query_skill(SS_LANGUAGE) < difficulty[mem])
     {
       NF("You try to read the writing, but the language "
         +"of the inscription is beyond your grasp.\n");
       return 0;
     }
   else
      write(writings[mem]+".\n");
   return 1;
}


// Make the banshee appear.
void
visit(object ob)
{ 
    if (!ban)
    {
        ban = clone_object("/d/Avenir/common/dead/mon/banshee");
        ban->move(TO);
    }
    return;
}

// Banshee is nice enough if she can interact with them.
int 
nice_ban(object tp)
{
	
    if (interactive(tp))
    {
	    tp->catch_msg("The ground beneath you "
	        +"suddenly gives way!\nYou slide down into darkness.\n");
		tp->add_prop(ABDM, 1);	
	    tell_room(ENV(tp),QCTNAME(tp)+
	        " suddenly falls through the ground!\n", tp);
    	tp->move_living("M", HILL +"falling", 0, 1);
    }

}	

// Banshee is nice to them. She likes their death mask. 
int
mask_ban(object tp)
{
	
    if (interactive(tp))
    {
	    tp->catch_msg("The ground beneath you "
	        +"suddenly gives way!\nYou slip down into darkness.\n");
		tp->add_prop(ABDM, 1);	
	    tell_room(ENV(tp),QCTNAME(tp)+
	        " suddenly falls through the ground!\n", tp);
    	tp->move_living("M", MARSH +"falling", 0, 1);
    }
}	

// Move player to the pit of despair in the catacombs
// where-ever they are, Because the Gods are angry.
void
bad_fall(object tp)
{
    // If she somehow killed player, don't interrupt death process.
    	if (tp->query_ghost())
    	    return;
		
    ban->command("emote flashes dark eyes full of rage and death");
    // Make it look like a special attack of some sort.
    ban->command("emote raises her fist and throws a ball of light "
        +"in your direction.");
	tp->catch_msg("The ground beneath you suddenly gives way!\n"
	    +"You fall into darkness.\n");
    tp->add_prop(ABDM, 1);	
	tell_room(ENV(tp),QCTNAME(tp)+
	    " suddenly falls screaming into the bowels of the cairn!\n", tp);
    tp->move_living("M", CRYPT +"pit_falling", 0, 1); 
	STATSERV_LOG_EVENT("crypt", "tossed into pit by Banshee");
}	

// Oooh they've done it now. They are going to regret it.
void
make_banshee_mad(object tp)
{
	ban->scream("A shriek of banshee rage echoes from the top of the cairn.");
	ban->command("emote towers with rage, looming over you.");
	ban->command("say You dare to disrespect the Guardians?");
	ban->command("$kill "+ OB_NAME(tp));    // She's mad now!
	tp->set_fatigue(tp->query_max_fatigue() / 2); // Take half of fatigue.
	set_alarm(6.0, 0.0, &bad_fall(tp));     // They fall.	

}

// Player is doing something disrespectful to the guardians.	
int
bad_touch(string str)
{
    string which;
    int mem, num;
    object flux;
    
    NF(CAP(QVB) +" at which guardian?\n");
    if(!strlen(str))
        return 0;

    if(parse_command(str, ({}), "[to] / [on] / [at] [the] %s 'object' / 'guardian' / 'sentinel' "
	    +"[to] / [of] [the] [hour]", which))
	{
        num = LANG_WORD2ORD(which);
    }
    if(!num)
	{
       num = member_array(str, objects) + 1;
	}
    if(!num || num > sizeof(objects))
    {
       NF("Do what at which guardian? Are you sure you want to do this?\n");
	   // They can't say they weren't warned.
       return 0;
    }
    which = LANG_ORD2WORD(num);
	
	// Make sure banshee is here to do her role.
    visit(TP);
    
	// You've done something blasphemous. Now you're going to pay.
	write("You "+ QVB +" at the "+ which +" guardian.\n");       
    say(QCTNAME(TP) +" does something to one of the massive objects.\n");
    flux = find_object("/d/Avenir/common/source_flux");
    flux->special_flux("The light of the Source momentarily flashes "
        +"with reddish light.\nYou get the feeling that the gods "
        +"of Sybarus have been angered.\n");	   
	set_alarm(2.0, 0.0, &make_banshee_mad(TP));
	STATSERV_LOG_EVENT("necronisi", "Defiled a Guardian of the Hours");
    return 1;
}


/* Player is moved to a room where they are falling 
 * before landing in the catacombs
 */
void
make_me_fall(object tp)
{
    if (interactive(tp))
    {
	    tp->catch_msg("The ground beneath you "
	        +"suddenly gives way!\nYou fall into darkness.\n");
		tp->add_prop(ABDM, 1);	
	    tell_room(ENV(tp),QCTNAME(tp)+
	        " suddenly falls through the ground!\n", tp);
    	tp->move_living("M", CRYPT +"falling", 0, 1);
		STATSERV_LOG_EVENT("crypt", "Entered crypt by Banshee");
    }
}



/* Player prays to the guardian stone for the Hour.
 * Banshee will drop players in more favorable areas if they have 
 * quickness or a death mask.
 */
int
check_touch(string str)
{
    string which;
    int mem, num, t;

    t = get_avenir_hour();

    NF("Pray before which guardian?\n");
    if(!strlen(str))
        return 0;

    if(parse_command(str, ({}), "[to] / [before] [the] %s 'object' / 'guardian' / 'sentinel' "
	    +"[to] / [of] [the] [hour]", which))
	{
        num = LANG_WORD2ORD(which);
    }

    if(!num)
	{
       num = member_array(str, objects) + 1;
	}
    if(!num || num > sizeof(objects))
    {
       NF("Pray before which guardian of the hour? The first guardian? The eleventh guardian?\n");
       return 0;
    }
    which = LANG_ORD2WORD(num);

    // Are they praying to the right guardian for the Hour? 
	// If no then nothing happens.
    if (num != t)
    {
        write("You pray before the "+ which +" guardian.\n"+
            "You wait a while, but nothing seems to happen.\n");
		say(QCTNAME(TP) +" prays before one of the massive objects.\n");
        return 1;
    }
    // Make sure banshee is here.
	visit(TP);
	
	// They've found the right guardian.    
	STATSERV_LOG_EVENT("crypt", "Entered crypt by Banshee");
	
	write("You pray before the "+ which +" guardian.\n"+
        "Something is happening.\n");
	say(QCTNAME(TP) +" prays before one of the guardians.\n");	
    FLUX("\nThe Source brightens directly above you. Something has "+
	    "pleased the Gods.\n"); 
	// Are they wearing a death mask? Be nice.
	if (TP->query_prop(DMASK_PROP))
	{
		ban->commmand("say What a beautiful death mask.");
		set_alarm(3.0, 0.0, &mask_ban(TP));
		return 1;
	}
	
	// Are they moving fast enough to interact with the Banshee?
    // She's nicer if you are.	
	if (TP->query_prop(LIVE_I_QUICKNESS) > 25)
    {	
        ban->command("whisper to "+ OB_NAME(TP) +" Be careful down there. "
		  +"I hope you have a token and some torches.");
		set_alarm(3.0, 0.0, &nice_ban(TP));
		return 1;
	}

	// If not, just dump you into the catacombs
	set_alarm(2.0, 0.0, &make_me_fall(TP));		
    return 1;
}

// They've angered the gods--give them a goood scare.
void
rumble(object ob, object amulet)
{
    ob->catch_tell("Your "+amulet->short()+" levitates "+
        "up from your hands and shatters into a thousand "+
        "tiny pieces.\n");
    amulet->remove_object();
    ob->catch_tell("The ground underfoot rumbles ominously.\n"+
        "You have a feeling that your very presence is "+
        "offensive to the guardians of this place. Perhaps "+
        "you'd better go now, before something hideous "+
        "happens to you!\n");
    tell_room((ob), "Something golden rises from "+ QCTNAME(ob)+
        "'s grasp and shatters into a thousand pieces.\n"+
        "The ground underfoot rumbles ominously.\n"+
        "You have a feeling that this is not a good "+
        "place to be right now!", ob);
    ob->add_panic(100);
    ob->panic();
    return;
}

// The watch (Amulet of the Hours) is present so let them
// know that it is important in this place.
void 
report(object ob, object amulet)
{
   if (!ob)
       return;
   if (environment(ob) != this_object())
       return;
   ob->catch_tell("Your "+amulet->short()+" levitates "+
      "for a moment as it is pulled toward one of the "+
      "massive objects on the hilltop.\n");
   return;
}

void 
enter_inv(object ob, object from)
{
    object amulet;

    ::enter_inv(ob, from);

    if(!interactive(ob)) return;

    // Do they have the watch?
    amulet = present("_avenir_hours_amulet_", ob);
    if(amulet)
    {
		
	    STATSERV_LOG_EVENT("necronisi", "Visited cairn with watch");	
		// Have they angered the Gods?
        if (IS_INFIDEL(ob))
        {
            set_alarm(2.0, 0.0, &rumble(ob, amulet));
            return;
        }
        // Respond to presence of the watch
        set_alarm(2.0, 0.0, &report(ob, amulet));
	}
	
	// Make Banshee appear
	if (!ban)
    {
	    set_alarm(itof(5 +(random(10))), 0.0, &visit(ob));
		return;
    }


}

void
init()
{
    ::init();
	
    add_action("read", "read");
   
    add_action("check_touch", "revere");
    add_action("check_touch", "worship");
    add_action("check_touch", "pray");
    add_action("check_touch", "beg");
    add_action("check_touch", "kneel");
    add_action("check_touch", "bow");
	add_action("check_touch", "curtsey");
    add_action("check_touch", "touch");
	    
	add_action("bad_touch",   "poke");
    add_action("bad_touch",   "kick");
    add_action("bad_touch",   "spit");
    add_action("bad_touch",   "grope");
    add_action("bad_touch",   "fart");
	add_action("bad_touch",   "sneeze");
    add_action("bad_touch",   "twiddle");
}

   
