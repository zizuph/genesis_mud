// file name:    /d/Avenir/common/village/obj/sculptures.c
// creator(s):   Lilith, 10/98
// revisions:    
// purpose:      Clone this into rooms where you want to add 
//               sculptures and other fanciful things.
//               Then just ob->set_decor(HU_M_BUST); in the
//               cloning sequence, or let it set randomly.
//               If you want to mention it in the room desc and
//               you want the actual object to be invis, use
//               ob->set_no_show(); in the cloning sequence.
// note:           
// bug(s):
// to-do:

#pragma strict_types

inherit "/std/object";

#include "/d/Avenir/common/village/village.h"
#include "/d/Avenir/include/relation.h"
#include "/sys/stdproperties.h"

int decor;

/*
 *  Function:    set_decor
 *  Description: Sets the description of the decoration to be
 *               cloned to a room.
 *  Arguments:   i - What you want the object to look like
 */
void
set_decor(int i)
{
    string *names;
    string short;
    string long;

    if (decor > 0)
        return;

    if (i < 0)
        i = random(15);

    switch(i)
    {
        case HU_M_BUST:     /* bust-sculpture of a male human */
        {
            names = ({"alabaster", "statue", "bust", "male", "human"});
            short = "alabaster statue";
            long = "This particular sculpture is a bust carved "+
                "in white alabaster with a fine, luminous quality. "+
                " It features a male human with a "+
                "strong, square jaw and straight brows over deep-"+
                "set eyes. His face is clean-shaven and revelatory "+
                "of a strong character.\n";
        }
            break;
        case HU_F_BUST:     /* bust-sculpture of a female human */
        {
            names = ({"alabaster", "statue", "bust", "female", "human"});
            short = "lovely alabaster sculpture";
            long = "A bust carved from alabaster. It depicts a female "+
                "human whose half-lidded eyes and slightly pursed "+
                "mouth lend a sensual cast to her delicate features. "+
                "Her neck and shoulders are slender and graceful, "+
                "as revealed by the mass of hair piled atop her head. "+
                "A single lock of hair trails down her neck to nestle "+
                "between her breasts.\n";
        }
            break;
        case GN_M_BUST:     /* bust-sculpture of a male gnome */
        {
            names = ({"figure","statue", "bust", "jasper", "male", "gnome"});
            short = "figure carved from a single piece of jasper";
            long = "Here is the bust of a prosperous-looking male "+
                "gnome, carved from a solid piece of jasper. His "+
                "hair is long, with a deep wave, and it frames a "+
                "slightly gaunt face with penetrating eyes. His beard "+
                "is parted and tied in two braids, revealing an "+
                "ornately-tied cravat around his neck.\n";
        }
            break;
        case GN_F_BUST:     /* bust-sculpture of a female gnome */
        {
            names = ({"statue", "bust", "curious", "jasper", "female", "gnome"});
            short = "curious jasper sculpture";
            long = "This particular sculpture is a bust carved from "+
	      "jasper. Featured is a female gnome of tender age "+
                "and beauty. Her long hair is held away from her "+
                "face by two braids fastened at her nape in a "+
                "serpentine knot. She has a small, stubborn chin "+
                "and ageless eyes.\n";
        }
            break;
        case DW_M_BUST:     /* bust-sculpture of a male dwarf */
        {
            names = ({"sculpture", "statue", "bust", "male", "dwarf"});
            short = "imposing granite statue";
            long =  "Carved from polished granite, this bust depicts a "+
               "male dwarf. His neck and shoulders are powerfully muscled. "+
               "One hand, calloused and scarred from battle, is shown "+
               "fisted over his heart and full, "+
               "wavy beard. There is an astonishingly fierce, almost "+
               "zealous, look in his eyes.\n";
        }
            break;
        case DW_F_BUST:      /* bust-sculpture of a female dwarf */
        {
            names = ({"sculpture", "statue", "bust", "female", "dwarf"});
            short = "intriguing granite sculpture";
            long = "Your gaze lingers upon this bust of a female dwarf "+
               "carved from granite. Her eyes are luminous in a "+
               "square, strong face. Her nose is long, with flaring "+
               "nostrils. Her short hair forms ringlets that are held "+
               "away from her face by an ornately embroidered sash "+
               "whose ends drape her left shoulder.\n";
        }
            break;
        case GO_M_BUST:     /* bust-sculpture of a male goblin */
        {
            names = ({"sculpture", "statue", "bust", "male", "goblin", 
               "jacinth"});
            short = "large jacinth bust";
            long = "An imposing bust, carved from jacinth, depicting a "+
               "male goblin in his prime. The massive, shaggy head "+
               "rests atop a thick, muscular neck. Fine fur covers "+
               "his round face, and his huge eyes seem to stare kind"+
               "ly into your own. Four eyeteeth jut from lips parted "+
               "in the grimace known to be a smile among goblin-kind.\n";
        }
            break;
        case GO_F_BUST:     /* bust-sculpture of a female goblin */
        {
            names = ({"sculpture", "statue", "bust", "goblin", "female",
               "jacinth"});
            short = "interesting jacinth sculpture";
            long = "This sculpture is the bust of a female goblin, carved "+
               "into a block of jacinth. A variety of treasures have "+
               "been tied into her wildly tangled hair. Her eyes are "+
               "huge, limpid pools of innocence trapped in a crude and "+
               "craggy face.\n";
        }
            break;
        case DRAGON:       /* bronze dragon sculpture */
        {
            names = ({"statue", "dragon", "two-headed"});
            short = "statue of a two-headed dragon";
            long = "This statue has been cast in bronze. It depicts a "+
                "two-headed dragon whose impossibly long tail is wrapped "+
                "protectively about it. The two wedge-shaped heads are "+
                "turned upon their long necks so that they stare eye-"+
                "to-eye. There is something powerful about this figure, "+
                "something that sends a riff of primal fear and recognition "+
                "up your spine to set the skin at the nape of your neck "+
                "to tingling.\n";
        }
            break;
        case CAT:
        {
            names = ({"statue", "cat", "feline", "gripping"});
            short = "gripping feline sculpture";
            long = "Beautifully done, this sculpture catches a cat in "+
                "mid-spring, with front claws extended and jaws open "+
                "to reveal wicked fangs. Every line is so fluid that "+
                "the muscles seem to ripple before your eyes. It has "+
                "been carved from black soapstone that is polished to "+
                "a mellow lustre.\n";
        }
            break;
        case TREFOIL:
        {
            names = ({"statue", "trefoil", "rings", "copper"});
            short = "sculpture of a trefoil in copper";
            long = "A sculpture composed of three interlocking rings "+
                "of verdigris copper. The rings seem to rotate in "+
                "the faint breeze, adding a sense of movement to "+
                "the otherwise static linear background of hedgerow "+
                "and cobbled street.\n";
        }
        default: 
        {
            names = ({"statue", "shapes", "abstract", "geometric"});
            short = "abstract geometric sculpture";
            long = "This is an abstract sculpture which brings together a "+
                "harmonious assortment of geometrical shapes carved from "+
                "several different types of stone.\n";
        }
            break;
    }
    decor = i;
    set_name("sculpture");
    add_name(names);
    add_adj(names);
    set_short(short);
    set_long(long);
}

/*
 *  Function:    get_check
 *  Description: Test if the living can get this object
 *  Arguments:   string str 
 *  Returns:     0 - Yes, it can be gotten; 1 - No it can't be.
 */
int 
get_check(string str)
{
    if (IS_SYBARITE(this_player()))
        return 0;
    else
    {
        write("You can't seem to get your arms around it.\n");     
        return 1;
    }
}


/* Create the object */
void
create_object()
{
    set_name("sculpture");
    set_adj("elegant");

    add_prop(OBJ_I_VOLUME, 30000);
    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(OBJ_I_VALUE, 3000 + random(1000));
    add_prop(OBJ_M_NO_GET, get_check);
    add_prop(OBJ_M_NO_SELL, "I don't have room for it, sorry.\n");

    /* Set the long and short */
    set_alarm(2.0, 0.0, &set_decor(-1));
}


/*
 *  Function:
 *  Description:
 *  Arguments:
 *  Returns:
 */


