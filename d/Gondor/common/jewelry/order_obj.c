/*
 * /d/Gondor/common/jewelry/order_obj.c
 *
 * This object is put into the player's inventory when ordering
 * a piece of jewelry. It is taken out when finished or when a
 * player leaves.
 *
 * Coded by Gwyneth, 08/26/02
 */
inherit "/std/object";

#include <composite.h>
#include <macros.h>
#include "jewelry.h"

#define TYPE_IND 0
#define DESC_IND 1
#define METL_IND 2
#define ENGR_IND 3

int gFlex = 0, 
    gVal = 0, 
    gNum = 0, 
    gGemMin = 0, 
    gGemMax = 0, 
    *gGemNums = ({ 0, 0 });

/* gOrder = ({ jtype, desc, metal, engraving }) */
string *gOrder,
       *gDesc, 
       *gMetals, 
       *gGems = ({ "n", "n" });

object gKeeper;

public void
create_object()
{
    set_name("slip");
    add_name(ORDER_OBJ_ID);
    set_short("order slip");

    /* Can't see this item. */
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_M_NO_DROP, "You can't drop this.");
}

public void
info(string str)
{
    environment(environment())->keeper_say(str, environment());
    write("] ");
}

public string
list_gems()
{
    int size, num;
    string *text = ({});

    size = sizeof(gGems);

    if (!size)
        return "no gems selected";

    if (gGems[1] != "n")
    {
        /* 1 diamond */
        num = gGemNums[1];
        text += ({ num + " " + (num > 1 ? LANG_PWORD(gGems[1]) :
            gGems[1])});
    }

    if (gGems[0] != "n")
    {
        num = gGemNums[0];
        /* 2 rubies */
        text += ({ num + " " + (num > 1 ? LANG_PWORD(gGems[0]) :
            gGems[0])});
    }
    else
        return "no gems selected";


    return COMPOSITE_WORDS(text) + " selected";
}

public void
remove_order_obj()
{
    environment()->keeper_say("Your order is cancelled. Start over if you " +
        "wish to continue.", environment());
    remove_object();
    return;
}

public void
finish_order()
{
    environment(environment())->set_orders(this_player()->query_real_name(), 
         gOrder[DESC_IND], gOrder[METL_IND], gOrder[TYPE_IND], 
         gGems[0], gGemNums[0], gGems[1], gGemNums[1], 
         time() + ftoi(CONSTRUCT_TIME), gVal, gOrder[ENGR_IND]);

    set_alarm(1.0, 0.0, &remove_object());
    return;
}

public void
finish_regalia()
{
    switch(gOrder[2])
    {
    case MEMBER_RANK:
        gVal = MEMBER_COST;
        break;
    case KC_RANK:
        gVal = KC_COST;
        break;
    case KGC_RANK:
        gVal = KGC_COST;
        break;
    default:
        remove_order_obj();
        return;
    }

    if (environment()->query_prop(PLAYER_I_GM_FREEBIE))
        gVal = 0;

    environment(environment())->set_regalia_orders(
        this_player()->query_real_name(), gOrder[1], gOrder[2],
        gOrder[3], gOrder[4], gGems[0], gGemNums[0], gGems[1], gGemNums[1], 
        time() + ftoi(CONSTRUCT_TIME), gVal);

    set_alarm(1.0, 0.0, &remove_object());
    return;
}

public void
choose_engraving(string str)
{
    if (!strlen(str))
    {
        gOrder += ({ "" });
        finish_order();
        return;
    }

    if (str == "~q")
    {
        remove_order_obj();
        return;
    }

    gOrder += ({ str });
    finish_order();
    return;
}

