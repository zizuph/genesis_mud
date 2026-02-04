/*
    Modified 3 May 2003, by Bleys
        - fixed a typo when approaching Clio
*/

#pragma save_binary

inherit "/std/object.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"
#include <cmdparse.h>
#include <ss_types.h>

#define MUSE_NUMBER(muse) \
    (member_array(muse, ({ "Thalia", "Calliope", "Melpomene", "Clio" })) + 1)

#define GUILD_CLOSED
#undef GUILD_CLOSED

string THIS_PED;

void
init()
{
    add_action("do_approach", "approach");
    add_action("do_dedicate", "dedicate");
}

/*
 * Function:	set_ped
 * Description: Sets the Very Important Variable THIS_PED and picks a matching
 *		long description. The object which clones the pedestal should
 *		call this function first thing.
 * Arguments:	str - may be one of the following:
 *	    "lute", "recorder", "dulcimer", "harp", "shawm", "viol", "trumpet"
 */
void
set_ped(string str)
{
    THIS_PED = str;
    add_name(({"instrument", THIS_PED}));
    set_pname("jungle_boys");		        /* Not to be called */
    set_pshort("marble pedestals");
    switch(THIS_PED)
    {
        case "lute":
             set_long(BS("This marble pedestal, sparse in line and elegant in its " +
		"simplicity, supports a wondrous instrument: the "+THIS_PED+".\n")+
                BS("The pear-shaped body of this beautiful lute has " +
                "been crafted from striped ribs of yew wood. " +
                "From the balsam wood bridge up the fretted neck " +
                "six strings have been tightly stretched, the lower " +
                "five in double courses. A tiny marble cameo has been carved " +
		"on each tuning-peg, depicting the elegant figure of a woman. "+
                "A circular hole in the lute's body, beneath the " +
                "strings, allows the instrument to resonate " +
                "strongly.\n"));
            break;

        case "recorder":
             set_long(BS("This marble pedestal, sparse in line and elegant in its " +
		"simplicity, supports a wondrous instrument: the "+THIS_PED+".\n")+
                BS("Fashioned from a deep red cherry wood, this recorder " +
                "is actually three sections fitted together: a flat, " +
                "lateral mouthpiece; a long middle piece with eight " +
                "fingerholes; and a small bell-shaped piece on the " +
                "end. A twirling vine of ivy has been carved into the " +
                "wood, running up and down the instrument's length, " +
		"curling at last around a florid inscription, a single word " +
		"whose form you can't quite make out.\n"));
            break;
	    
        case "dulcimer":
            set_long(BS("This marble pedestal, sparse in line and elegant in its " +
		"simplicity, supports a wondrous instrument: the "+THIS_PED+".\n")+
                BS("This beautiful dulcimer has been crafted from a " +
                "large, trapezoidally shaped piece of white ash wood. " +
                "Two octaves of silvery strings, in double courses, " +
                "are suspended across the width of " +
                "the instrument. These strings weave intricately over " +
                "two central bridges at different heights to produce " +
                "different pitches. Between the two central bridges " +
                "a silhouette has been painted, an image you somehow can't " +
                "quite make out. Two hammers are kept in a " +
                "small compartment on the dulcimer's back.\n"));
            break;

        case "harp":
             set_long(BS("This marble pedestal, sparse in line and elegant in its " +
		"simplicity, supports a wondrous instrument: the "+THIS_PED+".\n")+
                BS("This harp, made of a dark brown and fragrant spruce " +
                "wood, measures two and a half feet and is meant to be " +
                "pressed against the chest or rested in the lap. A " +
                "broad resonator supports a sounding board from which " +
                "29 strings, tuned diatonically, stretch up to the " +
                "neck, gently curving like a swan's. A narrow " +
                "forepillar reaches from the resonator's base to the " +
                "neck, forming a basic triangle. Above the point at " +
                "which the neck and forepillar meet has been placed the " +
                "carved and painted head of an astonishingly beautiful "+
		"woman.\n"));
            break;

        case "shawm":
             set_long(BS("This marble pedestal, sparse in line and elegant in its " +
		"simplicity, supports a wondrous instrument: the "+THIS_PED+".\n")+
                BS("This shawm is a long conical bore that flares out " +
                "into a two-inch bell. Made of stained walnut wood, it "+
                "may be disassembled into three basic parts: a small " +
                "mouthpiece with double-reed and pirouette, a long " +
                "section with drilled fingerholes, and the bell. " +
                "Three of the lower fingerholes are covered with pads; "+
                "keys maneuver the pads, making the shawm easier to " +
                "play. This is an alto shawm and its range is low, " +
                "rich, and melancholy.\n"));
            break;

        case "viol":
	    set_long(BS("This marble pedestal, sparse in line and elegant in its " +
		"simplicity, supports a wondrous instrument: the "+THIS_PED+".\n")+
                BS("This dark spruce-wood instrument is roughly two " +
                "feet in length. The sounding-box has a flat back " +
                "and rounded shoulders which curve inward and then " +
                "out again to round off at the bottom. Six strings, " +
                "tuned in fourths and thirds, stretch over the bridge, "+
                "up a fretted fingerboard, and are held by tuning-pegs "+
                "at the top of the neck. A bow of pine lays atop the viol. " +
                "While playing the viol, the instrument may be rested "+
                "on the knee or pressed against the arm and shoulder. " +
                "Twin fresco-like paintings adorn the " +
                "sounding-box, beneath resonating C-shaped holes.\n"));
            break;

        case "trumpet":
            set_long(BS("This marble pedestal, sparse in line and elegant in its " +
		"simplicity, supports a wondrous instrument: the "+THIS_PED+".\n")+
                BS("This long and slender trumpet has been fashioned " +
                "out of brass that shines with golden lustre. A silver "+
                "alloy mouthpiece may be detached from the smaller " +
                "end. From the mouthpiece, the bore of the trumpet " +
                "gradually increases in diameter, bending back around " +
                "itself only once and then flaring out into a bell. " +
                "Although the trumpet has no valves or keys, the " +
                "various pitches of the harmonic series may be " +
                "produced by manipulating the shape of the ombouchure " +
                "and pressure of air blown through the mouthpiece.\n"));
            break;
    }
}

