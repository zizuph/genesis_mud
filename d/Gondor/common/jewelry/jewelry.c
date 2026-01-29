/*
 * /d/Gondor/common/jewelry/jewelry.c
 *
 * A base jewelry object to allow tracking of metals, gems, descs.
 *
 * Coded by Gwyneth, 08/26/02
 */
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include "jewelry.h"

int    gNum1    = 0, 
       gNum2    = 0;
string gDesc    = "simple", 
       gMetal   = "bronze", 
       gType    = "jewelry", 
       gEngrave = "",
       gGem1    = "n", 
       gGem2    = "n";

public void    create_object();
public void    set_metal(string metal);
public void    set_desc(string desc);
public void    set_type(string jtype);
public void    set_engrave(string engrave);
public varargs void set_gems(string gem1, int num1, string gem2, int num2);
public string  gem_desc();
public void    init_jewelry();
public void    init_head_gear();
public mixed   query_auto_load();
public mixed   query_recover();
public void    init_arg(string arg);
public void    enter_env(object to, object from);
public void    leave_env(object from, object to);
public void    appraise_object(int num);
public void    init();

/* Function name: create_object
 * Description  : Create the object, set the name, call init_jewelry
 */
public void
create_object()
{
    set_name("jewelry");
    add_name(JEWELRY_ID);
    set_keep(1);
    set_alarm(1.0, 0.0, &init_jewelry());
}

/* Function name: wear
 * Description  : Called when worn
 */
public int
wear(object ob)
{
    if (ob != this_object())
        return -1;

    add_prop(OBJ_M_NO_DROP, "You must remove it before you can drop it.\n");
    add_prop(OBJ_M_NO_GIVE, "You must remove it first.\n");
    return 0;
}

public int
remove(object ob)
{
    if (ob != this_object())
        return -1;

    remove_prop(OBJ_I_NO_DROP);
    remove_prop(OBJ_I_NO_GIVE);
    return 0;
}

/* Function name: init_jewelry
 * Description  : Fixes the names and adjectives so they match with the
 *                global vars.
 */
