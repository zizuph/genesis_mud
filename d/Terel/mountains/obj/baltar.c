// updated by Lilith March 2009
// added functionality to make torches shed darkness instead of light
// by touching them to a burning corpse on the altar. This can only
// be done in a 90 second window once an hour. Darkness effect
// on torches only lasts until torches burn out.

inherit "/std/container";
#include "/d/Terel/guilds/vamp/guild.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>

#define ALTAR "_live_i_altar_action"

int burn;

void
create_container()
{
    object skull;
   
    set_name("altar");
    add_name("altar of darkness");
    set_short("altar");
    set_pshort("altars");
    set_long("A long black obsidian altar with a small niche. @@blood_test@@\n");
    add_prop(CONT_I_WEIGHT,     90000);    /* It weighs 1 Kg            */
    add_prop(CONT_I_MAX_WEIGHT, 195000);   /* It can contain up to 5 Kg  */
    add_prop(CONT_I_VOLUME,     200000);   /* It measures 3 Ltr         */
    add_prop(CONT_I_MAX_VOLUME, 275000);   /* It can contain 10 Ltr       */
    add_prop(CONT_I_RIGID, 0);             /* It is not a rigid object       */
    add_prop(CONT_I_CLOSED, 0);
    add_prop(CONT_I_LOCK, 0);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_TRANSP, 1);
    add_prop("proper", time() - 3600);

    seteuid(getuid(this_object()));
    skull=clone_object("/d/Terel/mountains/obj/skull");
    skull->move(this_object());
   
}

void
init()
{
    ::init();
    add_action("do_worship",    "worship");
    add_action("do_worship",    "kneel");
    add_action("do_kiss",       "kiss");
    add_action("do_mutilate",   "mutilate");
    add_action("do_mutilate",   "offer");
    add_action("do_mutilate",   "sacrifice");
    add_action("do_touch",      "touch");
    add_action("do_touch",      "cleanse");
    add_action("do_touch",      "burn");
    add_action("do_pray",       "pray");
}

int
do_pray(string str)
{
    if (!strlen(str)) 
        return 0;

    notify_fail("What?\n");
    if (!parse_command(str, ({ }),
        "[at] / [before] [the] [black] [obsidian] 'altar'"))
        return 0;  
    /* Get appropriate message, set altar prop */
    if (TP->query_guild_member("Necromancers Of Vile Darkness"))
    {
        write("You incline your head and pray before the altar.\n "+
            "The scent of death and decay tantilizes your nose and "+
            "and necromantic energy pervades your being.\n");
        tell_room(environment(TP),
          QCTNAME(TP) + " appears to pray before the black altar!\n", TP);
        TP->add_prop(ALTAR, 1);
        return 1;
    }

    /* Get appropriate message, set altar prop */
    if (IS_BG(TP))
    {
        write("You incline your head and pray before the altar, "+
            "honouring the dark power residing here, a power "+
            "reminiscent of The Eldest.\n");
        tell_room(environment(TP),
          QCTNAME(TP) + " appears to pray before the black altar!\n", TP);
        TP->add_prop(ALTAR, 1);
        return 1;     
    }
    /* Get appropriate message, set altar prop */
    if (IS_VAMP(TP))
    {
        write("You incline your head and pray before the altar.\n "+
            "The coppery scent of blood washes over you and "+
            "and a feeling of ecstasy pervades your being.\n"+
            "Here resides a power with a taste similar to "+
            "that of The Eldest...\n");
        tell_room(environment(TP),
          QCTNAME(TP) + " appears to pray before the black altar!\n", TP);
        TP->add_prop(ALTAR, 1);
        return 1;
        
    }    
    /* Get appropriate message, set altar prop */
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        write("You incline your head and pray before the altar.\n "+
            "The coppery scent of blood washes over you and "+
            "and a feeling of ecstasy pervades your being.\n");
        tell_room(environment(TP),
          QCTNAME(TP) + " appears to pray before the black altar!\n", TP);
        TP->add_prop(ALTAR, 1);
        return 1;
    }
    /* Prayed but no benefit cuz you're a goodie, add panic */
    if (TP->query_alignment() > 300)
    {
        write("You sense dark magick and great evil here.\n");
        tell_room(environment(TP),
          QCTNAME(TP) + " tries to pray before the black altar!\n", TP);
        TP->add_panic(100);
        return 1;
    }
    /* You're not a goodie, but you're not dark enough */
    write("Something dark and ancient trembles at the edges of your "+
       "eyesight.\n");
    tell_room(environment(TP),
      QCTNAME(TP) + " appears to pray before the black altar!\n", TP);

    return 1;

}


