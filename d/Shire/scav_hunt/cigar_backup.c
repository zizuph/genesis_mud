/*
 * A cigar for the massess
 * -- Finwe, October 2003
 * Ideas:
 *  smell the cigar
 */

inherit "/std/object";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

int   smoked = 0,
      cigar_lit = 0,
      max_puffs = 10,
      puffs = 0,
      bite_me = 0,
      cigar_puffs = 1,
      alarm_id;
float smoking = 480.0;

void create_object()
{
    seteuid(getuid());
    set_name("cigar");
    add_name("_shire_cigar_");
    add_name("dark brown cigar");
    set_pshort("dark brown cigars");
    set_adj(({"dark", "brown"}));
    set_short("dark brown cigar");
    set_long("This is a "+short()+". It is made from pipe-weed that has " +
        "been aged for many months. The leaves have been wrapped together " +
//        "tightly to form this " + short() + ".@@cigar_size@@\n");
        "tightly to form this " + short() + ".\n");

}

void
init()
{
    ::init();
/*
    add_action("light_cigar","light");
    add_action("smoke_cigar","smoke");
    add_action("tap_cigar", "tap");
    add_action("extinguish_cigar","extinguish");
    add_action("extinguish_cigar","snuff");
    add_action("bite_cigar", "bite");
    add_action("puff_cigar","puff");
*/
}

int
smoke_cigar(string str)
{
    if (!parse_command(str, TP, "[the] [long] [dark] [brown] 'cigar' "))
    {
        write("Smoke what, the " + short() + "\n?");
        return 1;

    }        

    if (cigar_lit == 0)
    {
        write("Your " + short() + " is not lit.\n");
        return 1;
    }


// check to see if there are enough smokes 
        if(puffs < max_puffs)
        {
           if (get_alarm(alarm_id)) remove_alarm(alarm_id);

            write("You take a nice long draw on your cigar. Afer a few " +
                "moments, you blow a few smoke rings, leaving you very " +
                "relaxed.\n");
            say(QCTNAME(TP) + " takes a nice long draw on " + HIS_HER(TP) + 
                " cigar. After a few moments, " +HE_SHE(TP) + " blows a " +
                "few smoke rings, leaving a very relaxed look on " + 
                HIS_HER(TP) + " face.\n");
            puffs++;
            alarm_id = set_alarm(smoking,0.0,"burns_out");
            return 1;
        }
        else if (puffs == max_puffs)
        {
            write("You take one last long draw on your cigar, savoring " +
                "its last moments. Then you lazily blow a few smoke " +
                "rings, leaving you most relaxed.\n");
            say(QCTNAME(TP) + " takes one last long draw on " + 
                HIS_HER(TP) + ". Then " +HE_SHE(TP) + " blows a few " +
                "smoke rings, leaving a most contented smile on " + 
                HIS_HER(TP) + ".\n");
            puffs ++;
            set_short("old dead cigar");
            set_long("This is a dead old cigar. It is has been smoked " +
                "completely, and not good for anything else. The top " +
                "of it is chewed, like it was gnawed on by someone.\n");
            return 1;
        }
        else 
        {
            write("You can't smoke this cigar. It's nothing more " +
                "than a dead old stub.\n");
            return 1;
        }
        

}

int extinguish_cigar(string str)
{
    if (!parse_command(str, TP, "[the] [long] [dark] [brown] 'cigar' "))
    {
        write("Extinguish what? The cigar is not lit.\n");
        return 0;

    }

    write("You snuff out your cigar carefully.\n");
    say(QCTNAME(TP) + " carefully snuffs out a cigar.\n");
    cigar_lit = 0;
    remove_alarm(alarm_id);
    return 1;
    
}


void burns_out()
{
    write("Your cigar suddenly goes out.\n");
    cigar_lit = 0;
    remove_alarm(alarm_id);
}

int tap_cigar(string str)
{
    
    if (str == "cigar")
    {
        if (cigar_lit == 0)
        {
            write("You tap your unlit cigar absent-mindedly.\n");
            say(QCTNAME(TP) + " taps " + HIS_HER(TP) + " unlit cigar " +
                "absent-mindedly.\n");
            return 1;
        }
        else
        {
            write("You tap your burning cigar lightly, scattering " +
                "ashes everywhere.\n");
            say(QCTNAME(TP) + " taps " + HIS_HER(TP) + " burning cigar " +
                "lightly, scattering ashes everywhere.\n");
            return 1;
        }
    }
    return 0;
}

