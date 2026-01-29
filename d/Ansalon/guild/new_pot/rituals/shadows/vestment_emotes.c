/* Stralle @ Genesis 000925
 *
 * A clerical robe for the PoT.
 *
 * Revisions:
 *  Stralle 020616: Changed ...
 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/lib/commands";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <composite.h>
#include <files.h>
#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"

#define ROBE_SUBLOC     "_pot_clerical_robe_subloc"

int     gHooded;
string  gColour;

public void
set_colour(string colour)
{
    gColour = colour;
}

public string
query_colour()
{
    return gColour;
}

/* Function name: create_armour
 * Description:   The create function
 */
void
create_object()
{
    set_name("robe_emotes_");
    set_short("robe emotes");
    set_long("PoT Robe Emotes\n");
    
    set_no_show();
}

int
query_hooded()
{
    return gHooded;
}

int
do_hood(string str)
{
    object shadow;

    if (!str)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    switch (query_verb())
    {
        case "raise":
        case "unhood":
            if (!TP->query_hood_worn())
            {
                notify_fail("Your hood is already raised.\n");
                return 0;
            }
            
            TP->set_hood_worn(0);
            write("You raise the hood on your robe and toss it back " +
                "over your shoulders, revealing your " +
                "features.\n");
            say(QCTNAME(TP) + " raises the hood on " + HIS(TP) + " robe " +
                "and tosses it back over " + HIS(TP) + " shoulders, " +
                "revealing " + HIS(TP) + " features.\n");
            
            return 1;
            break;

        case "lower":
        case "hood":
            if (TP->query_hood_worn())
            {
                notify_fail("You are already hooded.\n");
                return 0;
            }
            
            TP->set_hood_worn(1);
            write("You pull the hood of your robe down over your face.\n");
            say(QCTNAME(TP) + " pulls the hood on " + HIS(TP) + " robe, " +
                "down over " + HIS(TP) + " face.\n");

            return 1;
            break;
    }
    
    notify_fail("You sense a weird wrongness in the fabric of your robe.\n");
    return 0;
}    

/*
 * Emotes from here on
 */
int
do_bow(string str)
{
    object *oblist;
    string *how;
    
    if (environment() != this_player())
        return 0;

    how = parse_adverb_with_space(str, "gracefully", 0);
    
    if (!strlen(how[0]))
    {
        write("You bow" + how[1] + " making your black robe shimmer " +
            "in " + query_colour() + " with your movement.\n");
        allbb(" bows" + how[1] + " making " + HIS(TP) + " black robe " +
            "shimmer in " + query_colour() + " with " + HIS(TP) +
            " movement.");

        return 1;
    }

    oblist = parse_this(how[0], "[before] [to] [the] %l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Bow [how] to whom/what?\n");
        return 0;
    }
    
    actor("You bow" + how[1] + " before", oblist, " making your " +
        "black robe shimmer in " + query_colour() + " with your movement.");
    all2actbb(" bows" + how[1] + " before", oblist, " making " +
        HIS(TP) + " black robe shimmer in " + query_colour() + " with " +
        HIS(TP) + " movement.");
    targetbb(" bows" + how[1] + " before you making " + HIS(TP) +
        " black robe shimmer in " + query_colour() + " with " + HIS(TP) +
        " movement.", oblist);

    return 1;
}

int
do_curtsey(string str)
{
    object *oblist;
    string *how;
    
    if (environment() != this_player())
        return 0;

    how = parse_adverb_with_space(str, "gracefully", 0);
    
    if (!strlen(how[0]))
    {
        write("Curtseying" + how[1] + " your robe rustles softly as " +
            "the heavy black silk material shimmers faintly.\n");
        allbb(" curtseys" + how[1] + " making " + HIS(TP) + " robe rustle " +
            "softly as the heavy black silk material shimmers faintly.");

        return 1;
    }

    oblist = parse_this(how[0], "[before] [to] [the] %l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Curtsey [how] to whom/what?\n");
        return 0;
    }
    
    actor("Curtseying" + how[1] + " before", oblist, " your robe rustles " +
        "softly as the heavy black silk material shimmers faintly.");
    all2actbb(" curtseys" + how[1] + " before", oblist, " making " +
        HIS(TP) + " robe rustle softly as the heavy black silk material " +
        "shimmers faintly.");
    targetbb(" curtseys" + how[1] + " before you making " + HIS(TP) +
        " robe rustle softly as the heavy black silk material shimmers " +
        "faintly.", oblist);

    return 1;
}