public void
choose_gems(string str, int i)
{
    int index, num, remain;
    string gem;

    if (str == "~q")
    {
        remove_order_obj();
        return;
    }

    /* It's 0 gems or the max. */
    if (!gFlex)
        gGemMin = gGemMax;

    if (!strlen(str))
    {
        if (gNum < gGemMin)
        {
            info("You need at least " + LANG_NUM2WORD(gGemMin) +
                " gemstones for this piece. You have " + list_gems() +
                " so far. Enter ~q to quit, or choose more gems. ");
            input_to(&choose_gems(, i));
            return;
        }
        else
        {
            switch(gOrder[TYPE_IND])
            {
            case "circlet":
            case "coronet":
            case "crown":
                choose_engraving(capitalize(this_player()->query_real_name()));
                return;
            case "regalia":
                finish_regalia();
                return;
            default:
                break;
            }

            info("You can hit enter now, ~q to quit or if you would " +
                "like your " + gOrder[TYPE_IND] + " to be engraved, " +
                "please enter the text you want engraved now. ");
            input_to(choose_engraving);
            return;
        }
    }

    if (!parse_command(str, ({}), "%d %w", num, gem))
    {
        info("I didn't understand you. Enter ~q to quit, hit enter when " +
            "done or enter your gem choice (ex. 1 ruby or 4 sapphire) ");
        input_to(&choose_gems(, i));
        return;
    }

    if (!num)
    {
        info("I didn't understand you. Enter ~q to quit, hit enter when " +
            "done or your enter your gem choice (ex. 1 ruby or 4 sapphire) ");
        input_to(&choose_gems(, i));
        return;
    }

    remain = gGemMax - gNum;

    if (remain < num)
    {
        info("You only have " + LANG_NUM2WORD(remain) + " gemstones " +
            "left to choose. Enter " + LANG_NUM2WORD(remain) +
            " or fewer gems or ~q to quit: ");
        input_to(&choose_gems(, i));
        return;
    }

    /* LANG_SWORD is still a little buggy. */
    if (gem == "lapis" || gem == "lazuli")
        gem = "lapis lazuli";
    else if (extract(gem, -2) == "es" && gem != "rubies" && gem != "chalcedonies")
        gem = extract(gem, 0, -2);
    else
        gem = LANG_SWORD(gem);

    index = member_array(gem, gGems);
    if (index != -1)
    {
        gGemNums[index] += num;
        gNum += num;
    }
    else
    {
        if (i < 2)
        {
            gGems[i] = gem;
            gGemNums[i] = num;
            gNum += num;
            i++;
        }
        else
        {
            info("You have already chosen two different types of gems. " +
                "You may choose more of the same, hit enter if you're done " +
                "or ~q to quit. ");
            input_to(&choose_gems(, i));
            return;
        }
    }


    if (gNum >= gGemMax)
    {
        switch(gOrder[TYPE_IND])
        {
        case "circlet":
        case "coronet":
        case "crown":
            choose_engraving(capitalize(this_player()->query_real_name()));
            return;
        case "regalia":
            finish_regalia();
            return;
        default:
            break;
        }

        info("You can hit enter now, ~q to quit or if you would " +
            "like your " + gOrder[TYPE_IND] + " to be engraved, please " +
            "enter the text you want engraved now. ");
        input_to(choose_engraving);
        return;
    }

    info("You have " + list_gems() + " so far. Enter your next gem " +
        "choices, hit enter if you're done or ~q to quit: " );
    input_to(&choose_gems(, i));
    return;
}

public void
gem_choice(string str)
{
    string txt;

    if (str == "~q")
    {
        remove_order_obj();
        return;
    }

    if (str == "n")
    {
        switch(gOrder[TYPE_IND])
        {
        case "circlet":
        case "coronet":
        case "crown":
            choose_engraving(capitalize(this_player()->query_real_name()));
            return;
        default:
            break;
        }

        info("You can hit enter now, ~q to quit or if you would " +
            "like your " + gOrder[TYPE_IND] + " to be engraved, please " +
            "enter the text you want engraved now. ");
        input_to(choose_engraving);
        return;
    }

    if (gGemMax == gGemMin)
    {
        if (gGemMax == 1)
        {
            info ("You must have one gemstone for this piece. Enter your " +
                "choice and be sure to have the gem ready for the jeweller " +
                "when he asks. (ex. 1 ruby): ");
            input_to(choose_gems);
            return;
        }
        else
            txt = "must have " + LANG_NUM2WORD(gGemMin);
    }
    else if (!gFlex)
        txt = "must have either " + LANG_NUM2WORD(gGemMax) + " or " +
            LANG_NUM2WORD(gGemMin);
    else
        txt = "may have a maximum of " + LANG_NUM2WORD(gGemMax);

    info("You " + txt + " gemstones " +
        "for this piece. You may choose up to two different types " +
        "of gems. Enter your choices one at a time and be sure you " +
        "have those gems to place on the counter when your order is " +
        "complete (ex. 3 ruby). Hit enter when finished. ");

    input_to(&choose_gems(, 0));
}