public void
init_jewelry()
{
    int val, index;
    string str, extra_desc;

    if (strlen(gType))
        add_name(gType);

    if (strlen(gMetal))
        add_adj(gMetal);

    if (strlen(gDesc))
        add_adj(gDesc);

    if (gGem1 != "n")
        add_adj(gGem1);

    if (gGem2 != "n")
        add_adj(gGem2);

    switch(gType)
    {
    case "circlet":
    case "coronet":
    case "crown":
        init_head_gear();
        return;
    case "ring":
        config_wearable_item(A_ANY_FINGER, 2, 4, this_object());
        add_prop(OBJ_I_WEIGHT, 2+gNum1+gNum2);
        add_prop(OBJ_I_VOLUME, 2+gNum1+gNum2);

        if (gDesc == "equestrian")
        {
            val = EQS_RING_PRICE / 4;
            val *= 3;
            add_prop(OBJ_I_VALUE, val);
            set_short(gMetal + " equestrian ring");
            set_long("This ring is a simple and tasteful band -- " +
                "substantial, finely finished and of purest gold.  It is " +
                "traditionally used in some countries to identify members " +
                "of knightly families." + (strlen(gEngrave) ? 
                 " Tiny words are engraved on the inside of the ring. You " +
                 "can read them with <read words on ring>." : "") + 
                 "\n");
            return;
        }

        extra_desc = "The quality of this ring of " + gMetal + 
            " shows that it has been crafted by a master jeweller. The " +
            gMetal + " has not a single blemish, and you can almost see " +
            "your reflection in its highly polished surface.";

        switch(gNum1 + gNum2)
        {
        case 0:
            break;
        case 1:
            extra_desc += " A single " + gGem1 + " has been set in " +
                "a way that highlights the perfect beauty of the gem.";
            break;
        default:
            extra_desc += " " + capitalize(gem_desc()) + " have been set " +
                "in a way that highlights the perfect beauty of the gems.";
            break;
        }

        extra_desc += (strlen(gEngrave) ? 
            " Tiny words are engraved on the ring. You can read them with " +
            "<read words on ring>.\n" : "\n");
        set_long(extra_desc);
        val = RING_PRICE;
        break;
    case "necklace":
        set_long((strlen(gem_desc()) ? capitalize(gem_desc()) + " have been " +
            "threaded through a fine chain of " + gMetal + "." : 
            "This is a fine chain of " + gMetal + ".") + " A small " + gMetal +
            " clasp allows you to fasten the necklace comfortably around " +
            "your neck." +  (strlen(gEngrave) ? 
            " Tiny words are engraved on the " + gMetal + " clasp. You can " +
            "read them with <read words on necklace>.\n" : "\n"));
        config_wearable_item(A_NECK, 2, 4, this_object());
        add_prop(OBJ_I_WEIGHT, 25);
        add_prop(OBJ_I_VOLUME, 25);
        val = NECKLACE_PRICE;
        break;
    case "pendant":
        set_long("A single " + gGem1 + " hangs from the fine " + gMetal +
            " chain. A small " + gMetal + " clasp allows you to fasten the " +
            "pendant around your neck." +
            (strlen(gEngrave) ?
            " Tiny words are engraved on the clasp. You can read them with " +
            "<read words on pendant>.\n" : "\n"));
        config_wearable_item(A_NECK, 2, 4, this_object());
        add_prop(OBJ_I_WEIGHT, 25);
        add_prop(OBJ_I_VOLUME, 25);
        val = NECKLACE_PRICE;
        break;
    case "choker":
        set_long((strlen(gem_desc()) ? capitalize(gem_desc()) + " have been " +
            "threaded through a fine chain of " + gMetal + "." : 
            "This is a fine chain of " + gMetal + ".") + " It is just " +
            "barely long enough to fasten the " + gMetal + " clasp around " +
            "your neck." + (strlen(gEngrave) ? 
            " Tiny words are engraved on the " + gMetal + " clasp. You can " +
            "read them with <read words on choker>.\n" : "\n"));
        config_wearable_item(A_NECK, 2, 4, this_object());
        add_prop(OBJ_I_WEIGHT, 25);
        add_prop(OBJ_I_VOLUME, 25);
        val = NECKLACE_PRICE;
        break;
    case "bracelet":
        set_long((strlen(gem_desc()) ? capitalize(gem_desc()) + " have been " +
            "threaded through a fine chain of " + gMetal + "." : 
            "This is a fine chain of " + gMetal + ".") + " A small " + gMetal +
            " clasp allows you to fasten the necklace comfortably around " +
            "your wrist." +  (strlen(gEngrave) ? 
            " Tiny words are engraved on the " + gMetal + " clasp. You can " +
            "read them with <read words on bracelet>.\n" : "\n"));
        config_wearable_item(A_ANY_WRIST, 2, 4, this_object());
        add_prop(OBJ_I_WEIGHT, 20);
        add_prop(OBJ_I_VOLUME, 20);
        val = BRACELET_PRICE;
        break;
    case "anklet":
        set_long((strlen(gem_desc()) ? capitalize(gem_desc()) + " have been " +
            "threaded through a fine chain of " + gMetal + "." : 
            "This is a fine chain of " + gMetal + ".") + " A small " + gMetal +
            " clasp allows you to fasten the necklace comfortably around " +
            "your ankle." +  (strlen(gEngrave) ? 
            " Tiny words are engraved on the " + gMetal + " clasp. You can " +
            "read them with <read words on anklet>.\n" : "\n"));
        config_wearable_item(A_ANY_ANKLE, 2, 4, this_object());
        add_prop(OBJ_I_WEIGHT, 23);
        add_prop(OBJ_I_VOLUME, 23);
        val = ANKLET_PRICE;
        break;
    case "medal":
        set_long("This is a shiny " + gMetal + " medal" +
            (strlen(gem_desc()) ? " with " + gem_desc() : "") + ".\n" +
            (strlen(gEngrave) ? 
            " Engraved on the surface are the words, \"" + gEngrave + 
            "\".\n" : "\n"));
        config_wearable_item(A_NECK, 2, 4, this_object());
        add_prop(OBJ_I_WEIGHT, 30);
        add_prop(OBJ_I_VOLUME, 30);
        val = MEDAL_PRICE;
        break;
    case "torc":
        if (gDesc == "ribbon")
        {
            add_prop(OBJ_I_WEIGHT, 100);
            add_prop(OBJ_I_VOLUME, 100);
            val = TORC_PRICE;
            extra_desc = "This piece of neckwear is made of a strip of " +
                gMetal + " about three quarters of an inch wide, which has " +
                "been twisted into a helix, then bent into an almost " +
                "complete circle. ";
        }
        else
        {
            add_prop(OBJ_I_WEIGHT, 500);
            add_prop(OBJ_I_VOLUME, 500);
            val = TORC_PRICE * 10;
            extra_desc = "This piece of neckwear looks like a finely " +
                "twisted cable or rope of " + gMetal + ", with solid loops " +
                "at the front. ";
        }

        extra_desc += "The metal indicates the rank and level of " +
                "religious responsibility of the wearer. ";

        switch(gMetal)
        {
        case "bronze":
                extra_desc += "Bronze is what is worn by the great majority " +
                    "of the free, property-owning population. ";
                break;
        case "silver":
                extra_desc += "Silver indicates status as a minor cleric, " +
                    "or warrior with significant duties to the deities. ";
                break;
        case "gold":
                extra_desc += "Gold is usually reserved for clerics, or " +
                    "those who rule by the will of the gods. ";
                break;
        default:
        }

        extra_desc += "The design is vaguely reminiscent of a garotte, " +
            "making one think that perhaps the wearers were " +
            "symbolically offering themselves to the gods by wearing " +
            "them." + (strlen(gEngrave) ?
            " Tiny words are engraved on the inside of the torc. You can " +
            "read them with <read words on torc>.\n" : "\n");;

        set_long(extra_desc);
        set_short(gMetal + " " + gDesc + " torc");
        config_wearable_item(A_NECK, 2, 4, this_object());
        val /= 4;
        val *= 3;
        add_prop(OBJ_I_VALUE, val);
        return;
    case "collar":
        set_long("This collar of " + gMetal + " is used to identify " +
            "holders of major offices, such as high justices, ambassadors, " +
            "royal chancellors, or mayors of major cities.  It consists " +
            "of links in the shape of the letter \"S\" of over an inch " +
            "in height, standing for \"sovereynly\", a reminder to the " +
            "wearer that they were expected to act with the same dignity " +
            "as the head of state whose representative they were -- as well " +
            "as a reminder to others that they were in the presence of a " +
            "custodian of significant power." +
            (strlen(gEngrave) ? 
            " Tiny words are engraved on the " + gType + ". You can read " +
            "them with <read words on collar>.\n" : "\n"));
        config_wearable_item(A_NECK, 2, 4, this_object());
        add_prop(OBJ_I_WEIGHT, 40);
        add_prop(OBJ_I_VOLUME, 40);
        if (gMetal == "silver")
            val = COLLAR_SILVER_PRICE;
        else if (gMetal == "electrum")
            val = COLLAR_ELECTRUM_PRICE;
        else
            val = COLLAR_GOLD_PRICE;
        break;
    
    default:
        break;
    }

    index = member_array(gMetal, METALS);
    index = (index == -1 ? 0 : index);
    val += METAL_PRICE[index];
    val /= 4;
    val *= 3;
    add_prop(OBJ_I_VALUE, val);

    if (gNum1 && !gNum2)
        set_short(gMetal + " and " + gGem1 + " " + gType);
    else if (gNum1 && gNum2)
        set_short(gMetal + " and gemstone " + gType);
    else
        set_short(gMetal + " " + gType);
}