int bite_cigar(string str)
{
    if (!parse_command(str, TP, "[off] [end] [of] [the] [long] [dark] [brown] 'cigar'  "))
write(str);
//if (str != "end of cigar" || str != "end of cigar off" || str != "cigar")
    {
        write("Bite what, the end of the cigar off?\n");
        return 1;
    }        

    if (cigar_lit == 1)
    {
        write("The end of the cigar is burning. Biting its end is not a " +
            "good idea. You could burn yourself.\n");
        return 1;
    }

    if (bite_me == 1)
    {
        write("After examining the end of the cigar, it looks like it " +
            "has been bitten off already, and is probably ready to light " +
            "and be enjoyed.\n");
        say(QCTNAME(TP) + " turns " + HIS_HER(TP) + " " + short() + 
            " over a few times and examines it.\n");

        return 1;
    }

    
//    if (str == "end of cigar" || str == "end of cigar off" || str == "cigar")
    {
        write("You turn the cigar around and bite the end of it off. " +
            "Then you turn your head and spit the end out.\n");
        say(QCTNAME(TP) + " turns " + HIS_HER(TP) + " cigar around and " +
            "bites the end off. Then " + HE_SHE(TP) + " turns " + 
            HIS_HER(TP) + " head and spits out the end of the cigar.\n");
        bite_me = 1;
        return 1;
    }
    
}


string cigar_size()
{
    string descr;
// never been lit
    if (smoked == 0)
    {
        return " It is brand new and has never been smoked.";
    } 

// cigar is lit
    if (cigar_lit == 1)
    {
        descr = " The cigar is lit, lazily smoking as it burns.";
    }

    switch(puffs)
    {
        case 0..2:
        {
            descr = descr + " It is long and has hardly been smoked.";
            break;
        }

        case 3..4:
        {
            descr = descr + " The " + short() + " is fairly long and " +
                "has been partially smoked.";
            break;
        }
        case 5..6:
        {
            descr = descr + " The cigar is medium in length has been " +
                "smoked half-way.";
            break;
        }
        case 7..8:
        {
            descr = descr + " It is short and has almost been completly " +
                "smoked.";
            break;
        }
        case 9..10:
        {
            descr = descr + " The cigar is stubby and has pretty much " +
                "burned out.";
            break;
        }
    }
    return descr;

}

int puff_cigar(string str)
{
    if (!parse_command(str, TP, "[on] [the] [long] [dark] [brown] 'cigar'"))
    {
        write("Puff on what, the " + short() + "?\n");
        return 1;
    }        

    if (cigar_lit == 0)
    {
        write("The " + short() + " is not lit.\n");
        return 1;
    }


    switch(cigar_puffs)
    {
	    case 1..2:
        {
		    write("You puff on the " + short() + " several times. You " +
                "slowly exhale and blow the smoke out of your mouth.\n");
            say(QCTNAME(TP) + " puffs on the " + short() + " several " +
                "times. Next, " + HE_SHE(TP) + " slowly exhales and " +
                "blows the smoke out of " + HIS_HER(TP) + " mouth.\n");
            cigar_puffs++;
            return 1;
            break;
        }
        case 3:
        {
            write("You puff on the " + short() + " several times. You " +
                "slowly exhale and blow the smoke out of your mouth.\n");
            say(QCTNAME(TP) + " puffs on the " + short() + " several " +
                "times. Next, " + HE_SHE(TP) + " slowly exhales and " +
                "blows the smoke out of " + HIS_HER(TP) + " mouth.\n");
            cigar_puffs = 1;
            if (get_alarm(alarm_id)) remove_alarm(alarm_id);
            puffs++;
            alarm_id = set_alarm(smoking,0.0,"burns_out");
            return 1;
            break;
        }
    }
    
}    


int light_cigar(string str)
{

    if (!parse_command(str, TP, "[the] [long] [dark] [brown] 'cigar' "))
    {
        write("Light what?\n");
        return 1;
    }        

    if (bite_me == 0)
    {
        write("The end is too thick to light. You will need to bite the " +
            "end off first before you can light it.\n");
        return 1;
    }

    if(cigar_lit == 1)
    {
        write("Your " + short() + " is already lit.\n");
        return 1;

    }        

    write("You light the cigar, then give it a couple of quick puffs. " +
        "After a few moments, you blow a few smoke rings, leaving " +
        "you very relaxed.\n");
    say(QCTNAME(TP) + " lights a cigar, then gives it a few quick " +
        "puffs. After a few moments, " +HE_SHE(TP) + " blows a few " +
        "smoke rings, leaving a very relaxed look on " + HIS_HER(TP) + 
        " face.\n");
            
    smoked++;
    cigar_lit = 1;
    puffs++;
    alarm_id = set_alarm(smoking,0.0,"burns_out");
    return 1;

}