int
do_mutilate(string str)
{
    object corp;
   
    if (!str)
        return 0;
 

    if (!parse_command(str, ({ }),
       "[the] 'corpse' [at] / [on] / [over] [the] [black] [obsidian] 'altar'"))
    {
        notify_fail(capitalize(query_verb()) +" what at the altar?\n");
        return 0;
    }
    if (!present("corpse", ENV(TO))) 
    {
        TP->catch_msg("Your offering does not appear to be acceptible.\n");
        return 1;
    }
    if (!TP->query_prop(ALTAR))
    { 
        TP->catch_msg("You seem to be missing an important step in "+
            "using the altar properly.\n");
        return 1;
    }
    if (TO->query_prop("bloodied")) 
    {
        TP->catch_msg("An offering to the darkness was recently made.\n"+
        "You must cleanse the altar by fire in order to proceed.\n");
        return 1;
    }
    if (query_prop("proper") > time())
    {
       TP->catch_msg("The altar's necromantic energies are still "+
          "recovering from its recent cleansing.\n");
       return 1;
    }

    corp = present("corpse", ENV(TO));
    TP->catch_msg("You mutilate the corpse at the black altar!\n");
    TP->add_prop(ALTAR, 2);
    tell_room(environment(TP),
        QCTNAME(TP) + " mutilates " + corp->short() +" at the black altar!\n", TP);
    tell_room(ENV(TO), "The dead blood from the corpse slowly flows into the "+
        "altar's niche.\n");            
    TP->catch_msg("The blood on thy hands shall be glory to the darkness.\n");
    add_prop("bloodied", 1);
    corp->remove_object();

    return 1;
}

void 
burn()
{
    tell_room(ENV(TO), "The altar burns brightly until all traces " +
        "of the corpse and its blood are gone from its smooth "+
        "obsidian face.\n");
    remove_prop("bloodied");
    /* an hour must elapse before this can be done again */
    add_prop("proper", time() + 3600);
    remove_prop("bloodied");
    burn = 0;
}

int
do_touch(string str)
{
    object torch;

    if (!str)
        return 0;

    if (parse_command(str, all_inventory(TP), "[the] %o 'to' [the] 'altar' / 'corpse'", torch) ||
         parse_command(str, all_inventory(TP), "[the] 'altar' / 'corpse' 'with' [the] %o", torch))
    {
        if (!TP->query_prop(ALTAR) > 1)
        { 
            TP->catch_msg("You seem to be missing an important step in "+
                "using the altar properly.\n");
            return 1;
        }
   
        if (burn && torch->query_prop(OBJ_I_LIGHT))
        {
            tell_room(ENV(TO), "The "+ torch->short() +" touched to the altar "+
                "begins to shed darkness instead of light!\n");     
            /* Torch sheds negative light based on previous strength */       
            torch->set_strength(-(torch->query_strength()));          
            torch->extinguish_me();
            tell_room(ENV(TO), "A gust of wind roars by, extinguishing the "+ torch->short() +".\n");
            torch->set_short("charred "+ torch->short());
            torch->add_adj("charred");

            return 1;
        }       
        if (torch->query_prop(OBJ_I_LIGHT) && TO->query_prop("bloodied")) 
        {
            TP->catch_msg("You touch the torch to the altar.\n");
            tell_room(ENV(TO), QCTNAME(TP) + " touches the altar with a burning torch.\n", TP);
            tell_room(ENV(TO), "The corpse on the altar begins to burn, emitting a charnal smoke!\n");
            tell_room(ENV(TO), "The "+ torch->short() +" touched to the altar "+
                "begins to shed darkness instead of light!\n");  
            torch->set_strength(-(torch->query_strength()));          
            torch->extinguish_me();
            tell_room(ENV(TO), "A gust of wind roars by, extinguishing the "+ torch->short() +".\n");
            torch->set_short("charred "+ torch->short());
            torch->add_adj("charred");

            /* You have 90 seconds before the corpse is consumed */
            burn = set_alarm(90.0, 0.0, "burn");
            return 1;
        }
    }

    /* I am too good to perform rituals to the darkness */
    if (TP->query_alignment() > 300)
    {
        write("You cannot force yourself close enough to the altar to do that, "+
            "so greatly do you fear the evil magick which emanates from it.\n");
        TP->add_panic(100);
        return 1;
    }

    tell_room(ENV(TO), QCTNAME(TP) + " touches the altar.\n", TP);
    TP->catch_msg("You touch your fingertips to the altar. A powerful tingling "+
        "rushes up your arm, followed by intense numbness!\nYou jerk your hand "+
        "away and the feeling fades.\n");
    TP->add_panic(10);
    return 1;
}