/* Function name: init_head_gear
 * Description  : This sets up crowns/coronets/circlets
 */
public void
init_head_gear()
{
    int val;
    string str;

    switch(gDesc)
    {
    case "simple":
        set_long("This circlet is elegant in its simplicity of design.  It's " +
            "a ring of pure " + gMetal + ", about as big around as one's " +
            "little finger, with lightly engraved patterns which cause it " +
            "to shimmer in sunlight.  It can be worn directly on the head " +
            "and used to keep one's hair in place, or can be affixed to the " +
            "top of a helmet.  " + (strlen(gem_desc()) ?  
            (capitalize(gem_desc()) + " give the impression of stars resting " +
            "on the brow of the wearer.  ") : "") + "On the inside of the " +
            "circlet you see the owner's name engraved, \"" + gEngrave + 
            "\".\n");
        str = "-flecked";
        add_prop(OBJ_I_WEIGHT, 150);
        add_prop(OBJ_I_VOLUME, 100);
        if (gMetal == "bronze")
            val = SIMPLE_BRONZE_PRICE;
        else
            val = SIMPLE_SILVER_PRICE;

        val = (!gNum1 ? val - 1000 : val);
        break;
    case "knightly":
        set_long("This circlet is substantial and richly finished.  About " +
            "an inch wide, the thick " + gMetal + " is engraved with " +
            "geometric patterns and leaf shapes, with some details " +
            "highlighted in bright enamels or gold filigree.  " +
            (strlen(gem_desc()) ? (capitalize(gem_desc())) + ", finely cut " +
            "and polished, adorn the circlet at regular intervals.  " : "") + 
            "There is no doubt in your mind that this beautiful crownlet " +
            "was made for a member of a knightly family.  On the inside " +
            "you see the name of the owner, \"" + gEngrave + "\", engraved.\n");
        str = "-flecked";
        add_prop(OBJ_I_WEIGHT, 200);
        add_prop(OBJ_I_VOLUME, 150);
        if (gMetal == "silver")
            val = KNIGHTLY_SILVER_PRICE;
        else
            val = KNIGHTLY_ELECTRUM_PRICE;

        val = (!gNum1 ? val - 2000 : val);
        break;
    case "baronial":
        set_long("This beautiful coronet is over an inch wide, the " +
            "golden hue of the underlying metal decorated with " +
            "finely-etched geometric patterns which sparkle with platinum " +
            "filigree and richly-hued enamels.  Large pearls of the finest " +
            "quality have been affixed around the top at intervals of two " +
            "inches or so.  " +
            (strlen(gem_desc()) ? (capitalize(gem_desc())) + ", adorn the " +
            "body of the coronet.  " : "") + "The name of the aristocratic " +
            "owner has been stamped into the inside, \"" + gEngrave + "\".\n");
        str = "-studded";
        add_prop(OBJ_I_WEIGHT, 400);
        add_prop(OBJ_I_VOLUME, 300);
        if (gMetal == "electrum")
            val = BARONIAL_ELECTRUM_PRICE;
        else
            val = BARONIAL_GOLD_PRICE;

        val = (!gNum1 ? val - 3000 : val);
        break;
    case "ducal":
        set_long("This finely-polished crown of purest gold takes your " +
            "breath away!  The inside is lined with ermine fur to let it " +
            "rest easily on the wearer's head, and strawberry leaves of " +
            "gold are interspersed with large pearls around the top.  The " +
            "body of the crown is liberally studded with " + gem_desc() +
            " of the highest quality and finish.  You suspect that this " +
            "crown is worth as much as a large manorhouse, but that the " +
            "owner already has plenty of those, and probably some castles " +
            "as well.  A small tag on the ermine lining identifies this " +
            "fortunate soul as \"" + gEngrave + "\".\n");
        str = "-studded";
        add_prop(OBJ_I_WEIGHT, 600);
        add_prop(OBJ_I_VOLUME, 400);
        if (gMetal == "gold")
            val = DUCAL_GOLD_PRICE;
        else
            val = DUCAL_PLAT_PRICE;

        break;
    case "princely":
        set_long("This " + gMetal + " crown surely belongs to a member of " +
            "a royal family, or one who sits at the right hand of a king!  " +
            "From the wide band, encrusted with many " + LANG_PWORD(gGem1) +
            (gGem2 != "n" ? " and " + LANG_PWORD(gGem2) : "") + ", rise " +
            "many " + gMetal + " strawberry leaves, alternating with " +
            "points topped with still more " + LANG_PWORD(gGem1) +
            (gGem2 != "n" ? " and " + LANG_PWORD(gGem2) : "") + ".  The " +
            "quality of work and detail are beyond anything you've seen " +
            "before, or even thought possible.  This hefty piece of " +
            "treasure is lined with ermine fur, to cushion the head from " +
            "its not insignificant weight.  Within the ermine you find a " +
            "small tag bearing the name \"" + gEngrave + "\".\n");
        str = "-encrusted";
        add_prop(OBJ_I_WEIGHT, 800);
        add_prop(OBJ_I_VOLUME, 600);
        if (gMetal == "gold")
            val = PRINCELY_GOLD_PRICE;
        else if (gMetal == "platinum")
            val = PRINCELY_PLAT_PRICE;
        else
            val = PRINCELY_MITHRIL_PRICE;

        break;
    case "royal":
        set_long("As you gasp at the beauty of this piece of headwear, you " +
            "can only wonder to yourself which major country's crown jewels " +
            "it belongs to.  Surely the most substantial piece of jewelry " +
            "you will ever see in your life, it consists of a " +
            "breathtakingly designed and polished band of " + gMetal +
            ", heavily encrusted with " + LANG_PWORD(gGem1) +
            (gGem2 != "n" ? " and " + LANG_PWORD(gGem2) : "") + ".  " +
            "Strawberry leaves and fleur de lys of precious metals rise " +
            "from the rim, and thick strips of " + gMetal + " arc over the " +
            "top, each one shimmering with still more " + LANG_PWORD(gGem1) +
            (gGem2 != "n" ? " and " + LANG_PWORD(gGem2) : "") +
            " and seed pearls.  Thick ermine fur protects the wearer's " +
            "brow from the weight of this treasure.  You are sure that any " +
            "head of state would be proud to own as fine a crown as " +
            LANG_POSS(gEngrave) + ".\n");
        str = "-encrusted";
        add_prop(OBJ_I_WEIGHT, 1200);
        add_prop(OBJ_I_VOLUME, 800);
        if (gMetal == "gold")
            val = ROYAL_GOLD_PRICE;
        else if (gMetal == "platinum")
            val = ROYAL_PLAT_PRICE;
        else
            val = ROYAL_MITHRIL_PRICE;

        break;
    default:
        /* Should never get here. */
        set_long("Please 'bug " + query_name() + "'. There is something " +
            "wrong with your jewelry.\n");
        add_prop(OBJ_I_WEIGHT, 200);
        add_prop(OBJ_I_VOLUME, 150);
        val = SIMPLE_BRONZE_PRICE;
        break;
    }

    val /= 4;
    val *= 3;
    add_prop(OBJ_I_VALUE, val);

    config_wearable_item(A_HEAD, 2, 4, this_object());

    if (strlen(str))
    {
        if (gNum1 && !gNum2)
        {
            set_short(gDesc + " " + gType + " of " + gGem1 + str + " " +
                gMetal);
            add_adj(gGem1 + str);
        }
        else if (gNum1 && gNum2)
        {
            set_short(gDesc + " " + gType + " of gemstone" + str + " " +
                gMetal);
            add_adj("gemstone" + str);
            add_adj("gemstone");
        }
        else
            set_short(gDesc + " " + gType + " of " + gMetal);
    }
}

