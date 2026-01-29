// OBJECT:  handpuppet

    /* Calia Domain 

    HISTORY
    1999, Dec 6 -  Created by Valkira
    
    PURPOSE
    A Christmas toy

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/armour";


#include </sys/wa_types.h>
#include </sys/stdproperties.h>
#include </sys/formulas.h>
#include </sys/macros.h>
#include <options.h>
#include <math.h>
#include <cmdparse.h>

int n = random(3);  /*  Must match number of cases below.  */

// OBJECT DEFINITION

void
create_armour()

{

    /*
     * DESCRIPTION
     */

    set_name("hand puppet");
    add_name("puppet");
    add_name("toy");
    
    switch (n)

    {

        case 0:

        set_short("wolf puppet");
        set_long("A fuzzy grey wolf with ears, eyes and a mouth." +
             " This finely stitched hand puppet was made just" +
             " for you. You notice that a tag is attached to the" +
             " soft inner lining.\n");
        add_name("wolf");
        add_name("wolf puppet");
             add_item(({"ear", "ears"}), "The ears are pointed." +
                 " They wiggle as you move your puppet. \n");
             add_item(("mouth"), "A tongue hangs from the side of the" +
                 " mouth lined with teeth. The mouth is controlled by" +
                 " using your fingers to work the up lips and your" +
                 " thumb to work the lower lip.\n");
             add_item(("tongue"), "It is made of bright red felt.\n");
             add_item(("teeth"), "They are made of soft felt.\n");
                
        break;

        case 1:

        set_short("gopheroo puppet");
        set_long("A furry cuddly gopheroo with ears, eyes and a mouth." +
             " This finely stitched hand puppet was made just for" +
             " you. You notice that a tag is attached to the" +
             " soft inner lining.\n");

        add_name("gopheroo");
        add_name("gopheroo puppet");
        add_item(({"ear", "ears"}), "The ears are small and rounded." +
            " They wiggle as you move your puppet. \n");

        add_item(("mouth"), "This is certainly a wide mouthed" +
            " puppet. The mouth is operated by use of the fingers" +
            " controlling the upper lip and the thumb controlling" +
            " the lower lip.\n");

        break;

        case 2:

        set_short("frog puppet");
        set_long("A goofy green frog with eyes and a mouth." +
            " This finely stitched hand puppet was made just for" +
            " you. You notice that a tag is attached to the" +
            " soft inner lining.\n");
        add_name("frog");
        add_name("frog puppet");
        add_item(("mouth"), "This is certainly a wide mouthed" +
            " frog. The mouth is operated by use of the fingers" +
            " controlling the upper lip and the thumb controlling" +
            " the lower lip.\n");

    }

    /*
     * PROPERTIES
     */

    set_ac(0);
    set_at(A_R_HAND);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_M_NO_SELL, "The merchant says to you: What -" +
        " sell your hand puppet? 'Tis not nice to sell a gift!\n");

    /*
     * ITEMS
     */
     
    add_item(("tag"),
        "  _____________________________________ \n" +
        " |  INSTRUCTIONS FOR YOUR HAND PUPPET  |\n" +
        " |                                     |\n" +
        " |  To smile          - 'toysmile'     |\n" +
        " |  To frown          - 'toyfrown'     |\n" +
        " |  To show agreement - 'toynod'       |\n" +
        " |  To disagree       - 'toyshake'     |\n" +
        " |  To speak          - 'toysay <text>'|\n" +
        " |                                     |\n" +
        " |      Wash in cold water only        |\n" +
        " |_____________________________________|\n");

    add_item(({"eyes", "eye"}), "Called 'googly eyes'," +
        " these buttons are specifically made for puppets" +
        " and dolls. The button consists of a clear shell" +
        " casing and a loose inner pebble which jiggles" +
        " when these button-eyes are shaken.\n");
            
}


// FUNCTIONS

/*
 * Function:  puppet_smile
 * Purpose:   Give a big smile using the puppet!
 */

int
puppet_smile()

{

    object tp = this_player();
    object target;
    
    if (this_object()->query_worn())

    {
        switch (n)

        {

            case 0:
                    
            say(QCTNAME(tp) + " holds " + tp->query_possessive() +
                " grey wolf puppet for all to see. The puppet lips" +
                " are drawn up at the edges in a wolfish grin!\n");
            write("Your wolf puppet gives a wolfish smile.\n");

            break;
                        
            case 1:
                
            say(QCTNAME(tp) + " holds " + tp->query_possessive() +
                " silly gopheroo puppet for all to see. The puppet" +
                " lips are drawn up at the edges in a goofy smile!\n");
            write("Your gopheroo puppet gives a goofy smile.\n");

            break;
            
            case 2:
                
            say(QCTNAME(tp) + " holds " + tp->query_possessive() +
                " goofy frog puppet for all to see. The puppet lips" +
                " are drawn up at the edges in a wide smile!\n");
            write("Your frog puppet gives a wide smile.\n");

            break;

        }
                
        return 1;
                
    }
             
    else

    {

        notify_fail("This is a hand puppet. Wear it on your hand! \n");
        return 0;
    }
        
}

/* Function:  puppet_frown
 * Purpose:   Frown using the puppet!
 */

int
puppet_frown()