/*
 * Note that the object which clones this had better call set_ped()
 * with the type of instrument as an argument.
 */
void
create_object()
{
    set_name("pedestal");
    add_prop(OBJ_M_NO_GET, "You decide that to remove the icon would be in "
    + "the worst possible taste.\n");
    set_adj("marble");
}

int
do_approach(string str)
{
    object  ob;
    string  which_muse;
    string  text;
    mixed *oblist;

    notify_fail("Approach which pedestal?\n");
    if (!str) return 0;    
    if (!parse_command(str, all_inventory(environment(this_player())),
        "[the] %i", oblist) || !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    //if (!parse_command(str, environment(this_player()), "%o", ob))
	return 0;

    if (sizeof(oblist) > 1)
    {
        return 0;
    }

    ob = oblist[0];

    if (ob!=TO())
	return 0;
    seteuid(getuid(TO()));
    if (sizeof(get_dir(BANISHDIR+this_player()->query_real_name()+"_banished")))
    {
	write("You have been banished from this guild! Begone, you are not "
	      + "wanted here.\n");
	return 1;
    }
    if (MEMBER(this_player()))
    {
      

      if (present("minstrel_instrument", this_player()))
      {
          write(BS("You already have an instrument! These "
			     + "icons are for those who have lost their "
			     + "instruments, or who desire to join "
			     + "the Minstrels.\n"));
          return 1;
      }
      else
      {
	this_player()->CM(BS("As you approach the "+THIS_PED+" your head grows faint "
	+ "and the hall around you fades to black. Suddenly a Vision appears: "
	+ this_player()->query_muse_name()+" herself stands before you, and from "
	+ "somewhere nearby the music of the spheres seems to resonate in "
	+ "your very soul. The Lady "+this_player()->query_muse_name()+" smiles at you,"
	+ " her beauty the stuff of legend, and speaks:\n")+BS("Have you lost "
	+ "your instrument, my brave Minstrel? Come, then, take another! "
	+ "Your devotion to my cause has proved itself; now choose whichever "
	+ "of these instruments best pleases you. Dedicate the instrument "
	+ "of your choice to me. We shall begin anew, and spread music across "
	+ "the land!\n"));
	this_player()->CM(BS("You bow your head, overwhelmed. When you next look up "
	+ this_player()->query_muse_name()+" is gone, and the great hall has returned "
	+ "to normal.\n"));
      }

      return 1;
    }	

    which_muse = ({ "Thalia", "Calliope", "Melpomene", "Clio" })[random(4)];
    this_player()->add_prop("_muse_s_chosen", which_muse);
        
    switch(which_muse)
    {
      case "Thalia": 
	text = BS("As you approach the "+THIS_PED+" your head grows faint "
	+ "and the hall around you fades to black. Suddenly a Vision appears: "
	+ "the Muse Thalia herself stands before you, and from somewhere "
	+ "nearby the music of the spheres seems to resonate in your very "
	+ "soul. The beauty of the Lady Thalia is the stuff of legend, and "
	+ "when she turns her merry smile upon you the entire world seems to "
	+ "erupt with joy. She begins to speak, her accents underscored by "
	+ "the happy laughter of thousands:\n")+BS("So, "+this_player()->query_name()
	+ ", you would be a Minstrel? Come, then, join my joyful entourage! I "
	+ "am Thalia, Muse and Mistress of comedy. Dedicate this "+THIS_PED
	+ " to me, and forever follow the comedic Muse!\n")+BS("The vision "
	+ "fades, and the great hall returns to your sight, but a glad "
	+ "laughter still echos faintly in your mind.\n");
	break;
      case "Calliope":
	text = BS("As you approach the "+THIS_PED+" your head grows faint "
	+ "and the hall around you fades to black. Suddenly a Vision appears: "
	+ "the Muse Calliope herself stands before you, and from somewhere "
	+ "nearby the music of the spheres seems to resonate in your very "
	+ "soul. The beauty of the Lady Calliope is the stuff of legend, and "
	+ "when she turns her far-seeing gaze in your direction the sound of "
	+ "battle seems suddenly near. She begins to speak, her powerful voice "
	+ "redolant somehow with tales of ancient heroisms and glorious "
	+ "adventures:\n")+BS("So, "+this_player()->query_name()+", you would be a "
	+ "Minstrel? Come, then, sing the ancient songs with me! I am "
	+ "Calliope, Muse and Mistress of epic poetry. Dedicate this "
	+ THIS_PED+" to me, and forever follow the epic Muse!\n")+BS("The "
	+ "vison fades, and the great hall returns to your sight, but the "
	+ "clash of battle still echoes faintly in your mind.\n");
	break;
      case "Melpomene":
	text = BS("As you approach the "+THIS_PED+" your head grows faint "
	+ "and the hall around you fades to black. Suddenly a Vision appears: "
	+ "the Muse Melpomene herself stands before you, and from somewhere "
	+ "nearby the music of the spheres seems to resonate in your very "
	+ "being. The melancholy beauty of the Lady Melpomene tugs at your "
	+ "soul; her eyes are sad but startlingly clear. In low, pure "
	+ "tones she begins to speak, her voice an amalgam of bitter sorrow "
	+ "and hard-earned wisdom:\n")+BS("I am Melpomene, Muse and Mistress "
	+ "of tragedy. You, "+this_player()->query_name()+", would be a Minstrel? "
	+ "You would seek wisdom in word, and song, and deed? Join your way "
	+ "to mine. It is not a happy way, but it is the most honest; we "
	+ "must journey through the tragic if we are to reach the sublime. "
	+ "Dedicate this "+THIS_PED+" to me, and forever follow the Muse "
	+ "Melpomene!\n")+BS("The vison fades, and the great hall returns to "
	+ "your sight, but the sad, clear tones still echo faintly in your "
	+ "mind...\n");
	break;
      case "Clio":
	text = BS("As you approach the "+THIS_PED+" your head grows faint "
	+ "and the hall around you fades to black. Suddenly a Vision appears: "
	+ "the Muse Clio herself stands before you, and from somewhere "
	+ "nearby the music of the spheres seems to echo through your very "
	+ "being. The beauty of the Lady Clio is the stuff of legend, a "
	+ "timeless presence that invokes fear both and admiration. Her "
	+ "voice is full of power, yet distant, as if it resonated across "
	+ "the ages as she says:\n")+BS("So, "+this_player()->query_name()+", you would "
	+ "be a Minstrel? Come, then, sing with me of the bygone days! I "
	+ "am Clio, Muse and Mistress of history. Dedicate this "+THIS_PED
	+ " to me, and forever follow the historic Muse!\n")+BS("The "
	+ "vison fades, and the great hall returns to your sight, but the "
	+ "resonant voice still echoes faintly in your mind.\n");
	break;
   }
   write(text);
   say(QCTNAME(this_player())+" approaches the pedestal bearing a "+THIS_PED+". "
   +"Suddenly "+this_player()->query_pronoun()+" stiffens, and "
   + "stands as one transfixed. After a bit "+this_player()->query_pronoun()
   + " relaxes, though a far-away look still hovers in "+this_player()->query_possessive()
   + " eye.\n");
   return 1;
}

int
do_dedicate(string str)
{
    object ob, instrument, shadow, book;
    string the_muse;
    int i, book_given_flag;
    mixed *forks;
    string logfile, *loglines;
    mixed why;
    string muse;

    notify_fail("Dedicate what to whom?\n");
    if (!str)
    {
        return 0;    
    }

    if (!parse_command(str, environment(this_player()), "[the] %o 'to' %w", ob, the_muse))
    {
	return 0;
    }

    the_muse = capitalize(the_muse);

    if (ob!=TO())
    {
	return 0;
    }

    setuid();
    seteuid(getuid());

    if (sizeof(get_dir(BANISHDIR+this_player()->query_real_name()+"_banished")))
    {
	write("You have been banished from this guild! Begone, you are not "
	      + "wanted here.\n");
	return 1;
    }

    if (MEMBER(this_player()))
    {
        if (!this_player()->query_muse())
	{
            if ((i = MUSE_NUMBER(the_muse)) < 1)
	    {
                notify_fail("Dedicate the instrument to which muse?\n");
                return 0;
	    }

        MEMBER_MANAGER->set_muse(this_player(), capitalize(the_muse));
            book_given_flag = 1;
            write("Ok.\n");
	}
	else if (the_muse != this_player()->query_muse_name() &&
	    the_muse != lower_case(this_player()->query_muse_name()))
	{
	    write("Your Muse is "+this_player()->query_muse_name()
	    + ". None can change that now.\n");
	    return 1;
	}

        if (!present("minstrel_song_book",this_player()))
        {
	  book = clone_object("/d/Terel/cedric/guild/obj/songbook");

            book->move(this_player(),1);
	    write(this_player()->query_muse_name()+" grants you a new "
		     + "songbook!\n");
	    book_given_flag = 1;
	    
        }
	if ((instrument = present("minstrel_instrument", this_player()))
	    && !book_given_flag)
	{
	    write("Your instrument is already dedicated to "
	    +this_player()->query_muse_name()+". None can change that now.\n");
	    return 1;
	}
	if (!instrument)
	{
	    write(BS("You take hold of the "+THIS_PED+" and "
			       + "hold it aloft, dedicating it to the "
			       + "service of " + this_player()->query_muse_name()
			       + ". Suddenly there is a brilliant flash "
			       + "of light, and the "+THIS_PED
			       + " in your hand becomes as a living "
			       + "thing, warm and vibrant with power. "
			       + "That power swells and your "
			       + THIS_PED + " becomes a true Minstrel's "
			       + "instrument dedicated to "
			       + this_player()->query_muse_name()+" and alive "
			       + "with music...\n"));
	    instrument = clone_object(GUILDOBJ+"instrument");
	    instrument->set_name(THIS_PED);
	    instrument->move(this_player(), 1);
	    instrument->do_things();
	    say(QCTNAME(this_player())+" takes ahold of the carved "+THIS_PED+" and "
		+ "dedicates it to "+this_player()->query_muse_name()+". Suddenly "
		+ "there is a brilliant flash of light and "+QTNAME(this_player())
		+ " is left holding a true Minstrel's instrument!\n");
	    return 1;
	}

        if (!book_given_flag)
	{
            write("You rededicate your instrument to " +
	          this_player()->query_muse_name() + ".\n");
	}

        return 1;
    }

#ifdef GUILD_CLOSED
    if (!this_player()->query_wiz_level() && !wildmatch("*jr", this_player()->query_real_name()))
    {
    write("No new members are being accepted at this time.  Please " +
       "return at a later date.\n");
    return 1;
    }
#endif
    
    if (!(muse = this_player()->query_prop("_muse_s_chosen")))
    {
        write("You have not been chosen by a muse. Approach your " +
              "desired instrument before dedicating it.\n");
         return 1;
    }

    if (the_muse != muse)
    {
        write("You have been chosen by " + muse + ". Dedicate your instrument " +
              "to her or approach another.\n");
	return 1;
    }

    shadow = clone_object(GUILDOBJ+"m_shadow");

    if (stringp(why = shadow->acceptable_member(this_player())))
    {
        write(why);
	shadow->remove_shadow();
	return 1;
    }
/* Hmmm .... lets see how the guild works if we allow all alignments in.
 * If it proves to be a mistake, we can reverse it later.
 *   - Gorboth, December 2007
    else if (this_player()->query_alignment() <= -100)
    {
        write("Your evil soul makes you deaf to the muses. You are unable to join the August Order of Minstrels.\n");
        shadow->remove_shadow();
        return 1;
    }
*/

    else
    {
        i = shadow->shadow_me(this_player(), "layman", "cleric", GUILD_NAME);
    
    if (i==1)
    {
        MEMBER_MANAGER->new_member(this_player());
        MEMBER_MANAGER->set_muse(this_player(), capitalize(muse));
	write(BS("You take hold of the carved "+THIS_PED+" and hold it "
	+ "aloft, dedicating it to the service of "+this_player()->query_muse_name()
	+ ". Suddenly there is a brilliant flash of light, and the icon "
	+ "in your hand becomes as a living thing, warm and vibrant with "
	+ "power. The figure grows and becomes a true Minstrel's "+THIS_PED
	+ ", dedicated to "+this_player()->query_muse_name()+" and alive with "
	+ "music...\n"));
	say(QCTNAME(this_player())+" takes ahold of the carved "+THIS_PED+" and "
	+ "dedicates it to "+this_player()->query_muse_name()+". Suddenly there is "
	+ "a brilliant flash of light and "+QTNAME(this_player())+" is left holding "
	+ "a true Minstrel's instrument!\n");
	write("You have joined "+GUILD_NAME+"!\n");
	SONGBOOK_MANAGER->add_songbook(this_player());
    this_player()->clear_guild_stat(SS_LAYMAN);
	this_player()->set_hear_bells(1);
	this_player()->set_hear_dias(1);
	this_player()->set_hear_ballads(1);
	this_player()->setup_skill_decay();
	instrument = clone_object(GUILDOBJ+"instrument");
	instrument->set_name(THIS_PED);
	instrument->move(this_player(), 1);
	instrument->do_things();
        if (!present("minstrel_song_book",this_player()))
        {
  	    book = clone_object("/d/Terel/cedric/guild/obj/songbook");
            book->move(this_player(),1);
        }
	/* assign the minstrel a random voice */
	this_player()->set_random_voice(this_player()->query_real_name());

	write_file(JOIN_LOG, sprintf("%-12s joined %s\n",
				     this_player()->query_name(),
				     ctime(time())+"\n"));
	return 1;
    }
    else
    {
	write("Something prevents you from dedicating the "+THIS_PED+".\n");
	switch(i)
	{
	    case -4:
		write("It seems your other loyalties prevent you from "
		+ "joining "+GUILD_NAME+".\n");
		break;
	    default:
		write("Error Code "+i+"; report to the Guildmaster.\n");
		break;
	}

	shadow->remove_shadow();
	return 1;
    }
    }
    return 0;
}