/* Function name: set_metal
 * Description  : Set the type of metal the jewelry is crafted from.
 * Arguments    : string metal - the name of the metal
 */
public void
set_metal(string metal)
{
    remove_adj(gMetal);
    gMetal = metal;
}

/* Function name: set_desc
 * Description  : Set the one word description of the jewelry, such as
 *                delicate, princely, simple, etc.
 * Arguments    : string desc - the desc
 */
public void
set_desc(string desc)
{
    remove_adj(gDesc);
    gDesc = desc;
}

/* Function name: set_type
 * Description  : Set the type of jewelry, such as ring, anklet, crown, etc.
 * Arguments    : string jtype - the type of jewelry
 */
public void
set_type(string jtype)
{
    remove_name(gType);
    gType = jtype;
}

/* Function name: set_engrave
 * Description  : Set the engraving on the jewelry.
 * Arguments    : string engrave - the engraved string
 */
public void
set_engrave(string engrave)
{
    gEngrave = engrave;
}

public string
query_engrave()
{
    return gEngrave;
}

/* Function name: set_gems
 * Description  : Set which gems are used. There shouldn't be more than
 *                two different gems for our sanity.
 * Arguments    : string gem1, gem2 - the two gem names, or n for none
 *                int num1, num2 - the number of gems respecitvely
 */