int
do_straighten(string str)
{
    if (environment() != this_player())
        return 0;

    if (stringp(str))
    {
        notify_fail("Straighten how?\n");
        return 0;
    }
    
    write("You calmly straighten your robe, delighting in the " +
        "feeling of the soft material. You stop for a moment and feel " +
        "there is more to this robe than just fabric.\n");
    allbb(" calmly straightens " + HIS(TP) + " robe, pausing for " +
        "a moment as a confident smile crosses " + HIS(TP) + " lips.");
    
    return 1;
}

int
do_ignore(string str)
{
    object *oblist;
    int s;
    
    if (environment() != this_player())
        return 0;

    if (!str)
    {
        notify_fail("Ignore whom?\n");
        return 0;
    }
    
    oblist = parse_this(str, "[the] %l");
    s = sizeof(oblist);    

    if (!s)
    {
        notify_fail("Ignore whom?\n");
        return 0;
    }

    actor("You turn away from", oblist, " totally uninterested " +
        "in what " + (s > 1 ? "they" : HE(oblist[0])) + " might want " +
        "to say.");
    all2actbb(" turns away from", oblist, " seemingly uninterested in " +
        "what " + (s > 1 ? "they" : HE(oblist[0])) + " might want to " +
        "say.");
    targetbb(" turns away from you seemingly uninterested in what " +
        "you have to say. As " + HIS(TP) + " back is turned towards " +
        "you, you see all eyes of the five-headed dragon on the " +
        "back of " + HIS(TP) + " robe glare coldly at you.", oblist);

    return 1;
}

int
do_bored(string str)
{
    if (!objectp(this_player()->query_worn()) ||
        this_player()->query_worn() != this_player())
        return 0;

    if (stringp(str))
    {
        notify_fail("Bored what?\n");
        return 0;
    }

    write("You inspect the sleeves of your robe and flick off an " +
        "imagined speck of dust.\n");
    allbb(" inspects the sleeves of " + HIS(TP) + " robe and flicks " +
        "off a tiny speck of dust. " + C(HE(TP)) + " seems to be quite " +
        "bored.");

    return 1;
}        

int
do_change(string str)
{
    string adj;
    
    if (environment() != this_player())
        return 0;
    
    switch(str)
    {
        case "color":
        case "colour":
        if (!this_player()->query_hood_worn())
        {
            TP->set_hood_worn(1);
            write("You pull the hood of your robe down over your face.\n");
            say(QCTNAME(TP) + " pulls the hood on " + HIS(TP) + " robe, " +
                "down over " + HIS(TP) + " face.\n");
        }
        adj = this_player()->set_conceal_colour(gColour);
            break;
        case "feature":
        case "features":
        if (this_player()->query_hood_worn())
        {
            TP->set_hood_worn(0);
            write("You raise the hood on your robe and toss it back " +
                "over your shoulders, revealing your " +
                "features.\n");
            say(QCTNAME(TP) + " raises the hood on " + HIS(TP) + " robe " +
                "and tosses it back over " + HIS(TP) + " shoulders, " +
                "revealing " + HIS(TP) + " features.\n");
        }
        adj = this_player()->new_conceal_feature();
            break;
        case "hood":
        case "hooded":
        if (!this_player()->query_hood_worn())
        {
            TP->set_hood_worn(1);
            write("You pull the hood of your robe down over your face.\n");
            say(QCTNAME(TP) + " pulls the hood on " + HIS(TP) + " robe, " +
                "down over " + HIS(TP) + " face.\n");
        }
        adj = this_player()->set_conceal_colour("hooded");
            break;
    }
    
    if (adj)
    {
        write("You channel mana into the illusory enchantment " +
        "and emerge as " +
        LANG_ADDART(this_player()->query_nonmet_name()) + ".\n");
        
        return 1;
    }
    
    notify_fail("Change what? Colour, feature or hooded?\n");
    return 0;
}

int
do_read(string str)
{
    string adj;
    
    if (environment() != this_player() || str != "caption")
        return 0;
        
    write("The following can be done with the robe:\n\n" +
        "  bow [adverb] [target]\n" +
        "  curtsey [adverb] [target]\n" +
        "  straighten\n" +
        "  ignore <target>\n" +
        "  bored\n" +
        "  change <colour/feature/hooded>\n");
    
    return 1;
}

void
init()
{
    ::init();

    add_action(do_bow, "bow");
    add_action(do_curtsey, "curtsey");
    add_action(do_straighten, "straighten");
    add_action(do_ignore, "ignore");
    add_action(do_bored, "bored");

    add_action(do_hood, "raise");
    add_action(do_hood, "lower");
    add_action(do_hood, "hood");
    add_action(do_hood, "unhood");
    
    add_action(do_change, "change");
    add_action(do_read, "read");
}
