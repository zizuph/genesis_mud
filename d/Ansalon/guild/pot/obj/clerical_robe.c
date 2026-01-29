/* Stralle @ Genesis 000925
 *
 * A clerical robe for the PoT.
 *
 * Revisions:
 *  Stralle 020616: Changed ...
 */

#pragma strict_types
#pragma save_binary

inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/lib/keep";
inherit "/lib/commands";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <composite.h>
#include <files.h>
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"

#define ROBE_SUBLOC     "_pot_clerical_robe_subloc"

string gColour = "dark green";
int gHooded;

/* Function name: query_colour
 * Description:   Returns the colour previously set for the sleeves lining
 * Returns:       string - the colour
 */
string
query_colour()
{
    return gColour;
}

/* Function name: set_colour
 * Description:   Sets the colour of the sleeves according to the guild
 *                status of the player only if (s)he is a PoT. Called
 *                from enter_env()
 */
void
set_colour()
{
    if (environment()->query_guild_member(GUILD_NAME))
    {
        switch (environment()->query_priest_level())
        {
            case GUILD_LEVEL_PRIEST:
                gColour = "deep blue";
                break;
            case GUILD_LEVEL_HIGH_PRIEST:
                gColour = "dark purple";
                break;
            case GUILD_LEVEL_INITIATE:
            default:
                gColour = "dark green";
                break;
        }
    }
}

/* Function name: create_armour
 * Description:   The create function
 */
void
create_container()
{
    set_name("robe");
    set_adj(({"deep-black", "shimmering"}));
    set_short("deep-black shimmering robe");
    set_long("This is a long robe made of rich velvet fabric. It has " +
        "an iridescent black colour which shifts in green, blue and " +
        "deep purple like that of beetle wings, making it look alive. " +
        "An intricate embroidery of a five-headed multi-coloured " +
        "dragon adorns the back. The lining is made of fine " +
        "@@query_colour@@-coloured velvet. The large hood and wide sleeves are lined " +
        "with a two-inch wide band of the same material and on the " +
        "left side is a crescent of deepest black. You notice a " +
        "small caption on the inside of one of the sleeves.\n");

    add_item("caption", "The following can be done with the robe:\n\n" +
        "  bow [adverb] [target]\n" +
        "  curtsey [adverb] [target]\n" +
        "  straighten\n" +
        "  ignore <target>\n" +
        "  bored\n");

    set_slots(A_ROBE);
    set_looseness(2);
    set_layers(4);
    set_wf(TO);

    set_keep(1);
    
    add_prop(OBJ_I_VALUE, 315);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1400);

    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(CONT_I_MAX_WEIGHT, 3800);
    add_prop(CONT_I_MAX_VOLUME, 2900);
}

int
prevent_enter(object ob)
{
    if ((ob->check_weapon() || ob->check_armour()) &&
        ob->query_volume() > 1000)
        return 1;
    
    return 0;
}

/* Function name: query_recover
 * Description:   Recover code. Recovers also the colour of the sleeves
 */
string
query_recover()
{
    return MASTER + ":" + query_keep_recover() +
        "|:|" + gColour + "|:|";
}

/* Function name: init_recover
 * Description:   The init recover code
 */
void
init_recover(string arg)
{
    string colour, foobar;
    
    if (sscanf(arg, "%s|:|%s|:|%s", foobar, colour, foobar) == 3)
        gColour = colour;

    init_keep_recover(arg);
}

/* Function name: enter_env
 * Description:   Called whenever the robe enters a new environment.
 *                If entering a PoT we change the colour of the sleeves
 */
void
enter_env(object dest, object old)
{
    set_colour();

    if (function_exists("create_container", dest) == CORPSE_OBJECT)
    {
        tell_room(environment(old), "The robe worn by " +
            QTNAME(old) + " burns to a cinder.\n");
        set_alarm(0.0, 0.0, &remove_object());
    }

    ::enter_env(dest, old);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    wearable_item_leave_env(from, to);

    from->remove_subloc(ROBE_SUBLOC, TO);
}

void
destroy()
{
    tell_object(E(TO), "The " +short()+ " unravels into nothing " +
        "but motes of shadow!\n");
    remove_object();
}

/* Function name: wear
 * Description:   Called whenever we wear the robe. HEre to add a subloc
 */
int
wear(object ob)
{
    object shadow;

    if(TP->query_guild_name_occ() != "Priests of Takhisis")
    {
        set_alarm(1.0,0.0,"destroy");
        return -1;
    }

    TP->add_subloc(ROBE_SUBLOC, TO);

    setuid();
    seteuid(getuid());
    
    shadow = clone_object(GUILDDIR + "obj/clerical_robe_shadow");
    if (!shadow->shadow_me(TP))
        write("You sense a wrongness in the fabric of your robe.\n");
    else
        TP->setup_pot_hood_shadow();
    
    return 0;
}

/* Function name: remove
 * Description:   Called whenever we remove the robe. here to remove the
 *                subloc
 */
int
remove(object ob)
{
    query_worn()->remove_subloc(ROBE_SUBLOC);
    query_worn()->destroy_pot_hood_shadow();
        
    return 0;
}

/* Function name: show_subloc
 * Description:   Takes care of the subloc.
 */
string
show_subloc(string subloc, object obj, object for_obj)
{
    string str = "";

    if ((obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
        (subloc != ROBE_SUBLOC))
        return "";
    
    /* Only others can see the back on our worn robe */
    if (for_obj != obj)
    {
        str = "The back of " + HIS(obj) + " robe is adorned by " +
            "a five-headed multi-coloured dragon with glaring eyes.\n";
    }

    return str;
}

void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));
    
    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("The secret pockets of the " + short() +
            " contains " + COMPOSITE_DEAD(obarr) + ".\n");
    }
    else
    {
        for_obj->catch_tell("  The secret pockets of the " + short() +
            " are empty.\n");
    }
}

#ifdef 0
void
myallbb(string str);
{
    object *oblist, *npcs, *players;
    
    oblist = FILTER_CAN_SEE_IN_ROOM(all_inventory(environment(TP)) -
        ({ TP }));
    oblist = FILTER_IS_SEEN(TP, oblist);
    players = FILTER_PLAYERS(oblist);
    npcs = oblist - players;
    
    if (sizeof(players))
    {
        players->catch_msg(str + "\n");
    }
    
    if (sizeof(npcs))
    {
        npcs->emote_hook(query_verb(), TP, adverb, 0, cmd_attr);
    }
}
#endif

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
            if (!TP->query_pot_hooded())
            {
                notify_fail("Your hood is already raised.\n");
                return 0;
            }
            
            TP->unset_pot_hooded();
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
            if (TP->query_pot_hooded())
            {
                notify_fail("You are already hooded.\n");
                return 0;
            }
            
            TP->set_pot_hooded();
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
    
    if (query_worn() != this_player())
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
    
    if (query_worn() != this_player())
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
    if (query_worn() != this_player())
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
    
    if (query_worn() != this_player())
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
    if (query_worn() != this_player())
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
}