public varargs void
set_gems(string gem1 = "n", int num1 = 0, string gem2 = "n", int num2 = 0)
{
    int num;

    if (gGem1 != "n")
        remove_adj(gGem1);
    if (gGem2 != "n")
        remove_adj(gGem2);

    gGem1 = gem1;
    gNum1 = num1;
    gGem2 = gem2;
    gNum2 = num2;
}

/* Function name: gem_desc
 * Description  : Gives a description for the number of gems
 * Returns      : A string along the lines of: "one ruby and twenty diamonds"
 */
public string
gem_desc()
{
    string desc;

    if (!gNum1)
        return "";

    if (gNum1 == 1)
        desc =  "one " + gGem1;
    else
        desc = LANG_NUM2WORD(gNum1) + " " + LANG_PWORD(gGem1);

    if (!gNum2)
        return desc;

    if (gNum2 == 1)
        desc += " and one " + gGem2;
    else
        desc += " and " + LANG_NUM2WORD(gNum2) + " " + LANG_PWORD(gGem2);

    return desc;
}

/* Function name: read
 * Description  : Allows the holder to read the engraving, if any.
 * Arguments    : string str - as entered by the holder
 * Returns      : 1/0 - success/fail
 */
public int
read(string str)
{
    mixed *objs;

    if (!strlen(gEngrave))
        return 0;

    if (!strlen(str))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (!parse_command(str, 
      all_inventory(this_player()) + all_inventory(environment()),
      "'engraving' / 'words' [on] %i", objs) || 
      !sizeof(NORMAL_ACCESS(objs, 0, 0)))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (objs[1] == this_object())
    {
        write("You read the words engraved on the " + short() +
            ".\n\n" + query_engrave() + "\n");
        return 1;
    }

    return 0;
}