int
do_kiss(string str)
{
   object book;
   
    if (!str)
        return 0;

    notify_fail("What?\n");
    if (!parse_command(str, ({ }),
        "[the] [black] [obsidian] 'altar'"))
        return 0;  

    /* I am too good to perform rituals to the darkness */
    if (TP->query_alignment() > 300)
    {
        write("You cannot force yourself close enough to the altar to do that, "+
            "so greatly do you fear the dark magick which emanates from it.\n");
        TP->add_panic(100);
        return 1;
    }

    TP->catch_msg("You kiss the altar.\n");
    tell_room(ENV(TO), QCTNAME(TP) + " kisses the altar.\n", TP);

    book = present("book_of_darkness", ENV(TO));
    if (book)
    {
        if (TO->query_prop("bloodied")) 
        {
            tell_room(ENV(TO), "A darkness settles over this place!\n");
            TO->add_prop(OBJ_I_LIGHT, -10);
            book->remove_seal();
            return 1;
        }
    }
    return 1;
}

int
do_worship(string str)
{
    object book;

    notify_fail("What?\n");
    if (!parse_command(str, ({ }),
        "[at] / [before] [the] [black] [obsidian] 'altar'"))
        return 0;  
   
    write("You kneel down and worship before the ancient black altar.\n");
    say(QCTNAME(TP) + " kneels down and worships before the black altar.\n");

    /* I am too good to perform rituals to the darkness */
    if (TP->query_alignment() > 300)
    {
        write("Through your knees and legs you can feel the great evil that "+
           "saturates the very stones of this place.\nA wave of fear claws "+
           "at your middle. You wonder if you will be able to stand and "+
           "leave this light-forsaken place.\n");
        TP->add_panic(100);
        return 1;
    }


    book = present("book_of_darkness", ENV(TO));
    if (book) 
    {
        tell_room(ENV(TO), "A feeling of dread seems to overtake this place.\n");
        call_out("thunder", random(12));
    }

    return 1;
}

int
thunder()
{
    tell_room(ENV(TO), "Thunder sounds through the dark and twisted stormlit sky!\n");

    if (TP->query_prop("thunder")) 
    {
        TP->catch_msg("Lightning strikes you!\n");
        TP->heal_hp(-100);
        tell_room(ENV(TO), QCTNAME(TP) + " is struck by lightning!\n", TP);
        return 1;
    }
    TP->add_prop("thunder", 1);
    TP->catch_msg("You draw strength from the black book!\n");
    return 1;
}


string
blood_test()
{
    string add_long;

    if (TO->query_prop("bloodied"))
    {
        add_long = "Rivulets of dried blood mar the polished surface, "+
            "as does the mutilated remains of a corpse.";
    }
    else 
        add_long = "";

    return add_long;
}    


void
disturbance()
{
   object *userlist;
   int i;
   
   userlist = users();
   for (i=0; i<sizeof(userlist); i ++)
   if (userlist[i]->query_guild_member("The Ancient Mystic Order"))
      userlist[i]->catch_msg("You sense a disturbance in the ancient world.\n");
}

mixed
test_magic()
{
    if (TP->query_alignment() > 300)
    {
        return "The dark and evil magick pervading this place overpowers your own.\n";
    }
    else return 0;
}

string 
block_teleport()
{
    return "Some oppressive force prevents you from leaving here "+
        "through magical means.\n";
}

string 
block_scry()
{
    return "Some oppressive force prevents you from seeing here "+
        "through magical means.\n";
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    to->add_prop(ROOM_M_NO_MAGIC, "@@test_magic@@");
    to->add_prop(ROOM_M_NO_TELEPORT,"@@block_teleport@@");
    to->add_prop(ROOM_M_NO_SCRY,"@@block_scry@@");

}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    from->remove_prop(ROOM_M_NO_MAGIC);

}