{

    object tp = this_player();
    object target;
    if (this_object()->query_worn())

    {

        switch (n)

        {

            case 0:
                
            say(QCTNAME(tp) + " holds " + tp->query_possessive() +
                " grey wolf puppet for all to see. The puppet lips" +
                " are drawn into wolfish snarl.\n");
            write("Your wolf puppet gives a snarling frown.\n");

            break;

            case 1:
                
            say(QCTNAME(tp) + " holds " + tp->query_possessive() +
                " silly goopheroo puppet for all to see. The puppet" +
                " lips are drawn down at the corners a forlorn pout.\n");
            write("Your gopheroo puppet gives a forlorn pout.\n");

            break;

            case 2:
                
            say(QCTNAME(tp) + " holds " + tp->query_possessive() +
                " goofy frog puppet for all to see. The puppet lips" +
                " are drawn down at the corners in a sad frown.\n");
            write("Your frog puppet gives a frown.\n");

            break;

        }
                
    return 1;
                
    }
             
    else

    {

        notify_fail("This is a hand puppet. Wear it on your hand! \n");

        return 0;
    }
        
}

/* Function:  puppet_nod
 * Purpose:   Show your agreement using the puppet!
 */

int
puppet_nod()

{

    object tp = this_player();
    object target;
    if (this_object()->query_worn())

    {
        switch (n)

        {

            case 0:
                
            say(QCTNAME(tp) + " vigorously bobs " +
                tp->query_possessive() + " wolf puppet up and down." +
                " The pointed wolf ears wiggle and the googly eyes" +
                " jiggle in animated agreement.\n");
            write("You let your wolf puppet show how much you agree.\n");

            break;
                
            case 1:
                
            say(QCTNAME(tp) + " vigorously bobs " +
                tp->query_possessive() + " gopheroo puppet up and" +
                " down. The round ears wiggle and the googly eyes" +
                " jiggle in animated agreement.\n");
            write("You let your gopheroo puppet show how much you" +
                " agree.\n");

            break;

            case 2:
                
            say(QCTNAME(tp) + " vigorously bobs " +
                tp->query_possessive() + " goofy frog puppet" +
                " up and down. The googly eyes jiggle in animated" +
                " agreement. \n");
            write("You let your frog puppet show how much you agree.\n");

            break;

        }
                
    return 1;
                
    }
             
    else

    {

        notify_fail("This is a hand puppet. Wear it on your hand! \n");
        return 0;

    }
        
}


/* Function:  puppet_shake
 * Purpose:   Show your disagreement using the puppet!
 */

int
puppet_shake()

{

    object tp = this_player();
    object target;
    if (this_object()->query_worn())

        {
            switch (n)

            {

                case 0:
                
                say(QCTNAME(tp) + " shakes " + tp->query_possessive() +
                    " wolf puppet from side to side, showing" +
                    " disagreement.\n");
                write("You let your wolf puppet show how much you" +
                    " disagree.\n");
              
                break;

                case 1:
                
                say(QCTNAME(tp) + " shakes " + tp->query_possessive() +
                    " gopheroo puppet from side to side, showing" +
                    " disagreement.\n");
                write("You let your gopheroo puppet show how much you" +
                    " disagree.\n");

                break;

                case 2:
                
                say(QCTNAME(tp) + " shakes " + tp->query_possessive() +
                    " frog puppet from side to side, showing" +
                    " disagreement.\n");
                write("You let your frog puppet show how much you" +
                    " disagree.\n");
 
                break;

            }
                
            return 1;
                
        }
             
    else

    {

        notify_fail("This is a hand puppet. Wear it on your hand! \n");
        return 0;

    }
        
}

/* Function:  puppet_speak
 * Purpose:   Speak through your puppet!
 */

int
puppet_speak(string str)

{

    object tp = this_player();
	object target;
    string *speech = ({"%s"});


    if (this_object()->query_worn())

    {

       if (!str)

        {
            notify_fail("What did you want your puppet to say?");
            return 0;
        }

        if (!parse_command(str, ({ this_object() }), " %s ", speech));

        {
        
            switch (n)

            {
             
                case 0:
                
                say("In a growly voice " + QCTNAME(tp) +
                    " says through " + tp->query_possessive() +
                    " wolf puppet: " + speech + "\n");
                write("In a growly voice you say through your" +
                    " wolf puppet: " + speech + "\n");
                
                break;

                case 1:
                
                say("In a squeaky voice " + QCTNAME(tp) +
                    " says through " + tp->query_possessive() +
                    " gopheroo puppet: " + speech + "\n");
                write("In a squeaky voice you say through your" +
                    " gopheroo puppet: " + speech + "\n");


                break;

                case 2:
                
                
                say("In a silly voice " + QCTNAME(tp) +
                    " says through " + tp->query_possessive() +
                    " frog puppet: " + speech + "\n");
                write("In a silly voice you say through your" +
                    " frog puppet: " + speech + "\n");


                break;

            }
                
        return 1;

        }

    }

    else

    {

        notify_fail("This is a hand puppet.  Wear it on your hand! \n");
        return 0;

    }
        
}

/* Function:  init
 * Purpose:   define commands available in this object (called
 *            by system when object enters a player's inventory)
 * Arguments: none
 * Returns:   nothing
 */

void
init()

{

    ::init();
    add_action(puppet_smile, "toysmile");
    add_action(puppet_frown, "toyfrown");
    add_action(puppet_nod, "toynod");
    add_action(puppet_shake, "toyshake");
    add_action(puppet_speak, "toysay");
    
}
 
/* MERRY CHRISTMAS */