/* Function name: query_auto_load
 * Description  : Return the filename of the object and saved variables.
 * Returns      : See description.
 */
public mixed
query_auto_load()
{
    return (MASTER + ":" + gDesc + "#" + gMetal + "#" + gType + "#" +
               gGem1 + "#" + gNum1 + "#" + gGem2 + "#" + gNum2 + "#" +
               gEngrave);
}

/* Function name: query_recover
 * Description  : Don't make it recover and autoload.
 * Returns      : 0 always
 */
public mixed
query_recover()
{
    return 0;
}

/* Function name: init_arg
 * Description  : Called when autoloading to set the different variables.
 *                Also calls init_jewelry
 * Arguments    : string arg - the auto-load argument
 */
public void
init_arg(string arg)
{
    string *arglist = explode(arg, "#");
    set_desc(arglist[0]);
    set_metal(arglist[1]);
    set_type(arglist[2]);
    set_gems(arglist[3], atoi(arglist[4]), arglist[5], atoi(arglist[6]));
    if (sizeof(arglist) > 7)
        set_engrave(arglist[7]);
    init_jewelry();
}

/* Function name: enter_env
 * Description  : Called when entering a new environment.
 *                Don't allow a person more than MAX_NUM (originally 5)
 *                jewelry pieces at a time to keep down pfile bloat.
 * Arguments    : object to - the player to check the number of pieces on
 *                object from - where it's coming from
 */