public void
metal_choice(string str)
{
    if (str == "~q")
    {
        remove_order_obj();
        return;
    }

    if (member_array(str, gMetals) == -1)
    {
        info("Not an option. Enter ~q to quit or choose from " + 
            COMPOSITE_WORDS(gMetals) + ". ");
        input_to(metal_choice);
        return;
    }

    gOrder += ({ str });

    if (gOrder[0] == "collar")
    {
        if (str == "silver")
            gVal = COLLAR_SILVER_PRICE;
        if (str == "electrum")
            gVal = COLLAR_ELECTRUM_PRICE;
        if (str == "gold")
            gVal = COLLAR_GOLD_PRICE;

        info("You can hit enter now, ~q to quit or if you would " +
            "like your " + gOrder[TYPE_IND] + " to be engraved, please " +
            "enter the text you want engraved now. ");
        input_to(choose_engraving);
        return;
    }
    else if (gOrder[1] == "simple")
        gVal = (str == "bronze" ? SIMPLE_BRONZE_PRICE : SIMPLE_SILVER_PRICE);
    else if (gOrder[1] == "knightly")
        gVal = (str == "silver" ? KNIGHTLY_SILVER_PRICE : 
            KNIGHTLY_ELECTRUM_PRICE);
    else if (gOrder[1] == "baronial")
        gVal = (str == "electrum" ? BARONIAL_ELECTRUM_PRICE : 
            BARONIAL_GOLD_PRICE);
    else if (gOrder[1] == "ducal")
        gVal = (str == "gold" ? DUCAL_GOLD_PRICE : DUCAL_PLAT_PRICE);
    else if (gOrder[1] == "princely")
    {
        if (str == "gold")
            gVal = PRINCELY_GOLD_PRICE;
        if (str == "platinum")
            gVal = PRINCELY_PLAT_PRICE;
        if (str == "mithril")
            gVal = PRINCELY_MITHRIL_PRICE;
    }
    else if (gOrder[1] == "royal")
    {
        if (str == "gold")
            gVal = ROYAL_GOLD_PRICE;
        if (str == "platinum")
            gVal = ROYAL_PLAT_PRICE;
        if (str == "mithril")
            gVal = ROYAL_MITHRIL_PRICE;
 
    }
    else
    {
        switch(str)
        {
        case "bronze":
            gVal += BRONZE_PRICE;
            break;
        case "silver":
            gVal += SILVER_PRICE;
            break;
        case "electrum":
            gVal += ELECTRUM_PRICE;
            break;
        case "gold":
            gVal += GOLD_PRICE;
            break;
        case "platinum":
            gVal += PLATINUM_PRICE;
            break;
        case "mithril":
            gVal += MITHRIL_PRICE;
            break;
        default:
            break;
        }
    }

    if (!gGemMax)
    {
        switch(gOrder[TYPE_IND])
        {
        case "circlet":
        case "coronet":
        case "crown":
            choose_engraving(capitalize(this_player()->query_real_name()));
            return;
        default:
            break;
        }

        info("You can hit enter now, ~q to quit or if you would " +
            "like your " + gOrder[TYPE_IND] + " to be engraved, please " +
            "enter the text you want engraved now. ");
        input_to(choose_engraving);
    }
    else if (!gGemMin)
    {
        info("Would you like your " + gOrder[0] + " to have any gems? (y/n) ");
        input_to(gem_choice);
    }
    else
        gem_choice("y");

    return;
}

public void
desc_choice(string str)
{
    if (str == "~q")
    {
        remove_order_obj();
        return;
    }

    if (member_array(str, gDesc) == -1)
    {
        info("That's not an option. Enter ~q to quit or choose from " + 
            COMPOSITE_WORDS(gDesc) + ". ");
        input_to(desc_choice);
        return;
    }

    if (str == "normal")
        gOrder += ({ "" });
    else
        gOrder += ({ str });

    switch(str)
    {
    case "simple":
        gMetals = ({ "bronze", "silver" });
        gGemMin = 0;
        gGemMax = 5;
        break;
    case "knightly":
        gMetals = ({ "silver", "electrum" });
        gGemMin = 0;
        gGemMax = 10;
        break;
    case "baronial":
        gMetals = ({ "electrum", "gold" });
        gGemMin = 0;
        gGemMax = 15;
        break;
    case "ducal":
        gMetals = ({ "gold", "platinum" });
        gGemMin = 25;
        gGemMax = 25;
        break;
    case "princely":
        gMetals = ({ "gold", "platinum", "mithril" });
        gGemMin = 35;
        gGemMax = 35;
        break;
    case "royal":
        gMetals = ({ "gold", "platinum", "mithril" });
        gGemMin = 50;
        gGemMax = 50;
        break;
    case "ribbon":
        gMetals = ({ "bronze", "silver", "gold" });
        break;
    case "braided":
        gMetals = ({ "bronze", "silver", "gold" });
        gVal *= 10;
        break;
    case "equestrian":
        gOrder += ({ "gold" });
        gVal = EQS_RING_PRICE;
        info("You can hit enter now, ~q to quit or if you would " +
            "like your " + gOrder[TYPE_IND] + " to be engraved, please " +
            "enter the text you want engraved now. ");
        input_to(choose_engraving);
        return;
    default:
        break;
    }

    info("Enter ~q to quit or choose one of " + COMPOSITE_WORDS(gMetals) + 
        ". ");
    input_to(metal_choice);
    return;
}