public void
enter_env(object to, object from)
{
    int i;
    object *jewelry = ({});

    ::enter_env(to, from);

    /* So, to make it livings only, test for livings. */
    if (!living(to))
    {
        return;
    }

    jewelry = deep_inventory(to);
    for (i = sizeof(jewelry) - 1; i >= 0; i--)
        if (!jewelry[i]->id(JEWELRY_ID))
            jewelry -= ({ jewelry[i] });

    if (sizeof(jewelry) > MAX_NUM)
    {
        if (living(from))
        {
            if (!this_object()->move(from))
            {
                to->catch_tell(from->query_The_name(to) + " tries to give " +
                    "you " + LANG_ADDART(short()) + ", but is unable to " +
                    "since you can't have more than " +
                    LANG_NUM2WORD(MAX_NUM) + " pieces of jewelry.\n");
                from->catch_tell(to->query_The_name(from) + " is unable to " +
                    "carry that much jewelry.\n");
            }
            else if (!this_object()->move(environment(to)))
            {
                to->catch_tell("You can't have more than " +
                    LANG_NUM2WORD(MAX_NUM) + " pieces of jewelry.\n" +
                    "You drop the " + short() + ".\n");
                tell_room(environment(to), QCTNAME(to) + " can't carry the " +
                    short() + " and drops it.\n");
            }
            else
            {
                to->catch_tell("You shouldn't have more than " +
                    LANG_NUM2WORD(MAX_NUM) + " pieces of jewelry! Please " +
                    "make a bug report and limit yourself to " +
                    LANG_NUM2WORD(MAX_NUM) + " pieces or you will randomly " +
                    "lose some when you log out.\n");
            }
        }
        else
        {
            if (!this_object()->move(from))
            {
                to->catch_tell("You can't have more than " +
                    LANG_NUM2WORD(MAX_NUM) + " pieces of jewelry.\n" +
                    "You drop the " + short() + ".\n");
                tell_room(environment(to), QCTNAME(to) + " can't carry the " +
                    short() + ".\n");
            }
            else
            {
                to->catch_tell("You shouldn't have more than " +
                    LANG_NUM2WORD(MAX_NUM) + " pieces of jewelry! Please " +
                    "make a bug report <bug " + query_name() + 
                    "> yourself to " + LANG_NUM2WORD(MAX_NUM) + " pieces " +
                    "or you will randomly lose some when you log out.\n");
            }
        }
    }

    return;
}

/* Function name: leave_env
 * Description  : Must be called in wearable_item to make sure we remove
 *                it before it leaves the inventory.
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    wearable_item_leave_env(from, to);

    if (!objectp(to))
        return;

    if (from->query_wiz_level() && !to->query_wiz_level())
        log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
            capitalize(from->query_real_name()) + " gave " +
            gType + " worth " + query_prop(OBJ_I_VALUE) + " to " +
            capitalize(to->query_real_name()) + ".\n");
}

/* Function name: appraise_object
 * Description  : Must be called in wearable_item to give the right
 *                appraisal.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

/* Function name: init
 * Description  : Add the read command to the player so they can read the
 *                engraving, if any.
 */
public void
init()
{
    ::init();

    add_action(read, "read");
}