public void
regalia_gems(string str, int rank)
{
    if (!strlen(str))
    {
        info("Did you want me to use any gems in your collar?(y/n) ");
        input_to(regalia_gems);
        return;
    }

    if (str == "~q")
    {
        remove_order_obj();
        return;
    }

    if (str == "n" || str == "no")
    {
        finish_regalia();
        return;
    }

    if (str != "y" && str != "yes")
    {
        info("Did you want me to use any gems in your collar?(y/n) ");
        input_to(regalia_gems);
        return;
    }

    if (rank == KGC_RANK)
        gGemMax = 10;
    else
        gGemMax = 5;

    gGemMin = gGemMax;

    info("Please choose the first of " + LANG_NUM2WORD(gGemMax) + 
        " gems if you want more than one type of gem, or enter them all " +
        "if you want just one type. (ex. 1 diamond or 5 beryl) ");
    input_to(&choose_gems(, 0));
    return;
}

public void
choose_order(string str)
{
    int rank;
    object room;
    string emblem, colour;

    if (!strlen(str))
    {
        info("Which order did you want to purchase regalia for? " +
            "(Or ~q to quit) ");
        return;
    }

    if (str == "~q")
    {
        remove_order_obj();
        return;
    }

    (JEWELRY_DIR + "chivalry")->teleledningsanka();
    room = find_object(JEWELRY_DIR + "chivalry");
    rank = room->find_rank(str, environment()->query_real_name());
    str = room->case_check(str);

    if (rank == -1)
    {
        info("I'm sorry. You are not a member of any Order of " + str + 
            ". Enter a different order name or ~q to quit. ");
        input_to(choose_order);
        return;
    }
    
    emblem = room->query_order(str)[1];
    colour = room->query_order(str)[2];
    gOrder += ({ str, rank, emblem, colour });

    if (rank == MEMBER_RANK)
    {
        finish_regalia();
        return;
    }

    info("Did you want me to use any gems in your collar?(y/n) ");
    input_to(&regalia_gems(, rank));
    return;
}

public void
order(string str)
{
    if (str == "collar of office")
        str = "collar";

    gOrder = ({ str });

    /* This will be overwritten by the non-standard ones. */
    gMetals = METALS;

    switch(str)
    {
    case "circlet":
        gDesc = ({ "simple", "knightly" });
        info("Choose from " + COMPOSITE_WORDS(gDesc) + ". " );
        input_to(desc_choice);
        return;
    case "coronet":
        gDesc = ({ "baronial", "ducal" });
        info("Choose from " + COMPOSITE_WORDS(gDesc) + ". " );
        input_to(desc_choice);
        return;
    case "crown":
        gDesc = ({ "princely", "royal" });
        info("Choose from " + COMPOSITE_WORDS(gDesc) + ". " );
        input_to(desc_choice);
        return;
    case "ring":
        gDesc = ({ "equestrian", "normal" });
        gGemMin = 0;
        gGemMax = 3;
        gFlex = 1;
        gVal = RING_PRICE;
        info("Choose from equestrian or normal. ");
        input_to(desc_choice);
        return;
    case "pendant":
        gGemMin = 1;
        gGemMax = 1;
        gVal = NECKLACE_PRICE;
        break;
    case "necklace":
        gGemMin = 0;
        gGemMax = 100;
        gFlex = 1;
        gVal = NECKLACE_PRICE;
        break;
    case "choker":
        gGemMin = 45;
        gGemMax = 45;
        gVal = NECKLACE_PRICE;
        break;
    case "bracelet":
        gGemMin = 0;
        gGemMax = 25;
        gVal = BRACELET_PRICE;
        break;
    case "anklet":
        gGemMin = 0;
        gGemMax = 40;
        gVal = ANKLET_PRICE;
        break;
    case "torc":
        gDesc = ({ "ribbon", "braided" });
        gGemMin = 0;
        gGemMax = 0;
        gVal = TORC_PRICE;
        info("Choose from ribbon or braided. ");
        input_to(desc_choice);
        return;
    case "medal":
        gGemMin = 0;
        gGemMax = 5;
        gFlex = 1;
        gVal = MEDAL_PRICE;
        break;
    case "collar":
    case "collar of office":
        gGemMin = 0;
        gGemMax = 0;
        gMetals = ({ "silver", "electrum", "gold" });
        break;
    case "regalia":
        info("Which order would you like to purchase regalia for? ");
        input_to(choose_order);
        return;
    default:
        remove_order_obj();
        return;
    }

    /* No descs for this piece */
    gOrder += ({ "" });
    info("Enter ~q to quit or choose one of " + COMPOSITE_WORDS(gMetals) + 
        ". ");
    input_to(metal_choice);
    return;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    gKeeper = present("jeweller", environment(to));
}
